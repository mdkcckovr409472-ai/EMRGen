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


double find_magnitude(int a[], int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i] * a[i];
    }
    double result = sqrt(sum);
    return result;
}


typedef struct {
    int* a; int n;
} TestCase;

TestCase test_cases[] = {
    {(int[]){0}, 1},
    {(int[]){1}, 1},
    {(int[]){-1}, 1},
    {(int[]){3, 4}, 2},
    {(int[]){-3, 4}, 2},
    {(int[]){3, -4}, 2},
    {(int[]){-3, -4}, 2},
    {(int[]){1, 2, 2}, 3},
    {(int[]){-1, -2, -2}, 3},
    {(int[]){1, 0, -1}, 3},
    {(int[]){5, 12}, 2},
    {(int[]){8, 15}, 2},
    {(int[]){7, 24}, 2},
    {(int[]){1, 1, 1, 1}, 4},
    {(int[]){2, 4, 4, 3, 2}, 5},
    {(int[]){-2, 4, -4, 3, -2}, 5},
    {(int[]){10}, 1},
    {(int[]){-10}, 1},
    {(int[]){6, 8, 10}, 3},
    {(int[]){-6, 8, -10}, 3},
    {(int[]){1, 2, 3, 4, 5}, 5},
    {(int[]){-1, 2, -3, 4, -5}, 5},
    {(int[]){9, 12, 15}, 3},
    {(int[]){0, 0, 0, 0}, 4},
    {(int[]){1, -1, 1, -1, 1}, 5},
    {(int[]){2, 3, 6}, 3},
    {(int[]){-2, -3, -6}, 3},
    {(int[]){20, 21}, 2},
    {(int[]){-20, 21}, 2},
    {(int[]){11, 60, 61}, 3}
};
int num_test_cases = 30;


    typedef struct {
        double result1;
        double result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z24Change(TestCase t1) {
TestCase follow_case = t1;
// --- 这是根据规则4生成的内存处理代码 ---
int* follow_case_a = (int*)malloc(t1.n * sizeof(int));
memcpy(follow_case_a, t1.a, t1.n * sizeof(int));
follow_case.a = follow_case_a;
// ------------------------------------

// 这是根据规则6a生成的防御性代码，防止n<=1时排序无意义
if (follow_case.n <= 1) {
    // 元素不足2个，无需排序，直接返回副本
    return follow_case;
}

// 这是根据规则5生成的具体操作代码（降序排序）
for (int i = 0; i < follow_case.n - 1; i++) {
    for (int j = 0; j < follow_case.n - i - 1; j++) {
        if (follow_case.a[j] < follow_case.a[j + 1]) {
            int temp = follow_case.a[j];
            follow_case.a[j] = follow_case.a[j + 1];
            follow_case.a[j + 1] = temp;
        }
    }
}

return follow_case;}

#include <math.h>
#include <stddef.h>

int z24check(double result1, double result2) {
    // 1. 防御性编程 (针对标量，无需空指针和长度检查)
    // 2. 核心判断逻辑 (标量直接比较)
    // 浮点数比较特殊处理
    double epsilon = 1e-5;
    
    // 提取左右操作数 A 和 B (代数移项)
    // 条件: return.result1 == return.result2
    // 移项后: result1 == result2
    double A = result1;
    double B = result2;
    
    // 防御 NaN
    if (isnan(A) || isnan(B)) return 0;
    
    // 处理无穷大 (Inf)
    if (isinf(A) || isinf(B)) {
        // 对于无穷大，退化为数学上的直接比较
        if (A == B) return 1;
        else return 0;
    }
    
    // 计算动态宽容度
    double tol = epsilon * fmax(1.0, fmax(fabs(A), fabs(B)));
    
    // 带容差的相等判定 (若违反则 return 0)
    if (fabs(A - B) > tol) {
        return 0;
    }
    
    // 3. 满足条件，返回 1
    return 1;
}

TestResult z24runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z24Change(test_cases[test_case_id]);
    // 原始调用
    double source = find_magnitude(test_cases[test_case_id].a, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    double follow = find_magnitude(follow_case.a, follow_case.n);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    memory_list[0] = follow_case.a;
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z24check(source, follow);
    test_result.status = status;
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z24runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}