import subprocess
import os
import re
import shutil
import sys                
from Test_deepseek import check_code

def copy_parent_cpp_to_main(main_dir):
    """
    将 main_dir 父目录下唯一的 .cpp 文件复制到 main_dir 下
    """
    parent_dir = os.path.dirname(main_dir)
    if not os.path.isdir(parent_dir):
        print(f"错误: 父目录不存在 {parent_dir}")
        return False
    cpp_files = [f for f in os.listdir(parent_dir)
                 if f.endswith('.cpp') and os.path.isfile(os.path.join(parent_dir, f))]
    if len(cpp_files) == 0:
        print(f"错误: 父目录 {parent_dir} 下未找到 .cpp 文件")
        return False
    if len(cpp_files) > 1:
        print(f"警告: 父目录下存在多个 .cpp 文件: {cpp_files}，将使用第一个: {cpp_files[0]}")
    src = os.path.join(parent_dir, cpp_files[0])
    dst = os.path.join(main_dir, cpp_files[0])
    try:
        shutil.copy2(src, dst)
        print(f"已复制 {src} -> {dst}")
        return True
    except Exception as e:
        print(f"复制失败: {e}")
        return False

def extract_cpp_return_type(cpp_path):
    """
    解析 cpp 文件，提取首个函数的返回值类型
    """
    with open(cpp_path, 'r', encoding='utf-8', errors='ignore') as f:
        content = f.read()
    pattern = r'^\s*([A-Za-z0-9_:\s\*<>]+?)\s+[A-Za-z_][A-Za-z0-9_]*\s*\('
    match = re.search(pattern, content, re.MULTILINE)
    if match:
        data_type = match.group(1).strip()
        is_array = 1 if ('*' in data_type or '[' in data_type) else 0
        return data_type, is_array
    return "unknown_type", 0

def gene_MR_OR(main_dir):
    """
    遍历 main_dir 下所有 MR_ 开头的文件夹，利用 main_dir 下唯一的 .cpp 文件生成 MR_OR.txt
    """
    if not os.path.exists(main_dir):
        print(f"错误: 大文件夹路径不存在 {main_dir}")
        return
    cpp_files = [f for f in os.listdir(main_dir) if f.endswith('.cpp') and os.path.isfile(os.path.join(main_dir, f))]
    if not cpp_files:
        print(f"错误: {main_dir} 下未找到 .cpp 文件")
        return
    cpp_file_path = os.path.join(main_dir, cpp_files[0])
    data_type, is_array = extract_cpp_return_type(cpp_file_path)
    for t_folder in os.listdir(main_dir):
        t_folder_path = os.path.join(main_dir, t_folder)
        if not os.path.isdir(t_folder_path) or not t_folder.startswith("MR_"):
            continue
        parts = t_folder.split('_')
        if len(parts) >= 2 and parts[1].isdigit():
            folder_id = int(parts[1])
        else:
            print(f"警告: 无法从文件夹名 {t_folder} 中提取有效的 id")
            continue
        info_file_path = os.path.join(t_folder_path, "MR_info.txt")
        if not os.path.exists(info_file_path):
            print(f"跳过: {t_folder} (未找到 MR_info.txt)")
            continue
        invariant_condition = ""
        with open(info_file_path, 'r', encoding='utf-8') as info_f:
            for line in info_f:
                if "Invariant:" in line:
                    invariant_condition = line.split("Invariant:", 1)[1].strip()
                    break
        if not invariant_condition:
            print(f"警告: {t_folder}/MR_info.txt 中未找到 Invariant 内容")
            continue
        result_content = check_code(data_type, folder_id, is_array, invariant_condition)
        or_file_path = os.path.join(t_folder_path, "MR_OR.txt")
        with open(or_file_path, 'w', encoding='utf-8') as or_f:
            or_f.write(str(result_content))
        print(f"成功处理: {t_folder} -> 生成了 MR_OR.txt")

def generate_combined_cpp(main_folder_path):
    """
    遍历 main_folder_path 下所有 MR_* 文件夹，利用根目录下的 .cpp 生成组合 C++ 文件
    """
    if not os.path.exists(main_folder_path):
        print(f"错误: 路径不存在 {main_folder_path}")
        return
    headers = "\n".join([
        "#include <cstdio>", "#include <cstdlib>", "#include <ctime>",
        "#include <cstring>", "#include <cmath>", "#include <climits>",
        "#include <cfloat>", "#include <cctype>", "#include <iostream>",
        "#include <string>", "#include <vector>", "#include <algorithm>",
        "using namespace std;", ""
    ])
    cpp_files = [f for f in os.listdir(main_folder_path) if f.endswith('.cpp') and os.path.isfile(os.path.join(main_folder_path, f))]
    if not cpp_files:
        print(f"错误: {main_folder_path} 下未找到 .cpp 文件")
        return
    cpp_file_path = os.path.join(main_folder_path, cpp_files[0])
    input_code = ""
    with open(cpp_file_path, 'r', encoding='utf-8') as cpp_file:
        input_code = cpp_file.read()
    data_type, is_array = extract_cpp_return_type(cpp_file_path)
    size_var = "n"
    match_params = re.search(r"\((.*?)\)\s*\{", input_code, re.DOTALL)
    if match_params:
        params = match_params.group(1).split(',')
        for p in reversed(params):
            p = p.strip()
            if p.startswith("int ") or " int " in f" {p} ":
                size_var = p.split()[-1]
                break
    pattern = r"static\s+([a-zA-Z_]\w*)\s+([a-zA-Z_]\w*)\s*\[[^\]]*\]\s*;"
    replacement = rf"\1* \2 = (\1*)malloc({size_var} * sizeof(\1));"
    input_code = re.sub(pattern, replacement, input_code)
    return_type = "unknown_type"
    match = re.search(r'^\s*([A-Za-z0-9_:\s\*<>]+?)\s+[A-Za-z_][A-Za-z0-9_]*\s*\(', input_code, re.MULTILINE)
    if match:
        return_type = match.group(1).strip()
    for t_folder in os.listdir(main_folder_path):
        t_folder_path = os.path.join(main_folder_path, t_folder)
        if not os.path.isdir(t_folder_path) or not t_folder.startswith("MR_"):
            continue
        parts = t_folder.split('_')
        if len(parts) >= 2 and parts[1].isdigit():
            k = parts[1]
        else:
            continue
        try:
            with open(os.path.join(t_folder_path, "MR_test_cases.txt"), 'r', encoding='utf-8') as f:
                test_cases_code = f.read().strip()
            test_cases_code = re.sub(
                r'\}\s*TestResult;',
                r'    int status;\n} TestResult;',
                test_cases_code
            )
            with open(os.path.join(t_folder_path, "MR_IO.txt"), 'r', encoding='utf-8') as f:
                zkChange = f.read().strip()
            with open(os.path.join(t_folder_path, "MR_OR.txt"), 'r', encoding='utf-8') as f:
                zkcheck = f.read().strip()
            with open(os.path.join(t_folder_path, "run_info.txt"), 'r', encoding='utf-8') as f:
                run_info_lines = f.read().split('\n')
            modified_run_lines = []
            n_param = "unknown_n"
            for line in run_info_lines:
                if "source" in line and "=" in line and n_param == "unknown_n":
                    match_params = re.search(r'\((.*?)\)', line)
                    if match_params:
                        params_str = match_params.group(1)
                        params = [p.strip() for p in params_str.split(',')]
                        for p in params:
                            if re.search(r'(n|N|size|end)', p):
                                n_param = p
                                break
                modified_run_lines.append(line)
                if "test_result.result1 = source;" in line:
                    if is_array == 0:
                        insert_line1 = f"    int status = z{k}check(source, follow);"
                    else:
                        insert_line1 = f"    int status = z{k}check(source, follow, {n_param});"
                    insert_line2 = f"    test_result.status = status;"
                    modified_run_lines.append(insert_line1)
                    modified_run_lines.append(insert_line2)
            zkrunTest = "\n".join(modified_run_lines)
            main_code = (
                f"int main() {{\n"
                f"    srand(time(NULL));\n"
                f"    int status_end = 1;\n"
                f"    for (int i = 0; i < num_test_cases; i++) {{\n"
                f"        TestResult result = z{k}runTest(i);\n"
                f"        if (result.status == 0) status_end = 0;\n"
                f"        for (int j = 0; j < result.memory_count; j++) {{\n"
                f"            free(result.memory_to_free[j]);\n"
                f"        }}\n"
                f"        free(result.memory_to_free);\n"
                f"    }}\n"
                f"    std::cout << status_end << std::endl;\n"
                f"    return 0;\n"
                f"}}"
            )
            complete_code_parts = [
                headers,
                input_code,
                test_cases_code,
                zkChange,
                zkcheck,
                zkrunTest,
                main_code
            ]
            final_cpp_content = "\n\n".join(complete_code_parts)
            output_path = os.path.join(t_folder_path, f"MR_combined_{k}.cpp")
            with open(output_path, 'w', encoding='utf-8') as out_f:
                out_f.write(final_cpp_content)
            print(f"成功组装: {output_path} (提取的返回值类型: {return_type})")
        except Exception as e:
            print(f"处理 {t_folder_path} 时发生错误: {e}")

def compile_and_run_cpp(main_folder_path):
    """
    遍历 main_folder_path 下所有 MR_* 文件夹，编译运行其中的 MR_combined_*.cpp，
    将所有结果汇总到 main_folder_path/run_result.txt
    """
    if not os.path.exists(main_folder_path):
        print(f"错误: 文件夹路径不存在 {main_folder_path}")
        return
    all_results = []
    for folder_c in os.listdir(main_folder_path):
        path_c = os.path.join(main_folder_path, folder_c)
        if not os.path.isdir(path_c) or not folder_c.startswith("MR_"):
            continue
        cpp_file_path = None
        for f in os.listdir(path_c):
            if f.startswith("MR_") and f.endswith(".cpp"):
                cpp_file_path = os.path.join(path_c, f)
                break
        if not cpp_file_path:
            continue
        exec_name = "temp_exec.out" if os.name != 'nt' else "temp_exec.exe"
        exec_path = os.path.join(path_c, exec_name)
        result_entry = f"[{folder_c}]: "
        try:
            compile_cmd = ["g++", cpp_file_path, "-o", exec_path]
            compile_process = subprocess.run(compile_cmd, capture_output=True, text=True)
            if compile_process.returncode != 0:
                result_entry += f"编译失败\nError:\n{compile_process.stderr.strip()}"
            else:
                run_process = subprocess.run([exec_path], capture_output=True, text=True, timeout=5)
                if run_process.returncode == 0:
                    output = run_process.stdout.strip()
                    result_entry += f"运行成功, 输出: {output}"
                else:
                    result_entry += f"运行时错误 (返回码: {run_process.returncode})\nError:\n{run_process.stderr.strip()}"
        except subprocess.TimeoutExpired:
            result_entry += "执行超时 (可能存在死循环)，已强制终止。"
        except Exception as e:
            result_entry += f"发生未知异常: {str(e)}"
        finally:
            if os.path.exists(exec_path):
                try:
                    os.remove(exec_path)
                except:
                    pass
        all_results.append(result_entry)
        print(f"处理完成: {folder_c}")
    if all_results:
        result_file_path = os.path.join(main_folder_path, "run_result.txt")
        with open(result_file_path, 'w', encoding='utf-8') as rf:
            rf.write("\n\n".join(all_results) + "\n")
        print(f"====== 已生成汇总文件: {result_file_path} ======\n")
if __name__ == "__main__":
    if len(sys.argv) > 1:
        main_folder_path = sys.argv[1]
    else:
        main_folder_path = input("请输入 P_Info 所在的文件夹路径: ").strip()
    if not main_folder_path:
        print("错误: 未提供有效的文件夹路径，程序退出。")
        sys.exit(1)
    if not copy_parent_cpp_to_main(main_folder_path):
        print("终止执行：无法获取源 .cpp 文件。")
        sys.exit(1)
    gene_MR_OR(main_folder_path)
    generate_combined_cpp(main_folder_path)
    compile_and_run_cpp(main_folder_path)
