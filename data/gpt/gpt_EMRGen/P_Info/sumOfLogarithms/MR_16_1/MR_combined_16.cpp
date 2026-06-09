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


double sumOfLogarithms(double elements[], int n) {
    double logsum = 0;
    for(int i = 0; i < n; i++) {
        logsum += log(elements[i]);
    }
    return logsum;
}


typedef struct {
    double* elements; int n;
} TestCase;

TestCase test_cases[] = {
    { (double[]){}, 0 },
    { (double[]){1.0}, 1 },
    { (double[]){2.71828}, 1 },
    { (double[]){0.5, 4.0}, 2 },
    { (double[]){3.0, 0.2, 5.5}, 3 },
    { (double[]){10.0, 0.1, 7.2, 2.5}, 4 },
    { (double[]){1.5, 1.5, 1.5}, 3 },
    { (double[]){9.9, 0.3, 4.4, 8.8, 2.2}, 5 },
    { (double[]){0.75, 3.33, 0.66, 5.55}, 4 },
    { (double[]){4.0, 1.0, 5.0, 2.0, 6.0, 3.0}, 6 },
    { (double[]){0.7, 0.9, 0.5, 0.8, 0.6}, 5 },
    { (double[]){12.5, 3.3, 7.7, 2.2, 9.9, 5.5, 1.1}, 7 },
    { (double[]){1.75, 0.25, 2.25, 0.75, 1.25}, 5 },
    { (double[]){25.0, 100.0, 12.5, 50.0}, 4 },
    { (double[]){6.66, 0.33, 10.0, 4.44, 2.22, 8.88}, 6 },
    { (double[]){1.618, 3.1415, 0.5772, 2.718}, 4 },
    { (double[]){0.55, 0.99, 0.11, 0.77, 0.33, 0.88, 0.22, 0.66, 0.44}, 9 },
    { (double[]){5.5, 5.5, 5.5, 5.5, 5.5}, 5 },
    { (double[]){8.0, 2.0, 16.0, 4.0}, 4 },
    { (double[]){0.4, 1.0, 0.2, 0.9, 0.5, 0.1, 0.8, 0.3, 0.7, 0.6}, 10 },
    { (double[]){5.5, 0.1, 7.7, 2.2, 4.4, 3.3, 1.1, 6.6}, 8 },
    { (double[]){12.0, 9.0, 24.0, 3.0, 6.0}, 5 },
    { (double[]){1.345, 0.456, 0.123, 1.012, 0.789}, 5 },
    { (double[]){19.0, 3.14, 13.37, 7.13, 42.0}, 5 },
    { (double[]){0.85, 0.95, 0.75, 0.9, 0.8}, 5 },
    { (double[]){5.0, 2.5, 10.0, 2.5, 7.5}, 5 },
    { (double[]){3.33, 0.33, 5.33, 2.33, 1.33, 4.33}, 6 },
    { (double[]){10.0, 0.01, 100.0, 1.0, 0.1}, 5 },
    { (double[]){0.8, 0.2, 1.2, 0.6, 0.4}, 5 },
    { (double[]){3.0, 3.0, 3.0, 3.0, 3.0, 3.0}, 6 }
};
int num_test_cases = 30;


    typedef struct {
        double result1;
        double result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z16Change(TestCase t1) {
    TestCase follow_case = t1;
    // --- Memory handling code generated based on the rule ---
    double* follow_case_elements = (double*)malloc(t1.n * sizeof(double));
    memcpy(follow_case_elements, t1.elements, t1.n * sizeof(double));
    follow_case.elements = follow_case_elements;
    // ------------------------------------
    
    // Defensive code generated based on rule (a) to prevent errors when n == 0
    if (follow_case.n == 0) {
        return follow_case;
    }
    
    // Specific operation code: left circular shift array (move first element to end)
    double first = follow_case.elements[0];
    for (int i = 0; i < follow_case.n - 1; ++i) {
        follow_case.elements[i] = follow_case.elements[i + 1];
    }
    follow_case.elements[follow_case.n - 1] = first;
    
    return follow_case;
}

int z16check(double result1, double result2) {
    double epsilon = 1e-5;
    double A = result1;
    double B = result2;

    if (std::isnan(A) || std::isnan(B)) return 0;
    if (std::isinf(A) || std::isinf(B)) {
        if (A == B) return 1;
        else return 0;
    }

    double tol = epsilon * fmax(1.0, fmax(fabs(A), fabs(B)));

    if (fabs(A - B) > tol) return 0;

    return 1;
}

TestResult z16runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z16Change(test_cases[test_case_id]);
    // 原始调用
    double source = sumOfLogarithms(test_cases[test_case_id].elements, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    double follow = sumOfLogarithms(follow_case.elements, follow_case.n);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z16check(source, follow);
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