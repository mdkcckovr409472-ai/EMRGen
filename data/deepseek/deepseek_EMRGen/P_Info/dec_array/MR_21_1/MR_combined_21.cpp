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


int* dec_array(int a[], int k, int n) {
    int* cp1 = (int*)malloc(n * sizeof(int));
    memcpy(cp1,a,n*sizeof(int));
    for (int i = 0; i < n; i++) {
        cp1[i] -= k;
    }
    return cp1;
}


typedef struct {
    int* a; int k; int n;
} TestCase;

TestCase test_cases[] = {
    {(int[]){1, 2, 3}, 1, 3},
    {(int[]){5, 10, 15}, 5, 3},
    {(int[]){0, 0, 0}, 3, 3},
    {(int[]){-1, -2, -3}, 1, 3},
    {(int[]){100, 200}, 50, 2},
    {(int[]){7}, 7, 1},
    {(int[]){-5, 0, 5}, 2, 3},
    {(int[]){1, 1, 1, 1}, 0, 4},
    {(int[]){10, 20, 30, 40, 50}, 10, 5},
    {(int[]){-10, -20, -30}, -5, 3},
    {(int[]){2, 4, 6, 8}, 1, 4},
    {(int[]){15, 25, 35}, 20, 3},
    {(int[]){0}, 100, 1},
    {(int[]){-100, -200, -300}, -100, 3},
    {(int[]){3, 6, 9, 12, 15, 18}, 3, 6},
    {(int[]){1, 3, 5, 7, 9}, 2, 5},
    {(int[]){50, 60, 70, 80}, 25, 4},
    {(int[]){-2, -4, -6, -8, -10}, -1, 5},
    {(int[]){999, 1000}, 1, 2},
    {(int[]){0, 10, 20, 30}, 5, 4},
    {(int[]){-7, 7, -14, 14}, 7, 4},
    {(int[]){12, 24, 36}, 12, 3},
    {(int[]){1, 2, 3, 4, 5, 6, 7}, 0, 7},
    {(int[]){-50, 0, 50}, 10, 3},
    {(int[]){8, 16, 24, 32}, 8, 4},
    {(int[]){11, 22, 33, 44, 55}, 11, 5},
    {(int[]){-1, -1, -1}, -1, 3},
    {(int[]){9, 18, 27}, 9, 3},
    {(int[]){4, 8, 12, 16, 20, 24}, 4, 6},
    {(int[]){-3, 3, -9, 9, -15}, 6, 5}
};
int num_test_cases = 30;


    typedef struct {
        int* result1;
        int* result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z21Change(TestCase t1) {
    TestCase follow_case = t1;
    // --- 这是根据规则4生成的内存处理代码 ---
    int* follow_case_a = (int*)malloc(t1.n * sizeof(int));
    memcpy(follow_case_a, t1.a, t1.n * sizeof(int));
    follow_case.a = follow_case_a;
    // ------------------------------------
    
    // 这是根据规则6a生成的防御性代码，防止n<1时出错
    if (follow_case.n > 0) {
        // 这是根据规则5生成的具体操作代码
        for (int i = 1; i < follow_case.n; i += 2) {
            follow_case.a[i] = follow_case.a[i] / 3;
        }
    }
    
    return follow_case;}

int z21check(int* result1, int* result2, int n) {
    // 1. 防御性编程 (空指针与长度检查)
    if (result1 == NULL || result2 == NULL) return 0;
    if (n <= 0) return 1;

    // 2. 核心判断逻辑 (elementwise)
    // 条件为 result1[][0..0] == result2[][0..0]，切片为 [0..0]，即仅比较索引0处的元素。
    // 因此，不需要循环，直接进行单次判断。
    // 首先检查索引0是否在有效范围内。
    if (n <= 0) return 1; // 空数组，视为满足
    // 比较索引0处的元素
    if (!(result1[0] == result2[0])) {
        return 0; // 一旦违反条件，立即返回 0
    }

    // 3. 全部满足，返回 1
    return 1;
}

TestResult z21runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z21Change(test_cases[test_case_id]);
    // 原始调用
    int* source = dec_array(test_cases[test_case_id].a, test_cases[test_case_id].k, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    int* follow = dec_array(follow_case.a, follow_case.k, follow_case.n);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    memory_list[0] = follow_case.a;
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z21check(source, follow, test_cases[test_case_id].n);
    test_result.status = status;
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z21runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}