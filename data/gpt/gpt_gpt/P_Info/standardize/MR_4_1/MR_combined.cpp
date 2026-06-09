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


double* standardize(double data[], int n) {
    double* cp1 = (double*)malloc(n * sizeof(double));
    memcpy(cp1,data,n*sizeof(double));
    double sum = 0;
    double sumSq = 0;
    for (int i = 0; i < n; i++) {
        sum += cp1[i];
        sumSq += cp1[i] * cp1[i];
    }
    double mean = sum / n;
    double sd = sqrt((sumSq - mean * sum) / n);
    for (int i = 0; i < n; i++) {
        cp1[i] = (cp1[i] - mean) / sd;
    }
    return cp1;
}


typedef struct {
    double* data; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.5, -2.3, 42.0, 100.5, -150.2}, 5},
    {(double[]){-1000.0, 300.5, 215.4, -999.9, 67.3, 0.5}, 6},
    {(double[]){23.4, 0.001, -0.002, 345.6, 12.3}, 5},
    {(double[]){2500.0, -1200.5, 300.1, 70.3, 19.9, -400.2}, 6},
    {(double[]){5.5, -5.5, 10.1, -10.1, 100.0}, 5},
    {(double[]){102.4, 1500.3, -320.5, 4000.0, -29.7}, 5},
    {(double[]){-23.5, 0.0, 1.2, 20.3, 500.5}, 5},
    {(double[]){15.0, 42.1, -50.5, 260.0, 700.7}, 5},
    {(double[]){333.3, -333.3, 1000.0, -1000.0, 0.0}, 5},
    {(double[]){55.5, 65.5, 75.5, 85.5, 95.5}, 5},
    {(double[]){-100.0, -2000.0, 3000.0, -4000.0, 5000.0}, 5},
    {(double[]){1.1, 2.2, 3.3, 4.4, 5.5, 6.6}, 6},
    {(double[]){-10.0, 0.0, 10.0, 20.0, -20.0, 100.0}, 6},
    {(double[]){7.7, -7.7, 77.7, -77.7, 777.7}, 5},
    {(double[]){0.123, 456.789, -987.654, 321.123, -123.321}, 5},
    {(double[]){200.0, 300.0, 400.0, 500.0, 600.0, 700.0}, 6},
    {(double[]){-1.5, -2.5, -3.5, -4.5, -5.5}, 5},
    {(double[]){1234.5, -4567.8, 91011.12, -1314.15, 1617.18}, 5},
    {(double[]){39.0, 48.5, 57.9, 66.4, 80.8}, 5},
    {(double[]){-999.9, 0.0, 999.9, 10000.0, -10000.0}, 5},
    {(double[]){2000.1, -1500.3, 1200.5, -800.7, 400.2}, 5},
    {(double[]){13.14, 15.92, 65.35, 89.79, -32.38}, 5},
    {(double[]){-50.05, -75.1, 25.25, 50.5, 100.75}, 5},
    {(double[]){500.01, 1000.1, 1500.2, 2000.3, -2500.4}, 5},
    {(double[]){20.2, -30.3, 40.4, -50.5, 60.6}, 5},
    {(double[]){123.0, 456.0, 789.0, 1011.0, 1213.0}, 5},
    {(double[]){7.0, -14.0, 21.0, -28.0, 35.0}, 5},
    {(double[]){502.0, 700.0, 900.0, 1100.0, 1300.0}, 5},
    {(double[]){-10.99, 22.45, -33.67, 44.78, -55.89}, 5}
};
int num_test_cases = 29;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    if (tf.n > 0 && tf.data != nullptr) {
        double min_val = tf.data[0];
        for (int i = 1; i < tf.n; i++) {
            if (tf.data[i] < min_val) {
                min_val = tf.data[i];
            }
        }
        tf.data[tf.n - 1] = min_val;
    }
    return tf;
}

int check(TestCase tc) {
    if (tc.n == 0 || tc.data == nullptr) return 0;

    double* Os = standardize(tc.data, tc.n);

    TestCase Tf_case = change(tc);

    double* Of = standardize(Tf_case.data, Tf_case.n);

    int is_valid = 0;

    if (Os != nullptr && Of != nullptr) {
        // Check Os != Of ; arrays must differ at least at one element
        int differ = 0;
        for (int i = 0; i < tc.n; i++) {
            if (Os[i] != Of[i]) {
                differ = 1;
                break;
            }
        }
        if (differ) {
            is_valid = 1;
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