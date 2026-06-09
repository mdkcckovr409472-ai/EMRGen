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


int* selection_sort(int list[], int n) {
    int* cp1 = (int*)malloc(n * sizeof(int));
    memcpy(cp1,list,n*sizeof(int));
    int i;
    int j;
    int min;
    for (i = 0; i < n - 1; i++) {
        min = i;
        for (j = i + 1; j < n; j++) {
            if (cp1[j] < cp1[min]) {
                min = j;
            }
        }
        int tmp = cp1[i];
        cp1[i] = cp1[min];
        cp1[min] = tmp;
    }
    return cp1;
}


typedef struct {
    int* list; int n;
} TestCase;

TestCase test_cases[] = {
    {(int[]){5, 2, 8, 1, 9}, 5},
    {(int[]){1}, 1},
    {(int[]){2, 1}, 2},
    {(int[]){1, 2, 3}, 3},
    {(int[]){3, 2, 1}, 3},
    {(int[]){9, 8, 7, 6, 5, 4, 3, 2, 1, 0}, 10},
    {(int[]){0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, 10},
    {(int[]){-5, 10, 3, -2, 0}, 5},
    {(int[]){100, 200, 300}, 3},
    {(int[]){5, 5, 5, 5}, 4},
    {(int[]){1, 3, 2, 4, 5}, 5},
    {(int[]){7, 3, 5, 9, 1, 4}, 6},
    {(int[]){0, 0, 0}, 3},
    {(int[]){-10, -20, -30}, 3},
    {(int[]){15}, 1},
    {(int[]){2, 4, 6, 8, 10}, 5},
    {(int[]){10, 8, 6, 4, 2}, 5},
    {(int[]){1, 2, 1, 2, 1}, 5},
    {(int[]){-1, 0, 1}, 3},
    {(int[]){9, 1, 8, 2, 7, 3, 6, 4, 5}, 9},
    {(int[]){25, 15, 35, 5, 45}, 5},
    {(int[]){0, -1, 1, -2, 2}, 5},
    {(int[]){12, 12, 12, 12, 12, 12}, 6},
    {(int[]){6, 3, 9}, 3},
    {(int[]){1000, 500, 1500}, 3},
    {(int[]){4, 7, 2, 8, 1, 9, 3}, 7},
    {(int[]){-5, -1, -3, -7, -9}, 5},
    {(int[]){1, 2, 4, 3}, 4},
    {(int[]){0}, 1},
    {(int[]){11, 22, 33, 44, 55, 66}, 6}
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
int* follow_case_list = (int*)malloc(t1.n * sizeof(int));
memcpy(follow_case_list, t1.list, t1.n * sizeof(int));
follow_case.list = follow_case_list;
// ------------------------------------

// 这是根据规则6a生成的防御性代码，防止n<=0时出错
if (follow_case.n > 0) {
    // 这是根据规则5生成的具体操作代码
    for (int i = 0; i < follow_case.n; i++) {
        follow_case.list[i] = follow_case.list[i] + 1;
    }
}

return follow_case;}

int z1check(int* result1, int* result2, int n) {
    // 1. 防御性编程 (空指针与长度检查)
    if (result1 == NULL || result2 == NULL) return 0;
    if (n <= 0) return 1;

    // 2. 核心判断逻辑 (elementwise)
    // 条件: result1[] - result2[] + 1 == 0
    // 移项后: result1[] + 1 == result2[]
    for (int i = 0; i < n; i++) {
        if (!(result1[i] + 1 == result2[i])) {
            return 0; // 一旦违反条件，立即返回 0
        }
    }

    // 3. 全部满足，返回 1
    return 1;
}

TestResult z1runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z1Change(test_cases[test_case_id]);
    // 原始调用
    int* source = selection_sort(test_cases[test_case_id].list, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    int* follow = selection_sort(follow_case.list, follow_case.n);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    memory_list[0] = follow_case.list;
    
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