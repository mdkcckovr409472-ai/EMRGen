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


double pooledMean(double data1[], double data2[], int n1, int n2) {
    double sum1 = 0;
    for (int i = 0; i < n1; i++) {
        sum1 += data1[i];
    }
    double mean1 = sum1 / n1;
    double sum2 = 0;
    for (int i = 0; i < n2; i++) {
        sum2 += data2[i];
    }
    double mean2 = sum2 / n2;
    return (n1 * mean1 + n2 * mean2) / (n1 + n2);
}


typedef struct {
    double* data1; double* data2; int n1; int n2;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0, 2.0, 3.0}, (double[]){4.0, 5.0, 6.0}, 3, 3},
    {(double[]){10.0, 20.0}, (double[]){30.0}, 2, 1},
    {(double[]){0.0, 0.0, 0.0}, (double[]){0.0, 0.0}, 3, 2},
    {(double[]){-1.5, 2.5}, (double[]){3.5, -4.5, 1.0}, 2, 3},
    {(double[]){100.0, 200.0, 300.0}, (double[]){400.0}, 3, 1},
    {(double[]){1.1, 2.2}, (double[]){3.3, 4.4, 5.5}, 2, 3},
    {(double[]){5.0}, (double[]){5.0}, 1, 1},
    {(double[]){2.0, 4.0, 6.0, 8.0}, (double[]){1.0, 3.0, 5.0}, 4, 3},
    {(double[]){-10.0, -20.0, -30.0}, (double[]){-5.0, -15.0}, 3, 2},
    {(double[]){0.5, 1.5, 2.5, 3.5, 4.5}, (double[]){1.0, 2.0}, 5, 2},
    {(double[]){12.34, 45.67}, (double[]){89.01}, 2, 1},
    {(double[]){7.0}, (double[]){8.0, 9.0, 10.0, 11.0}, 1, 4},
    {(double[]){1.0, 3.0, 5.0, 7.0, 9.0}, (double[]){2.0, 4.0, 6.0, 8.0}, 5, 4},
    {(double[]){0.1, 0.2, 0.3}, (double[]){0.4, 0.5, 0.6, 0.7}, 3, 4},
    {(double[]){50.0, 60.0}, (double[]){70.0, 80.0, 90.0, 100.0, 110.0}, 2, 5},
    {(double[]){-2.0, -1.0, 0.0, 1.0, 2.0}, (double[]){-1.5, 0.5, 2.5}, 5, 3},
    {(double[]){1000.0, 2000.0}, (double[]){1500.0}, 2, 1},
    {(double[]){3.14159, 2.71828}, (double[]){1.41421, 1.73205, 2.23607}, 2, 3},
    {(double[]){25.0, 50.0, 75.0}, (double[]){10.0, 20.0, 30.0, 40.0}, 3, 4},
    {(double[]){8.0, 6.0, 4.0, 2.0}, (double[]){9.0, 7.0, 5.0, 3.0, 1.0}, 4, 5},
    {(double[]){0.0}, (double[]){1.0, 2.0, 3.0}, 1, 3},
    {(double[]){-100.0, 100.0}, (double[]){-50.0, 50.0, 0.0}, 2, 3},
    {(double[]){99.9, 100.1}, (double[]){100.0}, 2, 1},
    {(double[]){1.0, 2.0, 3.0, 4.0, 5.0, 6.0}, (double[]){7.0, 8.0}, 6, 2},
    {(double[]){15.0, 25.0, 35.0}, (double[]){45.0, 55.0}, 3, 2},
    {(double[]){0.25, 0.5, 0.75}, (double[]){1.0, 1.25, 1.5, 1.75}, 3, 4},
    {(double[]){6.0, 12.0, 18.0}, (double[]){24.0, 30.0, 36.0, 42.0, 48.0}, 3, 5},
    {(double[]){-3.0, 0.0, 3.0}, (double[]){-6.0, 6.0}, 3, 2},
    {(double[]){10.0, 20.0, 30.0, 40.0, 50.0}, (double[]){60.0, 70.0, 80.0, 90.0, 100.0}, 5, 5},
    {(double[]){2.5}, (double[]){7.5, 12.5}, 1, 2}
};
int num_test_cases = 30;


    typedef struct {
        double result1;
        double result2;
        double** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z73Change(TestCase t1) {
TestCase follow_case = t1;
// --- 这是根据规则4生成的内存处理代码 ---
double* follow_case_data2 = (double*)malloc(t1.n2 * sizeof(double));
memcpy(follow_case_data2, t1.data2, t1.n2 * sizeof(double));
follow_case.data2 = follow_case_data2;
// ------------------------------------

// 这是根据规则6a生成的防御性代码，防止n2<1时出错
if (follow_case.n2 < 1) {
    // 元素不足1个，无法进行移位，直接返回副本
    return follow_case;
}

// 这是根据规则5生成的具体操作代码
double last_element = follow_case.data2[follow_case.n2 - 1];
for (int i = follow_case.n2 - 1; i > 0; i--) {
    follow_case.data2[i] = follow_case.data2[i - 1];
}
follow_case.data2[0] = last_element;

return follow_case;}

#include <cmath>
#include <cstddef>

int z73check(double result1, double result2) {
    // 1. 核心判断逻辑 (标量直接比较)
    // 条件: result1 == result2
    // 移项后: result1 == result2 (A = result1, B = result2)

    // 浮点数比较特殊处理
    double A = result1;
    double B = result2;

    // 防御 NaN
    if (std::isnan(A) || std::isnan(B)) return 0;

    // 处理无穷大
    if (std::isinf(A) || std::isinf(B)) {
        // 无穷大时退化为数学直接比较
        if (A == B) return 1;
        else return 0;
    }

    // 定义基础容差
    double epsilon = 1e-5;
    // 计算动态容差
    double tol = epsilon * std::fmax(1.0, std::fmax(std::fabs(A), std::fabs(B)));

    // 带容差的相等比较
    if (std::fabs(A - B) > tol) {
        return 0;
    }

    // 2. 满足条件，返回 1
    return 1;
}

TestResult z73runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z73Change(test_cases[test_case_id]);
    // 原始调用
    double source = pooledMean(test_cases[test_case_id].data1, test_cases[test_case_id].data2, test_cases[test_case_id].n1, test_cases[test_case_id].n2); // MODIFIED: Explicit type
    // 变换后调用
    double follow = pooledMean(follow_case.data1, follow_case.data2, follow_case.n1, follow_case.n2);
    
    double** memory_list = (double**)malloc(1 * sizeof(double*));
    memory_list[0] = follow_case.data2;
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z73check(source, follow);
    test_result.status = status;
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z73runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}