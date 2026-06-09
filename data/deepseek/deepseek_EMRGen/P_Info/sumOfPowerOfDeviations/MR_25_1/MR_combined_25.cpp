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


double sumOfPowerOfDeviations(double data[], int k, double c, int n) {
    double sum = 0;
    for(int i = 0; i < n; i++) {
        sum += pow(data[i] - c, k);
        }
    return sum;
}


typedef struct {
    double* data; int k; double c; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0, 2.0, 3.0}, 1, 2.5, 3},
    {(double[]){1.0, 2.0, 3.0}, 2, 2.5, 3},
    {(double[]){1.0, 2.0, 3.0}, 3, 2.5, 3},
    {(double[]){1.0, 2.0, 3.0}, 4, 2.5, 3},
    {(double[]){1.0, 2.0, 3.0}, 0, 2.5, 3},
    {(double[]){-1.0, -2.0, -3.0}, 1, -2.0, 3},
    {(double[]){-1.0, -2.0, -3.0}, 2, -2.0, 3},
    {(double[]){-1.0, -2.0, -3.0}, 3, -2.0, 3},
    {(double[]){-1.0, -2.0, -3.0}, 4, -2.0, 3},
    {(double[]){-1.0, -2.0, -3.0}, 0, -2.0, 3},
    {(double[]){0.0, 0.0, 0.0}, 1, 0.0, 3},
    {(double[]){0.0, 0.0, 0.0}, 2, 0.0, 3},
    {(double[]){0.0, 0.0, 0.0}, 3, 0.0, 3},
    {(double[]){0.0, 0.0, 0.0}, 4, 0.0, 3},
    {(double[]){0.0, 0.0, 0.0}, 0, 0.0, 3},
    {(double[]){2.5, 2.5, 2.5}, 1, 2.5, 3},
    {(double[]){2.5, 2.5, 2.5}, 2, 2.5, 3},
    {(double[]){2.5, 2.5, 2.5}, 3, 2.5, 3},
    {(double[]){2.5, 2.5, 2.5}, 4, 2.5, 3},
    {(double[]){2.5, 2.5, 2.5}, 0, 2.5, 3},
    {(double[]){1.1, 2.2, 3.3, 4.4}, 1, 2.75, 4},
    {(double[]){1.1, 2.2, 3.3, 4.4}, 2, 2.75, 4},
    {(double[]){1.1, 2.2, 3.3, 4.4}, 3, 2.75, 4},
    {(double[]){1.1, 2.2, 3.3, 4.4}, 4, 2.75, 4},
    {(double[]){1.1, 2.2, 3.3, 4.4}, 0, 2.75, 4},
    {(double[]){-1.5, 0.0, 1.5}, 1, 0.0, 3},
    {(double[]){-1.5, 0.0, 1.5}, 2, 0.0, 3},
    {(double[]){-1.5, 0.0, 1.5}, 3, 0.0, 3},
    {(double[]){-1.5, 0.0, 1.5}, 4, 0.0, 3},
    {(double[]){-1.5, 0.0, 1.5}, 0, 0.0, 3}
};
int num_test_cases = 30;


    typedef struct {
        double result1;
        double result2;
        double** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z25Change(TestCase t1) {
TestCase follow_case = t1;
// --- 这是根据规则4生成的内存处理代码 ---
double* follow_case_data = (double*)malloc(t1.n * sizeof(double));
memcpy(follow_case_data, t1.data, t1.n * sizeof(double));
follow_case.data = follow_case_data;
// ------------------------------------

// 这是根据规则6a生成的防御性代码，防止n<2时出错
if (follow_case.n < 2) {
    // 元素不足2个，无需排序，直接返回副本
    return follow_case;
}

// 这是根据规则5生成的具体操作代码
// 使用标准库qsort进行升序排序
qsort(follow_case.data, follow_case.n, sizeof(double), [](const void* a, const void* b) -> int {
    double arg1 = *static_cast<const double*>(a);
    double arg2 = *static_cast<const double*>(b);
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
});

return follow_case;}

#include <math.h>
#include <stddef.h>

int z25check(double result1, double result2) {
    // 浮点数比较：移项后条件为 result1 == result2
    double A = result1;
    double B = result2;
    
    // 防御 NaN
    if (isnan(A) || isnan(B)) return 0;
    
    // 处理无穷大
    if (isinf(A) || isinf(B)) {
        if (A == B) return 1;
        else return 0;
    }
    
    // 动态容差比较
    double epsilon = 1e-5;
    double tol = epsilon * fmax(1.0, fmax(fabs(A), fabs(B)));
    
    if (fabs(A - B) > tol) return 0;
    
    return 1;
}

TestResult z25runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z25Change(test_cases[test_case_id]);
    // 原始调用
    double source = sumOfPowerOfDeviations(test_cases[test_case_id].data, test_cases[test_case_id].k, test_cases[test_case_id].c, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    double follow = sumOfPowerOfDeviations(follow_case.data, follow_case.k, follow_case.c, follow_case.n);
    
    double** memory_list = (double**)malloc(1 * sizeof(double*));
    memory_list[0] = follow_case.data;
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z25check(source, follow);
    test_result.status = status;
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z25runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}