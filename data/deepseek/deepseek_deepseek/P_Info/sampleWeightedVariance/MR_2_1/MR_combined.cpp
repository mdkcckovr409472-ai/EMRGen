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


double sampleWeightedVariance(double data[], double weights[], int n) {
    double sumOfWeights = 0;
    double sumOfProducts = 0;
    double sumOfSquaredProducts = 0;
    for (int i = 0; i < n; i++) {
        sumOfWeights += weights[i];
        sumOfProducts += data[i] * weights[i];
        sumOfSquaredProducts += data[i] * data[i] * weights[i];
    }
    return (sumOfSquaredProducts - sumOfProducts * sumOfProducts / sumOfWeights) / (sumOfWeights - 1);
}


typedef struct {
    double* data; double* weights; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0, 2.0, 3.0}, (double[]){1.0, 1.0, 1.0}, 3},
    {(double[]){1.0, 2.0, 3.0}, (double[]){0.5, 1.5, 2.0}, 3},
    {(double[]){-1.0, 0.0, 1.0}, (double[]){1.0, 2.0, 1.0}, 3},
    {(double[]){10.5, 20.3, 30.7}, (double[]){2.0, 3.0, 5.0}, 3},
    {(double[]){0.0}, (double[]){1.0}, 1},
    {(double[]){5.0}, (double[]){0.1}, 1},
    {(double[]){100.0, 200.0}, (double[]){1.0, 1.0}, 2},
    {(double[]){100.0, 200.0}, (double[]){0.1, 0.9}, 2},
    {(double[]){-5.0, -3.0, -1.0}, (double[]){1.0, 1.0, 1.0}, 3},
    {(double[]){-5.0, -3.0, -1.0}, (double[]){2.0, 3.0, 5.0}, 3},
    {(double[]){1.1, 2.2, 3.3, 4.4}, (double[]){1.0, 1.0, 1.0, 1.0}, 4},
    {(double[]){1.1, 2.2, 3.3, 4.4}, (double[]){0.5, 1.5, 0.5, 2.5}, 4},
    {(double[]){0.0, 0.0, 0.0}, (double[]){1.0, 2.0, 3.0}, 3},
    {(double[]){2.0, 2.0, 2.0}, (double[]){1.0, 2.0, 3.0}, 3},
    {(double[]){1.0, 2.0, 3.0, 4.0, 5.0}, (double[]){1.0, 1.0, 1.0, 1.0, 1.0}, 5},
    {(double[]){1.0, 2.0, 3.0, 4.0, 5.0}, (double[]){0.2, 0.4, 0.6, 0.8, 1.0}, 5},
    {(double[]){-2.5, 0.0, 2.5}, (double[]){1.0, 1.0, 1.0}, 3},
    {(double[]){-2.5, 0.0, 2.5}, (double[]){1.0, 2.0, 1.0}, 3},
    {(double[]){3.14, 6.28, 9.42}, (double[]){1.0, 2.0, 3.0}, 3},
    {(double[]){0.001, 0.002, 0.003}, (double[]){100.0, 200.0, 300.0}, 3},
    {(double[]){50.0, 100.0, 150.0}, (double[]){0.0, 1.0, 0.0}, 3},
    {(double[]){7.0}, (double[]){10.0}, 1},
    {(double[]){1.0, 4.0, 9.0, 16.0}, (double[]){1.0, 2.0, 3.0, 4.0}, 4},
    {(double[]){-10.0, -5.0, 5.0, 10.0}, (double[]){1.0, 2.0, 2.0, 1.0}, 4},
    {(double[]){1.0, 2.0}, (double[]){3.0, 4.0}, 2},
    {(double[]){1.0, 2.0, 1.0, 2.0}, (double[]){1.0, 1.0, 1.0, 1.0}, 4},
    {(double[]){1.0, 2.0, 1.0, 2.0}, (double[]){2.0, 1.0, 2.0, 1.0}, 4},
    {(double[]){0.0, 10.0, 20.0}, (double[]){0.5, 0.5, 0.5}, 3},
    {(double[]){1000000.0, 1000001.0}, (double[]){1.0, 1.0}, 2},
    {(double[]){1.0e-6, 2.0e-6}, (double[]){1.0e6, 1.0e6}, 2}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    tf.data = new double[tf.n];
    for (int i = 0; i < tf.n; i++) {
        tf.data[i] = tc.data[i] * 2.0;
    }
    return tf;
}

int check(TestCase tc) {
    double Os = sampleWeightedVariance(tc.data, tc.weights, tc.n);
    TestCase Tf_case = change(tc);
    double Of = sampleWeightedVariance(Tf_case.data, Tf_case.weights, Tf_case.n);
    int is_valid = 0;
    if (fabs(4.0 * Os - Of) < 1e-9) {
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