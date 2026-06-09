import os
import sys
import pandas as pd
import re
import random
target_directory = os.path.abspath('/home/robot/cp/PycharmProjects/InvariantMR')
sys.path.insert(0, target_directory)
from function import extract_function_signature, determine_test_type, generate_main_function, extract_function_inv_para
from llm_TestM3_rebuild import determine_test_type, int_array_model,char_array_model,find_arrays_and_lengths,array_model

def generate_test_cases_from_signature(param_list, array_info, num_cases=7):
    """
    一个统一的、强大的测试用例生成器，能够处理包含任意类型数组（包括混合类型）的函数签名。
    """
    test_case_fields = []
    for param in param_list:
        if param["is_array"]:
            type_no_pointers = param['type'].replace('*', '')
            type_clean = re.sub(r'\b(const|volatile)\b', '', type_no_pointers).strip()
            base_type = ' '.join(type_clean.split()).split(' ')[0]
            pointer_level = param['type'].count('*')
            if '[]' in param['type']:
                pointer_level += 1
            final_type = base_type + '*' * pointer_level
            test_case_fields.append(f"{final_type} {param['name']}")
        else:            
            test_case_fields.append(f"{param['type']} {param['name']}")
    length_params = {info["length_param_name"] for info in array_info if info["length_param_name"]}
    char_array_templates = [
        {'size': 10, 'generator': lambda n: [generate_random_string() for _ in range(n)]},
        {'size': 8, 'generator': lambda n: [generate_random_string(5, 15) for _ in range(n)]},
        {'size': 6, 'generator': lambda n: [generate_random_string(3, 12) for _ in range(n)]},
        {'size': 3, 'generator': lambda n: ["start", "middle", "end"]},
        {'size': 0, 'generator': lambda n: None}
    ]
    test_cases_init = []
    for i in range(num_cases):
        case_values = {}
        template_for_size = char_array_templates[i % len(char_array_templates)]
        current_size = template_for_size['size']
        for lp in length_params:
            case_values[lp] = str(current_size)
        for param in param_list:
            param_name = param['name']
            if param_name in length_params:
                continue
            if param["is_array"]:
                base_type_lower = param['type'].lower()
                pointer_level = param['type'].count('*')
                if '[]' in param['type']: pointer_level += 1
                is_string_array = 'char' in base_type_lower and pointer_level >= 2
                if current_size == 0:
                    if is_string_array:
                        case_values[param_name] = "NULL"
                    else:
                        for lp in length_params:
                            case_values[lp] = "1"
                        if 'double' in base_type_lower or 'float' in base_type_lower:
                            val = round(random.uniform(0, 100), 2)
                            clean_type = param['type'].replace('*','').replace('[]','').strip()
                            case_values[param_name] = f"({clean_type}[]){{{val:.2f}}}"
                        else:             
                            val = random.randint(0, 100)
                            case_values[param_name] = f"(int[]){{{val}}}"
                    continue            
                if is_string_array:
                    str_array = template_for_size['generator'](current_size)
                    quoted_strings = [f'"{s}"' for s in str_array]
                    case_values[param_name] = f"(char*[]){{{', '.join(quoted_strings)}}}"
                else:
                    if 'double' in base_type_lower or 'float' in base_type_lower:
                        arr = [round(random.uniform(0, 100), 2) for _ in range(current_size)]
                        values_str = ', '.join(f"{x:.2f}" for x in arr)
                        clean_type = param['type'].replace('*','').replace('[]','').strip()
                        case_values[param_name] = f"({clean_type}[]){{{values_str}}}"
                    elif 'int' in base_type_lower:
                        arr = [random.randint(0, 100) for _ in range(current_size)]
                        case_values[param_name] = f"(int[]){{{', '.join(map(str, arr))}}}"
            else:            
                if 'char' in param['type'].lower() and '*' in param['type']:
                    random_str = None             
                    if random_str is None:
                        case_values[param_name] = "NULL"
                    else:
                        case_values[param_name] = f'"{random_str}"'
                elif 'int' in param['type'].lower():
                    if length_params:
                        final_size_str = case_values.get(list(length_params)[0], "0")
                        final_size = int(final_size_str)
                        case_values[param_name] = str(random.randint(0, max(0, final_size - 1)))
                    else:
                        case_values[param_name] = str(random.randint(1, 20))
                elif 'double' in param['type'].lower() or 'float' in param['type'].lower():
                    case_values[param_name] = f"{random.uniform(1, 9):.2f}"
                else:
                    case_values[param_name] = "0"
        ordered_values = [case_values.get(p['name'], "/* ERROR */") for p in param_list]
        test_cases_init.append("{" + ", ".join(ordered_values) + "}")
    return test_case_fields, test_cases_init

def remove_markdown_blocks_from_code(complete_code):
    """
    从生成的C代码字符串中移除所有```c标记
    参数:
        complete_code (str): 包含C代码的完整字符串
    返回:
        str: 清理后的C代码字符串
    """
    lines = complete_code.split('\n')
    cleaned_lines = [line for line in lines if "```c" not in line and "```" not in line]              
    cleaned_code = '\n'.join(cleaned_lines)
    return cleaned_code

def generate_single_main_function(operation_index):
    """
    为单个测试操作生成 main 函数。
    :param operation_index: 当前操作的序号 (例如 1, 2, 3...)
    :return: 包含 main 函数的C++代码字符串
    """
    main_code = f"""
int main() {{
    srand(time(NULL));
    for (int i = 0; i < num_test_cases; i++) {{
        TestResult result = z{operation_index}runTest(i);
        for (int j = 0; j < result.memory_count; j++) {{
            free(result.memory_to_free[j]);
        }}
        free(result.memory_to_free);  // 释放指针数组本身
    }}
    return 0;
}}
"""
    return main_code

def generate_combine_code(input_file_path, output_filepath, code_list, test_case_fields, test_cases_init, array_info):
    """
    为每个变化操作生成独立的C++测试文件。
    :param input_file_path: 输入C文件路径
    :param output_filepath: 输出文件的基础路径和名称（例如 'output/gene_add_values'）。
                            最终文件名会是 <output_filepath>_<序号>.cpp
    :param code_list: 从LLM获取的操作列表
    :param ...: 其他参数保持不变
    """
    with open(input_file_path, 'r') as file:
        input_code = file.read()
    pattern = re.compile(
        r'static\s+(?P<type>\w+)\s+(?P<name>\w+)\s*\[\s*(?P<size>\d+)\s*\]\s*;',
        re.MULTILINE
    )
    def replacer(match):
        default_length_name = None
        if array_info:
            first_valid_entry = next((info for info in array_info if info.get("length_param_name")), None)
            if first_valid_entry:
                default_length_name = first_valid_entry["length_param_name"]
        type_ = match.group('type')
        name = match.group('name')
        size = match.group('size')
        final_size = default_length_name if size.isdigit() and default_length_name else size
        return f"{type_}* {name} = ({type_}*)malloc({final_size} * sizeof({type_}));"
    input_code = pattern.sub(replacer, input_code)
    try:
        return_type, function_name, parameters, gene_type = extract_function_signature(input_code)
        inv_para_info = extract_function_inv_para(input_code)
    except ValueError as e:
        print(f"Error processing {input_file_path}: {e}")
        return
    original_test_cases_code = ''
    if test_case_fields and test_cases_init:
        original_test_cases_code = """
typedef struct {{
    {0};
}} TestCase;
TestCase test_cases[] = {{
    {1}
}};
int num_test_cases = {2};""".format(
            '; '.join(test_case_fields),
            ',\n    '.join(test_cases_init),
            len(test_cases_init)
        )
    test_cases_code_final = original_test_cases_code
    for func_info in code_list:
        param_name = func_info["parameter_name"]
        param_type = func_info["parameter_type"]
        free_statement = ""
        if '*' in param_type:
            if 'char' in param_type.lower() and param_type.count('*') >= 2:
                length_param_name = "/* UNKNOWN_LENGTH */"
                for info in array_info:
                    if info['name'] == param_name:
                        length_param_name = info['length_param_name']
                        break
                if length_param_name != "/* UNKNOWN_LENGTH */":
                    free_statement = f"free_str_array(follow_case.{param_name}, follow_case.{length_param_name});"
                else:
                    free_statement = f"// WARNING: Could not determine length for {param_name} to call free_str_array."
            else:
                free_statement = f"memory_list[0] = follow_case.{param_name};|{param_type}"
        func_info['free_statement'] = free_statement
    headers = "\n".join([
        "#include <cstdio>", "#include <cstdlib>", "#include <ctime>",
        "#include <cstring>", "#include <cmath>", "#include <climits>",
        "#include <cfloat>", "#include <cctype>", "#include <iostream>",
        "#include <string>", "#include <vector>", "#include <algorithm>",
        "using namespace std;", ""
    ])
    deep_copy = ""
    free_arr = ""
    needs_str_array_helpers = any('char' in p['type'].lower() and p['type'].count('*') >= 2 for p in parameters)
    if needs_str_array_helpers:
        deep_copy = """char** deep_copy_str_array(const char* const* src, int n) {
    if (n <= 0 || src == NULL) {
        return NULL;
    }
    char** dest = (char**)malloc(n * sizeof(char*));
    if (dest == NULL) return NULL;
    for (int i = 0; i < n; i++) {
        // --- 新增保护 ---
        if (src[i] == NULL) {
            dest[i] = NULL; // 如果原始字符串是 NULL，复制后也应该是 NULL
        } else {
            // 只有在 src[i] 不是 NULL 时才调用 strlen
            dest[i] = (char*)malloc((strlen(src[i]) + 1) * sizeof(char));
            if (dest[i] == NULL) {
                // ... (内存释放和错误处理)
                return NULL;
            }
            strcpy(dest[i], src[i]);
        }
    }
    return dest;
}"""
        free_arr = """void free_str_array(char** arr, int n) {
    if (n <= 0 || arr == NULL) {
        return;
    }
    for (int i = 0; i < n; i++) {
        free(arr[i]);
    }
    free(arr);
}"""
    output_dir = os.path.dirname(output_filepath)
    if output_dir:
        os.makedirs(output_dir, exist_ok=True)
    base_name = os.path.basename(output_filepath)
    filename_prefix = os.path.splitext(base_name)[0]        
    for i, func_info in enumerate(code_list, 1):
        try:
            test_function_code,test_result_struct_definition = array_model(func_info, i, return_type,inv_para_info)
            main_code = generate_single_main_function(i)
            complete_code_parts = [
                headers,
                input_code,                        
                test_cases_code_final,                   
                test_result_struct_definition,            
                deep_copy,                            
                free_arr,                             
                "/** Test Functions **/",
                test_function_code,                                 
                main_code                              
            ]
            print(f"headers:{headers}")
            print(f"input_code:{input_code}")
            print(f"test_cases_code_final:{test_cases_code_final}")
            print(f"test_result_struct_definition:{test_result_struct_definition}")
            print(f"test_function_code:{test_function_code}")
            complete_code = '\n\n'.join(filter(None, complete_code_parts))                           
            cleaned_code = remove_markdown_blocks_from_code(complete_code)
            final_filename = f"{filename_prefix}_{i}.cpp"
            final_filepath = os.path.join(output_dir, final_filename)
            with open(final_filepath, 'w') as file:
                file.write(cleaned_code)
            print(f"测试文件已生成到: {final_filepath}")
        except Exception as e:
            print(f"为操作 #{i} ({func_info.get('operation', 'N/A')}) 生成测试文件失败: {e}")
