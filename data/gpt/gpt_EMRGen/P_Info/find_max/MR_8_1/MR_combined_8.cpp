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


int find_max(int a[], int n) {
    int max = a[0];
    for (int i = 0; i < n; i++) {
        if (a[i] > max) {
            max = a[i];
        }
    }
    return max;
}


typedef struct {
    int* a; int n;
} TestCase;

TestCase test_cases[] = {
    {(int[]){5}, 1},
    {(int[]){-3, 7, 2}, 3},
    {(int[]){0, 0, 0, 0}, 4},
    {(int[]){10, -5, 10, -5}, 4},
    {(int[]){3, 3, 3}, 3},
    {(int[]){-1, -2, -3, -4, -5}, 5},
    {(int[]){8, 1, 6, 3, 7, 9, 2, 5, 4}, 9},
    {(int[]){2, 2, 5, 1, 5, 3}, 6},
    {(int[]){-10, 0, 10}, 3},
    {(int[]){4, -2, 4, -2, 4}, 5},
    {(int[]){7, 7, 6, 6, 5, 5}, 6},
    {(int[]){1, 2, 3, 2, 1}, 5},
    {(int[]){9, -9, 9, -9, 0}, 5},
    {(int[]){5, 1, 4, 2, 3, 0}, 6},
    {(int[]){0, 5, 0, 5, 0, 5}, 6},
    {(int[]){-3, -3, -2, -2, -1}, 5},
    {(int[]){12, 12, 12, 12}, 4},
    {(int[]){-7, 3, -7, 3, -7}, 5},
    {(int[]){6, 1, 6, 1, 6, 1}, 6},
    {(int[]){-4, 0, 4, -4, 0, 4}, 6},
    {(int[]){2, 8, 5, 3, 9, 1, 7}, 7},
    {(int[]){-5, -10, -3, -8, -2}, 5},
    {(int[]){15, 5, 15, 5, 15, 5, 15}, 7},
    {(int[]){0}, 1},
    {(int[]){-1, 1, -1, 1, -1, 1}, 6},
    {(int[]){3, -3, 3, -3, 3}, 5},
    {(int[]){8, 8, 8, 7, 9}, 5},
    {(int[]){-6, -6, -6, -6, -5}, 5},
    {(int[]){4, 2, 4, 2, 4, 2, 4, 2}, 8},
    {(int[]){5, -2, 5, -2, 5, -2, 5}, 7}
};
int num_test_cases = 30;


    typedef struct {
        int result1;
        int result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z8Change(TestCase t1) {
    TestCase follow_case = t1;
    // Deep copy of array a
    int* follow_case_a = (int*)malloc(t1.n * sizeof(int));
    memcpy(follow_case_a, t1.a, t1.n * sizeof(int));
    follow_case.a = follow_case_a;

    // Defensive check: need at least one element
    if (follow_case.n == 0) {
        return follow_case;
    }

    // Increment a random element by 5
    int idx = rand() % follow_case.n;
    follow_case.a[idx] += 5;

    return follow_case;
}

int z8check(int result1, int result2) {
    if (!(result1 <= result2)) {
        return 0;
    }
    return 1;
}

TestResult z8runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z8Change(test_cases[test_case_id]);
    // 原始调用
    int source = find_max(test_cases[test_case_id].a, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    int follow = find_max(follow_case.a, follow_case.n);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    memory_list[0] = follow_case.a;
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z8check(source, follow);
    test_result.status = status;
    
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z8runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}