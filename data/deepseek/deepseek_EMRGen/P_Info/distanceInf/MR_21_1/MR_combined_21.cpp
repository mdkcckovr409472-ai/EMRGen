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


double distanceInf(double p1[], double p2[], int n) {
    double maxi = 0;
    for (int i = 0; i < n; i++) {
        maxi = max(maxi, abs(p1[i] - p2[i]));
    } 
    return maxi;
}


typedef struct {
    double* p1; double* p2; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){0.0, 0.0}, (double[]){0.0, 0.0}, 2},
    {(double[]){1.0, 2.0}, (double[]){1.0, 2.0}, 2},
    {(double[]){1.0, 2.0}, (double[]){4.0, 6.0}, 2},
    {(double[]){-1.0, -2.0}, (double[]){-4.0, -6.0}, 2},
    {(double[]){1.5, 2.5, 3.5}, (double[]){1.5, 2.5, 3.5}, 3},
    {(double[]){1.0, 2.0, 3.0}, (double[]){4.0, 5.0, 6.0}, 3},
    {(double[]){-1.0, -2.0, -3.0}, (double[]){-4.0, -5.0, -6.0}, 3},
    {(double[]){0.0}, (double[]){5.0}, 1},
    {(double[]){5.0}, (double[]){0.0}, 1},
    {(double[]){-5.0}, (double[]){5.0}, 1},
    {(double[]){1.1, 2.2}, (double[]){1.1, 3.3}, 2},
    {(double[]){10.0, 20.0, 30.0}, (double[]){11.0, 19.0, 31.0}, 3},
    {(double[]){0.5, 1.5, 2.5, 3.5}, (double[]){0.5, 1.5, 2.5, 3.5}, 4},
    {(double[]){0.5, 1.5, 2.5, 3.5}, (double[]){4.5, 5.5, 6.5, 7.5}, 4},
    {(double[]){-0.5, -1.5, -2.5, -3.5}, (double[]){-4.5, -5.5, -6.5, -7.5}, 4},
    {(double[]){100.0, 200.0}, (double[]){100.0, 200.0}, 2},
    {(double[]){100.0, 200.0}, (double[]){150.0, 250.0}, 2},
    {(double[]){1.0, 0.0, -1.0}, (double[]){0.0, 1.0, 0.0}, 3},
    {(double[]){2.2, 3.3, 4.4, 5.5}, (double[]){2.2, 3.3, 4.4, 5.5}, 4},
    {(double[]){2.2, 3.3, 4.4, 5.5}, (double[]){7.7, 8.8, 9.9, 10.1}, 4},
    {(double[]){0.001, 0.002}, (double[]){0.001, 0.002}, 2},
    {(double[]){0.001, 0.002}, (double[]){0.003, 0.004}, 2},
    {(double[]){-10.5, 20.5}, (double[]){-10.5, 20.5}, 2},
    {(double[]){-10.5, 20.5}, (double[]){5.5, -5.5}, 2},
    {(double[]){1.0, 2.0, 3.0, 4.0, 5.0}, (double[]){1.0, 2.0, 3.0, 4.0, 5.0}, 5},
    {(double[]){1.0, 2.0, 3.0, 4.0, 5.0}, (double[]){6.0, 7.0, 8.0, 9.0, 10.0}, 5},
    {(double[]){-1.0, -2.0, -3.0, -4.0, -5.0}, (double[]){-6.0, -7.0, -8.0, -9.0, -10.0}, 5},
    {(double[]){0.0, 0.0, 0.0}, (double[]){1.0, 2.0, 3.0}, 3},
    {(double[]){1.0, 2.0, 3.0}, (double[]){0.0, 0.0, 0.0}, 3},
    {(double[]){3.14, 2.71}, (double[]){3.14, 2.71}, 2}
};
int num_test_cases = 30;


    typedef struct {
        double result1;
        double result2;
        double** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z21Change(TestCase t1) {
TestCase follow_case = t1;
// --- 这是根据规则4生成的内存处理代码 ---
double* follow_case_p1 = (double*)malloc(t1.n * sizeof(double));
memcpy(follow_case_p1, t1.p1, t1.n * sizeof(double));
follow_case.p1 = follow_case_p1;
// ------------------------------------

// 这是根据规则6a生成的防御性代码，防止n<=0时出错
if (follow_case.n <= 0) {
    // 数组为空或长度为负，无法排序，直接返回副本
    return follow_case;
}

// 这是根据规则5生成的具体操作代码
// 使用标准库qsort进行升序排序
qsort(follow_case.p1, follow_case.n, sizeof(double), [](const void* a, const void* b) -> int {
    double arg1 = *static_cast<const double*>(a);
    double arg2 = *static_cast<const double*>(b);
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
});

return follow_case;}

#include <math.h>
#include <stddef.h>

int z21check(double result1, double result2) {
    // 1. 防御性编程 (标量情况无需指针和长度检查)
    // 2. 核心判断逻辑 (标量直接比较)
    // 浮点数比较特殊处理
    double epsilon = 1e-5;
    
    // 移项: return.result1 <= return.result2 等价于 result1 <= result2
    double A = result1;
    double B = result2;
    
    // 防御 NaN
    if (isnan(A) || isnan(B)) return 0;
    
    // 处理无穷大
    if (isinf(A) || isinf(B)) {
        if (A <= B) return 1;
        else return 0;
    }
    
    // 计算动态容差
    double tol = epsilon * fmax(1.0, fmax(fabs(A), fabs(B)));
    
    // 带容差的比较判定 (<=)
    if (A > B + tol) {
        return 0;
    }
    
    // 3. 满足条件，返回 1
    return 1;
}

TestResult z21runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z21Change(test_cases[test_case_id]);
    // 原始调用
    double source = distanceInf(test_cases[test_case_id].p1, test_cases[test_case_id].p2, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    double follow = distanceInf(follow_case.p1, follow_case.p2, follow_case.n);
    
    double** memory_list = (double**)malloc(1 * sizeof(double*));
    memory_list[0] = follow_case.p1;
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z21check(source, follow);
    test_result.status = status;
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z21runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}