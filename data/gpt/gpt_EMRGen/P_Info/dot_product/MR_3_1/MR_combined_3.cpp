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


int dot_product(int a[], int b[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
            sum += a[i] * b[i];
        }
    return sum;
}


typedef struct {
    int* a; int* b; int n;
} TestCase;

TestCase test_cases[] = {
    {(int[]){1, 2, 3}, (int[]){4, 5, 6}, 3},
    {(int[]){}, (int[]){}, 0},
    {(int[]){0}, (int[]){5}, 1},
    {(int[]){-3}, (int[]){7}, 1},
    {(int[]){-1, 2, -3}, (int[]){4, -5, 6}, 3},
    {(int[]){0, 0, 0, 0}, (int[]){0, 0, 0, 0}, 4},
    {(int[]){2, 2, 2}, (int[]){3, 3, 3}, 3},
    {(int[]){1, 1, 1, 1}, (int[]){5, 6, 7, 8}, 4},
    {(int[]){-2, -2, -2}, (int[]){-1, -1, -1}, 3},
    {(int[]){1, 2, 3, 4, 5}, (int[]){5, 4, 3, 2, 1}, 5},
    {(int[]){10, -10}, (int[]){-1, 1}, 2},
    {(int[]){1, 0, -1, 2, -2, 3}, (int[]){3, -3, 2, -2, 1, 0}, 6},
    {(int[]){100, -100}, (int[]){1, 1}, 2},
    {(int[]){1, 1, 1, 1, 1}, (int[]){1, 1, 1, 1, 1}, 5},
    {(int[]){1, -1, 1, -1}, (int[]){-1, 1, -1, 1}, 4},
    {(int[]){7, 8, 9}, (int[]){1, 2, 3}, 3},
    {(int[]){0, 5, 0}, (int[]){10, 0, 20}, 3},
    {(int[]){-5}, (int[]){-5}, 1},
    {(int[]){3, 3}, (int[]){4, 4}, 2},
    {(int[]){-2, 5, -3}, (int[]){7, -8, 9}, 3},
    {(int[]){2, -3, 4, -5}, (int[]){-2, 3, -4, 5}, 4},
    {(int[]){1, 0, 2}, (int[]){3, 4, 5}, 3},
    {(int[]){-1, 2, -3, 4, -5}, (int[]){5, -4, 3, -2, 1}, 5},
    {(int[]){0, 0}, (int[]){0, 0}, 2},
    {(int[]){50, -50, 25}, (int[]){2, 2, 2}, 3},
    {(int[]){1, 2, 1, 2}, (int[]){2, 1, 2, 1}, 4},
    {(int[]){9, 9, 9, 9, 9}, (int[]){1, 2, 3, 4, 5}, 5},
    {(int[]){-10, 1, 1}, (int[]){1, 1, 1}, 3},
    {(int[]){-3, 0, 3, -3}, (int[]){3, 0, -3, 3}, 4},
    {(int[]){0}, (int[]){0}, 1}
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
    // --- Memory handling code generated based on the rule ---
    int* follow_case_a = (int*)malloc(t1.n * sizeof(int));
    memcpy(follow_case_a, t1.a, t1.n * sizeof(int));
    follow_case.a = follow_case_a;
    // ------------------------------------
    
    // Defensive code: ensure there is at least one element to process
    if (follow_case.n == 0) {
        return follow_case;
    }
    
    // Operation: multiply all elements by 2
    for (int i = 0; i < follow_case.n; ++i) {
        follow_case.a[i] *= 2;
    }
    
    return follow_case;
}

int z3check(int result1, int result2) {
    if (!(2 * result1 - result2 == 0)) {
        return 0;
    }
    return 1;
}

TestResult z3runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z3Change(test_cases[test_case_id]);
    // 原始调用
    int source = dot_product(test_cases[test_case_id].a, test_cases[test_case_id].b, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    int follow = dot_product(follow_case.a, follow_case.b, follow_case.n);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    
    
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