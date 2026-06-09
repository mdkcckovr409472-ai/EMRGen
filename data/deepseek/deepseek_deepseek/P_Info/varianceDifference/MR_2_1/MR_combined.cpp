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


double varianceDifference(double sample1[], double sample2[], int n) {
    double sum1 = 0;
    double sum2 = 0;
    double diff = 0;
    double sumDifference = 0;

    for (int i = 0; i < n; i++) {
        sumDifference += sample1[i] - sample2[i];
    }
    
    double meanDifference = sumDifference / n;
    for (int i = 0; i < n; i++) {
        diff = sample1[i] - sample2[i];
        sum1 += (diff - meanDifference) * (diff - meanDifference);
        sum2 += diff - meanDifference;
    }
    return (sum1 - sum2 * sum2 / n) / (n - 1);
}


typedef struct {
    double* sample1; double* sample2; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0, 2.0, 3.0}, (double[]){4.0, 5.0, 6.0}, 3},
    {(double[]){0.0, 0.0, 0.0}, (double[]){0.0, 0.0, 0.0}, 3},
    {(double[]){-1.5, 2.2, -3.7}, (double[]){1.5, -2.2, 3.7}, 3},
    {(double[]){10.2, 20.4, 30.6}, (double[]){10.2, 20.4, 30.6}, 3},
    {(double[]){1.1, 1.1, 1.1, 1.1}, (double[]){2.2, 2.2, 2.2, 2.2}, 4},
    {(double[]){0.5, 1.0, 1.5, 2.0, 2.5}, (double[]){0.0, 0.5, 1.0, 1.5, 2.0}, 5},
    {(double[]){100.0, 200.0, 300.0}, (double[]){50.0, 150.0, 250.0}, 3},
    {(double[]){-10.0, -20.0, -30.0}, (double[]){-5.0, -15.0, -25.0}, 3},
    {(double[]){1.0}, (double[]){3.0}, 1},
    {(double[]){2.5, 7.8}, (double[]){2.5, 7.8}, 2},
    {(double[]){1.0, 2.0, 3.0, 4.0, 5.0}, (double[]){5.0, 4.0, 3.0, 2.0, 1.0}, 5},
    {(double[]){0.1, 0.2, 0.3}, (double[]){0.3, 0.2, 0.1}, 3},
    {(double[]){12.34, 45.67, 89.01}, (double[]){98.76, 54.32, 10.98}, 3},
    {(double[]){-1.0, 0.0, 1.0}, (double[]){1.0, 0.0, -1.0}, 3},
    {(double[]){5.5}, (double[]){5.5}, 1},
    {(double[]){1.0, 1.0, 2.0, 2.0}, (double[]){2.0, 2.0, 1.0, 1.0}, 4},
    {(double[]){3.14, 6.28, 9.42}, (double[]){1.57, 3.14, 4.71}, 3},
    {(double[]){0.0, 5.0, 10.0}, (double[]){2.0, 7.0, 12.0}, 3},
    {(double[]){-2.0, -1.0, 0.0, 1.0, 2.0}, (double[]){2.0, 1.0, 0.0, -1.0, -2.0}, 5},
    {(double[]){1000.0, 2000.0}, (double[]){500.0, 1500.0}, 2},
    {(double[]){0.001, 0.002, 0.003}, (double[]){0.003, 0.002, 0.001}, 3},
    {(double[]){8.0, 6.0, 7.0, 5.0, 3.0, 0.0, 9.0}, (double[]){1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0}, 7},
    {(double[]){1.2, 3.4, 5.6, 7.8}, (double[]){9.0, 10.1, 11.2, 12.3}, 4},
    {(double[]){-3.3, -6.6, -9.9}, (double[]){-1.1, -2.2, -3.3}, 3},
    {(double[]){15.0, 25.0, 35.0, 45.0}, (double[]){10.0, 20.0, 30.0, 40.0}, 4},
    {(double[]){0.0}, (double[]){0.0}, 1},
    {(double[]){2.0, 4.0, 8.0, 16.0}, (double[]){1.0, 2.0, 4.0, 8.0}, 4},
    {(double[]){7.7, 8.8, 9.9}, (double[]){7.7, 8.8, 9.9}, 3},
    {(double[]){1.5, 2.5, 3.5, 4.5, 5.5}, (double[]){5.5, 4.5, 3.5, 2.5, 1.5}, 5}
};
int num_test_cases = 29;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    double k = 5.0; // 常数k，示例值，可根据需要调整
    double* new_sample1 = new double[tf.n];
    for (int i = 0; i < tf.n; i++) {
        new_sample1[i] = tf.sample1[i] + k;
    }
    tf.sample1 = new_sample1;
    return tf;
}

int check(TestCase tc) {
    double Os = varianceDifference(tc.sample1, tc.sample2, tc.n);
    TestCase Tf_case = change(tc);
    double Of = varianceDifference(Tf_case.sample1, Tf_case.sample2, Tf_case.n);
    int is_valid = 0;
    if (Os == Of) {
        is_valid = 1;
    }
    delete[] Tf_case.sample1;
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