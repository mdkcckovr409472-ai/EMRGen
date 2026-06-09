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


double* ebeAdd(double a[], double b[], int n1, int n2) {
    if (n1 != n2) {
        return NULL; 
    }

    double* result = (double*)malloc(n1 * sizeof(double));
    if (result == NULL) {
        return NULL;  
    }

    for (int i = 0; i < n1; i++) {
        result[i] = a[i] + b[i];  
    }

    return result; 
}


typedef struct {
    double* a; double* b; int n1; int n2;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0, 2.0, 3.0}, (double[]){4.0, 5.0, 6.0}, 3, 3},
    {(double[]){0.0, 0.0}, (double[]){0.0, 0.0}, 2, 2},
    {(double[]){-1.5, 2.7}, (double[]){3.2, -4.1}, 2, 2},
    {(double[]){10.0}, (double[]){-10.0}, 1, 1},
    {(double[]){1.1, 2.2}, (double[]){-1.1, -2.2}, 2, 2},
    {(double[]){3.14159}, (double[]){2.71828}, 1, 1},
    {(double[]){100.5, 200.75, 300.9}, (double[]){50.25, 75.5, 90.1}, 3, 3},
    {(double[]){-0.001, 0.001}, (double[]){0.001, -0.001}, 2, 2},
    {(double[]){1.0e-6, 2.0e-6}, (double[]){3.0e-6, 4.0e-6}, 2, 2},
    {(double[]){999.999}, (double[]){0.001}, 1, 1},
    {(double[]){1.0, 2.0, 3.0, 4.0}, (double[]){5.0, 6.0, 7.0, 8.0}, 4, 4},
    {(double[]){-100.0, -200.0}, (double[]){100.0, 200.0}, 2, 2},
    {(double[]){12.34, 56.78}, (double[]){98.76, 43.21}, 2, 2},
    {(double[]){0.5, 1.5, 2.5}, (double[]){-0.5, -1.5, -2.5}, 3, 3},
    {(double[]){1.0}, (double[]){1.0}, 1, 1},
    {(double[]){2.2, 3.3, 4.4, 5.5, 6.6}, (double[]){1.1, 2.2, 3.3, 4.4, 5.5}, 5, 5},
    {(double[]){-3.14, 0.0, 3.14}, (double[]){1.0, 2.0, 3.0}, 3, 3},
    {(double[]){1.0, 0.0, -1.0}, (double[]){0.0, 1.0, 0.0}, 3, 3},
    {(double[]){10.1, 20.2}, (double[]){30.3, 40.4}, 2, 2},
    {(double[]){7.0, 8.0, 9.0, 10.0, 11.0, 12.0}, (double[]){1.0, 2.0, 3.0, 4.0, 5.0, 6.0}, 6, 6},
    {(double[]){0.25, 0.5, 0.75}, (double[]){0.25, 0.5, 0.75}, 3, 3},
    {(double[]){-999.9, 0.0, 999.9}, (double[]){0.1, 0.0, -0.1}, 3, 3},
    {(double[]){1.5}, (double[]){2.5}, 1, 1},
    {(double[]){1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0}, (double[]){7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0}, 7, 7},
    {(double[]){0.0}, (double[]){0.0}, 1, 1},
    {(double[]){-1.0, -2.0, -3.0}, (double[]){-4.0, -5.0, -6.0}, 3, 3},
    {(double[]){1000.0, 2000.0}, (double[]){-500.0, -1500.0}, 2, 2},
    {(double[]){9.876, 5.432}, (double[]){1.234, 4.568}, 2, 2},
    {(double[]){0.1, 0.2, 0.3, 0.4}, (double[]){0.9, 0.8, 0.7, 0.6}, 4, 4},
    {(double[]){15.0, 25.0, 35.0}, (double[]){10.0, 20.0, 30.0}, 3, 3}
};
int num_test_cases = 30;


    typedef struct {
        double* result1;
        double* result2;
        double** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z12Change(TestCase t1) {
TestCase follow_case = t1;
// --- 这是根据规则4生成的内存处理代码 ---
double* follow_case_a = (double*)malloc(t1.n1 * sizeof(double));
memcpy(follow_case_a, t1.a, t1.n1 * sizeof(double));
follow_case.a = follow_case_a;
// ------------------------------------

// 这是根据规则6a生成的防御性代码，防止n1<1时出错
if (follow_case.n1 < 1) {
    // 元素不足1个，无法排序，直接返回副本
    return follow_case;
}

// 这是根据规则5生成的具体操作代码
// 使用冒泡排序进行升序排序
for (int i = 0; i < follow_case.n1 - 1; i++) {
    for (int j = 0; j < follow_case.n1 - i - 1; j++) {
        if (follow_case.a[j] > follow_case.a[j + 1]) {
            double temp = follow_case.a[j];
            follow_case.a[j] = follow_case.a[j + 1];
            follow_case.a[j + 1] = temp;
        }
    }
}

return follow_case;}

#include <cmath>
#include <cfloat>

int z12check(double* result1, double* result2, int n) {
    // 1. 防御性编程 (空指针与长度检查)
    if (result1 == NULL || result2 == NULL) return 0;
    if (n <= 0) return 1;

    // 2. 字典序比较逻辑 (lexically)
    for (int i = 0; i < n; i++) {
        double A = result1[i];
        double B = result2[i];

        // 浮点数特殊处理
        // 防御 NaN
        if (std::isnan(A) || std::isnan(B)) return 0;

        // 处理无穷大（动态容差对Inf无效）
        if (std::isinf(A) || std::isinf(B)) {
            // 根据移项后的条件 result1 >= result2 直接比较
            if (A < B) {
                // 在第一个不相等的位置，result1[i] < result2[i]，违反 >= 条件
                return 0;
            } else if (A > B) {
                // 在第一个不相等的位置，result1[i] > result2[i]，满足 >= 条件
                return 1;
            }
            // 如果相等，继续检查下一个元素
            continue;
        }

        // 计算动态容差
        double epsilon = 1e-5;
        double tol = epsilon * fmax(1.0, fmax(fabs(A), fabs(B)));

        // 检查是否不相等（考虑容差）
        if (fabs(A - B) > tol) {
            // 找到第一个不相等的元素对
            // 根据条件 result1 >= result2 判断
            if (A < B - tol) {
                // 违反 >= 条件
                return 0;
            } else {
                // 满足 >= 条件
                return 1;
            }
        }
        // 如果相等（在容差范围内），继续检查下一个元素
    }

    // 3. 循环结束，所有元素都相等（在容差范围内），满足 >= 条件
    return 1;
}

TestResult z12runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z12Change(test_cases[test_case_id]);
    // 原始调用
    double* source = ebeAdd(test_cases[test_case_id].a, test_cases[test_case_id].b, test_cases[test_case_id].n1, test_cases[test_case_id].n2); // MODIFIED: Explicit type
    // 变换后调用
    double* follow = ebeAdd(follow_case.a, follow_case.b, follow_case.n1, follow_case.n2);
    
    double** memory_list = (double**)malloc(1 * sizeof(double*));
    memory_list[0] = follow_case.a;
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z12check(source, follow, test_cases[test_case_id].n1);
    test_result.status = status;
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z12runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}