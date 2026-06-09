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


double* calculateDifferences(double x[], double y[], int n){

    double* z = (double*)malloc(n * sizeof(double));

    for (int i = 0; i < n; i++)
    {
        z[i] = y[i] - x[i];
    }
    
    return z;
}


typedef struct {
    double* x; double* y; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0, 2.0, 3.0}, (double[]){4.0, 5.0, 6.0}, 3},
    {(double[]){0.0, 0.0}, (double[]){0.0, 0.0}, 2},
    {(double[]){-1.5, 2.7}, (double[]){3.2, -4.1}, 2},
    {(double[]){10.0}, (double[]){20.0}, 1},
    {(double[]){1.1, 2.2, 3.3, 4.4}, (double[]){5.5, 6.6, 7.7, 8.8}, 4},
    {(double[]){100.0, 200.0, 300.0}, (double[]){50.0, 150.0, 250.0}, 3},
    {(double[]){0.5, 1.5, 2.5, 3.5, 4.5}, (double[]){5.5, 6.5, 7.5, 8.5, 9.5}, 5},
    {(double[]){-10.0, -20.0}, (double[]){-5.0, -15.0}, 2},
    {(double[]){3.14, 6.28}, (double[]){1.57, 3.14}, 2},
    {(double[]){2.0, 4.0, 8.0, 16.0}, (double[]){1.0, 2.0, 4.0, 8.0}, 4},
    {(double[]){0.1, 0.2, 0.3}, (double[]){0.4, 0.5, 0.6}, 3},
    {(double[]){25.0, 50.0, 75.0}, (double[]){100.0, 125.0, 150.0}, 3},
    {(double[]){-1.0, 0.0, 1.0}, (double[]){1.0, 0.0, -1.0}, 3},
    {(double[]){12.34, 56.78}, (double[]){98.76, 43.21}, 2},
    {(double[]){1.0, 1.0, 1.0, 1.0}, (double[]){2.0, 2.0, 2.0, 2.0}, 4},
    {(double[]){7.0, 14.0, 21.0}, (double[]){3.0, 6.0, 9.0}, 3},
    {(double[]){0.01, 0.02, 0.03}, (double[]){0.05, 0.06, 0.07}, 3},
    {(double[]){-100.0, 100.0}, (double[]){0.0, 200.0}, 2},
    {(double[]){9.8, 4.9}, (double[]){0.0, 9.8}, 2},
    {(double[]){1.618, 2.718, 3.142}, (double[]){0.618, 1.718, 2.142}, 3},
    {(double[]){5.0, 10.0, 15.0, 20.0, 25.0}, (double[]){30.0, 35.0, 40.0, 45.0, 50.0}, 5},
    {(double[]){2.5, 5.0, 7.5}, (double[]){10.0, 12.5, 15.0}, 3},
    {(double[]){-3.0, -2.0, -1.0, 0.0}, (double[]){0.0, 1.0, 2.0, 3.0}, 4},
    {(double[]){1000.0, 2000.0}, (double[]){500.0, 1500.0}, 2},
    {(double[]){0.25, 0.5, 0.75, 1.0}, (double[]){1.25, 1.5, 1.75, 2.0}, 4},
    {(double[]){8.0, 6.0, 4.0, 2.0}, (double[]){1.0, 3.0, 5.0, 7.0}, 4},
    {(double[]){1.0, 2.0, 3.0, 4.0, 5.0, 6.0}, (double[]){6.0, 5.0, 4.0, 3.0, 2.0, 1.0}, 6},
    {(double[]){0.0, 10.0, 20.0}, (double[]){5.0, 15.0, 25.0}, 3},
    {(double[]){-7.5, 0.0, 7.5}, (double[]){-15.0, 0.0, 15.0}, 3},
    {(double[]){99.9, 88.8, 77.7}, (double[]){11.1, 22.2, 33.3}, 3}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    double k = 5.0;
    if (tf.y != nullptr) {
        for (int i = 0; i < tf.n; i++) {
            tf.y[i] += k;
        }
    }
    return tf;
}

int check(TestCase tc) {
    double* Os = calculateDifferences(tc.x, tc.y, tc.n);
    if (Os == nullptr) {
        return 0;
    }

    TestCase Tf_case = change(tc);
    double* Of = calculateDifferences(Tf_case.x, Tf_case.y, Tf_case.n);
    if (Of == nullptr) {
        free(Os);
        return 0;
    }

    int is_valid = 1;
    double k = 5.0;
    for (int i = 0; i < tc.n; i++) {
        if (Os[i] + k != Of[i]) {
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