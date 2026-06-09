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
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z83Change(TestCase t1) {
TestCase follow_case = t1;

// 根据规则5生成的具体操作代码
follow_case.c = follow_case.c - 10.5;

return follow_case;}

#include <cmath>
#include <cstddef>

int z83check(double result1, double result2) {
    // 1. 核心判断逻辑 (标量直接比较)
    // 条件: result1 <= result2
    // 移项后: result1 <= result2 (无需移项)
    double A = result1;
    double B = result2;

    // 防御 NaN
    if (std::isnan(A) || std::isnan(B)) return 0;

    // 处理无穷大
    if (std::isinf(A) || std::isinf(B)) {
        // 对于无穷大，退化为精确数学比较
        if (A <= B) return 1;
        else return 0;
    }

    // 定义基础容差
    const double epsilon = 1e-5;
    // 计算动态容差
    double tol = epsilon * std::fmax(1.0, std::fmax(std::fabs(A), std::fabs(B)));

    // 带容差的比较: A <= B
    // 违反条件: A > B + tol
    if (A > B + tol) {
        return 0;
    }

    // 2. 满足条件，返回 1
    return 1;
}

TestResult z83runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z83Change(test_cases[test_case_id]);
    // 原始调用
    double source = sumOfPowerOfDeviations(test_cases[test_case_id].data, test_cases[test_case_id].k, test_cases[test_case_id].c, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    double follow = sumOfPowerOfDeviations(follow_case.data, follow_case.k, follow_case.c, follow_case.n);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z83check(source, follow);
    test_result.status = status;
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z83runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}