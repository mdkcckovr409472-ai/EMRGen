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


double product(double elements[], int n) {
    int size = n;
    double product = 1;
    for (int i = size; --i >= 0; ) {
        product *= elements[i];
    }
    return product;
}


typedef struct {
    double* elements; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0, 2.0, 3.0}, 3},
    {(double[]){2.5, 4.0}, 2},
    {(double[]){-1.0, 5.0}, 2},
    {(double[]){0.0, 10.0, 20.0}, 3},
    {(double[]){0.5, 0.5, 0.5}, 3},
    {(double[]){-2.0, -3.0, -4.0}, 3},
    {(double[]){100.0}, 1},
    {(double[]){-1.0, -1.0, -1.0, -1.0}, 4},
    {(double[]){1.1, 2.2}, 2},
    {(double[]){3.14, 2.71}, 2},
    {(double[]){10.0, 0.1}, 2},
    {(double[]){-5.5, 2.0}, 2},
    {(double[]){1.0, 1.0, 1.0, 1.0, 1.0}, 5},
    {(double[]){2.0, 0.5}, 2},
    {(double[]){-10.0, 0.5}, 2},
    {(double[]){4.0, 2.5, 1.6}, 3},
    {(double[]){0.25, 4.0}, 2},
    {(double[]){-0.5, -2.0}, 2},
    {(double[]){7.5, 2.0, 1.0}, 3},
    {(double[]){0.0, 0.0, 5.0}, 3},
    {(double[]){1.5, -1.5}, 2},
    {(double[]){8.0, 0.125}, 2},
    {(double[]){6.0, 1.5, 2.0}, 3},
    {(double[]){-3.0, -0.333333}, 2},
    {(double[]){9.0, 0.0, 3.0}, 3},
    {(double[]){0.2, 0.2, 0.2, 0.2, 0.2}, 5},
    {(double[]){12.0, 0.25}, 2},
    {(double[]){-1.0, 1.0, -1.0}, 3},
    {(double[]){15.0, 2.0, 0.5}, 3},
    {(double[]){1.0}, 1}
};
int num_test_cases = 30;


    typedef struct {
        double result1;
        double result2;
        double** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z7Change(TestCase t1) {
    TestCase follow_case = t1;
    // --- 这是根据规则4生成的内存处理代码 ---
    double* follow_case_elements = (double*)malloc(t1.n * sizeof(double));
    memcpy(follow_case_elements, t1.elements, t1.n * sizeof(double));
    follow_case.elements = follow_case_elements;
    // ------------------------------------

    // 这是根据规则6a生成的防御性代码，防止n<=0时出错
    if (follow_case.n > 0) {
        // 这是根据规则5生成的具体操作代码
        for (int i = 0; i < follow_case.n; i++) {
            follow_case.elements[i] = follow_case.elements[i] * follow_case.elements[i];
        }
    }

    return follow_case;}

#include <cmath>
#include <cstddef>

int z7check(double result1, double result2) {
    // 1. 核心判断逻辑 (标量直接比较)
    // 条件: return.result2 == return.result1**2
    // 移项后: result2 == result1 * result1

    // 提取移项后的操作数
    double A = result2;
    double B = result1 * result1;

    // 防御 NaN
    if (std::isnan(A) || std::isnan(B)) return 0;

    // 处理无穷大 (动态容差对Inf无效)
    if (std::isinf(A) || std::isinf(B)) {
        // 退化为数学上的直接比较
        if (A == B) return 1;
        else return 0;
    }

    // 定义基础容差
    const double epsilon = 1e-5;
    // 计算动态宽容度
    double tol = epsilon * std::fmax(1.0, std::fmax(std::fabs(A), std::fabs(B)));

    // 带容差的相等判定 (若违反则 return 0)
    if (std::fabs(A - B) > tol) {
        return 0;
    }

    // 2. 满足条件，返回 1
    return 1;
}

TestResult z7runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z7Change(test_cases[test_case_id]);
    // 原始调用
    double source = product(test_cases[test_case_id].elements, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    double follow = product(follow_case.elements, follow_case.n);
    
    double** memory_list = (double**)malloc(1 * sizeof(double*));
    memory_list[0] = follow_case.elements;
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z7check(source, follow);
    test_result.status = status;
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z7runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}