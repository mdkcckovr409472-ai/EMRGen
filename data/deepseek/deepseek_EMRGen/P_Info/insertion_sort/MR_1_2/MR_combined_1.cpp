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


int* insertion_sort(int array[], int n) {
    int* cp1 = (int*)malloc(n * sizeof(int));
    memcpy(cp1,array,n*sizeof(int));
    for (int i = 1; i < n; i++) {
        int j = i;
        int B = cp1[i];
        while (j > 0 && cp1[j - 1] > B) {
            cp1[j] = cp1[j - 1];
            j--;
        }
        cp1[j] = B;
        }
    
    return cp1;
}


typedef struct {
    int* array; int n;
} TestCase;

TestCase test_cases[] = {
    {(int[]){1}, 1},
    {(int[]){2, 1}, 2},
    {(int[]){1, 2, 3}, 3},
    {(int[]){3, 2, 1}, 3},
    {(int[]){5, 2, 4, 6, 1, 3}, 6},
    {(int[]){-1, -2, -3}, 3},
    {(int[]){-3, -2, -1}, 3},
    {(int[]){0, 0, 0}, 3},
    {(int[]){100}, 1},
    {(int[]){1, 3, 2}, 3},
    {(int[]){9, 7, 5, 3, 1}, 5},
    {(int[]){1, 2, 3, 4, 5}, 5},
    {(int[]){4}, 1},
    {(int[]){-5, 10, 0, -10, 5}, 5},
    {(int[]){2, 2, 1, 1, 3, 3}, 6},
    {(int[]){1, 2}, 2},
    {(int[]){2, 1, 3}, 3},
    {(int[]){3, 1, 2}, 3},
    {(int[]){10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, 10},
    {(int[]){1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 10},
    {(int[]){5, 1, 4, 2, 8}, 5},
    {(int[]){0, 1, 0, 1}, 4},
    {(int[]){-100, 100, 0}, 3},
    {(int[]){7}, 1},
    {(int[]){6, 5}, 2},
    {(int[]){8, 4, 2}, 3},
    {(int[]){3, 3, 3, 1, 1, 1}, 6},
    {(int[]){15, 12, 10}, 3},
    {(int[]){9, 0, -9}, 3},
    {(int[]){1, 4, 2, 4, 3}, 5}
};
int num_test_cases = 30;


    typedef struct {
        int* result1;
        int* result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z1Change(TestCase t1) {
    TestCase follow_case = t1;
    // --- 这是根据规则4生成的内存处理代码 ---
    int* follow_case_array = (int*)malloc(t1.n * sizeof(int));
    memcpy(follow_case_array, t1.array, t1.n * sizeof(int));
    follow_case.array = follow_case_array;
    // ------------------------------------

    // 这是根据规则6a生成的防御性代码，防止n<=0时出错
    if (follow_case.n > 0) {
        // 这是根据规则5生成的具体操作代码
        for (int i = 0; i < follow_case.n; i++) {
            follow_case.array[i] += 1;
        }
    }

    return follow_case;}

int z1check(int* result1, int* result2, int n) {
    // 1. 防御性编程 (空指针与长度检查)
    if (result1 == NULL || result2 == NULL) return 0;
    if (n <= 0) return 1;

    // 2. 核心判断逻辑 (elementwise)
    for (int i = 0; i < n; i++) {
        if (!(result1[i] < result2[i])) {
            return 0; // 一旦违反条件，立即返回 0
        }
    }

    // 3. 全部满足，返回 1
    return 1;
}

TestResult z1runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z1Change(test_cases[test_case_id]);
    // 原始调用
    int* source = insertion_sort(test_cases[test_case_id].array, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    int* follow = insertion_sort(follow_case.array, follow_case.n);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    memory_list[0] = follow_case.array;
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z1check(source, follow, test_cases[test_case_id].n);
    test_result.status = status;
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z1runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}