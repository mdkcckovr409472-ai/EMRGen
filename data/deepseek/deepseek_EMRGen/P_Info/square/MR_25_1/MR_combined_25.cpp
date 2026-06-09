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


double* square(double data[], int n) {
    double* cp1 = (double*)malloc(n * sizeof(double));
    memcpy(cp1,data,n*sizeof(double));
    for (int i = 0; i < n; i++) {
        cp1[i] = cp1[i] * cp1[i];
    }
    return cp1;
}


typedef struct {
    double* data; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0}, 1},
    {(double[]){2.0, 3.0}, 2},
    {(double[]){0.0}, 1},
    {(double[]){-1.0}, 1},
    {(double[]){-2.0, -3.0}, 2},
    {(double[]){0.5}, 1},
    {(double[]){-0.5}, 1},
    {(double[]){1.5, 2.5}, 2},
    {(double[]){-1.5, -2.5}, 2},
    {(double[]){10.0}, 1},
    {(double[]){-10.0}, 1},
    {(double[]){0.0, 0.0, 0.0}, 3},
    {(double[]){1.0, 0.0, -1.0}, 3},
    {(double[]){2.0, 4.0, 6.0}, 3},
    {(double[]){-2.0, -4.0, -6.0}, 3},
    {(double[]){0.25, 0.75}, 2},
    {(double[]){-0.25, -0.75}, 2},
    {(double[]){100.0, 200.0}, 2},
    {(double[]){-100.0, -200.0}, 2},
    {(double[]){1.0, 2.0, 3.0, 4.0}, 4},
    {(double[]){-1.0, -2.0, -3.0, -4.0}, 4},
    {(double[]){0.1, 0.2, 0.3}, 3},
    {(double[]){-0.1, -0.2, -0.3}, 3},
    {(double[]){5.0}, 1},
    {(double[]){-5.0}, 1},
    {(double[]){1.0, -1.0, 2.0, -2.0}, 4},
    {(double[]){3.14159}, 1},
    {(double[]){-3.14159}, 1},
    {(double[]){1.0, 2.0, 3.0, 4.0, 5.0}, 5},
    {(double[]){-1.0, -2.0, -3.0, -4.0, -5.0}, 5}
};
int num_test_cases = 30;


    typedef struct {
        double* result1;
        double* result2;
        double** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z25Change(TestCase t1) {
    TestCase follow_case = t1;
    // --- 这是根据规则4生成的内存处理代码 ---
    double* follow_case_data = (double*)malloc(t1.n * sizeof(double));
    memcpy(follow_case_data, t1.data, t1.n * sizeof(double));
    follow_case.data = follow_case_data;
    // ------------------------------------

    // 这是根据规则6a生成的防御性代码，防止n<=0时出错
    if (follow_case.n <= 0) {
        // 数组为空或长度为负，无法进行随机位置操作，直接返回副本
        return follow_case;
    }

    // 这是根据规则5生成的具体操作代码
    // 生成一个随机索引
    int random_index = rand() % follow_case.n;
    // 将随机位置的元素置为最大值
    follow_case.data[random_index] = DBL_MAX;

    return follow_case;}

#include <math.h>
#include <stddef.h>

int z25check(double* result1, double* result2, int n) {
    // 1. 防御性编程 (空指针与长度检查)
    if (result1 == NULL || result2 == NULL) return 0;
    if (n <= 0) return 1;

    // 2. 字典序比较逻辑 (lexically)
    double epsilon = 1e-5;
    for (int i = 0; i < n; i++) {
        double A = result1[i];
        double B = result2[i];

        // 防御 NaN
        if (isnan(A) || isnan(B)) return 0;

        // 处理无穷大
        if (isinf(A) || isinf(B)) {
            if (A < B) {
                // 在第一个不相等的元素处，result1[i] < result2[i]，字典序条件成立，立即返回1
                return 1;
            } else if (A > B) {
                // 在第一个不相等的元素处，result1[i] > result2[i]，字典序条件不成立，立即返回0
                return 0;
            }
            // 如果A == B（包括同号无穷大相等），继续循环检查下一个元素
            continue;
        }

        // 计算动态容差
        double tol = epsilon * fmax(1.0, fmax(fabs(A), fabs(B)));

        // 比较当前元素对
        if (fabs(A - B) > tol) {
            // 找到第一个不相等的元素对
            if (A < B - tol) {
                // result1[i] < result2[i]，字典序条件成立，立即返回1
                return 1;
            } else {
                // result1[i] > result2[i]，字典序条件不成立，立即返回0
                return 0;
            }
        }
        // 如果A和B在容差内相等，继续检查下一个元素
    }

    // 3. 循环结束，所有元素在容差内相等
    // 对于严格小于 (<) 的字典序，完全相等意味着条件不满足
    return 0;
}

TestResult z25runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z25Change(test_cases[test_case_id]);
    // 原始调用
    double* source = square(test_cases[test_case_id].data, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    double* follow = square(follow_case.data, follow_case.n);
    
    double** memory_list = (double**)malloc(1 * sizeof(double*));
    memory_list[0] = follow_case.data;
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z25check(source, follow, test_cases[test_case_id].n);
    test_result.status = status;
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z25runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}