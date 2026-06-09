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


int* bubble(int a[], int n){
    int* cp1 = (int*)malloc(n * sizeof(int));
    memcpy(cp1, a, n * sizeof(int));
    int t;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (cp1[j] > cp1[j + 1])
            {
                t = cp1[j];
                cp1[j] = cp1[j + 1];
                cp1[j + 1] = t;
            }
        }
    }
    return cp1;
}

typedef struct {
    int* a; int n;
} TestCase;

TestCase test_cases[] = {
    {(int[]){1, 2, 3, 4, 5}, 5},
    {(int[]){5, 4, 3, 2, 1}, 5},
    {(int[]){1}, 1},
    {(int[]){2, 1}, 2},
    {(int[]){-1, -2, -3}, 3},
    {(int[]){0, 0, 0}, 3},
    {(int[]){10, 5, 8, 2, 7}, 5},
    {(int[]){1, 3, 2}, 3},
    {(int[]){100, 50, 75}, 3},
    {(int[]){-5, 0, 5}, 3},
    {(int[]){9, 8, 7, 6}, 4},
    {(int[]){1, 2, 1, 2}, 4},
    {(int[]){3, 1, 4, 1, 5}, 5},
    {(int[]){-10, 10, -20, 20}, 4},
    {(int[]){15}, 1},
    {(int[]){4, 3, 2, 1, 0, -1}, 6},
    {(int[]){6, 5, 4, 3, 2, 1, 0}, 7},
    {(int[]){1, 2, 3, 2, 1}, 5},
    {(int[]){7, 3, 9, 1, 6}, 5},
    {(int[]){-3, -1, -4, -2}, 4},
    {(int[]){0, 1, 0, 1, 0}, 5},
    {(int[]){12, 11, 13}, 3},
    {(int[]){5, 5, 5, 5}, 4},
    {(int[]){8, 2, 5, 1, 9, 3}, 6},
    {(int[]){-7, 7, -8, 8}, 4},
    {(int[]){1, 4, 2, 5, 3}, 5},
    {(int[]){10, 20, 30}, 3},
    {(int[]){30, 20, 10}, 3},
    {(int[]){6, 1, 8, 4, 2}, 5},
    {(int[]){0, -5, 5, -10, 10}, 5}
};
int num_test_cases = 30;


    typedef struct {
        int* result1;
        int* result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z3Change(TestCase t1) {
    TestCase follow_case = t1;
    int* follow_case_a = (int*)malloc(t1.n * sizeof(int));
    memcpy(follow_case_a, t1.a, t1.n * sizeof(int));
    follow_case.a = follow_case_a;
    if (follow_case.n > 0) {
        for (int i = 0; i < follow_case.n; i++) {
            follow_case.a[i] = follow_case.a[i] * 2;
        }
    }
    return follow_case;}

int z3check(int* result1, int* result2, int n) {
    // 1. 防御性编程 (空指针与长度检查)
    if (result1 == NULL || result2 == NULL) return 0;
    if (n <= 0) return 1;

    // 2. 核心判断逻辑 (elementwise)
    for (int i = 0; i < n; i++) {
        // 条件: 2 * result1[i] - result2[i] == 0
        // 移项后: 2 * result1[i] == result2[i]
        if (2 * result1[i] != result2[i]) {
            return 0; // 一旦违反条件，立即返回 0
        }
    }

    // 3. 全部满足，返回 1
    return 1;
}

TestResult z3runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z3Change(test_cases[test_case_id]);
    // 原始调用
    int* source = bubble(test_cases[test_case_id].a, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    int* follow = bubble(follow_case.a, follow_case.n);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    memory_list[0] = follow_case.a;
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z3check(source, follow, test_cases[test_case_id].n);
    test_result.status = status;
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z3runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}