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


double* computeDividedDifference1(double x[], double y[], int n) {
    double* a = (double*)malloc(n * sizeof(double));
    if (n <= 0) return nullptr;

    a[0] = y[0];
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < n - i; j++) {
            double denominator = x[j + i] - x[j];
            if (denominator == 0.0) {
                for (int k = 0; k < n; k++) a[k] = 0.0;
                return a;
            }
            y[j] = (y[j + 1] - y[j]) / denominator;
        }
        a[i] = y[0];
    }
    return a;
}

typedef struct {
    double* x; double* y; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){0.0}, (double[]){1.0}, 1},
    {(double[]){0.0, 1.0}, (double[]){1.0, 2.0}, 2},
    {(double[]){0.0, 1.0, 2.0}, (double[]){1.0, 4.0, 9.0}, 3},
    {(double[]){-2.0, -1.0, 0.0, 1.0, 2.0}, (double[]){4.0, 1.0, 0.0, 1.0, 4.0}, 5},
    {(double[]){1.0, 2.0, 3.0, 4.0}, (double[]){1.0, 8.0, 27.0, 64.0}, 4},
    {(double[]){0.5, 1.5, 2.5}, (double[]){0.25, 2.25, 6.25}, 3},
    {(double[]){10.0, 20.0, 30.0}, (double[]){100.0, 400.0, 900.0}, 3},
    {(double[]){-5.0, 0.0, 5.0}, (double[]){25.0, 0.0, 25.0}, 3},
    {(double[]){1.0, 2.0}, (double[]){3.0, 5.0}, 2},
    {(double[]){0.0, 0.5, 1.0}, (double[]){sin(0.0), sin(0.5), sin(1.0)}, 3},
    {(double[]){0.0, 1.0, 2.0, 3.0}, (double[]){exp(0.0), exp(1.0), exp(2.0), exp(3.0)}, 4},
    {(double[]){1.0, 4.0, 9.0}, (double[]){1.0, 2.0, 3.0}, 3},
    {(double[]){2.0, 3.0, 5.0, 7.0}, (double[]){1.0, 2.0, 3.0, 4.0}, 4},
    {(double[]){0.1, 0.2, 0.3}, (double[]){0.01, 0.04, 0.09}, 3},
    {(double[]){-1.0, 0.0, 1.0, 2.0}, (double[]){1.0, 0.0, 1.0, 4.0}, 4},
    {(double[]){100.0, 101.0, 102.0}, (double[]){10000.0, 10201.0, 10404.0}, 3},
    {(double[]){0.0, 2.0, 4.0, 6.0}, (double[]){0.0, 4.0, 16.0, 36.0}, 4},
    {(double[]){-3.0, -2.0, -1.0}, (double[]){9.0, 4.0, 1.0}, 3},
    {(double[]){1.1, 2.2, 3.3}, (double[]){1.21, 4.84, 10.89}, 3},
    {(double[]){0.0, 0.25, 0.5, 0.75, 1.0}, (double[]){0.0, 0.0625, 0.25, 0.5625, 1.0}, 5},
    {(double[]){1.0, 3.0, 5.0}, (double[]){2.0, 10.0, 26.0}, 3},
    {(double[]){-10.0, -5.0, 0.0, 5.0}, (double[]){100.0, 25.0, 0.0, 25.0}, 4},
    {(double[]){2.0, 4.0, 8.0}, (double[]){4.0, 16.0, 64.0}, 3},
    {(double[]){0.0, 1.0, 2.0, 3.0, 4.0}, (double[]){0.0, 1.0, 4.0, 9.0, 16.0}, 5},
    {(double[]){0.0, 0.2, 0.4, 0.6, 0.8, 1.0}, (double[]){0.0, 0.04, 0.16, 0.36, 0.64, 1.0}, 6},
    {(double[]){1.5, 2.5, 3.5}, (double[]){2.25, 6.25, 12.25}, 3},
    {(double[]){-2.0, 0.0, 2.0}, (double[]){4.0, 0.0, 4.0}, 3},
    {(double[]){1.0, 10.0, 100.0}, (double[]){1.0, 100.0, 10000.0}, 3},
    {(double[]){0.0, 0.1, 0.2, 0.3}, (double[]){cos(0.0), cos(0.1), cos(0.2), cos(0.3)}, 4},
    {(double[]){1.0, 2.0, 3.0, 4.0, 5.0}, (double[]){1.0, 4.0, 9.0, 16.0, 25.0}, 5}
};
int num_test_cases = 30;


    typedef struct {
        double* result1;
        double* result2;
        double** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z53Change(TestCase t1) {
    TestCase follow_case = t1;
    // --- 这是根据规则4生成的内存处理代码 ---
    double* follow_case_y = (double*)malloc(t1.n * sizeof(double));
    memcpy(follow_case_y, t1.y, t1.n * sizeof(double));
    follow_case.y = follow_case_y;
    // ------------------------------------
    
    // 这是根据规则6a生成的防御性代码，防止n<=0时出错
    if (follow_case.n > 0) {
        // 这是根据规则5生成的具体操作代码
        for (int i = 0; i < follow_case.n; i++) {
            follow_case.y[i] = floor(follow_case.y[i]);
        }
    }
    
    return follow_case;
}

#include <cmath>
#include <cfloat>

int z53check(double* result1, double* result2, int n) {
    // 1. 防御性编程 (空指针与长度检查)
    if (result1 == NULL || result2 == NULL) return 0;
    if (n <= 0) return 1;

    // 2. 字典序比较逻辑 (lexically)
    for (int i = 0; i < n; i++) {
        double A = result1[i];
        double B = result2[i];

        // 防御 NaN
        if (std::isnan(A) || std::isnan(B)) return 0;

        // 处理无穷大
        if (std::isinf(A) || std::isinf(B)) {
            // 对于字典序，在第一个不等元素处决定结果
            if (A > B) {
                // result1[i] > result2[i]，对于 >= 条件，当前元素已满足，但字典序需要继续检查后续元素吗？
                // 不，字典序规则：遇到第一个不相等元素时，根据该对元素的关系即可决定整个数组的关系。
                // 如果 A > B，则 result1[] 在字典序上已经 > result2[]，这满足 >= 条件，可以立即返回成功。
                // 但为了严格遵循“遇到第一个不相等元素就决定结果”的规则，我们在这里处理。
                // 条件为 result1[] >= result2[] (lexically)
                // 若 A > B，则 result1[] 在字典序上 > result2[]，这满足 >=，整个条件成立。
                // 因此，我们可以立即返回 1。
                return 1;
            } else if (A < B) {
                // result1[i] < result2[i]，则 result1[] 在字典序上 < result2[]，这违反 >= 条件。
                return 0;
            }
            // 如果 A == B (包括 +Inf == +Inf, -Inf == -Inf)，则继续循环检查下一个元素
            continue;
        }

        // 对于有限浮点数，使用容差比较判断是否相等
        double epsilon = 1e-5;
        double tol = epsilon * fmax(1.0, fmax(fabs(A), fabs(B)));

        if (fabs(A - B) > tol) {
            // 元素不相等，根据这一对元素决定字典序结果
            if (A > B) {
                // result1[i] > result2[i]，满足 >= 条件，整个条件成立。
                return 1;
            } else {
                // result1[i] < result2[i]，违反 >= 条件。
                return 0;
            }
        }
        // 如果元素在容差内相等，继续检查下一个元素
    }

    // 3. 循环结束，所有元素在容差内相等，满足 result1[] >= result2[] (lexically)
    return 1;
}

TestResult z53runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z53Change(test_cases[test_case_id]);
    // 原始调用
    double* source = computeDividedDifference1(test_cases[test_case_id].x, test_cases[test_case_id].y, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    double* follow = computeDividedDifference1(follow_case.x, follow_case.y, follow_case.n);
    
    double** memory_list = (double**)malloc(1 * sizeof(double*));
    memory_list[0] = follow_case.y;
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z53check(source, follow, test_cases[test_case_id].n);
    test_result.status = status;
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z53runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}