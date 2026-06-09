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


double durbinWatson(double elements[], int n) {
    
    double run = 0;
    for (int i = 1; i < n; ++i) {
        double x = elements[i] - elements[i - 1];
        run += x * x;
    }
    return run;
}


typedef struct {
    double* elements; int n;
} TestCase;

TestCase test_cases[] = {
    { (double[]){}, 0 },
    { (double[]){0.0}, 1 },
    { (double[]){5.0, 5.0}, 2 },
    { (double[]){5.0, -5.0}, 2 },
    { (double[]){2.0, 1.0, 3.0}, 3 },
    { (double[]){0.0, -1.0, 1.0}, 3 },
    { (double[]){10.0, -10.0, 10.0, -10.0}, 4 },
    { (double[]){3.5, 3.5, 3.5, 3.5}, 4 },
    { (double[]){7.2, -3.1, 0.0, 4.5, -2.2}, 5 },
    { (double[]){1.0, 1.0, 2.0, 2.0, 1.0}, 5 },
    { (double[]){-5.5, 2.2, -3.3, 4.4, -1.1, 0.0}, 6 },
    { (double[]){0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, 6 },
    { (double[]){9.9, -9.8, 9.7, -9.6, 9.5, -9.4, 9.3}, 7 },
    { (double[]){1.1, -2.2, 3.3, -4.4, 5.5, -6.6, 7.7}, 7 },
    { (double[]){2.0, -5.0, 3.0, -1.0, 4.0, -3.0, 0.0, 1.0}, 8 },
    { (double[]){0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5}, 8 },
    { (double[]){-1.0, 2.0, -3.0, 4.0, -5.0, 6.0, -7.0, 8.0, -9.0}, 9 },
    { (double[]){0.1, -0.2, 0.3, -0.4, 0.5, -0.6, 0.7, -0.8, 0.9}, 9 },
    { (double[]){10.0, -10.0, 10.0, -10.0, 10.0, -10.0, 10.0, -10.0, 10.0, -10.0}, 10 },
    { (double[]){3.0, -1.0, 4.0, -1.0, 5.0, -9.0, 2.0, 6.0, 5.0, 3.0}, 10 },
    { (double[]){1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0}, 11 },
    { (double[]){-2.0, -1.0, 0.0, 1.0, 2.0, -2.0, -1.0, 0.0, 1.0, 2.0, -2.0}, 11 },
    { (double[]){2.2, -3.3, 4.4, -5.5, 6.6, -7.7, 8.8, -9.9, 0.0, 1.1, -1.2, 2.3}, 12 },
    { (double[]){0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, 12 },
    { (double[]){1.0, 2.0, 1.0, 2.0, 1.0, 2.0, 1.0, 2.0, 1.0, 2.0, 1.0, 2.0, 1.0}, 13 },
    { (double[]){-5.0, 3.0, -2.0, 6.0, -1.0, 4.0, -3.0, 5.0, -4.0, 2.0, -6.0, 1.0, 0.0}, 13 },
    { (double[]){0.12, -0.34, 0.56, -0.78, 0.90, -0.11, 0.22, -0.33, 0.44, -0.55, 0.66, -0.77, 0.88, -0.99}, 14 },
    { (double[]){-1.5, -1.5, -1.5, -1.5, -1.5, -1.5, -1.5, -1.5, -1.5, -1.5, -1.5, -1.5, -1.5, -1.5, -1.5}, 15 },
    { (double[]){5.0, -3.0, 8.0, -2.0, 7.0, -6.0, 4.0, -5.0, 3.0, -1.0, 2.0, -4.0, 1.0, -7.0, 0.0}, 15 },
    { (double[]){2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0}, 15 }
};
int num_test_cases = 30;


    typedef struct {
        double result1;
        double result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z25Change(TestCase t1) {
    TestCase follow_case = t1;
    // --- Memory handling code generated based on the rule ---
    double* follow_case_elements = (double*)malloc(t1.n * sizeof(double));
    memcpy(follow_case_elements, t1.elements, t1.n * sizeof(double));
    follow_case.elements = follow_case_elements;
    // ------------------------------------
    
    // Defensive programming: ensure there is at least one element
    if (follow_case.n > 0) {
        for (int i = 0; i < follow_case.n; ++i) {
            if (follow_case.elements[i] < 0.0) {
                follow_case.elements[i] = 0.0;
            } else if (follow_case.elements[i] > 1.0) {
                follow_case.elements[i] = 1.0;
            }
        }
    }
    
    return follow_case;
}

#include <cmath>
int z25check(double result1, double result2) {
    double epsilon = 1e-5;
    double A = result1;
    double B = result2;
    if (std::isnan(A) || std::isnan(B)) return 0;
    if (std::isinf(A) || std::isinf(B)) {
        if (A >= B) return 1;
        else return 0;
    }
    double tol = epsilon * fmax(1.0, fmax(fabs(A), fabs(B)));
    if (A < B - tol) return 0;
    return 1;
}

TestResult z25runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z25Change(test_cases[test_case_id]);
    // 原始调用
    double source = durbinWatson(test_cases[test_case_id].elements, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    double follow = durbinWatson(follow_case.elements, follow_case.n);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z25check(source, follow);
    test_result.status = status;
    
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z25runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}