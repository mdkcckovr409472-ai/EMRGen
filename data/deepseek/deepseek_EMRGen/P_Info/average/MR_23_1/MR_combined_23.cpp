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


double average(int a[], int n){
    double suma = 0;
    for (int i = 0; i < n; i++)
    {
        suma += a[i];
    }
    return suma/n;
}


typedef struct {
    int* a; int n;
} TestCase;

TestCase test_cases[] = {
    {(int[]){1, 2, 3, 4, 5}, 5},
    {(int[]){10}, 1},
    {(int[]){0, 0, 0}, 3},
    {(int[]){-1, 0, 1}, 3},
    {(int[]){2, 4, 6, 8}, 4},
    {(int[]){-5, -4, -3, -2, -1}, 5},
    {(int[]){100, 200, 300}, 3},
    {(int[]){1, -1, 2, -2}, 4},
    {(int[]){7, 11, 13, 17, 19}, 5},
    {(int[]){0}, 1},
    {(int[]){15, 25, 35, 45}, 4},
    {(int[]){-10, -20, -30}, 3},
    {(int[]){1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 10},
    {(int[]){50, 100, 150, 200, 250}, 5},
    {(int[]){-7, 7, -14, 14}, 4},
    {(int[]){3, 6, 9, 12, 15, 18}, 6},
    {(int[]){-100, 0, 100}, 3},
    {(int[]){1, 3, 5, 7, 9, 11, 13}, 7},
    {(int[]){20, 40, 60, 80, 100, 120}, 6},
    {(int[]){-2, -1, 0, 1, 2}, 5},
    {(int[]){5, 10, 15, 20, 25, 30, 35}, 7},
    {(int[]){-50, -25, 0, 25, 50}, 5},
    {(int[]){8, 4, 2, 1}, 4},
    {(int[]){12, 24, 36, 48, 60}, 5},
    {(int[]){-3, -6, -9, -12}, 4},
    {(int[]){9, 18, 27}, 3},
    {(int[]){0, 5, 10, 15, 20, 25}, 6},
    {(int[]){-15, -10, -5, 0, 5, 10, 15}, 7},
    {(int[]){6, 12, 18, 24, 30, 36, 42, 48}, 8},
    {(int[]){1, 4, 9, 16, 25}, 5}
};
int num_test_cases = 30;


    typedef struct {
        double result1;
        double result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z23Change(TestCase t1) {
    TestCase follow_case = t1;
    // --- 这是根据规则4生成的内存处理代码 ---
    int* follow_case_a = (int*)malloc(t1.n * sizeof(int));
    memcpy(follow_case_a, t1.a, t1.n * sizeof(int));
    follow_case.a = follow_case_a;
    // ------------------------------------

    // 这是根据规则6a生成的防御性代码，防止n<=0时出错
    if (follow_case.n > 0) {
        // 这是根据规则5生成的具体操作代码
        int half = follow_case.n / 2; // 向下取整
        for (int i = 0; i < half; i++) {
            follow_case.a[i] += 1;
        }
    }

    return follow_case;}

#include <cmath>
#include <cfloat>

int z23check(double result1, double result2) {
    // 1. 核心判断逻辑 (标量直接比较)
    // 条件: result1 <= result2
    // 移项后: A = result1, B = result2, 比较符为 <=

    double A = result1;
    double B = result2;

    // 防御 NaN
    if (std::isnan(A) || std::isnan(B)) return 0;

    // 处理无穷大
    if (std::isinf(A) || std::isinf(B)) {
        // 无穷大时退化为数学直接比较
        if (A <= B) return 1;
        else return 0;
    }

    // 定义基础容差
    double epsilon = 1e-5;
    // 计算动态宽容度
    double tol = epsilon * fmax(1.0, fmax(fabs(A), fabs(B)));

    // 带容差的 <= 判断: 若 A > B + tol 则违反
    if (A > B + tol) {
        return 0;
    }

    // 2. 满足条件，返回 1
    return 1;
}

TestResult z23runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z23Change(test_cases[test_case_id]);
    // 原始调用
    double source = average(test_cases[test_case_id].a, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    double follow = average(follow_case.a, follow_case.n);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    memory_list[0] = follow_case.a;
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z23check(source, follow);
    test_result.status = status;
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z23runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}