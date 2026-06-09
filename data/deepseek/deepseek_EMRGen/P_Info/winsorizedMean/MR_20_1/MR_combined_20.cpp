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


double winsorizedMean(double elements[], int left, int right, int n) {
    qsort(elements, n, sizeof(double), [](const void *a, const void *b) -> int {
        double diff = *(double *)a - *(double *)b;
        if (diff > 0) return 1;
        else if (diff < 0) return -1;
        else return 0;
    });

    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += elements[i];
    }

    double mean = sum / n;

    if (n > 0 && left >= 0 && left < n) {
        double leftElement = elements[left];
        for (int i = 0; i < left; ++i) {
            mean += (leftElement - elements[i]) / n;
        }
    }

    if (n > 0 && right >= 0 && right < n && (n - 1 - right) >= 0) {
        double rightElement = elements[n - 1 - right];
        for (int i = 0; i < right; ++i) {
            mean += (rightElement - elements[n - 1 - i]) / n;
        }
    }

    return mean;
}

typedef struct {
    double* elements; int left; int right; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.5, 3.7, 2.1, 8.4, 5.0}, 1, 1, 5},
    {(double[]){-2.3, 0.0, 4.1, -1.2, 7.8, 3.3}, 0, 2, 6},
    {(double[]){10.5, 20.2, 15.8, 30.1, 25.6}, 2, 0, 5},
    {(double[]){0.1, 0.5, 0.3, 0.9, 0.7, 0.2, 0.6}, 1, 3, 7},
    {(double[]){100.0, 200.0, 150.0, 180.0}, 0, 0, 4},
    {(double[]){-5.5, -1.2, -3.7, -8.0, -2.9}, 1, 1, 5},
    {(double[]){12.34, 56.78, 90.12}, 0, 1, 3},
    {(double[]){42.0}, 0, 0, 1},
    {(double[]){1.1, 2.2, 3.3, 4.4, 5.5, 6.6}, 2, 2, 6},
    {(double[]){-10.1, 5.5, 0.0, 5.5, 10.1}, 1, 0, 5},
    {(double[]){7.2, 3.8, 9.1, 4.5, 6.0, 1.9, 8.7}, 3, 1, 7},
    {(double[]){0.01, 0.02, 0.05, 0.03}, 0, 1, 4},
    {(double[]){50.5, 30.3, 80.8, 60.6, 40.4, 70.7}, 1, 3, 6},
    {(double[]){-7.3, 2.4, -1.8, 5.9, -3.1, 4.0, -0.5, 1.2}, 2, 2, 8},
    {(double[]){999.9, 888.8, 777.7}, 1, 1, 3},
    {(double[]){1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0}, 4, 3, 9},
    {(double[]){-20.2, -15.7, -30.3, -25.1, -10.5}, 0, 4, 5},
    {(double[]){0.25, 0.75, 0.50, 1.00, 0.00}, 2, 0, 5},
    {(double[]){33.33, 66.66, 11.11, 99.99, 22.22}, 1, 2, 5},
    {(double[]){6.4, 2.1, 9.3, 5.7, 8.0, 3.5, 7.2, 4.9}, 0, 5, 8},
    {(double[]){-100.5, 200.2, -50.8, 150.1}, 1, 0, 4},
    {(double[]){0.0, 0.0, 0.0, 0.0, 0.0}, 2, 2, 5},
    {(double[]){1.618, 2.718, 3.142, 1.414, 2.236}, 0, 0, 5},
    {(double[]){18.6, 24.9, 12.3, 30.0, 21.7, 15.4}, 3, 1, 6},
    {(double[]){-9.8, -4.3, -12.1, -6.7, -2.2, -8.5}, 1, 2, 6},
    {(double[]){123.456, 789.012, 345.678, 901.234}, 0, 3, 4},
    {(double[]){5.0, 5.0, 5.0, 5.0, 5.0, 5.0}, 1, 4, 6},
    {(double[]){0.3, 0.7, 0.2, 0.9, 0.4, 0.8, 0.1, 0.6}, 2, 3, 8},
    {(double[]){-1.5, 3.0, -2.0, 4.5, -0.5, 2.0}, 0, 0, 6},
    {(double[]){10.0, 20.0, 30.0, 40.0, 50.0, 60.0, 70.0, 80.0, 90.0, 100.0}, 3, 4, 10}
};
int num_test_cases = 30;


    typedef struct {
        double result1;
        double result2;
        double** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z20Change(TestCase t1) {
TestCase follow_case = t1;
// --- 这是根据规则4生成的内存处理代码 ---
double* follow_case_elements = (double*)malloc(t1.n * sizeof(double));
memcpy(follow_case_elements, t1.elements, t1.n * sizeof(double));
follow_case.elements = follow_case_elements;
// ------------------------------------

// 这是根据规则6a生成的防御性代码，防止n<1时出错
if (follow_case.n > 0) {
    // 这是根据规则5生成的具体操作代码
    for (int i = 0; i < follow_case.n - 1; i++) {
        for (int j = 0; j < follow_case.n - i - 1; j++) {
            if (follow_case.elements[j] < follow_case.elements[j + 1]) {
                double temp = follow_case.elements[j];
                follow_case.elements[j] = follow_case.elements[j + 1];
                follow_case.elements[j + 1] = temp;
            }
        }
    }
}

return follow_case;}

#include <math.h>
#include <stddef.h>

int z20check(double result1, double result2) {
    // 1. 防御性编程 (标量情况无需指针/长度检查)

    // 2. 核心判断逻辑 (标量直接比较)
    // 条件: result1 == result2
    // 移项后: result1 == result2 (已满足两侧分布)

    // 浮点数特殊处理
    double epsilon = 1e-5;
    double A = result1;
    double B = result2;

    // 防御 NaN
    if (isnan(A) || isnan(B)) return 0;

    // 处理无穷大
    if (isinf(A) || isinf(B)) {
        if (A == B) return 1;
        else return 0;
    }

    // 计算动态容差
    double tol = epsilon * fmax(1.0, fmax(fabs(A), fabs(B)));

    // 带容差的相等比较
    if (fabs(A - B) > tol) {
        return 0;
    }

    // 3. 满足条件，返回 1
    return 1;
}

TestResult z20runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z20Change(test_cases[test_case_id]);
    // 原始调用
    double source = winsorizedMean(test_cases[test_case_id].elements, test_cases[test_case_id].left, test_cases[test_case_id].right, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    double follow = winsorizedMean(follow_case.elements, follow_case.left, follow_case.right, follow_case.n);
    
    double** memory_list = (double**)malloc(1 * sizeof(double*));
    memory_list[0] = follow_case.elements;
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z20check(source, follow);
    test_result.status = status;
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z20runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}