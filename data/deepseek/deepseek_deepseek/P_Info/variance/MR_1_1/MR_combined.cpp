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
    {(double[]){1.5, 2.5, 3.5}, 3},
    {(double[]){-2.1, 0.0, 4.3, -1.2}, 4},
    {(double[]){10.7}, 1},
    {(double[]){0.3, -0.3, 0.3, -0.3, 0.3}, 5},
    {(double[]){100.25, 200.75, 150.5}, 3},
    {(double[]){-8.9, 12.4, -5.6, 7.1, -3.3}, 5},
    {(double[]){1.1, 2.2, 3.3, 4.4, 5.5, 6.6}, 6},
    {(double[]){-15.0, 25.0, -35.0, 45.0}, 4},
    {(double[]){0.001, 0.002, 0.003}, 3},
    {(double[]){7.0}, 1},
    {(double[]){-1.5, -2.5, -3.5, -4.5}, 4},
    {(double[]){12.34, 56.78, 90.12}, 3},
    {(double[]){0.0, 0.0, 0.0, 0.0, 0.0}, 5},
    {(double[]){2.718, 3.142, 1.618}, 3},
    {(double[]){-100.1, 50.2, 75.3, -25.4}, 4},
    {(double[]){9.8, 7.6, 5.4, 3.2, 1.0}, 5},
    {(double[]){42.0}, 1},
    {(double[]){-6.6, 8.8, -10.1, 12.12, -14.14}, 5},
    {(double[]){0.5, 1.0, 1.5, 2.0, 2.5, 3.0, 3.5}, 7},
    {(double[]){-9.99, 18.18, -27.27}, 3},
    {(double[]){11.11, 22.22, 33.33, 44.44, 55.55}, 5},
    {(double[]){0.25, -0.75, 1.25, -1.75}, 4},
    {(double[]){6.02, 23.0, 1.38}, 3},
    {(double[]){-50.5, 30.3, -20.2, 10.1, 0.0}, 5},
    {(double[]){1.0, 4.0, 9.0, 16.0, 25.0}, 5},
    {(double[]){-7.3, 2.8, -4.1, 5.6, -0.9, 3.2}, 6},
    {(double[]){13.7, 29.4}, 2},
    {(double[]){0.0, -0.0}, 2},
    {(double[]){8.0, 15.0, 23.0, 31.0}, 4},
    {(double[]){-2.22, 3.33, -4.44, 5.55, -6.66}, 5}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    double k = 5.0; // 常数k，可以根据需要调整
    if (tf.x != nullptr && tf.n > 0) {
        double* new_x = new double[tf.n];
        for (int i = 0; i < tf.n; i++) {
            new_x[i] = tf.x[i] + k;
        }
        tf.x = new_x;
    }
    return tf;
}

int check(TestCase tc) {
    double Os = variance(tc.x, tc.n);
    TestCase Tf_case = change(tc);
    double Of = variance(Tf_case.x, Tf_case.n);
    int is_valid = 0;
    const double epsilon = 1e-9;
    if (fabs(Os - Of) < epsilon) {
        is_valid = 1;
    }
    if (Tf_case.x != tc.x && Tf_case.x != nullptr) {
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