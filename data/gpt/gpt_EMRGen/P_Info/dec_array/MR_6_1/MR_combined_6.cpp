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


int* dec_array(int a[], int k, int n) {
    int* cp1 = (int*)malloc(n * sizeof(int));
    memcpy(cp1,a,n*sizeof(int));
    for (int i = 0; i < n; i++) {
        cp1[i] -= k;
    }
    return cp1;
}


typedef struct {
    int* a; int k; int n;
} TestCase;

TestCase test_cases[] = {
    { (int[]){}, 0, 0 },
    { (int[]){5}, 2, 1 },
    { (int[]){0, 0, 0}, 0, 3 },
    { (int[]){1, 2, 3, 4, 5}, 1, 5 },
    { (int[]){10, -5, 3}, -2, 3 },
    { (int[]){7, 7, 7, 7}, 5, 4 },
    { (int[]){-3, 8, -1, 4}, 3, 4 },
    { (int[]){2, -2, 2, -2}, 0, 4 },
    { (int[]){9, 1, 8, 2, 7, 3, 6, 4, 5}, 4, 9 },
    { (int[]){15, 10, 5, 0, -5}, 5, 5 },
    { (int[]){100, 50, -50, -100}, 20, 4 },
    { (int[]){1, 1, 2, 3, 5, 8, 13}, 1, 7 },
    { (int[]){-10, -5, 0, 5, 10}, -5, 5 },
    { (int[]){3, 6, 9, 12}, 3, 4 },
    { (int[]){-1, -2, -3, -4}, 2, 4 },
    { (int[]){0}, 10, 1 },
    { (int[]){5, -5, 5, -5, 5}, -5, 5 },
    { (int[]){2, 4, 6, 8, 10}, 1, 5 },
    { (int[]){7}, 0, 1 },
    { (int[]){-8, 0, 8}, 8, 3 },
    { (int[]){1, 3, 5, 7, 9, 11}, 2, 6 },
    { (int[]){12, 6, 0, -6, -12}, -6, 5 },
    { (int[]){4, 4, 4, 4, 4, 4}, 4, 6 },
    { (int[]){-3, -1, 1, 3}, 1, 4 },
    { (int[]){0, 5, 10, 15, 20}, 5, 5 },
    { (int[]){-2, 2, -2, 2, -2, 2}, 0, 6 },
    { (int[]){9, -9, 9, -9}, 9, 4 },
    { (int[]){1, 2}, 3, 2 },
    { (int[]){20}, 20, 1 },
    { (int[]){-5, 0, 5}, -5, 3 }
};
int num_test_cases = 30;


    typedef struct {
        int* result1;
        int* result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z6Change(TestCase t1) {
    TestCase follow_case = t1;
    // --- Memory handling code ---
    int* follow_case_a = (int*)malloc(t1.n * sizeof(int));
    memcpy(follow_case_a, t1.a, t1.n * sizeof(int));
    follow_case.a = follow_case_a;
    // -------------------------

    // Defensive check: need at least one element
    if (follow_case.n <= 0) {
        return follow_case;
    }

    // Operation: increment a random element by 5 if it does not overflow
    int idx = rand() % follow_case.n;
    if (follow_case.a[idx] <= INT_MAX - 5) {
        follow_case.a[idx] += 5;
    }

    return follow_case;
}

int z6check(int* result1, int* result2, int n) {
    if (n <= 0) return 1;
    if (result1 == NULL || result2 == NULL) return 0;

    for (int i = 0; i < n; i++) {
        int A = result1[i];
        int B = result2[i];
        if (!(A < B)) {
            return 0;
        } else {
            // Found first unequal pair with result1[i] < result2[i], lexically less, condition satisfied
            return 1;
        }
    }

    // If all elements are equal, lexically < fails
    return 0;
}

TestResult z6runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z6Change(test_cases[test_case_id]);
    // 原始调用
    int* source = dec_array(test_cases[test_case_id].a, test_cases[test_case_id].k, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    int* follow = dec_array(follow_case.a, follow_case.k, follow_case.n);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z6check(source, follow, test_cases[test_case_id].n);
    test_result.status = status;
    
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z6runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}