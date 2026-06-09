import os
import subprocess
import shutil
from pathlib import Path
import re
daikon_dir = '/home/robot/app/daikonnew/daikon-5.8.20'

def modify_dtrace_return_values(dtrace_file_path, file_path):
    """
    根据 cpp 文件的测试用例和修改目标，修正 dtrace 文件中被截断的数组数据。
    """
    try:
        with open(file_path, 'r', encoding='utf-8') as f:
            cpp_code = f.read()
    except FileNotFoundError:
        print(f"错误: 找不到 C++ 文件 {file_path}")
        return
    last_include_idx = cpp_code.rfind('#include')
    code_after_includes = cpp_code[last_include_idx:] if last_include_idx != -1 else cpp_code
    func_match = re.search(r'\n[\w\s\*:<>&]+\s+\w+\s*\((.*?)\)\s*\{', code_after_includes)
    if not func_match:
        print("未找到目标函数签名")
        return
    params_str = func_match.group(1)                              
    array_params = []
    for param in params_str.split(','):
        param = param.strip()
        if '[]' in param or '*' in param:
            var_name = param.replace('[]', '').replace('*', '').split()[-1]
            array_params.append(var_name)
    print(f"[*] 识别到数组参数: {array_params}")
    para_match = re.search(r'//para:\s*(.*?)\s*opt:', cpp_code)
    target_para = para_match.group(1).strip() if para_match else None
    print(f"[*] 识别到操作目标 (para): {target_para}")
    test_cases = []
    tc_block_match = re.search(r'TestCase\s+test_cases\[\]\s*=\s*\{([\s\S]*?)\};', cpp_code)
    if tc_block_match:
        tc_block = tc_block_match.group(1)
        for line in tc_block.split('\n'):
            line = line.strip()
            if not line.startswith('{'):
                continue
            arrays_in_line = re.findall(r'\{([\d\s,\-\.]+)\}', line)
            if arrays_in_line:
                tc_dict = {}
                for i, arr_name in enumerate(array_params):
                    if i < len(arrays_in_line):
                        clean_nums = ' '.join(arrays_in_line[i].replace(',', ' ').split())
                        tc_dict[arr_name] = clean_nums
                if tc_dict:
                    test_cases.append(tc_dict)
    print(f"[*] 成功提取 {len(test_cases)} 组测试用例数据。")
    try:
        with open(dtrace_file_path, 'r', encoding='utf-8') as f:
            dtrace_lines = f.readlines()
    except FileNotFoundError:
        print(f"错误: 找不到 DTrace 文件 {dtrace_file_path}")
        return
    new_dtrace_lines = []
    current_tc_idx = -1
    in_target_block = False
    replace_next_line_with = None
    for line in dtrace_lines:
        if 'getInv' in line and 'EXIT0' in line:
            in_target_block = True
            current_tc_idx += 1
        if line.startswith('..') and not ('getInv' in line and 'EXIT0' in line):
            in_target_block = False
        if replace_next_line_with is not None:
            new_dtrace_lines.append(f"[ {replace_next_line_with} ]\n")
            replace_next_line_with = None        
            continue
        new_dtrace_lines.append(line)
        if in_target_block and 0 <= current_tc_idx < len(test_cases):
            line_stripped = line.strip()
            for arr_name in array_params:
                if line_stripped == f"{arr_name}_1[..]":
                    replace_next_line_with = test_cases[current_tc_idx][arr_name]
                    break
                elif line_stripped == f"{arr_name}_2[..]":
                    if arr_name == target_para:
                        replace_next_line_with = None
                    else:
                        replace_next_line_with = test_cases[current_tc_idx][arr_name]
                    break
    with open(dtrace_file_path, 'w', encoding='utf-8') as f:
        f.writelines(new_dtrace_lines)
    print(f"[*] DTrace 文件修正完成: {dtrace_file_path}")

def fix_decls_comparability_final(decls_file_path: str) -> None:
    """
    修改 Daikon .decls 文件，将所有名称包含 "Test" 的 EXIT0 程序点中，
    变量名包含 "test_cases" 或以 "return." 开头的 comparability 值设置为 20。
    Args:
        decls_file_path: 要修改的 .decls 文件路径。
    Returns:
        None。文件原地修改。
    """
    import re
    try:
        with open(decls_file_path, 'r') as f:
            original_content = f.read()
    except FileNotFoundError:
        print(f"错误：文件未找到 '{decls_file_path}'")
        return
    except Exception as e:
        print(f"读取文件 '{decls_file_path}' 时出错：{e}")
        return
    lines = original_content.splitlines()
    modified_lines = []
    current_ppt_name = None
    current_var_block = None
    for line in lines:
        ppt_match = re.match(r'^\s*ppt\s+\.\.(.+)', line)
        if ppt_match:
            current_ppt_name = ppt_match.group(1).strip()
        var_match = re.match(r'^\s*variable\s+(.+)', line)
        if var_match:
            current_var_block = var_match.group(1).strip()
        if current_var_block and line.strip().startswith('comparability'):
            indentation = re.match(r'^\s*', line).group(0)
            if (current_ppt_name and "getInv" in current_ppt_name and current_ppt_name.endswith(":::EXIT0") and
                    ("_1" in current_var_block or "_2" in current_var_block or current_var_block.startswith("return.") or "t1.result" in current_var_block)):
                modified_lines.append(f'{indentation}comparability 100')
                continue
        modified_lines.append(line)
    modified_content = "\n".join(modified_lines)
    try:
        with open(decls_file_path, 'w') as f:
            f.write(modified_content)
        print(f"成功修改并保存 '{decls_file_path}'")
    except Exception as e:
        print(f"写入文件 '{decls_file_path}' 时出错：{e}")

def process_c_files(input_folder, output_folder):
    print(f"input_folder:{input_folder}")
    """完全遵循官方文档的处理流程"""
    daikon_path = Path(daikon_dir).absolute()
    input_folder = Path(input_folder).absolute()
    output_folder = Path(output_folder).absolute()
    os.environ['DAIKONDIR'] = str(daikon_path)
    os.environ['PATH'] = f"{daikon_path / 'fjalar/valgrind/inst/bin'}:{os.environ['PATH']}"
    for filename in os.listdir(input_folder):
        if not (filename.endswith('.cpp') or filename.endswith('.cc') or filename.endswith('.cxx')):
            continue
        stem = Path(filename).stem
        output_dir = output_folder / stem
        output_dir.mkdir(exist_ok=True)
        try:
            shutil.copy(input_folder / filename, output_dir)
            os.chdir(output_dir)
            compile_cmd = [
                'g++',                   
                '-g', '-gdwarf-2',         
                '-no-pie',
                '-O0',         
                '-fno-stack-protector',
                '-fno-inline',         
                '-fno-omit-frame-pointer',            
                filename,
                '-o', stem,
            ]
            print(f"\n编译 {filename}: {' '.join(compile_cmd)}")
            subprocess.run(compile_cmd, check=True)
            dtrace_cmd = [
                'kvasir-dtrace',
                f'--dtrace-file={stem}.dtrace',
                f'--decls-file={stem}.decls',
                f'./{stem}'
            ]
            print(f"生成Dtrace: {' '.join(dtrace_cmd)}")
            dtrace_result = subprocess.run(
                dtrace_cmd,
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
                text=True,
                timeout=30
            )
            required_files = [f'{stem}.dtrace', f'{stem}.decls']
            missing = [f for f in required_files if not Path(f).exists()]
            if missing:
                error_msg = f"缺少输出文件: {missing}\n"
                if dtrace_result.stderr:
                    error_msg += f"错误输出:\n{dtrace_result.stderr}\n"
                raise RuntimeError(error_msg)
            modify_dtrace_return_values(f'{stem}.dtrace',filename)
            fix_decls_comparability_final(f'{stem}.decls')
            daikon_cmd = [
                'java',
                '-cp', str(daikon_path / 'daikon.jar'),
                'daikon.Daikon',
                '--config_option', 'daikon.derive.Derivation.disable_derived_variables=false',
                f'{stem}.decls',
                f'{stem}.dtrace'
            ]
            print(f"运行Daikon: {' '.join(daikon_cmd)}")
            daikon_result = subprocess.run(
                daikon_cmd,
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
                text=True,
                timeout=60
            )
            with open(f'{stem}_invariants.txt', 'w') as f:
                f.write(daikon_result.stdout)
            lines = daikon_result.stdout.splitlines()
            simplified_lines = [
                line for line in lines
                if not line.startswith('::') and line.strip() != 'return has only one value'
            ]
            simplified_output = '\n'.join(simplified_lines)
            with open(f'{stem}_invariants_simply.txt', 'w') as f:
                f.write(simplified_output)
            print(f"✅ 成功处理 {filename}")
        except Exception as e:
            print(f"❌ 处理 {filename} 失败: {str(e)}")
            with open(f'{stem}_error.log', 'w') as f:
                f.write(f"错误详情:\n{str(e)}\n\n")
                if 'dtrace_result' in locals():
                    f.write(f"Dtrace输出:\n{dtrace_result.stderr}\n")
                if 'daikon_result' in locals():
                    f.write(f"Daikon输出:\n{daikon_result.stderr}\n")
        finally:
            os.chdir(Path(__file__).parent)
if __name__ == '__main__':
    config = {
        'input_folder': '/home/robot/cp/InvariantMR/1_daikon_mt/test_daikon/test_sum',
        'output_folder': '/home/robot/cp/InvariantMR/1_daikon_mt/test_daikon/test_sum',
    }
    print("=" * 50)
    print("Daikon蜕变关系验证系统")
    print(f"输入目录: {config['input_folder']}")
    print(f"输出目录: {config['output_folder']}")
    print("=" * 50)
    try:
        process_c_files(**config)
        print("\n处理完成，结果已保存到输出目录")
    except Exception as e:
        print(f"\n❌ 系统错误: {str(e)}")
