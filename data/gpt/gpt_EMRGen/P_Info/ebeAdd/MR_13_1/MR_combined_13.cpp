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

TestCase z13Change(TestCase t1) {
    TestCase follow_case = t1;
    // --- Memory handling code generated based on the rule ---
    if(t1.a != NULL && t1.n1 > 0){
        double* follow_case_a = (double*)malloc(t1.n1 * sizeof(double));
        if(follow_case_a != NULL){
            memcpy(follow_case_a, t1.a, t1.n1 * sizeof(double));
            follow_case.a = follow_case_a;
        } else {
            // malloc failed, return without altering
            return follow_case;
        }
    } else {
        follow_case.a = NULL;
    }
    // ------------------------------------
    
    // Defensive code generated based on rule (a) to prevent errors when n1 < 2
    if (follow_case.a == NULL || follow_case.n1 < 2) {
        // Less than 2 elements, no sorting needed, return replica directly
        return follow_case;
    }
    
    // Specific operation code generated based on the rule
    // Simple ascending sort using bubble sort for demonstration and safety
    for(int i = 0; i < follow_case.n1 - 1; i++){
        for(int j = 0; j < follow_case.n1 - 1 - i; j++){
            if(follow_case.a[j] > follow_case.a[j+1]){
                double temp = follow_case.a[j];
                follow_case.a[j] = follow_case.a[j+1];
                follow_case.a[j+1] = temp;
            }
        }
    }
    
    return follow_case;
}

int z13check(double* result1, double* result2, int n) {
    // 4. Defensive Programming and Boundary Checks
    if (n <= 0) return 1;
    if (result1 == NULL || result2 == NULL) return 0;

    const double epsilon = 1e-5;

    for (int i = 0; i < n; i++) {
        double A = result1[i];
        double B = result2[i];

        // Step 3: Defend against NaN and handle Inf
        if (std::isnan(A) || std::isnan(B)) return 0;
        if (std::isinf(A) || std::isinf(B)) {
            // Condition: result1[i] >= result2[i]
            if (A >= B)
                return 1;
            else
                return 0;
        }

        double tol = epsilon * fmax(1.0, fmax(fabs(A), fabs(B)));
        double diff = A - B;

        if (fabs(diff) <= tol) {
            // Elements considered equal within tolerance; continue checking next
            continue;
        } else if (diff > tol) {
            // A > B + tol: result1[i] > result2[i], condition satisfied, early return 1
            return 1;
        } else {
            // A < B - tol: result1[i] < result2[i], condition violated, return 0
            return 0;
        }
    }

    // All elements equal within tolerance; equality allowed, return 1
    return 1;
}

TestResult z13runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z13Change(test_cases[test_case_id]);
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
    int status = z13check(source, follow, test_cases[test_case_id].n1);
    test_result.status = status;
    
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z13runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}