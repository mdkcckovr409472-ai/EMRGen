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


double evaluateWeightedProduct( double values[],  double weights[],  int begin, int lengths, int n) {
    double product = 1.0;
     
    for (int i = begin; i < begin + lengths; i++) {
        product *= pow(values[i], weights[i]);
    }
    return product;
}


typedef struct {
    double* values; double* weights; int begin; int lengths; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0, 2.0, 3.0}, (double[]){0.5, 1.0, 1.5}, 0, 3, 3},
    {(double[]){2.5, 3.5}, (double[]){1.0, 2.0}, 0, 2, 2},
    {(double[]){1.0, 1.0, 1.0, 1.0}, (double[]){0.0, 0.0, 0.0, 0.0}, 0, 4, 4},
    {(double[]){4.0, 9.0}, (double[]){0.5, 0.5}, 0, 2, 2},
    {(double[]){2.0, 3.0, 4.0}, (double[]){1.0, 0.0, 2.0}, 0, 3, 3},
    {(double[]){0.5, 2.0}, (double[]){2.0, -1.0}, 0, 2, 2},
    {(double[]){1.5}, (double[]){3.0}, 0, 1, 1},
    {(double[]){10.0, 20.0, 30.0}, (double[]){0.1, 0.2, 0.3}, 0, 3, 3},
    {(double[]){-2.0, 3.0}, (double[]){2.0, 3.0}, 0, 2, 2},
    {(double[]){0.1, 0.2, 0.3}, (double[]){1.0, 2.0, 1.0}, 0, 3, 3},
    {(double[]){1.0, 2.0, 3.0, 4.0}, (double[]){1.0, 1.0, 1.0, 1.0}, 1, 2, 4},
    {(double[]){5.0, 6.0, 7.0, 8.0}, (double[]){0.5, 0.5, 0.5, 0.5}, 2, 2, 4},
    {(double[]){2.0, 4.0, 8.0, 16.0}, (double[]){1.0, 2.0, 3.0, 4.0}, 0, 4, 4},
    {(double[]){3.0, 3.0, 3.0}, (double[]){1.0, 2.0, 3.0}, 0, 3, 3},
    {(double[]){1.0, 10.0, 100.0}, (double[]){0.0, 1.0, 0.5}, 0, 3, 3},
    {(double[]){0.25, 4.0}, (double[]){-1.0, 0.5}, 0, 2, 2},
    {(double[]){1.2, 2.4, 3.6}, (double[]){2.0, 1.0, 0.5}, 0, 3, 3},
    {(double[]){-1.0, -2.0, -3.0}, (double[]){2.0, 2.0, 2.0}, 0, 3, 3},
    {(double[]){8.0}, (double[]){1.0/3.0}, 0, 1, 1},
    {(double[]){9.0, 16.0, 25.0}, (double[]){0.5, 0.5, 0.5}, 0, 3, 3},
    {(double[]){1.0, 2.0, 3.0, 4.0, 5.0}, (double[]){0.1, 0.2, 0.3, 0.4, 0.5}, 2, 3, 5},
    {(double[]){0.0, 5.0}, (double[]){0.0, 2.0}, 0, 2, 2},
    {(double[]){2.0, 2.0, 2.0}, (double[]){1.0, 2.0, 3.0}, 1, 2, 3},
    {(double[]){1.5, 2.5, 3.5, 4.5}, (double[]){1.0, -1.0, 2.0, -2.0}, 0, 4, 4},
    {(double[]){100.0, 0.01}, (double[]){0.5, 0.5}, 0, 2, 2},
    {(double[]){6.0}, (double[]){2.5}, 0, 1, 1},
    {(double[]){1.0, 1.0}, (double[]){100.0, -100.0}, 0, 2, 2},
    {(double[]){2.71828, 3.14159}, (double[]){1.0, 2.0}, 0, 2, 2},
    {(double[]){7.0, 8.0, 9.0, 10.0}, (double[]){0.0, 1.0, 0.0, 1.0}, 1, 3, 4},
    {(double[]){-4.0, 4.0}, (double[]){3.0, 0.25}, 0, 2, 2}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    tf.values = new double[tc.n];
    for (int i = 0; i < tc.n; i++) {
        tf.values[i] = tc.values[i] * 2.0;
    }
    return tf;
}

int check(TestCase tc) {
    double Os = evaluateWeightedProduct(tc.values, tc.weights, tc.begin, tc.lengths, tc.n);
    TestCase Tf_case = change(tc);
    double Of = evaluateWeightedProduct(Tf_case.values, Tf_case.weights, Tf_case.begin, Tf_case.lengths, Tf_case.n);
    double weight_sum = 0.0;
    for (int i = tc.begin; i < tc.begin + tc.lengths; i++) {
        weight_sum += tc.weights[i];
    }
    double expected_factor = pow(2.0, weight_sum);
    int is_valid = 0;
    if (fabs(expected_factor * Os - Of) < 1e-9) {
        is_valid = 1;
    }
    delete[] Tf_case.values;
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