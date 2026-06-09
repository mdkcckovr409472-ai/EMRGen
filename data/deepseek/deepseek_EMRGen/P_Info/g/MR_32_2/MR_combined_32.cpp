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


double g( double expected[],  double observed[], int n) {
    double sumExpected = 0;
    double sumObserved = 0;
    for (int i = 0; i < n; i++) {
        sumExpected += expected[i];
        sumObserved += observed[i];
    }
    double ratio = 1;
    bool rescale = false;
    if (fabs(sumExpected - sumObserved) > 10E-6) {
        ratio = sumObserved / sumExpected;
        rescale = true;
    }
    double sum = 0;
        for (int i = 0; i < n; i++) {
            double dev = rescale ? log((double) observed[i] / (ratio * expected[i])) : log((double) observed[i] / expected[i]);
            sum += (double) observed[i] * dev;
        }
    return 2 * sum;
}



typedef struct {
    double* expected; double* observed; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0, 2.0, 3.0}, (double[]){1.0, 2.0, 3.0}, 3},
    {(double[]){4.0, 5.0, 6.0}, (double[]){4.0, 5.0, 6.0}, 3},
    {(double[]){10.0, 20.0, 30.0}, (double[]){9.0, 21.0, 31.0}, 3},
    {(double[]){2.5, 3.5}, (double[]){2.4, 3.6}, 2},
    {(double[]){100.0, 200.0}, (double[]){105.0, 195.0}, 2},
    {(double[]){0.5, 1.5, 2.5}, (double[]){0.55, 1.45, 2.55}, 3},
    {(double[]){7.0}, (double[]){7.0}, 1},
    {(double[]){7.0}, (double[]){7.5}, 1},
    {(double[]){1.0, 1.0, 1.0, 1.0}, (double[]){1.0, 1.0, 1.0, 1.0}, 4},
    {(double[]){1.0, 1.0, 1.0, 1.0}, (double[]){0.9, 1.1, 0.95, 1.05}, 4},
    {(double[]){3.14, 2.71}, (double[]){3.14, 2.71}, 2},
    {(double[]){3.14, 2.71}, (double[]){3.0, 2.8}, 2},
    {(double[]){0.1, 0.2, 0.3}, (double[]){0.1, 0.2, 0.3}, 3},
    {(double[]){0.1, 0.2, 0.3}, (double[]){0.12, 0.18, 0.28}, 3},
    {(double[]){8.0, 6.0, 7.0, 5.0}, (double[]){8.0, 6.0, 7.0, 5.0}, 4},
    {(double[]){8.0, 6.0, 7.0, 5.0}, (double[]){7.5, 6.5, 7.2, 4.8}, 4},
    {(double[]){50.0, 50.0}, (double[]){50.0, 50.0}, 2},
    {(double[]){50.0, 50.0}, (double[]){55.0, 45.0}, 2},
    {(double[]){12.0, 24.0, 36.0}, (double[]){12.0, 24.0, 36.0}, 3},
    {(double[]){12.0, 24.0, 36.0}, (double[]){11.0, 25.0, 37.0}, 3},
    {(double[]){9.8, 7.6}, (double[]){9.8, 7.6}, 2},
    {(double[]){9.8, 7.6}, (double[]){10.0, 7.4}, 2},
    {(double[]){15.0, 25.0, 35.0, 45.0}, (double[]){15.0, 25.0, 35.0, 45.0}, 4},
    {(double[]){15.0, 25.0, 35.0, 45.0}, (double[]){14.5, 25.5, 34.5, 45.5}, 4},
    {(double[]){2.0, 4.0, 8.0}, (double[]){2.0, 4.0, 8.0}, 3},
    {(double[]){2.0, 4.0, 8.0}, (double[]){2.1, 3.9, 8.05}, 3},
    {(double[]){6.0, 12.0, 18.0, 24.0, 30.0}, (double[]){6.0, 12.0, 18.0, 24.0, 30.0}, 5},
    {(double[]){6.0, 12.0, 18.0, 24.0, 30.0}, (double[]){5.5, 12.5, 17.5, 24.5, 30.0}, 5},
    {(double[]){0.01, 0.02, 0.03}, (double[]){0.01, 0.02, 0.03}, 3},
    {(double[]){0.01, 0.02, 0.03}, (double[]){0.009, 0.021, 0.029}, 3}
};
int num_test_cases = 30;


    typedef struct {
        double result1;
        double result2;
        double** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z32Change(TestCase t1) {
TestCase follow_case = t1;
// --- 这是根据规则4生成的内存处理代码 ---
double* follow_case_observed = (double*)malloc(t1.n * sizeof(double));
memcpy(follow_case_observed, t1.observed, t1.n * sizeof(double));
follow_case.observed = follow_case_observed;
// ------------------------------------

// 这是根据规则6a生成的防御性代码，防止n<=0时出错
if (follow_case.n > 0) {
    // 这是根据规则5生成的具体操作代码
    for (int i = 0; i < follow_case.n; i++) {
        follow_case.observed[i] = follow_case.observed[i] / 3.0;
    }
}

return follow_case;}

#include <cmath>
#include <cfloat>

int z32check(double result1, double result2) {
    // 1. 核心判断逻辑 (标量直接比较)
    // 条件: result1 >= result2
    // 移项后: A = result1, B = result2, 比较符 >=
    
    double A = result1;
    double B = result2;
    
    // 防御 NaN
    if (std::isnan(A) || std::isnan(B)) return 0;
    
    // 处理无穷大情况
    if (std::isinf(A) || std::isinf(B)) {
        // 直接数学比较
        if (A >= B) return 1;
        else return 0;
    }
    
    // 定义基础容差
    double epsilon = 1e-5;
    
    // 计算动态容差
    double tol = epsilon * fmax(1.0, fmax(fabs(A), fabs(B)));
    
    // 带容差的比较: A >= B
    // 违反条件: A < B - tol
    if (A < B - tol) {
        return 0;
    }
    
    // 2. 满足条件，返回 1
    return 1;
}

TestResult z32runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z32Change(test_cases[test_case_id]);
    // 原始调用
    double source = g(test_cases[test_case_id].expected, test_cases[test_case_id].observed, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    double follow = g(follow_case.expected, follow_case.observed, follow_case.n);
    
    double** memory_list = (double**)malloc(1 * sizeof(double*));
    memory_list[0] = follow_case.observed;
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z32check(source, follow);
    test_result.status = status;
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z32runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}