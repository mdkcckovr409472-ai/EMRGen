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


double* ebeMultiply(double a[], double b[], int n1, int n2) {
    if (n1 != n2) {
        return NULL;  
    }

    double* result = (double*)malloc(n1 * sizeof(double));
    if (result == NULL) {
        return NULL;  
    }

    for (int i = 0; i < n1; i++) {
        result[i] = a[i] * b[i];  
    }

    return result;  
}


typedef struct {
    double* a; double* b; int n1; int n2;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.5, -20.0, 3.14}, (double[]){2.0, 4.5, -0.5}, 3, 3},
    {(double[]){100.0, 500.5, -300.0, 1.1}, (double[]){-2.0, 1000.2, 0.25, -1.5}, 4, 4},
    {(double[]){42.42, -150.0, 600.6, 0.001, 999.99}, (double[]){-100.0, 0.1, -300.0, 4000.0, 0.5}, 5, 5},
    {(double[]){3.0, 7.7, 100.0, 2000.0}, (double[]){1.5, -2.2, 300.3, -1000.0}, 4, 4},
    {(double[]){999.99, 45.67, -12.0, 500.1, 0.5, -100.0}, (double[]){0.1, -0.2, 300.0, 1200.0, 2000.0, 3.1415}, 6, 6},
    {(double[]){33.33, -44.44, 55.55}, (double[]){66.66, 77.77, -88.88}, 3, 3},
    {(double[]){1000.0, 2000.0, 3000.0, 4000.0}, (double[]){-1.0, -2.0, -3.0, -4.0}, 4, 4},
    {(double[]){0.25, 0.5, 0.75, 1.0}, (double[]){10.0, 20.0, 30.0, 40.0}, 4, 4},
    {(double[]){-500.0, 250.0, 125.0}, (double[]){-2.0, 4.0, -6.0}, 3, 3},
    {(double[]){123.4, 234.5, -345.6}, (double[]){-456.7, 567.8, 678.9}, 3, 3},
    {(double[]){7.7, 8.8, 9.9, 10.10, 11.11}, (double[]){1.1, -2.2, 3.3, -4.4, 5.5}, 5, 5},
    {(double[]){200.0, 300.0, 400.0}, (double[]){-1.5, 2.5, -3.5}, 3, 3},
    {(double[]){0.0, 1.1, -1.1, 2.2, -2.2}, (double[]){3.3, -3.3, 4.4, -4.4, 5.5}, 5, 5},
    {(double[]){12.34, 56.78, 90.12}, (double[]){-21.43, 65.87, -91.21}, 3, 3},
    {(double[]){7.0, -14.0, 28.0, -56.0}, (double[]){-1.0, 2.0, -4.0, 8.0}, 4, 4},
    {(double[]){11.0, 22.0, 33.0, 44.0}, (double[]){-55.0, 66.0, -77.0, 88.0}, 4, 4},
    {(double[]){130.5, -260.1, 520.2, -1040.4}, (double[]){2.0, -4.0, 8.0, -16.0}, 4, 4},
    {(double[]){99.9, 88.8, 77.7, 66.6}, (double[]){-55.5, -44.4, -33.3, -22.2}, 4, 4},
    {(double[]){5.5, -5.5, 10.1, -10.1}, (double[]){-20.2, 20.2, -30.3, 30.3}, 4, 4},
    {(double[]){1000.0, -2000.0, 3000.0, -4000.0}, (double[]){5000.0, -6000.0, 7000.0, -8000.0}, 4, 4},
    {(double[]){123.0, 234.0, 345.0, 456.0, 567.0}, (double[]){-321.0, -432.0, -543.0, -654.0, -765.0}, 5, 5},
    {(double[]){1.23, -2.34, 3.45, -4.56}, (double[]){5.67, -6.78, 7.89, -8.90}, 4, 4},
    {(double[]){-300.3, 400.4, -500.5}, (double[]){600.6, -700.7, 800.8}, 3, 3},
    {(double[]){-999.9, 888.8, -777.7, 666.6}, (double[]){555.5, -444.4, 333.3, -222.2}, 4, 4},
    {(double[]){7.1, 8.2, 9.3}, (double[]){-9.1, -8.2, -7.3}, 3, 3},
    {(double[]){50.0, 60.0, 70.0}, (double[]){-10.0, -20.0, -30.0}, 3, 3},
    {(double[]){-1.1, 2.2, -3.3, 4.4}, (double[]){5.5, -6.6, 7.7, -8.8}, 4, 4},
    {(double[]){25.25, -50.50, 75.75}, (double[]){-100.1, 125.125, -150.15}, 3, 3},
    {(double[]){999.1, -888.2, 777.3, -666.4, 555.5}, (double[]){-444.6, 333.7, -222.8, 111.9, -0.1}, 5, 5}
};
int num_test_cases = 29;


    typedef struct {
        double* result1;
        double* result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z22Change(TestCase t1) {
    TestCase follow_case = t1;
    // --- Memory handling code generated based on the rule ---
    if (t1.n1 > 0 && t1.a != NULL) {
        double* follow_case_a = (double*)malloc(t1.n1 * sizeof(double));
        if (follow_case_a != NULL) {
            memcpy(follow_case_a, t1.a, t1.n1 * sizeof(double));
            follow_case.a = follow_case_a;
        }
    }
    // ------------------------------------

    // Defensive code generated based on rule (a) to prevent errors when n < 1
    if (follow_case.n1 <= 0 || follow_case.a == NULL) {
        // No elements to negate or invalid array, return replica directly
        return follow_case;
    }

    // Specific operation code generated based on the rule
    for (int i = 0; i < follow_case.n1; i++) {
        follow_case.a[i] = -follow_case.a[i];
    }

    return follow_case;
}

int z22check(double* result1, double* result2, int n) {
    // 1. Defensive programming (Length check first)
    if (n <= 0) return 1;
    if (result1 == NULL || result2 == NULL) return 0;

    const double epsilon = 1e-5;

    for (int i = 0; i < n; i++) {
        // Rearranged invariant: result1[i] + result2[i] == 0
        // A = result1[i], B = -result2[i], so that A == B
        double A = result1[i];
        double B = -result2[i];

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

TestResult z22runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z22Change(test_cases[test_case_id]);
    // 原始调用
    double* source = ebeMultiply(test_cases[test_case_id].a, test_cases[test_case_id].b, test_cases[test_case_id].n1, test_cases[test_case_id].n2); // MODIFIED: Explicit type
    // 变换后调用
    double* follow = ebeMultiply(follow_case.a, follow_case.b, follow_case.n1, follow_case.n2);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z22check(source, follow, test_cases[test_case_id].n1);
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