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


double* ebeSubtract(double a[], double b[], int n1, int n2) {
    if (n1 != n2 || a == NULL || b == NULL) {
        return NULL;
    }

    double* result = (double*)malloc(n1 * sizeof(double));
    if (!result) return NULL;

    for (int i = 0; i < n1; i++) {
        result[i] = a[i] - b[i];
    }
    return result;
}


typedef struct {
    double* a; double* b; int n1; int n2;
} TestCase;

TestCase test_cases[] = {
    {(double[]){10.5, -20.2, 300.1}, (double[]){5.5, 10.2, 100.0}, 3, 3},
    {(double[]){42.42, 999.99, 0.001}, (double[]){-1000.0, 50.0, 0.0001}, 3, 3},
    {(double[]){1500.0, -300.3, 50.555}, (double[]){1499.0, -299.0, 49.55}, 3, 3},
    {(double[]){-500.0, 200.2, -100.1}, (double[]){-501.0, 198.0, -101.0}, 3, 3},
    {(double[]){0.123, 456.789, -123.456}, (double[]){0.120, 460.0, -120.0}, 3, 3},
    {(double[]){9999.9, -8888.8, 7777.7}, (double[]){9990, -8890, 7750}, 3, 3},
    {(double[]){3.14, 2.71, 1.618}, (double[]){3.0, 3.0, 1.6}, 3, 3},
    {(double[]){123.4, 567.8, 910.1, 11.11}, (double[]){120.0, 560.0, 900.0, 10.1}, 4, 4},
    {(double[]){1000.0, -1000.0, 0.0, 123.0}, (double[]){900.0, -1050.0, 5.0, 121.0}, 4, 4},
    {(double[]){50.5, 60.6, 70.7, 80.8, 90.9}, (double[]){45.0, 55.0, 65.0, 75.0, 85.0}, 5, 5},
    {(double[]){-100.1, 200.2, -300.3, 400.4}, (double[]){-90.0, 210.0, -310.0, 390.0}, 4, 4},
    {(double[]){0.0001, 0.001, 0.01}, (double[]){0.00005, 0.0005, 0.005}, 3, 3},
    {(double[]){123456.789, -123456.789}, (double[]){123000, -123000}, 2, 2},
    {(double[]){87.654, -32.198, 76.543}, (double[]){85.0, -30.0, 70.0}, 3, 3},
    {(double[]){11.11, 22.22, 33.33, 44.44}, (double[]){10.10, 21.21, 31.31, 41.41}, 4, 4},
    {(double[]){9.9, 8.8, 7.7, 6.6, 5.5}, (double[]){7.7, 6.6, 5.5, 4.4, 3.3}, 5, 5},
    {(double[]){100.0, 200.0, 300.0}, (double[]){90.0, 180.0, 270.0}, 3, 3},
    {(double[]){0.5, 1.5, 2.5, 3.5}, (double[]){0.4, 1.4, 2.4, 3.4}, 4, 4},
    {(double[]){-1000, 0, 1000}, (double[]){-900, 100, 900}, 3, 3},
    {(double[]){14.14, 28.28, 56.56, 112.11}, (double[]){12.12, 24.24, 48.48, 96.96}, 4, 4},
    {(double[]){123.0, 234.0, 345.0, 456.0}, (double[]){120.0, 230.0, 340.0, 450.0}, 4, 4},
    {(double[]){-12.34, -56.78, 90.12}, (double[]){-10.0, -50.0, 80.0}, 3, 3},
    {(double[]){500.5, -500.5, 100.1}, (double[]){490.0, -490.0, 90.0}, 3, 3},
    {(double[]){700.7, 800.8, 900.9}, (double[]){600.6, 700.7, 800.8}, 3, 3},
    {(double[]){1.0, 2.0, 3.0, 4.0, 5.0}, (double[]){0.5, 1.5, 2.5, 3.5, 4.5}, 5, 5},
    {(double[]){-7.89, 6.54, -3.21}, (double[]){-6.78, 5.43, -2.10}, 3, 3},
    {(double[]){1234567.89, -987654.32}, (double[]){1234500, -987600}, 2, 2},
    {(double[]){321.0, 654.0, 987.0}, (double[]){310.0, 640.0, 970.0}, 3, 3},
    {(double[]){14.3, 15.2, 16.1}, (double[]){13.3, 14.2, 15.1}, 3, 3}
};
int num_test_cases = 29;


    typedef struct {
        double* result1;
        double* result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z27Change(TestCase t1) {
    TestCase follow_case = t1;

    // --- Memory handling code generated based on the rule ---
    double* follow_case_b = (double*)malloc(t1.n2 * sizeof(double));
    if (t1.b != NULL && t1.n2 > 0 && follow_case_b != NULL) {
        memcpy(follow_case_b, t1.b, t1.n2 * sizeof(double));
    }
    follow_case.b = follow_case_b;
    // ------------------------------------

    // Defensive code generated based on rule (a) to prevent errors when n2 < 1
    if (follow_case.n2 <= 0) {
        // No elements to process, return replica directly
        return follow_case;
    }

    // Specific operation code generated based on the rule
    for (int i = 0; i < follow_case.n2; i++) {
        follow_case.b[i] += 1.0;
    }

    return follow_case;
}

#include <cmath>

int z27check(double* result1, double* result2, int n) {
    // 4. Defensive Programming and Boundary Checks (Highest Priority & STRICT ORDER):
    if (n <= 0) return 1;
    if (result1 == NULL || result2 == NULL) return 0;

    // 3. Special Handling for Floating-Point Comparisons (Dynamic Tolerance and Infinity Handling):
    double epsilon = 1e-5;

    for (int i = 0; i < n; i++) {
        double A = result1[i];
        double B = result2[i];

        if (std::isnan(A) || std::isnan(B)) return 0;
        if (std::isinf(A) || std::isinf(B)) {
            if (A > B) {
                // condition satisfied
            } else {
                return 0;
            }
            continue;
        }

        double tol = epsilon * fmax(1.0, fmax(fabs(A), fabs(B)));

        // Condition: return.result1[] > return.result2[] (elementwise)
        if (!(A > B + tol)) {
            return 0;
        }
    }

    return 1;
}

TestResult z27runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z27Change(test_cases[test_case_id]);
    // 原始调用
    double* source = ebeSubtract(test_cases[test_case_id].a, test_cases[test_case_id].b, test_cases[test_case_id].n1, test_cases[test_case_id].n2); // MODIFIED: Explicit type
    // 变换后调用
    double* follow = ebeSubtract(follow_case.a, follow_case.b, follow_case.n1, follow_case.n2);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z27check(source, follow, test_cases[test_case_id].n1);
    test_result.status = status;
    
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z27runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}