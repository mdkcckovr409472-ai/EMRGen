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


double* square(double data[], int n) {
    double* cp1 = (double*)malloc(n * sizeof(double));
    memcpy(cp1,data,n*sizeof(double));
    for (int i = 0; i < n; i++) {
        cp1[i] = cp1[i] * cp1[i];
    }
    return cp1;
}


typedef struct {
    double* data; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0}, 1},
    {(double[]){2.0, 3.0}, 2},
    {(double[]){0.0}, 1},
    {(double[]){-1.0}, 1},
    {(double[]){-2.0, -3.0}, 2},
    {(double[]){0.5}, 1},
    {(double[]){-0.5}, 1},
    {(double[]){1.5, 2.5}, 2},
    {(double[]){-1.5, -2.5}, 2},
    {(double[]){10.0}, 1},
    {(double[]){-10.0}, 1},
    {(double[]){0.0, 0.0, 0.0}, 3},
    {(double[]){1.0, 0.0, -1.0}, 3},
    {(double[]){2.0, 4.0, 6.0}, 3},
    {(double[]){-2.0, -4.0, -6.0}, 3},
    {(double[]){0.25, 0.75}, 2},
    {(double[]){-0.25, -0.75}, 2},
    {(double[]){100.0, 200.0}, 2},
    {(double[]){-100.0, -200.0}, 2},
    {(double[]){1.0, 2.0, 3.0, 4.0}, 4},
    {(double[]){-1.0, -2.0, -3.0, -4.0}, 4},
    {(double[]){0.1, 0.2, 0.3}, 3},
    {(double[]){-0.1, -0.2, -0.3}, 3},
    {(double[]){5.0}, 1},
    {(double[]){-5.0}, 1},
    {(double[]){1.0, -1.0, 2.0, -2.0}, 4},
    {(double[]){3.14159}, 1},
    {(double[]){-3.14159}, 1},
    {(double[]){1.0, 2.0, 3.0, 4.0, 5.0}, 5},
    {(double[]){-1.0, -2.0, -3.0, -4.0, -5.0}, 5}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    tf.data = (double*)malloc(tf.n * sizeof(double));
    memcpy(tf.data, tc.data, tf.n * sizeof(double));
    for (int i = 0; i < tf.n; i++) {
        tf.data[i] = tf.data[i] * -1.0;
    }
    return tf;
}

int check(TestCase tc) {
    double* Os = square(tc.data, tc.n);
    TestCase Tf_case = change(tc);
    double* Of = square(Tf_case.data, Tf_case.n);
    int is_valid = 1;
    for (int i = 0; i < tc.n; i++) {
        if (Os[i] != Of[i]) {
            is_valid = 0;
            break;
        }
    }
    free(Os);
    free(Of);
    free(Tf_case.data);
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