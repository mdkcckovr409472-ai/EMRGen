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


double evaluateHoners(double coefficients[], double argument, int n) {
    
    double result = coefficients[n - 1];
    for (int j = n - 2; j >= 0; j--) {
        result = argument * result + coefficients[j];
    }
    return result;
}


typedef struct {
    double* coefficients; double argument; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0}, 2.0, 1},
    {(double[]){2.0, 1.0}, 3.0, 2},
    {(double[]){1.0, 2.0, 3.0}, 4.0, 3},
    {(double[]){-1.0, 0.0, 1.0}, 5.0, 3},
    {(double[]){0.5, -0.5, 1.5}, 0.0, 3},
    {(double[]){10.0, 20.0, 30.0, 40.0}, 1.0, 4},
    {(double[]){-2.0, -3.0, -4.0}, -1.0, 3},
    {(double[]){1.1, 2.2, 3.3}, 1.1, 3},
    {(double[]){0.0, 0.0, 0.0}, 100.0, 3},
    {(double[]){5.0}, 0.0, 1},
    {(double[]){-10.0, 20.0, -30.0, 40.0}, 2.0, 4},
    {(double[]){0.25, 0.5, 0.75, 1.0, 1.25}, 4.0, 5},
    {(double[]){1.0, -1.0, 1.0, -1.0}, 1.0, 4},
    {(double[]){3.14, 2.71}, 1.618, 2},
    {(double[]){100.0, 200.0, 300.0}, 0.5, 3},
    {(double[]){-1.5, 2.0, -2.5, 3.0}, -2.0, 4},
    {(double[]){7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0}, 1.0, 7},
    {(double[]){0.1, 0.2, 0.3, 0.4, 0.5}, 10.0, 5},
    {(double[]){-0.1, -0.2, -0.3}, -10.0, 3},
    {(double[]){2.0, 4.0, 6.0, 8.0}, 0.25, 4},
    {(double[]){9.0, 8.0, 7.0}, 1.5, 3},
    {(double[]){1.0, 0.0, 0.0, 0.0, 1.0}, 2.0, 5},
    {(double[]){-5.0, 10.0, -15.0}, 3.0, 3},
    {(double[]){0.0, 1.0, 0.0, 1.0}, -1.0, 4},
    {(double[]){6.0, 12.0, 18.0}, 0.333333, 3},
    {(double[]){2.5, 5.0, 7.5}, 2.0, 3},
    {(double[]){1.0, 2.0, 3.0, 4.0, 5.0, 6.0}, -2.0, 6},
    {(double[]){8.0, 4.0, 2.0, 1.0}, 0.5, 4},
    {(double[]){-1.0, -2.0, -3.0, -4.0}, -0.5, 4},
    {(double[]){15.0, 30.0, 45.0}, 1.0, 3}
};
int num_test_cases = 30;


    typedef struct {
        double result1;
        double result2;
        double** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z3Change(TestCase t1) {
TestCase follow_case = t1;
// --- 这是根据规则4生成的内存处理代码 ---
double* follow_case_coefficients = (double*)malloc(t1.n * sizeof(double));
memcpy(follow_case_coefficients, t1.coefficients, t1.n * sizeof(double));
follow_case.coefficients = follow_case_coefficients;
// ------------------------------------

// 这是根据规则6a生成的防御性代码，防止n<=0时出错
if (follow_case.n > 0) {
    // 这是根据规则5生成的具体操作代码
    for (int i = 0; i < follow_case.n; i++) {
        follow_case.coefficients[i] = follow_case.coefficients[i] * 2.0;
    }
}

return follow_case;}

#include <cmath>
#include <cfloat>

int z3check(double result1, double result2) {
    // 防御性编程：检查 NaN
    if (std::isnan(result1) || std::isnan(result2)) return 0;
    
    // 移项：2 * result1 - result2 == 0  ->  2 * result1 == result2
    double A = 2.0 * result1;
    double B = result2;
    
    // 处理无穷大情况
    if (std::isinf(A) || std::isinf(B)) {
        if (A == B) return 1;
        else return 0;
    }
    
    // 定义基础容差
    double epsilon = 1e-5;
    
    // 计算动态容差
    double tol = epsilon * fmax(1.0, fmax(fabs(A), fabs(B)));
    
    // 带容差的相等比较
    if (fabs(A - B) > tol) return 0;
    
    // 满足条件
    return 1;
}

TestResult z3runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z3Change(test_cases[test_case_id]);
    // 原始调用
    double source = evaluateHoners(test_cases[test_case_id].coefficients, test_cases[test_case_id].argument, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    double follow = evaluateHoners(follow_case.coefficients, follow_case.argument, follow_case.n);
    
    double** memory_list = (double**)malloc(1 * sizeof(double*));
    memory_list[0] = follow_case.coefficients;
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z3check(source, follow);
    test_result.status = status;
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z3runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}