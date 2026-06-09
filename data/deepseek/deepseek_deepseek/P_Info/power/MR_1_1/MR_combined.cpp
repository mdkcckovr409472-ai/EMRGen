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


double* power(double data[], int k, int n) {
    for (int i = 0; i < n; i++) {
        data[i] = pow(data[i], k);
    }
    return data;
}


typedef struct {
    double* data; int k; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0, 2.0, 3.0}, 1, 3},
    {(double[]){2.0, 3.0, 4.0}, 2, 3},
    {(double[]){1.5, 2.5}, 3, 2},
    {(double[]){0.5, 1.5, 2.5, 3.5}, 4, 4},
    {(double[]){10.0}, 0, 1},
    {(double[]){-1.0, -2.0, -3.0}, 2, 3},
    {(double[]){-2.0, 0.0, 2.0}, 1, 3},
    {(double[]){0.1, 0.2, 0.3}, 2, 3},
    {(double[]){4.0, 9.0, 16.0}, 0, 3},
    {(double[]){1.0}, 5, 1},
    {(double[]){2.0, 4.0, 8.0}, -1, 3},
    {(double[]){1.0, 1.0, 1.0, 1.0}, 10, 4},
    {(double[]){3.0, 6.0}, 2, 2},
    {(double[]){0.25, 0.5, 0.75}, 2, 3},
    {(double[]){-1.5, -0.5, 0.5, 1.5}, 3, 4},
    {(double[]){100.0, 200.0}, 1, 2},
    {(double[]){0.0, 5.0, 10.0}, 2, 3},
    {(double[]){1.2, 2.4, 3.6, 4.8}, 1, 4},
    {(double[]){9.0}, 0, 1},
    {(double[]){0.8, 1.6}, 4, 2},
    {(double[]){-4.0, 4.0}, 2, 2},
    {(double[]){0.01, 0.1, 1.0}, 2, 3},
    {(double[]){7.0, 14.0, 21.0}, 1, 3},
    {(double[]){1.25, 2.5, 5.0}, -2, 3},
    {(double[]){0.0, 1.0, 2.0, 3.0}, 3, 4},
    {(double[]){6.0, 12.0}, 0, 2},
    {(double[]){-3.0, 0.0, 3.0}, 1, 3},
    {(double[]){2.2, 3.3}, 2, 2},
    {(double[]){0.3, 0.6, 0.9}, 1, 3},
    {(double[]){5.0, 25.0, 125.0}, 1, 3}
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
    double* Os = power(tc.data, tc.k, tc.n);
    TestCase Tf_case = change(tc);
    double* Of = power(Tf_case.data, Tf_case.k, Tf_case.n);
    int is_valid = 0;
    double factor = pow(2.0, tc.k);
    int all_match = 1;
    for (int i = 0; i < tc.n; i++) {
        if (fabs(factor * Os[i] - Of[i]) > 1e-9) {
            all_match = 0;
            break;
        }
    }
    if (all_match) {
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