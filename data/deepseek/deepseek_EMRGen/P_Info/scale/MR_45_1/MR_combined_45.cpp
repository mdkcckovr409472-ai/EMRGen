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


double* scale(double val, double arr[], int n) {
    double* newArr = (double*)malloc(n * sizeof(double));

    for (int i = 0; i < n; i++) {
        newArr[i] = arr[i] * val;
    }
    return newArr;
}


typedef struct {
    double val; double* arr; int n;
} TestCase;

TestCase test_cases[] = {
    {1.0, (double[]){1.0, 2.0, 3.0}, 3},
    {0.5, (double[]){4.0, 6.0, 8.0}, 3},
    {2.0, (double[]){-1.0, 0.0, 1.0}, 3},
    {-1.0, (double[]){5.0, -5.0, 2.5}, 3},
    {0.0, (double[]){100.0, 200.0, 300.0}, 3},
    {1.5, (double[]){10.0}, 1},
    {0.25, (double[]){0.0, 0.0, 0.0, 0.0}, 4},
    {-2.0, (double[]){-2.0, -3.0, -4.0}, 3},
    {0.1, (double[]){1.1, 2.2, 3.3, 4.4, 5.5}, 5},
    {10.0, (double[]){0.001, 0.002, 0.003}, 3},
    {1.0, (double[]){}, 0},
    {-0.5, (double[]){8.0, 12.0, 16.0, 20.0}, 4},
    {3.0, (double[]){1.5}, 1},
    {0.333333, (double[]){9.0, 18.0, 27.0}, 3},
    {-1.5, (double[]){2.0, 4.0, 6.0, 8.0, 10.0}, 5},
    {1.0, (double[]){-10.5, 20.5}, 2},
    {0.01, (double[]){1000.0, 2000.0}, 2},
    {2.5, (double[]){0.4, 0.8, 1.2}, 3},
    {-0.2, (double[]){-50.0, 50.0}, 2},
    {1.0, (double[]){3.14159, 2.71828}, 2},
    {0.75, (double[]){12.0, 24.0, 36.0, 48.0}, 4},
    {-3.0, (double[]){1.0, -1.0, 2.0, -2.0}, 4},
    {1.2, (double[]){5.0, 10.0, 15.0, 20.0, 25.0, 30.0}, 6},
    {0.0, (double[]){-999.999, 999.999}, 2},
    {0.8, (double[]){7.5}, 1},
    {-1.0, (double[]){0.0}, 1},
    {1.0, (double[]){1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0}, 10},
    {0.5, (double[]){-6.0, -4.0, -2.0, 0.0, 2.0, 4.0, 6.0}, 7},
    {1.1, (double[]){0.1, 0.2, 0.3, 0.4}, 4},
    {2.0, (double[]){0.5, 1.0, 1.5, 2.0, 2.5, 3.0}, 6}
};
int num_test_cases = 30;


    typedef struct {
        double* result1;
        double* result2;
        double** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z45Change(TestCase t1) {
TestCase follow_case = t1;
// --- 这是根据规则4生成的内存处理代码 ---
double* follow_case_arr = (double*)malloc(t1.n * sizeof(double));
memcpy(follow_case_arr, t1.arr, t1.n * sizeof(double));
follow_case.arr = follow_case_arr;
// ------------------------------------

// 这是根据规则6a生成的防御性代码，防止n<2时出错
if (follow_case.n < 2) {
    // 元素不足2个，无需反转，直接返回副本
    return follow_case;
}

// 这是根据规则5生成的具体操作代码
for (int i = 0; i < follow_case.n / 2; i++) {
    double temp = follow_case.arr[i];
    follow_case.arr[i] = follow_case.arr[follow_case.n - 1 - i];
    follow_case.arr[follow_case.n - 1 - i] = temp;
}

return follow_case;}

int z45check(double* result1, double* result2, int n) {
    // 1. 防御性编程 (空指针与长度检查)
    if (result1 == NULL || result2 == NULL) return 0;
    if (n <= 0) return 1;

    // 2. 核心判断逻辑 (elementwise)
    // 条件: result1[] is the reverse of result2[]
    // 即: result1[i] 应与 result2[n-1-i] 相等
    for (int i = 0; i < n; i++) {
        double A = result1[i];
        double B = result2[n - 1 - i];
        
        // 浮点数比较特殊处理
        // 防御 NaN
        if (__builtin_isnan(A) || __builtin_isnan(B)) return 0;
        
        // 处理无穷大
        if (__builtin_isinf(A) || __builtin_isinf(B)) {
            if (A != B) return 0; // 无穷大直接比较
            continue;
        }
        
        // 动态容差比较
        double epsilon = 1e-5;
        double tol = epsilon * __builtin_fmax(1.0, __builtin_fmax(__builtin_fabs(A), __builtin_fabs(B)));
        if (__builtin_fabs(A - B) > tol) {
            return 0;
        }
    }

    // 3. 全部满足，返回 1
    return 1;
}

TestResult z45runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z45Change(test_cases[test_case_id]);
    // 原始调用
    double* source = scale(test_cases[test_case_id].val, test_cases[test_case_id].arr, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    double* follow = scale(follow_case.val, follow_case.arr, follow_case.n);
    
    double** memory_list = (double**)malloc(1 * sizeof(double*));
    memory_list[0] = follow_case.arr;
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z45check(source, follow, test_cases[test_case_id].n);
    test_result.status = status;
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z45runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}