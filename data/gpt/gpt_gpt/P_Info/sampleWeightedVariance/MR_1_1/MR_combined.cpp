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
    {(double[]){2.5, 3.0, 4.5}, (double[]){1.0, 0.5, 1.5}, 3},
    {(double[]){5.0}, (double[]){2.0}, 1},
    {(double[]){-1.2, 3.4}, (double[]){0.8, 1.2}, 2},
    {(double[]){0.0, 0.0, 0.0, 0.0}, (double[]){0.5, 0.5, 0.5, 0.5}, 4},
    {(double[]){7.1, -2.3, 5.5, 1.2}, (double[]){1.0, 0.3, 0.7, 0.5}, 4},
    {(double[]){10.0, 15.0, 20.0}, (double[]){2.0, 2.0, 2.0}, 3},
    {(double[]){-5.5, -3.3, -1.1}, (double[]){1.0, 1.0, 1.0}, 3},
    {(double[]){8.8, 2.2, 4.4, 6.6, 1.1}, (double[]){0.9, 0.2, 0.4, 0.6, 0.5}, 5},
    {(double[]){3.3, 6.6, 9.9}, (double[]){1.5, 0.5, 1.0}, 3},
    {(double[]){0.5, 1.5, 2.5, 3.5}, (double[]){0.25, 0.75, 0.5, 0.5}, 4},
    {(double[]){-2.0, 4.0}, (double[]){1.2, 0.9}, 2},
    {(double[]){5.5, 5.5, 5.5, 5.5}, (double[]){0.4, 0.4, 0.4, 0.4}, 4},
    {(double[]){1.0, 2.0, 3.0, 4.0, 5.0}, (double[]){0.5, 0.5, 0.5, 0.5, 0.5}, 5},
    {(double[]){-3.0, 0.0, 3.0}, (double[]){1.0, 1.0, 1.0}, 3},
    {(double[]){2.2, 4.4, 6.6, 8.8}, (double[]){0.3, 0.7, 0.5, 0.5}, 4},
    {(double[]){9.9}, (double[]){1.1}, 1},
    {(double[]){-4.4, -2.2, 0.0, 2.2, 4.4}, (double[]){0.2, 0.3, 0.5, 0.7, 0.8}, 5},
    {(double[]){3.14, 2.71}, (double[]){1.0, 1.0}, 2},
    {(double[]){6.0, 7.0, 8.0}, (double[]){0.6, 0.7, 0.8}, 3},
    {(double[]){-1.0, 0.0, 1.0, 2.0}, (double[]){0.5, 0.5, 0.5, 0.5}, 4},
    {(double[]){0.1, 0.2, 0.3, 0.4, 0.5}, (double[]){0.9, 0.8, 0.7, 0.6, 0.5}, 5},
    {(double[]){-9.0, -6.0, -3.0}, (double[]){1.5, 1.0, 0.5}, 3},
    {(double[]){12.0, 8.0, 4.0}, (double[]){0.4, 0.4, 0.4}, 3},
    {(double[]){1.5, 3.0, 4.5, 6.0}, (double[]){0.2, 0.3, 0.4, 0.5}, 4},
    {(double[]){7.5, 2.5}, (double[]){0.6, 0.9}, 2},
    {(double[]){0.0, 5.0, 10.0}, (double[]){0.3, 0.3, 0.4}, 3},
    {(double[]){-2.5, 2.5}, (double[]){1.0, 1.0}, 2},
    {(double[]){3.0, -3.0, 6.0, -6.0}, (double[]){0.5, 0.5, 0.5, 0.5}, 4},
    {(double[]){4.4, 5.5, 6.6, 7.7, 8.8, 9.9}, (double[]){0.2, 0.3, 0.4, 0.5, 0.6, 0.7}, 6},
    {(double[]){2.0, 2.0, 2.0}, (double[]){0.33, 0.33, 0.34}, 3}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    // Allocate new data array for follow-up input
    double* newData = new double[tc.n];
    for (int i = 0; i < tc.n; i++) {
        newData[i] = tc.data[i] * 2;
    }
    tf.data = newData;
    // weights and n remain the same, reuse original pointers
    return tf;
}

int check(TestCase tc) {
    double Os = sampleWeightedVariance(tc.data, tc.weights, tc.n);

    TestCase Tf_case = change(tc);
    double Of = sampleWeightedVariance(Tf_case.data, Tf_case.weights, Tf_case.n);

    int is_valid = 0;
    if (Of != Os) {
        is_valid = 1;
    }

    // Clean up dynamically allocated memory in Tf_case if any
    if (Tf_case.data != tc.data) {
        delete[] Tf_case.data;
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