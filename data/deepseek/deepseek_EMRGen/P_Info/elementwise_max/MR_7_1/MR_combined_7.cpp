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


int* elementwise_max(int a[], int b[], int n) {
    if (a == NULL || b == NULL || n <= 0) {
        return NULL;
    }


    int* result = (int*)malloc(n * sizeof(int));
    if (result == NULL) {
        return NULL;  
    }


    for (int i = 0; i < n; i++) {
        result[i] = (a[i] > b[i]) ? a[i] : b[i];
    }

    return result;
}


typedef struct {
    int* a; int* b; int n;
} TestCase;

TestCase test_cases[] = {
    {(int[]){1, 2, 3}, (int[]){3, 2, 1}, 3},
    {(int[]){5, 10, 15}, (int[]){15, 10, 5}, 3},
    {(int[]){0, 0, 0}, (int[]){0, 0, 0}, 3},
    {(int[]){-1, -2, -3}, (int[]){-3, -2, -1}, 3},
    {(int[]){100, 200}, (int[]){150, 250}, 2},
    {(int[]){7}, (int[]){9}, 1},
    {(int[]){-5, 0, 5}, (int[]){5, 0, -5}, 3},
    {(int[]){1, 1, 1, 1}, (int[]){2, 2, 2, 2}, 4},
    {(int[]){2, 2, 2, 2}, (int[]){1, 1, 1, 1}, 4},
    {(int[]){10, 20, 30, 40, 50}, (int[]){5, 15, 25, 35, 45}, 5},
    {(int[]){-10, -20, -30}, (int[]){-30, -20, -10}, 3},
    {(int[]){0, 1, 0, 1}, (int[]){1, 0, 1, 0}, 4},
    {(int[]){1000, 2000}, (int[]){2000, 1000}, 2},
    {(int[]){3, 1, 4, 1, 5}, (int[]){2, 7, 1, 8, 2}, 5},
    {(int[]){-100, 100, -200, 200}, (int[]){100, -100, 200, -200}, 4},
    {(int[]){6, 6, 6}, (int[]){6, 6, 6}, 3},
    {(int[]){15, 25, 35}, (int[]){10, 30, 20}, 3},
    {(int[]){99, 99}, (int[]){101, 101}, 2},
    {(int[]){-1, -1, -1, -1, -1}, (int[]){-2, -2, -2, -2, -2}, 5},
    {(int[]){50, 60, 70}, (int[]){55, 65, 75}, 3},
    {(int[]){12, 24, 36, 48}, (int[]){6, 18, 30, 42}, 4},
    {(int[]){0, -1, 2, -3}, (int[]){1, 0, -2, 3}, 4},
    {(int[]){999, 888, 777}, (int[]){777, 888, 999}, 3},
    {(int[]){4, 5, 6, 7, 8, 9}, (int[]){9, 8, 7, 6, 5, 4}, 6},
    {(int[]){-50, -25, 0, 25, 50}, (int[]){50, 25, 0, -25, -50}, 5},
    {(int[]){11, 22, 33}, (int[]){44, 33, 22}, 3},
    {(int[]){1, 3, 5, 7, 9, 11}, (int[]){2, 4, 6, 8, 10, 12}, 6},
    {(int[]){-7, 14, -21, 28}, (int[]){7, -14, 21, -28}, 4},
    {(int[]){100, 101, 102}, (int[]){99, 100, 101}, 3},
    {(int[]){8, 6, 4, 2}, (int[]){1, 3, 5, 7}, 4}
};
int num_test_cases = 30;


    typedef struct {
        int* result1;
        int* result2;
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
            follow_case.a[i] = follow_case.a[i] * follow_case.a[i];
        }
    }

    return follow_case;}

int z7check(int* result1, int* result2, int n) {
    // 1. 防御性编程 (空指针与长度检查)
    if (result1 == NULL || result2 == NULL) return 0;
    if (n <= 0) return 1;

    // 2. 核心判断逻辑 (elementwise)
    for (int i = 0; i < n; i++) {
        if (!(result1[i] <= result2[i])) {
            return 0; // 一旦违反条件，立即返回 0
        }
    }

    // 3. 全部满足，返回 1
    return 1;
}

TestResult z7runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z7Change(test_cases[test_case_id]);
    // 原始调用
    int* source = elementwise_max(test_cases[test_case_id].a, test_cases[test_case_id].b, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    int* follow = elementwise_max(follow_case.a, follow_case.b, follow_case.n);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    memory_list[0] = follow_case.a;
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z7check(source, follow, test_cases[test_case_id].n);
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