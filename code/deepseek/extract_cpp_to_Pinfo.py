import os
import re
import glob
import shutil
import sys                  

def parse_final_txt(filepath):
    """
    解析 final*.txt 文件，提取 Operation 和 Invariant。
    返回格式: [(k, n, operation_text, invariant_text), ...]
    """
    results = []
    with open(filepath, 'r', encoding='utf-8') as f:
        content = f.read()
    blocks = re.split(r'-{20,}|={20,}', content)
    for block in blocks:
        if 'Operation' not in block or 'Invariant:' not in block:
            continue
        k_match = re.search(r'Operation\s+(\d+):([^\n]+)', block)
        if not k_match:
            continue
        k = k_match.group(1)
        op_content = k_match.group(0).strip()
        inv_match = re.search(r'Invariant:\s*(.*?)(?=MR\s*：|$)', block, re.DOTALL)
        if not inv_match:
            continue
        inv_text = inv_match.group(1).strip()
        if not inv_text:
            continue
        inv_lines = inv_text.split('\n')
        n = 1
        for line in inv_lines:
            clean_line = line.strip()
            if not clean_line:
                continue
            if "size(return.result1[]) == size(return.result2[])" in clean_line:
                continue
            clean_line = clean_line.rstrip('✓○ ')
            results.append((k, n, op_content, clean_line))
            n += 1
    return results

def extract_cpp_blocks(cpp_content):
    """
    使用正则表达式精准提取 cpp 文件中的三个目标代码块
    """
    tc_pattern = r'(typedef struct\s*\{.*?int num_test_cases\s*=\s*\d+;.*?\}\s*TestResult;)'
    tc_match = re.search(tc_pattern, cpp_content, re.DOTALL)
    tc_text = tc_match.group(1) if tc_match else ""
    change_pattern = r'(TestCase\s+z\d+Change\(.*?\})(?=\s*(?://[^\n]*\n\s*)*TestResult\s+z\d+runTest)'
    change_match = re.search(change_pattern, cpp_content, re.DOTALL)
    change_text = change_match.group(1) if change_match else ""
    run_pattern = r'(TestResult\s+z\d+runTest\(.*?\})(?=\s*(?://[^\n]*\n\s*)*int\s+main\(\))'
    run_match = re.search(run_pattern, cpp_content, re.DOTALL)
    run_text = run_match.group(1) if run_match else ""
    if run_text:
        run_lines = run_text.split('\n')
        filtered_lines = [line for line in run_lines if not re.search(r'z\d+getInv', line)]
        run_text = '\n'.join(filtered_lines)
    return tc_text, change_text, run_text

def process(root_path):
    if not os.path.exists(root_path):
        print(f"错误: 路径不存在 {root_path}")
        return
    final_files = glob.glob(os.path.join(root_path, "final*.txt"))
    if not final_files:
        print(f"错误: 在 {root_path} 下未找到 final*.txt 文件")
        return
    final_txt_path = final_files[0]
    print(f"使用输入文件: {final_txt_path}")
    gene_base_dirs = [
        d for d in os.listdir(root_path)
        if d.startswith('gene') and os.path.isdir(os.path.join(root_path, d))
    ]
    if not gene_base_dirs:
        print(f"错误: 在 {root_path} 下未找到 gene_ 开头的文件夹")
        return
    gene_base = gene_base_dirs[0]
    gene_base_path = os.path.join(root_path, gene_base)
    print(f"使用基因目录: {gene_base_path}")
    mr_tasks = parse_final_txt(final_txt_path)
    if not mr_tasks:
        print("未提取到任何 MR 任务")
        return
    print(f"共提取到 {len(mr_tasks)} 个 MR 条目")
    output_root = os.path.join(root_path, "P_Info")
    os.makedirs(output_root, exist_ok=True)
    for k, n, op_text, inv_text in mr_tasks:
        target_gene_dir_name = f"{gene_base}_{k}"
        target_gene_dir_path = os.path.join(gene_base_path, target_gene_dir_name)
        if not os.path.exists(target_gene_dir_path):
            print(f"警告: 未找到对应的代码文件夹 {target_gene_dir_path}")
            continue
        cpp_files = [
            f for f in os.listdir(target_gene_dir_path)
            if f.startswith("gene") and f.endswith(".cpp")
        ]
        if not cpp_files:
            print(f"警告: 在 {target_gene_dir_path} 下未找到 gene*.cpp 文件")
            continue
        cpp_file_path = os.path.join(target_gene_dir_path, cpp_files[0])
        with open(cpp_file_path, 'r', encoding='utf-8') as cf:
            cpp_content = cf.read()
        tc_text, change_text, run_text = extract_cpp_blocks(cpp_content)
        mr_dir_name = f"MR_{k}_{n}"
        mr_dir_path = os.path.join(output_root, mr_dir_name)
        os.makedirs(mr_dir_path, exist_ok=True)
        with open(os.path.join(mr_dir_path, "MR_test_cases.txt"), 'w', encoding='utf-8') as f:
            f.write(tc_text + "\n")
        with open(os.path.join(mr_dir_path, "MR_IO.txt"), 'w', encoding='utf-8') as f:
            f.write(change_text + "\n")
        with open(os.path.join(mr_dir_path, "run_info.txt"), 'w', encoding='utf-8') as f:
            f.write(run_text + "\n")
        with open(os.path.join(mr_dir_path, "MR_info.txt"), 'w', encoding='utf-8') as f:
            f.write(f"{op_text}\n")
            f.write(f"Invariant: {inv_text}\n")
    print("处理完毕！")
if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("用法: python script.py <目标目录路径>")
        sys.exit(1)
    input_path = sys.argv[1]
    if not os.path.isdir(input_path):
        print(f"错误: 提供的路径无效或不是一个目录: {input_path}")
        sys.exit(1)
    print("开始处理...")
    process(input_path)
