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
    {(double[]){1.0, 2.0, 3.0}, 3},
    {(double[]){-1.0, -2.0, -3.0}, 3},
    {(double[]){0.0, 0.0, 0.0}, 3},
    {(double[]){-5.5, 10.2, -3.7}, 3},
    {(double[]){1.5}, 1},
    {(double[]){-1.5}, 1},
    {(double[]){0.0}, 1},
    {(double[]){100.0, -100.0}, 2},
    {(double[]){3.14159, -2.71828}, 2},
    {(double[]){1.1, 2.2, 3.3, 4.4}, 4},
    {(double[]){-1.1, -2.2, -3.3, -4.4}, 4},
    {(double[]){0.1, -0.1, 0.01, -0.01}, 4},
    {(double[]){-10.0, 20.0, -30.0, 40.0, -50.0}, 5},
    {(double[]){0.5, -0.5, 1.0, -1.0, 1.5, -1.5}, 6},
    {(double[]){2.0}, 1},
    {(double[]){-2.0}, 1},
    {(double[]){1.0, -1.0}, 2},
    {(double[]){10.0, 0.0, -10.0}, 3},
    {(double[]){0.25, -0.75, 1.25}, 3},
    {(double[]){-0.001, 0.001}, 2},
    {(double[]){999.999, -999.999}, 2},
    {(double[]){1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0}, 10},
    {(double[]){-1.0, -2.0, -3.0, -4.0, -5.0, -6.0, -7.0, -8.0, -9.0, -10.0}, 10},
    {(double[]){1.2, -3.4, 5.6, -7.8, 9.0}, 5},
    {(double[]){-1.2, 3.4, -5.6, 7.8, -9.0}, 5},
    {(double[]){0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, 6},
    {(double[]){12.34}, 1},
    {(double[]){-56.78}, 1},
    {(double[]){1.0, 0.0, -1.0, 0.5, -0.5}, 5},
    {(double[]){-1000.0, 500.0, -250.0, 125.0}, 4}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    if (tf.z != NULL && tf.n > 0) {
        for (int i = 0; i < tf.n; i++) {
            tf.z[i] = fabs(tf.z[i]);
        }
    }
    return tf;
}

int check(TestCase tc) {
    double* Os = calculateAbsoluteDifferences(tc.z, tc.n);
    if (Os == NULL && tc.n != 0) {
        return 0;
    }
    TestCase Tf_case = change(tc);
    double* Of = calculateAbsoluteDifferences(Tf_case.z, Tf_case.n);
    if (Of == NULL && Tf_case.n != 0) {
        free(Os);
        return 0;
    }
    int is_valid = 1;
    if (tc.n == Tf_case.n) {
        for (int i = 0; i < tc.n; i++) {
            if (Os[i] != Of[i]) {
                is_valid = 0;
                break;
            }
        }
    } else {
        is_valid = 0;
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