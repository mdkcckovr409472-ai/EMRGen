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


double weighted_average(double a[], double b[], int n) {
    double sum1 = 0;
    double sum2 = 0;
    for(int i = 0; i < n; i++) {
        sum1 += a[i] * b[i];
        sum2 += b[i];
    }
    return sum1 / sum2;
}


typedef struct {
    double* a; double* b; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0, 2.0, 3.0}, (double[]){1.0, 1.0, 1.0}, 3},
    {(double[]){5.0, 10.0, 15.0}, (double[]){2.0, 3.0, 5.0}, 3},
    {(double[]){-1.0, 0.0, 1.0}, (double[]){1.0, 2.0, 1.0}, 3},
    {(double[]){2.5, 3.5}, (double[]){4.0, 6.0}, 2},
    {(double[]){100.0, 200.0}, (double[]){0.5, 0.5}, 2},
    {(double[]){0.0, 0.0, 0.0}, (double[]){1.0, 2.0, 3.0}, 3},
    {(double[]){10.0}, (double[]){5.0}, 1},
    {(double[]){1.1, 2.2, 3.3, 4.4}, (double[]){0.1, 0.2, 0.3, 0.4}, 4},
    {(double[]){-2.0, -4.0, -6.0}, (double[]){1.0, 2.0, 3.0}, 3},
    {(double[]){3.0, 6.0, 9.0, 12.0}, (double[]){1.0, 2.0, 1.0, 2.0}, 4},
    {(double[]){7.0}, (double[]){3.0}, 1},
    {(double[]){0.5, 1.5, 2.5}, (double[]){2.0, 4.0, 6.0}, 3},
    {(double[]){8.0, 6.0, 4.0, 2.0}, (double[]){1.0, 1.0, 1.0, 1.0}, 4},
    {(double[]){9.0, 18.0}, (double[]){2.0, 4.0}, 2},
    {(double[]){1.0, 4.0, 9.0, 16.0}, (double[]){1.0, 2.0, 3.0, 4.0}, 4},
    {(double[]){2.0, 4.0, 8.0}, (double[]){0.25, 0.5, 0.25}, 3},
    {(double[]){-10.0, 10.0}, (double[]){3.0, 7.0}, 2},
    {(double[]){1.0, 2.0, 3.0, 4.0, 5.0}, (double[]){5.0, 4.0, 3.0, 2.0, 1.0}, 5},
    {(double[]){6.0, 12.0, 18.0}, (double[]){1.0, 2.0, 3.0}, 3},
    {(double[]){20.0, 40.0, 60.0}, (double[]){1.0, 2.0, 1.0}, 3},
    {(double[]){0.1, 0.2, 0.3}, (double[]){10.0, 20.0, 30.0}, 3},
    {(double[]){15.0, 25.0, 35.0}, (double[]){0.2, 0.3, 0.5}, 3},
    {(double[]){-1.5, -0.5, 0.5, 1.5}, (double[]){1.0, 2.0, 2.0, 1.0}, 4},
    {(double[]){50.0, 100.0}, (double[]){1.0, 3.0}, 2},
    {(double[]){1.0, 1.0, 1.0, 1.0}, (double[]){2.0, 3.0, 5.0, 7.0}, 4},
    {(double[]){12.0, 24.0, 36.0}, (double[]){0.5, 1.0, 1.5}, 3},
    {(double[]){0.0}, (double[]){5.0}, 1},
    {(double[]){2.0, 3.0, 5.0, 7.0}, (double[]){1.0, 1.0, 1.0, 1.0}, 4},
    {(double[]){30.0, 60.0, 90.0}, (double[]){1.0, 2.0, 3.0}, 3},
    {(double[]){4.0, 8.0, 12.0, 16.0, 20.0}, (double[]){1.0, 2.0, 3.0, 4.0, 5.0}, 5}
};
int num_test_cases = 30;


    typedef struct {
        double result1;
        double result2;
        double** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z31Change(TestCase t1) {
    TestCase follow_case = t1;
    // --- 这是根据规则4生成的内存处理代码 ---
    double* follow_case_b = (double*)malloc(t1.n * sizeof(double));
    memcpy(follow_case_b, t1.b, t1.n * sizeof(double));
    follow_case.b = follow_case_b;
    // ------------------------------------
    
    // 这是根据规则6a生成的防御性代码，防止n<=0时出错
    if (follow_case.n > 0) {
        // 这是根据规则5生成的具体操作代码
        for (int i = 0; i < follow_case.n; i++) {
            follow_case.b[i] *= 2.0;
        }
    }
    
    return follow_case;}

#include <math.h>
#include <stddef.h>

int z31check(double result1, double result2) {
    // 1. 防御 NaN
    if (isnan(result1) || isnan(result2)) return 0;
    
    // 2. 处理无穷大情况（动态容差对无穷大无效）
    if (isinf(result1) || isinf(result2)) {
        // 移项后的条件为 result1 == result2
        if (result1 == result2) return 1;
        else return 0;
    }
    
    // 3. 定义基础容差
    double epsilon = 1e-5;
    
    // 4. 移项提取操作数
    // 条件 return.result1 == return.result2 移项后为 result1 == result2
    double A = result1;
    double B = result2;
    
    // 5. 计算动态宽容度
    double tol = epsilon * fmax(1.0, fmax(fabs(A), fabs(B)));
    
    // 6. 带容差的相等比较
    if (fabs(A - B) > tol) {
        return 0;
    }
    
    // 7. 满足条件，返回 1
    return 1;
}

TestResult z31runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z31Change(test_cases[test_case_id]);
    // 原始调用
    double source = weighted_average(test_cases[test_case_id].a, test_cases[test_case_id].b, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    double follow = weighted_average(follow_case.a, follow_case.b, follow_case.n);
    
    double** memory_list = (double**)malloc(1 * sizeof(double*));
    memory_list[0] = follow_case.b;
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z31check(source, follow);
    test_result.status = status;
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z31runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}