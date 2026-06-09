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


double geometric_mean(int a[], int n) {
    long product = 1;
    for (int i = 0; i < n; i++) {
        product *= a[i];
    }
    return pow(product, (double) 1 / n);
}


typedef struct {
    int* a; int n;
} TestCase;

TestCase test_cases[] = {
    {(int[]){1, 2, 3}, 3},
    {(int[]){4, 5, 6}, 3},
    {(int[]){10, 20, 30, 40}, 4},
    {(int[]){7, 3, 11, 2, 8}, 5},
    {(int[]){15, 25, 35, 45, 55, 65}, 6},
    {(int[]){9, 13, 17, 19}, 4},
    {(int[]){21, 22, 23, 24, 25}, 5},
    {(int[]){11, 13, 12, 15, 14}, 5},
    {(int[]){2, 11, 7, 9, 5, 10}, 6},
    {(int[]){100, 150, 200}, 3},
    {(int[]){5, 8, 6, 7, 3, 12}, 6},
    {(int[]){3, 17, 29, 101}, 4},
    {(int[]){45, 55, 60, 73, 85}, 5},
    {(int[]){13, 23, 19, 31}, 4},
    {(int[]){19, 7, 22}, 3},
    {(int[]){27, 33, 29, 24}, 4},
    {(int[]){8, 14, 9, 16, 11}, 5},
    {(int[]){2, 4, 6, 8, 10, 12, 14}, 7},
    {(int[]){50, 70, 65, 80}, 4},
    {(int[]){95, 85, 75, 65, 55}, 5},
    {(int[]){28, 39, 47, 35}, 4},
    {(int[]){44, 42, 38, 50}, 4},
    {(int[]){60, 72, 84, 96, 108}, 5},
    {(int[]){18, 29, 41, 37}, 4},
    {(int[]){1, 3, 7, 9, 13}, 5},
    {(int[]){6, 12, 24, 36, 48}, 5},
    {(int[]){16, 32, 64, 128}, 4},
    {(int[]){5, 10, 15, 20, 25, 30}, 6},
    {(int[]){70, 55, 40, 25}, 4},
    {(int[]){33, 44, 55, 66, 77}, 5}
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
    if (t1.n > 0) {
        int* follow_case_a = (int*)malloc(t1.n * sizeof(int));
        if (follow_case_a != NULL) {
            memcpy(follow_case_a, t1.a, t1.n * sizeof(int));
            follow_case.a = follow_case_a;
        } else {
            // malloc failed, return original to avoid crash
            return follow_case;
        }
    }
    // ------------------------------------

    // Defensive code generated based on rule (a) to prevent errors when n < 2
    if (follow_case.n < 2) {
        // Less than 2 elements, no need to reverse, return replica directly
        return follow_case;
    }

    // Specific operation code generated based on the rule
    int left = 0;
    int right = follow_case.n - 1;
    while (left < right) {
        int temp = follow_case.a[left];
        follow_case.a[left] = follow_case.a[right];
        follow_case.a[right] = temp;
        left++;
        right--;
    }

    return follow_case;
}

int z9check(double result1, double result2) {
    double epsilon = 1e-5;
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
    double source = geometric_mean(test_cases[test_case_id].a, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    double follow = geometric_mean(follow_case.a, follow_case.n);
    
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