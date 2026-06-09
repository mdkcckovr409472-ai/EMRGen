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


int find_min(int a[], int n) {
    int min = a[0];
    int i;
    for (i = 0; i < n; i++) {
        if (a[i] < min) {
            min = a[i];
        }
    }
    return min;
}


typedef struct {
    int* a; int n;
} TestCase;

TestCase test_cases[] = {
    {(int[]){1}, 1},
    {(int[]){1, 2, 3}, 3},
    {(int[]){3, 2, 1}, 3},
    {(int[]){5, 5, 5, 5}, 4},
    {(int[]){-1, 0, 1}, 3},
    {(int[]){10, 20, 30, 40, 50}, 5},
    {(int[]){50, 40, 30, 20, 10}, 5},
    {(int[]){0, 0, 0}, 3},
    {(int[]){100}, 1},
    {(int[]){-5, -10, -3}, 3},
    {(int[]){-10, -5, -3}, 3},
    {(int[]){2, 4, 6, 8, 10, 12}, 6},
    {(int[]){12, 10, 8, 6, 4, 2}, 6},
    {(int[]){7, 3, 9, 1, 5}, 5},
    {(int[]){1, 3, 5, 7, 9}, 5},
    {(int[]){-2, 4, -6, 8, -10}, 5},
    {(int[]){15, 11, 19, 14, 16}, 5},
    {(int[]){100, 200, 150}, 3},
    {(int[]){0, -1, -2, -3}, 4},
    {(int[]){-3, -2, -1, 0}, 4},
    {(int[]){42}, 1},
    {(int[]){6, 2, 8, 4, 10}, 5},
    {(int[]){10, 4, 8, 2, 6}, 5},
    {(int[]){-7, -7, -7}, 3},
    {(int[]){9, 8, 7, 6, 5, 4, 3, 2, 1}, 9},
    {(int[]){1, 2, 3, 4, 5, 6, 7, 8, 9}, 9},
    {(int[]){13, 17, 12, 19, 11}, 5},
    {(int[]){25, 50, 75}, 3},
    {(int[]){-100, -50, -200}, 3},
    {(int[]){8, 3, 8, 1, 8}, 5}
};
int num_test_cases = 30;


    typedef struct {
        int result1;
        int result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z12Change(TestCase t1) {
TestCase follow_case = t1;
// --- 这是根据规则4生成的内存处理代码 ---
int* follow_case_a = (int*)malloc(t1.n * sizeof(int));
memcpy(follow_case_a, t1.a, t1.n * sizeof(int));
follow_case.a = follow_case_a;
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
    int temp = follow_case.a[i];
    follow_case.a[i] = follow_case.a[j];
    follow_case.a[j] = temp;
}

return follow_case;}

int z12check(int result1, int result2) {
    // 1. 核心判断逻辑 (标量直接比较)
    if (!(result1 == result2)) {
        return 0;
    }
    
    // 2. 满足条件，返回 1
    return 1;
}

TestResult z12runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z12Change(test_cases[test_case_id]);
    // 原始调用
    int source = find_min(test_cases[test_case_id].a, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    int follow = find_min(follow_case.a, follow_case.n);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    memory_list[0] = follow_case.a;
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z12check(source, follow);
    test_result.status = status;
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z12runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}