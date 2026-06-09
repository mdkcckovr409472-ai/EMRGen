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


int* shell_sort(int a[], int n) {
    int* cp1 = (int*)malloc(n * sizeof(int));
    memcpy(cp1,a,n*sizeof(int));
    int j;
    int i;
    int k;
    int m;
    int mid;
        
    for (m = n/2; m > 0; m /= 2) {
        for (j = m; j < n; j++) {
            for (i = j - m; i >= 0; i -= m) {
                if (cp1[i + m] >= cp1[i]) {
                    break;
                } else {
                    mid = cp1[i];
                    cp1[i] = cp1[i + m];
                    cp1[i + m] = mid;
                }
            }
        }
    }
    return cp1;
}


typedef struct {
    int* a; int n;
} TestCase;

TestCase test_cases[] = {
    { (int[]){5, 2, 9, 1, 5, 6}, 6 },
    { (int[]){1, 2, 3, 4, 5}, 5 },
    { (int[]){9, 8, 7, 6, 5, 4}, 6 },
    { (int[]){3, 3, 3, 3}, 4 },
    { (int[]){-3, -1, -7, 2, 0}, 5 },
    { (int[]){42}, 1 },
    { (int[]){1, 2}, 2 },
    { (int[]){2, 1}, 2 },
    { (int[]){}, 0 },
    { (int[]){0, 5, 0, 3, 0}, 5 },
    { (int[]){12, 4, 7, 3, 9, 1, 8, 6, 2, 10, 5, 11}, 12 },
    { (int[]){4, 2, 4, 2, 4}, 5 },
    { (int[]){-10, 5, -3, 8, -2, 0}, 6 },
    { (int[]){1, 1, 2, 2, 3, 3}, 6 },
    { (int[]){5, 5, 4, 4, 3, 3, 2, 2, 1, 1}, 10 },
    { (int[]){100, -50, 30, -20, 0, 50}, 6 },
    { (int[]){2, 3, 5, 7, 11, 13, 17}, 7 },
    { (int[]){0, 1, 1, 2, 3, 5, 8, 13, 21}, 9 },
    { (int[]){100, 1, 99, 2, 98, 3, 97, 4}, 8 },
    { (int[]){0, 0, 0, 0, 0}, 5 },
    { (int[]){-1, -2, -3, -4, -5}, 5 },
    { (int[]){-5, -3, 0, 2, 4}, 5 },
    { (int[]){5, 3, 0, -2, -4}, 5 },
    { (int[]){7, -2, 5}, 3 },
    { (int[]){3, 1, 4, 1, 5, 9, 2, 6, 5}, 9 },
    { (int[]){8, 3, 6, 2, 7, 5, 1, 4}, 8 },
    { (int[]){-1000, 500, -250, 250, 0}, 5 },
    { (int[]){-10, -5, 0, 5, 10}, 5 },
    { (int[]){10, 5, 0, -5, -10}, 5 },
    { (int[]){200, -150, 75, -25, 50, -75, 125}, 7 }
};
int num_test_cases = 30;


    typedef struct {
        int* result1;
        int* result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z17Change(TestCase t1) {
    TestCase follow_case = t1;
    // --- Memory handling code ---
    int* follow_case_a = (int*)malloc(t1.n * sizeof(int));
    memcpy(follow_case_a, t1.a, t1.n * sizeof(int));
    follow_case.a = follow_case_a;
    // ----------------------------
    
    // Defensive check: ensure array has at least one element
    if (follow_case.n == 0) {
        return follow_case;
    }
    
    // Set a random position's element to -999 (when element > -999)
    int idx = rand() % follow_case.n;
    if (follow_case.a[idx] > -999) {
        follow_case.a[idx] = -999;
    }
    
    return follow_case;
}

int z17check(int* result1, int* result2, int n) {
    // 1. Defensive programming (Length check first)
    if (n <= 0) return 1;
    
    // 2. Defensive programming (Null pointer check after length check)
    if (result1 == NULL || result2 == NULL) return 0;

    // 3. Core evaluation logic (elementwise)
    for (int i = 0; i < n; i++) {
        if (!(result1[i] >= result2[i])) {
            return 0; // Return 0 immediately upon any violation
        }
    }

    // 4. Fully satisfied, return 1
    return 1;
}

TestResult z17runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z17Change(test_cases[test_case_id]);
    // 原始调用
    int* source = shell_sort(test_cases[test_case_id].a, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    int* follow = shell_sort(follow_case.a, follow_case.n);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z17check(source, follow, test_cases[test_case_id].n);
    test_result.status = status;
    
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z17runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}