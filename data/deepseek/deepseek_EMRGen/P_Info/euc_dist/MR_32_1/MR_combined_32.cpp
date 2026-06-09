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


double euc_Dist_m(double array1[], double array2[], int n) {
    double Sum = 0.0;
    for (int i = 0; i < n; i++) {
        Sum = Sum + pow((array1[i] - array2[i]), 2.0);
    }
    return sqrt(Sum);
}

typedef struct {
    double* array1; double* array2; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){0.0}, (double[]){0.0}, 1},
    {(double[]){1.0}, (double[]){1.0}, 1},
    {(double[]){3.0}, (double[]){7.0}, 1},
    {(double[]){1.0, 2.0}, (double[]){1.0, 2.0}, 2},
    {(double[]){1.0, 2.0}, (double[]){4.0, 6.0}, 2},
    {(double[]){-1.0, -2.0}, (double[]){-1.0, -2.0}, 2},
    {(double[]){-1.0, -2.0}, (double[]){1.0, 2.0}, 2},
    {(double[]){1.5, 2.5}, (double[]){1.5, 2.5}, 2},
    {(double[]){1.5, 2.5}, (double[]){4.5, 6.5}, 2},
    {(double[]){0.0, 0.0, 0.0}, (double[]){0.0, 0.0, 0.0}, 3},
    {(double[]){1.0, 0.0, 0.0}, (double[]){0.0, 0.0, 0.0}, 3},
    {(double[]){0.0, 1.0, 0.0}, (double[]){0.0, 0.0, 0.0}, 3},
    {(double[]){0.0, 0.0, 1.0}, (double[]){0.0, 0.0, 0.0}, 3},
    {(double[]){1.0, 2.0, 3.0}, (double[]){1.0, 2.0, 3.0}, 3},
    {(double[]){1.0, 2.0, 3.0}, (double[]){4.0, 5.0, 6.0}, 3},
    {(double[]){-1.0, -2.0, -3.0}, (double[]){-1.0, -2.0, -3.0}, 3},
    {(double[]){-1.0, -2.0, -3.0}, (double[]){1.0, 2.0, 3.0}, 3},
    {(double[]){1.1, 2.2, 3.3}, (double[]){1.1, 2.2, 3.3}, 3},
    {(double[]){1.1, 2.2, 3.3}, (double[]){4.4, 5.5, 6.6}, 3},
    {(double[]){1.0, 2.0, 3.0, 4.0}, (double[]){1.0, 2.0, 3.0, 4.0}, 4},
    {(double[]){1.0, 2.0, 3.0, 4.0}, (double[]){5.0, 6.0, 7.0, 8.0}, 4},
    {(double[]){-1.0, -2.0, -3.0, -4.0}, (double[]){-1.0, -2.0, -3.0, -4.0}, 4},
    {(double[]){-1.0, -2.0, -3.0, -4.0}, (double[]){1.0, 2.0, 3.0, 4.0}, 4},
    {(double[]){0.5, 1.5, 2.5, 3.5}, (double[]){0.5, 1.5, 2.5, 3.5}, 4},
    {(double[]){0.5, 1.5, 2.5, 3.5}, (double[]){4.5, 5.5, 6.5, 7.5}, 4},
    {(double[]){1.0, 2.0, 3.0, 4.0, 5.0}, (double[]){1.0, 2.0, 3.0, 4.0, 5.0}, 5},
    {(double[]){1.0, 2.0, 3.0, 4.0, 5.0}, (double[]){6.0, 7.0, 8.0, 9.0, 10.0}, 5},
    {(double[]){-1.0, -2.0, -3.0, -4.0, -5.0}, (double[]){-1.0, -2.0, -3.0, -4.0, -5.0}, 5},
    {(double[]){-1.0, -2.0, -3.0, -4.0, -5.0}, (double[]){1.0, 2.0, 3.0, 4.0, 5.0}, 5},
    {(double[]){1.1, 2.2, 3.3, 4.4, 5.5}, (double[]){1.1, 2.2, 3.3, 4.4, 5.5}, 5}
};
int num_test_cases = 30;


    typedef struct {
        double result1;
        double result2;
        double** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z32Change(TestCase t1) {
TestCase follow_case = t1;
// --- 这是根据规则4生成的内存处理代码 ---
double* follow_case_array2 = (double*)malloc(t1.n * sizeof(double));
memcpy(follow_case_array2, t1.array2, t1.n * sizeof(double));
follow_case.array2 = follow_case_array2;
// ------------------------------------

// 这是根据规则6a生成的防御性代码，防止n<=0时出错
if (follow_case.n > 0) {
    // 这是根据规则5生成的具体操作代码
    for (int i = 0; i < follow_case.n; i++) {
        follow_case.array2[i] = follow_case.array2[i] * 3.0;
    }
}

return follow_case;}

#include <math.h>
#include <stddef.h>

int z32check(double result1, double result2) {
    // 防御性编程：检查NaN
    if (isnan(result1) || isnan(result2)) return 0;
    
    // 处理无穷大情况（动态容差对Inf无效，需直接比较）
    if (isinf(result1) || isinf(result2)) {
        // 移项后的条件：result1 <= result2
        if (result1 <= result2) return 1;
        else return 0;
    }
    
    // 定义基础容差
    double epsilon = 1e-5;
    
    // 移项后的条件：result1 <= result2
    // 提取A和B（已移项）
    double A = result1;
    double B = result2;
    
    // 计算动态容差
    double tol = epsilon * fmax(1.0, fmax(fabs(A), fabs(B)));
    
    // 带容差的比较：A <= B
    // 违反条件：A > B + tol
    if (A > B + tol) return 0;
    
    // 满足条件
    return 1;
}

TestResult z32runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z32Change(test_cases[test_case_id]);
    // 原始调用
    double source = euc_Dist_m(test_cases[test_case_id].array1, test_cases[test_case_id].array2, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    double follow = euc_Dist_m(follow_case.array1, follow_case.array2, follow_case.n);
    
    double** memory_list = (double**)malloc(1 * sizeof(double*));
    memory_list[0] = follow_case.array2;
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z32check(source, follow);
    test_result.status = status;
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z32runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}