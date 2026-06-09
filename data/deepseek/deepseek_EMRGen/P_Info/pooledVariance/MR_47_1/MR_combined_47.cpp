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


double pooledVariance(double data1[], double data2[], int n1, int n2) {
    double sum1 = 0;
    double sumSq1 = 0;
    for (int i = 0; i < n1; i++) {
        sum1 += data1[i];
        sumSq1 += data1[i] * data1[i];
    }
    double mean1 = sum1 / n1;
    double var1 = (sumSq1 - mean1 * sum1) / n1;
    double sum2 = 0;
    double sumSq2 = 0;
    for (int i = 0; i < n2; i++) {
        sum2 += data2[i];
        sumSq2 += data2[i] * data2[i];
    }
    double mean2 = sum2 / n2;
    double var2 = (sumSq2 - mean2 * sum2) / n2;
    return (n1 * var1 + n2 * var2) / (n1 + n2);
}


typedef struct {
    double* data1; double* data2; int n1; int n2;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0, 2.0, 3.0}, (double[]){4.0, 5.0, 6.0}, 3, 3},
    {(double[]){0.0, 0.0, 0.0}, (double[]){0.0, 0.0, 0.0}, 3, 3},
    {(double[]){-1.0, 0.0, 1.0}, (double[]){-2.0, 0.0, 2.0}, 3, 3},
    {(double[]){10.5, 20.5, 30.5}, (double[]){15.5, 25.5, 35.5}, 3, 3},
    {(double[]){1.0}, (double[]){2.0}, 1, 1},
    {(double[]){1.0, 2.0, 3.0, 4.0, 5.0}, (double[]){6.0, 7.0, 8.0, 9.0, 10.0}, 5, 5},
    {(double[]){2.5, 3.5}, (double[]){4.5, 5.5, 6.5}, 2, 3},
    {(double[]){100.0, 200.0}, (double[]){150.0}, 2, 1},
    {(double[]){-10.0, -20.0, -30.0}, (double[]){-5.0, -15.0}, 3, 2},
    {(double[]){0.1, 0.2, 0.3}, (double[]){0.4, 0.5, 0.6, 0.7}, 3, 4},
    {(double[]){1.0, 1.0, 1.0, 1.0}, (double[]){2.0, 2.0, 2.0}, 4, 3},
    {(double[]){3.14, 6.28}, (double[]){1.57, 3.14, 4.71}, 2, 3},
    {(double[]){7.0}, (double[]){8.0, 9.0, 10.0}, 1, 3},
    {(double[]){-1.5, 1.5}, (double[]){-3.0, 0.0, 3.0}, 2, 3},
    {(double[]){12.0, 24.0, 36.0, 48.0}, (double[]){6.0, 18.0}, 4, 2},
    {(double[]){5.0, 10.0, 15.0}, (double[]){5.0, 10.0, 15.0}, 3, 3},
    {(double[]){2.0, 4.0, 8.0}, (double[]){1.0, 3.0, 9.0, 27.0}, 3, 4},
    {(double[]){0.0}, (double[]){1.0}, 1, 1},
    {(double[]){-100.0, 100.0}, (double[]){-50.0, 50.0}, 2, 2},
    {(double[]){9.9, 8.8, 7.7}, (double[]){6.6, 5.5, 4.4, 3.3}, 3, 4},
    {(double[]){20.0, 40.0}, (double[]){10.0, 30.0, 50.0, 70.0}, 2, 4},
    {(double[]){1.1, 2.2}, (double[]){3.3, 4.4, 5.5}, 2, 3},
    {(double[]){0.5, 1.0, 1.5, 2.0, 2.5}, (double[]){3.0, 3.5}, 5, 2},
    {(double[]){6.0, 12.0, 18.0}, (double[]){24.0, 30.0, 36.0, 42.0, 48.0}, 3, 5},
    {(double[]){-0.1, -0.2, -0.3}, (double[]){-0.4, -0.5}, 3, 2},
    {(double[]){15.0, 25.0, 35.0, 45.0}, (double[]){10.0, 20.0, 30.0, 40.0, 50.0}, 4, 5},
    {(double[]){2.0, 2.0}, (double[]){4.0, 4.0, 4.0}, 2, 3},
    {(double[]){11.0, 22.0, 33.0}, (double[]){44.0, 55.0}, 3, 2},
    {(double[]){0.25, 0.75}, (double[]){1.25, 1.75, 2.25}, 2, 3},
    {(double[]){8.0, 6.0, 4.0, 2.0}, (double[]){9.0, 7.0, 5.0, 3.0, 1.0}, 4, 5}
};
int num_test_cases = 30;


    typedef struct {
        double result1;
        double result2;
        double** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z47Change(TestCase t1) {
TestCase follow_case = t1;
// --- 这是根据规则4生成的内存处理代码 ---
double* follow_case_data2 = (double*)malloc(t1.n2 * sizeof(double));
memcpy(follow_case_data2, t1.data2, t1.n2 * sizeof(double));
follow_case.data2 = follow_case_data2;
// ------------------------------------

// 这是根据规则6a生成的防御性代码，防止n2<=0时出错
if (follow_case.n2 > 0) {
    // 这是根据规则5生成的具体操作代码
    for (int i = 0; i < follow_case.n2; i++) {
        follow_case.data2[i] = fabs(follow_case.data2[i]);
    }
}

return follow_case;}

#include <cmath>
#include <cfloat>

int z47check(double result1, double result2) {
    // 1. 核心判断逻辑 (标量直接比较)
    // 条件: result1 >= result2
    // 移项后: result1 >= result2 (已满足两侧分布)

    // 提取操作数
    double A = result1;
    double B = result2;

    // 防御NaN
    if (std::isnan(A) || std::isnan(B)) return 0;

    // 处理无穷大情况
    if (std::isinf(A) || std::isinf(B)) {
        // 无穷大时直接数学比较
        if (A >= B) return 1;
        else return 0;
    }

    // 定义基础容差
    double epsilon = 1e-5;
    // 计算动态容差
    double tol = epsilon * fmax(1.0, fmax(fabs(A), fabs(B)));

    // 带容差的比较: 检查是否违反 A >= B
    // 违反条件为: A < B - tol
    if (A < B - tol) {
        return 0;
    }

    // 2. 满足条件，返回 1
    return 1;
}

TestResult z47runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z47Change(test_cases[test_case_id]);
    // 原始调用
    double source = pooledVariance(test_cases[test_case_id].data1, test_cases[test_case_id].data2, test_cases[test_case_id].n1, test_cases[test_case_id].n2); // MODIFIED: Explicit type
    // 变换后调用
    double follow = pooledVariance(follow_case.data1, follow_case.data2, follow_case.n1, follow_case.n2);
    
    double** memory_list = (double**)malloc(1 * sizeof(double*));
    memory_list[0] = follow_case.data2;
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z47check(source, follow);
    test_result.status = status;
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z47runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}