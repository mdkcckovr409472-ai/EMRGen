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


int* selection_sort(int list[], int n) {
    int* cp1 = (int*)malloc(n * sizeof(int));
    memcpy(cp1,list,n*sizeof(int));
    int i;
    int j;
    int min;
    for (i = 0; i < n - 1; i++) {
        min = i;
        for (j = i + 1; j < n; j++) {
            if (cp1[j] < cp1[min]) {
                min = j;
            }
        }
        int tmp = cp1[i];
        cp1[i] = cp1[min];
        cp1[min] = tmp;
    }
    return cp1;
}


typedef struct {
    int* list; int n;
} TestCase;

TestCase test_cases[] = {
    { (int[]){}, 0 },
    { (int[]){5}, 1 },
    { (int[]){1, 2}, 2 },
    { (int[]){2, 1}, 2 },
    { (int[]){3, 1, 2}, 3 },
    { (int[]){1, 2, 3}, 3 },
    { (int[]){3, 2, 1}, 3 },
    { (int[]){2, 2, 1, 3}, 4 },
    { (int[]){7, 7, 7, 7}, 4 },
    { (int[]){-3, -1, -2}, 3 },
    { (int[]){0, -5, 5, 2, -1}, 5 },
    { (int[]){0, 0, 1, -1}, 4 },
    { (int[]){8, 3, 5, 2, 9, 1}, 6 },
    { (int[]){4, 2, 4, 2, 5}, 5 },
    { (int[]){1, 2, 3, 4, 5, 6, 7}, 7 },
    { (int[]){7, 6, 5, 4, 3, 2, 1}, 7 },
    { (int[]){10, -2, 8, -5, 3}, 5 },
    { (int[]){15, 3, 12, 7, 9, 0}, 6 },
    { (int[]){100, 20, 50, -30}, 4 },
    { (int[]){-100, 0, 50, -20}, 4 },
    { (int[]){5, -1, 3, 8, -2, 0, 7, 2}, 8 },
    { (int[]){1, 3, 3, 2, 5, 5, 4, 2, 1}, 9 },
    { (int[]){10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, 10 },
    { (int[]){3, 1, 4, 1, 5, 9, 2, 6, 5, 3}, 10 },
    { (int[]){0, 5, 0, 5, 0}, 5 },
    { (int[]){-5, -4, -3, -2, -1}, 5 },
    { (int[]){-50, 20, -30, 40, -10}, 5 },
    { (int[]){12, -1, 6, -7, 3, 0, 9, -2, 8, 5, -3, 4}, 12 },
    { (int[]){0, 0, 0, 0, 0, 0}, 6 },
    { (int[]){-7}, 1 }
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
    // --- Memory handling code generated based on the rule ---
    int* follow_case_list = (int*)malloc(t1.n * sizeof(int));
    memcpy(follow_case_list, t1.list, t1.n * sizeof(int));
    follow_case.list = follow_case_list;
    // ------------------------------------
    
    // Defensive code: ensure there is at least one element
    if (follow_case.n > 0) {
        int idx = rand() % follow_case.n;  // random index 0 ≤ idx < n
        follow_case.list[idx] -= 1;        // decrement element at idx by 1
    }
    
    return follow_case;
}

#include <cmath>
#include <algorithm>

int z6check(int* result1, int* result2, int n) {
    if (n <= 0) return 1;
    if (result1 == NULL || result2 == NULL) return 0;

    for (int i = 0; i < n; i++) {
        if (result1[i] <= result2[i]) return 0;
        else return 1;
    }
    // If all elements equal (loop ends normally), strictly greater requires return 0
    return 0;
}

TestResult z6runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z6Change(test_cases[test_case_id]);
    // 原始调用
    int* source = selection_sort(test_cases[test_case_id].list, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    int* follow = selection_sort(follow_case.list, follow_case.n);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    memory_list[0] = follow_case.list;
    
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