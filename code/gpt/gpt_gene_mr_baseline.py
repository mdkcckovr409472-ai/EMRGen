import os
import glob
from openai import OpenAI
import re
client = OpenAI
TARGET_FOLDER = "/home/robot/cp/InvariantMR/1_daikon_mt_gpt/program_all_use"
OUTPUT_FOLDER = "/home/robot/cp/InvariantMR/1_daikon_mt_gpt/llm"
EXAMPLE_TEMPLATE = """
Example Code:
int add_values(int a[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) sum += a[i];
    return sum;
}
Example Output:
MR ：For the function where the initial input Ts contains a (int*), if the operation 「add 1 to all elements」 is executed on a to obtain the new input Tf, then the initial output Os and the subsequent output Of of the function should satisfy the following relation:
Os < Of
----------------------------------------
MR ：For the function where the initial input Ts contains a (int*), if the operation 「multiply all elements by 2」 is executed on a to obtain the new input Tf, then the initial output Os and the subsequent output Of of the function should satisfy the following relation:
2 * Os == Of
----------------------------------------
MR ：For the function where the initial input Ts contains a (int*), if the operation 「reverse the entire array」 is executed on a to obtain the new input Tf, then the initial output Os and the subsequent output Of of the function should satisfy the following relation:
Os == Of
----------------------------------------
"""

def generate_mr_content(file_name, code_content):
    """
    Constructs the Prompt and calls the API to generate content.
    """
    system_prompt = (
        "You are an expert in metamorphic relation generation in the field of software testing. "
        "Your task is to generate as many transformation operations as possible for function parameters based on code logic, "
        "and derive the corresponding output relations. You must strictly adhere to the specified operation generation rules and output format."
    )
    user_content = f"""
Please analyze the following C++ function, and mimic the 【Format Example】 I provided to generate as many metamorphic relations as possible for this function.
Code to be analyzed ({file_name}):
{code_content}
【Generation Steps】
1. For every transformable parameter in the given function, generate as many descriptions as possible of transformation operations involving various distinct principles. The operations must only involve a single object, excluding length parameters.
2. Based on these transformation operations, identify as many metamorphic relation descriptions for the function as possible (Os represents the initial output and Of represents the subsequent output). Each operation might contain no metamorphic relation, or it might involve multiple metamorphic relations.
3. Generate the corresponding results according to the generation format requirements below.
【Core Task: Operation Generation Rules】
Before generating MRs, please strictly follow the logic below to think about how to transform the parameters:
1.  **Parameter Analysis and Classification**:
    *   Identify length control parameters (e.g., size, len, n, count). It is **strictly prohibited** to modify these length parameters themselves.
    *   Only generate transformation operations for **non-length control parameters** (e.g., array contents, numeric variables).
2.  **Operation Diversity Requirements (Maximize Diversity)**:
    Generate as many different principles of operations as possible for each modifiable parameter, which must cover the following categories:
    *   **Mathematical transformations**: Must include addition, subtraction, multiplication, and division (e.g., 「add 1 to all elements」, 「multiply by 0.5」). When values are involved, specific values must be given or substitutes like 'k' should be used.
    *   **Sequence/Position transformations** (for arrays): Reverse, sort (ascending/descending), shuffle randomly, circular shift.
    *   **Special value injection**: Set all to 0, set all to 1, set a specific element to the maximum/minimum value.
    *   **Array/Sub-array operations**: If the return type allows, try modifying partial elements.
    *   **Note**: For functions returning an array, apart from "adding/removing one element", **avoid** generating operations that drastically change the array length (like truncating in half, self-replication) to prevent breaking memory relations.
3.  **Strict Prohibitions**:
    *   **No cross-parameter operations**: An operation can only modify one parameter (e.g., cannot modify both a and b at the same time).
    *   **No bitwise operations**: Do not generate "bitwise AND", "bitwise OR" operations.
    *   **No ambiguous operations**: Do not use vague descriptions like "add noise"; they must be precise (e.g., "add 0.01").
    *   **Memory safety**: The logic implied by the operation description must comply with C++ memory safety (e.g., no index out of bounds).
【Generation Format Requirements】 (Must be strictly followed, used for script parsing)
1.  **Sentence Template**: Every MR must strictly use the following fixed sentence structure, and punctuation marks must not be altered:
    "MR ：For the function where the initial input Ts contains [variable_name] ([variable_type]), if the operation 「[operation_description]」 is executed on [variable_name] to obtain the new input Tf, then the initial output Os and the subsequent output Of of the function should satisfy the following relation:"
2.  **Critical Symbols**:
    *   Use a **full-width colon** (：) after "MR".
    *   The operation description must be enclosed in **Chinese corner brackets** (「 and 」).
    *   The operation description must be clear and unambiguous, e.g., 「add 2 to all elements」.
3.  **Mathematical Relation on an Independent Line**: The line immediately following the description sentence must and can only be a mathematical relational expression containing Os and Of (e.g., Os == Of, Os < Of, 2 * Os == Of). Do not add any remarks, and do NOT include Os != Of.
4.  **Separators**: Use dashed lines (----------------------------------------) to separate each MR.
【Format Example】
{EXAMPLE_TEMPLATE}
Please think according to the 【Core Task: Operation Generation Rules】 above, and output the results following the 【Generation Format Requirements】. Do not output Markdown formatting tags.
Please start generating:
"""
    try:
        response = client.chat.completions.create(
            model="gpt-3.5-turbo",
            messages=[
                {"role": "system", "content": system_prompt},
                {"role": "user", "content": user_content},
            ],
            stream=False,
        )
        print(f"usercontent:{user_content}")
        return response.choices[0].message.content.strip()
    except Exception as e:
        print(f"API 调用出错: {e}")
        return None

def save_report(file_name, code_content, mr_content):
    """
    按照要求的最终格式拼接并保存文件
    """
    base_name = os.path.splitext(file_name)[0]
    specific_output_dir = os.path.join(OUTPUT_FOLDER, base_name)
    if not os.path.exists(specific_output_dir):
        os.makedirs(specific_output_dir)
    output_filename = f"final_report_{base_name}.txt"
    output_path = os.path.join(specific_output_dir, output_filename)
    count = mr_content.count("MR ：")
    final_output = f"{code_content}\n\n"
    final_output += "========================================================\n"
    final_output += " *  Contextual Operations and Discovered Invariants\n"
    final_output += "========================================================\n\n"
    final_output += mr_content + "\n\n"
    final_output += f"操作总数: {count}\n"
    final_output += f"关系总数: {count}\n"
    try:
        with open(output_path, 'w', encoding='utf-8') as f:
            f.write(final_output)
        print(f"  -> 生成完毕: {output_path} (包含 {count} 条关系)")
    except Exception as e:
        print(f"  -> 写入文件失败: {e}")

def main():
    if not os.path.exists(TARGET_FOLDER):
        print(f"错误: 文件夹 '{TARGET_FOLDER}' 不存在。")
        return
    cpp_files = glob.glob(os.path.join(TARGET_FOLDER, "*.cpp"))
    if not cpp_files:
        print(f"在 '{TARGET_FOLDER}' 中未找到 .cpp 文件。")
        return
    print(f"开始处理 {len(cpp_files)} 个文件...")
    for file_path in cpp_files:
        file_name = os.path.basename(file_path)
        print(f"正在分析: {file_name} ...")
        try:
            with open(file_path, 'r', encoding='utf-8') as f:
                code_content = f.read()
        except Exception as e:
            print(f"  -> 读取源码失败: {e}")
            continue
        mr_content = generate_mr_content(file_name, code_content)
        if mr_content:
            save_report(file_name, code_content, mr_content)
        else:
            print(f"  -> {file_name} 生成内容为空，跳过。")

def gene_change_check(code_info, mr_info, testcase_struct):
    user_content = f"""
You are now a senior C++ software testing and automated generation expert. Your task is to generate two core C++ scheduling functions for an automated Metamorphic Testing framework based on the context I provide.
[Input Context Information]
1. C++ source code of the function under test:
{code_info}
2. Rule description of the Metamorphic Relation (MR):
{mr_info}
3. The defined TestCase struct (used to store the initial test case array):
{testcase_struct}
[Task Objectives]
To integrate with a fixed main() batch testing framework, please strictly follow the MR rules in [Information 2] to generate the following two functions:
1. `TestCase change(TestCase tc)`: Construct the follow-up input based on the source input.
2. `int check(TestCase tc)`: Execute the test, verify the metamorphic relation, and clean up resources.
[Coding Standards & Constraints]
1. Test case reuse principle: When processing the TestCase in the `change()` function, reuse the data and associated states from the original struct, performing necessary field overwrites based on the passed object.
2. When verifying Os (source output) and Of (follow-up output) in `check()`, you must evaluate whether their relationship satisfies the corresponding MR description.
3. If dynamic memory is allocated using `new` or `malloc` inside the `change()` function or during parameter extraction, it must be correctly deallocated (`delete`/`free`) before the `check()` function returns (this includes before both `return 1` and `return 0`).
[Function Templates & Workflow Reference (Does not need to be identically strict)]
// 1. Follow-up input construction function
TestCase change(TestCase tc) {{
    TestCase tf = tc; 
    // Modify the internal fields of tf according to the MR rules in [Information 2] to construct the follow-up input Tf
    // tf.xxx = ... 
    return tf;
}}
// 2. Verification function
int check(TestCase tc) {{
    // (1) Extract the source input (Ts)
    // auto Ts = tc.xxx;
    // (2) Call the function under test from [Information 1] to get the source output (Os)
    // auto Os = target_function(Ts);
    // (3) Call the change function to construct the follow-up test case object
    TestCase Tf_case = change(tc);
    // (4) Extract the follow-up input and get the follow-up output (Of)
    // auto Of = target_function(Tf_case.xxx);
    // (5) Verify whether Os and Of satisfy the metamorphic relation based on [Information 2]
    int is_valid = 0;
    if ( /* Verify if Os and Of satisfy the MR logic */ ) {{
        is_valid = 1;
    }}
    // (6) Free Tf_case or any dynamic memory generated during the process
    // (7) Return the verification result
    return is_valid;
}}
[Output Requirements]
1. Do NOT output any explanatory text, analytical processes, or markdown code block wrappers (do NOT output ```cpp and ```).
2. ONLY output pure plain-text C++ code.
3. Strictly follow the layout format below for your output:
[Complete code of the change() function]
---------------------------
[Complete code of the check() function]
"""
    try:
        response = client.chat.completions.create(
            model="gpt-3.5-turbo",
            messages=[
                {"role": "system", "content": ""},
                {"role": "user", "content": user_content},
            ],
            stream=False,
        )
        get_content = response.choices[0].message.content
        clean_content = get_content.replace("```cpp", "").replace("```c++", "").replace("```C++", "").replace("```", "")
        clean_content = clean_content.strip()
        parts = re.split(r'(?://)?\s*-{5,}\s*', clean_content)
        if len(parts) >= 2:
            change_code = parts[0].strip()
            check_code = parts[1].strip()
            return change_code, check_code
        else:
            check_func_index = clean_content.find("int check(")
            if check_func_index != -1:
                change_code = clean_content[:check_func_index].strip()
                check_code = clean_content[check_func_index:].strip()
                return change_code, check_code
            else:
                print("警告：大模型未生成预期的分割线，且未能找到 check 函数签名。")
                print("模型原始输出：\n", clean_content)
                return clean_content, ""
    except Exception as e:
        print(f"API 调用出错: {e}")
        return None, None
if __name__ == "__main__":
    main()
