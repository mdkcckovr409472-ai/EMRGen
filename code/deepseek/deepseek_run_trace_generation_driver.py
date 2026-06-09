import os
import re
from daikon_simplifier_double import simplify_daikon_report
import sys
import datetime
import pprint
from function import extract_function_signature
from llm_TestM3_rebuild import find_arrays_and_lengths
from openai import OpenAI
from Test_deepseek import get_main_code,get_operation_llm_unnumber,get_input_data
from llm_rebuild_generate_int_code_datarandom import generate_combine_code
from run_daikon_cp import process_c_files
client = OpenAI(api_key="sk-0af7f8397143442d9382c1a9b303be06", base_url="https://api.deepseek.com")

def get_function_signatures(input_filepath):
    with open(input_filepath, 'r') as file:
        input_code = file.read()
    try:
        return_type, function_name, parameters, gene_type = extract_function_signature(input_code)
    except ValueError as e:
        print(f"Error processing {input_filepath}: {e}")
        return
    return return_type, function_name, parameters,gene_type

def get_test_cases(parameters,input_filepath):
    array_info = find_arrays_and_lengths(parameters)
    with open(input_filepath, 'r') as file:
        input_code = file.read()
    test_case_fields, test_cases_init = get_input_data(input_code,30)
    return test_case_fields, test_cases_init, array_info

def get_code_list(operations,parameters,testcase_fields,func_name,return_type):
    testcase_struct = """
typedef struct {{
    {0};
}} TestCase;
""".format(
        '; '.join(testcase_fields)
    )
    final_code_list = []
    id = 0
    for param_info in operations:
        param_name = param_info["parameter_name"]
        param_type = param_info["parameter_type"]
        for operation_str in param_info["operations"]:
            id = id + 1
            code_res = get_main_code(testcase_struct, param_name, param_type, operation_str, parameters, id, func_name,return_type)
            operation_details = {
                "parameter_name": param_name,
                "parameter_type": param_type,
                "operation": operation_str,
                "code": code_res["func"],
                "call_s1":code_res["call_string1"],
                "call_s2":code_res["call_string2"]
            }
            final_code_list.append(operation_details)
    return final_code_list

def sort_inv(daikon_output_file_dir, input_file_path, final_report_path, operations):
    """
    扫描Daikon结果目录（包含多个子目录），汇总所有独立分析文件中的不变量，
    并生成一份统一的元启发式关系报告。
    此版本适配了每个操作结果保存在独立子目录中的文件结构。
    参数:
        daikon_output_file_dir (str): 存放所有Daikon分析结果子目录的顶层目录。
                                      例如: '.../gene_add_values'
        input_file_path (str): 原始被测C/C++文件的路径，用于在报告中包含源代码。
        final_report_path (str): 最终生成的汇总报告文件的保存路径。
        operations (list): 包含所有操作上下文信息的原始数据结构。
    """
    print(f"--- 正在扫描顶层目录: {daikon_output_file_dir} ---")
    all_daikon_outputs = []
    try:
        subdirectories = sorted([d for d in os.listdir(daikon_output_file_dir)
                                 if os.path.isdir(os.path.join(daikon_output_file_dir, d))])
        if not subdirectories:
            print(f"警告: 在 '{daikon_output_file_dir}' 中未找到任何子目录。")
            return
        for subdir_name in subdirectories:
            expected_filename = f"{subdir_name}_invariants_simply.txt"
            full_file_path = os.path.join(daikon_output_file_dir, subdir_name, expected_filename)
            print(f"正在尝试读取: {full_file_path}")
            if os.path.isfile(full_file_path):
                try:
                    with open(full_file_path, 'r', encoding='utf-8') as f:
                        content = f.read()
                        if content.strip():           
                            all_daikon_outputs.append(content)
                            print(f"  > 成功读取并添加内容。")
                        else:
                            print(f"  > 警告: 文件为空，已跳过。")
                except Exception as e:
                    print(f"  > 警告: 读取文件 {expected_filename} 时发生错误: {e}")
            else:
                print(f"  > 警告: 未找到预期的结果文件。")
    except FileNotFoundError:
        print(f"错误: Daikon结果目录未找到: {daikon_output_file_dir}")
        return
    except Exception as e:
        print(f"扫描目录时发生未知错误: {e}")
        return
    if not all_daikon_outputs:
        print("错误: 未能从任何文件中读取到有效的Daikon输出。无法生成报告。")
        return
    combined_daikon_output = "\n===========================================================================\n".join(all_daikon_outputs)
    sections = combined_daikon_output.split("===========================================================================")
    invariants_dict = {}
    print("\n--- 开始解析汇总后的Daikon输出 ---")
    for section in sections:
        clean_section = section.strip()
        if not clean_section:
            continue
        match = re.match(r"\.\.z(\d+)getInv\(.*\):::EXIT", clean_section)
        if match:
            run_id = match.group(1)
            print(f"找到 z{run_id}getInv 的 EXIT 块...")
            raw_content = clean_section[match.end():]
            lines = raw_content.splitlines()
            filtered_lines = [
                line for line in lines
                if "::" not in line
                   and line.strip()
                   and "Exiting Daikon." not in line
                   and "return.memory_to_free" not in line         
                   and "return.memory_count" not in line           
            ]
            content = "\n".join(filtered_lines).strip()
            if content:
                invariants_dict[run_id] = content
                print(f"  > 提取到不变量: {content}")
            else:
                invariants_dict[run_id] = "no_inv"
                print(f"  > 未找到与返回值相关的不变量。")
    print("\n--- 提取并整理后的不变量字典 ---")
    pprint.pprint(invariants_dict)
    try:
        with open(input_file_path, 'r', encoding='utf-8') as file:
            source_code_content = file.read()
    except FileNotFoundError:
        print(f"错误: 输入代码文件未找到: {input_file_path}")
        return
    except Exception as e:
        print(f"读取输入代码文件时出错: {e}")
        return
    all_operations_with_context = [
        (param_details["parameter_name"], param_details["parameter_type"], op_string)
        for param_details in operations
        for op_string in param_details["operations"]
    ]
    print("\n--- 压平后包含上下文的操作列表 ---")
    pprint.pprint(all_operations_with_context)
    operation_count = 0
    try:
        operation_count = 0
        total_relations_count = 0                        
        with open(final_report_path, 'w', encoding='utf-8') as f:
            f.write(source_code_content)
            f.write("\n\n========================================================\n")
            f.write(" *  Contextual Operations and Discovered Invariants\n")
            f.write("========================================================\n\n")
            for i, op_data in enumerate(all_operations_with_context):
                op_id = str(i + 1)
                param_name, param_type, op_str = op_data
                block_keywords = ["弦", "倒数", "NaN", "float再转回int", "逻辑", "置100", "置-100","回int"]
                if any(keyword in op_str for keyword in block_keywords):
                    continue
                inv_str = invariants_dict.get(op_id, "invariant_not_found")
                if (inv_str in ["no_inv", "invariant_not_found"]) or ("one of {" in inv_str):
                    continue
                lines = inv_str.strip().split('\n')
                lines = [line for line in lines if "orig(test_case_id)" not in line]
                filtered_lines_c = []
                for line in lines:
                    stripped_line = line.strip()
                    if ("return.result1 != return.result2" in stripped_line or
                            "return.result1 != 0" in stripped_line or
                            "return.result2 != 0" in stripped_line):
                        continue                 
                    filtered_lines_c.append(line)
                lines = filtered_lines_c
                has_a1_eq = any(
                    re.search(r't1\.result1(?:\[[^\]]*\])?\s*==\s*a_1(?:\[[^\]]*\])?', line) or
                    re.search(r'a_1(?:\[[^\]]*\])?\s*==\s*t1\.result1(?:\[[^\]]*\])?', line)
                    for line in lines
                )
                has_a2_eq = any(
                    re.search(r't1\.result2(?:\[[^\]]*\])?\s*==\s*a_2(?:\[[^\]]*\])?', line) or
                    re.search(r'a_2(?:\[[^\]]*\])?\s*==\s*t1\.result2(?:\[[^\]]*\])?', line)
                    for line in lines
                )
                if has_a1_eq:
                    lines = [re.sub(r'\ba_1\b', 't1.result1', line) for line in lines]
                if has_a2_eq:
                    lines = [re.sub(r'\ba_2\b', 't1.result2', line) for line in lines]
                filtered_lines_strict = []
                for line in lines:
                    if "t1.result1" in line and "t1.result2" in line and "!=" not in line:
                        new_line = line.replace("t1.result1", "return.result1").replace("t1.result2", "return.result2")
                        def replace_orig(match):
                            return match.group(1)              
                        new_line = re.sub(r'orig\(([^)]+)\)', replace_orig, new_line)
                        new_line = re.sub(r'_1\b', '', new_line)
                        new_line = re.sub(r'_2\b', '', new_line)
                        new_line = re.sub(r'\[[^\]]*\](?=\[)', '', new_line)
                        filtered_lines_strict.append(new_line)
                filtered_lines_strict = list(dict.fromkeys(filtered_lines_strict))
                lines = filtered_lines_strict
                inv_str = '\n'.join(lines).strip()
                if not inv_str:
                    continue
                relation_count_for_this_op = sum(1 for line in lines if line.strip())
                total_relations_count += relation_count_for_this_op
                operation_count += 1
                f.write(
                    f"Operation {op_id}: On parameter '{param_name}' ({param_type}): {op_str}\n"
                    f"Invariant: \n{inv_str}\n\n"
                )
                transformed_inv = inv_str.replace("return.result1", "Os").replace("return.result2", "Of")
                f.write(
                    f"MR ：对于初始输入Ts中包含{param_name}（{param_type}）的函数，"
                    f"若对 {param_name}执行「{op_str}」操作得到新输入Tf，"
                    f"则函数的初始输出Os和Of应满足以下关系：\n"
                    f"{transformed_inv}\n\n"
                )
                f.write("----------------------------------------\n\n")
            f.write(f"\n操作总数: {operation_count}\n")
            f.write(f"关系总数: {total_relations_count}\n")
        print(f"\n文件 '{final_report_path}' 已成功创建！")
    except Exception as e:
        print(f"写入文件时出错: {e}")
    print("开始简化 Daikon 报告...")
    was_simplified = simplify_daikon_report(final_report_path, verbose=True)
    if was_simplified:
        print("报告已成功简化。")
    else:
        print("报告未被修改。")

def all_flow(input_file_path,output_file_dir):
    return_type, function_name, parameters, gene_type = get_function_signatures(input_file_path)
    test_case_fields, test_cases_init, array_info = get_test_cases(parameters,input_file_path)
    operations = get_operation_llm_unnumber(function_name, return_type, parameters)
    code_list = get_code_list(operations,parameters,test_case_fields,function_name,return_type)
    for item in code_list:
        print(item)
    daikon_output_file_dir = f"{output_file_dir}/gene_{function_name}"
    if not os.path.exists(daikon_output_file_dir):
        os.mkdir(daikon_output_file_dir)
    output_file_path = f"{daikon_output_file_dir}/gene_{function_name}.cpp"
    try:
        generate_combine_code(input_file_path, output_file_path, code_list,test_case_fields, test_cases_init, array_info)
    except ValueError as e:
        print(f"Error unpacking: {e}")
        raise
    process_c_files(daikon_output_file_dir,daikon_output_file_dir)
    final_report_path = os.path.join(output_file_dir, f"final_report_{function_name}.txt")
    sort_inv(daikon_output_file_dir,input_file_path,final_report_path,operations)
if __name__ == '__main__':
    if len(sys.argv) != 2:
        print("用法: python script.py <input_file_path>")
        sys.exit(1)
    input_file = sys.argv[1]
    if not os.path.isfile(input_file):
        print(f"错误: 文件 '{input_file}' 不存在。")
        sys.exit(1)
    directory_path = os.path.dirname(input_file)
    print(f"输入文件目录: {directory_path}")
    output_file = directory_path
    all_flow(input_file, output_file)
