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


double manhattan_dist(int a[], int b[], int n) {
    int i;
    double sum = 0;
    for (i = 0; i < n; i++) {
        sum += abs(a[i] - b[i]);
    }
    return sum;
}


typedef struct {
    int* a; int* b; int n;
} TestCase;

TestCase test_cases[] = {
    {(int[]){0}, (int[]){0}, 1},
    {(int[]){1}, (int[]){2}, 1},
    {(int[]){-1}, (int[]){1}, 1},
    {(int[]){5}, (int[]){5}, 1},
    {(int[]){10}, (int[]){-10}, 1},
    {(int[]){1, 2}, (int[]){3, 4}, 2},
    {(int[]){-1, -2}, (int[]){-3, -4}, 2},
    {(int[]){0, 0}, (int[]){0, 0}, 2},
    {(int[]){100, 200}, (int[]){50, 150}, 2},
    {(int[]){-5, 10}, (int[]){5, -10}, 2},
    {(int[]){1, 2, 3}, (int[]){4, 5, 6}, 3},
    {(int[]){-1, -2, -3}, (int[]){-4, -5, -6}, 3},
    {(int[]){0, 0, 0}, (int[]){0, 0, 0}, 3},
    {(int[]){10, 20, 30}, (int[]){5, 15, 25}, 3},
    {(int[]){1, -1, 2}, (int[]){-1, 1, -2}, 3},
    {(int[]){1, 2, 3, 4}, (int[]){5, 6, 7, 8}, 4},
    {(int[]){-1, -2, -3, -4}, (int[]){-5, -6, -7, -8}, 4},
    {(int[]){0, 0, 0, 0}, (int[]){0, 0, 0, 0}, 4},
    {(int[]){100, 200, 300, 400}, (int[]){50, 150, 250, 350}, 4},
    {(int[]){1, 0, -1, 2}, (int[]){0, 1, 2, -1}, 4},
    {(int[]){1, 2, 3, 4, 5}, (int[]){6, 7, 8, 9, 10}, 5},
    {(int[]){-1, -2, -3, -4, -5}, (int[]){-6, -7, -8, -9, -10}, 5},
    {(int[]){0, 0, 0, 0, 0}, (int[]){0, 0, 0, 0, 0}, 5},
    {(int[]){2, 4, 6, 8, 10}, (int[]){1, 3, 5, 7, 9}, 5},
    {(int[]){5, -5, 10, -10, 15}, (int[]){-5, 5, -10, 10, -15}, 5},
    {(int[]){1, 2, 3, 4, 5, 6}, (int[]){7, 8, 9, 10, 11, 12}, 6},
    {(int[]){-1, -2, -3, -4, -5, -6}, (int[]){-7, -8, -9, -10, -11, -12}, 6},
    {(int[]){0, 0, 0, 0, 0, 0}, (int[]){0, 0, 0, 0, 0, 0}, 6},
    {(int[]){10, 20, 30, 40, 50, 60}, (int[]){5, 15, 25, 35, 45, 55}, 6},
    {(int[]){1, 0, 2, 0, 3, 0}, (int[]){0, 1, 0, 2, 0, 3}, 6}
};
int num_test_cases = 30;


    typedef struct {
        double result1;
        double result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z31Change(TestCase t1) {
TestCase follow_case = t1;
// --- 这是根据规则4生成的内存处理代码 ---
int* follow_case_b = (int*)malloc(t1.n * sizeof(int));
memcpy(follow_case_b, t1.b, t1.n * sizeof(int));
follow_case.b = follow_case_b;
// ------------------------------------

// 这是根据规则6a生成的防御性代码，防止n<=0时出错
if (follow_case.n > 0) {
    // 这是根据规则5生成的具体操作代码
    for (int i = 0; i < follow_case.n; i++) {
        follow_case.b[i] = follow_case.b[i] * 2;
    }
}

return follow_case;}

#include <math.h>
#include <stddef.h>

int z31check(double result1, double result2) {
    // 1. 防御性编程 (标量版本无需空指针和长度检查)
    
    // 2. 核心判断逻辑 (标量直接比较)
    // 条件: result1 <= result2
    
    // 浮点数特殊处理
    double epsilon = 1e-5;
    
    // 提取左右操作数 (已移项: result1 <= result2)
    double A = result1;
    double B = result2;
    
    // 防御NaN
    if (isnan(A) || isnan(B)) return 0;
    
    // 处理无穷大情况
    if (isinf(A) || isinf(B)) {
        // 直接数学比较
        if (A <= B) return 1;
        else return 0;
    }
    
    // 计算动态容差
    double tol = epsilon * fmax(1.0, fmax(fabs(A), fabs(B)));
    
    // 带容差的比较: A <= B
    if (A > B + tol) {
        return 0;  // 违反条件
    }
    
    // 3. 满足条件，返回 1
    return 1;
}

TestResult z31runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z31Change(test_cases[test_case_id]);
    // 原始调用
    double source = manhattan_dist(test_cases[test_case_id].a, test_cases[test_case_id].b, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    double follow = manhattan_dist(follow_case.a, follow_case.b, follow_case.n);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    memory_list[0] = follow_case.b;
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z31check(source, follow);
    test_result.status = status;
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z31runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}