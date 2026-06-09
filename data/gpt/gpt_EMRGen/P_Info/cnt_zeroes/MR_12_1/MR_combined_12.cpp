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


int cnt_zeroes(int a[], int n){
    int cnt = 0;
    for (int i = 0; i < n; i++)
    {
        if (a[i] == 0)
        {
            cnt ++;
        }
    }
        return cnt;
    }
    


typedef struct {
    int* a; int n;
} TestCase;

TestCase test_cases[] = {
    { (int[]){}, 0 },
    { (int[]){0}, 1 },
    { (int[]){5}, 1 },
    { (int[]){0, 0}, 2 },
    { (int[]){3, -2}, 2 },
    { (int[]){0, 7, 0}, 3 },
    { (int[]){1, 2, 3, 4, 5}, 5 },
    { (int[]){0, 0, 0, 0, 0}, 5 },
    { (int[]){-1, -2, -3, -4, -5}, 5 },
    { (int[]){0, -1, 2, 0, -3}, 5 },
    { (int[]){7, 0, 8, 0, 9}, 5 },
    { (int[]){1, 0, 1, 0, 1, 0}, 6 },
    { (int[]){0, 2, 4, 6, 8, 10}, 6 },
    { (int[]){-5, 0, 5, 0, -5, 5}, 6 },
    { (int[]){3, 0, -3, 0, 3, -3, 0}, 7 },
    { (int[]){0, 1, 0, 2, 0, 3, 0}, 7 },
    { (int[]){-7, -6, -5, -4, -3, -2, -1}, 7 },
    { (int[]){9, 8, 7, 6, 5, 4, 3}, 7 },
    { (int[]){0, 0, 1, 1, 2, 2, 3, 3}, 8 },
    { (int[]){4, 5, 6, 7, 8, 9, 10, 11}, 8 },
    { (int[]){-10, 0, 10, 0, -10, 0, 10, 0}, 8 },
    { (int[]){0, -2, 4, -6, 8, -10, 12, -14, 16}, 9 },
    { (int[]){1, -1, 2, -2, 3, -3, 4, -4, 5}, 9 },
    { (int[]){0, 0, 0, 1, 2, 3, 4, 5, 6}, 9 },
    { (int[]){7, 8, 9, 0, 0, 0, 10, 11, 12}, 9 },
    { (int[]){-3, -2, -1, 0, 1, 2, 3, 0, 0, 0}, 10 },
    { (int[]){5, 4, 3, 2, 1, 0, -1, -2, -3, -4}, 10 },
    { (int[]){0, 1, 0, 2, 0, 3, 0, 4, 0, 5}, 10 },
    { (int[]){6, 0, 7, 0, 8, 0, 9, 0, 10, 0}, 10 },
    { (int[]){0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 11 },
    { (int[]){1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}, 11 }
};
int num_test_cases = 31;


    typedef struct {
        int result1;
        int result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z12Change(TestCase t1) {
    TestCase follow_case = t1;
    // --- Memory handling code generated based on the rule ---
    int* follow_case_a = (int*)malloc(t1.n * sizeof(int));
    memcpy(follow_case_a, t1.a, t1.n * sizeof(int));
    follow_case.a = follow_case_a;
    // ------------------------------------
    
    // Defensive code generated based on rule (a) to prevent errors when n == 0
    if (follow_case.n == 0) {
        return follow_case;
    }
    
    // Specific operation code: replace each element with its square
    for (int i = 0; i < follow_case.n; ++i) {
        follow_case.a[i] = follow_case.a[i] * follow_case.a[i];
    }
    
    return follow_case;
}

int z12check(int result1, int result2) {
    if (!(result1 == result2)) {
        return 0;
    }
    return 1;
}

TestResult z12runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z12Change(test_cases[test_case_id]);
    // 原始调用
    int source = cnt_zeroes(test_cases[test_case_id].a, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    int follow = cnt_zeroes(follow_case.a, follow_case.n);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z12check(source, follow);
    test_result.status = status;
    
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z12runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}