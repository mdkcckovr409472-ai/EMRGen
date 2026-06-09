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


int count_k(int a[], int k, int n) {
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] == k) {
            cnt++;
        }
    }
    return cnt;
}


typedef struct {
    int* a; int k; int n;
} TestCase;

TestCase test_cases[] = {
    {(int[]){1, 2, 3}, 2, 3},
    {(int[]){4, 5, 6}, 1, 3},
    {(int[]){7, 7, 7}, 7, 3},
    {(int[]){}, 0, 0},
    {(int[]){-1, -2, -3, -2}, -2, 4},
    {(int[]){-5, 0, 5, 0, 5}, 5, 5},
    {(int[]){2, 2, 2, 2}, 3, 4},
    {(int[]){9, 1, 2, 3, 9}, 9, 5},
    {(int[]){0, 1, 0, 2, 3}, 0, 5},
    {(int[]){4, 4, 5, 5, 6}, 7, 5},
    {(int[]){1, 3, 5, 7, 9, 1, 3, 5}, 5, 8},
    {(int[]){8}, 8, 1},
    {(int[]){9}, 8, 1},
    {(int[]){2, 3, 2, 4, 2, 5}, 2, 6},
    {(int[]){10, 20, 30, 40}, 5, 4},
    {(int[]){-3, -3, 0, 1}, -3, 4},
    {(int[]){6, 6}, 6, 2},
    {(int[]){6, 7}, 8, 2},
    {(int[]){10, 9, 8, 7, 6, 5}, 10, 6},
    {(int[]){3, 1, 4, 1, 5, 9, 2, 6}, 1, 8},
    {(int[]){0, 0, 0, 0}, 0, 4},
    {(int[]){-1, 2, -3, 4, -5}, 0, 5},
    {(int[]){5, 5, 5, 5, 5, 5, 5}, 5, 7},
    {(int[]){1, 2, 3, 4, 5}, 3, 5},
    {(int[]){-2, 0, 2, 0, -2}, 0, 5},
    {(int[]){8, 6, 7, 5, 3, 0, 9, 1, 2}, 7, 9},
    {(int[]){1, 2, 3, 4, 5, 6, 7, 8, 9}, 10, 9},
    {(int[]){2, 2, 3, 2, 4, 2, 5}, 2, 7},
    {(int[]){-4}, 4, 1},
    {(int[]){1, 0, 1, 0, 1, 0}, 1, 6}
};
int num_test_cases = 30;


    typedef struct {
        int result1;
        int result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z26Change(TestCase t1) {
    TestCase follow_case = t1;
    // Memory handling: deep copy of array a
    int* follow_case_a = (int*)malloc(t1.n * sizeof(int));
    memcpy(follow_case_a, t1.a, t1.n * sizeof(int));
    follow_case.a = follow_case_a;

    // Defensive check: need at least 2 elements to form a subarray
    if (follow_case.n < 2) {
        return follow_case;
    }

    // Rotate a random subarray left by 1
    int start = rand() % (follow_case.n - 1);
    int end = start + 1 + rand() % (follow_case.n - start - 1);
    int temp = follow_case.a[start];
    for (int i = start; i < end; ++i) {
        follow_case.a[i] = follow_case.a[i + 1];
    }
    follow_case.a[end] = temp;

    return follow_case;
}

int z26check(int result1, int result2) {
    if (!(result1 == result2)) {
        return 0;
    }
    return 1;
}

TestResult z26runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z26Change(test_cases[test_case_id]);
    // 原始调用
    int source = count_k(test_cases[test_case_id].a, test_cases[test_case_id].k, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    int follow = count_k(follow_case.a, follow_case.k, follow_case.n);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z26check(source, follow);
    test_result.status = status;
    
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z26runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}