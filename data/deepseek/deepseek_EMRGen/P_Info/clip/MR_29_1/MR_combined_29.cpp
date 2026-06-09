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


int* clip(int a[], int lowerLim, int upperLim, int n) {
    int* r = (int*)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) {
            if (a[i] < lowerLim) {
                r[i] = lowerLim;
            } else {
                if (a[i] > upperLim) {
                    r[i] = upperLim;
                } else {
                    r[i] = a[i];
                }
            }
        }
        return r;
    }
    


typedef struct {
    int* a; int lowerLim; int upperLim; int n;
} TestCase;

TestCase test_cases[] = {
    {(int[]){10, 20, 30}, 15, 25, 3},
    {(int[]){5, 12, 18, 7}, 10, 15, 4},
    {(int[]){-3, 0, 8, -1, 4}, 0, 5, 5},
    {(int[]){100, 200, 150}, 120, 180, 3},
    {(int[]){22, 33, 44, 55}, 30, 50, 4},
    {(int[]){7}, 5, 10, 1},
    {(int[]){-10, -5, 0, 5, 10}, -7, 7, 5},
    {(int[]){14, 19, 23, 28}, 18, 25, 4},
    {(int[]){50, 60, 70, 80, 90}, 65, 85, 5},
    {(int[]){-20, -15, -10}, -18, -12, 3},
    {(int[]){0, 1, 2, 3, 4, 5}, 1, 4, 6},
    {(int[]){99, 101, 98, 102}, 100, 101, 4},
    {(int[]){45, 67, 89, 23}, 50, 80, 4},
    {(int[]){6, 7, 8, 9, 10}, 6, 10, 5},
    {(int[]){-50, 50, -25, 25}, -30, 30, 4},
    {(int[]){17, 29, 31, 42}, 20, 40, 4},
    {(int[]){123, 456, 789}, 200, 700, 3},
    {(int[]){11, 22, 33, 44, 55, 66}, 25, 60, 6},
    {(int[]){-1, -2, -3, -4}, -3, -1, 4},
    {(int[]){80, 85, 90, 95, 100}, 82, 97, 5},
    {(int[]){37, 52, 48, 61}, 40, 60, 4},
    {(int[]){999, 1001, 998, 1002}, 1000, 1001, 4},
    {(int[]){0, 10, 20, 30, 40}, 5, 35, 5},
    {(int[]){-100, 0, 100}, -50, 50, 3},
    {(int[]){71, 82, 93, 64, 75}, 70, 90, 5},
    {(int[]){19, 27, 35, 43}, 20, 40, 4},
    {(int[]){150, 250, 350}, 200, 300, 3},
    {(int[]){8, 16, 24, 32}, 10, 30, 4},
    {(int[]){-9, 9, -8, 8, -7, 7}, -8, 8, 6},
    {(int[]){55, 66, 77, 88, 99}, 60, 95, 5}
};
int num_test_cases = 30;


    typedef struct {
        int* result1;
        int* result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z29Change(TestCase t1) {
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
        if (follow_case.a[i] > follow_case.upperLim) {
            follow_case.a[i] = follow_case.upperLim;
        }
    }
}

return follow_case;}

int z29check(int* result1, int* result2, int n) {
    // 1. 防御性编程 (空指针与长度检查)
    if (result1 == NULL || result2 == NULL) return 0;
    if (n <= 0) return 1;

    // 2. 核心判断逻辑 (elementwise)
    for (int i = 0; i < n; i++) {
        if (!(result1[i] == result2[i])) {
            return 0; // 一旦违反条件，立即返回 0
        }
    }

    // 3. 全部满足，返回 1
    return 1;
}

TestResult z29runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z29Change(test_cases[test_case_id]);
    // 原始调用
    int* source = clip(test_cases[test_case_id].a, test_cases[test_case_id].lowerLim, test_cases[test_case_id].upperLim, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    int* follow = clip(follow_case.a, follow_case.lowerLim, follow_case.upperLim, follow_case.n);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    memory_list[0] = follow_case.a;
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z29check(source, follow, test_cases[test_case_id].n);
    test_result.status = status;
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z29runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}