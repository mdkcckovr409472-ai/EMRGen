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


double g( double expected[],  double observed[], int n) {
    double sumExpected = 0;
    double sumObserved = 0;
    for (int i = 0; i < n; i++) {
        sumExpected += expected[i];
        sumObserved += observed[i];
    }
    double ratio = 1;
    bool rescale = false;
    if (fabs(sumExpected - sumObserved) > 10E-6) {
        ratio = sumObserved / sumExpected;
        rescale = true;
    }
    double sum = 0;
        for (int i = 0; i < n; i++) {
            double dev = rescale ? log((double) observed[i] / (ratio * expected[i])) : log((double) observed[i] / expected[i]);
            sum += (double) observed[i] * dev;
        }
    return 2 * sum;
}



typedef struct {
    double* expected; double* observed; int n;
} TestCase;

TestCase test_cases[] = {
    { (double[]){1.0, 2.0, 3.0}, (double[]){1.0, 2.0, 3.0}, 3 },
    { (double[]){2.5, 4.0}, (double[]){5.0, 8.0}, 2 },
    { (double[]){0.5, 1.5, 2.5}, (double[]){0.6, 1.4, 2.4}, 3 },
    { (double[]){10.0}, (double[]){5.0}, 1 },
    { (double[]){3.3, 7.7}, (double[]){6.6, 15.4}, 2 },
    { (double[]){1.2, 2.8, 4.6, 5.0}, (double[]){1.2, 2.8, 4.6, 5.0}, 4 },
    { (double[]){9.0, 1.0}, (double[]){3.0, 7.0}, 2 },
    { (double[]){0.1, 0.2, 0.3, 0.4, 0.5}, (double[]){0.2, 0.1, 0.4, 0.3, 0.6}, 5 },
    { (double[]){5.5, 6.5, 7.5}, (double[]){5.5, 6.5, 7.5}, 3 },
    { (double[]){2.0, 3.0, 5.0}, (double[]){4.0, 6.0, 10.0}, 3 },
    { (double[]){1.0, 4.0, 9.0}, (double[]){2.0, 8.0, 18.0}, 3 },
    { (double[]){0.9, 1.1}, (double[]){0.9, 1.1}, 2 },
    { (double[]){8.0, 2.0, 6.0}, (double[]){4.0, 1.0, 3.0}, 3 },
    { (double[]){1.5, 2.5, 3.5, 4.5}, (double[]){3.0, 5.0, 7.0, 9.0}, 4 },
    { (double[]){0.3, 0.7, 1.2}, (double[]){0.6, 1.4, 2.4}, 3 },
    { (double[]){100.0, 200.0}, (double[]){150.0, 250.0}, 2 },
    { (double[]){0.01, 0.02}, (double[]){0.02, 0.04}, 2 },
    { (double[]){3.1415, 2.7182}, (double[]){6.2830, 5.4364}, 2 },
    { (double[]){5.0, 5.0, 5.0}, (double[]){5.0, 5.0, 5.0}, 3 },
    { (double[]){7.0, 3.0, 9.0}, (double[]){14.0, 6.0, 18.0}, 3 },
    { (double[]){1.0, 2.0}, (double[]){1.5, 2.5}, 2 },
    { (double[]){4.4, 5.5, 6.6, 7.7}, (double[]){8.8, 11.0, 13.2, 15.4}, 4 },
    { (double[]){0.25, 0.75, 1.25}, (double[]){0.5, 1.5, 2.5}, 3 },
    { (double[]){2.2, 3.3, 4.4}, (double[]){2.2, 3.3, 4.4}, 3 },
    { (double[]){9.9, 8.8, 7.7}, (double[]){9.9, 8.8, 7.7}, 3 },
    { (double[]){0.6, 1.2, 1.8}, (double[]){0.9, 1.8, 2.7}, 3 },
    { (double[]){1.0, 1.0, 1.0, 1.0}, (double[]){2.0, 2.0, 2.0, 2.0}, 4 },
    { (double[]){3.0, 6.0, 9.0, 12.0}, (double[]){3.0, 6.0, 9.0, 12.0}, 4 },
    { (double[]){0.5, 1.5, 2.5, 3.5}, (double[]){0.75, 2.25, 3.75, 5.25}, 4 },
    { (double[]){ }, (double[]){ }, 0 }
};
int num_test_cases = 30;


    typedef struct {
        double result1;
        double result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z42Change(TestCase t1) {
    TestCase follow_case = t1;
    // Memory handling for observed array
    double* follow_case_observed = (double*)malloc(t1.n * sizeof(double));
    memcpy(follow_case_observed, t1.observed, t1.n * sizeof(double));
    follow_case.observed = follow_case_observed;
    // Defensive check for array length
    if (follow_case.n > 0) {
        for (int i = 0; i < follow_case.n; ++i) {
            follow_case.observed[i] *= 0.5;
        }
    }
    return follow_case;
}

#include <cmath>

int z42check(double result1, double result2) {
    double epsilon = 1e-5;

    // Algebraic rearrangement of return.result1 - 2 * return.result2 == 0:
    // This is equivalent to result1 == 2 * result2
    // So set A = result1, B = 2 * result2 to restore true magnitudes.
    double A = result1;
    double B = 2.0 * result2;

    // Defend against NaN
    if (std::isnan(A) || std::isnan(B))
        return 0;

    // Handle infinity
    if (std::isinf(A) || std::isinf(B)) {
        if (A == B)
            return 1;
        else
            return 0;
    }

    // Dynamic tolerance
    double tol = epsilon * fmax(1.0, fmax(fabs(A), fabs(B)));

    // Tolerance-based equality
    if (fabs(A - B) > tol)
        return 0;

    return 1;
}

TestResult z42runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z42Change(test_cases[test_case_id]);
    // 原始调用
    double source = g(test_cases[test_case_id].expected, test_cases[test_case_id].observed, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    double follow = g(follow_case.expected, follow_case.observed, follow_case.n);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z42check(source, follow);
    test_result.status = status;
    
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z42runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}