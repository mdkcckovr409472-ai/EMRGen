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

TestCase z13Change(TestCase t1) {
TestCase follow_case = t1;
// --- 这是根据规则4生成的内存处理代码 ---
double* follow_case_a = (double*)malloc(t1.n1 * sizeof(double));
memcpy(follow_case_a, t1.a, t1.n1 * sizeof(double));
follow_case.a = follow_case_a;
// ------------------------------------

// 这是根据规则6a生成的防御性代码，防止n1<1时出错
if (follow_case.n1 <= 0) {
    // 数组为空或长度为负，无法排序，直接返回副本
    return follow_case;
}

// 这是根据规则5生成的具体操作代码
// 数组降序排序
int i, j;
double temp;
for (i = 0; i < follow_case.n1 - 1; i++) {
    for (j = 0; j < follow_case.n1 - i - 1; j++) {
        if (follow_case.a[j] < follow_case.a[j + 1]) {
            temp = follow_case.a[j];
            follow_case.a[j] = follow_case.a[j + 1];
            follow_case.a[j + 1] = temp;
        }
    }
}

return follow_case;}

#include <cmath>
#include <cfloat>

int z13check(double* result1, double* result2, int n) {
    // 1. 防御性编程 (空指针与长度检查)
    if (result1 == NULL || result2 == NULL) return 0;
    if (n <= 0) return 1;

    // 2. 核心判断逻辑 (字典序比较)
    // 条件: result1[] <= result2[] (lexically)
    // 移项后: result1 <= result2 (逐元素，但按字典序规则)
    double epsilon = 1e-5;

    for (int i = 0; i < n; i++) {
        double A = result1[i];
        double B = result2[i];

        // 防御 NaN
        if (std::isnan(A) || std::isnan(B)) return 0;

        // 处理无穷大
        if (std::isinf(A) || std::isinf(B)) {
            // 对于字典序，在第一个不相等的元素处决定结果
            if (A < B) {
                // result1[i] < result2[i]，字典序上 result1[] < result2[]，满足 <=
                return 1;
            } else if (A > B) {
                // result1[i] > result2[i]，字典序上 result1[] > result2[]，不满足 <=
                return 0;
            }
            // 如果相等（例如都是 +Inf），继续检查下一个元素
            continue;
        }

        // 计算动态容差
        double tol = epsilon * fmax(1.0, fmax(fabs(A), fabs(B)));

        // 字典序比较：寻找第一个不相等的元素对
        if (fabs(A - B) > tol) {
            // 元素不相等
            if (A < B - tol) {
                // result1[i] < result2[i]，字典序上 result1[] < result2[]，满足 <=
                return 1;
            } else {
                // result1[i] > result2[i]，字典序上 result1[] > result2[]，不满足 <=
                return 0;
            }
        }
        // 如果元素在容差内相等，继续检查下一个元素
    }

    // 3. 循环结束，所有元素在容差内相等，满足 result1[] <= result2[]
    return 1;
}

TestResult z13runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z13Change(test_cases[test_case_id]);
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
    int status = z13check(source, follow, test_cases[test_case_id].n1);
    test_result.status = status;
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z13runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}