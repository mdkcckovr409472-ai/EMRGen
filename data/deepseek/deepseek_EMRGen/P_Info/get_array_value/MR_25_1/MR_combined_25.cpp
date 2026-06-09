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


int get_array_value(int a[], int k, int n) {
        return a[k - 1];
}


typedef struct {
    int* a; int k; int n;
} TestCase;

TestCase test_cases[] = {
    {(int[]){10, 20, 30, 40, 50}, 1, 5},
    {(int[]){10, 20, 30, 40, 50}, 3, 5},
    {(int[]){10, 20, 30, 40, 50}, 5, 5},
    {(int[]){7}, 1, 1},
    {(int[]){-1, 0, 1}, 1, 3},
    {(int[]){-1, 0, 1}, 2, 3},
    {(int[]){-1, 0, 1}, 3, 3},
    {(int[]){100, 200, 300, 400}, 2, 4},
    {(int[]){100, 200, 300, 400}, 4, 4},
    {(int[]){5, 4, 3, 2, 1}, 1, 5},
    {(int[]){5, 4, 3, 2, 1}, 5, 5},
    {(int[]){0, 0, 0, 0}, 2, 4},
    {(int[]){15, 25, 35}, 1, 3},
    {(int[]){15, 25, 35}, 2, 3},
    {(int[]){15, 25, 35}, 3, 3},
    {(int[]){2, 4, 6, 8, 10, 12}, 3, 6},
    {(int[]){2, 4, 6, 8, 10, 12}, 6, 6},
    {(int[]){-10, -20, -30}, 1, 3},
    {(int[]){-10, -20, -30}, 3, 3},
    {(int[]){1, 3, 5, 7, 9, 11, 13}, 4, 7},
    {(int[]){1, 3, 5, 7, 9, 11, 13}, 7, 7},
    {(int[]){42}, 1, 1},
    {(int[]){8, 6, 7, 5, 3, 0, 9}, 1, 7},
    {(int[]){8, 6, 7, 5, 3, 0, 9}, 4, 7},
    {(int[]){8, 6, 7, 5, 3, 0, 9}, 7, 7},
    {(int[]){1000, 2000, 3000}, 2, 3},
    {(int[]){-5, -3, -1, 1, 3, 5}, 3, 6},
    {(int[]){-5, -3, -1, 1, 3, 5}, 5, 6},
    {(int[]){9, 8, 7, 6, 5}, 2, 5},
    {(int[]){9, 8, 7, 6, 5}, 5, 5}
};
int num_test_cases = 30;


    typedef struct {
        int result1;
        int result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z25Change(TestCase t1) {
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
        if (follow_case.a[i] > 50) {
            follow_case.a[i] = 50;
        }
    }
}

return follow_case;}

int z25check(int result1, int result2) {
    // 1. 核心判断逻辑 (标量直接比较)
    if (!(result1 >= result2)) {
        return 0;
    }

    // 2. 满足条件，返回 1
    return 1;
}

TestResult z25runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z25Change(test_cases[test_case_id]);
    // 原始调用
    int source = get_array_value(test_cases[test_case_id].a, test_cases[test_case_id].k, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    int follow = get_array_value(follow_case.a, follow_case.k, follow_case.n);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    memory_list[0] = follow_case.a;
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z25check(source, follow);
    test_result.status = status;
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z25runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}