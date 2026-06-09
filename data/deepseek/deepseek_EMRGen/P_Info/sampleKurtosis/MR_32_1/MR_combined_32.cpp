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

TestCase z32Change(TestCase t1) {
TestCase follow_case = t1;

// 防御性编程：避免除以零
if (follow_case.sampleVariance == 0.0) {
    return follow_case;
}

// 具体操作：除10.0
follow_case.sampleVariance = follow_case.sampleVariance / 10.0;

return follow_case;}

#include <cmath>
#include <cstddef>

int z32check(double result1, double result2) {
    // 1. 防御性编程 (标量版本无需空指针和长度检查)
    
    // 2. 核心判断逻辑 (标量直接比较)
    // 条件: result1 <= result2
    
    // 第三步：防御 NaN，并对 Inf 进行特殊放行
    if (std::isnan(result1) || std::isnan(result2)) return 0;
    
    // 如果出现无穷大，动态容差会失效(Inf-Inf=NaN)，此时应退化为数学上的直接比较
    if (std::isinf(result1) || std::isinf(result2)) {
        if (result1 <= result2) return 1;
        else return 0;
    }
    
    // 第一步：定义基础容差
    double epsilon = 1e-5;
    
    // 第二步：提取左右操作数 A 和 B（已移项为 result1 <= result2）
    double A = result1;
    double B = result2;
    
    // 第四步：计算动态宽容度
    double tol = epsilon * fmax(1.0, fmax(fabs(A), fabs(B)));
    
    // 第五步：带容差的比较判定 (若违反则 return 0)
    // 条件为 A <= B，违反条件是 A > B + tol
    if (A > B + tol) {
        return 0;
    }
    
    // 3. 满足条件，返回 1
    return 1;
}

TestResult z32runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z32Change(test_cases[test_case_id]);
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