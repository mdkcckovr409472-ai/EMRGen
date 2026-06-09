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


double* ebeMultiply(double a[], double b[], int n1, int n2) {
    if (n1 != n2) {
        return NULL;  
    }

    double* result = (double*)malloc(n1 * sizeof(double));
    if (result == NULL) {
        return NULL;  
    }

    for (int i = 0; i < n1; i++) {
        result[i] = a[i] * b[i];  
    }

    return result;  
}


typedef struct {
    double* a; double* b; int n1; int n2;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0, 2.0, 3.0}, (double[]){4.0, 5.0, 6.0}, 3, 3},
    {(double[]){0.0, 0.0}, (double[]){0.0, 0.0}, 2, 2},
    {(double[]){-1.5, 2.5}, (double[]){2.0, -4.0}, 2, 2},
    {(double[]){10.0}, (double[]){-2.0}, 1, 1},
    {(double[]){0.5, 1.5, 2.5}, (double[]){2.0, 2.0, 2.0}, 3, 3},
    {(double[]){-2.0, -3.0, -4.0}, (double[]){-1.0, -2.0, -3.0}, 3, 3},
    {(double[]){1.1, 2.2}, (double[]){10.0, 20.0}, 2, 2},
    {(double[]){100.0, 200.0, 300.0}, (double[]){0.1, 0.2, 0.3}, 3, 3},
    {(double[]){3.14159, 2.71828}, (double[]){1.0, 1.0}, 2, 2},
    {(double[]){1.0, 2.0, 3.0, 4.0}, (double[]){5.0, 6.0, 7.0, 8.0}, 4, 4},
    {(double[]){-10.5, 20.5}, (double[]){2.0, 0.5}, 2, 2},
    {(double[]){0.0, 1.0, 0.0}, (double[]){5.0, 0.0, 5.0}, 3, 3},
    {(double[]){2.5}, (double[]){4.0}, 1, 1},
    {(double[]){1.0, 0.0, -1.0}, (double[]){-1.0, 0.0, 1.0}, 3, 3},
    {(double[]){1.2, 3.4, 5.6}, (double[]){7.8, 9.0, 1.2}, 3, 3},
    {(double[]){}, (double[]){}, 0, 0},
    {(double[]){1.0, 2.0}, (double[]){3.0, 4.0}, 2, 2},
    {(double[]){-0.1, -0.2, -0.3}, (double[]){10.0, 20.0, 30.0}, 3, 3},
    {(double[]){999.999, 888.888}, (double[]){1.001, 2.002}, 2, 2},
    {(double[]){1.0, 2.0, 3.0, 4.0, 5.0}, (double[]){-1.0, -2.0, -3.0, -4.0, -5.0}, 5, 5},
    {(double[]){0.25, 0.5, 0.75}, (double[]){4.0, 2.0, 1.33333}, 3, 3},
    {(double[]){12.34, 56.78}, (double[]){9.87, 6.54}, 2, 2},
    {(double[]){1.0}, (double[]){0.0}, 1, 1},
    {(double[]){2.0, 4.0, 8.0}, (double[]){0.5, 0.25, 0.125}, 3, 3},
    {(double[]){-100.0, 50.0, -25.0}, (double[]){2.0, -2.0, 4.0}, 3, 3},
    {(double[]){1.5}, (double[]){-2.0}, 1, 1},
    {(double[]){1.0, 1.0, 1.0, 1.0}, (double[]){2.0, 3.0, 4.0, 5.0}, 4, 4},
    {(double[]){7.0, 8.0, 9.0}, (double[]){10.0, 11.0, 12.0}, 3, 3},
    {(double[]){0.0, 0.0, 0.0, 0.0}, (double[]){1.0, 2.0, 3.0, 4.0}, 4, 4},
    {(double[]){1.0, 2.0, 3.0}, (double[]){1.0, 0.5, 0.333333}, 3, 3}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    if (tf.b != NULL && tf.n1 > 0) {
        for (int i = 0; i < tf.n1; i++) {
            tf.b[i] = -tf.b[i];
        }
    }
    return tf;
}

int check(TestCase tc) {
    double* Os = ebeMultiply(tc.a, tc.b, tc.n1, tc.n2);
    if (Os == NULL) {
        return 0;
    }

    TestCase Tf_case = change(tc);
    double* Of = ebeMultiply(Tf_case.a, Tf_case.b, Tf_case.n1, Tf_case.n2);
    if (Of == NULL) {
        free(Os);
        return 0;
    }

    int is_valid = 1;
    if (tc.n1 > 0) {
        for (int i = 0; i < tc.n1; i++) {
            if (fabs(-Os[i] - Of[i]) > 1e-9) {
                is_valid = 0;
                break;
            }
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