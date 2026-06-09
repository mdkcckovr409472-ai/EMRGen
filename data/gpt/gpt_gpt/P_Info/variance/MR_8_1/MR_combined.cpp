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


double variance(double x[], int n) {
    double sum = 0;
    double sum1 = 0;
    double var = 0;
    double avrg = 0;
    for(int i = 0; i < n; i++) {
        sum = sum + x[i];
    }
    
    avrg = sum / (double)n;
    for (int i = 0; i < n; i++) {
        sum1 = sum1 + (x[i] - avrg) * (x[i] - avrg);
    }
    var = sum1 / (double) n;
    return var;
}


typedef struct {
    double* x; int n;
} TestCase;

TestCase test_cases[] = {
    { (double[]){0.0, 0.0, 0.0}, 3 },
    { (double[]){5.5}, 1 },
    { (double[]){2.2, 2.2}, 2 },
    { (double[]){-1.0, 2.0, -3.0, 4.0}, 4 },
    { (double[]){0.1, 0.2, 0.3, 0.4, 0.5}, 5 },
    { (double[]){-50.0, -20.0, -30.0}, 3 },
    { (double[]){3.5, -2.1, 7.8, 0.0, -5.5}, 5 },
    { (double[]){1.0, -1.0, 1.0, -1.0}, 4 },
    { (double[]){10.0, 10.0, 10.0, 10.0}, 4 },
    { (double[]){0.0, 5.0, 0.0, 5.0}, 4 },
    { (double[]){1.0, 2.0, 2.0, 3.0}, 4 },
    { (double[]){5.0, 4.0, 4.0, 3.0}, 4 },
    { (double[]){-3.3, 4.4, -1.1, 2.2, 0.0, 5.5, -2.2, 3.3}, 8 },
    { (double[]){9.9, -9.9, 8.8, -8.8, 7.7, -7.7, 6.6, -6.6, 0.0}, 9 },
    { (double[]){0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09, 0.10}, 10 },
    { (double[]){99.9, 80.0, 70.5, 60.2, 50.1, 40.0}, 6 },
    { (double[]){1.0, 2.5, -3.75}, 3 },
    { (double[]){-10.0, 20.0, -30.0, 40.0, -50.0}, 5 },
    { (double[]){1e-6, -1e-6, 2e-6, -2e-6}, 4 },
    { (double[]){5.5, -4.4, 3.3, -2.2, 1.1, 0.0, -0.5}, 7 },
    { (double[]){0.0, 3.14}, 2 },
    { (double[]){-7.0, -7.0, -7.0}, 3 },
    { (double[]){1.0, 2.0, 3.0, 2.0, 1.0}, 5 },
    { (double[]){-99.9, 0.0, 99.9, -50.5, 50.5, -0.1}, 6 },
    { (double[]){2.5, 2.0, 2.5, 2.0}, 4 },
    { (double[]){0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0}, 9 },
    { (double[]){100.0, 101.0, 99.5, 100.5, 100.2}, 5 },
    { (double[]){0.333, 0.666, 0.999}, 3 },
    { (double[]){-0.1, -0.2, -0.3, -0.4, -0.5, -0.6, -0.7, -0.8}, 8 },
    { (double[]){0.0, 50.0, -50.0, 25.0, -25.0, 0.0}, 6 }
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    if (tc.n > 1) {
        double* shifted = new double[tc.n];
        shifted[0] = tc.x[tc.n - 1];
        for (int i = 1; i < tc.n; i++) {
            shifted[i] = tc.x[i - 1];
        }
        tf.x = shifted;
    } else {
        // No shift needed if array size <= 1
        tf.x = tc.x;
    }
    return tf;
}

int check(TestCase tc) {
    double Os = variance(tc.x, tc.n);
    TestCase Tf_case = change(tc);
    double Of = variance(Tf_case.x, Tf_case.n);
    int is_valid = 0;
    // Check if Os == Of exactly since shift should not affect variance
    if (Os == Of) {
        is_valid = 1;
    }
    // Free dynamically allocated memory in Tf_case if any
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