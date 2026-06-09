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


double* calculateDifferences(double x[], double y[], int n){

    double* z = (double*)malloc(n * sizeof(double));

    for (int i = 0; i < n; i++)
    {
        z[i] = y[i] - x[i];
    }
    
    return z;
}


typedef struct {
    double* x; double* y; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0, 2.0, 3.0}, (double[]){4.0, 5.0, 6.0}, 3},
    {(double[]){0.0, 0.0}, (double[]){0.0, 0.0}, 2},
    {(double[]){-1.5, 2.7}, (double[]){3.2, -4.1}, 2},
    {(double[]){10.0}, (double[]){20.0}, 1},
    {(double[]){1.1, 2.2, 3.3, 4.4}, (double[]){5.5, 6.6, 7.7, 8.8}, 4},
    {(double[]){100.0, 200.0, 300.0}, (double[]){50.0, 150.0, 250.0}, 3},
    {(double[]){0.5, 1.5, 2.5, 3.5, 4.5}, (double[]){5.5, 6.5, 7.5, 8.5, 9.5}, 5},
    {(double[]){-10.0, -20.0}, (double[]){-5.0, -15.0}, 2},
    {(double[]){3.14, 6.28}, (double[]){1.57, 3.14}, 2},
    {(double[]){2.0, 4.0, 8.0, 16.0}, (double[]){1.0, 2.0, 4.0, 8.0}, 4},
    {(double[]){0.1, 0.2, 0.3}, (double[]){0.4, 0.5, 0.6}, 3},
    {(double[]){25.0, 50.0, 75.0}, (double[]){100.0, 125.0, 150.0}, 3},
    {(double[]){-1.0, 0.0, 1.0}, (double[]){1.0, 0.0, -1.0}, 3},
    {(double[]){12.34, 56.78}, (double[]){98.76, 43.21}, 2},
    {(double[]){1.0, 1.0, 1.0, 1.0}, (double[]){2.0, 2.0, 2.0, 2.0}, 4},
    {(double[]){7.0, 14.0, 21.0}, (double[]){3.0, 6.0, 9.0}, 3},
    {(double[]){0.01, 0.02, 0.03}, (double[]){0.05, 0.06, 0.07}, 3},
    {(double[]){-100.0, 100.0}, (double[]){0.0, 200.0}, 2},
    {(double[]){9.8, 4.9}, (double[]){0.0, 9.8}, 2},
    {(double[]){1.618, 2.718, 3.142}, (double[]){0.618, 1.718, 2.142}, 3},
    {(double[]){5.0, 10.0, 15.0, 20.0, 25.0}, (double[]){30.0, 35.0, 40.0, 45.0, 50.0}, 5},
    {(double[]){2.5, 5.0, 7.5}, (double[]){10.0, 12.5, 15.0}, 3},
    {(double[]){-3.0, -2.0, -1.0, 0.0}, (double[]){0.0, 1.0, 2.0, 3.0}, 4},
    {(double[]){1000.0, 2000.0}, (double[]){500.0, 1500.0}, 2},
    {(double[]){0.25, 0.5, 0.75, 1.0}, (double[]){1.25, 1.5, 1.75, 2.0}, 4},
    {(double[]){8.0, 6.0, 4.0, 2.0}, (double[]){1.0, 3.0, 5.0, 7.0}, 4},
    {(double[]){1.0, 2.0, 3.0, 4.0, 5.0, 6.0}, (double[]){6.0, 5.0, 4.0, 3.0, 2.0, 1.0}, 6},
    {(double[]){0.0, 10.0, 20.0}, (double[]){5.0, 15.0, 25.0}, 3},
    {(double[]){-7.5, 0.0, 7.5}, (double[]){-15.0, 0.0, 15.0}, 3},
    {(double[]){99.9, 88.8, 77.7}, (double[]){11.1, 22.2, 33.3}, 3}
};
int num_test_cases = 30;


    typedef struct {
        double* result1;
        double* result2;
        double** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z49Change(TestCase t1) {
TestCase follow_case = t1;
// --- 这是根据规则4生成的内存处理代码 ---
double* follow_case_y = (double*)malloc(t1.n * sizeof(double));
memcpy(follow_case_y, t1.y, t1.n * sizeof(double));
follow_case.y = follow_case_y;
// ------------------------------------

// 这是根据规则6a生成的防御性代码，防止n<2时出错
if (follow_case.n < 2) {
    // 元素不足2个，无需排序，直接返回副本
    return follow_case;
}

// 这是根据规则5生成的具体操作代码
for (int i = 0; i < follow_case.n - 1; i++) {
    for (int j = 0; j < follow_case.n - i - 1; j++) {
        if (follow_case.y[j] < follow_case.y[j + 1]) {
            double temp = follow_case.y[j];
            follow_case.y[j] = follow_case.y[j + 1];
            follow_case.y[j + 1] = temp;
        }
    }
}

return follow_case;}

#include <math.h>
#include <stddef.h>

int z49check(double* result1, double* result2, int n) {
    // 1. 防御性编程 (空指针与长度检查)
    if (result1 == NULL || result2 == NULL) return 0;
    if (n <= 0) return 1;

    // 2. 核心判断逻辑 (字典序比较)
    double epsilon = 1e-5;
    for (int i = 0; i < n; i++) {
        double A = result1[i];
        double B = result2[i];

        // 防御 NaN
        if (isnan(A) || isnan(B)) return 0;

        // 处理无穷大
        if (isinf(A) || isinf(B)) {
            if (A < B) {
                // 在第一个不相等的元素处，result1[i] < result2[i]，满足字典序 <=，立即返回成功
                return 1;
            } else if (A > B) {
                // 在第一个不相等的元素处，result1[i] > result2[i]，违反字典序 <=，立即返回失败
                return 0;
            }
            // A 和 B 都是无穷大且相等，继续检查下一个元素
            continue;
        }

        // 计算动态容差
        double tol = epsilon * fmax(1.0, fmax(fabs(A), fabs(B)));

        // 检查第一个不相等的元素对
        if (fabs(A - B) > tol) {
            // 元素不相等，根据它们的关系决定字典序
            if (A < B - tol) {
                // result1[i] < result2[i]，满足字典序 <=，立即返回成功
                return 1;
            } else {
                // result1[i] > result2[i]，违反字典序 <=，立即返回失败
                return 0;
            }
        }
        // 元素在容差内相等，继续循环
    }

    // 3. 循环结束，所有元素在容差内相等，满足字典序 <=
    return 1;
}

TestResult z49runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z49Change(test_cases[test_case_id]);
    // 原始调用
    double* source = calculateDifferences(test_cases[test_case_id].x, test_cases[test_case_id].y, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    double* follow = calculateDifferences(follow_case.x, follow_case.y, follow_case.n);
    
    double** memory_list = (double**)malloc(1 * sizeof(double*));
    memory_list[0] = follow_case.y;
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z49check(source, follow, test_cases[test_case_id].n);
    test_result.status = status;
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z49runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}