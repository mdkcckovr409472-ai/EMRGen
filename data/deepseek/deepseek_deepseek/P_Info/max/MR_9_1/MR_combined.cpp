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
    {(double[]){1.0, 2.0, 3.0}, 3},
    {(double[]){3.0, 2.0, 1.0}, 3},
    {(double[]){-1.5, -2.0, -3.0}, 3},
    {(double[]){0.0, 0.0, 0.0}, 3},
    {(double[]){5.5}, 1},
    {(double[]){-10.2, 15.7, 0.0, 3.3}, 4},
    {(double[]){1.1, 1.1, 1.1}, 3},
    {(double[]){2.71828, 3.14159}, 2},
    {(double[]){100.0, 200.0, 150.0}, 3},
    {(double[]){-0.001, 0.001}, 2},
    {(double[]){1.0, 2.0, 3.0, 4.0, 5.0}, 5},
    {(double[]){5.0, 4.0, 3.0, 2.0, 1.0}, 5},
    {(double[]){1.5}, 1},
    {(double[]){-5.0, -1.0, -3.0}, 3},
    {(double[]){10.0, 20.0, 10.0, 20.0}, 4},
    {(double[]){0.1, 0.2, 0.3, 0.4, 0.5}, 5},
    {(double[]){-100.0, -50.0, -75.0}, 3},
    {(double[]){12.34, 56.78}, 2},
    {(double[]){1.0, -1.0, 2.0, -2.0}, 4},
    {(double[]){999.999}, 1},
    {(double[]){2.0, 1.0, 2.0, 1.0, 2.0}, 5},
    {(double[]){0.0, -5.0, 10.0}, 3},
    {(double[]){7.7, 8.8, 9.9, 10.1}, 4},
    {(double[]){-2.5, -1.5, -3.5}, 3},
    {(double[]){1.0, 2.0, 3.0, 2.0, 1.0}, 5},
    {(double[]){0.0}, 1},
    {(double[]){4.4, 5.5, 6.6}, 3},
    {(double[]){-10.0, 0.0, 10.0}, 3},
    {(double[]){1.23, 4.56, 7.89}, 3},
    {(double[]){-0.5, 0.0, 0.5}, 3}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    double Os = max(tc.elements, tc.n);
    for (int i = 0; i < tf.n; ++i) {
        if (tf.elements[i] == Os) {
            tf.elements[i] = Os + 10.0;
            break;
        }
    }
    return tf;
}

int check(TestCase tc) {
    double Os = max(tc.elements, tc.n);
    TestCase Tf_case = change(tc);
    double Of = max(Tf_case.elements, Tf_case.n);
    int is_valid = 0;
    if (Os + 10.0 == Of) {
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