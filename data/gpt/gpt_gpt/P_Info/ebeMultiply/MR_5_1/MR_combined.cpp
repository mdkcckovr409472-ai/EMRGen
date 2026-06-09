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
    {(double[]){1.5, -20.0, 3.14}, (double[]){2.0, 4.5, -0.5}, 3, 3},
    {(double[]){100.0, 500.5, -300.0, 1.1}, (double[]){-2.0, 1000.2, 0.25, -1.5}, 4, 4},
    {(double[]){42.42, -150.0, 600.6, 0.001, 999.99}, (double[]){-100.0, 0.1, -300.0, 4000.0, 0.5}, 5, 5},
    {(double[]){3.0, 7.7, 100.0, 2000.0}, (double[]){1.5, -2.2, 300.3, -1000.0}, 4, 4},
    {(double[]){999.99, 45.67, -12.0, 500.1, 0.5, -100.0}, (double[]){0.1, -0.2, 300.0, 1200.0, 2000.0, 3.1415}, 6, 6},
    {(double[]){33.33, -44.44, 55.55}, (double[]){66.66, 77.77, -88.88}, 3, 3},
    {(double[]){1000.0, 2000.0, 3000.0, 4000.0}, (double[]){-1.0, -2.0, -3.0, -4.0}, 4, 4},
    {(double[]){0.25, 0.5, 0.75, 1.0}, (double[]){10.0, 20.0, 30.0, 40.0}, 4, 4},
    {(double[]){-500.0, 250.0, 125.0}, (double[]){-2.0, 4.0, -6.0}, 3, 3},
    {(double[]){123.4, 234.5, -345.6}, (double[]){-456.7, 567.8, 678.9}, 3, 3},
    {(double[]){7.7, 8.8, 9.9, 10.10, 11.11}, (double[]){1.1, -2.2, 3.3, -4.4, 5.5}, 5, 5},
    {(double[]){200.0, 300.0, 400.0}, (double[]){-1.5, 2.5, -3.5}, 3, 3},
    {(double[]){0.0, 1.1, -1.1, 2.2, -2.2}, (double[]){3.3, -3.3, 4.4, -4.4, 5.5}, 5, 5},
    {(double[]){12.34, 56.78, 90.12}, (double[]){-21.43, 65.87, -91.21}, 3, 3},
    {(double[]){7.0, -14.0, 28.0, -56.0}, (double[]){-1.0, 2.0, -4.0, 8.0}, 4, 4},
    {(double[]){11.0, 22.0, 33.0, 44.0}, (double[]){-55.0, 66.0, -77.0, 88.0}, 4, 4},
    {(double[]){130.5, -260.1, 520.2, -1040.4}, (double[]){2.0, -4.0, 8.0, -16.0}, 4, 4},
    {(double[]){99.9, 88.8, 77.7, 66.6}, (double[]){-55.5, -44.4, -33.3, -22.2}, 4, 4},
    {(double[]){5.5, -5.5, 10.1, -10.1}, (double[]){-20.2, 20.2, -30.3, 30.3}, 4, 4},
    {(double[]){1000.0, -2000.0, 3000.0, -4000.0}, (double[]){5000.0, -6000.0, 7000.0, -8000.0}, 4, 4},
    {(double[]){123.0, 234.0, 345.0, 456.0, 567.0}, (double[]){-321.0, -432.0, -543.0, -654.0, -765.0}, 5, 5},
    {(double[]){1.23, -2.34, 3.45, -4.56}, (double[]){5.67, -6.78, 7.89, -8.90}, 4, 4},
    {(double[]){-300.3, 400.4, -500.5}, (double[]){600.6, -700.7, 800.8}, 3, 3},
    {(double[]){-999.9, 888.8, -777.7, 666.6}, (double[]){555.5, -444.4, 333.3, -222.2}, 4, 4},
    {(double[]){7.1, 8.2, 9.3}, (double[]){-9.1, -8.2, -7.3}, 3, 3},
    {(double[]){50.0, 60.0, 70.0}, (double[]){-10.0, -20.0, -30.0}, 3, 3},
    {(double[]){-1.1, 2.2, -3.3, 4.4}, (double[]){5.5, -6.6, 7.7, -8.8}, 4, 4},
    {(double[]){25.25, -50.50, 75.75}, (double[]){-100.1, 125.125, -150.15}, 3, 3},
    {(double[]){999.1, -888.2, 777.3, -666.4, 555.5}, (double[]){-444.6, 333.7, -222.8, 111.9, -0.1}, 5, 5}
};
int num_test_cases = 29;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    if (tf.a != NULL && tf.n1 > 0) {
        double* new_a = (double*)malloc(tf.n1 * sizeof(double));
        if (new_a == NULL) {
            // If malloc fails, return original tc without change (to avoid crash)
            return tf;
        }
        for (int i = 0; i < tf.n1; i++) {
            new_a[i] = tf.a[i];
        }
        new_a[0] = std::numeric_limits<double>::max();
        tf.a = new_a;
    }
    return tf;
}

int check(TestCase tc) {
    if (tc.a == NULL || tc.b == NULL || tc.n1 != tc.n2) {
        return 0;
    }
    double* Os = ebeMultiply(tc.a, tc.b, tc.n1, tc.n2);
    if (Os == NULL) {
        return 0;
    }
    TestCase Tf_case = change(tc);
    if (Tf_case.a == NULL || Tf_case.b == NULL || Tf_case.n1 != Tf_case.n2) {
        free(Os);
        return 0;
    }
    double* Of = ebeMultiply(Tf_case.a, Tf_case.b, Tf_case.n1, Tf_case.n2);
    if (Of == NULL) {
        free(Os);
        if (Tf_case.a != tc.a) free(Tf_case.a);
        return 0;
    }
    int is_valid = 1;
    if (Tf_case.n1 > 0) {
        if (Of[0] != std::numeric_limits<double>::max() * Tf_case.b[0]) {
            is_valid = 0;
        }
    }
    for (int i = 1; i < tc.n1 && is_valid; i++) {
        if (Of[i] != Os[i]) {
            is_valid = 0;
            break;
        }
    }
    free(Os);
    free(Of);
    if (Tf_case.a != tc.a) {
        free(Tf_case.a);
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