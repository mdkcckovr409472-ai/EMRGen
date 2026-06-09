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


double errorRate(double labels[], double predictions[], int n) {
    double nberrors = 0;
    double datasize = 0;
    for (int index = 0; index < n; index++) {
        if (predictions[index] == -1) {
            continue;
        }
        if (predictions[index] != labels[index]) {
            nberrors++;
        }
        datasize++;
    }
    return nberrors / datasize;
}


typedef struct {
    double* labels; double* predictions; int n;
} TestCase;

TestCase test_cases[] = {
    { (double[]){0.0, 1.0, 0.0}, (double[]){0.0, 1.0, 0.0}, 3 },
    { (double[]){0.0, 0.0, 0.0}, (double[]){1.0, 1.0, 1.0}, 3 },
    { (double[]){1.0, 0.0, 1.0, 0.0}, (double[]){1.0, -1.0, 0.0, -1.0}, 4 },
    { (double[]){0.0, 1.0, 2.0}, (double[]){-1.0, -1.0, 2.0}, 3 },
    { (double[]){0.5, -0.2, 0.3}, (double[]){0.5, -0.2, -0.3}, 3 },
    { (double[]){1.1, 2.2, 3.3, 4.4, 5.5}, (double[]){1.1, -1.0, 0.0, 4.4, 5.0}, 5 },
    { (double[]){1.0, 1.0, 1.0, 2.0, 2.0, 2.0}, (double[]){1.0, 2.0, -1.0, 2.0, 1.0, -1.0}, 6 },
    { (double[]){5.0, 6.0}, (double[]){-1.0, 6.0}, 2 },
    { (double[]){-1.0, -2.0, -3.0, -4.0}, (double[]){-1.0, -2.0, -3.0, -5.0}, 4 },
    { (double[]){1.0, 2.0, 3.0, 4.0, 5.0}, (double[]){-1.0, -1.0, -1.0, 0.0, 0.0}, 5 },
    { (double[]){10.0, 20.0, 30.0, 40.0, 50.0}, (double[]){10.0, 20.0, 30.0, 40.0, 50.0}, 5 },
    { (double[]){10.0, 20.0, 30.0, 40.0, 50.0}, (double[]){11.0, 21.0, 31.0, 41.0, 51.0}, 5 },
    { (double[]){0.1, 0.2, 0.3}, (double[]){0.1, 0.2, 0.4}, 3 },
    { (double[]){3.14}, (double[]){3.14}, 1 },
    { (double[]){3.14}, (double[]){2.71}, 1 },
    { (double[]){5.0, -5.0, 10.0, -10.0, 0.0, 1.0}, (double[]){5.0, -5.0, -1.0, -10.0, 2.0, 1.0}, 6 },
    { (double[]){0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0}, (double[]){0.0, -1.0, 2.0, -1.0, 5.0, 5.0, -1.0}, 7 },
    { (double[]){100.0, -100.0, 0.0}, (double[]){-1.0, -100.0, 1.0}, 3 },
    { (double[]){0.0, 0.0, 0.0, 0.0}, (double[]){0.0, -1.0, 1.0, 0.0}, 4 },
    { (double[]){1000.0, 2000.0, 3000.0, 4000.0, 5000.0, 6000.0}, (double[]){1000.0, -1.0, 3001.0, 4000.0, -1.0, 6000.0}, 6 },
    { (double[]){7.0, 7.0, 7.0, 7.0, 7.0}, (double[]){7.0, -1.0, 8.0, 7.0, -1.0}, 5 },
    { (double[]){1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0}, (double[]){-1.0, 2.0, -1.0, 4.0, 5.0, -1.0, 7.0, 9.0}, 8 },
    { (double[]){-1.0, -2.0, -3.0}, (double[]){-1.0, -2.0, -3.0}, 3 },
    { (double[]){1.0, 2.0, 3.0, 4.0}, (double[]){-1.0, -1.0, 5.0, -1.0}, 4 },
    { (double[]){0.0, 1.0, 0.0, 1.0, 0.0}, (double[]){0.0, 0.0, 0.0, 1.0, 1.0}, 5 },
    { (double[]){10.0, 20.0, 30.0, 40.0, 50.0, 60.0}, (double[]){10.0, -1.0, 30.0, -1.0, 50.0, 60.0}, 6 }
};
int num_test_cases = 26;


    typedef struct {
        double result1;
        double result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z6Change(TestCase t1) {
    TestCase follow_case = t1;
    // Deep copy of labels array
    double* follow_case_labels = (double*)malloc(t1.n * sizeof(double));
    memcpy(follow_case_labels, t1.labels, t1.n * sizeof(double));
    follow_case.labels = follow_case_labels;

    // Defensive check for empty array
    if (follow_case.n <= 0) {
        return follow_case;
    }

    // Set a random element to -1.0 if it is greater than -1.0
    int idx = rand() % follow_case.n;
    if (follow_case.labels[idx] > -1.0) {
        follow_case.labels[idx] = -1.0;
    }

    return follow_case;
}

int z6check(double result1, double result2) {
    // Core evaluation logic (direct scalar comparison)

    // Step 1: Define the base tolerance
    double epsilon = 1e-5;

    // Step 2: Rearrange inequality "result1 <= result2"
    // Here, we keep A = result1, B = result2 to preserve magnitude for tolerance computation

    double A = result1;
    double B = result2;

    // Step 3: NaN and Inf checks
    if (std::isnan(A) || std::isnan(B)) return 0;
    if (std::isinf(A) || std::isinf(B)) {
        if (A <= B) return 1;
        else return 0;
    }

    // Step 4: Calculate dynamic tolerance
    double tol = epsilon * fmax(1.0, fmax(fabs(A), fabs(B)));

    // Step 5: Tolerance-based comparison for <= condition
    if (A > B + tol) return 0;

    // Satisfied
    return 1;
}

TestResult z6runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z6Change(test_cases[test_case_id]);
    // 原始调用
    double source = errorRate(test_cases[test_case_id].labels, test_cases[test_case_id].predictions, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    double follow = errorRate(follow_case.labels, follow_case.predictions, follow_case.n);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z6check(source, follow);
    test_result.status = status;
    
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z6runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}