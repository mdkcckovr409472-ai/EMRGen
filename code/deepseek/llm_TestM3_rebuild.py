import pandas as pd
import random
import string

def determine_test_type(param_list):
    has_int_array = any(p['is_array'] and 'int' in p['type'] for p in param_list)
    has_string_array = any(p['is_array'] and 'char' in p['type'] for p in param_list)
    if has_int_array and has_string_array:
        return 'string_arr_and_int_arr'
    elif has_string_array:
        return 'string_array_only'
    elif has_int_array:
        return 'int_array_only'
    else:
        return 'int_only'

def find_arrays_and_lengths(param_list):
    """
    分析参数列表，识别数组参数及其可能关联的长度参数
    参数:
    param_list - 参数列表，每项包含类型(type)、名称(name)和是否数组(is_array)
    返回:
    array_info - 数组信息列表，每个元素包含:
        "name": 数组参数名
        "type": 数组基本类型（去除指针/数组符号）
        "length_param_name": 匹配到的长度参数名（如找到）
    """
    arrays = [p for p in param_list if p["is_array"]]
    potential_length_params = {
        p["name"]: p for p in param_list
        if not p["is_array"] and 'int' in p["type"]
    }
    array_info = []
    for arr in arrays:
        possible_length_names = [
            f"{arr['name']}_len",               
            f"{arr['name']}_length",               
            f"{arr['name']}_size",               
            "size",                          
            "len",                           
            "length",                        
            "n"                              
        ]
        n_digits_names = [
            name for name in potential_length_params
            if name.startswith('n') and name[1:].isdigit()
        ]
        n_digits_names.sort(key=lambda n: int(n[1:]))
        possible_length_names.extend(n_digits_names)
        matched_len_name = None
        for name_pattern in possible_length_names:
            if name_pattern in potential_length_params:
                matched_len_name = name_pattern
                break
        base_type = " ".join(arr["type"].replace('*', '').replace('[]', '').replace('const', '').split())
        array_info.append({
            "name": arr["name"],
            "type": base_type,
            "length_param_name": matched_len_name                 
        })
    return array_info                        

def get_trans_length(orig_length):
    return orig_length          

def int_array_trans_func(arr_info, arr_length_orig, arr_length_trans, llm_code):
    arr_name = arr_info['name']
    arr_type = arr_info['type']
    length_param_name = arr_info['length_param_name']
    c_code = f"""
    // Exclusive transform for array: {arr_name}
    {arr_type}* cp_{arr_name} = ({arr_type}*)malloc({arr_length_orig} * sizeof({arr_type}));
    memcpy(cp_{arr_name}, test_cases[test_case_id].{arr_name}, {arr_length_orig} * sizeof({arr_type}));
    int follow_size_val_{arr_name} = {arr_length_trans}; // 后续大小的具体值
    {arr_type} *follow_{arr_name} = ({arr_type}*)malloc((follow_size_val_{arr_name} > 0 ? follow_size_val_{arr_name} : 1) * sizeof({arr_type}));
    memcpy(follow_{arr_name}, test_cases[test_case_id].{arr_name}, {arr_length_trans} * sizeof({arr_type}));
    {llm_code}
    """
    return c_code

def char_array_trans_func(arr_info, arr_length_orig, arr_length_trans, llm_code):
    arr_name = arr_info['name']
    arr_type = arr_info['type']
    length_param_name = arr_info['length_param_name']
    c_code = f"""
    // Exclusive transform for array: {arr_name}
    TestCase tc = test_cases[test_case_id];
    char** cp_{arr_name} = deep_copy_str_array((const char* const*)tc.{arr_name}, {arr_length_orig});
    int follow_size_val_{arr_name} = {arr_length_trans};// 后续大小的具体值
    char** follow_{arr_name} = deep_copy_str_array((const char* const*)tc.{arr_name}, (follow_size_val_{arr_name} > 0 ? follow_size_val_{arr_name} : 1));
    {llm_code}
    """
    return c_code

def array_model(code_info,func_id,return_type,inv_para_info):
    print(f"code_info:{code_info}")
    if "char" in code_info['parameter_type']:
        test_codes, test_result_struct_def = char_array_model(code_info,func_id,return_type)
    else:
        test_codes, test_result_struct_def = int_array_model2(code_info, func_id,return_type,inv_para_info)
    return test_codes , test_result_struct_def

def int_array_model(code_info, func_id, core_func_params, core_func_array_info, core_func_return_type, core_func_name):
    """
    适配性测试函数生成器（简化版）。
    本版本假设所有数组/指针参数都可能被修改，因此会统一为源测试用例中的所有数组创建本地副本。
    不再需要 'is_const' 标志。
    """
    source_copy_parts = []
    source_copy_map = {}                          
    for arr_info in core_func_array_info:
        arr_name = arr_info['name']
        length_param_name = arr_info['length_param_name']
        param_detail = next((p for p in core_func_params if p['name'] == arr_name), None)
        if not param_detail:
            continue
        base_type = param_detail['type'].replace('*', '').replace('[]', '').strip()
        copy_var_name = f"source_{arr_name}_copy"
        source_copy_map[arr_name] = copy_var_name
        length_expr = f"test_cases[test_case_id].{length_param_name}"
        source_array_expr = f"test_cases[test_case_id].{arr_name}"
        source_copy_parts.append(f"    // 为源参数 '{arr_name}' 创建一个本地副本以防被修改")
        source_copy_parts.append(f"    {base_type}* {copy_var_name} = ({base_type}*)malloc({length_expr} * sizeof({base_type}));")
        source_copy_parts.append(f"    memcpy({copy_var_name}, {source_array_expr}, {length_expr} * sizeof({base_type}));")
    source_copy_code = "\n".join(source_copy_parts)
    orig_args = []
    for p in core_func_params:
        if p['name'] in source_copy_map:
            orig_args.append(source_copy_map[p['name']])
        else:
            orig_args.append(f"test_cases[test_case_id].{p['name']}")
    orig_args_str = ", ".join(orig_args)
    call_s1 = f"{core_func_return_type} source = {core_func_name}({orig_args_str});"
    trans_args = [f"follow_case.{p['name']}" for p in core_func_params]
    call_s2 = f"{core_func_return_type} follow = {core_func_name}({', '.join(trans_args)});"
    free_parts = []
    for copy_var in source_copy_map.values():
        free_parts.append(f"    free({copy_var});")
    for arr_info in core_func_array_info:
        free_parts.append(f"    free(follow_case.{arr_info['name']});")
    free_statement_code = "\n".join(free_parts) if free_parts else "    // 无需释放内存。"
    return """
//{opt}
{pre_func}
//{opt}
TestResult z{id}runTest(int test_case_id) {{ // MODIFIED: Return type
    TestResult test_result; // MODIFIED: Add TestResult instance
    TestCase follow_case = z{id}Change(test_cases[test_case_id]);
{source_copy_code}
    // 原始调用
    {call_s1}
    // 变换后调用
    {call_s2}
    test_result.result1 = source; // MODIFIED
    test_result.result2 = follow; // MODIFIED
    // --- 自动生成的内存释放语句 ---
{free_statement_code}
    return test_result; // MODIFIED: Return TestResult
}}""".format(
        pre_func=code_info["code"],
        opt=code_info["operation"],
        id=func_id,
        source_copy_code=source_copy_code,
        call_s1=call_s1,
        call_s2=call_s2,
        free_statement_code=free_statement_code
    )

def split_free_statement(free_statement):
    """以|为分界线分割free_statement"""
    if '|' in free_statement:
        parts = free_statement.split('|', 1)           
        assignment_part = parts[0]             
        type_part = parts[1]                   
    else:
        assignment_part = free_statement
        type_part = ""
    return assignment_part, type_part

def extract_parentheses_content(s):
    """
    从字符串中提取函数调用括号内的内容
    @param s: 输入的字符串
    @return: 括号内的内容，如果未找到则返回空字符串
    """
    left_paren_pos = s.find('(')
    if left_paren_pos == -1:
        return ""           
    brackets = []
    right_paren_pos = -1
    for i in range(left_paren_pos, len(s)):
        c = s[i]
        if c == '(':
            brackets.append(c)
        elif c == ')':
            if brackets:
                brackets.pop()
                if not brackets:
                    right_paren_pos = i
                    break
    if right_paren_pos != -1 and right_paren_pos > left_paren_pos + 1:
        return s[left_paren_pos + 1:right_paren_pos]
    return ""                   

def int_array_model2(code_info, func_id,return_type,inv_para_info):
    vari_para1 = extract_parentheses_content(code_info["call_s1"])
    vari_para2 = extract_parentheses_content(code_info["call_s2"])
    print(f"codeinfo:{code_info}")
    free_statement = code_info.get('free_statement', '    // 未生成 free 语句。')
    if free_statement != "":             
        free_type = free_statement.split("|", 1)[1]
        free_type = free_type.rstrip('*') + "**"
    else:
        free_type = "int**"
    assignment_part, type_part = split_free_statement(free_statement)
    type_part = type_part.replace(';', '')
    define_part = "int** memory_list = (int**)malloc(1 * sizeof(int*));"
    if type_part != "":
        define_part = f"{type_part}* memory_list = ({type_part}*)malloc(1 * sizeof({type_part}));"
    test_codes = """
//get_inv
void z{id}getInv(TestResult t1, {inv_para_info}){{
    return;
}}
//para:{para} opt:{opt}
{pre_func}
//para:{para} opt:{opt}
TestResult z{id}runTest(int test_case_id) {{ // MODIFIED: Return type
    TestCase follow_case = z{id}Change(test_cases[test_case_id]);
    // 原始调用
    {call_s1}
    // 变换后调用
    {call_s2}
    {define_part}
    {assignment_part}
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    z{id}getInv(test_result, {vari_para1}, {vari_para2}); 
    return test_result; // MODIFIED: Return TestResult
}}""".format(
        para = code_info["parameter_name"],
        vari_para1 = vari_para1,
        vari_para2 = vari_para2,
        inv_para_info = inv_para_info,
        pre_func=code_info["code"],
        opt = code_info["operation"],
        id = func_id,
        param_name = code_info["parameter_name"],             
        call_s1 = code_info["call_s1"],
        call_s2 = code_info["call_s2"],
        assignment_part = assignment_part,            
        define_part = define_part
    )
    actual_member_type_for_test_result = return_type
    if return_type.strip().lower() == "void":
        actual_member_type_for_test_result = "int"
    test_result_struct_definition = f"""
    typedef struct {{
        {actual_member_type_for_test_result} result1;
        {actual_member_type_for_test_result} result2;
        {free_type} memory_to_free;
        int memory_count; 
    }} TestResult;
    """
    return test_codes, test_result_struct_definition

def char_array_model(code_info, func_id, return_type):
    """
    为 char 类型生成 runTest 函数。这个函数的核心逻辑现在与 int_array_model 完全相同，
    因为复杂的释放逻辑已经由上游处理了。
    """
    print(f"char_array_model_code_info: {code_info}")
    free_statement = code_info.get('free_statement', '    // 未生成 free 语句。')
    null_or_error_value = "NULL" if "char" in return_type else "-1"
    test_codes = """
//{opt}
{pre_func}
//{opt}
TestResult z{id}runTest(int test_case_id) {{ // MODIFIED: Return type
    TestResult test_result; // MODIFIED: Add TestResult instance
    // 新增：添加一个“守卫子句”，防止 NULL 输入导致程序崩溃
    if (test_cases[test_case_id].{param_name} == NULL) {{
        test_result.result1 = {null_or_error_value};
        test_result.result2 = {null_or_error_value};
        return test_result;
    }}
    TestCase follow_case = z{id}Change(test_cases[test_case_id]);
    // 原始调用
    {call_s1}
    // 变换后调用
    {call_s2}
    test_result.result1 = source; // MODIFIED
    test_result.result2 = follow; // MODIFIED
    // --- 核心修改：在此处插入动态生成的内存释放语句 ---
{free_statement_code}
    return test_result; // MODIFIED: Return TestResult
}}""".format(
        pre_func=code_info["code"],
        opt=code_info["operation"],
        id=func_id,
        param_name=code_info["parameter_name"],             
        call_s1=code_info["call_s1"],
        call_s2=code_info["call_s2"],
        free_statement_code = free_statement,           
        null_or_error_value = null_or_error_value
    )
    actual_member_type_for_test_result = return_type
    if return_type.strip().lower() == "void":
        actual_member_type_for_test_result = "int"
    test_result_struct_definition = f"""
    typedef struct {{
        {actual_member_type_for_test_result} result1;
        {actual_member_type_for_test_result} result2;
        int** memory_to_free;  //char类型未适配
        int memory_count; 
    }} TestResult;
    """
    return test_codes, test_result_struct_definition

# def char_array_model2(main_code, func_id, param_list,arr_info_first, array_info, func_return_type,func_name, opt):
#     "main_code:llm生成核心代码"
#     arr_name = arr_info_first['name']
#     arr_type = arr_info_first['type']
#     length_param_name = arr_info_first['length_param_name']
#     n_param_info = next((p for p in param_list if p['name'] == length_param_name and 'int' in p['type'] and not p['is_array']), None)
#     n_param_name = n_param_info['name']
#     original_length = f"test_cases[test_case_id].{length_param_name}"
#     taans_length = get_trans_length(original_length)
#     trans_c_codes = []
#     for arr_info in array_info:
#         arr_name = arr_info['name']
#         arr_length_name = arr_info.get("length_param_name")
#         arr_length_orig = f"test_cases[test_case_id].{length_param_name}"
#         arr_length_trans = get_trans_length(arr_length_orig)
#         c_code = char_array_trans_func(arr_info,arr_length_orig,arr_length_trans,main_code)
#         trans_c_codes.append(c_code)
#     transformed_array_names_map = {}
#     transformed_length_values_map = {}
#     unique_length_names = {arr.get("length_param_name") for arr in array_info if arr.get("length_param_name")}
#     for length_name in unique_length_names:
#         transformed_len_var_name = length_name
#         transformed_length_values_map[length_name] = f"test_cases[test_case_id].{length_name}"
#     for arr_info in array_info:
#         arr_name = arr_info['name']
#         length_param_name = arr_info.get("length_param_name")
#         transformed_name = f"follow_{arr_name}"
#         transformed_array_names_map[arr_name] = transformed_name
#     orig_args_str = build_call_args(param_list,False,{}, {})
#     trans_args_str = build_call_args(param_list,True,transformed_array_names_map, transformed_length_values_map)
#     return """
# //{opt}
# TestResult z{id}runTest(int test_case_id) {{ // MODIFIED: Return type
#     TestResult test_result; // MODIFIED: Add TestResult instance
# {transforms}
#     // 原始调用
#     {return_type} source = {func_name}({orig_args}); // MODIFIED: Explicit type
#     // 变换后调用
#     {return_type} follow = {func_name}({trans_args}); // MODIFIED: Explicit type
#     test_result.result1 = source; // MODIFIED
#     test_result.result2 = follow; // MODIFIED
#     free(cp_{arr_name});
#     free(follow_{arr_name});
#     return test_result; // MODIFIED: Return TestResult
# }}""".format(
#         opt = opt,
#         id = func_id,
#         transforms='\n'.join(trans_c_codes),
#         return_type=func_return_type,
#         func_name=func_name,
#         orig_args=orig_args_str,
#         trans_args=trans_args_str,
#         arr_name=arr_name
#     )

def find_arrays_and_lengths(param_list):
    """
    分析参数列表，识别数组参数及其可能关联的长度参数。
    此版本增强了对 'n' 前缀长度参数的识别，可处理 nk, n_k 等模式。
    参数:
    param_list - 参数列表，每项包含类型(type)、名称(name)和是否数组(is_array)
    返回:
    array_info - 数组信息列表，每个元素包含:
        "name": 数组参数名
        "type": 数组基本类型（去除指针/数组符号）
        "length_param_name": 匹配到的长度参数名（如找到）
    """
    arrays = [p for p in param_list if p["is_array"]]
    potential_length_params = {
        p["name"]: p for p in param_list
        if not p["is_array"] and 'int' in p["type"]
    }
    array_info = []
    used_length_params = set()
    for arr in arrays:
        possible_length_names = [
            f"{arr['name']}_len",
            f"{arr['name']}_length",
            f"{arr['name']}_size",
            f"num_{arr['name']}",
        ]
        possible_length_names.extend(["size", "len", "length", "count", "n"])
        n_prefixed_params = [
            name for name in potential_length_params
            if name.startswith('n') and len(name) > 1
        ]
        n_digits_names = [name for name in n_prefixed_params if name[1:].isdigit()]
        n_other_names = [name for name in n_prefixed_params if not name[1:].isdigit()]
        n_digits_names.sort(key=lambda n: int(n[1:]))
        n_other_names.sort()
        possible_length_names.extend(n_digits_names)
        possible_length_names.extend(n_other_names)
        matched_len_name = None
        for name_pattern in possible_length_names:
            if name_pattern in potential_length_params and name_pattern not in used_length_params:
                matched_len_name = name_pattern
                used_length_params.add(matched_len_name)         
                break
        base_type = " ".join(arr["type"].replace('*', '').replace('[]', '').replace('const', '').split())
        array_info.append({
            "name": arr["name"],
            "type": base_type,
            "length_param_name": matched_len_name
        })
    return array_info
