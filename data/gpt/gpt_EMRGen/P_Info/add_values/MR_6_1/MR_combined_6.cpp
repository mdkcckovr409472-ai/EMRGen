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
    { (int[]){}, 0 },
    { (int[]){0}, 1 },
    { (int[]){5}, 1 },
    { (int[]){-3}, 1 },
    { (int[]){1, 2}, 2 },
    { (int[]){-1, -2}, 2 },
    { (int[]){4, -3}, 2 },
    { (int[]){1, -1, 2}, 3 },
    { (int[]){0, 0, 0}, 3 },
    { (int[]){3, -2, 5, -1}, 4 },
    { (int[]){2, 2, 2, 2, 2}, 5 },
    { (int[]){-5, 4, -3, 2, -1}, 5 },
    { (int[]){1, -1, 1, -1, 1, -1}, 6 },
    { (int[]){-2, 3, 0, -1, 4, -3, 2}, 7 },
    { (int[]){10, -10, 5, -5, 0, 1, -1, 2}, 8 },
    { (int[]){0, 0, 1, 2, 3, 0, -1, -2, 0}, 9 },
    { (int[]){-4, 6, -2, 3, -1, 5, -3, 2, -6, 4}, 10 },
    { (int[]){-7, -7, -7, -7}, 4 },
    { (int[]){7, 7, 7, 7, 7}, 5 },
    { (int[]){9, 8, 7, 6, 5}, 5 },
    { (int[]){-9, -8, -7, -6, -5}, 5 },
    { (int[]){0, 1, 0, 2, 0, 3}, 6 },
    { (int[]){0, -1, 0, -2, 0, -3}, 6 },
    { (int[]){-3, -2, -1, 0, 1, 2, 3}, 7 },
    { (int[]){5, -2, 5, -2, 5, -2}, 6 },
    { (int[]){2, 3, 5, 7, 11}, 5 },
    { (int[]){0, 1, 1, 2, 3, 5, 8}, 7 },
    { (int[]){0, -1, -1, -2, -3, -5, -8}, 7 },
    { (int[]){-4, 0, 4, -4, 0, 4}, 6 },
    { (int[]){-3, 7, -2, 6, -1, 5}, 6 }
};
int num_test_cases = 30;


    typedef struct {
        int result1;
        int result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z6Change(TestCase t1) {
    TestCase follow_case = t1;
    // Memory handling code
    int* follow_case_a = (int*)malloc(t1.n * sizeof(int));
    memcpy(follow_case_a, t1.a, t1.n * sizeof(int));
    follow_case.a = follow_case_a;
    // Defensive check for empty array
    if (follow_case.n == 0) {
        return follow_case;
    }
    // Operation: set last element to 100 if less than 100
    if (follow_case.a[follow_case.n - 1] < 100) {
        follow_case.a[follow_case.n - 1] = 100;
    }
    return follow_case;
}

int z6check(int result1, int result2) {
    if (!(result1 <= result2)) {
        return 0;
    }
    return 1;
}

TestResult z6runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z6Change(test_cases[test_case_id]);
    // 原始调用
    int source = add_values(test_cases[test_case_id].a, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    int follow = add_values(follow_case.a, follow_case.n);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z6check(source, follow);
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