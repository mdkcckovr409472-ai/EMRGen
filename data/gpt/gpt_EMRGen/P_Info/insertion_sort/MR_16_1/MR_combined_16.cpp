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


int* insertion_sort(int array[], int n) {
    int* cp1 = (int*)malloc(n * sizeof(int));
    memcpy(cp1,array,n*sizeof(int));
    for (int i = 1; i < n; i++) {
        int j = i;
        int B = cp1[i];
        while (j > 0 && cp1[j - 1] > B) {
            cp1[j] = cp1[j - 1];
            j--;
        }
        cp1[j] = B;
        }
    
    return cp1;
}


typedef struct {
    int* array; int n;
} TestCase;

TestCase test_cases[] = {
    {(int[]){}, 0},
    {(int[]){5}, 1},
    {(int[]){1, 2}, 2},
    {(int[]){2, 1}, 2},
    {(int[]){-3, -1, 0, 2, 5}, 5},
    {(int[]){9, 7, 5, 3, 1}, 5},
    {(int[]){3, -2, 7, 1, 0}, 5},
    {(int[]){4, 4, 4, 4}, 4},
    {(int[]){2, 3, 2, 1, 3}, 5},
    {(int[]){-5, -2, -9, -1}, 4},
    {(int[]){-3, 2, -1, 4, 0}, 5},
    {(int[]){1, 2, 2, 3, 4}, 5},
    {(int[]){5, 4, 4, 3, 2}, 5},
    {(int[]){0, 5, -3, 8, -2, 7, 1, 4, -1, 3}, 10},
    {(int[]){0, 0, 0, 0}, 4},
    {(int[]){10, -10, 9, -9, 8, -8}, 6},
    {(int[]){1, 2, 6, 4, 5}, 5},
    {(int[]){-7}, 1},
    {(int[]){-5, -5}, 2},
    {(int[]){6, -3, 5, -2, 4}, 5},
    {(int[]){-5, -4, -3, -2, -1}, 5},
    {(int[]){-1, -2, -3, -4, -5}, 5},
    {(int[]){0, -1, 2, -3, 4}, 5},
    {(int[]){3, 1, 4, 1, 5, 9, 2, 6}, 8},
    {(int[]){-2, 8, -5, 3, 0, -1, 7, -3, 2}, 9},
    {(int[]){0}, 1},
    {(int[]){0, 5}, 2},
    {(int[]){0, -2}, 2},
    {(int[]){7, -3, 5}, 3}
};
int num_test_cases = 29;


    typedef struct {
        int* result1;
        int* result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z16Change(TestCase t1) {
    TestCase follow_case = t1;
    // --- Memory handling code generated based on the rule ---
    int* follow_case_array = (int*)malloc(t1.n * sizeof(int));
    memcpy(follow_case_array, t1.array, t1.n * sizeof(int));
    follow_case.array = follow_case_array;
    // ------------------------------------
    
    // Defensive code to ensure there are at least two elements for swapping
    if (follow_case.n < 2) {
        return follow_case;
    }
    
    // Swap two random positions in the array
    int idx1 = rand() % follow_case.n;
    int idx2 = rand() % follow_case.n;
    while (idx2 == idx1) {
        idx2 = rand() % follow_case.n;
    }
    int temp = follow_case.array[idx1];
    follow_case.array[idx1] = follow_case.array[idx2];
    follow_case.array[idx2] = temp;
    
    return follow_case;
}

int z16check(int* result1, int* result2, int n) {
    if (n <= 0) return 1;
    if (result1 == NULL || result2 == NULL) return 0;

    for (int i = 0; i < n; i++) {
        if (!(result1[i] == result2[i])) {
            return 0;
        }
    }
    return 1;
}

TestResult z16runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z16Change(test_cases[test_case_id]);
    // 原始调用
    int* source = insertion_sort(test_cases[test_case_id].array, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    int* follow = insertion_sort(follow_case.array, follow_case.n);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z16check(source, follow, test_cases[test_case_id].n);
    test_result.status = status;
    
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z16runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}