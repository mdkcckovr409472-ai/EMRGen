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


double* computeDividedDifference1(double x[], double y[], int n) {
    static double a[100];
    if (n <= 0) return nullptr;

    a[0] = y[0];
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < n - i; j++) {
            double denominator = x[j + i] - x[j];
            if (denominator == 0.0) {
                for (int k = 0; k < n; k++) a[k] = 0.0;
                return a;
            }
            y[j] = (y[j + 1] - y[j]) / denominator;
        }
        a[i] = y[0];
    }
    return a;
}

typedef struct {
    double* x; double* y; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){0.0}, (double[]){1.0}, 1},
    {(double[]){0.0, 1.0}, (double[]){1.0, 2.0}, 2},
    {(double[]){0.0, 1.0, 2.0}, (double[]){1.0, 4.0, 9.0}, 3},
    {(double[]){-2.0, -1.0, 0.0, 1.0, 2.0}, (double[]){4.0, 1.0, 0.0, 1.0, 4.0}, 5},
    {(double[]){1.0, 2.0, 3.0, 4.0}, (double[]){1.0, 8.0, 27.0, 64.0}, 4},
    {(double[]){0.5, 1.5, 2.5}, (double[]){0.25, 2.25, 6.25}, 3},
    {(double[]){10.0, 20.0, 30.0}, (double[]){100.0, 400.0, 900.0}, 3},
    {(double[]){-5.0, 0.0, 5.0}, (double[]){25.0, 0.0, 25.0}, 3},
    {(double[]){1.0, 2.0}, (double[]){3.0, 5.0}, 2},
    {(double[]){0.0, 0.5, 1.0}, (double[]){sin(0.0), sin(0.5), sin(1.0)}, 3},
    {(double[]){0.0, 1.0, 2.0, 3.0}, (double[]){exp(0.0), exp(1.0), exp(2.0), exp(3.0)}, 4},
    {(double[]){1.0, 4.0, 9.0}, (double[]){1.0, 2.0, 3.0}, 3},
    {(double[]){2.0, 3.0, 5.0, 7.0}, (double[]){1.0, 2.0, 3.0, 4.0}, 4},
    {(double[]){0.1, 0.2, 0.3}, (double[]){0.01, 0.04, 0.09}, 3},
    {(double[]){-1.0, 0.0, 1.0, 2.0}, (double[]){1.0, 0.0, 1.0, 4.0}, 4},
    {(double[]){100.0, 101.0, 102.0}, (double[]){10000.0, 10201.0, 10404.0}, 3},
    {(double[]){0.0, 2.0, 4.0, 6.0}, (double[]){0.0, 4.0, 16.0, 36.0}, 4},
    {(double[]){-3.0, -2.0, -1.0}, (double[]){9.0, 4.0, 1.0}, 3},
    {(double[]){1.1, 2.2, 3.3}, (double[]){1.21, 4.84, 10.89}, 3},
    {(double[]){0.0, 0.25, 0.5, 0.75, 1.0}, (double[]){0.0, 0.0625, 0.25, 0.5625, 1.0}, 5},
    {(double[]){1.0, 3.0, 5.0}, (double[]){2.0, 10.0, 26.0}, 3},
    {(double[]){-10.0, -5.0, 0.0, 5.0}, (double[]){100.0, 25.0, 0.0, 25.0}, 4},
    {(double[]){2.0, 4.0, 8.0}, (double[]){4.0, 16.0, 64.0}, 3},
    {(double[]){0.0, 1.0, 2.0, 3.0, 4.0}, (double[]){0.0, 1.0, 4.0, 9.0, 16.0}, 5},
    {(double[]){0.0, 0.2, 0.4, 0.6, 0.8, 1.0}, (double[]){0.0, 0.04, 0.16, 0.36, 0.64, 1.0}, 6},
    {(double[]){1.5, 2.5, 3.5}, (double[]){2.25, 6.25, 12.25}, 3},
    {(double[]){-2.0, 0.0, 2.0}, (double[]){4.0, 0.0, 4.0}, 3},
    {(double[]){1.0, 10.0, 100.0}, (double[]){1.0, 100.0, 10000.0}, 3},
    {(double[]){0.0, 0.1, 0.2, 0.3}, (double[]){cos(0.0), cos(0.1), cos(0.2), cos(0.3)}, 4},
    {(double[]){1.0, 2.0, 3.0, 4.0, 5.0}, (double[]){1.0, 4.0, 9.0, 16.0, 25.0}, 5}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    int n = tf.n;
    if (n > 0 && tf.x != nullptr) {
        double* new_x = new double[n];
        for (int i = 0; i < n; i++) {
            new_x[i] = tf.x[i] + 5.0;
        }
        tf.x = new_x;
    }
    return tf;
}

int check(TestCase tc) {
    double* Os = computeDividedDifference1(tc.x, tc.y, tc.n);
    if (Os == nullptr) {
        return 0;
    }

    TestCase Tf_case = change(tc);
    double* Of = computeDividedDifference1(Tf_case.x, Tf_case.y, Tf_case.n);
    if (Of == nullptr) {
        if (Tf_case.x != tc.x) {
            delete[] Tf_case.x;
        }
        return 0;
    }

    int n = tc.n;
    int is_valid = 1;
    for (int i = 0; i < n; i++) {
        if (Os[i] != Of[i]) {
            is_valid = 0;
            break;
        }
    }

    if (Tf_case.x != tc.x) {
        delete[] Tf_case.x;
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