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


int sum(int values[],  int n) {
    int sum = 0;
    for (int i = 0; i < n; i++){
        sum += values[i];
}
    return sum;
}


typedef struct {
    int* values; int n;
} TestCase;

TestCase test_cases[] = {
    {(int[]){1, 2, 3}, 3},
    {(int[]){0}, 1},
    {(int[]){-1, 1}, 2},
    {(int[]){10, 20, 30, 40, 50}, 5},
    {(int[]){-5, -4, -3, -2, -1}, 5},
    {(int[]){100}, 1},
    {(int[]){0, 0, 0, 0}, 4},
    {(int[]){1, -1, 2, -2, 3, -3}, 6},
    {(int[]){2147483647, 0, -2147483648}, 3},
    {(int[]){1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 10},
    {(int[]){-10, -20, -30}, 3},
    {(int[]){5}, 1},
    {(int[]){2, 4, 6, 8}, 4},
    {(int[]){-1, -2, -3, -4, -5}, 5},
    {(int[]){100, 200, 300}, 3},
    {(int[]){15, 25, 35, 45}, 4},
    {(int[]){-100, 100, -200, 200}, 4},
    {(int[]){0, 10, 0, 20, 0}, 5},
    {(int[]){1, 0, 0, 0, 1}, 5},
    {(int[]){-7, 8, -9, 10}, 4},
    {(int[]){50, 60, 70, 80, 90, 100}, 6},
    {(int[]){-50, -60, -70}, 3},
    {(int[]){12, 24, 36}, 3},
    {(int[]){1, 3, 5, 7, 9, 11, 13}, 7},
    {(int[]){-2, 4, -6, 8, -10}, 5},
    {(int[]){999, -999, 1000, -1000}, 4},
    {(int[]){0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, 10},
    {(int[]){-15, -25, -35, -45, -55}, 5},
    {(int[]){42}, 1},
    {(int[]){6, 12, 18, 24, 30, 36}, 6}
};
int num_test_cases = 30;


    typedef struct {
        int result1;
        int result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z19Change(TestCase t1) {
    TestCase follow_case = t1;
    // --- 这是根据规则4生成的内存处理代码 ---
    int* follow_case_values = (int*)malloc(t1.n * sizeof(int));
    memcpy(follow_case_values, t1.values, t1.n * sizeof(int));
    follow_case.values = follow_case_values;
    // ------------------------------------

    // 这是根据规则6a生成的防御性代码，防止n<2时出错
    if (follow_case.n < 2) {
        // 元素不足2个，无法进行随机重排序，直接返回副本
        return follow_case;
    }

    // 这是根据规则5生成的具体操作代码
    srand(time(NULL));
    for (int i = follow_case.n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = follow_case.values[i];
        follow_case.values[i] = follow_case.values[j];
        follow_case.values[j] = temp;
    }

    return follow_case;}

int z19check(int result1, int result2) {
    // 1. 核心判断逻辑 (标量直接比较)
    if (!(result1 == result2)) {
        return 0;
    }
    
    // 2. 满足条件，返回 1
    return 1;
}

TestResult z19runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z19Change(test_cases[test_case_id]);
    // 原始调用
    int source = sum(test_cases[test_case_id].values, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    int follow = sum(follow_case.values, follow_case.n);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    memory_list[0] = follow_case.values;
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z19check(source, follow);
    test_result.status = status;
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z19runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}