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


double meanDeviation(double elements[], double mean, int n) {
    int size = n;
    double sum = 0;
    for (int i = size; --i >= 0; ) {
        sum += fabs(elements[i] - mean);
    }
    return sum / size;
}


typedef struct {
    double* elements; double mean; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0, 2.0, 3.0}, 2.0, 3},
    {(double[]){1.0, 2.0, 3.0}, 1.0, 3},
    {(double[]){1.0, 2.0, 3.0}, 3.0, 3},
    {(double[]){-1.0, 0.0, 1.0}, 0.0, 3},
    {(double[]){-5.0, 0.0, 5.0}, 0.0, 3},
    {(double[]){10.0, 20.0, 30.0}, 20.0, 3},
    {(double[]){2.5, 3.5, 4.5}, 3.5, 3},
    {(double[]){0.0}, 0.0, 1},
    {(double[]){100.0}, 100.0, 1},
    {(double[]){1.1, 2.2, 3.3, 4.4}, 2.75, 4},
    {(double[]){-2.5, -1.5, -0.5, 0.5, 1.5}, -0.5, 5},
    {(double[]){0.0, 0.0, 0.0, 0.0}, 0.0, 4},
    {(double[]){1.0, 1.0, 1.0, 1.0}, 1.0, 4},
    {(double[]){-10.0, -5.0, 0.0, 5.0, 10.0}, 0.0, 5},
    {(double[]){3.14, 6.28, 9.42}, 6.28, 3},
    {(double[]){0.001, 0.002, 0.003}, 0.002, 3},
    {(double[]){-0.001, -0.002, -0.003}, -0.002, 3},
    {(double[]){1.0, 2.0, 3.0, 4.0, 5.0, 6.0}, 3.5, 6},
    {(double[]){-3.0, -2.0, -1.0, 0.0, 1.0, 2.0, 3.0}, 0.0, 7},
    {(double[]){1.5}, 2.0, 1},
    {(double[]){10.0, 20.0, 30.0, 40.0}, 25.0, 4},
    {(double[]){-100.0, 0.0, 100.0}, 0.0, 3},
    {(double[]){7.0, 7.0, 7.0, 7.0, 7.0}, 7.0, 5},
    {(double[]){2.0, 4.0, 6.0, 8.0}, 5.0, 4},
    {(double[]){-1.0, -2.0, -3.0, -4.0}, -2.5, 4},
    {(double[]){0.1, 0.2, 0.3, 0.4, 0.5}, 0.3, 5},
    {(double[]){-0.1, -0.2, -0.3, -0.4, -0.5}, -0.3, 5},
    {(double[]){1.0, 3.0, 5.0, 7.0, 9.0}, 5.0, 5},
    {(double[]){2.0, 2.0, 2.0}, 2.0, 3},
    {(double[]){1.0, 2.0, 3.0, 4.0}, 2.5, 4}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    if (tf.n > 1 && tf.elements != nullptr) {
        double first_element = tf.elements[0];
        for (int i = 0; i < tf.n - 1; ++i) {
            tf.elements[i] = tf.elements[i + 1];
        }
        tf.elements[tf.n - 1] = first_element;
    }
    return tf;
}

int check(TestCase tc) {
    if (tc.n <= 0 || tc.elements == nullptr) {
        return 1;
    }

    double Os = meanDeviation(tc.elements, tc.mean, tc.n);

    TestCase Tf_case = change(tc);

    double Of = meanDeviation(Tf_case.elements, Tf_case.mean, Tf_case.n);

    int is_valid = 0;
    const double epsilon = 1e-9;
    if (fabs(Os - Of) < epsilon) {
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