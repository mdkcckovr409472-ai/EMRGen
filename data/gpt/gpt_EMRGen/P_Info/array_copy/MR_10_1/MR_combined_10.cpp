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


int* array_copy(int a[], int n) {
    if (a == NULL || n <= 0) {
        return NULL;
    }


    int* copy = (int*)malloc(n * sizeof(int));
    if (copy == NULL) {
        return NULL;  
    }


    for (int i = 0; i < n; i++) {
        copy[i] = a[i];
    }

    return copy;
}


typedef struct {
    int* a; int n;
} TestCase;

TestCase test_cases[] = {
    {(int[]){7, -3, 42, 150, -60}, 5},
    {(int[]){300, -1000, 45, 78, -22, 13}, 6},
    {(int[]){99, -150, 23, 42, 107}, 5},
    {(int[]){1, -1, 3, -3, 5, -5, 7}, 7},
    {(int[]){22, 0, 51, -250, 130}, 5},
    {(int[]){-444, 222, 333, -555, 0, 1234}, 6},
    {(int[]){150, -150, 300, -300, 600, -600}, 6},
    {(int[]){12, 1300, -500, 220, -10}, 5},
    {(int[]){4000, 100, 0, -100, 50, -500}, 6},
    {(int[]){-900, 435, -870, 220, 180, -60, 70}, 7},
    {(int[]){130, 42, -17, 88, 255}, 5},
    {(int[]){75, 33, 12, -25, 150, -77}, 6},
    {(int[]){5, 200, -200, 1000, -1000}, 5},
    {(int[]){39, -300, 400, -500, 600}, 5},
    {(int[]){1300, 1400, 1500, -1250, -1300}, 5},
    {(int[]){80, -70, 60, -50, 40, -30}, 6},
    {(int[]){123, 234, 345, 456, 567, 678, 789}, 7},
    {(int[]){0, 5, -5, 10, -10, 15, -15}, 7},
    {(int[]){250, -125, 375, -375, 500}, 5},
    {(int[]){-100, 200, -300, 400, -500, 600}, 6},
    {(int[]){3, 6, 2, 8, 7, 9, 1, 4}, 8},
    {(int[]){11, -20, 33, -44, 55}, 5},
    {(int[]){100, 200, 300, -400, -500}, 5},
    {(int[]){9, -18, 27, -36, 45, -54}, 6},
    {(int[]){13, 26, -39, 52, -65}, 5},
    {(int[]){210, -420, 630, -840, 1050}, 5},
    {(int[]){140, 280, -420, 560, -700, 840}, 6},
    {(int[]){7, 14, 21, 28, 35}, 5},
    {(int[]){-123, 234, -345, 456, -567, 678}, 6},
    {(int[]){15, -30, 45, -60, 75}, 5}
};
int num_test_cases = 30;


    typedef struct {
        int* result1;
        int* result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z10Change(TestCase t1) {
    TestCase follow_case = t1;
    // --- Memory handling code generated based on the rule ---
    int* follow_case_a = (int*)malloc(t1.n * sizeof(int));
    if(t1.n > 0 && t1.a != NULL) {
        memcpy(follow_case_a, t1.a, t1.n * sizeof(int));
    }
    follow_case.a = follow_case_a;
    // ------------------------------------
    
    // Defensive code generated based on rule (a) to prevent errors when n < 2
    if (follow_case.n < 2) {
        // Less than 2 elements, no need to sort, return replica directly
        return follow_case;
    }
    
    // Specific operation code generated based on the rule
    // Simple ascending sort - using bubble sort for robustness
    for (int i = 0; i < follow_case.n - 1; i++) {
        for (int j = 0; j < follow_case.n - 1 - i; j++) {
            if (follow_case.a[j] > follow_case.a[j + 1]) {
                int temp = follow_case.a[j];
                follow_case.a[j] = follow_case.a[j + 1];
                follow_case.a[j + 1] = temp;
            }
        }
    }
    
    return follow_case;
}

#include <math.h>
#include <stdbool.h>

int z10check(int* result1, int* result2, int n) {
    // 4.a Length validity check (FIRST)
    if (n <= 0) return 1;
    // 4.b Null pointer check (SECOND)
    if (result1 == NULL || result2 == NULL) return 0;
    
    // Lexicographical comparison for return.result1[] >= return.result2[] (lexically)
    // Since data type is int*, no floating-point tolerance needed.
    for (int i = 0; i < n; i++) {
        if (result1[i] > result2[i]) {
            return 1; // result1[i] > result2[i], lexicographically satisfied
        } else if (result1[i] < result2[i]) {
            return 0; // result1[i] < result2[i], lexicographically violated
        }
        // else equal, continue checking next element
    }
    // All elements equal, >= lexically means satisfied
    return 1;
}

TestResult z10runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z10Change(test_cases[test_case_id]);
    // 原始调用
    int* source = array_copy(test_cases[test_case_id].a, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    int* follow = array_copy(follow_case.a, follow_case.n);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z10check(source, follow, test_cases[test_case_id].n);
    test_result.status = status;
    
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z10runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}