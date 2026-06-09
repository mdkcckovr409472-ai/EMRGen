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


double meanDifference(double sample1[], double sample2[], int n ) {
    double sumDifference = 0;
    for (int i = 0; i < n; i++) {
        sumDifference += sample1[i] - sample2[i];
    }
    return sumDifference / n;
}


typedef struct {
    double* sample1; double* sample2; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0, 2.0, 3.0}, (double[]){4.0, 5.0, 6.0}, 3},
    {(double[]){0.0, 0.0, 0.0}, (double[]){0.0, 0.0, 0.0}, 3},
    {(double[]){-1.5, -2.5}, (double[]){1.5, 2.5}, 2},
    {(double[]){10.2, 20.4, 30.6}, (double[]){5.1, 10.2, 15.3}, 3},
    {(double[]){1.0}, (double[]){1.0}, 1},
    {(double[]){100.0, 200.0, 300.0, 400.0}, (double[]){50.0, 150.0, 250.0, 350.0}, 4},
    {(double[]){2.5, 3.5}, (double[]){7.5, 6.5}, 2},
    {(double[]){-10.0, -20.0, -30.0}, (double[]){-5.0, -10.0, -15.0}, 3},
    {(double[]){0.1, 0.2, 0.3}, (double[]){0.3, 0.2, 0.1}, 3},
    {(double[]){1.1, 2.2, 3.3, 4.4, 5.5}, (double[]){5.5, 4.4, 3.3, 2.2, 1.1}, 5},
    {(double[]){8.0, 6.0, 4.0}, (double[]){2.0, 4.0, 6.0}, 3},
    {(double[]){15.0, 25.0, 35.0}, (double[]){15.0, 25.0, 35.0}, 3},
    {(double[]){12.34, 45.67}, (double[]){98.76, 54.32}, 2},
    {(double[]){7.0}, (double[]){3.0}, 1},
    {(double[]){1.0, 3.0, 5.0, 7.0, 9.0}, (double[]){2.0, 4.0, 6.0, 8.0, 10.0}, 5},
    {(double[]){-2.0, -4.0, -6.0}, (double[]){-1.0, -3.0, -5.0}, 3},
    {(double[]){0.5, 1.5, 2.5, 3.5}, (double[]){3.5, 2.5, 1.5, 0.5}, 4},
    {(double[]){1000.0, 2000.0}, (double[]){500.0, 1500.0}, 2},
    {(double[]){9.9, 8.8, 7.7}, (double[]){1.1, 2.2, 3.3}, 3},
    {(double[]){6.0, 12.0, 18.0, 24.0}, (double[]){3.0, 6.0, 9.0, 12.0}, 4},
    {(double[]){-7.5, 7.5}, (double[]){7.5, -7.5}, 2},
    {(double[]){1.2, 3.4, 5.6}, (double[]){1.2, 3.4, 5.6}, 3},
    {(double[]){22.0, 33.0, 44.0}, (double[]){11.0, 22.0, 33.0}, 3},
    {(double[]){0.01, 0.02}, (double[]){0.02, 0.01}, 2},
    {(double[]){50.0, 60.0, 70.0, 80.0, 90.0}, (double[]){55.0, 65.0, 75.0, 85.0, 95.0}, 5},
    {(double[]){4.0, 8.0, 12.0}, (double[]){1.0, 2.0, 3.0}, 3},
    {(double[]){-100.0, 100.0}, (double[]){0.0, 0.0}, 2},
    {(double[]){1.0, 2.0, 3.0, 4.0, 5.0, 6.0}, (double[]){6.0, 5.0, 4.0, 3.0, 2.0, 1.0}, 6},
    {(double[]){2.0, 4.0, 8.0}, (double[]){1.0, 2.0, 4.0}, 3}
};
int num_test_cases = 29;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    double k = 5.0; // 任意常数 k
    if (tf.sample2 != nullptr && tf.n > 0) {
        double* new_sample2 = new double[tf.n];
        for (int i = 0; i < tf.n; i++) {
            new_sample2[i] = tf.sample2[i] + k;
        }
        tf.sample2 = new_sample2;
    }
    return tf;
}

int check(TestCase tc) {
    double Os = meanDifference(tc.sample1, tc.sample2, tc.n);
    TestCase Tf_case = change(tc);
    double Of = meanDifference(Tf_case.sample1, Tf_case.sample2, Tf_case.n);
    double k = 5.0;
    int is_valid = 0;
    if (fabs((Os - k) - Of) < 1e-9) {
        is_valid = 1;
    }
    if (Tf_case.sample2 != nullptr && Tf_case.sample2 != tc.sample2) {
        delete[] Tf_case.sample2;
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