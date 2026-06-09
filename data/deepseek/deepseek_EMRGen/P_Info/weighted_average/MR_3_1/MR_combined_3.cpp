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


double weighted_average(double a[], double b[], int n) {
    double sum1 = 0;
    double sum2 = 0;
    for(int i = 0; i < n; i++) {
        sum1 += a[i] * b[i];
        sum2 += b[i];
    }
    return sum1 / sum2;
}


typedef struct {
    double* a; double* b; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0, 2.0, 3.0}, (double[]){1.0, 1.0, 1.0}, 3},
    {(double[]){5.0, 10.0, 15.0}, (double[]){2.0, 3.0, 5.0}, 3},
    {(double[]){-1.0, 0.0, 1.0}, (double[]){1.0, 2.0, 1.0}, 3},
    {(double[]){2.5, 3.5}, (double[]){4.0, 6.0}, 2},
    {(double[]){100.0, 200.0}, (double[]){0.5, 0.5}, 2},
    {(double[]){0.0, 0.0, 0.0}, (double[]){1.0, 2.0, 3.0}, 3},
    {(double[]){10.0}, (double[]){5.0}, 1},
    {(double[]){1.1, 2.2, 3.3, 4.4}, (double[]){0.1, 0.2, 0.3, 0.4}, 4},
    {(double[]){-2.0, -4.0, -6.0}, (double[]){1.0, 2.0, 3.0}, 3},
    {(double[]){3.0, 6.0, 9.0, 12.0}, (double[]){1.0, 2.0, 1.0, 2.0}, 4},
    {(double[]){7.0}, (double[]){3.0}, 1},
    {(double[]){0.5, 1.5, 2.5}, (double[]){2.0, 4.0, 6.0}, 3},
    {(double[]){8.0, 6.0, 4.0, 2.0}, (double[]){1.0, 1.0, 1.0, 1.0}, 4},
    {(double[]){9.0, 18.0}, (double[]){2.0, 4.0}, 2},
    {(double[]){1.0, 4.0, 9.0, 16.0}, (double[]){1.0, 2.0, 3.0, 4.0}, 4},
    {(double[]){2.0, 4.0, 8.0}, (double[]){0.25, 0.5, 0.25}, 3},
    {(double[]){-10.0, 10.0}, (double[]){3.0, 7.0}, 2},
    {(double[]){1.0, 2.0, 3.0, 4.0, 5.0}, (double[]){5.0, 4.0, 3.0, 2.0, 1.0}, 5},
    {(double[]){6.0, 12.0, 18.0}, (double[]){1.0, 2.0, 3.0}, 3},
    {(double[]){20.0, 40.0, 60.0}, (double[]){1.0, 2.0, 1.0}, 3},
    {(double[]){0.1, 0.2, 0.3}, (double[]){10.0, 20.0, 30.0}, 3},
    {(double[]){15.0, 25.0, 35.0}, (double[]){0.2, 0.3, 0.5}, 3},
    {(double[]){-1.5, -0.5, 0.5, 1.5}, (double[]){1.0, 2.0, 2.0, 1.0}, 4},
    {(double[]){50.0, 100.0}, (double[]){1.0, 3.0}, 2},
    {(double[]){1.0, 1.0, 1.0, 1.0}, (double[]){2.0, 3.0, 5.0, 7.0}, 4},
    {(double[]){12.0, 24.0, 36.0}, (double[]){0.5, 1.0, 1.5}, 3},
    {(double[]){0.0}, (double[]){5.0}, 1},
    {(double[]){2.0, 3.0, 5.0, 7.0}, (double[]){1.0, 1.0, 1.0, 1.0}, 4},
    {(double[]){30.0, 60.0, 90.0}, (double[]){1.0, 2.0, 3.0}, 3},
    {(double[]){4.0, 8.0, 12.0, 16.0, 20.0}, (double[]){1.0, 2.0, 3.0, 4.0, 5.0}, 5}
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
double* follow_case_a = (double*)malloc(t1.n * sizeof(double));
memcpy(follow_case_a, t1.a, t1.n * sizeof(double));
follow_case.a = follow_case_a;
// ------------------------------------

// 这是根据规则6a生成的防御性代码，防止n<=0时出错
if (follow_case.n > 0) {
    // 这是根据规则5生成的具体操作代码
    for (int i = 0; i < follow_case.n; i++) {
        follow_case.a[i] = follow_case.a[i] * 3.0;
    }
}

return follow_case;}

#include <cmath>
#include <cfloat>

int z3check(double result1, double result2) {
    // 浮点数比较的特殊处理
    double epsilon = 1e-5;
    
    // 代数移项：3 * result1 - result2 == 0 移项为 3 * result1 == result2
    double A = 3.0 * result1;
    double B = result2;
    
    // 防御 NaN
    if (std::isnan(A) || std::isnan(B)) return 0;
    
    // 处理无穷大情况（动态容差失效）
    if (std::isinf(A) || std::isinf(B)) {
        if (A == B) return 1;  // 移项后的相等比较
        else return 0;
    }
    
    // 计算动态容差
    double tol = epsilon * fmax(1.0, fmax(fabs(A), fabs(B)));
    
    // 带容差的相等比较（移项后是 ==）
    if (fabs(A - B) > tol) return 0;
    
    // 满足条件
    return 1;
}

TestResult z3runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z3Change(test_cases[test_case_id]);
    // 原始调用
    double source = weighted_average(test_cases[test_case_id].a, test_cases[test_case_id].b, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    double follow = weighted_average(follow_case.a, follow_case.b, follow_case.n);
    
    double** memory_list = (double**)malloc(1 * sizeof(double*));
    memory_list[0] = follow_case.a;
    
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