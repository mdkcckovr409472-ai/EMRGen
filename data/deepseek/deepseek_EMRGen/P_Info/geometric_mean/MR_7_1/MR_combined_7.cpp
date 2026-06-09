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


double geometric_mean(int a[], int n) {
    long product = 1;
    for (int i = 0; i < n; i++) {
        product *= a[i];
    }
    return pow(product, (double) 1 / n);
}


typedef struct {
    int* a; int n;
} TestCase;

TestCase test_cases[] = {
    {(int[]){1, 2, 4}, 3},
    {(int[]){2, 8}, 2},
    {(int[]){3, 3, 3}, 3},
    {(int[]){1, 1, 1, 1}, 4},
    {(int[]){4, 9}, 2},
    {(int[]){10, 10, 10}, 3},
    {(int[]){5, 20}, 2},
    {(int[]){2, 4, 8}, 3},
    {(int[]){1, 3, 9}, 3},
    {(int[]){6, 6, 6, 6}, 4},
    {(int[]){7, 14}, 2},
    {(int[]){1, 4, 16}, 3},
    {(int[]){9, 16}, 2},
    {(int[]){2, 2, 2, 2, 2}, 5},
    {(int[]){3, 12}, 2},
    {(int[]){1, 5, 25}, 3},
    {(int[]){8, 27}, 2},
    {(int[]){4, 4, 4, 4}, 4},
    {(int[]){6, 24}, 2},
    {(int[]){1, 2, 4, 8}, 4},
    {(int[]){5, 5, 5}, 3},
    {(int[]){9, 9}, 2},
    {(int[]){2, 6, 18}, 3},
    {(int[]){7, 7, 7, 7}, 4},
    {(int[]){3, 6, 12}, 3},
    {(int[]){10, 40}, 2},
    {(int[]){1, 8, 64}, 3},
    {(int[]){4, 12}, 2},
    {(int[]){5, 10, 20}, 3},
    {(int[]){2, 3, 6}, 3}
};
int num_test_cases = 30;


    typedef struct {
        double result1;
        double result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z7Change(TestCase t1) {
    TestCase follow_case = t1;
    // --- 这是根据规则4生成的内存处理代码 ---
    int* follow_case_a = (int*)malloc(t1.n * sizeof(int));
    memcpy(follow_case_a, t1.a, t1.n * sizeof(int));
    follow_case.a = follow_case_a;
    // ------------------------------------

    // 这是根据规则6a生成的防御性代码，防止n<=0时出错
    if (follow_case.n > 0) {
        // 这是根据规则5生成的具体操作代码
        for (int i = 0; i < follow_case.n; i++) {
            follow_case.a[i] = 1;
        }
    }

    return follow_case;}

#include <cmath>
#include <cstddef>

int z7check(double result1, double result2) {
    // 1. 核心判断逻辑 (标量直接比较)
    // 条件为 result1 >= result2
    // 移项后：A = result1, B = result2, 比较符为 >=

    // 浮点数特殊处理流程
    double A = result1;
    double B = result2;

    // 防御 NaN
    if (std::isnan(A) || std::isnan(B)) return 0;

    // 处理无穷大情况
    if (std::isinf(A) || std::isinf(B)) {
        // 对于无穷大，退化为数学直接比较
        if (A >= B) return 1;
        else return 0;
    }

    // 定义基础容差
    const double epsilon = 1e-5;
    // 计算动态容差
    double tol = epsilon * std::fmax(1.0, std::fmax(std::fabs(A), std::fabs(B)));

    // 带容差的比较判定 (>=)
    // 若 A < B - tol，则违反条件
    if (A < B - tol) {
        return 0;
    }

    // 2. 满足条件，返回 1
    return 1;
}

TestResult z7runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z7Change(test_cases[test_case_id]);
    // 原始调用
    double source = geometric_mean(test_cases[test_case_id].a, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    double follow = geometric_mean(follow_case.a, follow_case.n);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    memory_list[0] = follow_case.a;
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z7check(source, follow);
    test_result.status = status;
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z7runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}