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


double* standardize(double data[], int n) {
    double* cp1 = (double*)malloc(n * sizeof(double));
    memcpy(cp1,data,n*sizeof(double));
    double sum = 0;
    double sumSq = 0;
    for (int i = 0; i < n; i++) {
        sum += cp1[i];
        sumSq += cp1[i] * cp1[i];
    }
    double mean = sum / n;
    double sd = sqrt((sumSq - mean * sum) / n);
    for (int i = 0; i < n; i++) {
        cp1[i] = (cp1[i] - mean) / sd;
    }
    return cp1;
}


typedef struct {
    double* data; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0}, 1},
    {(double[]){0.0, 0.0}, 2},
    {(double[]){1.0, 2.0, 3.0}, 3},
    {(double[]){-1.0, 0.0, 1.0}, 3},
    {(double[]){10.5, 20.3, 30.7}, 3},
    {(double[]){-5.2, -3.1, -1.8}, 3},
    {(double[]){2.5, 2.5, 2.5, 2.5}, 4},
    {(double[]){1.1, 2.2, 3.3, 4.4, 5.5}, 5},
    {(double[]){-10.0, -5.0, 0.0, 5.0, 10.0}, 5},
    {(double[]){100.0, 200.0, 300.0}, 3},
    {(double[]){0.001, 0.002, 0.003}, 3},
    {(double[]){-0.5, 0.0, 0.5}, 3},
    {(double[]){3.14, 6.28, 9.42}, 3},
    {(double[]){1.0, 4.0, 9.0, 16.0}, 4},
    {(double[]){2.0, 4.0, 8.0, 16.0, 32.0}, 5},
    {(double[]){-2.0, -1.0, 0.0, 1.0, 2.0}, 5},
    {(double[]){7.0}, 1},
    {(double[]){1.5, 3.0, 4.5, 6.0}, 4},
    {(double[]){0.1, 0.2, 0.3, 0.4, 0.5, 0.6}, 6},
    {(double[]){-20.0, -10.0, 0.0, 10.0, 20.0}, 5},
    {(double[]){50.0, 60.0, 70.0, 80.0, 90.0}, 5},
    {(double[]){-3.0, -2.0, -1.0}, 3},
    {(double[]){12.34, 45.67, 78.90}, 3},
    {(double[]){0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0}, 7},
    {(double[]){-7.5, -2.5, 2.5, 7.5}, 4},
    {(double[]){1.0, 1.0, 2.0, 3.0, 5.0, 8.0}, 6},
    {(double[]){0.25, 0.5, 0.75, 1.0}, 4},
    {(double[]){-100.0, 0.0, 100.0}, 3},
    {(double[]){9.8, 8.7, 7.6, 6.5}, 4},
    {(double[]){2.718, 3.142, 1.618}, 3}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    double* new_data = (double*)malloc(tf.n * sizeof(double));
    double k = 2.0;
    for (int i = 0; i < tf.n; i++) {
        new_data[i] = tf.data[i] * k;
    }
    tf.data = new_data;
    return tf;
}

int check(TestCase tc) {
    double* Os = standardize(tc.data, tc.n);
    TestCase Tf_case = change(tc);
    double* Of = standardize(Tf_case.data, Tf_case.n);
    int is_valid = 1;
    for (int i = 0; i < tc.n; i++) {
        if (fabs(Os[i] - Of[i]) > 1e-12) {
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