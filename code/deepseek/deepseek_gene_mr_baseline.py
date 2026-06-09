import os
import glob
from openai import OpenAI
import re
client = OpenAI
TARGET_FOLDER = "/home/robot/cp/InvariantMR/1_daikon_mt/program_test"
OUTPUT_FOLDER = "/home/robot/cp/InvariantMR/1_daikon_mt/test_llm"
EXAMPLE_TEMPLATE = """
Example Code:
int add_values(int a[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) sum += a[i];
    return sum;
}
Example Output:
MR ：对于初始输入Ts中包含a（int*）的函数，若对 a执行「所有元素加1」操作得到新输入Tf，则函数的初始输出Os和后续输出Of应满足以下关系：
Os < Of
----------------------------------------
MR ：对于初始输入Ts中包含a（int*）的函数，若对 a执行「所有元素乘2」操作得到新输入Tf，则函数的初始输出Os和后续输出Of应满足以下关系：
2 * Os == Of
----------------------------------------
MR ：对于初始输入Ts中包含a（int*）的函数，若对 a执行「反转整个数组」操作得到新输入Tf，则函数的初始输出Os和后续输出Of应满足以下关系：
Os == Of
----------------------------------------
"""

def generate_mr_content(file_name, code_content):
    """
    构造 Prompt 并调用 DeepSeek API 生成内容
    """
    system_prompt = (
        "你是一个软件测试领域的蜕变关系生成专家。你的任务是根据代码逻辑，为函数参数生成高质量的变换操作，并推导对应的输出关系。"
        "你必须严格遵守指定的操作生成规则和输出格式。"
    )
    user_content = f"""
请分析以下 C++ 函数，并模仿我提供的【格式范例】，生成尽可能多的该函数的蜕变关系。
待分析代码 ({file_name}):
{code_content}
【生成步骤】
1、为给定函数中每一个可被变换的参数，都生成尽可能多的多个包含多种不同原理变换操作的描述，且操作都只涉及一个对象，长度参数除外。
2、根据这些变换操作，找出尽可能多的该函数的蜕变关系描述（Os表示初始输出和Of表示后续输出），每个操作可能不含蜕变关系，也可能涉及多个蜕变关系。
3、根据下方的生成格式要求，生成对应的结果。
【核心任务：操作生成规则】
在生成 MR 之前，请严格按照以下逻辑思考如何对参数进行变换：
1.  **参数分析与分类**:
    *   识别长度控制参数（如 size, len, n, count）。**严禁**对这些长度参数本身进行修改操作。
    *   仅对**非长度控制参数**（如数组内容、数值变量）生成变换操作。
2.  **操作多样性要求 (Maximize Diversity)**:
    为每个可修改参数生成尽可能多的不同原理的操作，必须覆盖以下类别：
    *   **数学变换**：必须包含加、减、乘、除（如「所有元素加1」、「乘以0.5」）。涉及数值时，必须给出具体值或用k之类的替代。
    *   **顺序/位置变换**（针对数组）：反转、排序（升序/降序）、随机打乱、循环移位。
    *   **特殊值注入**：设置为全0、全1、设置特定元素为最大值/最小值。
    *   **数组/子数组操作**：如果返回类型允许，可尝试修改部分元素。
    *   **注意**：对于返回类型为数组的函数，除了“添加/移除一个元素”外，**避免**生成剧烈改变数组长度的操作（如截取一半、自我复制），以免破坏内存关系。
3.  **严格禁忌**:
    *   **禁止跨参数操作**：一个操作只能修改一个参数（例如：不能同时修改 a 和 b）。
    *   **禁止位操作**：不要生成“位与”、“位或”操作。
    *   **禁止模糊操作**：不要使用“添加噪声”等模糊描述，必须精确（如“加0.01”）。
    *   **内存安全**：操作描述隐含的逻辑必须符合 C++ 内存安全（如索引不越界）。
【生成格式要求】（必须严格遵守，用于脚本解析）
1.  **句式模板**：每一条 MR 必须严格使用以下固定句式，标点符号不得更改：
    "MR ：对于初始输入Ts中包含[变量名]（[变量类型]）的函数，若对 [变量名]执行「[操作描述]」操作得到新输入Tf，则函数的初始输出Os和后续输出Of应满足以下关系："
2.  **关键符号**：
    *   使用 **全角冒号** (：) 在 "MR" 之后。
    *   操作描述必须包裹在 **中文直角引号** (「 和 」) 之中。
    *   操作描述必须清晰无歧义，例如「所有元素加2」。
3.  **数学关系独立成行**：描述句结束后的下一行，必须且只能是包含 Os 和 Of 的数学关系表达式（如 Os == Of, Os < Of, 2 * Os == Of），不要加任何备注， 且不包括Os != Of。
4.  **分隔符**：每条 MR 之间使用虚线 (----------------------------------------) 分隔。
【格式范例】
{EXAMPLE_TEMPLATE}
请根据上述【操作生成规则】思考，并按照【生成格式要求】输出结果。不要输出 Markdown 标记。
请开始生成：
"""
    try:
        response = client.chat.completions.create(
            model="deepseek-chat",
            messages=[
                {"role": "system", "content": system_prompt},
                {"role": "user", "content": user_content},
            ],
            stream=False
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
你现在是一位资深的 C++ 软件测试与自动化生成专家。你的任务是基于我提供的上下文，为一个自动化蜕变测试（Metamorphic Testing）框架生成两个核心的 C++ 调度函数。
【输入上下文信息】
1、待测函数的 C++ 源码：
{code_info}
2、蜕变关系（Metamorphic Relation, MR）的规则描述：
{mr_info}
3、已定义的 TestCase 结构体（用于存放初始测试用例数组）：
{testcase_struct}
【任务目标】
为了配合固定的 main() 批量测试框架，请严格按照【信息2】的 MR 规则，生成以下两个函数：
1. `TestCase change(TestCase tc)`：基于初始输入构造衍生输入。
2. `int check(TestCase tc)`：执行测试、验证蜕变关系，并清理资源。
【编码规范与约束】
1. 用例复用原则：在 change() 函数中处理 TestCase 时，复用原有结构体中的数据和关联状态,基于传入的对象基础进行必要的字段覆盖。
2. 在 `check()` 中验证 Os 和 Of 时，需要判断两者关系是否符合对应的关系描述。若 Os 或 Of 为浮点类型（如 double、float），禁止直接使用 == 或 != 判断相等，应基于绝对误差或相对误差（如 std::abs(a - b) < 1e-8）进行比较；对于大小关系（>、<、>=、<=），也应当考虑容差（例如 a > b 应改写为 a - b > 1e-8 以避免接近相等时的误判）
3. 如果 `change()` 函数内部或提取参数时使用了 `new` 或 `malloc` 分配动态内存，必须在 `check()` 函数返回前（包括 return 1 和 return 0 之前）正确释放（`delete`/`free`）。
【函数模板与工作流参考,不需要完全相同】
// 1. 衍生输入构造函数
TestCase change(TestCase tc) {{
    TestCase tf = tc; 
    // 根据【信息2】的 MR 规则，修改 tf 的内部字段，构造衍生输入 Tf
    // tf.xxx = ... 
    return tf;
}}
// 2. 验证函数
int check(TestCase tc) {{
    // (1) 提取初始输入 (Ts)
    // auto Ts = tc.xxx;
    // (2) 调用【信息1】的待测函数，获取初始输出 (Os)
    // auto Os = target_function(Ts);
    // (3) 调用 change 函数，构造衍生用例对象
    TestCase Tf_case = change(tc);
    // (4) 提取衍生输入并获取衍生输出 (Of)
    // auto Of = target_function(Tf_case.xxx);
    // (5) 根据【信息2】验证 Os 和 Of 是否满足蜕变关系
    int is_valid = 0;
    if ( /* 验证 Os 和 Of 是否满足 MR 逻辑 */ ) {{
        is_valid = 1;
    }}
    // (6) 释放 Tf_case 或其他过程中产生的动态内存
    // (7) 返回验证结果
    return is_valid;
}}
【输出要求】
1. 不要输出任何解释性文字、分析过程或 markdown 代码块的包裹（不要输出 ```cpp 和 ```）。
2. 只允许输出纯文本的 C++ 代码。
3. 严格遵循以下排版格式输出：
[change()函数的完整代码]
---------------------------
[check()函数的完整代码]
"""
    try:
        response = client.chat.completions.create(
            model="deepseek-chat",
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
    code_info = """int* array_copy(int a[], int n) {
    if (a == NULL || n <= 0) {
        return NULL;
    }
    int* copy = (int*)malloc(n * sizeof(int));
    if (copy == NULL) {
        return NULL;  
    }
    for (int i = 0; i < n; i++) {
        copy[i] = a[i];
    }
    return copy;
}
"""
    mr_info = """[Operation]
MR ：对于初始输入Ts中包含a（int*）的函数，若对 a执行「所有元素乘以m（m为非零整数）」操作得到新输入Tf，则函数的初始输出Os和后续输出Of应满足以下关系：
[Invariant]
Os[i] * m == Of[i]
"""
    testcase = """typedef struct {
    int* a; int n;
} TestCase;"""
    change_code, check_code = gene_change_check(code_info,mr_info,testcase)
    print(f"change_code:{change_code}")
    print(f"check_code:{check_code}")
