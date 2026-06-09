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


double* ebeDivide(double a[], double b[], int n1, int n2) {
    if (n1 != n2) {
        return NULL;  
    }

    double* result = (double*)malloc(n1 * sizeof(double));
    if (result == NULL) {
        return NULL;  
    }

    for (int i = 0; i < n1; i++) {
        if (b[i] == 0.0) {
            result[i] = INFINITY;  
        } else {
            result[i] = a[i] / b[i];
        }
    }

    return result;  
}


typedef struct {
    double* a; double* b; int n1; int n2;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0, 2.0, 3.0}, (double[]){4.0, 5.0, 6.0}, 3, 3},
    {(double[]){10.0, 20.0}, (double[]){2.0, 4.0}, 2, 2},
    {(double[]){0.0, 0.0, 0.0}, (double[]){1.0, 2.0, 3.0}, 3, 3},
    {(double[]){-1.0, -2.0, -3.0}, (double[]){1.0, 2.0, 3.0}, 3, 3},
    {(double[]){1.5, 2.5}, (double[]){0.5, 0.5}, 2, 2},
    {(double[]){100.0, 200.0, 300.0}, (double[]){100.0, 200.0, 300.0}, 3, 3},
    {(double[]){1.0}, (double[]){1.0}, 1, 1},
    {(double[]){1.0, 2.0, 3.0, 4.0}, (double[]){0.1, 0.2, 0.3, 0.4}, 4, 4},
    {(double[]){-10.0, 20.0, -30.0}, (double[]){5.0, -4.0, 6.0}, 3, 3},
    {(double[]){0.0}, (double[]){5.0}, 1, 1},
    {(double[]){1.0, 2.0, 3.0}, (double[]){1.0, 0.0, 3.0}, 3, 3},
    {(double[]){2.0, 4.0, 6.0, 8.0}, (double[]){2.0, 2.0, 2.0, 2.0}, 4, 4},
    {(double[]){1.0, 1.0, 1.0, 1.0, 1.0}, (double[]){2.0, 2.0, 2.0, 2.0, 2.0}, 5, 5},
    {(double[]){3.14, 2.71}, (double[]){1.0, 1.0}, 2, 2},
    {(double[]){1.0, 2.0}, (double[]){-1.0, -2.0}, 2, 2},
    {(double[]){0.5, 1.5, 2.5}, (double[]){2.0, 3.0, 5.0}, 3, 3},
    {(double[]){10.0}, (double[]){3.0}, 1, 1},
    {(double[]){1.0, 2.0, 3.0, 4.0, 5.0}, (double[]){5.0, 4.0, 3.0, 2.0, 1.0}, 5, 5},
    {(double[]){1000.0, 2000.0}, (double[]){500.0, 1000.0}, 2, 2},
    {(double[]){0.0, 0.0}, (double[]){1.0, -1.0}, 2, 2},
    {(double[]){-1.0, -1.0, -1.0}, (double[]){-1.0, -1.0, -1.0}, 3, 3},
    {(double[]){2.0, 4.0, 8.0}, (double[]){1.0, 2.0, 4.0}, 3, 3},
    {(double[]){9.0, 16.0, 25.0}, (double[]){3.0, 4.0, 5.0}, 3, 3},
    {(double[]){1.1, 2.2}, (double[]){1.1, 2.2}, 2, 2},
    {(double[]){7.0, 14.0, 21.0}, (double[]){7.0, 7.0, 7.0}, 3, 3},
    {(double[]){0.001, 0.002}, (double[]){0.001, 0.002}, 2, 2},
    {(double[]){1.0, 2.0, 3.0}, (double[]){0.0, 0.0, 0.0}, 3, 3},
    {(double[]){5.0, 10.0, 15.0, 20.0}, (double[]){1.0, 2.0, 3.0, 4.0}, 4, 4},
    {(double[]){12.0, 24.0}, (double[]){6.0, 8.0}, 2, 2},
    {(double[]){1.0, 3.0, 5.0, 7.0, 9.0}, (double[]){2.0, 2.0, 2.0, 2.0, 2.0}, 5, 5}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    if (tf.b != NULL && tf.n2 > 0) {
        for (int i = 0; i < tf.n2; i++) {
            tf.b[i] *= -1.0;
        }
    }
    return tf;
}

int check(TestCase tc) {
    double* Os = ebeDivide(tc.a, tc.b, tc.n1, tc.n2);
    if (Os == NULL) {
        return 0;
    }

    TestCase Tf_case = change(tc);
    double* Of = ebeDivide(Tf_case.a, Tf_case.b, Tf_case.n1, Tf_case.n2);
    if (Of == NULL) {
        free(Os);
        return 0;
    }

    int is_valid = 1;
    int n = tc.n1;
    for (int i = 0; i < n; i++) {
        if (Os[i] == INFINITY && Of[i] == INFINITY) {
            continue;
        }
        if (fabs(-1.0 * Os[i] - Of[i]) > 1e-12) {
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