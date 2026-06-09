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


double variance(double x[], int n) {
    double sum = 0;
    double sum1 = 0;
    double var = 0;
    double avrg = 0;
    for(int i = 0; i < n; i++) {
        sum = sum + x[i];
    }
    
    avrg = sum / (double)n;
    for (int i = 0; i < n; i++) {
        sum1 = sum1 + (x[i] - avrg) * (x[i] - avrg);
    }
    var = sum1 / (double) n;
    return var;
}


typedef struct {
    double* x; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.5, 2.5, 3.5}, 3},
    {(double[]){-2.1, 0.0, 4.3, -1.2}, 4},
    {(double[]){10.7}, 1},
    {(double[]){0.3, -0.3, 0.3, -0.3, 0.3}, 5},
    {(double[]){100.25, 200.75, 150.5}, 3},
    {(double[]){-8.9, 12.4, -5.6, 7.1, -3.3}, 5},
    {(double[]){1.1, 2.2, 3.3, 4.4, 5.5, 6.6}, 6},
    {(double[]){-15.0, 25.0, -35.0, 45.0}, 4},
    {(double[]){0.001, 0.002, 0.003}, 3},
    {(double[]){7.0}, 1},
    {(double[]){-1.5, -2.5, -3.5, -4.5}, 4},
    {(double[]){12.34, 56.78, 90.12}, 3},
    {(double[]){0.0, 0.0, 0.0, 0.0, 0.0}, 5},
    {(double[]){2.718, 3.142, 1.618}, 3},
    {(double[]){-100.1, 50.2, 75.3, -25.4}, 4},
    {(double[]){9.8, 7.6, 5.4, 3.2, 1.0}, 5},
    {(double[]){42.0}, 1},
    {(double[]){-6.6, 8.8, -10.1, 12.12, -14.14}, 5},
    {(double[]){0.5, 1.0, 1.5, 2.0, 2.5, 3.0, 3.5}, 7},
    {(double[]){-9.99, 18.18, -27.27}, 3},
    {(double[]){11.11, 22.22, 33.33, 44.44, 55.55}, 5},
    {(double[]){0.25, -0.75, 1.25, -1.75}, 4},
    {(double[]){6.02, 23.0, 1.38}, 3},
    {(double[]){-50.5, 30.3, -20.2, 10.1, 0.0}, 5},
    {(double[]){1.0, 4.0, 9.0, 16.0, 25.0}, 5},
    {(double[]){-7.3, 2.8, -4.1, 5.6, -0.9, 3.2}, 6},
    {(double[]){13.7, 29.4}, 2},
    {(double[]){0.0, -0.0}, 2},
    {(double[]){8.0, 15.0, 23.0, 31.0}, 4},
    {(double[]){-2.22, 3.33, -4.44, 5.55, -6.66}, 5}
};
int num_test_cases = 30;


    typedef struct {
        double result1;
        double result2;
        double** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z11Change(TestCase t1) {
    TestCase follow_case = t1;
    // --- 这是根据规则4生成的内存处理代码 ---
    double* follow_case_x = (double*)malloc(t1.n * sizeof(double));
    memcpy(follow_case_x, t1.x, t1.n * sizeof(double));
    follow_case.x = follow_case_x;
    // ------------------------------------

    // 这是根据规则6a生成的防御性代码，防止n<=0时出错
    if (follow_case.n > 0) {
        // 这是根据规则5生成的具体操作代码
        for (int i = 0; i < follow_case.n; i++) {
            follow_case.x[i] = 0.0;
        }
    }

    return follow_case;}

#include <math.h>
#include <stddef.h>

int z11check(double result1, double result2) {
    // 1. 防御性编程 (针对浮点数的特殊处理)
    // 定义基础容差
    double epsilon = 1e-5;
    
    // 根据条件 "return.result1 >= return.result2" 提取 A 和 B
    // 移项后条件为: result1 >= result2
    double A = result1;
    double B = result2;
    
    // 检查 NaN
    if (isnan(A) || isnan(B)) return 0;
    
    // 处理无穷大情况
    if (isinf(A) || isinf(B)) {
        // 无穷大时退化为数学直接比较
        if (A >= B) return 1;
        else return 0;
    }
    
    // 计算动态容差
    double tol = epsilon * fmax(1.0, fmax(fabs(A), fabs(B)));
    
    // 2. 核心判断逻辑 (带容差的浮点数比较)
    // 条件: A >= B  (即 result1 >= result2)
    // 违反条件: A < B - tol
    if (A < B - tol) {
        return 0;
    }
    
    // 3. 满足条件，返回 1
    return 1;
}

TestResult z11runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z11Change(test_cases[test_case_id]);
    // 原始调用
    double source = variance(test_cases[test_case_id].x, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    double follow = variance(follow_case.x, follow_case.n);
    
    double** memory_list = (double**)malloc(1 * sizeof(double*));
    memory_list[0] = follow_case.x;
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z11check(source, follow);
    test_result.status = status;
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z11runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}