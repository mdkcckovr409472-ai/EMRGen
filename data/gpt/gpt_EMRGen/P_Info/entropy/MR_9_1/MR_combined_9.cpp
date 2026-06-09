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


double entropy(double k[], int n){
    double h = 0;
    double sum_k = 0;
    for (int i = 0; i < n; i++) {
        sum_k += (double) k[i];
    }
    for (int i = 0; i < n; i++) {
        if (k[i] != 0) {
            double p_i = (double) k[i] / sum_k;
            h += p_i * log(p_i);
        }
    }
    return -h;
}


typedef struct {
    double* k; int n;
} TestCase;

TestCase test_cases[] = {
    { (double[]){}, 0 },
    { (double[]){1.0}, 1 },
    { (double[]){0.0}, 1 },
    { (double[]){2.5, 2.5}, 2 },
    { (double[]){3.0, 1.0}, 2 },
    { (double[]){0.0, 4.0, 2.0}, 3 },
    { (double[]){5.5, 1.2, 3.3}, 3 },
    { (double[]){7.0, 0.0, 2.0, 5.0}, 4 },
    { (double[]){1.0, 1.0, 2.0, 2.0, 3.0}, 5 },
    { (double[]){0.5, 2.5, 1.5, 3.5, 4.5, 0.5}, 6 },
    { (double[]){1.0, 0.0, 0.0, 2.0, 3.0, 0.0, 4.0}, 7 },
    { (double[]){2.2, 3.3, 1.1, 4.4, 0.0, 5.5, 6.6, 1.0}, 8 },
    { (double[]){0.0, 1.0, 0.0, 2.0, 0.0, 3.0, 0.0, 4.0, 0.0}, 9 },
    { (double[]){5.0, 4.0, 3.0, 2.0, 1.0, 0.5, 0.5, 1.5, 2.5, 3.5}, 10 },
    { (double[]){1.0, 2.0, 1.0, 2.0, 1.0, 2.0, 1.0, 2.0, 1.0, 2.0, 1.0}, 11 },
    { (double[]){0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2}, 12 },
    { (double[]){3.0, 0.0, 3.0, 0.0, 3.0, 0.0, 3.0, 0.0, 3.0, 0.0, 3.0, 0.0, 3.0}, 13 },
    { (double[]){2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0, 16.0, 18.0, 20.0, 22.0, 24.0, 26.0, 28.0}, 14 },
    { (double[]){1.5, 2.5, 3.5, 4.5, 5.5, 6.5, 7.5, 8.5, 9.5, 10.5, 11.5, 12.5, 13.5, 14.5, 15.5}, 15 },
    { (double[]){0.0, 0.0, 0.0, 1.0}, 4 },
    { (double[]){5.0, 5.0, 5.0, 5.0, 5.0}, 5 },
    { (double[]){9.9, 0.1, 9.8, 0.2, 9.7, 0.3}, 6 },
    { (double[]){3.1415, 2.7182, 1.618, 0.5772, 0.0}, 5 },
    { (double[]){0.25, 0.75, 0.5, 0.25, 0.75, 0.5}, 6 },
    { (double[]){4.0, 2.0, 0.0, 2.0, 4.0}, 5 },
    { (double[]){1.0, 3.0, 5.0, 7.0, 9.0, 11.0, 13.0}, 7 },
    { (double[]){2.0, 2.0, 0.0, 2.0, 2.0, 0.0, 2.0}, 7 },
    { (double[]){0.0, 1.0, 2.0, 0.0, 1.0, 2.0, 0.0, 1.0}, 8 },
    { (double[]){6.0, 3.0, 0.0, 3.0, 6.0, 9.0, 12.0, 15.0, 0.0}, 9 },
    { (double[]){0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5}, 10 }
};
int num_test_cases = 30;


    typedef struct {
        double result1;
        double result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z9Change(TestCase t1) {
    TestCase follow_case = t1;
    // --- Memory handling code generated based on the rule ---
    double* follow_case_k = (double*)malloc(t1.n * sizeof(double));
    memcpy(follow_case_k, t1.k, t1.n * sizeof(double));
    follow_case.k = follow_case_k;
    // ------------------------------------
    
    // Defensive code: ensure there is at least one element
    if (follow_case.n <= 0) {
        return follow_case;
    }
    
    // Reverse array operation
    for (int i = 0; i < follow_case.n / 2; ++i) {
        double temp = follow_case.k[i];
        follow_case.k[i] = follow_case.k[follow_case.n - 1 - i];
        follow_case.k[follow_case.n - 1 - i] = temp;
    }
    
    return follow_case;
}

int z9check(double result1, double result2) {
    const double epsilon = 1e-5;
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

TestResult z9runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z9Change(test_cases[test_case_id]);
    // 原始调用
    double source = entropy(test_cases[test_case_id].k, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    double follow = entropy(follow_case.k, follow_case.n);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z9check(source, follow);
    test_result.status = status;
    
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z9runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}