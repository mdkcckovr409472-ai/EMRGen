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


double winsorizedMean(double elements[], int left, int right, int n) {
    qsort(elements, n, sizeof(double), [](const void *a, const void *b) -> int {
        double diff = *(double *)a - *(double *)b;
        if (diff > 0) return 1;
        else if (diff < 0) return -1;
        else return 0;
    });

    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += elements[i];
    }

    double mean = sum / n;

    if (n > 0 && left >= 0 && left < n) {
        double leftElement = elements[left];
        for (int i = 0; i < left; ++i) {
            mean += (leftElement - elements[i]) / n;
        }
    }

    if (n > 0 && right >= 0 && right < n && (n - 1 - right) >= 0) {
        double rightElement = elements[n - 1 - right];
        for (int i = 0; i < right; ++i) {
            mean += (rightElement - elements[n - 1 - i]) / n;
        }
    }

    return mean;
}

typedef struct {
    double* elements; int left; int right; int n;
} TestCase;

TestCase test_cases[] = {
    { (double[]){3.0, 1.0, 2.0}, 0, 0, 3 },
    { (double[]){3.0, 1.0, 2.0}, 1, 0, 3 },
    { (double[]){3.0, 1.0, 2.0}, 0, 1, 3 },
    { (double[]){3.0, 1.0, 2.0}, 1, 1, 3 },
    { (double[]){5.0, 5.0, 2.0, 8.0, 5.0}, 2, 1, 5 },
    { (double[]){-3.5, 2.2, 0.0, -1.1, 4.4, 3.3}, 2, 2, 6 },
    { (double[]){10.0, -5.0, 3.0, 7.0, 2.0}, 0, 0, 5 },
    { (double[]){10.0, -5.0, 3.0, 7.0, 2.0}, 2, 0, 5 },
    { (double[]){10.0, -5.0, 3.0, 7.0, 2.0}, 0, 2, 5 },
    { (double[]){10.0, -5.0, 3.0, 7.0, 2.0}, 2, 2, 5 },
    { (double[]){1.0, 9.0, -4.0, 6.0, 2.0, 8.0}, 3, 1, 6 },
    { (double[]){1.0, 9.0, -4.0, 6.0, 2.0, 8.0}, 1, 3, 6 },
    { (double[]){4.0, -2.0, 7.0, 1.0, 5.0, 3.0, 6.0}, 3, 3, 7 },
    { (double[]){0.5, 2.5, -1.5, 4.0}, 3, 0, 4 },
    { (double[]){0.5, 2.5, -1.5, 4.0}, 0, 3, 4 },
    { (double[]){0.0, -2.0, 3.0, 0.0, 5.0}, 2, 2, 5 },
    { (double[]){7.0, 7.0, 7.0, 7.0}, 1, 1, 4 },
    { (double[]){12.0, 8.0, 15.0, 9.0, 11.0, 10.0}, 2, 1, 6 },
    { (double[]){0.1, 0.2, 0.3, 0.4, 0.5}, 1, 2, 5 },
    { (double[]){5.0, -5.0}, 0, 0, 2 },
    { (double[]){5.0, -5.0}, 1, 0, 2 },
    { (double[]){5.0, -5.0}, 0, 1, 2 },
    { (double[]){9.0, 1.0, 5.0}, 2, 2, 3 },
    { (double[]){3.3, -1.2, 4.5, 0.0, 2.2, -3.3, 5.5, 1.1}, 3, 2, 8 },
    { (double[]){6.6, -2.2, 3.3, 8.8, 0.0, -5.5, 7.7, 2.2, 4.4}, 4, 4, 9 },
    { (double[]){5.0, 1.0, 8.0, 3.0, 10.0, 2.0, 9.0, 4.0, 7.0, 6.0}, 5, 5, 10 },
    { (double[]){-1.0, -3.0, -2.0}, 1, 1, 3 },
    { (double[]){0.0, -1.0, 2.0, -2.0, 3.0}, 2, 1, 5 },
    { (double[]){4.0, 1.0, 5.0, 2.0, 6.0, 3.0}, 2, 2, 6 },
    { (double[]){7.0, 2.0, 9.0, 4.0, 1.0}, 0, 0, 5 }
};
int num_test_cases = 30;


    typedef struct {
        double result1;
        double result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z1Change(TestCase t1) {
    TestCase follow_case = t1;
    // Memory handling code generated based on the rule
    double* follow_case_elements = (double*)malloc(t1.n * sizeof(double));
    memcpy(follow_case_elements, t1.elements, t1.n * sizeof(double));
    follow_case.elements = follow_case_elements;
    // Defensive code generated based on rule (a) to prevent errors when n == 0
    if (follow_case.n == 0) {
        return follow_case;
    }
    // Specific operation code: add 1.0 to all elements
    for (int i = 0; i < follow_case.n; ++i) {
        follow_case.elements[i] += 1.0;
    }
    return follow_case;
}

int z1check(double result1, double result2) {
    const double epsilon = 1e-5;
    // Rearranged invariant: result1 - result2 + 1 == 0  ->  result1 == result2 - 1
    double A = result1;
    double B = result2 - 1;

    if (std::isnan(A) || std::isnan(B)) return 0;
    if (std::isinf(A) || std::isinf(B)) {
        if (A == B) return 1;
        else return 0;
    }

    double tol = epsilon * fmax(1.0, fmax(fabs(A), fabs(B)));

    if (fabs(A - B) > tol) return 0;

    return 1;
}

TestResult z1runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z1Change(test_cases[test_case_id]);
    // 原始调用
    double source = winsorizedMean(test_cases[test_case_id].elements, test_cases[test_case_id].left, test_cases[test_case_id].right, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    double follow = winsorizedMean(follow_case.elements, follow_case.left, follow_case.right, follow_case.n);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z1check(source, follow);
    test_result.status = status;
    
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z1runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}