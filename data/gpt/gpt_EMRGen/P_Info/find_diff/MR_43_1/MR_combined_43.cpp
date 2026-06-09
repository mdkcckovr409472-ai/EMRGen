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


int*  find_diff(int a[], int b[], int na) {
    int* c = (int*)malloc(na * sizeof(int));
    for (int i = 0; i < na; i++) {
        c[i] = a[i] - b[i];
    }
    return c;
}


typedef struct {
    int* a; int* b; int na;
} TestCase;

TestCase test_cases[] = {
    {(int[]){5, 2, -3}, (int[]){1, 4, -3}, 3},
    {(int[]){0}, (int[]){0}, 1},
    {(int[]){10, -10, 5, -5}, (int[]){5, -5, 5, -5}, 4},
    {(int[]){}, (int[]){}, 0},
    {(int[]){100, 200, 300}, (int[]){300, 200, 100}, 3},
    {(int[]){-1, -2, -3, -4}, (int[]){1, 2, 3, 4}, 4},
    {(int[]){7, 14, 21}, (int[]){3, 6, 9}, 3},
    {(int[]){42, 0, -42}, (int[]){0, 0, 0}, 3},
    {(int[]){1, 1, 1, 1, 1}, (int[]){2, 2, 2, 2, 2}, 5},
    {(int[]){9, 8, 7, 6, 5}, (int[]){5, 6, 7, 8, 9}, 5},
    {(int[]){123, -456, 789}, (int[]){321, -654, 987}, 3},
    {(int[]){0, 1, 0, 1}, (int[]){1, 0, 1, 0}, 4},
    {(int[]){15, 30, 45, 60}, (int[]){5, 10, 15, 20}, 4},
    {(int[]){-100, 50, -25}, (int[]){100, -50, 25}, 3},
    {(int[]){2, 4, 8, 16, 32, 64}, (int[]){1, 2, 4, 8, 16, 32}, 6},
    {(int[]){7}, (int[]){3}, 1},
    {(int[]){3, -3, 3, -3}, (int[]){-3, 3, -3, 3}, 4},
    {(int[]){0, -1, 2, -3, 4}, (int[]){0, 1, -2, 3, -4}, 5},
    {(int[]){5, 10, 15}, (int[]){5, 10, 15}, 3},
    {(int[]){99, 1, 99, 1}, (int[]){1, 99, 1, 99}, 4},
    {(int[]){-5, 0, 5}, (int[]){5, 0, -5}, 3},
    {(int[]){8, 6, 7, 5, 3, 0, 9}, (int[]){0, 1, 2, 3, 4, 5, 6}, 7},
    {(int[]){-10, -20, -30}, (int[]){-30, -20, -10}, 3},
    {(int[]){1000, -1000}, (int[]){-1000, 1000}, 2},
    {(int[]){1, 2, 3, 4, 5}, (int[]){5, 4, 3, 2, 1}, 5},
    {(int[]){-1, 0, 1}, (int[]){1, 0, -1}, 3},
    {(int[]){11, 22, 33, 44}, (int[]){44, 33, 22, 11}, 4},
    {(int[]){0, 0, 0, 0, 0}, (int[]){0, 0, 0, 0, 0}, 5},
    {(int[]){12345, -12345, 0}, (int[]){-12345, 12345, 0}, 3},
    {(int[]){7, 14, 21, 28}, (int[]){28, 21, 14, 7}, 4}
};
int num_test_cases = 30;


    typedef struct {
        int* result1;
        int* result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z43Change(TestCase t1) {
    TestCase follow_case = t1;
    // --- Memory handling code generated based on the rule ---
    int* follow_case_b = (int*)malloc(t1.na * sizeof(int));
    memcpy(follow_case_b, t1.b, t1.na * sizeof(int));
    follow_case.b = follow_case_b;
    // ------------------------------------
    
    // Defensive code generated based on rule (a) to prevent errors when array is empty
    if (follow_case.na == 0) {
        return follow_case;
    }
    
    // Specific operation code: subtract 4 from every element of b
    for (int i = 0; i < follow_case.na; ++i) {
        follow_case.b[i] -= 4;
    }
    
    return follow_case;
}

int z43check(int* result1, int* result2, int n) {
    // 4.a Length validity check
    if (n <= 0) return 1;
    // 4.b Null pointer check
    if (result1 == NULL || result2 == NULL) return 0;

    // 2. Core evaluation logic (elementwise)
    // Condition: return.result1[] - return.result2[] + 4 == 0
    // Rearranged: result1[i] == result2[i] - 4
    for (int i = 0; i < n; i++) {
        if (!(result1[i] - result2[i] + 4 == 0)) {
            return 0;
        }
    }

    // 3. Fully satisfied
    return 1;
}

TestResult z43runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z43Change(test_cases[test_case_id]);
    // 原始调用
    int* source = find_diff(test_cases[test_case_id].a, test_cases[test_case_id].b, test_cases[test_case_id].na); // MODIFIED: Explicit type
    // 变换后调用
    int* follow = find_diff(follow_case.a, follow_case.b, follow_case.na);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    memory_list[0] = follow_case.b;
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z43check(source, follow, test_cases[test_case_id].na);
    test_result.status = status;
    
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z43runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}