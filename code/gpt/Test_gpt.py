from openai import OpenAI
import os
import sys,io
import ast
import re
sys.stdin = io.TextIOWrapper(sys.stdin.buffer, encoding='utf-8')
client = OpenAI

def get_operation_llm_unnumber(function_name, return_type, parameters):
    system_content = f"You are a professional assistant specialized in generating input transformation operations for metamorphic testing. Your task is to generate as diverse transformation operations as possible for each mutable parameter based on the function parameter information. You must strictly adhere to the user-specified output format and provide absolutely no extra explanations."
    user_content = (f"""
    Please explore feasible operations for the following inputdata, from the perspective of applying metamorphic relations.
    The information of input data:
    • Function Name: {function_name}
    • Return Type: {return_type}
    • Full Parameter List: {parameters}
    The output format:
        `Parameter Name 1 | Parameter Type 1 | Operation 1 | Operation 2 | ... | Operation N`
        `Parameter Name 2 | Parameter Type 2 | Operation 1 | Operation 2 | ... | Operation N`
    **Core Tasks and Rules:**
    Your task is to generate a single line containing descriptions of multiple transformation operations based on diverse principles for **every mutable parameter** in the given function.
    1. **Parameter Analysis and Classification**:
       a) Analyze the parameter list and identify length-controlling parameters (e.g., size/len/n/count).
       b) Categorize parameters into:
          • **Mutable parameters**: Non-length-controlling parameters.
          • **Immutable parameters**: Length-controlling parameters.
    2. **Maximize Operation Quantity**: Generate **as many high-quality** transformation operations based on different principles **as possible** for each mutable parameter.
    3. **Intra-Parameter Operation Diversity**:
       a) Operation types should cover: global operations, positional operations, content modifications, mathematical transformations, logical transformations, and random perturbations. They must also include addition, subtraction, multiplication, and division operations.
       b) Based on design requirements, cross-parameter operations are strictly prohibited (e.g., when operating on parameter 'a', modifying parameter 'b' or modifying both simultaneously is forbidden; you can only modify 'a'). However, operations on two elements within the same array are allowed (e.g., incrementing one element in an array by 1 while decrementing another element by 1).
       c) For array parameters, additionally include: sorting operations and subarray operations.
       d) For numerical parameters, additionally include: type casting and special value injections (strictly limited to 0, 1, and -1; absolutely no +inf, -inf, or NaN).
       e) If the function's return type is an array, apart from adding a single new element or removing a single element, do not include operations that change the array's length (e.g., truncating the first half of the array, self-duplication).
       f) Avoid generating overly specialized or cross-domain operations.
       g) Avoid generating noise-adding operations (e.g., adding/subtracting tiny epsilon values like 1e-9) and strictly avoid special floating-point values (e.g., +inf, -inf, NaN).
       h) Avoid "bitwise AND" and "bitwise OR" operations.
       i) When specific numerical values are involved, state the exact value explicitly, unless specifying "set to maximum" or "set to minimum".
       j) When setting numerical values, explicitly state the directional tendency of the modification. For example: "set a random position's element to 999 (when the element is less than 999)".
    4. **Strict Memory Safety Requirements**:
       a) Array indices must have bounds checking.
       b) String arrays must comply with memory management rules.
       c) Cross-parameter operations are strictly prohibited.
       d) Operation descriptions must be clear and unambiguous. Use parentheses for clarification if necessary (e.g., "Left circular shift of array (move first element to the end)").
    5. **Output Format**:
       a) Format: `Parameter Name | Parameter Type | Operation 1 | Operation 2 | ... | Operation N`
       b) **Generate as many high-quality operations as possible, but do not exceed 30 operations per parameter.**
       c) Do not output anything for immutable parameters.
    **Example Output:**
    `data_in | array[int] | add 1 to all elements | set random position to -1 | swap two random elements | right shift array | reverse array | randomly shuffle | fill with random numbers | square elements | take absolute value`
    `factor | double | multiply by 2.0 | subtract 1.5 | add 1.0 | set to 2.0 | take reciprocal | square root | round to integer | random perturbation | take absolute value`
    Now, please execute the task for the function `{function_name}`.""")
    response = client.chat.completions.create(
        model="gpt-3.5-turbo",
        messages=[
            {"role": "system", "content": system_content},
            {"role": "user", "content": user_content},
        ],
        stream=False,
    )
    print(f"{system_content}\n{user_content}")
    operations = response.choices[0].message.content
    print(f"operations:{operations}")
    operations_cleaned = re.sub(r'```[a-zA-Z]*', '', operations)
    operations_cleaned = operations_cleaned.replace('`', '')
    structured_operations = []
    for line in operations_cleaned.splitlines():
        if not line.strip():
            continue
        parts = [part.strip() for part in line.split('|')]
        if len(parts) >= 2:
            param_dict = {
                "parameter_name": parts[0],                 
                "parameter_type": parts[1],                  
                "operations": parts[2:]                             
            }
            structured_operations.append(param_dict)
    return structured_operations

def get_main_code(testCaseStruct,parameter_name,parameter_type,operation,parameters,id,func_name,return_type):
    system_content = f"You are a code generation assistant that strictly follows instructions. You must strictly output in the format specified by the user, and only output the operations for one parameter without any extra explanation."
    user_content_int = f"""
    You need to generate a safe and robust C++ function based on the following information to implement the transformation of the given input data. The generated code must be able to handle various edge cases (e.g., empty arrays, single-element arrays) without crashing.
    The information of input data and transformation:
    Operation ID (id): {id}
    Initial function name (func_name): {func_name}
    Function return type (return_type): {return_type}
    TestCase struct (TestCaseStruct): {testCaseStruct}
    Target parameter name (parameter_name): {parameter_name}
    Target parameter type (parameter_type): {parameter_type}
    Specific transformation operation description (operation): {operation}
    Original function parameters (parameters): {parameters} (This is strictly for understanding the context; the function implementation should be based on TestCaseStruct)
    The format of the generated function:
     [DO NOT output any markdown formatting like ```c or ```cpp, just raw code]
    TestCase z{id}Change(TestCase t1) {{
        TestCase follow_case = t1;
    // [Step 1: Deep copy memory allocation ONLY IF the parameter is an array/pointer]
    // (e.g., malloc and memcpy)
       // [Step 2: Defensive Programming & Boundary Checks]
    // (e.g., if (follow_case.n < 2) return follow_case;)
    // [Step 3: Specific transformation logic translated from {operation}]
    // (Apply changes to follow_case)
    return follow_case;
    }}
    Generation Rules (Must be strictly followed):
    TestCase Struct Usage:
    Assume the {testCaseStruct} is already defined. You MUST NOT output any #include statements or struct definitions. Start your output directly with the function signature.
    Function Signature:
    The function name must be z{id}Change.
    Both the parameter and return value types of the function must be TestCase. The complete signature is TestCase z{id}Change(TestCase t1).
    Function Body - Core Template:
    The function body must start with TestCase follow_case = t1; and end with return follow_case;.
    Special Memory Handling for Arrays/Pointers (Critical Rule):
    Condition: Execute if and only if {parameter_type} is an array type.
    Operation: Use malloc and memcpy to create and populate a deep copy for the target parameter in follow_case. The memory size and loop boundaries must use the corresponding length variables in the TestCase struct. This copy operation must be placed on the very first lines and precede any defensive programming or boundary checks.
    Operation Code Translation:
    Translate the {operation} (natural language description) into specific C code, operating on the replica inside follow_case.
    Defensive Programming and Boundary Checks (Highest Priority Rule):
    Before implementing the operation code, you must add strict checks to prevent runtime errors. This is the most important rule.
    a) Check Array Length:
    If the operation requires at least 1 element (e.g., loop traversal), an if (follow_case.n > 0) check must be added.
    If the operation requires at least 2 elements (e.g., "swap first and last elements", "construct an arithmetic sequence"), an if (follow_case.n < 2) check must be added, returning immediately if not satisfied.
    b) Avoid Division by Zero:
    Before any division operation, check if the denominator is zero. If the denominator depends on the array length (like n-1), this check should be covered by rule a.
    c) Protect Mathematical Function Domains:
    Before using functions like sqrt(), check if the input value is within its valid domain (e.g., x >= 0). Invalid inputs should result in skipping the transformation for that element.
    d) Memory Safety - Forbid Illegal free:
    Inside the z{id}Change function, calling free() to release the passed parameter t1 or its members (like t1.a) is strictly forbidden. free() should only be used in the testing framework (e.g., runTest function) to release newly allocated memory created by the z{id}Change function.
    e) When writing z{id}Change, for malloc operations, you must completely copy the entire array to avoid copying only a portion of it.
    Function Call Strings Generation:
    After generating the complete C++ function, you must additionally generate two lines of C++ code strings.
    These two lines should be placed outside the main C function code block and separated by the comment header // --- Generated function call strings ---.
    First Line (Original Call):
    Format: {{type}} source = {func_name}(...); // MODIFIED: Explicit type  {{type}} is the return type corresponding to the function.
    Parameters List: Strictly constructed according to the order and names in {parameters}, and each parameter must be prefixed with test_cases[test_case_id].
    Second Line (Follow Call):
    Format: {{type}} follow = {func_name}(...);{{type}} is the return type corresponding to the function.
    Parameters List: Also strictly constructed according to the order and names in {parameters}, but each parameter must be prefixed with follow_case.
    IMPORTANT: The type used in these two lines MUST be exactly the provided return_type = {return_type}. Do NOT use int if the return_type is double, float, or any other type.
    Example:
    Input Information:
    id: 14
    func_name: add_values
    TestCaseStruct: typedef struct {{ int* a; int n; }} TestCase;
    parameter_name: a
    parameter_type: array[int]
    operation: Construct an arithmetic sequence
    parameters: (int a[], int n)
    Expected Output (Complete Code):
    TestCase z14Change(TestCase t1) {{
    TestCase follow_case = t1;
    // --- Memory handling code generated based on the rule ---
    int* follow_case_a = (int*)malloc(t1.n * sizeof(int));
    memcpy(follow_case_a, t1.a, t1.n * sizeof(int));
    follow_case.a = follow_case_a;
    // ------------------------------------
    // Defensive code generated based on rule (a) to prevent errors when n < 2
    if (follow_case.n < 2) {{
        // Less than 2 elements, cannot form a sequence, return replica directly
        return follow_case;
    }}
    // Specific operation code generated based on the rule
    int first = follow_case.a[0];
    int last = follow_case.a[follow_case.n - 1];
    // Division denominator (n-1) is guaranteed not to be zero by n >= 2
    int diff = (last - first) / (follow_case.n - 1);
    for (int i = 0; i < follow_case.n; i++) {{
    follow_case.a[i] = first + i * diff;
    }}
    return follow_case;}}
    // --- Generated function call strings ---
    int source = add_values(test_cases[test_case_id].a, test_cases[test_case_id].n); // MODIFIED: Explicit type
    int follow = add_values(follow_case.a, follow_case.n);
    """
    user_content = user_content_int
    response = client.chat.completions.create(
        model="gpt-3.5-turbo",
        messages=[
            {"role": "system", "content": system_content},
            {"role": "user", "content": user_content},
        ],
        stream=False
    )
    get_content = response.choices[0].message.content
    print("get_content_gpt")
    print(get_content)
    print("get_content_end")
    cleaned_content = get_content.strip()
    if cleaned_content.startswith("```cpp"):
        cleaned_content = cleaned_content[6:].strip()
    elif cleaned_content.startswith("```c"):
        cleaned_content = cleaned_content[4:].strip()
    elif cleaned_content.startswith("```"):
        cleaned_content = cleaned_content[3:].strip()
    if cleaned_content.endswith("```"):
        cleaned_content = cleaned_content[:-3].strip()
    separator = "// --- Generated function call strings ---"
    parts = cleaned_content.split(separator)
    function_code = ""
    call_string_1 = ""
    call_string_2 = ""
    if len(parts) > 0:
        function_code = parts[0].strip()
    if len(parts) > 1:
        calls_block = parts[1].strip()
        call_lines = calls_block.splitlines()
        cleaned_lines = [line.strip() for line in call_lines if line.strip()]
        if len(cleaned_lines) >= 1:
            call_string_1 = cleaned_lines[0]
        if len(cleaned_lines) >= 2:
            call_string_2 = cleaned_lines[1]
    code_res = {}
    code_res["func"] = function_code
    code_res["call_string1"] = call_string_1
    code_res["call_string2"] = call_string_2
    print(f"code_res!!!!:{code_res}")
    return code_res

def check_code(data_type,id,is_array,invariant_condition):
    user_content = f"""
    Your task is to generate a complete, safe, and robust C/C++ validation function based on the provided information. This function takes two parameters representing execution results and checks if they satisfy a specific invariant condition. If the condition is fully satisfied, the function returns 1; if there is any violation of the condition, it returns 0.
    Input Information:
    Operation ID (id): {id}
    Data Type (data_type): {data_type}
    Is Array (is_array): {is_array} 
    Invariant Condition (invariant_condition): {invariant_condition}
    =========================================
    Generation Templates:
    [When {is_array} is 1]
    int z{id}check({data_type} result1, {data_type} result2, int n) {{
        // 1. Defensive programming (Null pointer and length checks)
        if (result1 == NULL || result2 == NULL) return 0;
        if (n <= 0) return 1;
        // 2. Core evaluation logic (elementwise)
        for (int i = 0; i < n; i++) {{
            if (!( /* Check if result1[i] and result2[i] satisfy {{invariant_condition}} */ )) {{
                return 0; // Return 0 immediately upon any violation
            }}
        }}
        // 3. Fully satisfied, return 1
        return 1;
    }}
    [When {is_array} is 0]
    int z{id}check({data_type} result1, {data_type} result2) {{
        // 1. Core evaluation logic (direct scalar comparison)
        if (!( /* Check if result1 and result2 satisfy {invariant_condition} */ )) {{
            return 0;
        }}
        // 2. Satisfied, return 1
        return 1;
    }}
    Generation Rules (Strictly Enforced):
    1. Dynamic Generation of Function Signature and Parameters:
       - The function name must be exactly: z{id}check.
       - The return type must be: int (1 means satisfied, 0 means not satisfied).
       - The default name for the length parameter is n.
       - The parameter list must be dynamically determined by the value of {is_array}:
         * If {is_array} is 1 (or data_type contains '*'): The function must accept three parameters. The first two parameter types are {data_type}, named result1 and result2 respectively; the third parameter type is int, named n.
           (Example: int z{id}check(int* result1, int* result2, int n))
         * If {is_array} is 0: 
            - If {invariant_condition} contains the variable 'n', it MUST accept three parameters: {data_type} result1, {data_type} result2, int n. (Example: int zcheck(double result1, double result2, int n))
            - Otherwise, accept two parameters: {data_type} result1, {data_type} result2.
    2. Logic Validation Implementation Rules:
       - If invariant_condition is in the format "return.result1 < return.result2", treat it as "result1 < result2".
       - Scalar comparison logic (non-array): Compare result1 and result2 directly based on {invariant_condition}. If not satisfied, `return 0;`.
       - Lexicographical comparison logic (Lexical - for conditions containing "(lexically)"):
         * If {invariant_condition} contains "(lexically)", you ABSOLUTELY MUST NOT use the elementwise evaluation template!
         * You must implement standard lexicographical logic: Iterate from 0 to n-1. Upon encountering the **first unequal pair of elements** (floating-point numbers must consider the tolerance in Rule 3), directly determine the final result based on the size relationship of this **single pair** of elements and return immediately (e.g., if the requirement is <= and result1[i] < result2[i], immediately return 1; if result1[i] > result2[i], immediately return 0).
         * Warning: As soon as the first unequal element is found and a result is concluded, ABSOLUTELY DO NOT check any subsequent elements!
         * If the loop ends without finding any unequal elements (i.e., the two arrays are completely equal), if the condition allows equality (like <=), return 1; if strictly unequal (like <), return 0.
       - Array comparison logic (elementwise): 
         * Check if {invariant_condition} contains array slice notation (e.g., `[a..b]`).
         * [Full Array Comparison]: If there are no slice notations, or if it explicitly requires comparing the whole array, use a standard loop `for (int i = 0; i < n; i++)`.
         * [Partial Slice Comparison (Crucial)]: If it contains `[a..b]` (e.g., `result1[][0..0] == result2[][0..0]`), **it is strictly forbidden to blindly use `i < n` as the loop boundary!** 
           -> If a and b are equal (e.g., `[0..0]`), **DO NOT use a for loop**. Directly perform a single evaluation on that specific index (e.g., directly write `if (!(result1[0] == result2[0])) return 0;`).
           -> If a and b are not equal (e.g., `[0..2]`), generate a loop based on the extracted boundaries: `for (int i = a; i <= b; i++)`.
         * Inside the loop (or in the single evaluation), compare result1 and result2 element by element to see if they satisfy {invariant_condition}.
         * Once **any pair** of elements fails to satisfy the condition, you must immediately exit and `return 0;` (short-circuit evaluation).
        - If all checks pass (or the loop finishes normally), `return 1;` at the end of the function.
    3. Special Handling for Floating-Point Comparisons (Dynamic Tolerance and Infinity Handling):
       If {data_type} contains float or double, you MUST strictly adhere to the following workflow. Directly comparing regular floating-point numbers using ==, <, > is strictly prohibited:
       Step 1: Define the base tolerance `double epsilon = 1e-5;`
       Step 2: Extract the left and right operands A and B (**Algebraic rearrangement is mandatory to restore data magnitude!**)
       If the format of {invariant_condition} places all variables on one side of the comparison operator (e.g., `expression - expression == 0` or `expression <= 0`), you **ABSOLUTELY MUST NOT** set B = 0! Because this will lose the original massive magnitude of large floating-point numbers, leading to calculation errors in tolerance.
       You must mathematically rearrange the equation (or inequality) so that `result1` and `result2` are distributed on both sides of the comparison operator (==, <, >, <=, >=), thereby restoring their true magnitudes.
       Step 3: Defend against NaN, and implement special pass-through for Inf
       After extracting A and B, the following logic must be added:
           `if (std::isnan(A) || std::isnan(B)) return 0;`
           `if (std::isinf(A) || std::isinf(B)) {{`
           `    if ( /* Directly use <, >, == etc. to compare A and B based on the rearranged {invariant_condition} */ ) return 1;`
           `    else return 0;`
           `}}`
       Step 4: Calculate Dynamic Tolerance
       `double tol = epsilon * fmax(1.0, fmax(fabs(A), fabs(B)));`
       Step 5: Tolerance-based comparison evaluation
       Note: The evaluation MUST be based on the comparison operator **AFTER rearrangement**!
       - [For Element-wise mode (Default)]: If violated, return 0 immediately:
         * If the condition is (`==`): if `fabs(A - B) > tol`, then `return 0;`
         * If the condition is (`<=`): if `A > B + tol`, then `return 0;`
         * If the condition is (`>=`): if `A < B - tol`, then `return 0;`
         * If the condition is (`<`): if `A >= B - tol`, then `return 0;`
         * If the condition is (`>`): if `A <= B + tol`, then `return 0;`
       - [For Lexicographical mode (CRITICAL)]: If {invariant_condition} contains "(lexically)", DO NOT use the violation rules above! You MUST use a 3-way branch to skip equal elements:
         `if (fabs(A - B) <= tol) continue; // Equal within tolerance, check next element`
         `else if (A > B + tol) return /* 1 if expects > or >=; else 0 */;`
         `else return /* 1 if expects < or <=; else 0 */;`
    4. Defensive Programming and Boundary Checks (Highest Priority & STRICT ORDER):
       Before executing any core logic, the following safety checks MUST be added EXACTLY in this order:
       a) Length validity check (FIRST): If {is_array} is 1, check the length first: `if (n <= 0) return 1;` (Empty arrays default to not violating the condition, hence treated as satisfied. This avoids falsely rejecting valid empty arrays where pointers might naturally be NULL).
       b) Null pointer check (SECOND): If {is_array} is 1, check pointers AFTER the length check: `if (result1 == NULL || result2 == NULL) return 0;`
    5. Code Purity:
       Please output ONLY pure C/C++ code. Do not include any markdown explanations, do not write a main function. Only output the implementation of the `z{id}check` function.
    """
    response = client.chat.completions.create(
        model="gpt-3.5-turbo",
        messages=[
            {"role": "system", "content": ""},
            {"role": "user", "content": user_content},
        ],
        stream=False
    )
    get_content = response.choices[0].message.content
    get_content = re.sub(r'^\s*(?:\+\+\s*|#include\s*<cmath>\s*)+', '', get_content)
    match = re.search(r'```[a-zA-Z]*\s*(.*?)```', get_content, re.DOTALL)
    if match:
        get_content = match.group(1).strip()
    else:
        get_content = get_content.strip()
    return get_content

def strip_markdown_code_block(text: str) -> str:
    """移除 text 中可能包裹的 Markdown 代码块标记（如 ```cpp ... ```）"""
    pattern = r'```(?:\w+)?\s*\n(.*?)\n```'
    match = re.search(pattern, text, re.DOTALL)
    if match:
        return match.group(1).strip()
    lines = text.split('\n')
    if lines and lines[0].strip().startswith('```'):
        lines = lines[1:]
    if lines and lines[-1].strip() == '```':
        lines = lines[:-1]
    return '\n'.join(lines).strip()

def get_input_data(function, num):
    system_content = "You are a senior C++ test engineer, specializing in writing high-coverage, robust unit tests. Your task is to generate a set of input test cases for a given C++ target function. You must strictly output in the format specified by the user, without providing any extra explanation."
    separator = "//__SPLIT__"
    user_content = f"""
    I will provide the source code of a C++ function. You need to analyze the parameter signature of this function and generate data for two parts.
    # Goal
    Generate {num} representative test cases. The data should include:
    1. **Base cases**: Typical input data to verify the basic functionality of the function.
    2. To ensure the function runs normally, do NOT generate extreme values, empty values, or NULL. All pointer parameters must point to valid, non-null memory.
    3. There must be no obvious patterns between the values in the arrays, such as strictly increasing or decreasing (unless required by the specific nature of the function's functionality).
    4. Ensure numeric diversity: For numeric arrays (especially double), values must span a wide range of magnitudes. Do NOT restrict values to [-10, 10]. Explicitly include tens, hundreds, or thousands (e.g., 42.5, -150.2, 300.0).
    5. Within a single test case, if there are multiple arrays, their lengths should be the same. However, across different test cases, the array lengths should vary randomly.    
    # Output Format Constraints (Must be strictly followed)
    Please output two parts, separated by `{separator}`.
    **Part 1: Struct Member Definition List**
    - **Each line** defines one member variable in the format `Type variable_name;`.
    - **Critical Rule**: If a function parameter is an array (e.g., `int a[]` or `int a[10]`), it **must** be defined as a pointer in the struct (e.g., `int* a;`).
    - **Never** use `[]` in the struct members.
    - Example: `int a[]` -> `int* a;`
    **Part 2: Test Case Initialization List**
    - **Do not include** the `TestCase test_cases[] =` wrapper.
    - **Each line** represents the data for one test case.
    - The format is: `{{ value_for_param1, value_for_param2, ... }},` 
    - Array/pointer parameters must use compound literals, for example, `(int[]){{1, 2, 3}}`.
    - **A comma must be added at the end of every line.**
    # Example (Reference only)
    **Input Function:**
    int func(int* arr, int n);
    **Output:**
    int* arr;
    int n;
    {separator}
    {{(int[]){{1, 2, 3}}, 3}},
    {{(int[]){{2, 4, 3, -1}}, 4}},
    {{(int[]){{-5, 100}}, 2}},
    # Target Task
    **Input Function:**
    {function}
    """
    response = client.chat.completions.create(
        model="gpt-3.5-turbo",
        messages=[
            {"role": "system", "content": system_content},
            {"role": "user", "content": user_content},
        ],
        stream=False,
    )
    res = response.choices[0].message.content
    test_case_fields = []
    test_cases_init = []
    if separator in res:
        parts = res.split(separator)
        part1_str = strip_markdown_code_block(parts[0].strip())
        part2_str = strip_markdown_code_block(parts[1].strip())
        for line in part1_str.split('\n'):
            line = line.strip()
            if line:
                if line.endswith(';'):
                    line = line[:-1]
                test_case_fields.append(line)
        for line in part2_str.split('\n'):
            line = line.strip()
            if line:
                if line.endswith(','):
                    line = line[:-1]
                if line.startswith('{') and line.endswith('}'):
                    test_cases_init.append(line)
    else:
        print("Error: Separator not found in LLM response.")
        return [], []
    return test_case_fields, test_cases_init
