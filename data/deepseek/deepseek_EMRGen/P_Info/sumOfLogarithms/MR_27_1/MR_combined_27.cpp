#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cmath>
#include <climits>
#include <cfloat>
#include <cctype>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;


double sumOfLogarithms(double elements[], int n) {
    double logsum = 0;
    for(int i = 0; i < n; i++) {
        logsum += log(elements[i]);
    }
    return logsum;
}


typedef struct {
    double* elements; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0, 2.0, 3.0}, 3},
    {(double[]){2.718281828459045, 7.38905609893065}, 2},
    {(double[]){0.5, 0.25, 0.125}, 3},
    {(double[]){10.0, 100.0, 1000.0}, 3},
    {(double[]){1.0}, 1},
    {(double[]){1.0, 1.0, 1.0, 1.0, 1.0}, 5},
    {(double[]){1.5, 2.5, 3.5}, 3},
    {(double[]){0.36787944117144233, 1.0, 2.718281828459045}, 3},
    {(double[]){4.0, 9.0, 16.0, 25.0}, 4},
    {(double[]){0.1, 0.01, 0.001}, 3},
    {(double[]){1.0, 2.0, 4.0, 8.0, 16.0}, 5},
    {(double[]){0.2, 0.4, 0.6, 0.8}, 4},
    {(double[]){3.0, 6.0, 9.0}, 3},
    {(double[]){1.1, 2.2, 3.3, 4.4, 5.5}, 5},
    {(double[]){0.75, 1.5, 3.0}, 3},
    {(double[]){5.0, 25.0, 125.0}, 3},
    {(double[]){0.9, 0.99, 0.999}, 3},
    {(double[]){1.25, 1.5, 1.75, 2.0}, 4},
    {(double[]){2.0, 4.0, 8.0, 16.0, 32.0}, 5},
    {(double[]){0.3333333333333333, 0.6666666666666666}, 2},
    {(double[]){6.0, 12.0, 18.0, 24.0}, 4},
    {(double[]){1.01, 1.02, 1.03}, 3},
    {(double[]){0.8, 1.6, 3.2}, 3},
    {(double[]){1.0, 10.0, 100.0, 1000.0, 10000.0}, 5},
    {(double[]){0.125, 0.25, 0.5, 1.0, 2.0}, 5},
    {(double[]){1.2, 1.44, 1.728}, 3},
    {(double[]){0.99, 1.0, 1.01}, 3},
    {(double[]){2.5, 6.25, 15.625}, 3},
    {(double[]){0.3, 0.6, 0.9, 1.2}, 4},
    {(double[]){1.0, 1.5, 2.0, 2.5, 3.0, 3.5}, 6}
};
int num_test_cases = 30;


    typedef struct {
        double result1;
        double result2;
        double** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z27Change(TestCase t1) {
    TestCase follow_case = t1;
    // --- 这是根据规则4生成的内存处理代码 ---
    double* follow_case_elements = (double*)malloc(t1.n * sizeof(double));
    memcpy(follow_case_elements, t1.elements, t1.n * sizeof(double));
    follow_case.elements = follow_case_elements;
    // ------------------------------------
    
    // 这是根据规则6a生成的防御性代码，防止n<=0时出错
    if (follow_case.n <= 0) {
        // 数组为空或长度无效，直接返回副本
        return follow_case;
    }
    
    // 这是根据规则5生成的具体操作代码
    // 1. 找到最小值
    double min_val = follow_case.elements[0];
    for (int i = 1; i < follow_case.n; i++) {
        if (follow_case.elements[i] < min_val) {
            min_val = follow_case.elements[i];
        }
    }
    
    // 2. 生成随机位置
    srand(time(NULL)); // 初始化随机种子
    int random_index = rand() % follow_case.n; // 生成[0, n-1]的随机索引
    
    // 3. 将随机位置的元素置为最小值
    follow_case.elements[random_index] = min_val;
    
    return follow_case;
}

#include <cmath>
#include <cstddef>

int z27check(double result1, double result2) {
    // 1. 核心判断逻辑 (标量直接比较)
    // 条件为 result1 >= result2
    // 对于浮点数，必须进行带容差的比较

    // 第一步：定义基础容差
    const double epsilon = 1e-5;

    // 第二步：提取左右操作数 A 和 B（代数移项）
    // 条件 result1 >= result2 已经是标准形式
    double A = result1;
    double B = result2;

    // 第三步：防御 NaN，并对 Inf 进行特殊处理
    if (std::isnan(A) || std::isnan(B)) return 0;
    
    if (std::isinf(A) || std::isinf(B)) {
        // 出现无穷大，退化为数学上的直接比较
        if (A >= B) return 1;
        else return 0;
    }

    // 第四步：计算动态宽容度
    double tol = epsilon * fmax(1.0, fmax(fabs(A), fabs(B)));

    // 第五步：带容差的比较判定
    // 条件为 A >= B，违反条件是 A < B - tol
    if (A < B - tol) {
        return 0;
    }

    // 2. 满足条件，返回 1
    return 1;
}

TestResult z27runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z27Change(test_cases[test_case_id]);
    // 原始调用
    double source = sumOfLogarithms(test_cases[test_case_id].elements, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    double follow = sumOfLogarithms(follow_case.elements, follow_case.n);
    
    double** memory_list = (double**)malloc(1 * sizeof(double*));
    memory_list[0] = follow_case.elements;
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z27check(source, follow);
    test_result.status = status;
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z27runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}