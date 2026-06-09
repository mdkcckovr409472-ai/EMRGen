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


double evaluateInternal(double x[], double y[], double z, int n) {
    int nearest = 0;
    double c[1000];
    double d[1000];
    double min_dist = INFINITY;
    for (int i = 0; i < n; i++) {
        c[i] = y[i];
        d[i] = y[i];
        double dist = abs(z - x[i]);
        if (dist < min_dist) {
            nearest = i;
            min_dist = dist;
        }
    }
    double value = y[nearest];
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < n - i; j++) {
            double tc = x[j] - z;
            double td = x[i + j] - z;
            double divider = x[j] - x[i + j];
            double w = (c[j + 1] - d[j]) / divider;
            c[j] = tc * w;
            d[j] = td * w;
        }
        if (nearest < 0.5 * (n - i + 1)) {
            value += c[nearest];
        } else {
            nearest--;
            value += d[nearest];
        }
    }
    return value;
}


typedef struct {
    double* x; double* y; double z; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0, 2.0, 3.0}, (double[]){4.0, 5.0, 6.0}, 2.5, 3},
    {(double[]){0.0}, (double[]){0.0}, 0.0, 1},
    {(double[]){-1.0, 0.0, 1.0}, (double[]){-1.0, 0.0, 1.0}, 0.5, 3},
    {(double[]){10.0, 20.0, 30.0, 40.0}, (double[]){1.0, 2.0, 3.0, 4.0}, 25.0, 4},
    {(double[]){5.0}, (double[]){10.0}, 5.0, 1},
    {(double[]){1.5, 2.5, 3.5}, (double[]){2.0, 3.0, 4.0}, 2.0, 3},
    {(double[]){0.1, 0.2, 0.3, 0.4, 0.5}, (double[]){0.5, 0.4, 0.3, 0.2, 0.1}, 0.25, 5},
    {(double[]){100.0, 200.0}, (double[]){50.0, 60.0}, 150.0, 2},
    {(double[]){-5.0, -4.0, -3.0, -2.0, -1.0}, (double[]){25.0, 16.0, 9.0, 4.0, 1.0}, -2.5, 5},
    {(double[]){2.0, 4.0, 6.0, 8.0}, (double[]){1.0, 1.5, 2.0, 2.5}, 5.0, 4},
    {(double[]){1.0, 2.0}, (double[]){3.0, 4.0}, 1.5, 2},
    {(double[]){3.0, 1.0, 4.0, 2.0}, (double[]){30.0, 10.0, 40.0, 20.0}, 2.5, 4},
    {(double[]){0.0, 0.5, 1.0, 1.5}, (double[]){0.0, 0.25, 1.0, 2.25}, 0.8, 4},
    {(double[]){-10.0, 0.0, 10.0}, (double[]){100.0, 0.0, 100.0}, -5.0, 3},
    {(double[]){1.1, 2.2, 3.3, 4.4, 5.5}, (double[]){2.2, 4.4, 6.6, 8.8, 11.0}, 3.0, 5},
    {(double[]){7.0, 14.0, 21.0}, (double[]){2.0, 3.0, 4.0}, 10.0, 3},
    {(double[]){0.25, 0.5, 0.75}, (double[]){4.0, 2.0, 1.33333}, 0.6, 3},
    {(double[]){8.0, 6.0, 7.0, 5.0, 9.0}, (double[]){64.0, 36.0, 49.0, 25.0, 81.0}, 7.5, 5},
    {(double[]){-2.0, -1.0, 0.0, 1.0, 2.0}, (double[]){4.0, 1.0, 0.0, 1.0, 4.0}, -0.5, 5},
    {(double[]){12.0, 24.0, 36.0}, (double[]){144.0, 576.0, 1296.0}, 20.0, 3},
    {(double[]){1.0, 1.0, 2.0, 3.0}, (double[]){1.0, 2.0, 3.0, 4.0}, 1.5, 4},
    {(double[]){9.0, 10.0, 11.0, 12.0}, (double[]){81.0, 100.0, 121.0, 144.0}, 10.5, 4},
    {(double[]){0.0, 2.0, 4.0, 6.0}, (double[]){0.0, 4.0, 16.0, 36.0}, 3.0, 4},
    {(double[]){5.0, 10.0, 15.0}, (double[]){25.0, 100.0, 225.0}, 12.0, 3},
    {(double[]){-3.0, -1.0, 1.0, 3.0}, (double[]){9.0, 1.0, 1.0, 9.0}, 0.0, 4},
    {(double[]){6.0, 12.0, 18.0, 24.0}, (double[]){1.0, 2.0, 3.0, 4.0}, 15.0, 4},
    {(double[]){2.5, 5.0, 7.5}, (double[]){6.25, 25.0, 56.25}, 4.0, 3},
    {(double[]){1.0, 3.0, 5.0, 7.0, 9.0}, (double[]){2.0, 4.0, 6.0, 8.0, 10.0}, 4.0, 5},
    {(double[]){0.0, 1.0, 2.0, 3.0, 4.0, 5.0}, (double[]){0.0, 1.0, 8.0, 27.0, 64.0, 125.0}, 2.5, 6}
};
int num_test_cases = 29;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    double k = 5.0;
    tf.y = new double[tc.n];
    for (int i = 0; i < tc.n; i++) {
        tf.y[i] = tc.y[i] + k;
    }
    return tf;
}

int check(TestCase tc) {
    double Os = evaluateInternal(tc.x, tc.y, tc.z, tc.n);
    TestCase Tf_case = change(tc);
    double Of = evaluateInternal(Tf_case.x, Tf_case.y, Tf_case.z, Tf_case.n);
    int is_valid = 0;
    double k = 5.0;
    if (fabs(Os + k - Of) < 1e-9) {
        is_valid = 1;
    }
    delete[] Tf_case.y;
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