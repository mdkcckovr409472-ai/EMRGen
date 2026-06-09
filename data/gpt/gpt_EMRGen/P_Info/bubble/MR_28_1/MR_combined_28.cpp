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


int* bubble(int a[], int n){
    int* cp1 = (int*)malloc(n * sizeof(int));
    memcpy(cp1, a, n * sizeof(int));
    int t;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (cp1[j] > cp1[j + 1])
            {
                t = cp1[j];
                cp1[j] = cp1[j + 1];
                cp1[j + 1] = t;
            }
        }
    }
    return cp1;
}

typedef struct {
    int* a; int n;
} TestCase;

TestCase test_cases[] = {
    {(int[]){}, 0},
    {(int[]){5}, 1},
    {(int[]){-3, 2}, 2},
    {(int[]){9, -1}, 2},
    {(int[]){4, -2, 7}, 3},
    {(int[]){-5, 0, 3}, 3},
    {(int[]){8, 6, 4}, 3},
    {(int[]){2, 2, 5, 5}, 4},
    {(int[]){7, 7, 7, 7}, 4},
    {(int[]){-4, 0, 3, -1, 5}, 5},
    {(int[]){0, 0, 0, 0, 0}, 5},
    {(int[]){3, -2, 8, 1, -5, 4}, 6},
    {(int[]){-6, -3, -1, 0, 2, 5}, 6},
    {(int[]){9, 7, 5, 3, 1, -1}, 6},
    {(int[]){-10, -5, -2, -2, 0, 3}, 6},
    {(int[]){12, -8, 15, -3, 7, -1, 4}, 7},
    {(int[]){-12, -9, -6, -3, 0, 3, 6}, 7},
    {(int[]){5, 1, 4, 2, 3, 0, -1, -4}, 8},
    {(int[]){-7, -3, -5, -2, -6, -1, -4, -8}, 8},
    {(int[]){1, 3, 2, 4, 5}, 5},
    {(int[]){5, 4, 3, 2, 1}, 5},
    {(int[]){-2, -2, -1, 0, 1, 1}, 6},
    {(int[]){10, -10, 9, -9, 8, -8, 7, -7}, 8},
    {(int[]){3, 3, -1, -1, 2, 2, 0, 0}, 8},
    {(int[]){4, 1, 3, 2}, 4},
    {(int[]){2, 4, 1, 3}, 4},
    {(int[]){-3, 2, -1, 4, -2, 5}, 6},
    {(int[]){7, 2, 5, 3, 8, 1, 6, 4}, 8},
    {(int[]){0, -1, 1, -2, 2, -3, 3, -4}, 8},
    {(int[]){-5, 0, 5, -5, 0, 5}, 6}
};
int num_test_cases = 30;


    typedef struct {
        int* result1;
        int* result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z28Change(TestCase t1) {
    TestCase follow_case = t1;
    // Memory handling: deep copy of array
    int* follow_case_a = (int*)malloc(t1.n * sizeof(int));
    memcpy(follow_case_a, t1.a, t1.n * sizeof(int));
    follow_case.a = follow_case_a;

    // Defensive check: need at least 2 elements for rotation
    if (follow_case.n < 2) {
        return follow_case;
    }

    // Rotate array right by k positions (k random 1..n-1)
    int n = follow_case.n;
    int k = 1 + rand() % (n - 1);

    // Reverse whole array
    for (int i = 0, j = n - 1; i < j; ++i, --j) {
        int tmp = follow_case.a[i];
        follow_case.a[i] = follow_case.a[j];
        follow_case.a[j] = tmp;
    }
    // Reverse first k elements
    for (int i = 0, j = k - 1; i < j; ++i, --j) {
        int tmp = follow_case.a[i];
        follow_case.a[i] = follow_case.a[j];
        follow_case.a[j] = tmp;
    }
    // Reverse remaining n‑k elements
    for (int i = k, j = n - 1; i < j; ++i, --j) {
        int tmp = follow_case.a[i];
        follow_case.a[i] = follow_case.a[j];
        follow_case.a[j] = tmp;
    }

    return follow_case;
}

int z28check(int* result1, int* result2, int n) {
    if (n <= 0) return 1;
    if (result1 == NULL || result2 == NULL) return 0;

    for (int i = 0; i < n; i++) {
        if (!(result1[i] == result2[i])) {
            return 0;
        }
    }

    return 1;
}

TestResult z28runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z28Change(test_cases[test_case_id]);
    // 原始调用
    int* source = bubble(test_cases[test_case_id].a, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    int* follow = bubble(follow_case.a, follow_case.n);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    memory_list[0] = follow_case.a;
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z28check(source, follow, test_cases[test_case_id].n);
    test_result.status = status;
    
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z28runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}