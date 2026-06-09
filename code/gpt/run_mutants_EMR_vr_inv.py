import os
import re
import glob
import shutil
import subprocess
LARGE_DIR = "/home/robot/cp/InvariantMR/1_daikon_mt_gpt/inv/1_inv_project/mutation_arrange_vr"
UM_CMD = "mutate"                       
CXX_CMD = "g++"              
CXX_FLAGS = ["-O0", "-g", "-std=c++17"]       
TIMEOUT_SECONDS = 5              
NEW_MAIN_CODE = """int main() {
    srand(time(NULL));
    int status_end = 1;
    int failed_count = 0;
    std::vector<int> failed_ids; // 用于保存失败的测试用例编号
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z3runTest(i);
        if (result.status == 0) {
            status_end = 0;
            failed_count++;
            failed_ids.push_back(i); // 将失败的测试用例编号(索引i)加入容器
        }
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    // 计算 Violation Rate
    double violation_rate = static_cast<double>(failed_count) / num_test_cases;
    // 1. 输出 status_end 和 violation_rate
    std::cout << "Status End: " << status_end << std::endl;
    std::cout << "Violation Rate: " << violation_rate << " (" << failed_count << "/" << num_test_cases << ")" << std::endl;
    // 2. 输出失败的测试用例编号
    std::cout << "Failed Test Case IDs: ";
    if (failed_ids.empty()) {
        std::cout << "None"; // 如果全通过，输出None
    } else {
        for (size_t i = 0; i < failed_ids.size(); i++) {
            std::cout << failed_ids[i];
            // 格式化输出，不在最后一个编号后加逗号
            if (i != failed_ids.size() - 1) {
                std::cout << ", ";
            }
        }
    }
    std::cout << std::endl;
    return 0;
}"""

def extract_mr_file_parts(mr_file_path):
    """
    解析 MR_ 开头的文件，提取头部（using namespace std;及以上）
    和尾部（typedef struct及以下），去掉中间的原始SUT函数。
    """
    with open(mr_file_path, 'r', encoding='utf-8') as f:
        content = f.read()
    pattern = re.compile(r'(using\s+namespace\s+std\s*;)(.*?)(typedef\s+struct\s*\{)', re.DOTALL)
    match = pattern.search(content)
    if not match:
        print(f"[Error] 无法在 {mr_file_path} 中找到特征锚点(using namespace std; 或 typedef struct)")
        return None, None
    prefix = content[:match.end(1)]
    suffix = content[match.start(3):]
    return prefix, suffix

def generate_mutants(sut_file_path, output_dir):
    """
    对 SUT 文件生成突变体，并提取所有突变体内容作为 F 列表返回
    """
    temp_mutant_dir = os.path.join(output_dir, "temp_mutants")
    if os.path.exists(temp_mutant_dir):
        shutil.rmtree(temp_mutant_dir)
    os.makedirs(temp_mutant_dir, exist_ok=True)
    print(f"    [INFO] 正在为 {os.path.basename(sut_file_path)} 生成突变体...")
    try:
        cmd = [UM_CMD, sut_file_path, "--mutantDir", temp_mutant_dir]
        subprocess.check_call(cmd, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    except Exception as e:
        print(f"    [Error] UniversalMutator 运行失败: {e}")
        return []
    mutant_files = glob.glob(os.path.join(temp_mutant_dir, "*.cpp")) + glob.glob(os.path.join(temp_mutant_dir, "*.c"))
    mutants_content = []
    for mf in mutant_files:
        if "mutant" in os.path.basename(mf) or os.path.basename(mf) != os.path.basename(sut_file_path):
            with open(mf, 'r', encoding='utf-8') as f:
                mutants_content.append(f.read())
    shutil.rmtree(temp_mutant_dir)
    return mutants_content

def process_t_folder(t_folder, sut_file_path, mutants_content, failed_comp_ids):
    """
    处理最底层的 T 文件夹：注入突变体，编译，运行，并记录结果。
    接受 failed_comp_ids 集合，若存在于集合中，则跳过编译直接跳过。
    """
    mr_files = glob.glob(os.path.join(t_folder, "MR_*.cpp"))
    if not mr_files:
        print(f"    [WARN] 在 {t_folder} 中未找到 MR_ 开头的 cpp 文件。")
        return
    mr_file = mr_files[0]
    prefix, suffix = extract_mr_file_parts(mr_file)
    if not prefix or not suffix:
        return
    run_func_name = "z3runTest"         
    func_pattern = re.search(r'TestResult\s+([a-zA-Z0-9_]+)\s*\(\s*int\s+[a-zA-Z0-9_]+\s*\)', suffix)
    if func_pattern:
        run_func_name = func_pattern.group(1)
    else:
        print(f"    [WARN] 未能自动识别到 runTest 函数名，默认使用 z3runTest")
    DYNAMIC_MAIN_CODE = NEW_MAIN_CODE.replace("z3runTest", run_func_name)
    main_pattern = re.compile(r'int\s+main\s*\([^)]*\)\s*\{.*', re.DOTALL)
    if main_pattern.search(suffix):
        new_suffix = main_pattern.sub(DYNAMIC_MAIN_CODE, suffix)
    else:
        new_suffix = suffix + "\n\n" + DYNAMIC_MAIN_CODE
    total_generated = len(mutants_content)
    total_compiled = 0
    total_detected = 0
    detected_mutants_list = []
    mutant_rates = {}
    print(f"    [INFO] 开始处理 T 文件夹: {t_folder}")
    print(f"    [INFO] 共需评估 {total_generated} 个突变体...")
    for i, mutant_f in enumerate(mutants_content, start=1):
        mutation_folder = os.path.join(t_folder, f"mutation_file_{i}")
        os.makedirs(mutation_folder, exist_ok=True)
        mutated_mr_path = os.path.join(mutation_folder, f"mutated_MR_{i}.cpp")
        with open(mutated_mr_path, 'w', encoding='utf-8') as f:
            f.write(prefix + "\n\n")
            f.write("// ================= MUTANT =================\n")
            f.write(mutant_f + "\n")
            f.write("// ==========================================\n\n")
            f.write(new_suffix)
        if i in failed_comp_ids:
            continue
        exe_path = os.path.abspath(os.path.join(mutation_folder, "test_runner.exe"))
        compile_cmd = [CXX_CMD] + CXX_FLAGS + [mutated_mr_path, "-o", exe_path]
        compile_proc = subprocess.run(compile_cmd, capture_output=True)
        if compile_proc.returncode != 0:
            failed_comp_ids.add(i)
            continue
        total_compiled += 1
        current_violation_rate = 0.0                        
        try:
            run_proc = subprocess.run(
                [exe_path],
                capture_output=True,
                text=True,
                timeout=TIMEOUT_SECONDS,
                cwd=mutation_folder
            )
            output_str = run_proc.stdout.strip()
            rate_match = re.search(r"Violation Rate:\s*([0-9.]+)", output_str)
            if rate_match:
                current_violation_rate = float(rate_match.group(1))
            if run_proc.returncode != 0:
                current_violation_rate = 1.0
            if run_proc.returncode != 0 or "Status End: 0" in output_str:
                total_detected += 1
                detected_mutants_list.append(str(i))
        except subprocess.TimeoutExpired:
            total_detected += 1
            detected_mutants_list.append(str(i))
            current_violation_rate = 1.0
        mutant_rates[i] = current_violation_rate
    avg_rate = sum(mutant_rates.values()) / len(mutant_rates) if mutant_rates else 0.0
    result_txt_path = os.path.join(t_folder, "mutant_result.txt")
    with open(result_txt_path, 'w', encoding='utf-8') as f:
        f.write(f"Total Mutants Generated: {total_generated}\n")
        f.write(f"Total Mutants Compiled: {total_compiled}\n")
        f.write(f"Total Mutants Detected: {total_detected}\n")
        f.write(f"Average Violation Rate: {avg_rate:.4f}\n")
        f.write(f"Detected Mutant IDs: {', '.join(detected_mutants_list) if detected_mutants_list else 'None'}\n")
        f.write("\n=== Individual Mutant Violation Rates ===\n")
        if mutant_rates:
            for m_id, rate in sorted(mutant_rates.items()):
                f.write(f"Mutant {m_id}: {rate:.4f}\n")
        else:
            f.write("None (No mutants compiled successfully)\n")
    print(f"    [DONE] {t_folder} 测试完成. 检出率: {total_detected}/{total_compiled}, 平均 Violation Rate: {avg_rate:.4f}")

def aggregate_q_results(q_path):
    print(f"  [汇总] 正在汇总 Q 文件夹: {q_path} 下的所有结果...")
    result_files = glob.glob(os.path.join(q_path, "*", "mutant_result.txt"))
    if not result_files:
        print("    [WARN] 未找到任何 mutant_result.txt 无法汇总。")
        return
    total_gen = 0
    total_comp = 0
    all_detected_ids = set()
    t_folder_stats = []
    for rf in result_files:
        t_folder_name = os.path.basename(os.path.dirname(rf))
        local_compiled = 0
        local_detected = 0
        local_avg_rate = 0.0
        with open(rf, 'r', encoding='utf-8') as f:
            lines = f.readlines()
            for line in lines:
                line = line.strip()
                if line.startswith("Total Mutants Generated:"):
                    total_gen = int(line.split(":")[1].strip())
                elif line.startswith("Total Mutants Compiled:"):
                    local_compiled = int(line.split(":")[1].strip())
                    total_comp = local_compiled                   
                elif line.startswith("Total Mutants Detected:"):
                    local_detected = int(line.split(":")[1].strip())
                elif line.startswith("Average Violation Rate:"):
                    local_avg_rate = float(line.split(":")[1].strip())
                elif line.startswith("Detected Mutant IDs:"):
                    ids_str = line.split(":", 1)[1].strip()
                    if ids_str and ids_str != "None":
                        current_ids = [x.strip() for x in ids_str.split(',')]
                        all_detected_ids.update(current_ids)
        t_folder_stats.append({
            "name": t_folder_name,
            "detected": local_detected,
            "compiled": local_compiled,
            "avg_rate": local_avg_rate
        })
    sorted_unique_ids = sorted(list(all_detected_ids), key=lambda x: int(x))
    total_detected_all = len(sorted_unique_ids)
    all_result_path = os.path.join(q_path, "mutant_all_result.txt")
    with open(all_result_path, 'w', encoding='utf-8') as f:
        f.write("=== Global Aggregated Results ===\n")
        f.write(f"Total Mutants Generated: {total_gen}\n")
        f.write(f"Total Mutants Compiled: {total_comp}\n")
        f.write(f"Total Mutants Detected_All: {total_detected_all}\n")
        global_score_pct = (total_detected_all / total_comp * 100) if total_comp > 0 else 0.0
        f.write(f"Global Mutation Score: {total_detected_all}/{total_comp} ({global_score_pct:.2f}%)\n")
        f.write(f"All Detected Mutant IDs: {', '.join(sorted_unique_ids) if sorted_unique_ids else 'None'}\n")
        f.write("\n=== Individual T Folder Scores ===\n")
        t_folder_stats.sort(key=lambda x: x["name"])
        for stat in t_folder_stats:
            d = stat["detected"]
            c = stat["compiled"]
            pct = (d / c * 100) if c > 0 else 0.0
            avg_rate = stat["avg_rate"]
            f.write(f"Folder [{stat['name']}]: {d}/{c} ({pct:.2f}%) | Avg Violation Rate: {avg_rate:.4f}\n")
    print(f"  [汇总完成] 汇总文件已保存至: {all_result_path}")

def main(target_dir):
    if not os.path.exists(target_dir):
        print(f"[Error] 大文件夹路径不存在: {target_dir}")
        return
    for q_name in os.listdir(target_dir):
        q_path = os.path.join(target_dir, q_name)
        if not os.path.isdir(q_path):
            continue
        print(f"\n[SCAN] 正在处理 Q 文件夹: {q_name}")
        sut_files = [f for f in os.listdir(q_path) if f.endswith('.cpp')]
        if not sut_files:
            print(f"  [WARN] 在 {q_path} 下未找到基础 cpp 文件，跳过...")
            continue
        sut_file_path = os.path.join(q_path, sut_files[0])
        mutants_content = generate_mutants(sut_file_path, q_path)
        if not mutants_content:
            print(f"  [WARN] 未能生成任何突变体，跳过该 Q 文件夹...")
            continue
        failed_compilation_ids = set()
        for t_name in os.listdir(q_path):
            t_path = os.path.join(q_path, t_name)
            if os.path.isdir(t_path):
                mr_files = glob.glob(os.path.join(t_path, "MR_*.cpp"))
                if mr_files:
                    process_t_folder(t_path, sut_file_path, mutants_content, failed_compilation_ids)
        aggregate_q_results(q_path)
if __name__ == "__main__":
    print(f"\n========== 开始处理 LARGE_DIR ==========\n路径: {LARGE_DIR}")
    main(LARGE_DIR)
