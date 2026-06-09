from openai import OpenAI
import os
import re
import sys,io
import ast
sys.stdin = io.TextIOWrapper(sys.stdin.buffer, encoding='utf-8')
client = OpenAI

def get_operation_llm(function_name, return_type, parameters):
    system_content = f"你是一个严格遵循指令的测试数据修改助手。你的任务是根据用户提供的函数信息，为其中一个参数生成4种不同的修改操作。你必须严格按照用户指定的格式输出，并且只输出一个参数的操作，不多做任何解释。"
    user_content = (f"""你的任务是为给定函数中**每一个可被修改的参数**，都生成一行包含多种不同原理变换操作的描述。
**函数上下文:**
• 函数名: {function_name}
• 返回类型: {return_type}
• 完整参数列表: {parameters}
**核心任务与规则:**
1.  **参数分析与分类 (首要任务)**:
    a) 你的第一个任务是**分析完整的参数列表 (`{parameters}`)**，并根据命名习惯（如 `size`, `len`, `n`, `count`）、数据类型（通常为整型）以及与其它参数（如数组）的关联性，**自行识别**出哪些是用于控制数组或指针长度/大小的参数。
    b) 基于你的分析，将参数分为两类：
       • **可修改参数**: 所有非长度控制器的参数（例如，数组指针、结构体指针、普通数值类型等）。你的操作目标是**所有**这些参数。
       • **禁止修改的参数**: 你识别出的所有长度控制器参数，如size,n,length,count等)。**如果一个整型参数的名称是以上之一(包括，但不限于)，并且函数参数列表中同时存在一个数组或指针类型的参数，那么你必须将其视为长度参数**，并严禁为其生成任何修改操作。
2.  **跨参数操作多样性 (重要)**：当函数有多个可修改的参数时（例如 `arr1` 和 `arr2`），请尽量为它们设计**不同类型**的变换。例如，可以对 `arr1` 应用算术运算（加/乘），而对 `arr2` 应用结构性变换（交换/逆序），以最大化测试的覆盖面。
3.  **单参数内操作多样性**：在为**单个**参数生成操作时（即单行输出内），其自身的多个操作也应原理不同（如：全局操作、位置操作、内容修改等）。
4.  **内存安全强制要求 (尤其针对C/C++代码)**：
   a) 所有数组的索引访问必须有边界检查（例如，使用其关联的长度参数作为循环边界）。
   b) 对于字符串数组（若存在），所有修改必须遵循动态内存管理规则（如使用 `strdup` 创建新字符串，修改前 `free` 旧字符串）。
   c) 基于设计需求，禁止跨参数操作（例如操作参数a时，禁止修改参数b,或是同时修改参数a和b,只能修改a)
   d) 操作名称必须无歧义，必要时用括号注释（如“数组向左循环移位（首元素移到末尾）”）
所有操作必须限定在单个参数内部，避免数据交叉污染。
5.  **输出格式**：为**每一个可修改的参数**生成**一行**输出，格式为 `参数名 | 参数类型 | 操作1 | 操作2 | 操作3 | 操作4`。将所有行一起输出。
   **参数类型说明**:
   - `array[char]`: 字符串数组
   - `array[int]`: 整型数组
   - `array[double]`: 浮点数组
   - `int`, `double` 等: 非数组参数
6.  **对于禁止修改**  输出中不应该包括*禁止修改*，当输出中出现“禁止修改”时，去掉出现禁止修改的这一行。
**示例输出 (关键：展示了如何自行识别并排除长度参数):**
*   假设函数参数为 `(int* data_in, int* data_out, int size, double factor)`。
*   在此场景下，LLM应自行识别出 `size` 是长度参数并禁止修改，因此最终输出仅包含 `data_in`, `data_out`, `factor` 三个参数的变换。
*   注意：禁止修改的长度参数禁止放入最终输出中
*   **最终输出应包含3行**:
    `data_in | array[int] | 所有元素加1 | 随机位置的元素置为-1 | 随机两元素交换位置 | 数组整体右移一位`
    `data_out | array[int] | 所有元素乘以factor | 首位元素置0 | 数组逆序排列 | 随机两位元素交换`
    `factor | double | 乘以2.0 | 减去1.5 | 加上1.0 | 置为2.0`
*   输出中不应该包括*禁止修改*，当输出中出现“禁止修改”时，去掉输出的这一行！！！！
现在，请为函数 `{function_name}` 执行任务。严格按照上述所有规则，首先分析参数列表，然后为**每一个**你识别出的可修改参数生成一行对应的变换操作，并将所有结果一同输出。""")
    response = client.chat.completions.create(
        model="deepseek-chat",
        messages=[
            {"role": "system", "content": system_content},
            {"role": "user", "content": user_content},
        ],
        stream=False
    )
    operations = response.choices[0].message.content
    print(operations)
    structured_operations = []
    for line in operations.splitlines():
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

def get_operation_llm_unnumber(function_name, return_type, parameters):
    system_content = f"你是一个专门为蜕变测试生成输入变换操作的专业助手。你的任务是根据函数参数信息，为每个可修改参数生成尽可能多样化的变换操作。你必须严格按照用户指定的格式输出，不多做任何解释。"
    user_content = (f"""你的任务是为给定函数中**每一个可被变换的参数**，都生成一行包含多种不同原理变换操作的描述。
    **函数上下文:**
    • 函数名: {function_name}
    • 返回类型: {return_type}
    • 完整参数列表: {parameters}
    **核心任务与规则:**
    1.  **参数分析与分类**:
        a) 分析参数列表，识别长度控制参数（如size/len/n/count）
        b) 将参数分为：
           • **可修改参数**：非长度控制器
           • **禁止修改的参数**：长度控制器
    2. **操作数量最大化**：为每个可修改参数生成**尽可能多的高质量的**不同原理的变换操作
    3.  **单参数内操作多样性**：
       a) 操作类型应覆盖：全局操作、位置操作、内容修改、数学变换、逻辑变换、随机扰动、且包括加、减、乘、除操作
       b) 基于设计需求，禁止跨参数操作（例如操作参数a时，禁止修改参数b,或是同时修改参数a和b,只能修改a，但能操作一个数组内的两个数，例如将数组中某个元素的值增加1，同时将另一个元素的值减少1
       c) 数组参数额外增加：排序操作、子数组操作
       d) 数值参数额外增加：类型转换、特殊值注入
       e) 对于返回类型为数组型的，除了向数组添加一个新元素、从数组中移除一个元素操作外，不要涉及让数组长度发生变化的操作（例如数组截取前一半、数组自我复制等）
       f) 避免生成过于专业或跨领域操作
       g) 避免生成添加噪声操作
       h) 避免“位与”、“位或”操作
       i) 涉及具体数值时，明确给出具体值,除非说明是置最大值或置最小值
       j） 设置数值时，必须明确修改大小倾向，例如随机位置元素置为999(当元素小于999时）
    4.  **内存安全强制要求**：
       a) 数组索引必须有边界检查
       b) 字符串数组遵循内存管理规则
       c) 严格禁止跨参数操作
       d) 操作名称必须无歧义，必要时用括号注释（如“数组向左循环移位（首元素移到末尾）”）
    5.  **输出格式**：
       a) 格式：`参数名 | 参数类型 | 操作1 | 操作2 | ... | 操作N`
       b) **生成尽可能多的高质量操作，但操作数量不超过30个**
       c) 禁止修改的参数不输出
    **示例输出：**
    `data_in | array[int] | 所有元素加1 | 随机位置置-1 | 随机两元素交换 | 数组右移 | 数组反转 | 随机重排序 | 清空数组 | 填充随机数 | 元素平方 | 取绝对值 | 添加高斯噪声`
    `factor | double | 乘2.0 | 减1.5 | 加1.0 | 置2.0 | 取倒数 | 平方根 | 正弦变换 | 取整操作 | 随机扰动 | 取绝对值`
    现在，请为函数 `{function_name}` 执行任务。""")
    response = client.chat.completions.create(
        model="deepseek-chat",
        messages=[
            {"role": "system", "content": system_content},
            {"role": "user", "content": user_content},
        ],
        stream=False,
    )
    print(f"{system_content}\n{user_content}")
    operations = response.choices[0].message.content
    print(f"operations:{operations}")
    structured_operations = []
    for line in operations.splitlines():
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
    system_content = f"你是一个严格遵循指令的代码生成助手。你必须严格按照用户指定的格式输出，并且只输出一个参数的操作，不多做任何解释。"
    user_content_int = f"""
    你的任务是基于给定的信息，生成一个完整的、安全且健壮的 C++ 函数，并附带两行用于测试的函数调用代码。生成的代码必须能够处理各种边界情况（如空数组、单元素数组）而不会崩溃。
    输入信息:
    操作ID (id): {id}
    初始函数名 (func_name): {func_name}
    函数返回类型 (return_type): {return_type}
    TestCase结构体 (TestCaseStruct): {testCaseStruct}
    目标参数名称 (parameter_name): {parameter_name}
    目标参数类型 (parameter_type): {parameter_type}
    具体操作描述 (operation): {operation}
    原始函数参数 (parameters): {parameters} (此项仅供理解上下文，函数实现应以TestCaseStruct为准)
    生成规则 (必须严格遵守):
    TestCase 结构体使用:
    你必须直接使用输入信息中提供的 {testCaseStruct} 作为函数上下文的结构体定义。
    函数签名:
    函数名必须为 z{id}Change。
    函数的参数和返回值类型都必须是 TestCase。完整签名为 TestCase z{id}Change(TestCase t1)。
    函数体 - 核心模板:
    函数体必须以 TestCase follow_case = t1; 开始，并以 return follow_case; 结束。
    数组/指针的特殊内存处理 (关键规则):
    条件: 当且仅当 {parameter_type} 是数组类型时执行。
    操作: 使用 malloc 和 memcpy 为 follow_case 中的目标参数创建并填充一个深拷贝。内存大小和循环边界必须使用 TestCase 结构中相应的长度变量，该拷贝操作位于第一行且位于防御性编程和边界检查之外。
    操作代码转换:
    将 {operation}（自然语言描述）转换为具体的 C 语言代码，操作于 follow_case 的副本上。
    防御性编程与边界检查 (最高优先级规则):
    在实现操作代码之前，你必须加入严格的检查来防止运行时错误。这是最重要的规则。
    a) 检查数组长度:
    如果操作至少需要1个元素（例如，循环遍历），则必须添加 if (follow_case.n > 0) 检查。
    如果操作至少需要2个元素（例如，“交换首尾元素”、“构造等差数列”），则必须添加 if (follow_case.n < 2) 检查并在不满足时直接返回。
    b) 避免除以零:
    在任何除法运算前，必须检查分母是否为零。如果分母依赖于数组长度（如 n-1），此检查应由规则6a覆盖。
    c) 保护数学函数域:
    在使用 sqrt() 等函数前，必须检查输入值是否在其合法定义域内（如 x >= 0）。对于无效输入，应跳过该元素的变换。
    d) 内存安全 - 禁止非法free:
    在 z...Change 函数内部，严禁调用 free() 来释放传入的参数 t1 或其成员（如 t1.a）。free() 只能在测试框架（如 runTest 函数）中用于释放 z...Change 函数 新分配 的内存。
    e) 在编写z{id}Change时,对于malloc操作,需要完整复制整个数组,避免只复制部分数组.
    函数调用字符串生成:
    在生成完整的 C++ 函数之后，你必须额外生成两行 C++ 代码字符串。
    这两行代码应放在主 C 函数代码块的外部，并用注释标题 // --- 生成的函数调用字符串 --- 分隔。
    第一行 (原始调用):
    格式: {type} source = {func_name}(...); // MODIFIED: Explicit type
    参数列表: 严格按照 {parameters} 的顺序和名称构建，且每个参数都必须以 test_cases[test_case_id]. 为前缀。{type} 为函数对应的返回类型。
    第二行 (变换后调用):
    格式: {type} follow = {func_name}(...);
    参数列表: 同样严格按照 {parameters} 的顺序和名称构建，但每个参数都必须以 follow_case. 为前缀。{type} 为函数对应的返回类型。
    示例：
    输入信息:
    id: 14
    func_name: add_values
    TestCaseStruct: typedef struct {{ int* a; int n; }} TestCase;
    parameter_name: a
    parameter_type: array[int]
    operation: 构造一个等差数列
    parameters: (int a[], int n)
    预期输出 (完整代码):
    TestCase z14Change(TestCase t1) {{
    TestCase follow_case = t1;
    // --- 这是根据规则4生成的内存处理代码 ---
    int* follow_case_a = (int*)malloc(t1.n * sizeof(int));
    memcpy(follow_case_a, t1.a, t1.n * sizeof(int));
    follow_case.a = follow_case_a;
    // ------------------------------------
    // 这是根据规则6a生成的防御性代码，防止n<2时出错
    if (follow_case.n < 2) {{
        // 元素不足2个，无法构成数列，直接返回副本
        return follow_case;
    }}
    // 这是根据规则5生成的具体操作代码
    int first = follow_case.a[0];
    int last = follow_case.a[follow_case.n - 1];
    // 除法分母(n-1)已由n>=2保证不为零
    int diff = (last - first) / (follow_case.n - 1);
    for (int i = 0; i < follow_case.n; i++) {{
    follow_case.a[i] = first + i * diff;
    }}
    return follow_case;}}
    // --- 生成的函数调用字符串 ---
    int source = add_values(test_cases[test_case_id].a, test_cases[test_case_id].n); // MODIFIED: Explicit type
    int follow = add_values(follow_case.a, follow_case.n);
    """
    user_content = user_content_int
    response = client.chat.completions.create(
        model="deepseek-chat",
        messages=[
            {"role": "system", "content": system_content},
            {"role": "user", "content": user_content},
        ],
        stream=False
    )
    get_content = response.choices[0].message.content
    separator = "// --- 生成的函数调用字符串 ---"
    parts = get_content.split(separator)
    function_code = ""
    call_string_1 = ""
    call_string_2 = ""
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
    return code_res

def check_code(data_type,id,is_array,invariant_condition):
    user_content = f"""
    你的任务是基于给定的信息，生成一个完整的、安全且健壮的 C/C++ 验证函数。该函数接受两个表示运行结果的参数，并检查它们是否满足特定的条件不变式。如果条件完全满足，函数返回 1；只要存在任何违反条件的情况，函数返回 0。
    输入信息:
    操作ID (id): {id}
    数据类型 (data_type): {data_type}
    是否为数组 (is_array): {is_array} 
    条件不变式 (invariant_condition): {invariant_condition}
    =========================================
    生成模板：
    [当 {is_array} 为 1 时]
    int z{id}check({data_type} result1, {data_type} result2, int n) {{
        // 1. 防御性编程 (空指针与长度检查)
        if (result1 == NULL || result2 == NULL) return 0;
        if (n <= 0) return 1;
        // 2. 核心判断逻辑 (elementwise)
        for (int i = 0; i < n; i++) {{
        if (!( /* 判断 result1[i] 和 result2[i] 满足 {{invariant_condition}} */ )) {{
        return 0; // 一旦违反条件，立即返回 0
        }}
        }}
        // 3. 全部满足，返回 1
    return 1;
    }}
    [当 {is_array} 为 0 时]
    int z{id}check({data_type} result1, {data_type} result2) {{
    // 1. 核心判断逻辑 (标量直接比较)
    if (!( /* 判断 result1 和 result2 满足 {invariant_condition} */ )) {{
    return 0;
    }}
    // 2. 满足条件，返回 1
    return 1;
    }}
    生成规则 (必须严格遵守):
    1. 函数签名与参数动态生成:
       - 函数名必须命名为：z{id}check。
       - 返回值类型必须为：int（1代表满足，0代表不满足）。
       - 长度参数名默认为 n 。
       - 参数列表必须根据 {is_array} 的值动态决定：
         * 如果 {is_array} 为 1（或 data_type 带有 '*'）：函数必须接受三个参数。前两个参数类型为 {data_type}，分别命名为 result1 和 result2；第三个参数类型为 int，命名为 n。
           (示例: int z{id}check(int* result1, int* result2, int n))
         * 如果 {is_array} 为 0：函数仅接受两个参数。类型均为 {data_type}，分别命名为 result1 和 result2。
           (示例: int z{id}check(double result1, double result2))
    2. 逻辑验证实现规则:
       - invariant_condition若为“return.result1 < return.result2”这种格式，将其视为“result1 < result2”
       - 标量比较逻辑 (非数组): 直接根据 {invariant_condition} 比较 result1 和 result2。如果不满足则 `return 0;`。
       - 数组比较逻辑 (elementwise): 
         * 检查 {invariant_condition} 中是否包含数组切片标识（如 `[a..b]`）。
         * 【全数组比较】：如果没有切片标识，或者明确需要比较整个数组，使用标准循环 `for (int i = 0; i < n; i++)`。
         * 【局部切片比较 (关键)】：如果包含 `[a..b]`（例如 `result1[][0..0] == result2[][0..0]`），**绝对禁止盲目使用 `i < n` 作为循环边界！** 
           -> 如果 a 和 b 相等（如 `[0..0]`），**不要使用 for 循环**，直接对该具体索引进行单次判断（例如直接写 `if (!(result1[0] == result2[0])) return 0;`）。
           -> 如果 a 和 b 不相等（如 `[0..2]`），则根据提取出的边界生成循环：`for (int i = a; i <= b; i++)`。
         * 在循环内部（或单次判断中），逐对比较 result1 和 result2 是否满足 {invariant_condition}。
         * 一旦发现**任何一对**元素不满足条件，必须立即退出并 `return 0;` (短路求值)。
       - 字典序比较逻辑 (Lexical - 针对包含 "(lexically)" 的条件):
         * 若 {invariant_condition} 中包含 (lexically)，绝对不能使用 elementwise 的逐元素判断模板！
         * 必须实现标准字典序逻辑：从 0 到 n-1 遍历。遇到**第一个不相等的元素对**时（浮点数需考虑规则3的误差），直接根据这**一对**元素的大小关系决定最终结果并立即 return（例如：若要求 <= 且 result1[i] < result2[i]，立即 return 1；若 result1[i] > result2[i]，立即 return 0）。
         * 警告：只要发现第一个不相等的元素并得出结果，绝对不要再检查后续任何元素！
         * 如果循环结束都没发现不相等的元素（即两数组完全相等），若条件允许相等（如 <=），return 1；若严格不等（如 <），return 0。
       - 如果所有检查都通过（或循环正常结束），在函数末尾 `return 1;`。
    3. 浮点数比较的特殊处理 (动态容差与无穷大处理):
   如果 {data_type} 包含 float 或 double，必须严格遵守以下流程，绝对禁止直接使用 ==, <, > 比较常规浮点数：
   第一步：定义基础容差 `double epsilon = 1e-5;`
   第二步：提取左右操作数 A 和 B（**强制要求代数移项，恢复数据量级！**）
   如果 {invariant_condition} 的形式是把所有变量都放在了比较符的一侧（例如 `表达式 - 表达式 == 0` 或 `表达式 <= 0`），**绝对不能**令 B = 0！因为这会丢失大浮点数原本的巨大化量级，导致容差计算错误。
   你必须在数学上将等式（或不等式）两边移项，使得 `result1` 和 `result2` 分布在比较符（==, <, >, <=, >=）的两侧，从而恢复它们真实的量级。
   - 【错误示范】：条件 `3.0 * result1 - result2 == 0`，提取 A = 3.0 * result1 - result2; B = 0.0; （绝对禁止！）
   - 【正确示范】：条件 `3.0 * result1 - result2 == 0`，必须在脑内移项为 `3.0 * result1 == result2`。从而提取：`double A = 3.0 * result1; double B = result2;`
   - 【正确示范】：条件 `result1 - result2 <= 0`，必须移项为 `result1 <= result2`。从而提取：`double A = result1; double B = result2;`
   第三步：防御 NaN，并对 Inf 进行特殊放行
   在提取出 A 和 B 之后，必须加入以下逻辑：
       `if (std::isnan(A) || std::isnan(B)) return 0;`
       `// 如果出现无穷大，动态容差会失效(Inf-Inf=NaN)，此时应退化为数学上的直接比较`
       `if (std::isinf(A) || std::isinf(B)) {{`
        `    if ( /* 根据移项后的 {invariant_condition} 直接使用 <, >, == 等符号比较 A 和 B */ ) return 1;`
    `    else return 0;`
    `}}`
    第四步：计算动态宽容度 (Dynamic Tolerance)
    `double tol = epsilon * fmax(1.0, fmax(fabs(A), fabs(B)));`
    第五步：带容差的比较判定 (若违反则 return 0)
    注意：必须根据**移项后**的比较运算符进行判定！
    - 如果移项后的条件是相等 (`==`)：若 `fabs(A - B) > tol`，则 `return 0;`
    - 如果移项后的条件是 (`<=`)：若 `A > B + tol`，则 `return 0;`
    - 如果移项后的条件是 (`>=`)：若 `A < B - tol`，则 `return 0;`
    - 如果移项后的条件是 (`<`)：若 `A >= B - tol`，则 `return 0;`
    - 如果移项后的条件是 (`>`)：若 `A <= B + tol`，则 `return 0;`
    4. 防御性编程与边界检查 (最高优先级):
       在执行任何核心逻辑之前，必须加入以下安全检查：
       a) 空指针检查: 如果 {is_array} 为 1，必须首先检查指针：`if (result1 == NULL || result2 == NULL) return 0;`
       b) 长度合法性检查: 如果 {is_array} 为 1，必须检查长度：`if (n <= 0) return 1;`（空数组默认不违反条件，视为满足）。
    5. 代码纯净度:
       请只输出纯 C/C++ 代码，不要包含任何 markdown 解释，不要写 main 函数，只输出 `z{id}check` 的函数实现。"""
    response = client.chat.completions.create(
        model="deepseek-chat",
        messages=[
            {"role": "system", "content": ""},
            {"role": "user", "content": user_content},
        ],
        stream=False
    )
    get_content = response.choices[0].message.content
    match = re.search(r'```[a-zA-Z]*\s*(.*?)```', get_content, re.DOTALL)
    if match:
        get_content = match.group(1).strip()
    else:
        get_content = get_content.strip()
    return get_content

def get_input_data(function, num):
    system_content = "你是一位资深的C++测试工程师，擅长编写高覆盖率、鲁棒性强的单元测试。你的任务是为给定的C++目标函数生成一组输入测试用例。你必须严格按照用户指定的格式输出，不多做任何解释。"
    separator = "//__SPLIT__"
    user_content = f"""
    我将提供一个C++函数的源码。你需要分析该函数的参数签名，并为两个部分生成数据。
    # Goal
    生成 {num} 个具有代表性的测试用例。数据应包含：
    1. **基础用例**：典型的输入数据，验证函数基本功能。
    2. 为了函数能正常运行，禁止生成极端值。
    3. 数组内值之间禁止有什么规律,如递增、递减（函数功能性质有要求除外）
    4. 确保数值多样性：对于数值数组（尤其是 double），数值必须覆盖较大的范围，**不要**限制在 [-10, 10] 之间。明确包含十、百、千数量级的数值（例如 42.5、-150.2、300.0）。
    5. 当有多个数组时,数组长度优先相同,函数有特殊要求除外
    # Output Format Constraints (必须严格遵守)
    请输出两部分内容，中间用 `{separator}` 隔开。
    **第一部分：结构体成员定义列表**
    - **每一行**定义一个成员变量，格式为 `类型 变量名;`。
    - **关键规则**：如果函数参数是数组（例如 `int a[]` 或 `int a[10]`），在结构体中**必须**定义为指针（例如 `int* a;`）。
    - **绝不要**在结构体成员中使用 `[]`。
    - 示例：`int a[]` -> `int* a;`
    **第二部分：测试用例初始化列表**
    - **不需要** `TestCase test_cases[] =` 外壳。
    - **每一行**代表一个测试用例的数据。
    - 格式为：`{{ 参数1数值, 参数2数值, ... }},` 
    - 数组/指针参数必须使用复合字面量，例如 `(int[]){{1, 2, 3}}`。
    - **每一行末尾必须加逗号**。
    # Example (Reference only)
    **Input Function:**
    int func(int* arr, int n);
    **Output:**
    int* arr;
    int n;
    {separator}
    {{(int[]){{1, 2, 3}}, 3}},
    {{(int[]){{}}, 0}},
    {{(int[]){{-5, 100}}, 2}},
    # Target Task
    **Input Function:**
    {function}
    """
    response = client.chat.completions.create(
        model="deepseek-chat",
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
        part1_str = parts[0].strip()
        part2_str = parts[1].strip()
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

def get_operation_input(function_name, return_type, parameters, array_info_first):
    print(f"function_name:{function_name}")
    print(f"return_type:{return_type}")
    print(f"parameters:{parameters}")
    print(f"array_info_first:{array_info_first}")
    print("输入操作(空格分割):")
    item = input()                               
    item_list = item.split()         
    print(f"item_list:{item_list}")
    return item
