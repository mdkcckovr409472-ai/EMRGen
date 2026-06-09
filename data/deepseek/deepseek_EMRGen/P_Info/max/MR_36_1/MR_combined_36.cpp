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


double max(double elements[], int n) {
    int size = n;
    double max = elements[size - 1];
    for (int i = size - 1; --i >= 0; ) {
        if (elements[i] > max) {
            max = elements[i];
        }
    }
    return max;
}


typedef struct {
    double* elements; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0, 2.0, 3.0}, 3},
    {(double[]){3.0, 2.0, 1.0}, 3},
    {(double[]){-1.5, -2.0, -3.0}, 3},
    {(double[]){0.0, 0.0, 0.0}, 3},
    {(double[]){5.5}, 1},
    {(double[]){-10.2, 15.7, 0.0, 3.3}, 4},
    {(double[]){1.1, 1.1, 1.1}, 3},
    {(double[]){2.71828, 3.14159}, 2},
    {(double[]){100.0, 200.0, 150.0}, 3},
    {(double[]){-0.001, 0.001}, 2},
    {(double[]){1.0, 2.0, 3.0, 4.0, 5.0}, 5},
    {(double[]){5.0, 4.0, 3.0, 2.0, 1.0}, 5},
    {(double[]){1.5}, 1},
    {(double[]){-5.0, -1.0, -3.0}, 3},
    {(double[]){10.0, 20.0, 10.0, 20.0}, 4},
    {(double[]){0.1, 0.2, 0.3, 0.4, 0.5}, 5},
    {(double[]){-100.0, -50.0, -75.0}, 3},
    {(double[]){12.34, 56.78}, 2},
    {(double[]){1.0, -1.0, 2.0, -2.0}, 4},
    {(double[]){999.999}, 1},
    {(double[]){2.0, 1.0, 2.0, 1.0, 2.0}, 5},
    {(double[]){0.0, -5.0, 10.0}, 3},
    {(double[]){7.7, 8.8, 9.9, 10.1}, 4},
    {(double[]){-2.5, -1.5, -3.5}, 3},
    {(double[]){1.0, 2.0, 3.0, 2.0, 1.0}, 5},
    {(double[]){0.0}, 1},
    {(double[]){4.4, 5.5, 6.6}, 3},
    {(double[]){-10.0, 0.0, 10.0}, 3},
    {(double[]){1.23, 4.56, 7.89}, 3},
    {(double[]){-0.5, 0.0, 0.5}, 3}
};
int num_test_cases = 30;


    typedef struct {
        double result1;
        double result2;
        double** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z36Change(TestCase t1) {
    TestCase follow_case = t1;
    // --- 这是根据规则4生成的内存处理代码 ---
    double* follow_case_elements = (double*)malloc(t1.n * sizeof(double));
    memcpy(follow_case_elements, t1.elements, t1.n * sizeof(double));
    follow_case.elements = follow_case_elements;
    // ------------------------------------
    
    // 这是根据规则6a生成的防御性代码，防止n<1时出错
    if (follow_case.n > 0) {
        // 这是根据规则5生成的具体操作代码
        int new_n = (follow_case.n - 1) / 2;
        if (new_n > 0) {
            double* new_elements = (double*)malloc(new_n * sizeof(double));
            for (int i = 0; i < new_n; i++) {
                new_elements[i] = follow_case.elements[1 + i * 2];
            }
            free(follow_case.elements);
            follow_case.elements = new_elements;
            follow_case.n = new_n;
        }
    }
    
    return follow_case;}

#include <math.h>
#include <stddef.h>

int z36check(double result1, double result2) {
    // 1. 核心判断逻辑 (标量直接比较)
    // 条件: result1 >= result2
    // 移项后: A = result1, B = result2, 比较符 >=

    double A = result1;
    double B = result2;

    // 防御 NaN
    if (isnan(A) || isnan(B)) return 0;

    // 处理无穷大情况
    if (isinf(A) || isinf(B)) {
        // 对于无穷大，直接进行数学比较
        if (A >= B) return 1;
        else return 0;
    }

    // 定义基础容差
    double epsilon = 1e-5;
    
    // 计算动态宽容度
    double tol = epsilon * fmax(1.0, fmax(fabs(A), fabs(B)));
    
    // 带容差的比较: A >= B 等价于 !(A < B)
    // 违反条件: A < B - tol
    if (A < B - tol) {
        return 0;
    }

    // 2. 满足条件，返回 1
    return 1;
}

TestResult z36runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z36Change(test_cases[test_case_id]);
    // 原始调用
    double source = max(test_cases[test_case_id].elements, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    double follow = max(follow_case.elements, follow_case.n);
    
    double** memory_list = (double**)malloc(1 * sizeof(double*));
    memory_list[0] = follow_case.elements;
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z36check(source, follow);
    test_result.status = status;
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z36runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}