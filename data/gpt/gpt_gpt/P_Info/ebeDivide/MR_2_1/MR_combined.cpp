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
    {(double[]){10.5, -3.2, 1000.0}, (double[]){2.0, 4.0, -50.0}, 3, 3},
    {(double[]){-25.0, 300.5, 7.7, 82.1}, (double[]){5.0, -150.2, 0.5, 9.1}, 4, 4},
    {(double[]){123.45, 0.001, 5000.0, -1000.0}, (double[]){-1.5, 200.0, 2.5, -2.5}, 4, 4},
    {(double[]){-900.0, 707.1, 8000.0}, (double[]){0.1, -70.7, 400.0}, 3, 3},
    {(double[]){3.14, -2.71, 1.618}, (double[]){1.0, 0.1, -0.5}, 3, 3},
    {(double[]){250.0, -20.3, 760.0, -880.0}, (double[]){2.5, 2.0, -4.0, 8.0}, 4, 4},
    {(double[]){5.5, 0.0001, -700.0}, (double[]){1.1, 0.0002, -350.0}, 3, 3},
    {(double[]){600.0, -50.0, 0.25, 192.0}, (double[]){-3.0, 25.0, 0.5, -96.0}, 4, 4},
    {(double[]){18.0, 0.12, -900.0, 720.0}, (double[]){6.0, 0.03, -300.0, 360.0}, 4, 4},
    {(double[]){1000.0, 500.0, 250.0}, (double[]){10.0, 5.0, 2.5}, 3, 3},
    {(double[]){-45.0, 33.3, -25.5, 14.5}, (double[]){-5.0, 3.7, -2.5, 1.0}, 4, 4},
    {(double[]){0.5, 150.0, -0.75}, (double[]){0.25, 50.0, -0.25}, 3, 3},
    {(double[]){55.4, -123.7, 88.9}, (double[]){2.0, -41.23, 44.45}, 3, 3},
    {(double[]){12.0, -240.0}, (double[]){4.0, 60.0}, 2, 2},
    {(double[]){5.0, 5.0, 5.0, 5.0}, (double[]){1.0, 2.0, 5.0, 10.0}, 4, 4},
    {(double[]){111.0, -222.0, 333.0}, (double[]){3.0, -6.0, 11.0}, 3, 3},
    {(double[]){77.7, -88.8, 99.9}, (double[]){7.7, -8.8, 9.9}, 3, 3},
    {(double[]){9000.0, 8000.0, 7000.0}, (double[]){3000.0, 4000.0, 5000.0}, 3, 3},
    {(double[]){6.28, -3.14, 1.57}, (double[]){2.0, -1.0, 0.5}, 3, 3},
    {(double[]){0.33, 1.44, -2.55}, (double[]){0.11, 0.48, -0.85}, 3, 3},
    {(double[]){150.0, -450.0, 900.0}, (double[]){50.0, -150.0, 300.0}, 3, 3},
    {(double[]){3.0, -9.0, 12.0, -15.0}, (double[]){1.0, -3.0, 4.0, -5.0}, 4, 4},
    {(double[]){500.5, -400.4, 300.3}, (double[]){25.0, -20.0, 15.0}, 3, 3},
    {(double[]){999.9, -888.8, 777.7}, (double[]){9.999, -8.888, 7.777}, 3, 3},
    {(double[]){4.0, 16.0, 64.0, 256.0}, (double[]){2.0, 4.0, 8.0, 16.0}, 4, 4},
    {(double[]){27.0, -9.0, 3.0, -1.0}, (double[]){9.0, -3.0, 1.0, -0.5}, 4, 4},
    {(double[]){1234.5, -6789.0, 5432.1}, (double[]){123.45, -678.9, 543.21}, 3, 3},
    {(double[]){7.0, 14.0, 21.0}, (double[]){1.0, 7.0, 3.0}, 3, 3},
    {(double[]){19.0, -38.0, 57.0, -76.0}, (double[]){1.9, -3.8, 5.7, -7.6}, 4, 4}
};
int num_test_cases = 29;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    if (tf.n1 > 0) {
        double* new_a = (double*)malloc(tf.n1 * sizeof(double));
        if (new_a == NULL) {
            tf.a = NULL; 
            return tf;
        }
        for (int i = 0; i < tf.n1; i++) {
            new_a[i] = tf.a[i] - 1.0;
        }
        tf.a = new_a;
    }
    return tf;
}

int check(TestCase tc) {
    double* Os = ebeDivide(tc.a, tc.b, tc.n1, tc.n2);
    if (Os == NULL) {
        return 0;
    }

    TestCase Tf_case = change(tc);
    if (Tf_case.a == NULL && tc.n1 > 0) {
        free(Os);
        return 0;
    }

    double* Of = ebeDivide(Tf_case.a, Tf_case.b, Tf_case.n1, Tf_case.n2);
    
    int is_valid = 1;
    if (Of == NULL) {
        is_valid = 0;
    } else {
        for (int i = 0; i < tc.n1; i++) {
            if (tc.b[i] == 0.0) {
                if (Of[i] != INFINITY) {
                    is_valid = 0;
                    break;
                }
            } else {
                double expected = Os[i] - 1.0 / tc.b[i];
                if (!( (Of[i] == expected) || (std::abs(Of[i] - expected) < 1e-12) )) {
                    is_valid = 0;
                    break;
                }
            }
        }
    }

    free(Os);
    if (Tf_case.a != tc.a) {
        free(Tf_case.a);
    }
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