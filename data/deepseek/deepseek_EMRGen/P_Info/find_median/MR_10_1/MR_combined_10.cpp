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


double find_median(int a[], int n) {
    int k = n / 2 + 1;
    int minIndex = 0;
    int minValue = a[0];
    for (int i = 0; i < k; i++) {
        minIndex = i;
        minValue = a[i];
        for (int j = i + 1; j < n; j++) {
            if (a[j] < minValue) {
                minIndex = j;
                minValue = a[j];
            }
        }
        int temp = a[i];
        a[i] = a[minIndex];
        a[minIndex] = temp;
    }
    if (n % 2 == 0) {
        return (double) (a[n / 2 - 1] + a[n / 2]) / 2;
    } else {
        return a[n / 2];
    }
}


typedef struct {
    int* a; int n;
} TestCase;

TestCase test_cases[] = {
    {(int[]){1}, 1},
    {(int[]){1, 2}, 2},
    {(int[]){2, 1}, 2},
    {(int[]){1, 2, 3}, 3},
    {(int[]){3, 1, 2}, 3},
    {(int[]){3, 2, 1}, 3},
    {(int[]){1, 3, 2}, 3},
    {(int[]){1, 2, 3, 4}, 4},
    {(int[]){4, 3, 2, 1}, 4},
    {(int[]){2, 4, 1, 3}, 4},
    {(int[]){1, 2, 3, 4, 5}, 5},
    {(int[]){5, 4, 3, 2, 1}, 5},
    {(int[]){3, 5, 1, 4, 2}, 5},
    {(int[]){-1, 0, 1}, 3},
    {(int[]){10, 20, 30, 40}, 4},
    {(int[]){40, 10, 30, 20}, 4},
    {(int[]){7, 7, 7, 7, 7}, 5},
    {(int[]){1, 2, 3, 4, 5, 6}, 6},
    {(int[]){6, 5, 4, 3, 2, 1}, 6},
    {(int[]){2, 1, 4, 3, 6, 5}, 6},
    {(int[]){100, 200, 300}, 3},
    {(int[]){-5, -4, -3, -2, -1}, 5},
    {(int[]){0, 0, 0, 0}, 4},
    {(int[]){9, 1, 8, 2, 7, 3, 6, 4, 5}, 9},
    {(int[]){15, 25, 10, 30, 20}, 5},
    {(int[]){1, 2, 3, 4, 5, 6, 7}, 7},
    {(int[]){7, 6, 5, 4, 3, 2, 1}, 7},
    {(int[]){4, 2, 5, 1, 3, 6}, 6},
    {(int[]){8, 3, 9, 2, 7, 1}, 6},
    {(int[]){12, 15, 18, 21}, 4}
};
int num_test_cases = 30;


    typedef struct {
        double result1;
        double result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z10Change(TestCase t1) {
TestCase follow_case = t1;
// --- 这是根据规则4生成的内存处理代码 ---
int* follow_case_a = (int*)malloc(t1.n * sizeof(int));
memcpy(follow_case_a, t1.a, t1.n * sizeof(int));
follow_case.a = follow_case_a;
// ------------------------------------

// 这是根据规则6a生成的防御性代码，防止n<2时出错
if (follow_case.n < 2) {
    // 元素不足2个，无法进行随机重排序，直接返回副本
    return follow_case;
}

// 这是根据规则5生成的具体操作代码
srand(time(NULL)); // 初始化随机数种子
for (int i = follow_case.n - 1; i > 0; i--) {
    int j = rand() % (i + 1);
    int temp = follow_case.a[i];
    follow_case.a[i] = follow_case.a[j];
    follow_case.a[j] = temp;
}

return follow_case;}

#include <math.h>
#include <stddef.h>

int z10check(double result1, double result2) {
    // 1. 防御性编程 (标量版本无需空指针和长度检查)
    // 2. 核心判断逻辑 (标量直接比较)
    // 根据规则3，对浮点数进行特殊处理
    
    // 第一步：定义基础容差
    double epsilon = 1e-5;
    
    // 第二步：提取左右操作数 A 和 B（代数移项）
    // 条件: return.result1 == return.result2
    // 移项后: result1 == result2
    double A = result1;
    double B = result2;
    
    // 第三步：防御 NaN，并对 Inf 进行特殊放行
    if (isnan(A) || isnan(B)) return 0;
    
    // 处理无穷大情况
    if (isinf(A) || isinf(B)) {
        // 根据移项后的条件直接比较
        if (A == B) return 1;
        else return 0;
    }
    
    // 第四步：计算动态宽容度
    double tol = epsilon * fmax(1.0, fmax(fabs(A), fabs(B)));
    
    // 第五步：带容差的比较判定
    // 移项后的条件是相等 (==)
    if (fabs(A - B) > tol) {
        return 0;
    }
    
    // 3. 满足条件，返回 1
    return 1;
}

TestResult z10runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z10Change(test_cases[test_case_id]);
    // 原始调用
    double source = find_median(test_cases[test_case_id].a, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    double follow = find_median(follow_case.a, follow_case.n);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    memory_list[0] = follow_case.a;
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z10check(source, follow);
    test_result.status = status;
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z10runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}