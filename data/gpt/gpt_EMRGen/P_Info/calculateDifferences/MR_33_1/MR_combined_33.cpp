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

TestCase z33Change(TestCase t1) {
    TestCase follow_case = t1;
    // Deep copy of y array
    double* follow_case_y = (double*)malloc(t1.n * sizeof(double));
    memcpy(follow_case_y, t1.y, t1.n * sizeof(double));
    follow_case.y = follow_case_y;

    // Defensive check for empty array
    if (follow_case.n == 0) {
        return follow_case;
    }

    // Decrement a random element by 0.5
    int idx = rand() % follow_case.n;
    follow_case.y[idx] -= 0.5;

    return follow_case;
}

#include <cmath>

int z33check(double* result1, double* result2, int n) {
    // 4a. Length validity check (FIRST)
    if (n <= 0) return 1;

    // 4b. Null pointer check (SECOND)
    if (result1 == NULL || result2 == NULL) return 0;

    const double epsilon = 1e-5;

    for (int i = 0; i < n; i++) {
        double A = result1[i];
        double B = result2[i];

        // NaN check
        if (std::isnan(A) || std::isnan(B)) return 0;

        // Infinity check
        if (std::isinf(A) || std::isinf(B)) {
            if (A > B) return 1;
            else if (A < B) return 0;
            // If both are infinite and equal, continue checking
            else continue;
        }

        // Calculate dynamic tolerance
        double tol = epsilon * fmax(1.0, fmax(fabs(A), fabs(B)));

        // Lexicographical comparison with tolerance
        if (fabs(A - B) <= tol) {
            // Equal within tolerance, continue checking next element
            continue;
        } else if (A > B + tol) {
            return 1; // condition satisfied
        } else {
            return 0; // condition not satisfied
        }
    }

    // All elements are equal within tolerance, condition strictly requires >
    return 0;
}

TestResult z33runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z33Change(test_cases[test_case_id]);
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
    int status = z33check(source, follow, test_cases[test_case_id].n);
    test_result.status = status;
    
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z33runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}