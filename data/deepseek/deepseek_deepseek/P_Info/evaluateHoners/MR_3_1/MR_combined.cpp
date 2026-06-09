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


double evaluateHoners(double coefficients[], double argument, int n) {
    
    double result = coefficients[n - 1];
    for (int j = n - 2; j >= 0; j--) {
        result = argument * result + coefficients[j];
    }
    return result;
}


typedef struct {
    double* coefficients; double argument; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0}, 2.0, 1},
    {(double[]){2.0, 1.0}, 3.0, 2},
    {(double[]){1.0, 2.0, 3.0}, 4.0, 3},
    {(double[]){-1.0, 0.0, 1.0}, 5.0, 3},
    {(double[]){0.5, -0.5, 1.5}, 0.0, 3},
    {(double[]){10.0, 20.0, 30.0, 40.0}, 1.0, 4},
    {(double[]){-2.0, -3.0, -4.0}, -1.0, 3},
    {(double[]){1.1, 2.2, 3.3}, 1.1, 3},
    {(double[]){0.0, 0.0, 0.0}, 100.0, 3},
    {(double[]){5.0}, 0.0, 1},
    {(double[]){-10.0, 20.0, -30.0, 40.0}, 2.0, 4},
    {(double[]){0.25, 0.5, 0.75, 1.0, 1.25}, 4.0, 5},
    {(double[]){1.0, -1.0, 1.0, -1.0}, 1.0, 4},
    {(double[]){3.14, 2.71}, 1.618, 2},
    {(double[]){100.0, 200.0, 300.0}, 0.5, 3},
    {(double[]){-1.5, 2.0, -2.5, 3.0}, -2.0, 4},
    {(double[]){7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0}, 1.0, 7},
    {(double[]){0.1, 0.2, 0.3, 0.4, 0.5}, 10.0, 5},
    {(double[]){-0.1, -0.2, -0.3}, -10.0, 3},
    {(double[]){2.0, 4.0, 6.0, 8.0}, 0.25, 4},
    {(double[]){9.0, 8.0, 7.0}, 1.5, 3},
    {(double[]){1.0, 0.0, 0.0, 0.0, 1.0}, 2.0, 5},
    {(double[]){-5.0, 10.0, -15.0}, 3.0, 3},
    {(double[]){0.0, 1.0, 0.0, 1.0}, -1.0, 4},
    {(double[]){6.0, 12.0, 18.0}, 0.333333, 3},
    {(double[]){2.5, 5.0, 7.5}, 2.0, 3},
    {(double[]){1.0, 2.0, 3.0, 4.0, 5.0, 6.0}, -2.0, 6},
    {(double[]){8.0, 4.0, 2.0, 1.0}, 0.5, 4},
    {(double[]){-1.0, -2.0, -3.0, -4.0}, -0.5, 4},
    {(double[]){15.0, 30.0, 45.0}, 1.0, 3}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    double* new_coeffs = new double[tf.n];
    for (int i = 0; i < tf.n; ++i) {
        new_coeffs[i] = tf.coefficients[i] * 2.0;
    }
    tf.coefficients = new_coeffs;
    return tf;
}

int check(TestCase tc) {
    double Os = evaluateHoners(tc.coefficients, tc.argument, tc.n);
    TestCase Tf_case = change(tc);
    double Of = evaluateHoners(Tf_case.coefficients, Tf_case.argument, Tf_case.n);
    int is_valid = 0;
    if (std::abs(Of - (2.0 * Os)) < 1e-9) {
        is_valid = 1;
    }
    delete[] Tf_case.coefficients;
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