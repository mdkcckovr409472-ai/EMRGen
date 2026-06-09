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
    TestCase tf = tc;
    if (tf.n > 0) {
        for (int i = tf.n / 2; i < tf.n; i++) {
            tf.z[i] = tf.z[i] * 3;
        }
    }
    return tf;
}

int check(TestCase tc) {
    double* Os = calculateAbsoluteDifferences(tc.z, tc.n);
    if (tc.n == 0) {
        // Os should be NULL, so just verify that and return 1 (MR holds trivially)
        return Os == NULL ? 1 : (Os ? (free(Os), 0) : 0);
    }

    TestCase Tf_case = change(tc);
    double* Of = calculateAbsoluteDifferences(Tf_case.z, Tf_case.n);

    if (Os == NULL || Of == NULL) {
        if (Os) free(Os);
        if (Of) free(Of);
        return 0;
    }

    double sum_Os_first_half = 0.0;
    double sum_Os_second_half = 0.0;
    double sum_Of_first_half = 0.0;
    double sum_Of_second_half = 0.0;

    int mid = tc.n / 2;

    for (int i = 0; i < tc.n; i++) {
        if (i < mid) {
            sum_Os_first_half += Os[i];
            sum_Of_first_half += Of[i];
        } else {
            sum_Os_second_half += Os[i];
            sum_Of_second_half += Of[i];
        }
    }

    free(Os);
    free(Of);

    int is_valid = 0;
    double eps = 1e-9;
    if (fabs(sum_Of_first_half - sum_Os_first_half) < eps &&
        fabs(sum_Of_second_half - 3.0 * sum_Os_second_half) < eps) {
        is_valid = 1;
    }

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