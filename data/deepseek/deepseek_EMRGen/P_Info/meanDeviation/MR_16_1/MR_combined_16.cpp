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


double meanDeviation(double elements[], double mean, int n) {
    int size = n;
    double sum = 0;
    for (int i = size; --i >= 0; ) {
        sum += fabs(elements[i] - mean);
    }
    return sum / size;
}


typedef struct {
    double* elements; double mean; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0, 2.0, 3.0}, 2.0, 3},
    {(double[]){1.0, 2.0, 3.0}, 1.0, 3},
    {(double[]){1.0, 2.0, 3.0}, 3.0, 3},
    {(double[]){-1.0, 0.0, 1.0}, 0.0, 3},
    {(double[]){-5.0, 0.0, 5.0}, 0.0, 3},
    {(double[]){10.0, 20.0, 30.0}, 20.0, 3},
    {(double[]){2.5, 3.5, 4.5}, 3.5, 3},
    {(double[]){0.0}, 0.0, 1},
    {(double[]){100.0}, 100.0, 1},
    {(double[]){1.1, 2.2, 3.3, 4.4}, 2.75, 4},
    {(double[]){-2.5, -1.5, -0.5, 0.5, 1.5}, -0.5, 5},
    {(double[]){0.0, 0.0, 0.0, 0.0}, 0.0, 4},
    {(double[]){1.0, 1.0, 1.0, 1.0}, 1.0, 4},
    {(double[]){-10.0, -5.0, 0.0, 5.0, 10.0}, 0.0, 5},
    {(double[]){3.14, 6.28, 9.42}, 6.28, 3},
    {(double[]){0.001, 0.002, 0.003}, 0.002, 3},
    {(double[]){-0.001, -0.002, -0.003}, -0.002, 3},
    {(double[]){1.0, 2.0, 3.0, 4.0, 5.0, 6.0}, 3.5, 6},
    {(double[]){-3.0, -2.0, -1.0, 0.0, 1.0, 2.0, 3.0}, 0.0, 7},
    {(double[]){1.5}, 2.0, 1},
    {(double[]){10.0, 20.0, 30.0, 40.0}, 25.0, 4},
    {(double[]){-100.0, 0.0, 100.0}, 0.0, 3},
    {(double[]){7.0, 7.0, 7.0, 7.0, 7.0}, 7.0, 5},
    {(double[]){2.0, 4.0, 6.0, 8.0}, 5.0, 4},
    {(double[]){-1.0, -2.0, -3.0, -4.0}, -2.5, 4},
    {(double[]){0.1, 0.2, 0.3, 0.4, 0.5}, 0.3, 5},
    {(double[]){-0.1, -0.2, -0.3, -0.4, -0.5}, -0.3, 5},
    {(double[]){1.0, 3.0, 5.0, 7.0, 9.0}, 5.0, 5},
    {(double[]){2.0, 2.0, 2.0}, 2.0, 3},
    {(double[]){1.0, 2.0, 3.0, 4.0}, 2.5, 4}
};
int num_test_cases = 30;


    typedef struct {
        double result1;
        double result2;
        double** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z16Change(TestCase t1) {
    TestCase follow_case = t1;
    // --- 这是根据规则4生成的内存处理代码 ---
    double* follow_case_elements = (double*)malloc(t1.n * sizeof(double));
    memcpy(follow_case_elements, t1.elements, t1.n * sizeof(double));
    follow_case.elements = follow_case_elements;
    // ------------------------------------

    // 这是根据规则6a生成的防御性代码，防止n<1时出错
    if (follow_case.n > 0) {
        // 这是根据规则5生成的具体操作代码
        int random_index = rand() % follow_case.n;
        follow_case.elements[random_index] = INFINITY;
    }

    return follow_case;
}

#include <cmath>
#include <cfloat>

int z16check(double result1, double result2) {
    // 1. 防御性编程 (针对浮点数)
    // 检查 NaN
    if (std::isnan(result1) || std::isnan(result2)) return 0;
    
    // 2. 核心判断逻辑 (标量直接比较)
    // 处理无穷大情况（动态容差对无穷大无效）
    if (std::isinf(result1) || std::isinf(result2)) {
        // 直接数学比较
        if (result1 < result2) return 1;
        else return 0;
    }
    
    // 3. 浮点数比较的特殊处理
    // 第一步：定义基础容差
    double epsilon = 1e-5;
    
    // 第二步：提取左右操作数（已移项为 result1 < result2）
    double A = result1;
    double B = result2;
    
    // 第三步：计算动态宽容度
    double tol = epsilon * fmax(1.0, fmax(fabs(A), fabs(B)));
    
    // 第四步：带容差的比较判定
    // 条件：A < B
    // 违反条件：A >= B - tol
    if (A >= B - tol) {
        return 0;
    }
    
    // 5. 满足条件，返回 1
    return 1;
}

TestResult z16runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z16Change(test_cases[test_case_id]);
    // 原始调用
    double source = meanDeviation(test_cases[test_case_id].elements, test_cases[test_case_id].mean, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    double follow = meanDeviation(follow_case.elements, follow_case.mean, follow_case.n);
    
    double** memory_list = (double**)malloc(1 * sizeof(double*));
    memory_list[0] = follow_case.elements;
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z16check(source, follow);
    test_result.status = status;
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z16runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}