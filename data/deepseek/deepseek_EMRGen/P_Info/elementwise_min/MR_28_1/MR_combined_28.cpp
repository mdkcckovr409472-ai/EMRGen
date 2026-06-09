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


int* elementwise_min(int a[], int b[], int n) {
    if (a == NULL || b == NULL || n <= 0) {
        return NULL;
    }

    int* result = (int*)malloc(n * sizeof(int));
    if (result == NULL) {
        return NULL;  
    }

    for (int i = 0; i < n; i++) {
        result[i] = (a[i] < b[i]) ? a[i] : b[i];  }

    return result;
}


typedef struct {
    int* a; int* b; int n;
} TestCase;

TestCase test_cases[] = {
    {(int[]){1, 2, 3}, (int[]){4, 5, 6}, 3},
    {(int[]){-1, -2, -3}, (int[]){-4, -5, -6}, 3},
    {(int[]){10, 20, 30}, (int[]){5, 25, 35}, 3},
    {(int[]){0, 0, 0}, (int[]){0, 0, 0}, 3},
    {(int[]){100}, (int[]){99}, 1},
    {(int[]){7, 8, 9, 10}, (int[]){6, 7, 8, 9}, 4},
    {(int[]){-10, 0, 10}, (int[]){-5, 5, 15}, 3},
    {(int[]){1, 3, 5}, (int[]){2, 4, 6}, 3},
    {(int[]){2, 4, 6}, (int[]){1, 3, 5}, 3},
    {(int[]){15, 25, 35, 45}, (int[]){20, 30, 40, 50}, 4},
    {(int[]){50, 40, 30, 20}, (int[]){45, 35, 25, 15}, 4},
    {(int[]){-100, 200, -300}, (int[]){-50, 150, -250}, 3},
    {(int[]){999, 888, 777}, (int[]){1000, 889, 776}, 3},
    {(int[]){42}, (int[]){42}, 1},
    {(int[]){1, 2}, (int[]){2, 1}, 2},
    {(int[]){-1, -1, -1, -1}, (int[]){-2, -2, -2, -2}, 4},
    {(int[]){5, 10, 15, 20, 25}, (int[]){4, 11, 14, 21, 24}, 5},
    {(int[]){0, 100, -100}, (int[]){1, 99, -99}, 3},
    {(int[]){6, 7, 8}, (int[]){6, 7, 8}, 3},
    {(int[]){9, 8, 7, 6, 5}, (int[]){10, 7, 8, 5, 6}, 5},
    {(int[]){-7, -8, -9}, (int[]){-6, -9, -10}, 3},
    {(int[]){123, 456, 789}, (int[]){124, 455, 790}, 3},
    {(int[]){11, 22, 33, 44, 55, 66}, (int[]){12, 21, 34, 43, 56, 65}, 6},
    {(int[]){2, 3, 5, 7, 11}, (int[]){1, 4, 6, 8, 13}, 5},
    {(int[]){1000, 2000, 3000}, (int[]){500, 2500, 3500}, 3},
    {(int[]){-20, -10, 0, 10, 20}, (int[]){-15, -5, 5, 15, 25}, 5},
    {(int[]){4, 4, 4}, (int[]){5, 5, 5}, 3},
    {(int[]){19, 28, 37, 46}, (int[]){21, 26, 39, 44}, 4},
    {(int[]){51, 62, 73}, (int[]){49, 64, 71}, 3},
    {(int[]){8, 6, 4, 2, 0}, (int[]){9, 5, 3, 1, -1}, 5}
};
int num_test_cases = 30;


    typedef struct {
        int* result1;
        int* result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z28Change(TestCase t1) {
TestCase follow_case = t1;
// --- 这是根据规则4生成的内存处理代码 ---
int* follow_case_a = (int*)malloc(t1.n * sizeof(int));
memcpy(follow_case_a, t1.a, t1.n * sizeof(int));
follow_case.a = follow_case_a;
// ------------------------------------

// 这是根据规则6a生成的防御性代码，防止n<2时出错
if (follow_case.n < 2) {
    // 元素不足2个，边界元素即自身，无需操作
    return follow_case;
}

// 这是根据规则5生成的具体操作代码
int* temp = (int*)malloc(follow_case.n * sizeof(int));
memcpy(temp, follow_case.a, follow_case.n * sizeof(int));

for (int i = 1; i < follow_case.n - 1; i++) {
    follow_case.a[i] = temp[i - 1] + temp[i + 1];
}
free(temp);

return follow_case;}

int z28check(int* result1, int* result2, int n) {
    // 1. 防御性编程 (空指针与长度检查)
    if (result1 == NULL || result2 == NULL) return 0;
    if (n <= 0) return 1;

    // 2. 核心判断逻辑 (elementwise)
    // 条件: return.result1[][0..0] == return.result2[][0..0] (elementwise)
    // 切片为 [0..0]，即只比较索引 0 处的单个元素。
    // 因此，不使用循环，直接进行单次判断。
    if (!(result1[0] == result2[0])) {
        return 0; // 一旦违反条件，立即返回 0
    }

    // 3. 全部满足，返回 1
    return 1;
}

TestResult z28runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z28Change(test_cases[test_case_id]);
    // 原始调用
    int* source = elementwise_min(test_cases[test_case_id].a, test_cases[test_case_id].b, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    int* follow = elementwise_min(follow_case.a, follow_case.b, follow_case.n);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    memory_list[0] = follow_case.a;
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z28check(source, follow, test_cases[test_case_id].n);
    test_result.status = status;
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z28runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}