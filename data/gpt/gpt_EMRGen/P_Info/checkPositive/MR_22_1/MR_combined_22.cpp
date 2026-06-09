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


bool checkPositive(double a[], int n){
    
    for (int i = 0; i < n; i++)
    {
        if (a[i] <= 0)
        {
            return false;
        }
    }
    return true; 
}


typedef struct {
    double* a; int n;
} TestCase;

TestCase test_cases[] = {
    { (double[]){1.0, 2.5, 3.3}, 3 },
    { (double[]){0.1}, 1 },
    { (double[]){3.3, 1.1, 4.4, 2.2, 5.5}, 5 },
    { (double[]){-0.5, 2.0, 3.0}, 3 },
    { (double[]){0.0, 1.0}, 2 },
    { (double[]){10.0, 20.0, 30.0, 40.0}, 4 },
    { (double[]){-1.0, -2.0, -3.0}, 3 },
    { (double[]){0.00001, 0.00002}, 2 },
    { (double[]){100.0, -100.0}, 2 },
    { (double[]){}, 0 },
    { (double[]){7.7, 8.8, 9.9, 6.6}, 4 },
    { (double[]){2.5, -2.5, 2.5}, 3 },
    { (double[]){3.1415, 2.718, 1.618}, 3 },
    { (double[]){-0.000001, 0.5}, 2 },
    { (double[]){5.0, 5.0, 5.0}, 3 },
    { (double[]){9.99, 0.01, 5.55}, 3 },
    { (double[]){-10.0}, 1 },
    { (double[]){0.5, 0.0, 0.5}, 3 },
    { (double[]){123.456, 654.321}, 2 },
    { (double[]){-3.3, -2.2, -1.1, 0.1}, 4 },
    { (double[]){0.2, 0.4, 0.6, 0.8, 1.0}, 5 },
    { (double[]){-0.9, 0.9}, 2 },
    { (double[]){0.001, 0.002, 0.003}, 3 },
    { (double[]){-5.5, 5.5}, 2 },
    { (double[]){0.123, 0.456, 0.789}, 3 },
    { (double[]){-0.001, -0.002}, 2 },
    { (double[]){9.0, 8.0, 7.0, 6.0}, 4 },
    { (double[]){0.333, 0.666, 0.999}, 3 },
    { (double[]){-100.0, 0.0}, 2 },
    { (double[]){2.2, 4.4, 6.6, 8.8, 1.1}, 5 }
};
int num_test_cases = 30;


    typedef struct {
        bool result1;
        bool result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z22Change(TestCase t1) {
    TestCase follow_case = t1;
    // --- Memory handling code generated based on the rule ---
    double* follow_case_a = (double*)malloc(t1.n * sizeof(double));
    memcpy(follow_case_a, t1.a, t1.n * sizeof(double));
    follow_case.a = follow_case_a;
    // ------------------------------------
    // Defensive code: ensure there is at least one element
    if (follow_case.n <= 0) {
        return follow_case;
    }
    // Operation: replace each element with its reciprocal when element != 0
    for (int i = 0; i < follow_case.n; ++i) {
        if (follow_case.a[i] != 0.0) {
            follow_case.a[i] = 1.0 / follow_case.a[i];
        }
    }
    return follow_case;
}

int z22check(bool result1, bool result2) {
    if (!(result1 == result2)) {
        return 0;
    }
    return 1;
}

TestResult z22runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z22Change(test_cases[test_case_id]);
    // 原始调用
    bool source = checkPositive(test_cases[test_case_id].a, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    bool follow = checkPositive(follow_case.a, follow_case.n);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z22check(source, follow);
    test_result.status = status;
    
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z22runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}