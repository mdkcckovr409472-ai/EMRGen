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


double autoCorrelation(double data[], int lag, double mean, double variance, int n){
    double run = 0;
    for (int i = lag; i < n; i++)
    {
        run += (data[i] - mean) * (data[i - lag] - mean);
    }
    
    return run / (n - lag) / variance;
}


typedef struct {
    double* data; int lag; double mean; double variance; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0, 2.0, 3.0, 4.0, 5.0}, 1, 3.0, 2.0, 5},
    {(double[]){1.0, 2.0, 3.0, 4.0, 5.0}, 2, 3.0, 2.0, 5},
    {(double[]){1.0, 2.0, 3.0, 4.0, 5.0}, 3, 3.0, 2.0, 5},
    {(double[]){1.0, 2.0, 3.0, 4.0, 5.0}, 4, 3.0, 2.0, 5},
    {(double[]){5.0, 4.0, 3.0, 2.0, 1.0}, 1, 3.0, 2.0, 5},
    {(double[]){5.0, 4.0, 3.0, 2.0, 1.0}, 2, 3.0, 2.0, 5},
    {(double[]){2.5, 2.5, 2.5, 2.5, 2.5}, 1, 2.5, 0.0, 5},
    {(double[]){2.5, 2.5, 2.5, 2.5, 2.5}, 2, 2.5, 0.0, 5},
    {(double[]){-1.0, -2.0, -3.0, -4.0, -5.0}, 1, -3.0, 2.0, 5},
    {(double[]){-1.0, -2.0, -3.0, -4.0, -5.0}, 2, -3.0, 2.0, 5},
    {(double[]){0.0, 0.0, 0.0, 0.0, 0.0}, 1, 0.0, 0.0, 5},
    {(double[]){0.0, 0.0, 0.0, 0.0, 0.0}, 3, 0.0, 0.0, 5},
    {(double[]){10.2, 20.4, 30.6, 40.8}, 1, 25.5, 125.0, 4},
    {(double[]){10.2, 20.4, 30.6, 40.8}, 2, 25.5, 125.0, 4},
    {(double[]){10.2, 20.4, 30.6, 40.8}, 3, 25.5, 125.0, 4},
    {(double[]){1.1, 2.2, 3.3, 4.4, 5.5, 6.6}, 1, 3.85, 3.4225, 6},
    {(double[]){1.1, 2.2, 3.3, 4.4, 5.5, 6.6}, 2, 3.85, 3.4225, 6},
    {(double[]){1.1, 2.2, 3.3, 4.4, 5.5, 6.6}, 3, 3.85, 3.4225, 6},
    {(double[]){1.1, 2.2, 3.3, 4.4, 5.5, 6.6}, 4, 3.85, 3.4225, 6},
    {(double[]){1.1, 2.2, 3.3, 4.4, 5.5, 6.6}, 5, 3.85, 3.4225, 6},
    {(double[]){100.0, 200.0, 150.0, 250.0, 180.0}, 1, 176.0, 2500.0, 5},
    {(double[]){100.0, 200.0, 150.0, 250.0, 180.0}, 2, 176.0, 2500.0, 5},
    {(double[]){100.0, 200.0, 150.0, 250.0, 180.0}, 3, 176.0, 2500.0, 5},
    {(double[]){100.0, 200.0, 150.0, 250.0, 180.0}, 4, 176.0, 2500.0, 5},
    {(double[]){-5.5, 10.0, -2.5, 7.5, 0.0}, 1, 2.0, 30.0, 5},
    {(double[]){-5.5, 10.0, -2.5, 7.5, 0.0}, 2, 2.0, 30.0, 5},
    {(double[]){3.14, 1.59, 2.65, 3.58, 9.79}, 1, 4.15, 8.122, 5},
    {(double[]){3.14, 1.59, 2.65, 3.58, 9.79}, 2, 4.15, 8.122, 5},
    {(double[]){1.0}, 0, 1.0, 0.0, 1},
    {(double[]){8.0, 6.0, 7.0, 5.0, 3.0, 0.0, 9.0}, 1, 5.42857, 8.2449, 7}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    int n = tf.n;
    double* reversed_data = new double[n];
    for (int i = 0; i < n; ++i) {
        reversed_data[i] = tf.data[n - 1 - i];
    }
    tf.data = reversed_data;
    return tf;
}

int check(TestCase tc) {
    double Os = autoCorrelation(tc.data, tc.lag, tc.mean, tc.variance, tc.n);
    TestCase Tf_case = change(tc);
    double Of = autoCorrelation(Tf_case.data, Tf_case.lag, Tf_case.mean, Tf_case.variance, Tf_case.n);
    int is_valid = 0;
    if (Os == Of) {
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