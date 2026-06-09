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


double average(int a[], int n){
    double suma = 0;
    for (int i = 0; i < n; i++)
    {
        suma += a[i];
    }
    return suma/n;
}


typedef struct {
    int* a; int n;
} TestCase;

TestCase test_cases[] = {
    {(int[]){4, 1, 5, 2, 3}, 5},
    {(int[]){5, 5, 5, 5}, 4},
    {(int[]){-1, -2, -3}, 3},
    {(int[]){0, 0, 0, 0, 0}, 5},
    {(int[]){10, -10, 10, -10}, 4},
    {(int[]){100, 200, 50}, 3},
    {(int[]){-5, 0, 5}, 3},
    {(int[]){7}, 1},
    {(int[]){-100, 50, -30, 20, -10}, 5},
    {(int[]){3, 3, 2, 2, 1, 1}, 6},
    {(int[]){9, 1, 8, 2, 7, 3, 6, 4, 5}, 9},
    {(int[]){-3, -1, -4, -2, -5}, 5},
    {(int[]){2, -2, 2, -2, 2}, 5},
    {(int[]){15, 0, -15, 30, -30}, 5},
    {(int[]){1, 1, 1, 2, 2, 2, 3, 3, 3}, 9},
    {(int[]){1000, -1000}, 2},
    {(int[]){8, 6, 7, 5, 3, 0, 9}, 7},
    {(int[]){4, 4, 4, 4, 4, 4, 4, 4}, 8},
    {(int[]){-7, 14, -21, 28, -35}, 5},
    {(int[]){0, 1, 0, 1, 0, 1}, 6},
    {(int[]){-9, -8, -7, -6, -5, -4, -3, -2, -1}, 9},
    {(int[]){12, -12, 0, 24, -24}, 5},
    {(int[]){10, 5, 15, 0, 20, 25}, 6},
    {(int[]){-2, -4, -6, -8, -10}, 5},
    {(int[]){3, -3, 6, -6, 9, -9}, 6},
    {(int[]){1, 0, -1, 0, 1}, 5},
    {(int[]){16, 2, 64, 8, 32, 4}, 6},
    {(int[]){-5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5}, 11},
    {(int[]){35, 7, 42, 14, 49, 21, 28}, 7},
    {(int[]){-100, -50, 0, 50, 100}, 5}
};
int num_test_cases = 30;


    typedef struct {
        double result1;
        double result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z2Change(TestCase t1) {
    TestCase follow_case = t1;
    // --- Memory handling code generated based on the rule ---
    int* follow_case_a = (int*)malloc(t1.n * sizeof(int));
    memcpy(follow_case_a, t1.a, t1.n * sizeof(int));
    follow_case.a = follow_case_a;
    // ------------------------------------
    
    // Defensive code generated based on rule (a) to prevent errors when n == 0
    if (follow_case.n == 0) {
        return follow_case;
    }
    
    // Specific operation code: subtract 1 from every element
    for (int i = 0; i < follow_case.n; ++i) {
        follow_case.a[i] -= 1;
    }
    
    return follow_case;
}

int z2check(double result1, double result2) {
    const double epsilon = 1e-5;
    // Rearranged: return.result1 - return.result2 - 1 == 0 -> result1 == result2 + 1
    double A = result1;
    double B = result2 + 1;

    if (std::isnan(A) || std::isnan(B)) return 0;
    if (std::isinf(A) || std::isinf(B)) {
        if (A == B) return 1;
        else return 0;
    }

    double tol = epsilon * fmax(1.0, fmax(fabs(A), fabs(B)));
    if (fabs(A - B) > tol) return 0;

    return 1;
}

TestResult z2runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z2Change(test_cases[test_case_id]);
    // 原始调用
    double source = average(test_cases[test_case_id].a, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    double follow = average(follow_case.a, follow_case.n);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z2check(source, follow);
    test_result.status = status;
    
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z2runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}