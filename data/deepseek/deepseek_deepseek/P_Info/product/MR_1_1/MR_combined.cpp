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
    {(double[]){1.0, 2.0, 3.0}, 3},
    {(double[]){2.5, 4.0}, 2},
    {(double[]){-1.0, 5.0}, 2},
    {(double[]){0.0, 10.0, 20.0}, 3},
    {(double[]){0.5, 0.5, 0.5}, 3},
    {(double[]){-2.0, -3.0, -4.0}, 3},
    {(double[]){100.0}, 1},
    {(double[]){-1.0, -1.0, -1.0, -1.0}, 4},
    {(double[]){1.1, 2.2}, 2},
    {(double[]){3.14, 2.71}, 2},
    {(double[]){10.0, 0.1}, 2},
    {(double[]){-5.5, 2.0}, 2},
    {(double[]){1.0, 1.0, 1.0, 1.0, 1.0}, 5},
    {(double[]){2.0, 0.5}, 2},
    {(double[]){-10.0, 0.5}, 2},
    {(double[]){4.0, 2.5, 1.6}, 3},
    {(double[]){0.25, 4.0}, 2},
    {(double[]){-0.5, -2.0}, 2},
    {(double[]){7.5, 2.0, 1.0}, 3},
    {(double[]){0.0, 0.0, 5.0}, 3},
    {(double[]){1.5, -1.5}, 2},
    {(double[]){8.0, 0.125}, 2},
    {(double[]){6.0, 1.5, 2.0}, 3},
    {(double[]){-3.0, -0.333333}, 2},
    {(double[]){9.0, 0.0, 3.0}, 3},
    {(double[]){0.2, 0.2, 0.2, 0.2, 0.2}, 5},
    {(double[]){12.0, 0.25}, 2},
    {(double[]){-1.0, 1.0, -1.0}, 3},
    {(double[]){15.0, 2.0, 0.5}, 3},
    {(double[]){1.0}, 1}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    tf.elements = new double[tf.n];
    for (int i = 0; i < tf.n; ++i) {
        tf.elements[i] = tc.elements[i] * 2.0;
    }
    return tf;
}

int check(TestCase tc) {
    double Os = product(tc.elements, tc.n);
    TestCase Tf_case = change(tc);
    double Of = product(Tf_case.elements, Tf_case.n);
    int is_valid = 0;
    double expected = Os * pow(2.0, tc.n);
    if (fabs(Of - expected) < 1e-9) {
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