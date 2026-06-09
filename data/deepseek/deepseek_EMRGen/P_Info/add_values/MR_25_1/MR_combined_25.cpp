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


int add_values(int a[], int n) {
    int sum = 0;

    for (int i = 0; i < n; i++) {
        sum += a[i];
    }
    return sum;
}


typedef struct {
    int* a; int n;
} TestCase;

TestCase test_cases[] = {
    {(int[]){1, 2, 3}, 3},
    {(int[]){5}, 1},
    {(int[]){-1, 0, 1}, 3},
    {(int[]){10, 20, 30, 40}, 4},
    {(int[]){-10, -20, -30}, 3},
    {(int[]){100, 200, 300, 400, 500}, 5},
    {(int[]){0, 0, 0, 0}, 4},
    {(int[]){2, 4, 6, 8, 10, 12}, 6},
    {(int[]){-5, 10, -15, 20}, 4},
    {(int[]){1}, 1},
    {(int[]){-1, -2, -3, -4, -5}, 5},
    {(int[]){7, 14, 21}, 3},
    {(int[]){0}, 1},
    {(int[]){50, 25, 12, 6}, 4},
    {(int[]){-100, 100, -200, 200}, 4},
    {(int[]){9, 8, 7, 6, 5, 4, 3, 2, 1}, 9},
    {(int[]){15, 30, 45, 60, 75}, 5},
    {(int[]){-3, -6, -9, -12}, 4},
    {(int[]){11, 22, 33, 44, 55, 66}, 6},
    {(int[]){0, 10, 0, 20, 0}, 5},
    {(int[]){999, 1}, 2},
    {(int[]){-50, 0, 50}, 3},
    {(int[]){4, 8, 12, 16, 20, 24, 28}, 7},
    {(int[]){-1, 1, -2, 2, -3, 3}, 6},
    {(int[]){19, 27, 35}, 3},
    {(int[]){1000, 2000, 3000}, 3},
    {(int[]){-8, -4, 0, 4, 8}, 5},
    {(int[]){6, 12, 18, 24, 30, 36}, 6},
    {(int[]){-25, 50, -75, 100}, 4},
    {(int[]){13, 26, 39, 52, 65, 78, 91}, 7}
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
if (follow_case.n <= 0) {
    // 数组为空或长度为负，无法进行移位操作，直接返回副本
    return follow_case;
}

// 这是根据规则5生成的具体操作代码
int last_element = follow_case.a[follow_case.n - 1];
for (int i = follow_case.n - 1; i > 0; i--) {
    follow_case.a[i] = follow_case.a[i - 1];
}
follow_case.a[0] = last_element;

return follow_case;}

int z25check(int result1, int result2) {
    // 1. 核心判断逻辑 (标量直接比较)
    if (!(result1 == result2)) {
        return 0;
    }
    
    // 2. 满足条件，返回 1
    return 1;
}

TestResult z25runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z25Change(test_cases[test_case_id]);
    // 原始调用
    int source = add_values(test_cases[test_case_id].a, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    int follow = add_values(follow_case.a, follow_case.n);
    
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