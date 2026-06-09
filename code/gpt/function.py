import os
import subprocess
import random
import string
import re

def extract_function_signature(c_code):
    """
    从C代码中提取函数签名，并能精确区分指针和数组。
    - 对于 'char* a[]', 结果为: type='char**', is_array=True
    - 对于 'char *arr[]', 结果为: type='char**', is_array=True
    - 对于 'char* a',   结果为: type='char*', is_array=False
    - 对于 'const char* const* strs', 结果为: type='const char* const*', is_array=True
    """
    pattern = r'''
        # 返回类型（匹配尽可能多的类型修饰符和指针）
        ((?:(?:const|unsigned|struct|long|short)\s+)*\w+\s*[\*]*)
        \s+
        (\w+)               # 函数名
        \s*
        \(([^)]*)\)         # 参数列表
    '''
    match = re.search(pattern, c_code, re.VERBOSE | re.DOTALL)
    if not match:
        raise ValueError("未找到符合要求的函数")
    return_type = match.group(1).strip()
    function_name = match.group(2).strip()
    parameters_str = match.group(3).strip()
    param_list = []
    has_char_array = False
    if not parameters_str or parameters_str.lower() == 'void':
        return return_type, function_name, [], 'int_arr'
    for param in parameters_str.split(','):
        param = param.strip()
        if not param:
            continue
        last_space_index = param.rfind(' ')
        if last_space_index == -1:
            star_index = param.rfind('*')
            if star_index != -1:
                type_part = param[:star_index+1].strip()
                name_part = param[star_index+1:].strip()
            else:           
                type_part = param
                name_part = ""
        else:
            type_part = param[:last_space_index].strip()
            name_part = param[last_space_index:].strip()
        while name_part.startswith('*') or name_part.endswith('[]'):
            if name_part.startswith('*'):
                type_part += ' *'
                name_part = name_part[1:].strip()
            if name_part.endswith('[]'):
                type_part += '*'
                name_part = name_part[:-2].strip()
        type_part = type_part.replace(' *', '*')
        is_array = '*' in type_part
        param_list.append({
            "type": type_part,
            "name": name_part,
            "is_array": is_array
        })
        if is_array and 'char' in type_part and type_part.count('*') >= 2:
            has_char_array = True
    gene_type = 'char_arr' if has_char_array else 'int_arr'
    return return_type, function_name, param_list, gene_type

def extract_function_inv_para(c_code):
    """
    从C代码中提取函数参数，并返回每个参数名加_1的副本列表和每个参数名加_2的副本列表，
    格式如 "int a_1[], int a2_1[], int n_1, int a_2[], int a2_2[], int n_2"
    """
    pattern = r'''
        # 返回类型（匹配尽可能多的类型修饰符和指针）
        ((?:(?:const|unsigned|struct|long|short)\s+)*\w+\s*[\*]*)
        \s+
        (\w+)               # 函数名
        \s*
        \(([^)]*)\)         # 参数列表
    '''
    match = re.search(pattern, c_code, re.VERBOSE | re.DOTALL)
    if not match:
        raise ValueError("未找到符合要求的函数")
    parameters_str = match.group(3).strip()
    if not parameters_str or parameters_str.lower() == 'void':
        return ""
    raw_params = [p.strip() for p in parameters_str.split(',') if p.strip()]
    params_1 = []
    params_2 = []
    name_pattern = re.compile(r'(\w+)((?:\s*\[[^\]]*\])*)$')
    for param in raw_params:
        m = name_pattern.search(param)
        if m:
            name = m.group(1)
            array_part = m.group(2) if m.group(2) else ""
            escaped_array = re.escape(array_part)
            pattern_replace = r'(\w+)(' + escaped_array + r')$'
            param_1 = re.sub(pattern_replace, r'\1_1\2', param)
            param_2 = re.sub(pattern_replace, r'\1_2\2', param)
            params_1.append(param_1)
            params_2.append(param_2)
        else:
            params_1.append(param + "_1")
            params_2.append(param + "_2")
    inv_para_info = ', '.join(params_1 + params_2)
    return inv_para_info

def extract_function_signature_old(c_code):
    """
    从C代码中提取函数签名，并能精确区分指针和数组。
    - 对于 'char* a[]', 结果为: is_array=True, type='char*'
    - 对于 'char* a',   结果为: is_array=False, type='char*'
    """
    pattern = r'''
        # 返回类型（可能包含 const, unsigned, 指针等）
        ((?:const\s+|unsigned\s+)?\w+\s*[\*]*)  
        \s+
        (\w+)               # 函数名
        \s*
        \(([^)]*)\)         # 参数列表
    '''
    match = re.search(pattern, c_code, re.VERBOSE)
    if not match:
        raise ValueError("未找到符合要求的函数")
    return_type = match.group(1).strip()
    function_name = match.group(2).strip()
    parameters = match.group(3).strip()
    param_list = []
    has_char_array = False
    if not parameters or parameters.lower() == 'void':
        return return_type, function_name, [], 'int_arr'                    
    for param in parameters.split(','):
        param = param.strip()
        if not param:
            continue
        is_array = param.endswith('[]')
        if is_array:
            parse_str = param[:-2].strip()
        else:
            parse_str = param
        last_space_index = parse_str.rfind(' ')
        if last_space_index == -1:
            if '*' in parse_str:
                star_index = parse_str.rfind('*')
                type_part = parse_str[:star_index+1].strip()
                name_part = parse_str[star_index+1:].strip()
            else:
                type_part = parse_str
                name_part = ''       
        else:
            type_part = parse_str[:last_space_index].strip()
            name_part = parse_str[last_space_index:].strip()
        while name_part.startswith('*'):
            type_part += ' *'
            name_part = name_part[1:]
        param_list.append({
            "type": type_part,
            "name": name_part,
            "is_array": is_array
        })
        if is_array and 'char' in type_part:
            has_char_array = True
    gene_type = 'char_arr' if has_char_array else 'int_arr'
    return return_type, function_name, param_list, gene_type

def generate_random_string(length):
    """
      生成指定长度的随机字符串。
      :param length: 随机字符串的长度。
      :return: 随机字符串。
      """
    return ''.join(random.choices(string.ascii_letters + string.digits, k=length))

def generate_random_int_list(length):
    """
       生成指定长度的随机整数列表。
       :param length: 列表长度。
       :return: 随机整数列表。
       """
    return [random.randint(1, 100) for _ in range(length)]

def generate_main_function(num,return_type):
    test_calls_lines = []
    if "char" in return_type:
        for a in range(1, num + 1):
            test_calls_lines.append(f"        TestResult result{a} = z{a}runTest(i);")
            test_calls_lines.append(f"        free(result{a}.result1);")
            test_calls_lines.append(f"        free(result{a}.result2);")
    else:
        test_calls_lines = [f"        TestResult result{a} = z{a}runTest(i);" for a in range(1, num + 1)]
    calls_block = "\n".join(test_calls_lines)
    main_function_code = f"""
int main() {{
    for (int i = 0; i < num_test_cases; i++) {{
{calls_block}
    }}
    return 0;
}}
"""
    return main_function_code

def determine_test_type(parameters):
    """
       根据函数参数类型确定测试类型：
       - string_only: 参数中包含字符型但不包含整数型
       - string_and_int: 参数中同时包含字符型和整数型
       - int_only: 参数仅包含整数型
       """
    if 'char *' in parameters and 'int' not in parameters:
        return 'char_arr'
    elif 'char *' in parameters and 'int' in parameters:
        return 'char_arr'                      
    else:
        return 'int_arr'
