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


int sum(int values[],  int n) {
    int sum = 0;
    for (int i = 0; i < n; i++){
        sum += values[i];
}
    return sum;
}


typedef struct {
    int* values; int n;
} TestCase;

TestCase test_cases[] = {
    { (int[]){1, 2, 3}, 3 },
    { (int[]){}, 0 },
    { (int[]){-5, 10}, 2 },
    { (int[]){0, 0, 0, 0}, 4 },
    { (int[]){5}, 1 },
    { (int[]){-1, -2, -3}, 3 },
    { (int[]){100, -50, 25, -75}, 4 },
    { (int[]){7, 7, 7, 7, 7}, 5 },
    { (int[]){3, 1, 4, 1, 5, 9}, 6 },
    { (int[]){-10, 20, -30, 40, -50}, 5 },
    { (int[]){2, -2, 2, -2}, 4 },
    { (int[]){99, 1}, 2 },
    { (int[]){-100, 0, 100}, 3 },
    { (int[]){8, 6, 7, 5, 3, 0, -1}, 7 },
    { (int[]){-3, -1, 0, 1, 3}, 5 },
    { (int[]){42, -42}, 2 },
    { (int[]){5, -5, 10, -10, 15, -15}, 6 },
    { (int[]){1, -1, 1, -1, 1}, 5 },
    { (int[]){0}, 1 },
    { (int[]){-7, 14, -21, 28}, 4 },
    { (int[]){3, -3, 3, -3, 3, -3}, 6 },
    { (int[]){11, 22, 33, 44, 55}, 5 },
    { (int[]){-9, -8, -7, -6, -5}, 5 },
    { (int[]){2, 4, 6, 8, 10, 12, 14, 16, 18, 20}, 10 },
    { (int[]){-2, -4, -6, -8, -10}, 5 },
    { (int[]){1, 2, 1, 2, 1, 2}, 6 },
    { (int[]){7, 0, 7, 0, 7}, 5 },
    { (int[]){-1, 0, 1}, 3 },
    { (int[]){13, -13, 26, -26}, 4 },
    { (int[]){5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, 10 }
};
int num_test_cases = 30;


    typedef struct {
        int result1;
        int result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z8Change(TestCase t1) {
    TestCase follow_case = t1;
    // Memory handling: deep copy of the array
    int* follow_case_values = (int*)malloc(t1.n * sizeof(int));
    memcpy(follow_case_values, t1.values, t1.n * sizeof(int));
    follow_case.values = follow_case_values;

    // Defensive check: need at least two elements to swap
    if (follow_case.n < 2) {
        return follow_case;
    }

    // Swap two random elements
    int idx1 = rand() % follow_case.n;
    int idx2 = rand() % follow_case.n;
    while (idx2 == idx1) {
        idx2 = rand() % follow_case.n;
    }
    int temp = follow_case.values[idx1];
    follow_case.values[idx1] = follow_case.values[idx2];
    follow_case.values[idx2] = temp;

    return follow_case;
}

int z8check(int result1, int result2) {
    if (!(result1 == result2)) {
        return 0;
    }
    return 1;
}

TestResult z8runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z8Change(test_cases[test_case_id]);
    // 原始调用
    int source = sum(test_cases[test_case_id].values, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    int follow = sum(follow_case.values, follow_case.n);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    memory_list[0] = follow_case.values;
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z8check(source, follow);
    test_result.status = status;
    
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z8runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}