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


int* array_copy(int a[], int n) {
    if (a == NULL || n <= 0) {
        return NULL;
    }


    int* copy = (int*)malloc(n * sizeof(int));
    if (copy == NULL) {
        return NULL;  
    }


    for (int i = 0; i < n; i++) {
        copy[i] = a[i];
    }

    return copy;
}


typedef struct {
    int* a; int n;
} TestCase;

TestCase test_cases[] = {
    {(int[]){1}, 1},
    {(int[]){1, 2}, 2},
    {(int[]){1, 2, 3}, 3},
    {(int[]){0}, 1},
    {(int[]){-1, 0, 1}, 3},
    {(int[]){10, 20, 30, 40}, 4},
    {(int[]){5, 4, 3, 2, 1}, 5},
    {(int[]){100}, 1},
    {(int[]){-5, -4, -3, -2, -1}, 5},
    {(int[]){2, 4, 6, 8, 10, 12}, 6},
    {(int[]){1, 1, 1, 1}, 4},
    {(int[]){-10, 10, -20, 20}, 4},
    {(int[]){7}, 1},
    {(int[]){0, 0, 0}, 3},
    {(int[]){15, 25, 35}, 3},
    {(int[]){-100, -200, -300}, 3},
    {(int[]){999}, 1},
    {(int[]){1, 3, 5, 7, 9, 11, 13}, 7},
    {(int[]){-1, -2, -3, -4}, 4},
    {(int[]){50, 60, 70, 80, 90}, 5},
    {(int[]){6, 5, 4, 3, 2, 1, 0}, 7},
    {(int[]){12, 24, 36}, 3},
    {(int[]){-7, 7, -14, 14}, 4},
    {(int[]){1000, 2000, 3000, 4000}, 4},
    {(int[]){8, 6, 4, 2, 0, -2}, 6},
    {(int[]){9}, 1},
    {(int[]){11, 22, 33, 44, 55, 66, 77, 88}, 8},
    {(int[]){-50, 0, 50}, 3},
    {(int[]){19, 28, 37, 46}, 4},
    {(int[]){255}, 1}
};
int num_test_cases = 30;


    typedef struct {
        int* result1;
        int* result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z20Change(TestCase t1) {
    TestCase follow_case = t1;
    // --- 这是根据规则4生成的内存处理代码 ---
    int* follow_case_a = (int*)malloc(t1.n * sizeof(int));
    memcpy(follow_case_a, t1.a, t1.n * sizeof(int));
    follow_case.a = follow_case_a;
    // ------------------------------------
    
    // 这是根据规则6a生成的防御性代码，防止n<=0时出错
    if (follow_case.n > 0) {
        // 这是根据规则5生成的具体操作代码
        for (int i = 0; i < follow_case.n; i += 2) {
            follow_case.a[i] += 3;
        }
    }
    
    return follow_case;
}

int z20check(int* result1, int* result2, int n) {
    // 1. 防御性编程 (空指针与长度检查)
    if (result1 == NULL || result2 == NULL) return 0;
    if (n <= 0) return 1;

    // 2. 核心判断逻辑 (字典序比较)
    for (int i = 0; i < n; i++) {
        // 找到第一个不相等的元素对
        if (result1[i] != result2[i]) {
            // 根据这一对元素的大小关系决定结果
            // 条件要求 result1[] < result2[] (lexically)
            if (result1[i] < result2[i]) {
                return 1; // 第一个不相等处 result1[i] < result2[i]，满足字典序小于
            } else {
                return 0; // 第一个不相等处 result1[i] > result2[i]，不满足字典序小于
            }
        }
    }
    
    // 3. 循环结束，说明所有元素都相等
    // 严格小于要求不相等，因此相等时不满足条件
    return 0;
}

TestResult z20runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z20Change(test_cases[test_case_id]);
    // 原始调用
    int* source = array_copy(test_cases[test_case_id].a, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    int* follow = array_copy(follow_case.a, follow_case.n);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    memory_list[0] = follow_case.a;
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z20check(source, follow, test_cases[test_case_id].n);
    test_result.status = status;
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z20runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}