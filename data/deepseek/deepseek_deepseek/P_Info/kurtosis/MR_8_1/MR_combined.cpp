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


double kurtosis(double data[], int n) {
    double sum = 0;
    double sumPD = 0;
    double sumSq = 0;
    for (int i = 0; i < n; i++) {
        sum += data[i];
        sumSq += data[i] * data[i];
    }
    double mean = sum / n;
    double standardDeviation = sqrt((sumSq - mean * sum) / n);
    for (int i = 0; i < n; i++) {
        sumPD += pow(data[i] - mean, 4);
    }
    double moment4 = sumPD / n;
    return -3 + moment4 / (standardDeviation * standardDeviation * standardDeviation * standardDeviation);
}


typedef struct {
    double* data; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0, 2.0, 3.0, 4.0, 5.0}, 5},
    {(double[]){2.5, 3.5, 4.5, 5.5, 6.5}, 5},
    {(double[]){-1.0, 0.0, 1.0}, 3},
    {(double[]){10.0, 20.0, 30.0, 40.0}, 4},
    {(double[]){0.1, 0.2, 0.3, 0.4, 0.5, 0.6}, 6},
    {(double[]){100.0, 200.0, 300.0}, 3},
    {(double[]){-5.0, -4.0, -3.0, -2.0, -1.0}, 5},
    {(double[]){1.5}, 1},
    {(double[]){2.0, 2.0, 2.0, 2.0}, 4},
    {(double[]){1.0, 1.0, 2.0, 2.0}, 4},
    {(double[]){1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0}, 8},
    {(double[]){-10.0, 0.0, 10.0}, 3},
    {(double[]){3.14, 6.28, 9.42}, 3},
    {(double[]){0.5, 1.5, 2.5, 3.5, 4.5, 5.5}, 6},
    {(double[]){7.0, 7.0, 7.0, 7.0, 7.0}, 5},
    {(double[]){1.1, 2.2, 3.3, 4.4}, 4},
    {(double[]){-2.0, -1.0, 0.0, 1.0, 2.0}, 5},
    {(double[]){15.0, 25.0, 35.0, 45.0, 55.0}, 5},
    {(double[]){0.0, 0.0, 0.0, 0.0}, 4},
    {(double[]){8.0, 6.0, 7.0, 5.0, 3.0, 0.0, 9.0}, 7},
    {(double[]){1.0, 4.0, 9.0, 16.0, 25.0}, 5},
    {(double[]){-3.5, -2.5, -1.5, -0.5, 0.5, 1.5, 2.5}, 7},
    {(double[]){12.34, 56.78}, 2},
    {(double[]){0.01, 0.02, 0.03}, 3},
    {(double[]){50.0, 60.0, 70.0, 80.0, 90.0, 100.0}, 6},
    {(double[]){-100.0, -50.0, 0.0, 50.0, 100.0}, 5},
    {(double[]){1.0, 1.0, 1.0, 2.0, 2.0, 2.0}, 6},
    {(double[]){9.0, 10.0, 11.0, 12.0, 13.0}, 5},
    {(double[]){0.25, 0.5, 0.75, 1.0}, 4},
    {(double[]){6.0, 12.0, 18.0, 24.0, 30.0}, 5}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    double k = 5.0; // 常数k，可根据需要调整
    double* new_data = new double[tf.n];
    for (int i = 0; i < tf.n; i++) {
        new_data[i] = tf.data[i] + k;
    }
    tf.data = new_data;
    return tf;
}

int check(TestCase tc) {
    double Os = kurtosis(tc.data, tc.n);
    TestCase Tf_case = change(tc);
    double Of = kurtosis(Tf_case.data, Tf_case.n);
    int is_valid = 0;
    const double epsilon = 1e-9;
    if (fabs(Os - Of) < epsilon) {
        is_valid = 1;
    }
    delete[] Tf_case.data;
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