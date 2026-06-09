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


double sampleKurtosis(double moment4, double sampleVariance,int size) {
    int n = size;
    double s2 = sampleVariance;
    double m4 = moment4 * n;
    return m4 * n * (n + 1) / ((n - 1) * (n - 2) * (n - 3) * s2 * s2) - 3.0 * (n - 1) * (n - 1) / ((n - 2) * (n - 3));
}


typedef struct {
    double moment4; double sampleVariance; int size;
} TestCase;

TestCase test_cases[] = {
    {1.0, 1.0, 4},
    {2.5, 0.5, 5},
    {0.0, 0.1, 6},
    {10.0, 2.0, 7},
    {0.25, 0.25, 8},
    {5.0, 1.0, 9},
    {1.5, 3.0, 10},
    {8.0, 4.0, 11},
    {0.01, 0.05, 12},
    {15.0, 2.5, 13},
    {0.1, 1.0, 14},
    {4.0, 1.0, 15},
    {20.0, 5.0, 16},
    {0.5, 0.2, 17},
    {12.0, 3.0, 18},
    {0.0, 2.0, 19},
    {7.0, 1.4, 20},
    {0.75, 0.75, 21},
    {30.0, 6.0, 22},
    {0.2, 0.1, 23},
    {9.0, 1.8, 24},
    {0.0, 0.01, 25},
    {6.0, 1.2, 26},
    {1.0, 0.5, 27},
    {25.0, 5.0, 28},
    {0.05, 0.25, 29},
    {3.0, 0.6, 30},
    {18.0, 3.6, 31},
    {0.3, 0.15, 32},
    {11.0, 2.2, 33}
};
int num_test_cases = 30;


    typedef struct {
        double result1;
        double result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z51Change(TestCase t1) {
TestCase follow_case = t1;

// 防御性编程：避免除以零
if (follow_case.sampleVariance == 0.0) {
    return follow_case;
}

// 具体操作：除π
follow_case.sampleVariance = follow_case.sampleVariance / 3.14159265358979323846;

return follow_case;}

#include <cmath>
#include <cfloat>

int z51check(double result1, double result2) {
    // 1. 核心判断逻辑 (标量直接比较)
    // 条件: result1 <= result2
    
    // 提取移项后的操作数
    double A = result1;
    double B = result2;
    
    // 防御NaN
    if (std::isnan(A) || std::isnan(B)) return 0;
    
    // 处理无穷大情况
    if (std::isinf(A) || std::isinf(B)) {
        if (A <= B) return 1;
        else return 0;
    }
    
    // 定义基础容差
    double epsilon = 1e-5;
    
    // 计算动态宽容度
    double tol = epsilon * fmax(1.0, fmax(fabs(A), fabs(B)));
    
    // 带容差的比较判定 (<=)
    if (A > B + tol) {
        return 0;
    }
    
    // 2. 满足条件，返回 1
    return 1;
}

TestResult z51runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z51Change(test_cases[test_case_id]);
    // 原始调用
    double source = sampleKurtosis(test_cases[test_case_id].moment4, test_cases[test_case_id].sampleVariance, test_cases[test_case_id].size); // MODIFIED: Explicit type
    // 变换后调用
    double follow = sampleKurtosis(follow_case.moment4, follow_case.sampleVariance, follow_case.size);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z51check(source, follow);
    test_result.status = status;
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z51runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}