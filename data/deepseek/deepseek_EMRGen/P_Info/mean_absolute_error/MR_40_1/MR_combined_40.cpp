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


double mean_absolute_error(int a[], int b[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += abs(a[i] - b[i]);
    }
    return (double) sum / n;
}


typedef struct {
    int* a; int* b; int n;
} TestCase;

TestCase test_cases[] = {
    {(int[]){1, 2, 3}, (int[]){1, 2, 3}, 3},
    {(int[]){1, 2, 3}, (int[]){4, 5, 6}, 3},
    {(int[]){0, 0, 0}, (int[]){0, 0, 0}, 3},
    {(int[]){-1, -2, -3}, (int[]){-1, -2, -3}, 3},
    {(int[]){-1, -2, -3}, (int[]){1, 2, 3}, 3},
    {(int[]){10}, (int[]){5}, 1},
    {(int[]){5}, (int[]){10}, 1},
    {(int[]){100, 200}, (int[]){150, 250}, 2},
    {(int[]){7, 8, 9, 10}, (int[]){7, 8, 9, 10}, 4},
    {(int[]){7, 8, 9, 10}, (int[]){10, 9, 8, 7}, 4},
    {(int[]){1, 3, 5, 7, 9}, (int[]){2, 4, 6, 8, 10}, 5},
    {(int[]){2, 4, 6, 8, 10}, (int[]){1, 3, 5, 7, 9}, 5},
    {(int[]){0, 10, 20}, (int[]){5, 15, 25}, 3},
    {(int[]){-5, 0, 5}, (int[]){5, 0, -5}, 3},
    {(int[]){1}, (int[]){1}, 1},
    {(int[]){999}, (int[]){1}, 1},
    {(int[]){1, 2, 3, 4, 5, 6}, (int[]){0, 0, 0, 0, 0, 0}, 6},
    {(int[]){0, 0, 0, 0, 0, 0}, (int[]){1, 2, 3, 4, 5, 6}, 6},
    {(int[]){15, 25, 35}, (int[]){20, 30, 40}, 3},
    {(int[]){-10, -20, -30}, (int[]){-15, -25, -35}, 3},
    {(int[]){2, 4, 8, 16}, (int[]){1, 1, 1, 1}, 4},
    {(int[]){1, 1, 1, 1}, (int[]){2, 4, 8, 16}, 4},
    {(int[]){12, 24, 36}, (int[]){6, 12, 18}, 3},
    {(int[]){6, 12, 18}, (int[]){12, 24, 36}, 3},
    {(int[]){50, 60, 70, 80, 90}, (int[]){55, 65, 75, 85, 95}, 5},
    {(int[]){100, 101, 102}, (int[]){99, 100, 101}, 3},
    {(int[]){0, 1, 2, 3, 4, 5}, (int[]){5, 4, 3, 2, 1, 0}, 6},
    {(int[]){-7, 7, -14, 14}, (int[]){7, -7, 14, -14}, 4},
    {(int[]){9, 18, 27}, (int[]){9, 18, 27}, 3},
    {(int[]){33, 66, 99}, (int[]){22, 44, 66}, 3}
};
int num_test_cases = 30;


    typedef struct {
        double result1;
        double result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z40Change(TestCase t1) {
TestCase follow_case = t1;
// --- 这是根据规则4生成的内存处理代码 ---
int* follow_case_b = (int*)malloc(t1.n * sizeof(int));
memcpy(follow_case_b, t1.b, t1.n * sizeof(int));
follow_case.b = follow_case_b;
// ------------------------------------

// 这是根据规则6a生成的防御性代码，防止n<2时出错
if (follow_case.n < 2) {
    // 元素不足2个，无法进行两元素交换，直接返回副本
    return follow_case;
}

// 这是根据规则5生成的具体操作代码
int idx1 = rand() % follow_case.n;
int idx2 = rand() % follow_case.n;
int temp = follow_case.b[idx1];
follow_case.b[idx1] = follow_case.b[idx2];
follow_case.b[idx2] = temp;

return follow_case;}

#include <cmath>
#include <cfloat>

int z40check(double result1, double result2) {
    // 1. 核心判断逻辑 (标量直接比较)
    // 条件: result1 <= result2
    // 移项后: result1 <= result2 (无需移项)
    
    // 浮点数特殊处理
    double A = result1;
    double B = result2;
    
    // 防御NaN
    if (std::isnan(A) || std::isnan(B)) return 0;
    
    // 处理无穷大情况
    if (std::isinf(A) || std::isinf(B)) {
        // 无穷大时直接数学比较
        if (A <= B) return 1;
        else return 0;
    }
    
    // 定义基础容差
    double epsilon = 1e-5;
    
    // 计算动态容差
    double tol = epsilon * fmax(1.0, fmax(fabs(A), fabs(B)));
    
    // 带容差的 <= 比较
    // 条件: A <= B
    // 违反条件: A > B + tol
    if (A > B + tol) {
        return 0;
    }
    
    // 2. 满足条件，返回 1
    return 1;
}

TestResult z40runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z40Change(test_cases[test_case_id]);
    // 原始调用
    double source = mean_absolute_error(test_cases[test_case_id].a, test_cases[test_case_id].b, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    double follow = mean_absolute_error(follow_case.a, follow_case.b, follow_case.n);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    memory_list[0] = follow_case.b;
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z40check(source, follow);
    test_result.status = status;
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z40runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}