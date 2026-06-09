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


double g( double expected[],  double observed[], int n) {
    double sumExpected = 0;
    double sumObserved = 0;
    for (int i = 0; i < n; i++) {
        sumExpected += expected[i];
        sumObserved += observed[i];
    }
    double ratio = 1;
    bool rescale = false;
    if (fabs(sumExpected - sumObserved) > 10E-6) {
        ratio = sumObserved / sumExpected;
        rescale = true;
    }
    double sum = 0;
        for (int i = 0; i < n; i++) {
            double dev = rescale ? log((double) observed[i] / (ratio * expected[i])) : log((double) observed[i] / expected[i]);
            sum += (double) observed[i] * dev;
        }
    return 2 * sum;
}



typedef struct {
    double* expected; double* observed; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0, 2.0, 3.0}, (double[]){1.0, 2.0, 3.0}, 3},
    {(double[]){4.0, 5.0, 6.0}, (double[]){4.0, 5.0, 6.0}, 3},
    {(double[]){10.0, 20.0, 30.0}, (double[]){9.0, 21.0, 31.0}, 3},
    {(double[]){2.5, 3.5}, (double[]){2.4, 3.6}, 2},
    {(double[]){100.0, 200.0}, (double[]){105.0, 195.0}, 2},
    {(double[]){0.5, 1.5, 2.5}, (double[]){0.55, 1.45, 2.55}, 3},
    {(double[]){7.0}, (double[]){7.0}, 1},
    {(double[]){7.0}, (double[]){7.5}, 1},
    {(double[]){1.0, 1.0, 1.0, 1.0}, (double[]){1.0, 1.0, 1.0, 1.0}, 4},
    {(double[]){1.0, 1.0, 1.0, 1.0}, (double[]){0.9, 1.1, 0.95, 1.05}, 4},
    {(double[]){3.14, 2.71}, (double[]){3.14, 2.71}, 2},
    {(double[]){3.14, 2.71}, (double[]){3.0, 2.8}, 2},
    {(double[]){0.1, 0.2, 0.3}, (double[]){0.1, 0.2, 0.3}, 3},
    {(double[]){0.1, 0.2, 0.3}, (double[]){0.12, 0.18, 0.28}, 3},
    {(double[]){8.0, 6.0, 7.0, 5.0}, (double[]){8.0, 6.0, 7.0, 5.0}, 4},
    {(double[]){8.0, 6.0, 7.0, 5.0}, (double[]){7.5, 6.5, 7.2, 4.8}, 4},
    {(double[]){50.0, 50.0}, (double[]){50.0, 50.0}, 2},
    {(double[]){50.0, 50.0}, (double[]){55.0, 45.0}, 2},
    {(double[]){12.0, 24.0, 36.0}, (double[]){12.0, 24.0, 36.0}, 3},
    {(double[]){12.0, 24.0, 36.0}, (double[]){11.0, 25.0, 37.0}, 3},
    {(double[]){9.8, 7.6}, (double[]){9.8, 7.6}, 2},
    {(double[]){9.8, 7.6}, (double[]){10.0, 7.4}, 2},
    {(double[]){15.0, 25.0, 35.0, 45.0}, (double[]){15.0, 25.0, 35.0, 45.0}, 4},
    {(double[]){15.0, 25.0, 35.0, 45.0}, (double[]){14.5, 25.5, 34.5, 45.5}, 4},
    {(double[]){2.0, 4.0, 8.0}, (double[]){2.0, 4.0, 8.0}, 3},
    {(double[]){2.0, 4.0, 8.0}, (double[]){2.1, 3.9, 8.05}, 3},
    {(double[]){6.0, 12.0, 18.0, 24.0, 30.0}, (double[]){6.0, 12.0, 18.0, 24.0, 30.0}, 5},
    {(double[]){6.0, 12.0, 18.0, 24.0, 30.0}, (double[]){5.5, 12.5, 17.5, 24.5, 30.0}, 5},
    {(double[]){0.01, 0.02, 0.03}, (double[]){0.01, 0.02, 0.03}, 3},
    {(double[]){0.01, 0.02, 0.03}, (double[]){0.009, 0.021, 0.029}, 3}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    double k = 2.5;
    if (tf.expected != nullptr && tf.n > 0) {
        for (int i = 0; i < tf.n; i++) {
            tf.expected[i] *= k;
        }
    }
    return tf;
}

int check(TestCase tc) {
    double Os = g(tc.expected, tc.observed, tc.n);
    TestCase Tf_case = change(tc);
    double Of = g(Tf_case.expected, Tf_case.observed, Tf_case.n);
    int is_valid = 0;
    if (fabs(Os - Of) < 1e-6) {
        is_valid = 1;
    }
    if (Tf_case.expected != tc.expected) {
        delete[] Tf_case.expected;
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