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


double entropy(double k[], int n){
    double h = 0;
    double sum_k = 0;
    for (int i = 0; i < n; i++) {
        sum_k += (double) k[i];
    }
    for (int i = 0; i < n; i++) {
        if (k[i] != 0) {
            double p_i = (double) k[i] / sum_k;
            h += p_i * log(p_i);
        }
    }
    return -h;
}


typedef struct {
    double* k; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0, 1.0, 1.0}, 3},
    {(double[]){2.0, 2.0, 2.0, 2.0}, 4},
    {(double[]){1.0, 2.0, 3.0, 4.0}, 4},
    {(double[]){0.1, 0.2, 0.3, 0.4}, 4},
    {(double[]){10.0, 20.0, 30.0}, 3},
    {(double[]){5.0}, 1},
    {(double[]){0.5, 0.5}, 2},
    {(double[]){1.0, 0.0, 1.0}, 3},
    {(double[]){0.0, 5.0, 0.0, 5.0}, 4},
    {(double[]){100.0, 200.0, 300.0}, 3},
    {(double[]){0.25, 0.25, 0.25, 0.25}, 4},
    {(double[]){1.5, 2.5, 3.5}, 3},
    {(double[]){0.01, 0.02, 0.03}, 3},
    {(double[]){7.0, 14.0, 21.0}, 3},
    {(double[]){1.0, 1.0, 1.0, 1.0, 1.0}, 5},
    {(double[]){2.0, 4.0, 6.0, 8.0}, 4},
    {(double[]){0.0, 1.0, 0.0, 0.0}, 4},
    {(double[]){3.0, 3.0, 3.0, 3.0, 3.0}, 5},
    {(double[]){1.2, 2.4, 3.6}, 3},
    {(double[]){0.001, 0.002, 0.003}, 3},
    {(double[]){8.0, 8.0}, 2},
    {(double[]){1.0, 2.0, 1.0, 2.0}, 4},
    {(double[]){0.0, 0.0, 10.0}, 3},
    {(double[]){6.0, 12.0, 18.0, 24.0}, 4},
    {(double[]){0.75, 0.75}, 2},
    {(double[]){9.0, 18.0, 27.0}, 3},
    {(double[]){1.0, 0.0, 0.0, 1.0}, 4},
    {(double[]){4.0, 4.0, 4.0, 4.0, 4.0}, 5},
    {(double[]){0.15, 0.25, 0.35, 0.25}, 4},
    {(double[]){20.0, 40.0, 60.0}, 3}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    if (tf.n > 1) {
        double* new_k = new double[tf.n];
        for (int i = 0; i < tf.n - 1; i++) {
            new_k[i] = tc.k[i + 1];
        }
        new_k[tf.n - 1] = tc.k[0];
        tf.k = new_k;
    }
    return tf;
}

int check(TestCase tc) {
    double Os = entropy(tc.k, tc.n);
    TestCase Tf_case = change(tc);
    double Of = entropy(Tf_case.k, Tf_case.n);
    int is_valid = 0;
    if (fabs(Os - Of) < 1e-12) {
        is_valid = 1;
    }
    if (Tf_case.k != tc.k) {
        delete[] Tf_case.k;
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