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


double quantile(double sortedElements[], double phi, int n) {      
    double index = phi * (n - 1);
    int lhs = (int) index;
    double delta = index - lhs;
    double result;
    if (n == 0) {
        return 0.0;
    }
    if (lhs == n - 1) {
        result = sortedElements[lhs];
    } else {
        result = (1 - delta) * sortedElements[lhs] + delta * sortedElements[lhs + 1];
    }
    return result;
}


typedef struct {
    double* sortedElements; double phi; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0}, 0.0, 1},
    {(double[]){1.0}, 0.5, 1},
    {(double[]){1.0}, 1.0, 1},
    {(double[]){1.0, 2.0}, 0.0, 2},
    {(double[]){1.0, 2.0}, 0.25, 2},
    {(double[]){1.0, 2.0}, 0.5, 2},
    {(double[]){1.0, 2.0}, 0.75, 2},
    {(double[]){1.0, 2.0}, 1.0, 2},
    {(double[]){1.0, 2.0, 3.0}, 0.0, 3},
    {(double[]){1.0, 2.0, 3.0}, 0.2, 3},
    {(double[]){1.0, 2.0, 3.0}, 0.4, 3},
    {(double[]){1.0, 2.0, 3.0}, 0.5, 3},
    {(double[]){1.0, 2.0, 3.0}, 0.6, 3},
    {(double[]){1.0, 2.0, 3.0}, 0.8, 3},
    {(double[]){1.0, 2.0, 3.0}, 1.0, 3},
    {(double[]){-5.0, 0.0, 5.0}, 0.0, 3},
    {(double[]){-5.0, 0.0, 5.0}, 0.33, 3},
    {(double[]){-5.0, 0.0, 5.0}, 0.66, 3},
    {(double[]){-5.0, 0.0, 5.0}, 1.0, 3},
    {(double[]){1.5, 2.5, 3.5, 4.5}, 0.1, 4},
    {(double[]){1.5, 2.5, 3.5, 4.5}, 0.333, 4},
    {(double[]){1.5, 2.5, 3.5, 4.5}, 0.5, 4},
    {(double[]){1.5, 2.5, 3.5, 4.5}, 0.667, 4},
    {(double[]){1.5, 2.5, 3.5, 4.5}, 0.9, 4},
    {(double[]){10.0}, 0.001, 1},
    {(double[]){10.0}, 0.999, 1},
    {(double[]){0.0, 10.0, 20.0, 30.0, 40.0}, 0.125, 5},
    {(double[]){0.0, 10.0, 20.0, 30.0, 40.0}, 0.375, 5},
    {(double[]){0.0, 10.0, 20.0, 30.0, 40.0}, 0.625, 5},
    {(double[]){0.0, 10.0, 20.0, 30.0, 40.0}, 0.875, 5}
};
int num_test_cases = 30;


    typedef struct {
        double result1;
        double result2;
        double** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z2Change(TestCase t1) {
TestCase follow_case = t1;
// --- 这是根据规则4生成的内存处理代码 ---
double* follow_case_sortedElements = (double*)malloc(t1.n * sizeof(double));
memcpy(follow_case_sortedElements, t1.sortedElements, t1.n * sizeof(double));
follow_case.sortedElements = follow_case_sortedElements;
// ------------------------------------

// 这是根据规则6a生成的防御性代码，防止n<=0时出错
if (follow_case.n > 0) {
    // 这是根据规则5生成的具体操作代码
    for (int i = 0; i < follow_case.n; i++) {
        follow_case.sortedElements[i] = follow_case.sortedElements[i] - 1.0;
    }
}

return follow_case;}

#include <cmath>
#include <cfloat>

int z2check(double result1, double result2) {
    // 浮点数比较的特殊处理
    double epsilon = 1e-5;
    
    // 第一步：代数移项，恢复数据量级
    // 原条件: result1 - result2 - 1 == 0
    // 移项后: result1 == result2 + 1
    double A = result1;
    double B = result2 + 1.0;
    
    // 第二步：防御NaN
    if (std::isnan(A) || std::isnan(B)) return 0;
    
    // 第三步：处理无穷大
    if (std::isinf(A) || std::isinf(B)) {
        if (A == B) return 1;
        else return 0;
    }
    
    // 第四步：计算动态宽容度
    double tol = epsilon * fmax(1.0, fmax(fabs(A), fabs(B)));
    
    // 第五步：带容差的比较判定
    if (fabs(A - B) > tol) {
        return 0;
    }
    
    return 1;
}

TestResult z2runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z2Change(test_cases[test_case_id]);
    // 原始调用
    double source = quantile(test_cases[test_case_id].sortedElements, test_cases[test_case_id].phi, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    double follow = quantile(follow_case.sortedElements, follow_case.phi, follow_case.n);
    
    double** memory_list = (double**)malloc(1 * sizeof(double*));
    memory_list[0] = follow_case.sortedElements;
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z2check(source, follow);
    test_result.status = status;
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z2runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}