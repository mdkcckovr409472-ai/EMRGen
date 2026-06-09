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


int dot_product(int a[], int b[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
            sum += a[i] * b[i];
        }
    return sum;
}


typedef struct {
    int* a; int* b; int n;
} TestCase;

TestCase test_cases[] = {
    {(int[]){1, 2, 3}, (int[]){4, 5, 6}, 3},
    {(int[]){0, 0, 0}, (int[]){0, 0, 0}, 3},
    {(int[]){1}, (int[]){1}, 1},
    {(int[]){-1, 2}, (int[]){3, -4}, 2},
    {(int[]){10, 20, 30, 40}, (int[]){1, 2, 3, 4}, 4},
    {(int[]){-5, -10}, (int[]){-2, -3}, 2},
    {(int[]){100}, (int[]){-100}, 1},
    {(int[]){1, 0, -1}, (int[]){0, 5, 0}, 3},
    {(int[]){2, 4, 6, 8, 10}, (int[]){1, 1, 1, 1, 1}, 5},
    {(int[]){3, 6, 9}, (int[]){-1, -2, -3}, 3},
    {(int[]){1, 2, 3, 4, 5, 6}, (int[]){6, 5, 4, 3, 2, 1}, 6},
    {(int[]){7}, (int[]){8}, 1},
    {(int[]){0, 100, 200}, (int[]){300, 0, 400}, 3},
    {(int[]){-1, -2, -3, -4}, (int[]){-1, -2, -3, -4}, 4},
    {(int[]){15, 25}, (int[]){4, -6}, 2},
    {(int[]){9, 8, 7}, (int[]){1, 2, 3}, 3},
    {(int[]){1, 1, 1, 1}, (int[]){2, 2, 2, 2}, 4},
    {(int[]){-10, 20, -30}, (int[]){1, -2, 3}, 3},
    {(int[]){5, 10, 15, 20, 25, 30}, (int[]){2, 2, 2, 2, 2, 2}, 6},
    {(int[]){12, 24}, (int[]){0, 0}, 2},
    {(int[]){6, 12, 18, 24}, (int[]){-1, 1, -1, 1}, 4},
    {(int[]){100, 200, 300}, (int[]){1, 0, -1}, 3},
    {(int[]){2, 3, 5, 7}, (int[]){11, 13, 17, 19}, 4},
    {(int[]){-8, -6, -4, -2, 0}, (int[]){1, 2, 3, 4, 5}, 5},
    {(int[]){1, 4, 9, 16}, (int[]){1, 2, 3, 4}, 4},
    {(int[]){50, 60}, (int[]){-10, -20}, 2},
    {(int[]){0, 1, 2, 3, 4, 5, 6}, (int[]){7, 6, 5, 4, 3, 2, 1}, 7},
    {(int[]){-3, 0, 3}, (int[]){5, 10, 15}, 3},
    {(int[]){8, 4, 2, 1}, (int[]){1, 2, 4, 8}, 4},
    {(int[]){11, 22, 33}, (int[]){0, 0, 0}, 3}
};
int num_test_cases = 30;


    typedef struct {
        int result1;
        int result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z5Change(TestCase t1) {
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
        follow_case.a[i] = -follow_case.a[i];
    }
}

return follow_case;}

int z5check(int result1, int result2) {
    // 1. 核心判断逻辑 (标量直接比较)
    if (!(result1 + result2 == 0)) {
        return 0;
    }
    
    // 2. 满足条件，返回 1
    return 1;
}

TestResult z5runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z5Change(test_cases[test_case_id]);
    // 原始调用
    int source = dot_product(test_cases[test_case_id].a, test_cases[test_case_id].b, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    int follow = dot_product(follow_case.a, follow_case.b, follow_case.n);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    memory_list[0] = follow_case.a;
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z5check(source, follow);
    test_result.status = status;
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z5runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}