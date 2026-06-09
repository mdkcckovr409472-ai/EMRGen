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


double* calculateAbsoluteDifferences(double z[], int n){
    if (n == 0)
    {
        return NULL;
    }
    
    double* zAbs = (double*)malloc(n * sizeof(double));
    for (int i = 0; i < n; i++)
    {
        zAbs[i] = fabs(z[i]);
    }
    return zAbs;
}


typedef struct {
    double* z; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0, 2.0, 3.0}, 3},
    {(double[]){-1.0, -2.0, -3.0}, 3},
    {(double[]){0.0, 0.0, 0.0}, 3},
    {(double[]){-5.5, 10.2, -3.7}, 3},
    {(double[]){1.5}, 1},
    {(double[]){-1.5}, 1},
    {(double[]){0.0}, 1},
    {(double[]){100.0, -100.0}, 2},
    {(double[]){3.14159, -2.71828}, 2},
    {(double[]){1.1, 2.2, 3.3, 4.4}, 4},
    {(double[]){-1.1, -2.2, -3.3, -4.4}, 4},
    {(double[]){0.1, -0.1, 0.01, -0.01}, 4},
    {(double[]){-10.0, 20.0, -30.0, 40.0, -50.0}, 5},
    {(double[]){0.5, -0.5, 1.0, -1.0, 1.5, -1.5}, 6},
    {(double[]){2.0}, 1},
    {(double[]){-2.0}, 1},
    {(double[]){1.0, -1.0}, 2},
    {(double[]){10.0, 0.0, -10.0}, 3},
    {(double[]){0.25, -0.75, 1.25}, 3},
    {(double[]){-0.001, 0.001}, 2},
    {(double[]){999.999, -999.999}, 2},
    {(double[]){1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0}, 10},
    {(double[]){-1.0, -2.0, -3.0, -4.0, -5.0, -6.0, -7.0, -8.0, -9.0, -10.0}, 10},
    {(double[]){1.2, -3.4, 5.6, -7.8, 9.0}, 5},
    {(double[]){-1.2, 3.4, -5.6, 7.8, -9.0}, 5},
    {(double[]){0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, 6},
    {(double[]){12.34}, 1},
    {(double[]){-56.78}, 1},
    {(double[]){1.0, 0.0, -1.0, 0.5, -0.5}, 5},
    {(double[]){-1000.0, 500.0, -250.0, 125.0}, 4}
};
int num_test_cases = 30;


    typedef struct {
        double* result1;
        double* result2;
        double** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z13Change(TestCase t1) {
    TestCase follow_case = t1;
    // --- 这是根据规则4生成的内存处理代码 ---
    double* follow_case_z = (double*)malloc(t1.n * sizeof(double));
    memcpy(follow_case_z, t1.z, t1.n * sizeof(double));
    follow_case.z = follow_case_z;
    // ------------------------------------

    // 这是根据规则6a生成的防御性代码，防止n<=0时出错
    if (follow_case.n <= 0) {
        // 数组为空或长度为负，无法选择随机位置，直接返回副本
        return follow_case;
    }

    // 这是根据规则5生成的具体操作代码
    int random_index = rand() % follow_case.n;
    follow_case.z[random_index] = INFINITY;

    return follow_case;}

#include <cmath>
#include <cfloat>

int z13check(double* result1, double* result2, int n) {
    // 1. 防御性编程 (空指针与长度检查)
    if (result1 == NULL || result2 == NULL) return 0;
    if (n <= 0) return 1;

    // 2. 字典序比较逻辑 (lexically)
    // 基础容差
    double epsilon = 1e-5;

    for (int i = 0; i < n; i++) {
        // 提取移项后的操作数 A = result1[i], B = result2[i] (条件为 result1[i] < result2[i])
        double A = result1[i];
        double B = result2[i];

        // 防御 NaN
        if (std::isnan(A) || std::isnan(B)) return 0;

        // 处理无穷大
        if (std::isinf(A) || std::isinf(B)) {
            // 无穷大时退化为直接数学比较
            if (A < B) {
                // 在第一个不相等的元素处，result1[i] < result2[i]，字典序成立，立即返回1
                return 1;
            } else if (A > B) {
                // 在第一个不相等的元素处，result1[i] > result2[i]，字典序不成立，立即返回0
                return 0;
            }
            // 如果相等（都是正无穷或都是负无穷），继续检查下一个元素
            continue;
        }

        // 计算动态容差
        double tol = epsilon * fmax(1.0, fmax(fabs(A), fabs(B)));

        // 判断 A < B 是否成立（带容差）
        if (A < B - tol) {
            // 在第一个满足 result1[i] < result2[i] 的元素处，字典序成立，立即返回1
            return 1;
        } else if (A > B + tol) {
            // 在第一个满足 result1[i] > result2[i] 的元素处，字典序不成立，立即返回0
            return 0;
        }
        // 如果 A 和 B 在容差范围内视为相等，则继续检查下一个元素
    }

    // 3. 循环结束，所有元素在容差内都相等，严格小于条件不满足
    return 0;
}

TestResult z13runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z13Change(test_cases[test_case_id]);
    // 原始调用
    double* source = calculateAbsoluteDifferences(test_cases[test_case_id].z, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    double* follow = calculateAbsoluteDifferences(follow_case.z, follow_case.n);
    
    double** memory_list = (double**)malloc(1 * sizeof(double*));
    memory_list[0] = follow_case.z;
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z13check(source, follow, test_cases[test_case_id].n);
    test_result.status = status;
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z13runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}