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


int* elementwise_max(int a[], int b[], int n) {
    if (a == NULL || b == NULL || n <= 0) {
        return NULL;
    }


    int* result = (int*)malloc(n * sizeof(int));
    if (result == NULL) {
        return NULL;  
    }


    for (int i = 0; i < n; i++) {
        result[i] = (a[i] > b[i]) ? a[i] : b[i];
    }

    return result;
}


typedef struct {
    int* a; int* b; int n;
} TestCase;

TestCase test_cases[] = {
    {(int[]){1, 5, 3}, (int[]){4, 2, 6}, 3},
    {(int[]){10, -50, 30, 200}, (int[]){100, 20, -300, 150}, 4},
    {(int[]){0, -1, 99, 1000}, (int[]){1, -5, 100, 500}, 4},
    {(int[]){-100, 55, 42, 33, 77}, (int[]){-90, 60, 40, 50, 70}, 5},
    {(int[]){300, 200, -300, 0, 800}, (int[]){100, 1000, -500, 1, 700}, 5},
    {(int[]){-10, -20, 30, 40, 50}, (int[]){-30, 50, 25, 35, 60}, 5},
    {(int[]){13, 17, 9, 5, 0, 20}, (int[]){12, 14, 15, 6, -1, 19}, 6},
    {(int[]){1000, -1000, 300, 400, -500}, (int[]){-100, 1000, 500, -300, 0}, 5},
    {(int[]){42, 600, 1200, 50}, (int[]){43, 590, 1000, 100}, 4},
    {(int[]){-999, 0, 999, 123}, (int[]){-1000, 1, 800, 200}, 4},
    {(int[]){700, 800, 900}, (int[]){800, 700, 1000}, 3},
    {(int[]){1, -1, 2, -2, 3, -3}, (int[]){1, 1, -2, 2, -3, 3}, 6},
    {(int[]){214, 0, -214}, (int[]){200, 100, -250}, 3},
    {(int[]){-600, 700, 800, -900, 1000}, (int[]){-700, 600, 900, -800, 1100}, 5},
    {(int[]){50, 49, 48, 47, 46}, (int[]){46, 47, 48, 49, 50}, 5},
    {(int[]){150, -150, 0}, (int[]){-150, 150, 0}, 3},
    {(int[]){333, 444, 555}, (int[]){555, 444, 333}, 3},
    {(int[]){20, -20, 30, -30}, (int[]){-20, 20, -30, 30}, 4},
    {(int[]){100, 200, 300, 400, 500}, (int[]){500, 400, 300, 200, 100}, 5},
    {(int[]){-123, 456, -789, 1011, -1213}, (int[]){-321, 654, -987, 1110, -1312}, 5},
    {(int[]){5, 10, 15, 20, 25}, (int[]){25, 20, 15, 10, 5}, 5},
    {(int[]){3000, -3000, 1500}, (int[]){-1500, 3000, -3000}, 3},
    {(int[]){123, 312, 231, 132}, (int[]){321, 213, 312, 123}, 4},
    {(int[]){-555, 555, -444, 444}, (int[]){444, -444, 555, -555}, 4},
    {(int[]){700, 900, 1100}, (int[]){800, 1000, 1200}, 3},
    {(int[]){-1, -2, -3, -4, -5}, (int[]){-5, -4, -3, -2, -1}, 5},
    {(int[]){0, 1000, 2000, 3000}, (int[]){1000, 0, 3000, 2000}, 4},
    {(int[]){11, 22, 33, 44, 55}, (int[]){55, 44, 33, 22, 11}, 5},
    {(int[]){999, -999, 888, -888}, (int[]){-888, 888, -999, 999}, 4}
};
int num_test_cases = 29;


    typedef struct {
        int* result1;
        int* result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z42Change(TestCase t1) {
    TestCase follow_case = t1;
    // --- Memory handling code generated based on the rule ---
    int* follow_case_b = (int*)malloc(t1.n * sizeof(int));
    if (follow_case_b == NULL) {
        // malloc failed, return original
        return follow_case;
    }
    memcpy(follow_case_b, t1.b, t1.n * sizeof(int));
    follow_case.b = follow_case_b;
    // ------------------------------------
    
    // Defensive code generated based on rule (a) to prevent errors when n < 1
    if (follow_case.n <= 0) {
        // No elements to process, return replica directly
        return follow_case;
    }
    
    // Specific operation code generated based on the rule
    for (int i = 0; i < follow_case.n; i++) {
        if (follow_case.b[i] < 0) {
            follow_case.b[i] = -follow_case.b[i];
        }
    }
    
    return follow_case;
}

int z42check(int* result1, int* result2, int n) {
    if (n <= 0) return 1;
    if (result1 == NULL || result2 == NULL) return 0;

    for (int i = 0; i < n; i++) {
        if (!(result1[i] <= result2[i])) {
            return 0;
        }
    }
    return 1;
}

TestResult z42runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z42Change(test_cases[test_case_id]);
    // 原始调用
    int* source = elementwise_max(test_cases[test_case_id].a, test_cases[test_case_id].b, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    int* follow = elementwise_max(follow_case.a, follow_case.b, follow_case.n);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z42check(source, follow, test_cases[test_case_id].n);
    test_result.status = status;
    
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z42runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}