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


int find_max(int a[], int n) {
    int max = a[0];
    for (int i = 0; i < n; i++) {
        if (a[i] > max) {
            max = a[i];
        }
    }
    return max;
}


typedef struct {
    int* a; int n;
} TestCase;

TestCase test_cases[] = {
    {(int[]){1, 2, 3, 4, 5}, 5},
    {(int[]){5, 4, 3, 2, 1}, 5},
    {(int[]){-10, -5, 0, 5, 10}, 5},
    {(int[]){42}, 1},
    {(int[]){0, 0, 0, 0}, 4},
    {(int[]){1, 3, 5, 7, 9, 2, 4, 6, 8}, 9},
    {(int[]){100, 200, 150}, 3},
    {(int[]){-1, -2, -3, -100}, 4},
    {(int[]){7, 7, 7, 7, 7}, 5},
    {(int[]){-5, 10, -5, 20, -5}, 5},
    {(int[]){1, 2}, 2},
    {(int[]){999, 998, 997}, 3},
    {(int[]){0, -1, 1, -2, 2}, 5},
    {(int[]){15, 30, 45, 60, 75, 90}, 6},
    {(int[]){-1000, -500, -750}, 3},
    {(int[]){2, 4, 8, 16, 32, 64}, 6},
    {(int[]){9, 8, 7, 6, 5, 4, 3, 2, 1, 0}, 10},
    {(int[]){1, 100, 50, 100, 1}, 5},
    {(int[]){-3, -2, -1, 0, 1, 2, 3}, 7},
    {(int[]){25}, 1},
    {(int[]){10, 20, 30, 20, 10}, 5},
    {(int[]){-8, -4, -12, -1}, 4},
    {(int[]){6, 2, 9, 1, 8}, 5},
    {(int[]){0, 1000, 500}, 3},
    {(int[]){-99, 0, 99}, 3},
    {(int[]){11, 22, 33, 44, 55, 66}, 6},
    {(int[]){1, 2, 1, 2, 1, 2}, 6},
    {(int[]){-20, -10, -30}, 3},
    {(int[]){50, 60, 70, 80, 90, 100}, 6},
    {(int[]){4, 3, 2, 1, 5}, 5}
};
int num_test_cases = 30;


    typedef struct {
        int result1;
        int result2;
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
        for (int i = 0; i < follow_case.n; i++) {
            follow_case.a[i] = follow_case.a[i] + i;
        }
    }

    return follow_case;}

int z23check(int result1, int result2) {
    // 1. 核心判断逻辑 (标量直接比较)
    if (!(result1 <= result2)) {
        return 0;
    }
    
    // 2. 满足条件，返回 1
    return 1;
}

TestResult z23runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z23Change(test_cases[test_case_id]);
    // 原始调用
    int source = find_max(test_cases[test_case_id].a, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    int follow = find_max(follow_case.a, follow_case.n);
    
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