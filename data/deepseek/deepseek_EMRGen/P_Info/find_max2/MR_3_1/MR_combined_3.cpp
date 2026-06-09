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


int find_max2(int a[], int n) {
    int max = a[0] + a[1];
    for (int i = 0; i < n - 1; i++) {
        if (a[i] + a[i + 1] > max) {
            max = a[i] + a[i + 1];
        }
    }
    return max;
}


typedef struct {
    int* a; int n;
} TestCase;

TestCase test_cases[] = {
    {(int[]){1, 2, 3, 4}, 4},
    {(int[]){-1, -2, -3}, 3},
    {(int[]){5, 5, 5, 5}, 4},
    {(int[]){10, -10, 20, -20}, 4},
    {(int[]){0, 0, 0, 0, 0}, 5},
    {(int[]){100, 200}, 2},
    {(int[]){-5, 10, -2, 8}, 4},
    {(int[]){1, 2}, 2},
    {(int[]){3, 1, 4, 1, 5}, 5},
    {(int[]){-100, 50, 0, 75}, 4},
    {(int[]){2, 4, 6, 8, 10}, 5},
    {(int[]){9, 8, 7, 6, 5}, 5},
    {(int[]){15, 30, 15}, 3},
    {(int[]){-1, 0, 1, 2, 3}, 5},
    {(int[]){6, 2, 9, 4, 7}, 5},
    {(int[]){20, 10, 30, 5}, 4},
    {(int[]){-8, -3, -7, -1}, 4},
    {(int[]){12, 24, 36, 48}, 4},
    {(int[]){1, 3, 2, 4, 5, 7}, 6},
    {(int[]){-10, 20, -30, 40, -50}, 5},
    {(int[]){50, 40, 30, 20, 10}, 5},
    {(int[]){0, 5, 10, 15, 20}, 5},
    {(int[]){7, 3, 8, 2, 9, 1}, 6},
    {(int[]){-2, -4, -6, -8}, 4},
    {(int[]){11, 22, 33, 44, 55}, 5},
    {(int[]){4, 9, 1, 6, 3}, 5},
    {(int[]){25, 15, 35, 5}, 4},
    {(int[]){-9, -5, -1, -3}, 4},
    {(int[]){13, 17, 19, 23}, 4},
    {(int[]){8, 6, 4, 2, 0}, 5}
};
int num_test_cases = 30;


    typedef struct {
        int result1;
        int result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z3Change(TestCase t1) {
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
        follow_case.a[i] = follow_case.a[i] * 2;
    }
}

return follow_case;}

int z3check(int result1, int result2) {
    // 核心判断逻辑 (标量直接比较)
    // 条件不变式: 2 * return.result1 - return.result2 == 0
    // 移项后等价于: 2 * result1 == result2
    if (!(2 * result1 == result2)) {
        return 0;
    }
    
    // 满足条件，返回 1
    return 1;
}

TestResult z3runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z3Change(test_cases[test_case_id]);
    // 原始调用
    int source = find_max2(test_cases[test_case_id].a, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    int follow = find_max2(follow_case.a, follow_case.n);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    memory_list[0] = follow_case.a;
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z3check(source, follow);
    test_result.status = status;
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z3runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}