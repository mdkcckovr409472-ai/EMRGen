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


int* dec(int array1[], int array2[], int n) {
    int* cp1 = (int*)malloc(n * sizeof(int));
    memcpy(cp1,array1,n*sizeof(int));
    for (int index = 0; index < n; index++) {
        cp1[index] -= array2[index];
    }
    return cp1;
}

typedef struct {
    int* array1; int* array2; int n;
} TestCase;

TestCase test_cases[] = {
    {(int[]){0, 0, 0}, (int[]){0, 0, 0}, 3},
    {(int[]){1, 2, 3}, (int[]){1, 2, 3}, 3},
    {(int[]){5, 10, 15}, (int[]){2, 3, 4}, 3},
    {(int[]){10, 20, 30}, (int[]){1, 2, 3}, 3},
    {(int[]){-1, -2, -3}, (int[]){-1, -2, -3}, 3},
    {(int[]){100, 200}, (int[]){50, 150}, 2},
    {(int[]){7}, (int[]){3}, 1},
    {(int[]){0}, (int[]){0}, 1},
    {(int[]){-5, -10}, (int[]){-2, -7}, 2},
    {(int[]){15, 25, 35, 45}, (int[]){5, 10, 15, 20}, 4},
    {(int[]){2, 4, 6, 8, 10}, (int[]){1, 3, 5, 7, 9}, 5},
    {(int[]){1000, 2000, 3000}, (int[]){500, 1000, 1500}, 3},
    {(int[]){-20, -10, 0}, (int[]){-5, 5, 10}, 3},
    {(int[]){1, 1, 1, 1}, (int[]){0, 0, 0, 0}, 4},
    {(int[]){9, 8, 7, 6, 5}, (int[]){4, 3, 2, 1, 0}, 5},
    {(int[]){50, 60, 70}, (int[]){20, 30, 40}, 3},
    {(int[]){-100, -200, -300}, (int[]){-50, -100, -150}, 3},
    {(int[]){12, 24, 36, 48}, (int[]){6, 12, 18, 24}, 4},
    {(int[]){3, 6, 9, 12, 15, 18}, (int[]){1, 2, 3, 4, 5, 6}, 6},
    {(int[]){0, 5, 10, 15, 20}, (int[]){0, 5, 10, 15, 20}, 5},
    {(int[]){-8, -6, -4, -2}, (int[]){-1, -2, -3, -4}, 4},
    {(int[]){25, 50, 75}, (int[]){10, 20, 30}, 3},
    {(int[]){11, 22, 33, 44, 55}, (int[]){1, 2, 3, 4, 5}, 5},
    {(int[]){999, 888, 777}, (int[]){111, 222, 333}, 3},
    {(int[]){-15, 0, 15}, (int[]){-5, 0, 5}, 3},
    {(int[]){6, 12, 18, 24, 30, 36}, (int[]){1, 2, 3, 4, 5, 6}, 6},
    {(int[]){40, 80, 120}, (int[]){20, 40, 60}, 3},
    {(int[]){-1, 0, 1}, (int[]){-1, 0, 1}, 3},
    {(int[]){19, 28, 37}, (int[]){9, 18, 27}, 3},
    {(int[]){14, 28, 42, 56}, (int[]){7, 14, 21, 28}, 4}
};
int num_test_cases = 30;


    typedef struct {
        int* result1;
        int* result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z36Change(TestCase t1) {
TestCase follow_case = t1;
// --- 这是根据规则4生成的内存处理代码 ---
int* follow_case_array2 = (int*)malloc(t1.n * sizeof(int));
memcpy(follow_case_array2, t1.array2, t1.n * sizeof(int));
follow_case.array2 = follow_case_array2;
// ------------------------------------

// 这是根据规则6a生成的防御性代码，防止n<=0时出错
if (follow_case.n > 0) {
    // 这是根据规则5生成的具体操作代码
    for (int i = 0; i < follow_case.n; i++) {
        if (i % 3 == 0) {
            follow_case.array2[i] += 10;
        }
    }
}

return follow_case;}

int z36check(int* result1, int* result2, int n) {
    // 1. 防御性编程 (空指针与长度检查)
    if (result1 == NULL || result2 == NULL) return 0;
    if (n <= 0) return 1;

    // 2. 核心判断逻辑 (字典序比较)
    for (int i = 0; i < n; i++) {
        // 找到第一个不相等的元素对
        if (result1[i] != result2[i]) {
            // 根据这一对元素的大小关系决定结果
            // 条件要求 result1[] > result2[] (lexically)
            if (result1[i] > result2[i]) {
                return 1; // 第一个不相等处 result1[i] > result2[i]，字典序上 result1 > result2
            } else {
                return 0; // 第一个不相等处 result1[i] < result2[i]，字典序上 result1 < result2
            }
        }
    }
    
    // 3. 循环结束，所有元素都相等
    // 条件要求严格大于 (>) ，相等不满足条件
    return 0;
}

TestResult z36runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z36Change(test_cases[test_case_id]);
    // 原始调用
    int* source = dec(test_cases[test_case_id].array1, test_cases[test_case_id].array2, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    int* follow = dec(follow_case.array1, follow_case.array2, follow_case.n);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    memory_list[0] = follow_case.array2;
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z36check(source, follow, test_cases[test_case_id].n);
    test_result.status = status;
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z36runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}