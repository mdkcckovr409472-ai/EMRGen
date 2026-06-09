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


double min(double elements[], int n) {
    int size = n;
    double min = elements[size - 1];
    for (int i = size - 1; --i >= 0; ) {
        if (elements[i] < min) {
            min = elements[i];
        }
    }
    return min;
}


typedef struct {
    double* elements; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){5.0}, 1},
    {(double[]){-1.0, 2.0}, 2},
    {(double[]){0.0, 0.0, 0.0}, 3},
    {(double[]){3.2, 1.5, 4.8, 2.2}, 4},
    {(double[]){-5.5, -3.3, -9.9, -1.1}, 4},
    {(double[]){10.0, -10.0, 5.0, -5.0}, 4},
    {(double[]){2.2, 2.2, 2.2}, 3},
    {(double[]){7.7, 3.3, 5.5, 1.1, 9.9}, 5},
    {(double[]){-0.5, 0.5, -0.5, 0.5}, 4},
    {(double[]){100.0, 50.0, 75.0, 25.0, 0.0}, 5},
    {(double[]){-100.0, -50.0, -75.0, -25.0, -1.0}, 5},
    {(double[]){3.1415, 2.7182, 1.618, 0.5772}, 4},
    {(double[]){-2.0, 2.0, -2.0, 2.0, -2.0}, 5},
    {(double[]){9.9, 8.8, 7.7, 6.6, 5.5, 4.4}, 6},
    {(double[]){-1.1, -2.2, -3.3, -4.4, -5.5}, 5},
    {(double[]){0.001, 0.0001, 0.01, 0.1}, 4},
    {(double[]){-0.001, -0.0001, -0.01, -0.1}, 4},
    {(double[]){5.5, 3.3, 5.5, 3.3, 1.1}, 5},
    {(double[]){1.0, -1.0, 1.0, -1.0, 1.0, -1.0}, 6},
    {(double[]){8.0, 6.0, 7.0, 5.0, 3.0, 4.0, 2.0}, 7},
    {(double[]){2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0}, 7},
    {(double[]){-3.0, 0.0, 3.0, -6.0, 9.0}, 5},
    {(double[]){1.5, 2.5, 3.5, 4.5, 0.5}, 5},
    {(double[]){-2.5, -1.5, -0.5, 0.5, 1.5}, 5},
    {(double[]){0.0, -0.0, 0.0, -0.0}, 4},
    {(double[]){-9.9, 9.9, -8.8, 8.8, -7.7, 7.7}, 6},
    {(double[]){3.0, 1.0, 4.0, 1.5, 5.0, 9.0, 2.6}, 7},
    {(double[]){-1.2, 3.4, -5.6, 7.8, -9.0, 11.2}, 6},
    {(double[]){0.123, 0.456, 0.789, 0.012}, 4},
    {(double[]){-0.123, -0.456, -0.789, -0.012}, 4}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    // Allocate new memory for divided elements
    double* new_elements = new double[tc.n];
    for (int i = 0; i < tc.n; i++) {
        new_elements[i] = tc.elements[i] / 2.0;
    }
    tf.elements = new_elements;
    return tf;
}

int check(TestCase tc) {
    // (1) Extract source input Ts
    double* Ts = tc.elements;
    int n = tc.n;
    // (2) Call function under test for source output Os
    double Os = min(Ts, n);
    // (3) Call change() to construct follow-up test case Tf_case
    TestCase Tf_case = change(tc);
    // (4) Extract Tf input and get follow-up output Of
    double* Tf = Tf_case.elements;
    double Of = min(Tf, n);
    // (5) Verify MR: Os / 2 == Of (allowing small epsilon for floating point)
    int is_valid = 0;
    const double epsilon = 1e-9;
    if (std::abs((Os / 2.0) - Of) < epsilon) {
        is_valid = 1;
    }
    // (6) Free dynamically allocated memory from change()
    delete[] Tf_case.elements;
    // (7) Return verification result
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