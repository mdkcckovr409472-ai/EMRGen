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
    {(double[]){1.0, -1.0, 1.0, -1.0, 1.0}, 1, 0.0, 1.0, 5},
    {(double[]){1.0, -1.0, 1.0, -1.0, 1.0}, 0, 0.0, 1.0, 5},
    {(double[]){3.5, -2.2, 0.0, 4.1, -1.5, 2.8}, 2, 0.78, 4.5, 6},
    {(double[]){-5.0, 2.3, 4.4, -3.1, 0.0, 1.9, -2.2}, 3, -0.23, 7.0, 7},
    {(double[]){2.0, 2.0, 2.0, 2.0}, 3, 2.0, 0.1, 4},
    {(double[]){2.0, 2.0, 2.0, 2.0}, 1, 2.0, 0.1, 4},
    {(double[]){0.5, -0.7, 0.3, -0.2, 0.9}, 2, 0.16, 0.5, 5},
    {(double[]){0.0, 0.0, 0.0, 0.0}, 1, 0.0, 0.01, 4},
    {(double[]){10.0, -10.0, 10.0, -10.0, 10.0}, 2, 0.0, 100.0, 5},
    {(double[]){3.14}, 0, 3.14, 0.5, 1},
    {(double[]){1.0, -1.0}, 1, 0.0, 1.0, 2},
    {(double[]){2.0, 2.0, 2.0}, 2, 2.0, 0.2, 3},
    {(double[]){5.1, -3.2, 4.8, 0.0, -1.1, 2.2, -4.0, 3.3}, 4, 0.775, 8.0, 8},
    {(double[]){5.1, -3.2, 4.8, 0.0, -1.1, 2.2, -4.0, 3.3}, 0, 0.775, 8.0, 8},
    {(double[]){1.01, 0.99, 1.00, 1.02}, 1, 1.005, 0.0001, 4},
    {(double[]){-2.0, -3.5, -1.0, -4.5}, 2, -2.75, 2.0, 4},
    {(double[]){0.25, 0.75, -0.5, 1.5, -1.25}, 3, 0.15, 1.0, 5},
    {(double[]){1.0, 2.0, 3.0, 2.5, 1.5, 0.5, -0.5, -1.5, -2.0, -1.0}, 5, 0.5, 3.0, 10},
    {(double[]){1.0, 2.0, 3.0, 2.5, 1.5, 0.5, -0.5, -1.5, -2.0, -1.0}, 0, 0.5, 3.0, 10},
    {(double[]){4.4, 4.4, -2.2, 3.3, -2.2, 5.5}, 2, 2.3, 9.0, 6},
    {(double[]){4.4, 4.4, -2.2, 3.3, -2.2, 5.5}, 1, 2.3, 9.0, 6},
    {(double[]){0.0, 1.0, 0.0, -1.0, 0.0}, 2, 0.0, 0.5, 5},
    {(double[]){0.0, 1.0, 0.0, -1.0, 0.0}, 4, 0.0, 0.5, 5},
    {(double[]){7.2, -3.1, 4.6, -2.8, 0.9, 1.2}, 3, 0.8333, 10.0, 6},
    {(double[]){7.2, -3.1, 4.6, -2.8, 0.9, 1.2}, 0, 0.8333, 10.0, 6},
    {(double[]){2.5, -1.5, 3.0, -2.0, 0.0, 1.0, -3.5, 4.0, -0.5}, 5, 0.1111, 5.0, 9},
    {(double[]){2.5, -1.5, 3.0, -2.0, 0.0, 1.0, -3.5, 4.0, -0.5}, 2, 0.1111, 5.0, 9},
    {(double[]){5.0,5.0,5.0,5.0,5.0}, 2, 5.0, 0.2, 5},
    {(double[]){5.0,5.0,5.0,5.0,5.0}, 0, 5.0, 0.2, 5},
    {(double[]){-0.3, 0.7, -0.2}, 1, 0.067, 0.2, 3}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    tf.variance = tc.variance * 2;
    return tf;
}

int check(TestCase tc) {
    double Os = autoCorrelation(tc.data, tc.lag, tc.mean, tc.variance, tc.n);
    TestCase Tf_case = change(tc);
    double Of = autoCorrelation(Tf_case.data, Tf_case.lag, Tf_case.mean, Tf_case.variance, Tf_case.n);
    int is_valid = 0;
    const double epsilon = 1e-9;
    if (fabs(Of - 0.5 * Os) < epsilon) {
        is_valid = 1;
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