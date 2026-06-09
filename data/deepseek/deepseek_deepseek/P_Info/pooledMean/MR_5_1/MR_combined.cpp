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


double pooledMean(double data1[], double data2[], int n1, int n2) {
    double sum1 = 0;
    for (int i = 0; i < n1; i++) {
        sum1 += data1[i];
    }
    double mean1 = sum1 / n1;
    double sum2 = 0;
    for (int i = 0; i < n2; i++) {
        sum2 += data2[i];
    }
    double mean2 = sum2 / n2;
    return (n1 * mean1 + n2 * mean2) / (n1 + n2);
}


typedef struct {
    double* data1; double* data2; int n1; int n2;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0, 2.0, 3.0}, (double[]){4.0, 5.0, 6.0}, 3, 3},
    {(double[]){10.0, 20.0}, (double[]){30.0}, 2, 1},
    {(double[]){0.0, 0.0, 0.0}, (double[]){0.0, 0.0}, 3, 2},
    {(double[]){-1.5, 2.5}, (double[]){3.5, -4.5, 1.0}, 2, 3},
    {(double[]){100.0, 200.0, 300.0}, (double[]){400.0}, 3, 1},
    {(double[]){1.1, 2.2}, (double[]){3.3, 4.4, 5.5}, 2, 3},
    {(double[]){5.0}, (double[]){5.0}, 1, 1},
    {(double[]){2.0, 4.0, 6.0, 8.0}, (double[]){1.0, 3.0, 5.0}, 4, 3},
    {(double[]){-10.0, -20.0, -30.0}, (double[]){-5.0, -15.0}, 3, 2},
    {(double[]){0.5, 1.5, 2.5, 3.5, 4.5}, (double[]){1.0, 2.0}, 5, 2},
    {(double[]){12.34, 45.67}, (double[]){89.01}, 2, 1},
    {(double[]){7.0}, (double[]){8.0, 9.0, 10.0, 11.0}, 1, 4},
    {(double[]){1.0, 3.0, 5.0, 7.0, 9.0}, (double[]){2.0, 4.0, 6.0, 8.0}, 5, 4},
    {(double[]){0.1, 0.2, 0.3}, (double[]){0.4, 0.5, 0.6, 0.7}, 3, 4},
    {(double[]){50.0, 60.0}, (double[]){70.0, 80.0, 90.0, 100.0, 110.0}, 2, 5},
    {(double[]){-2.0, -1.0, 0.0, 1.0, 2.0}, (double[]){-1.5, 0.5, 2.5}, 5, 3},
    {(double[]){1000.0, 2000.0}, (double[]){1500.0}, 2, 1},
    {(double[]){3.14159, 2.71828}, (double[]){1.41421, 1.73205, 2.23607}, 2, 3},
    {(double[]){25.0, 50.0, 75.0}, (double[]){10.0, 20.0, 30.0, 40.0}, 3, 4},
    {(double[]){8.0, 6.0, 4.0, 2.0}, (double[]){9.0, 7.0, 5.0, 3.0, 1.0}, 4, 5},
    {(double[]){0.0}, (double[]){1.0, 2.0, 3.0}, 1, 3},
    {(double[]){-100.0, 100.0}, (double[]){-50.0, 50.0, 0.0}, 2, 3},
    {(double[]){99.9, 100.1}, (double[]){100.0}, 2, 1},
    {(double[]){1.0, 2.0, 3.0, 4.0, 5.0, 6.0}, (double[]){7.0, 8.0}, 6, 2},
    {(double[]){15.0, 25.0, 35.0}, (double[]){45.0, 55.0}, 3, 2},
    {(double[]){0.25, 0.5, 0.75}, (double[]){1.0, 1.25, 1.5, 1.75}, 3, 4},
    {(double[]){6.0, 12.0, 18.0}, (double[]){24.0, 30.0, 36.0, 42.0, 48.0}, 3, 5},
    {(double[]){-3.0, 0.0, 3.0}, (double[]){-6.0, 6.0}, 3, 2},
    {(double[]){10.0, 20.0, 30.0, 40.0, 50.0}, (double[]){60.0, 70.0, 80.0, 90.0, 100.0}, 5, 5},
    {(double[]){2.5}, (double[]){7.5, 12.5}, 1, 2}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    double k = 10.0; // 示例常数k，可根据需要调整
    if (tf.data2 != nullptr && tf.n2 > 0) {
        double* new_data2 = new double[tf.n2];
        for (int i = 0; i < tf.n2; i++) {
            new_data2[i] = tf.data2[i] + k;
        }
        tf.data2 = new_data2;
    }
    return tf;
}

int check(TestCase tc) {
    double Os = pooledMean(tc.data1, tc.data2, tc.n1, tc.n2);
    TestCase Tf_case = change(tc);
    double Of = pooledMean(Tf_case.data1, Tf_case.data2, Tf_case.n1, Tf_case.n2);
    double k = 10.0;
    double expected = Os + (tc.n2 * k) / (tc.n1 + tc.n2);
    int is_valid = 0;
    if (std::abs(Of - expected) < 1e-9) {
        is_valid = 1;
    }
    if (Tf_case.data2 != tc.data2) {
        delete[] Tf_case.data2;
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