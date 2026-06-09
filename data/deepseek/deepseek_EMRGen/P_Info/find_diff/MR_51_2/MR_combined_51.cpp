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


int*  find_diff(int a[], int b[], int na) {
    int* c = (int*)malloc(na * sizeof(int));
    for (int i = 0; i < na; i++) {
        c[i] = a[i] - b[i];
    }
    return c;
}


typedef struct {
    int* a; int* b; int na;
} TestCase;

TestCase test_cases[] = {
    {(int[]){1, 2, 3}, (int[]){4, 5, 6}, 3},
    {(int[]){10, 20}, (int[]){5, 15}, 2},
    {(int[]){0, 0, 0}, (int[]){0, 0, 0}, 3},
    {(int[]){-1, -2, -3}, (int[]){-4, -5, -6}, 3},
    {(int[]){100, 200}, (int[]){50, 150}, 2},
    {(int[]){7}, (int[]){3}, 1},
    {(int[]){15, 25, 35}, (int[]){10, 20, 30}, 3},
    {(int[]){-10, 10}, (int[]){-5, 5}, 2},
    {(int[]){2, 4, 6, 8}, (int[]){1, 3, 5, 7}, 4},
    {(int[]){0}, (int[]){100}, 1},
    {(int[]){50, 60, 70}, (int[]){20, 30, 40}, 3},
    {(int[]){-100, -200}, (int[]){-50, -250}, 2},
    {(int[]){9, 18, 27}, (int[]){6, 12, 18}, 3},
    {(int[]){33, 66}, (int[]){11, 22}, 2},
    {(int[]){1, 3, 5, 7, 9}, (int[]){0, 2, 4, 6, 8}, 5},
    {(int[]){-7, -14, -21}, (int[]){-3, -6, -9}, 3},
    {(int[]){1000, 2000}, (int[]){500, 1500}, 2},
    {(int[]){12, 24, 36, 48}, (int[]){6, 12, 18, 24}, 4},
    {(int[]){-25, 0, 25}, (int[]){-10, 10, 0}, 3},
    {(int[]){8, 16, 24, 32, 40}, (int[]){4, 8, 12, 16, 20}, 5},
    {(int[]){99, 88, 77}, (int[]){66, 55, 44}, 3},
    {(int[]){-1, 0, 1}, (int[]){1, 0, -1}, 3},
    {(int[]){45, 90}, (int[]){15, 30}, 2},
    {(int[]){6, 12, 18, 24, 30, 36}, (int[]){1, 2, 3, 4, 5, 6}, 6},
    {(int[]){-50, 50, -50}, (int[]){-25, 25, -25}, 3},
    {(int[]){19, 38, 57}, (int[]){9, 18, 27}, 3},
    {(int[]){100, 101, 102}, (int[]){1, 2, 3}, 3},
    {(int[]){-99, -88, -77, -66}, (int[]){-33, -22, -11, 0}, 4},
    {(int[]){14, 28, 42, 56, 70}, (int[]){7, 14, 21, 28, 35}, 5},
    {(int[]){0, -10, 10, -20}, (int[]){5, -5, 15, -15}, 4}
};
int num_test_cases = 30;


    typedef struct {
        int* result1;
        int* result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z51Change(TestCase t1) {
TestCase follow_case = t1;
// --- 这是根据规则4生成的内存处理代码 ---
int* follow_case_b = (int*)malloc(t1.na * sizeof(int));
memcpy(follow_case_b, t1.b, t1.na * sizeof(int));
follow_case.b = follow_case_b;
// ------------------------------------

// 这是根据规则6a生成的防御性代码，防止na<=0时出错
if (follow_case.na <= 0) {
    // 数组为空或长度无效，直接返回副本
    return follow_case;
}

// 这是根据规则5生成的具体操作代码
for (int i = 0; i < follow_case.na; i++) {
    if (i % 2 == 1) { // 检查是否为奇数位置（索引从0开始）
        follow_case.b[i] -= 5;
    }
}

return follow_case;}

int z51check(int* result1, int* result2, int n) {
    // 1. 防御性编程 (空指针与长度检查)
    if (result1 == NULL || result2 == NULL) return 0;
    if (n <= 0) return 1;

    // 2. 核心判断逻辑 (elementwise)
    // 条件为 result1[][0..0] == result2[][0..0]，切片 [0..0] 表示只比较索引 0 处的单个元素。
    // 因此，直接对索引 0 进行单次判断，无需循环。
    // 注意：需要确保数组长度 n > 0（已由防御性检查保证）。
    if (!(result1[0] == result2[0])) {
        return 0; // 一旦违反条件，立即返回 0
    }

    // 3. 全部满足，返回 1
    return 1;
}

TestResult z51runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z51Change(test_cases[test_case_id]);
    // 原始调用
    int* source = find_diff(test_cases[test_case_id].a, test_cases[test_case_id].b, test_cases[test_case_id].na); // MODIFIED: Explicit type
    // 变换后调用
    int* follow = find_diff(follow_case.a, follow_case.b, follow_case.na);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    memory_list[0] = follow_case.b;
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z51check(source, follow, test_cases[test_case_id].na);
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