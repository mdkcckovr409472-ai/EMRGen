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


int* array_calc1(int a[], int k, int n) {
    int* b = (int*)malloc(n * sizeof(int));
    if (b == NULL) return NULL;

    for (int i = 0; i < n; i++) {
        double val = (double)a[i] / k;
        b[i] = (int)round(val); 
    }
    return b;
}


typedef struct {
    int* a; int k; int n;
} TestCase;

TestCase test_cases[] = {
    {(int[]){10, 20, 30}, 5, 3},
    {(int[]){7, 14, 21}, 7, 3},
    {(int[]){0, 0, 0}, 1, 3},
    {(int[]){-10, -20, -30}, 5, 3},
    {(int[]){1, 2, 3, 4, 5}, 2, 5},
    {(int[]){15}, 3, 1},
    {(int[]){100, 200}, 100, 2},
    {(int[]){33, 66, 99}, 33, 3},
    {(int[]){-5, 5, -5, 5}, 1, 4},
    {(int[]){8, 9, 10}, 2, 3},
    {(int[]){25, 50, 75, 100}, 25, 4},
    {(int[]){12, 24, 36, 48, 60}, 12, 5},
    {(int[]){-1, -2, -3}, 1, 3},
    {(int[]){49, 50, 51}, 10, 3},
    {(int[]){17, 34, 51, 68}, 17, 4},
    {(int[]){999, 1000, 1001}, 1000, 3},
    {(int[]){6, 7, 8, 9, 10, 11}, 3, 6},
    {(int[]){0, 10, 20, 30}, 10, 4},
    {(int[]){-100, 0, 100}, 50, 3},
    {(int[]){22, 44, 66, 88}, 11, 4},
    {(int[]){3, 6, 9, 12, 15}, 3, 5},
    {(int[]){45, 90, 135}, 45, 3},
    {(int[]){13, 26, 39, 52}, 13, 4},
    {(int[]){77, 154, 231}, 77, 3},
    {(int[]){2, 4, 6, 8, 10, 12, 14}, 2, 7},
    {(int[]){-8, -16, -24}, 8, 3},
    {(int[]){19, 38, 57, 76}, 19, 4},
    {(int[]){123, 456, 789}, 123, 3},
    {(int[]){1, 3, 5, 7, 9}, 1, 5},
    {(int[]){-15, 30, -45, 60}, 15, 4}
};
int num_test_cases = 30;


    typedef struct {
        int* result1;
        int* result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z13Change(TestCase t1) {
TestCase follow_case = t1;
// --- 这是根据规则4生成的内存处理代码 ---
int* follow_case_a = (int*)malloc(t1.n * sizeof(int));
memcpy(follow_case_a, t1.a, t1.n * sizeof(int));
follow_case.a = follow_case_a;
// ------------------------------------

// 这是根据规则6a生成的防御性代码，防止n<2时出错
if (follow_case.n < 2) {
    // 元素不足2个，无需反转，直接返回副本
    return follow_case;
}

// 这是根据规则5生成的具体操作代码
int left = 0;
int right = follow_case.n - 1;
while (left < right) {
    int temp = follow_case.a[left];
    follow_case.a[left] = follow_case.a[right];
    follow_case.a[right] = temp;
    left++;
    right--;
}

return follow_case;}

int z13check(int* result1, int* result2, int n) {
    // 1. 防御性编程 (空指针与长度检查)
    if (result1 == NULL || result2 == NULL) return 0;
    if (n <= 0) return 1;

    // 2. 核心判断逻辑：result1[] 是 result2[] 的逆序
    for (int i = 0; i < n; i++) {
        if (result1[i] != result2[n - 1 - i]) {
            return 0; // 一旦违反条件，立即返回 0
        }
    }

    // 3. 全部满足，返回 1
    return 1;
}

TestResult z13runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z13Change(test_cases[test_case_id]);
    // 原始调用
    int* source = array_calc1(test_cases[test_case_id].a, test_cases[test_case_id].k, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    int* follow = array_calc1(follow_case.a, follow_case.k, follow_case.n);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    memory_list[0] = follow_case.a;
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z13check(source, follow, test_cases[test_case_id].n);
    test_result.status = status;
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z13runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}