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


double* ebeAdd(double a[], double b[], int n1, int n2) {
    if (n1 != n2) {
        return NULL; 
    }

    double* result = (double*)malloc(n1 * sizeof(double));
    if (result == NULL) {
        return NULL;  
    }

    for (int i = 0; i < n1; i++) {
        result[i] = a[i] + b[i];  
    }

    return result; 
}


typedef struct {
    double* a; double* b; int n1; int n2;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.5, 2.3, -4.1}, (double[]){3.2, -1.1, 0.0}, 3, 3},
    {(double[]){42.0, -150.2, 300.0}, (double[]){1000.5, 0.5, -999.9}, 3, 3},
    {(double[]){12.12, -99.99, 88.88, 77.77}, (double[]){-12.12, 99.99, -88.88, -77.77}, 4, 4},
    {(double[]){1234.56, -654.32, 0.0}, (double[]){-234.56, 1654.32, 10.10}, 3, 3},
    {(double[]){0.1, 0.01, 0.001, 0.0001}, (double[]){100.0, 2000.0, -30000.0, 400000.0}, 4, 4},
    {(double[]){10.5, -20.5, 30.5}, (double[]){-10.5, 20.5, -30.5}, 3, 3},
    {(double[]){-9999.9, 8888.8, -7777.7}, (double[]){1111.1, -2222.2, 3333.3}, 3, 3},
    {(double[]){123, -456, 789, -1011}, (double[]){-321, 654, -987, 1110}, 4, 4},
    {(double[]){-0.5, 0.5, -1.5, 1.5}, (double[]){1.0, -1.0, 2.0, -2.0}, 4, 4},
    {(double[]){200.2, -300.3}, (double[]){-200.2, 300.3}, 2, 2},
    {(double[]){5000.0, -4000.0, 3000.0}, (double[]){-5000.0, 4000.0, -3000.0}, 3, 3},
    {(double[]){0.0001, -0.0002, 0.0003}, (double[]){0.0004, -0.0005, 0.0006}, 3, 3},
    {(double[]){-123.45, 678.9}, (double[]){123.45, -678.9}, 2, 2},
    {(double[]){100.0, 200.0, 300.0}, (double[]){-100.0, -200.0, -300.0}, 3, 3},
    {(double[]){999.99, -888.88, 777.77}, (double[]){-999.99, 888.88, -777.77}, 3, 3},
    {(double[]){1.1, 2.2, 3.3, 4.4, 5.5}, (double[]){-1.1, -2.2, -3.3, -4.4, -5.5}, 5, 5},
    {(double[]){10.0, 100.0, 1000.0}, (double[]){-10.0, -100.0, -1000.0}, 3, 3},
    {(double[]){314.15, -271.82}, (double[]){-314.15, 271.82}, 2, 2},
    {(double[]){-42.42, 84.84, -126.26}, (double[]){42.42, -84.84, 126.26}, 3, 3},
    {(double[]){555.5, -666.6, 777.7}, (double[]){-555.5, 666.6, -777.7}, 3, 3},
    {(double[]){-0.123, 0.456, -0.789}, (double[]){0.123, -0.456, 0.789}, 3, 3},
    {(double[]){1.234, 5.678, 9.1011}, (double[]){-1.234, -5.678, -9.1011}, 3, 3},
    {(double[]){-11.11, 22.22, -33.33, 44.44}, (double[]){11.11, -22.22, 33.33, -44.44}, 4, 4},
    {(double[]){101.1, 202.2, 303.3}, (double[]){-101.1, -202.2, -303.3}, 3, 3},
    {(double[]){-500.5, 400.4, -300.3}, (double[]){500.5, -400.4, 300.3}, 3, 3},
    {(double[]){12345.6, -65432.1}, (double[]){-12345.6, 65432.1}, 2, 2},
    {(double[]){345.67, -890.12, 567.89}, (double[]){-345.67, 890.12, -567.89}, 3, 3},
    {(double[]){707.07, -808.08}, (double[]){-707.07, 808.08}, 2, 2},
    {(double[]){1.0, 2.0, 4.0, 7.0}, (double[]){-1.0, -2.0, -4.0, -7.0}, 4, 4}
};
int num_test_cases = 29;


    typedef struct {
        double* result1;
        double* result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z31Change(TestCase t1) {
    TestCase follow_case = t1;
    // --- Memory handling code generated based on the rule ---
    if(t1.n2 > 0 && t1.b != NULL) {
        double* follow_case_b = (double*)malloc(t1.n2 * sizeof(double));
        if(follow_case_b != NULL) {
            memcpy(follow_case_b, t1.b, t1.n2 * sizeof(double));
            follow_case.b = follow_case_b;
        } else {
            // malloc failed, return original follow_case
            return follow_case;
        }
    } else {
        // If n2 <= 0 or b is NULL, no allocation or copy
        follow_case.b = NULL;
    }
    // ------------------------------------

    // Defensive code generated based on rule (a) to prevent errors when n < 1
    if (follow_case.n2 <= 0 || follow_case.b == NULL) {
        // No elements to process, return replica directly
        return follow_case;
    }

    // Specific operation code generated based on the rule
    for (int i = 0; i < follow_case.n2; i++) {
        follow_case.b[i] -= 1.0;
    }

    return follow_case;
}

int z31check(double* result1, double* result2, int n) {
    // 4. Defensive programming and boundary checks
    if (n <= 0) return 1;
    if (result1 == NULL || result2 == NULL) return 0;

    const double epsilon = 1e-5;
    for (int i = 0; i < n; i++) {
        double A = result1[i];
        double B = result2[i];

        if (std::isnan(A) || std::isnan(B)) return 0;
        if (std::isinf(A) || std::isinf(B)) {
            if (A > B) return 1;
            else if (A <= B) return 0;
        }

        double tol = epsilon * fmax(1.0, fmax(fabs(A), fabs(B)));
        double diff = A - B;

        if (fabs(diff) <= tol) {
            // Equal within tolerance, continue to next element
            continue;
        } else if (diff > tol) {
            // result1[i] > result2[i] within tolerance: condition met, lexicographically greater
            return 1;
        } else {
            // result1[i] < result2[i], so condition violated (result1[] > result2[])
            return 0;
        }
    }
    // All elements are equal within tolerance, strictly greater lex comparison means violation
    return 0;
}

TestResult z31runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z31Change(test_cases[test_case_id]);
    // 原始调用
    double* source = ebeAdd(test_cases[test_case_id].a, test_cases[test_case_id].b, test_cases[test_case_id].n1, test_cases[test_case_id].n2); // MODIFIED: Explicit type
    // 变换后调用
    double* follow = ebeAdd(follow_case.a, follow_case.b, follow_case.n1, follow_case.n2);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z31check(source, follow, test_cases[test_case_id].n1);
    test_result.status = status;
    
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z31runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}