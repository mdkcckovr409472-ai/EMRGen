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


double* calculateDifferences(double x[], double y[], int n){

    double* z = (double*)malloc(n * sizeof(double));

    for (int i = 0; i < n; i++)
    {
        z[i] = y[i] - x[i];
    }

    return z;
}


typedef struct {
    double* x; double* y; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0, 2.0, 3.0}, (double[]){4.0, 5.0, 6.0}, 3},
    {(double[]){0.0, -1.5, 2.5, -3.0, 4.0}, (double[]){1.0, -0.5, 3.0, -2.0, 5.5}, 5},
    {(double[]){10.0}, (double[]){5.0}, 1},
    {(double[]){}, (double[]){}, 0},
    {(double[]){100.0, -100.0, 0.0, 50.0}, (double[]){-100.0, 100.0, 0.0, -50.0}, 4},
    {(double[]){3.14, -2.71}, (double[]){2.71, 3.14}, 2},
    {(double[]){5.5, -4.2, 3.3, -2.1, 0.0, 1.1}, (double[]){-5.5, 4.2, -3.3, 2.1, 0.0, -1.1}, 6},
    {(double[]){7.0, 7.0, 7.0}, (double[]){8.0, 8.0, 8.0}, 3},
    {(double[]){0.0, 0.0, 0.0, 0.0, 0.0}, (double[]){1.0, -1.0, 2.0, -2.0, 0.5}, 5},
    {(double[]){2.5, -3.5}, (double[]){2.5, -3.5}, 2},
    {(double[]){20.0, 30.0, 40.0}, (double[]){25.0, 35.0, 45.0}, 3},
    {(double[]){-10.0, -20.0, -30.0}, (double[]){-5.0, -15.0, -25.0}, 3},
    {(double[]){-5.0, 10.0, -15.0, 20.0}, (double[]){5.0, -10.0, 15.0, -20.0}, 4},
    {(double[]){1.1, 2.2, 3.3, 4.4, 5.5}, (double[]){5.5, 4.4, 3.3, 2.2, 1.1}, 5},
    {(double[]){1.0, 2.0, 1.0}, (double[]){2.0, 1.0, 2.0}, 3},
    {(double[]){-9.0, 8.0, -7.0, 6.0, -5.0, 4.0, -3.0}, (double[]){9.0, -8.0, 7.0, -6.0, 5.0, -4.0, 3.0}, 7},
    {(double[]){0.0}, (double[]){0.0}, 1},
    {(double[]){0.0, 5.0}, (double[]){5.0, 0.0}, 2},
    {(double[]){1.0, 2.0, 3.0, 4.0}, (double[]){4.0, 3.0, 2.0, 1.0}, 4},
    {(double[]){5.0, 5.0, 5.0, 5.0, 5.0}, (double[]){5.0, 5.0, 5.0, 5.0, 5.0}, 5},
    {(double[]){9.0, 8.0, 7.0}, (double[]){1.0, 2.0, 3.0}, 3},
    {(double[]){1.0, 2.0, 3.0}, (double[]){9.0, 8.0, 7.0}, 3},
    {(double[]){-1.2, 3.4, -5.6, 7.8, -9.0, 10.1}, (double[]){1.2, -3.4, 5.6, -7.8, 9.0, -10.1}, 6},
    {(double[]){-4.0, 6.0}, (double[]){4.0, -6.0}, 2},
    {(double[]){0.25, 0.5, 0.75, 1.0}, (double[]){1.25, 1.5, 1.75, 2.0}, 4},
    {(double[]){3.3, 3.3, 3.3}, (double[]){3.3, 3.3, 3.3}, 3},
    {(double[]){-2.0, 2.0, -2.0, 2.0, -2.0}, (double[]){2.0, -2.0, 2.0, -2.0, 2.0}, 5},
    {(double[]){0.001, -0.001, 0.002, -0.002}, (double[]){-0.001, 0.001, -0.002, 0.002}, 4},
    {(double[]){15.0, -15.0, 30.0}, (double[]){-15.0, 15.0, -30.0}, 3},
    {(double[]){8.8, -7.7, 6.6, -5.5, 4.4}, (double[]){-8.8, 7.7, -6.6, 5.5, -4.4}, 5}
};
int num_test_cases = 30;


    typedef struct {
        double* result1;
        double* result2;
        double** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z38Change(TestCase t1) {
    TestCase follow_case = t1;
    // --- Memory handling code generated based on the rule ---
    double* follow_case_y = (double*)malloc(t1.n * sizeof(double));
    memcpy(follow_case_y, t1.y, t1.n * sizeof(double));
    follow_case.y = follow_case_y;
    // ------------------------------------
    
    // Defensive code generated based on rule (a) to prevent errors when n < 2
    if (follow_case.n < 2) {
        return follow_case;
    }
    
    // Specific operation code generated based on the rule: sort array in ascending order
    std::sort(follow_case.y, follow_case.y + follow_case.n);
    
    return follow_case;
}

#include <cmath>
int z38check(double* result1, double* result2, int n) {
    // 4.a Defensive check: length validity
    if (n <= 0) return 1;
    // 4.b Defensive check: null pointer check
    if (result1 == NULL || result2 == NULL) return 0;

    const double epsilon = 1e-5;
    // Invariant: result1[] >= result2[] (lexically)

    for (int i = 0; i < n; i++) {
        double A = result1[i];
        double B = result2[i];

        if (std::isnan(A) || std::isnan(B)) return 0;
        if (std::isinf(A) || std::isinf(B)) {
            if (A >= B) return 1;
            else return 0;
        }

        double tol = epsilon * fmax(1.0, fmax(fabs(A), fabs(B)));
        double diff = A - B;

        if (fabs(diff) <= tol) {
            // equal within tolerance, continue to next element
            continue;
        } else if (diff > tol) {
            // result1[i] > result2[i], so invariant is satisfied at this element => return 1
            return 1;
        } else {
            // result1[i] < result2[i], invariant violated => return 0
            return 0;
        }
    }
    // All elements equal within tolerance, condition allows equality => return 1
    return 1;
}

TestResult z38runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z38Change(test_cases[test_case_id]);
    // 原始调用
    double* source = calculateDifferences(test_cases[test_case_id].x, test_cases[test_case_id].y, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    double* follow = calculateDifferences(follow_case.x, follow_case.y, follow_case.n);
    
    double** memory_list = (double**)malloc(1 * sizeof(double*));
    memory_list[0] = follow_case.y;
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z38check(source, follow, test_cases[test_case_id].n);
    test_result.status = status;
    
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z38runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}