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


double* calculateAbsoluteDifferences(double z[], int n){
    if (n == 0)
    {
        return NULL;
    }
    
    double* zAbs = (double*)malloc(n * sizeof(double));
    for (int i = 0; i < n; i++)
    {
        zAbs[i] = fabs(z[i]);
    }
    return zAbs;
}


typedef struct {
    double* z; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0, 2.0, 3.0}, 3},
    {(double[]){-1.0, -2.0, -3.0}, 3},
    {(double[]){0.0, 0.0, 0.0}, 3},
    {(double[]){-5.5, 10.2, -3.7}, 3},
    {(double[]){1.5}, 1},
    {(double[]){-1.5}, 1},
    {(double[]){0.0}, 1},
    {(double[]){100.0, -100.0}, 2},
    {(double[]){3.14159, -2.71828}, 2},
    {(double[]){1.1, 2.2, 3.3, 4.4}, 4},
    {(double[]){-1.1, -2.2, -3.3, -4.4}, 4},
    {(double[]){0.1, -0.1, 0.01, -0.01}, 4},
    {(double[]){-10.0, 20.0, -30.0, 40.0, -50.0}, 5},
    {(double[]){0.5, -0.5, 1.0, -1.0, 1.5, -1.5}, 6},
    {(double[]){2.0}, 1},
    {(double[]){-2.0}, 1},
    {(double[]){1.0, -1.0}, 2},
    {(double[]){10.0, 0.0, -10.0}, 3},
    {(double[]){0.25, -0.75, 1.25}, 3},
    {(double[]){-0.001, 0.001}, 2},
    {(double[]){999.999, -999.999}, 2},
    {(double[]){1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0}, 10},
    {(double[]){-1.0, -2.0, -3.0, -4.0, -5.0, -6.0, -7.0, -8.0, -9.0, -10.0}, 10},
    {(double[]){1.2, -3.4, 5.6, -7.8, 9.0}, 5},
    {(double[]){-1.2, 3.4, -5.6, 7.8, -9.0}, 5},
    {(double[]){0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, 6},
    {(double[]){12.34}, 1},
    {(double[]){-56.78}, 1},
    {(double[]){1.0, 0.0, -1.0, 0.5, -0.5}, 5},
    {(double[]){-1000.0, 500.0, -250.0, 125.0}, 4}
};
int num_test_cases = 30;


    typedef struct {
        double* result1;
        double* result2;
        double** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z5Change(TestCase t1) {
TestCase follow_case = t1;
// --- 这是根据规则4生成的内存处理代码 ---
double* follow_case_z = (double*)malloc(t1.n * sizeof(double));
memcpy(follow_case_z, t1.z, t1.n * sizeof(double));
follow_case.z = follow_case_z;
// ------------------------------------

// 这是根据规则6a生成的防御性代码，防止n<2时出错
if (follow_case.n < 2) {
    // 元素不足2个，无需反转，直接返回副本
    return follow_case;
}

// 这是根据规则5生成的具体操作代码
for (int i = 0; i < follow_case.n / 2; i++) {
    double temp = follow_case.z[i];
    follow_case.z[i] = follow_case.z[follow_case.n - 1 - i];
    follow_case.z[follow_case.n - 1 - i] = temp;
}

return follow_case;}

#include <math.h>
#include <stddef.h>

int z5check(double* result1, double* result2, int n) {
    // 1. 防御性编程 (空指针与长度检查)
    if (result1 == NULL || result2 == NULL) return 0;
    if (n <= 0) return 1;

    // 2. 核心判断逻辑 (elementwise)
    // 条件: result1[] is the reverse of result2[]
    // 这意味着对于所有 i: result1[i] == result2[n-1-i]
    for (int i = 0; i < n; i++) {
        // 提取移项后的操作数 A = result1[i], B = result2[n-1-i]
        double A = result1[i];
        double B = result2[n-1-i];
        
        // 防御 NaN
        if (isnan(A) || isnan(B)) return 0;
        
        // 处理无穷大
        if (isinf(A) || isinf(B)) {
            // 移项后的条件是 A == B
            if (A != B) return 0;
            // 如果相等，继续检查下一个元素
            continue;
        }
        
        // 定义基础容差
        double epsilon = 1e-5;
        // 计算动态宽容度
        double tol = epsilon * fmax(1.0, fmax(fabs(A), fabs(B)));
        
        // 移项后的条件是相等 (==)
        // 若 fabs(A - B) > tol，则违反条件
        if (fabs(A - B) > tol) {
            return 0;
        }
    }

    // 3. 全部满足，返回 1
    return 1;
}

TestResult z5runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z5Change(test_cases[test_case_id]);
    // 原始调用
    double* source = calculateAbsoluteDifferences(test_cases[test_case_id].z, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    double* follow = calculateAbsoluteDifferences(follow_case.z, follow_case.n);
    
    double** memory_list = (double**)malloc(1 * sizeof(double*));
    memory_list[0] = follow_case.z;
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z5check(source, follow, test_cases[test_case_id].n);
    test_result.status = status;
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z5runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}