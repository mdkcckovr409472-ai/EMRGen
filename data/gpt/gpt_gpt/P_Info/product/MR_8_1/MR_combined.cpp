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


double product(double elements[], int n) {
    int size = n;
    double product = 1;
    for (int i = size; --i >= 0; ) {
        product *= elements[i];
    }
    return product;
}


typedef struct {
    double* elements; int n;
} TestCase;

TestCase test_cases[] = {
    { (double[]){}, 0 },
    { (double[]){1.0}, 1 },
    { (double[]){0.0}, 1 },
    { (double[]){-1.0}, 1 },
    { (double[]){2.0, 3.0}, 2 },
    { (double[]){5.0, 0.0}, 2 },
    { (double[]){-2.0, -3.0}, 2 },
    { (double[]){1.5, -2.0, 4.0}, 3 },
    { (double[]){0.0, 1.2, -3.3}, 3 },
    { (double[]){3.0, 1.0, 4.0, 2.0}, 4 },
    { (double[]){-1.0, 2.0, -3.0, 4.0}, 4 },
    { (double[]){-0.5, 2.5, 0.0, -1.5, 3.0}, 5 },
    { (double[]){1.0, 1.0, 1.0, 1.0, 1.0}, 5 },
    { (double[]){2.2, -2.2, 3.3, -3.3, 0.1, -0.1}, 6 },
    { (double[]){10.0, 0.5, -0.5, 2.0, -2.0, 1.0}, 6 },
    { (double[]){-2.0, -2.0, -2.0}, 3 },
    { (double[]){0.25, 4.0}, 2 },
    { (double[]){0.5, 0.2, 5.0, 2.0}, 4 },
    { (double[]){0.0, 0.0, 1.0, -1.0, 2.0}, 5 },
    { (double[]){1e-3}, 1 },
    { (double[]){1e-3, 1e3}, 2 },
    { (double[]){9.0, -9.0, 1.0}, 3 },
    { (double[]){-1.0, 1.0, -1.0, 1.0}, 4 },
    { (double[]){3.1415, -2.718, 0.577, -1.618, 2.0}, 5 },
    { (double[]){0.0, 1.0, 0.0, 1.0, 0.0, 1.0}, 6 },
    { (double[]){-5.0, 0.0, -2.0}, 3 },
    { (double[]){-0.75, 1.25, -1.25, 0.75}, 4 },
    { (double[]){0.1, -10.0, 5.0, -0.2, 2.0}, 5 },
    { (double[]){2.0, 2.0, 2.0, 2.0, 2.0, 2.0}, 6 },
    { (double[]){1.0, -1.0, 1.0}, 3 }
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    if (tc.n > 0) {
        double* shifted = new double[tc.n];
        for (int i = 0; i < tc.n - 1; i++) {
            shifted[i] = tc.elements[i + 1];
        }
        shifted[tc.n - 1] = tc.elements[0];
        tf.elements = shifted;
    }
    return tf;
}

int check(TestCase tc) {
    double Os = product(tc.elements, tc.n);
    TestCase Tf_case = change(tc);
    double Of = product(Tf_case.elements, Tf_case.n);
    int is_valid = 0;
    if (Os == Of) {
        is_valid = 1;
    }
    if (Tf_case.elements != tc.elements) {
        delete[] Tf_case.elements;
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