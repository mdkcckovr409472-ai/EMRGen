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


int partition(double work[], int begin, int end, int pivot) {
    double value = work[pivot];
    work[pivot] = work[begin];
    int i = begin + 1;
    int j = end - 1;
    while (i < j) {
        while (i < j && work[j] > value) {
            --j;
        }
        while (i < j && work[i] < value) {
            ++i;
        }
        if (i < j) {
            double tmp = work[i];
            work[i++] = work[j];
            work[j--] = tmp;
        }
    }
    if (i >= end || work[i] > value) {
        --i;
    }
    work[begin] = work[i];
    work[i] = value;
    return i;
}


typedef struct {
    double* work; int begin; int end; int pivot;
} TestCase;

TestCase test_cases[] = {
    { (double[]){5.0, 2.0, 8.0, 6.0, 3.0}, 0, 5, 2 },
    { (double[]){1.0, 4.0, 3.0, 2.0, 5.0}, 0, 5, 1 },
    { (double[]){10.0, -1.0, 7.0, 3.0, 0.0, 2.0}, 1, 5, 3 },
    { (double[]){0.0, 0.0, 0.0, 0.0}, 0, 4, 2 },
    { (double[]){9.5, -3.2, 4.1, 6.6, -2.0, 7.7}, 0, 6, 5 },
    { (double[]){2.5, 3.5, 1.5, 4.5, 0.5}, 0, 5, 0 },
    { (double[]){8.0, 6.0, 7.0, 5.0, 9.0, 1.0, 2.0}, 2, 7, 4 },
    { (double[]){3.3, 2.2, 1.1, 4.4, 5.5}, 1, 5, 3 },
    { (double[]){100.0, -50.0, 25.0, -75.0, 0.0}, 0, 5, 4 },
    { (double[]){1.0, 2.0, 3.0, 4.0, 5.0}, 0, 5, 2 },
    { (double[]){5.0, 4.0, 3.0, 2.0, 1.0}, 0, 5, 2 },
    { (double[]){7.0, 7.0, 2.0, 7.0, 5.0, 7.0}, 0, 6, 3 },
    { (double[]){-10.0, 20.0, -30.0, 40.0, -50.0, 60.0}, 0, 6, 1 },
    { (double[]){0.1, -0.2, 0.3, -0.4, 0.5}, 0, 5, 2 },
    { (double[]){3.14, 2.71, 1.41, 1.73, 2.58}, 0, 5, 0 },
    { (double[]){9.0, 8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0}, 0, 9, 8 },
    { (double[]){1.5, 2.5, 1.5, 2.5, 1.5}, 0, 5, 1 },
    { (double[]){-5.0, -10.0, -3.0, -8.0, -1.0}, 0, 5, 3 },
    { (double[]){0.0, 100.0, -100.0, 50.0, -50.0}, 0, 5, 2 },
    { (double[]){2.0, 2.0, 2.0, 2.0, 2.0}, 0, 5, 4 },
    { (double[]){-1.0, 1.0, -1.0, 1.0, -1.0, 1.0}, 0, 6, 5 },
    { (double[]){10.0, 20.0, 30.0, 40.0, 5.0, 35.0}, 2, 6, 4 },
    { (double[]){3.0, 1.0, 4.0, 1.5, 2.5, 0.5}, 1, 5, 2 },
    { (double[]){6.0, 2.0, 8.0, 3.0, 7.0, 4.0, 5.0}, 0, 7, 6 },
    { (double[]){-2.0, -3.0, -1.0, -4.0, -5.0}, 0, 5, 2 },
    { (double[]){0.0, 1.0, 0.0, 1.0, 0.0}, 0, 5, 1 },
    { (double[]){12.0, 6.0, 18.0, 3.0, 9.0, 15.0}, 0, 6, 3 },
    { (double[]){4.0, 5.0, 6.0, 7.0, 8.0}, 0, 5, 4 },
    { (double[]){8.0, 7.0, 6.0, 5.0, 4.0}, 0, 5, 1 },
    { (double[]){1.0, 3.0, 2.0, 4.0, 0.0, 5.0}, 0, 6, 0 }
};
int num_test_cases = 30;


    typedef struct {
        int result1;
        int result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z1Change(TestCase t1) {
    TestCase follow_case = t1;
    // --- Memory handling code generated based on the rule ---
    int len = t1.end - t1.begin + 1;
    double* follow_case_work = (double*)malloc(len * sizeof(double));
    memcpy(follow_case_work, t1.work, len * sizeof(double));
    follow_case.work = follow_case_work;
    // ------------------------------------
    
    // Defensive code to ensure there is at least one element
    if (len <= 0) {
        return follow_case;
    }
    
    // Operation: add 1.0 to all elements
    for (int i = 0; i < len; ++i) {
        follow_case.work[i] += 1.0;
    }
    
    return follow_case;
}

int z1check(int result1, int result2) {
    if (!(result1 <= result2)) {
        return 0;
    }
    return 1;
}

TestResult z1runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z1Change(test_cases[test_case_id]);
    // 原始调用
    int source = partition(test_cases[test_case_id].work, test_cases[test_case_id].begin, test_cases[test_case_id].end, test_cases[test_case_id].pivot); // MODIFIED: Explicit type
    // 变换后调用
    int follow = partition(follow_case.work, follow_case.begin, follow_case.end, follow_case.pivot);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z1check(source, follow);
    test_result.status = status;
    
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z1runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}