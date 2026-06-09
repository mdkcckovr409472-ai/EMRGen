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


double* square(double data[], int n) {
    double* cp1 = (double*)malloc(n * sizeof(double));
    memcpy(cp1,data,n*sizeof(double));
    for (int i = 0; i < n; i++) {
        cp1[i] = cp1[i] * cp1[i];
    }
    return cp1;
}


typedef struct {
    double* data; int n;
} TestCase;

TestCase test_cases[] = {
    { (double[]){}, 0 },
    { (double[]){0.0}, 1 },
    { (double[]){3.5}, 1 },
    { (double[]){-2.2}, 1 },
    { (double[]){0.0, 0.0}, 2 },
    { (double[]){1.1, 4.4}, 2 },
    { (double[]){-5.5, -3.3}, 2 },
    { (double[]){2.0, -1.5, 3.0}, 3 },
    { (double[]){0.25, -0.75, 1.5}, 3 },
    { (double[]){7.7, 7.7, 2.2, 2.2}, 4 },
    { (double[]){-4.0, 5.5, -3.3, 2.2, -1.1}, 5 },
    { (double[]){1.0, -2.0, 3.0, -4.0, 5.0, -6.0}, 6 },
    { (double[]){-0.5, 0.5, -1.5, 1.5, -2.5, 2.5, -3.5}, 7 },
    { (double[]){4.4, 4.4, 4.4, 4.4}, 4 },
    { (double[]){-1.0, 2.0, -3.0, 4.0, -5.0, 6.0}, 6 },
    { (double[]){9.9, -8.8, 7.7, -6.6, 5.5, -4.4, 3.3, -2.2}, 8 },
    { (double[]){0.1, 0.2, 0.3, 0.4, 0.5}, 5 },
    { (double[]){-0.9, -0.8, -0.7, -0.6, -0.5}, 5 },
    { (double[]){1.2, -1.2, 2.4, -2.4, 3.6, -3.6}, 6 },
    { (double[]){5.0, 0.0, -5.0, 0.0, 5.0}, 5 },
    { (double[]){9.5, 8.5, 7.5, 6.5, 5.5}, 5 },
    { (double[]){-9.5, -8.5, -7.5, -6.5, -5.5}, 5 },
    { (double[]){2.2, -2.2, 3.3, -3.3, 4.4}, 5 },
    { (double[]){0.0, 1.1, 0.0, 1.1, 0.0}, 5 },
    { (double[]){3.0, 2.0, 1.0, 1.0, 2.0, 3.0}, 6 },
    { (double[]){6.0, 5.0, 4.0, 3.0, 2.0, 1.0}, 6 },
    { (double[]){-0.25, 0.75, -1.25, 1.75, -2.25, 2.75}, 6 },
    { (double[]){0.33, -0.66, 0.99, -1.32, 1.65, -1.98}, 6 },
    { (double[]){4.1, -3.2, 2.3, -1.4, 0.5}, 5 },
    { (double[]){-2.7, 3.8, -4.9, 5.0, -6.1}, 5 }
};
int num_test_cases = 30;


    typedef struct {
        double* result1;
        double* result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z3Change(TestCase t1) {
    TestCase follow_case = t1;
    // Memory handling for deep copy of the array
    double* follow_case_data = (double*)malloc(t1.n * sizeof(double));
    memcpy(follow_case_data, t1.data, t1.n * sizeof(double));
    follow_case.data = follow_case_data;

    // Defensive check: ensure there is at least one element
    if (follow_case.n > 0) {
        for (int i = 0; i < follow_case.n; ++i) {
            follow_case.data[i] *= 2.0;
        }
    }

    return follow_case;
}

int z3check(double* result1, double* result2, int n) {
    if (n <= 0) return 1;
    if (result1 == NULL || result2 == NULL) return 0;
    const double epsilon = 1e-5;
    for (int i = 0; i < n; i++) {
        double A = result1[i];
        double B = result2[i] / 4.0;
        if (std::isnan(A) || std::isnan(B)) return 0;
        if (std::isinf(A) || std::isinf(B)) {
            if (A == B) continue;
            else return 0;
        }
        double tol = epsilon * fmax(1.0, fmax(fabs(A), fabs(B)));
        if (fabs(A - B) > tol) return 0;
    }
    return 1;
}

TestResult z3runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z3Change(test_cases[test_case_id]);
    // 原始调用
    double* source = square(test_cases[test_case_id].data, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    double* follow = square(follow_case.data, follow_case.n);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z3check(source, follow, test_cases[test_case_id].n);
    test_result.status = status;
    
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z3runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}