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


double max(double elements[], int n) {
    int size = n;
    double max = elements[size - 1];
    for (int i = size - 1; --i >= 0; ) {
        if (elements[i] > max) {
            max = elements[i];
        }
    }
    return max;
}


typedef struct {
    double* elements; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){5.0}, 1},
    {(double[]){-3.2, 7.1}, 2},
    {(double[]){1.5, 2.5, 3.5}, 3},
    {(double[]){9.9, 0.0, -1.0}, 3},
    {(double[]){-5.5, -2.2, -3.3}, 3},
    {(double[]){4.0, 4.0, 4.0}, 3},
    {(double[]){2.1, 8.3, 5.5, 7.7}, 4},
    {(double[]){-1.0, 0.0, 1.0, -2.0, 2.0}, 5},
    {(double[]){3.14, 2.71, 1.41, 1.73}, 4},
    {(double[]){0.001, 0.002, 0.003, 0.004, 0.005}, 5},
    {(double[]){100.0, -100.0, 50.0, -50.0}, 4},
    {(double[]){-0.5, -0.2, -0.8, -0.1}, 4},
    {(double[]){7.5, 3.2, 7.5, 2.2}, 4},
    {(double[]){1e-3, 1e-2, 1e-1, 1.0}, 4},
    {(double[]){-10.0, 0.0, 10.0, 5.0}, 4},
    {(double[]){5.5, 6.6, 7.7, 8.8, 9.9}, 5},
    {(double[]){9.9, 8.8, 7.7, 6.6, 5.5}, 5},
    {(double[]){2.2, 3.3, 2.2, 3.3, 2.2}, 5},
    {(double[]){0.0, -0.0, 0.0}, 3},
    {(double[]){-3.3, 3.3, -3.3, 3.3}, 4},
    {(double[]){0.5, 0.5, 0.4, 0.6, 0.5}, 5},
    {(double[]){-1.1, -2.2, -3.3, -4.4, -0.5}, 5},
    {(double[]){100.5, 99.9, 101.0, 100.0}, 4},
    {(double[]){-50.0, 25.0, -25.0, 50.0}, 4},
    {(double[]){3.0, 1.0, 4.0, 1.5, 2.5}, 5},
    {(double[]){0.123, 0.456, 0.789, 0.101, 0.112}, 5},
    {(double[]){-0.001, -0.002, -0.003}, 3},
    {(double[]){5.0, 10.0, 5.0, 10.0, 5.0}, 5},
    {(double[]){2.718, 3.1415, 1.618, 2.0, 3.0}, 5},
    {(double[]){-9.9, 9.9, -8.8, 8.8, 0.0}, 5}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    double* new_elements = new double[tf.n];
    for (int i = 0; i < tf.n; ++i) {
        new_elements[i] = tf.elements[i] - 1.0;
    }
    tf.elements = new_elements;
    return tf;
}

int check(TestCase tc) {
    double Os = max(tc.elements, tc.n);
    TestCase Tf_case = change(tc);
    double Of = max(Tf_case.elements, Tf_case.n);
    int is_valid = 0;
    if (Os > Of) {
        is_valid = 1;
    }
    delete[] Tf_case.elements;
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