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


double* calculateAbsoluteDifferences(double z[], int n){
    if (n == 0)
    {
        return NULL;
    }
    
    double* zAbs = (double*)malloc(n * sizeof(double));
    for (int i = 0; i < n; i++)
    {
        zAbs[i] = fabs(z[i]);
    }
    return zAbs;
}


typedef struct {
    double* z; int n;
} TestCase;

TestCase test_cases[] = {
    { (double[]){}, 0 },
    { (double[]){0.5, 2.3, 4.1}, 3 },
    { (double[]){-1.0, -3.14, -0.001}, 3 },
    { (double[]){-2.5, 0.0, 3.7}, 3 },
    { (double[]){5.5, -5.5, 5.5, -5.5}, 4 },
    { (double[]){0.0}, 1 },
    { (double[]){7.89}, 1 },
    { (double[]){-9.99}, 1 },
    { (double[]){-1.2, 1.2, -1.2, 1.2, 0.0}, 5 },
    { (double[]){3.3, -2.2, 0.0, -4.4, 5.5}, 5 },
    { (double[]){0.001, -0.002, 0.003, -0.004}, 4 },
    { (double[]){-1000.0, 500.0, -250.0}, 3 },
    { (double[]){999.9, -999.9}, 2 },
    { (double[]){-10, 0.5, 20.75, -30.125}, 4 },
    { (double[]){0.0, 0.0, -0.0, 0.0}, 4 },
    { (double[]){1.0, -1.0, 2.0, -2.0, 3.0, -3.0}, 6 },
    { (double[]){-0.75, -2.5, -3.125}, 3 },
    { (double[]){0.25, 1.125, 2.875}, 3 },
    { (double[]){-5.5, 4.4, -3.3, 2.2, -1.1, 0.0, 1.1, -2.2, 3.3, -4.4}, 10 },
    { (double[]){8.8, -1.1, 3.3, -7.7, 5.5}, 5 },
    { (double[]){-6.0, 6.0, -6.0, 6.0}, 4 },
    { (double[]){1e-06, -2e-06, 3e-06}, 3 },
    { (double[]){-15.5, 20.0, -25.5, 30.0}, 4 },
    { (double[]){0.0, -12.34, 0.0, 56.78, -0.0}, 5 },
    { (double[]){-1, -2, -3, -4, -5}, 5 },
    { (double[]){1, 2, 3, 4, 5}, 5 },
    { (double[]){-7, 8.0, -9.5, 10}, 4 },
    { (double[]){-999.0}, 1 },
    { (double[]){999.0}, 1 },
    { (double[]){-0.5, 1, -1.5, 2, -2.5, 3}, 6 }
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    for (int i = 0; i < tc.n; i++) {
        tc.z[i] = 1.0;
    }
    return tc;
}

int check(TestCase tc) {
    if (tc.n == 0) {
        // For empty input, both outputs should be NULL according to the function under test
        double* Os = calculateAbsoluteDifferences(tc.z, tc.n);
        TestCase Tf_case = change(tc);
        double* Of = calculateAbsoluteDifferences(Tf_case.z, Tf_case.n);
        int is_valid = 0;
        if (Os == NULL && Of == NULL) {
            is_valid = 1;
        }
        // No heap allocations in this branch, so nothing to free
        return is_valid;
    }

    double* Os = calculateAbsoluteDifferences(tc.z, tc.n);

    if (Os == NULL) {
        // If Os is NULL but n > 0, it's an error, return 0
        return 0;
    }

    TestCase Tf_case = change(tc);
    double* Of = calculateAbsoluteDifferences(Tf_case.z, Tf_case.n);

    if (Of == NULL) {
        free(Os);
        return 0;
    }

    int is_valid = 1;
    for (int i = 0; i < tc.n; i++) {
        if (!(fabs(Of[i] - 1.0) < 1e-12 && Os[i] >= 0)) {
            is_valid = 0;
            break;
        }
    }

    free(Os);
    free(Of);

    return is_valid;
}

int main() {
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        int is_valid = check(test_cases[i]);
        if (is_valid == 0) {
            status_end = 0; 
        }
    }
    std::cout << status_end << std::endl;
    return 0;
}