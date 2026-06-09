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


int* s_add(int array1[], int array2[], int n) {
    int* cp1 = (int*)malloc(n * sizeof(int));
    memcpy(cp1,array1,n*sizeof(int));
    for (int index = 0; index < n; index++) {
        cp1[index] += array2[index];
    }
    return cp1;
}

typedef struct {
    int* array1; int* array2; int n;
} TestCase;

TestCase test_cases[] = {
    {(int[]){1, 2, 3}, (int[]){4, 5, 6}, 3},
    {(int[]){0, 0, 0}, (int[]){0, 0, 0}, 3},
    {(int[]){-1, -2, -3}, (int[]){1, 2, 3}, 3},
    {(int[]){10}, (int[]){20}, 1},
    {(int[]){100, 200}, (int[]){-50, -100}, 2},
    {(int[]){7, 8, 9, 10}, (int[]){1, 2, 3, 4}, 4},
    {(int[]){-5, 0, 5}, (int[]){5, 0, -5}, 3},
    {(int[]){1}, (int[]){999}, 1},
    {(int[]){2, 4, 6, 8, 10}, (int[]){1, 3, 5, 7, 9}, 5},
    {(int[]){15, 25, 35}, (int[]){-10, -20, -30}, 3},
    {(int[]){0}, (int[]){0}, 1},
    {(int[]){-100, -200, -300}, (int[]){100, 200, 300}, 3},
    {(int[]){12, 24, 36, 48}, (int[]){6, 12, 18, 24}, 4},
    {(int[]){1, 1, 1, 1, 1}, (int[]){2, 2, 2, 2, 2}, 5},
    {(int[]){50, 60, 70}, (int[]){-5, -6, -7}, 3},
    {(int[]){999, 888, 777}, (int[]){1, 12, 123}, 3},
    {(int[]){0, 10, 20, 30}, (int[]){5, 15, 25, 35}, 4},
    {(int[]){-1, 0, 1}, (int[]){-1, 0, 1}, 3},
    {(int[]){42}, (int[]){58}, 1},
    {(int[]){3, 6, 9, 12, 15, 18}, (int[]){1, 2, 3, 4, 5, 6}, 6},
    {(int[]){1000, 2000}, (int[]){-500, -1500}, 2},
    {(int[]){11, 22, 33, 44, 55}, (int[]){0, 0, 0, 0, 0}, 5},
    {(int[]){-7, -14, -21}, (int[]){7, 14, 21}, 3},
    {(int[]){9, 8, 7, 6}, (int[]){1, 2, 3, 4}, 4},
    {(int[]){25, 50, 75, 100}, (int[]){25, 50, 75, 100}, 4},
    {(int[]){123, 456}, (int[]){789, 101112}, 2},
    {(int[]){0, -1, -2, -3, -4}, (int[]){0, 1, 2, 3, 4}, 5},
    {(int[]){19, 28, 37}, (int[]){6, 15, 24}, 3},
    {(int[]){5, 10, 15, 20, 25, 30, 35}, (int[]){2, 4, 6, 8, 10, 12, 14}, 7},
    {(int[]){-999, 0, 999}, (int[]){1, -1, 0}, 3}
};
int num_test_cases = 30;


    typedef struct {
        int* result1;
        int* result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z17Change(TestCase t1) {
TestCase follow_case = t1;
// --- 这是根据规则4生成的内存处理代码 ---
int* follow_case_array1 = (int*)malloc(t1.n * sizeof(int));
memcpy(follow_case_array1, t1.array1, t1.n * sizeof(int));
follow_case.array1 = follow_case_array1;
// ------------------------------------

// 这是根据规则6a生成的防御性代码，防止n<=0时出错
if (follow_case.n <= 0) {
    // 数组长度无效，直接返回副本
    return follow_case;
}

// 这是根据规则5生成的具体操作代码
// 使用冒泡排序进行降序排序
for (int i = 0; i < follow_case.n - 1; i++) {
    for (int j = 0; j < follow_case.n - i - 1; j++) {
        if (follow_case.array1[j] < follow_case.array1[j + 1]) {
            // 交换元素
            int temp = follow_case.array1[j];
            follow_case.array1[j] = follow_case.array1[j + 1];
            follow_case.array1[j + 1] = temp;
        }
    }
}

return follow_case;}

#include <cmath>
#include <cfloat>

int z17check(int* result1, int* result2, int n) {
    // 1. 防御性编程 (空指针与长度检查)
    if (result1 == NULL || result2 == NULL) return 0;
    if (n <= 0) return 1;

    // 2. 核心判断逻辑 (字典序比较)
    for (int i = 0; i < n; i++) {
        // 找到第一个不相等的元素对
        if (result1[i] != result2[i]) {
            // 根据这一对元素的大小关系决定结果
            // 条件为 result1[] <= result2[] (lexically)
            if (result1[i] < result2[i]) {
                return 1; // 第一个不相等处 result1[i] < result2[i]，字典序满足 <=
            } else {
                return 0; // 第一个不相等处 result1[i] > result2[i]，字典序不满足 <=
            }
        }
        // 如果相等，继续检查下一个元素
    }

    // 3. 循环结束，所有元素都相等，满足 result1[] <= result2[]
    return 1;
}

TestResult z17runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z17Change(test_cases[test_case_id]);
    // 原始调用
    int* source = s_add(test_cases[test_case_id].array1, test_cases[test_case_id].array2, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    int* follow = s_add(follow_case.array1, follow_case.array2, follow_case.n);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    memory_list[0] = follow_case.array1;
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z17check(source, follow, test_cases[test_case_id].n);
    test_result.status = status;
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z17runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}