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
    { (double[]){}, 0 },
    { (double[]){0.0}, 1 },
    { (double[]){3.5}, 1 },
    { (double[]){-2.2}, 1 },
    { (double[]){0.0, 0.0}, 2 },
    { (double[]){1.1, 4.4}, 2 },
    { (double[]){-5.5, -3.3}, 2 },
    { (double[]){2.0, -1.5, 3.0}, 3 },
    { (double[]){0.25, -0.75, 1.5}, 3 },
    { (double[]){7.7, 7.7, 2.2, 2.2}, 4 },
    { (double[]){-4.0, 5.5, -3.3, 2.2, -1.1}, 5 },
    { (double[]){1.0, -2.0, 3.0, -4.0, 5.0, -6.0}, 6 },
    { (double[]){-0.5, 0.5, -1.5, 1.5, -2.5, 2.5, -3.5}, 7 },
    { (double[]){4.4, 4.4, 4.4, 4.4}, 4 },
    { (double[]){-1.0, 2.0, -3.0, 4.0, -5.0, 6.0}, 6 },
    { (double[]){9.9, -8.8, 7.7, -6.6, 5.5, -4.4, 3.3, -2.2}, 8 },
    { (double[]){0.1, 0.2, 0.3, 0.4, 0.5}, 5 },
    { (double[]){-0.9, -0.8, -0.7, -0.6, -0.5}, 5 },
    { (double[]){1.2, -1.2, 2.4, -2.4, 3.6, -3.6}, 6 },
    { (double[]){5.0, 0.0, -5.0, 0.0, 5.0}, 5 },
    { (double[]){9.5, 8.5, 7.5, 6.5, 5.5}, 5 },
    { (double[]){-9.5, -8.5, -7.5, -6.5, -5.5}, 5 },
    { (double[]){2.2, -2.2, 3.3, -3.3, 4.4}, 5 },
    { (double[]){0.0, 1.1, 0.0, 1.1, 0.0}, 5 },
    { (double[]){3.0, 2.0, 1.0, 1.0, 2.0, 3.0}, 6 },
    { (double[]){6.0, 5.0, 4.0, 3.0, 2.0, 1.0}, 6 },
    { (double[]){-0.25, 0.75, -1.25, 1.75, -2.25, 2.75}, 6 },
    { (double[]){0.33, -0.66, 0.99, -1.32, 1.65, -1.98}, 6 },
    { (double[]){4.1, -3.2, 2.3, -1.4, 0.5}, 5 },
    { (double[]){-2.7, 3.8, -4.9, 5.0, -6.1}, 5 }
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    for (int i = 0; i < tf.n; i++) {
        tf.data[i] = tf.data[i] * 2.0;
    }
    return tf;
}

int check(TestCase tc) {
    double* Os = square(tc.data, tc.n);
    if (Os == NULL) {
        return 0;
    }
    TestCase Tf_case = change(tc);
    double* Of = square(Tf_case.data, Tf_case.n);
    if (Of == NULL) {
        free(Os);
        return 0;
    }
    int is_valid = 1;
    for (int i = 0; i < tc.n; i++) {
        if (Of[i] != 4.0 * Os[i]) {
            is_valid = 0;
            break;
        }
    }
    free(Os);
    free(Of);
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