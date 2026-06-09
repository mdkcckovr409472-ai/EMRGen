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
    {(double[]){1.0, 2.0, 3.0}, (double[]){10.0, 20.0, 30.0}, 2.5, 3},
    {(double[]){5.0, -1.0, 3.5, 0.0}, (double[]){0.0, 1.0, -1.0, 2.0}, -0.5, 4},
    {(double[]){0.0, 10.0}, (double[]){5.0, 15.0}, 7.0, 2},
    {(double[]){-3.2, 4.1, 2.5, -1.0, 8.0}, (double[]){1.0, 2.0, 3.0, 4.0, 5.0}, 0.0, 5},
    {(double[]){100.0, -50.0, 25.0}, (double[]){-10.0, 20.0, -30.0}, 60.0, 3},
    {(double[]){0.5, -0.5, 1.5, -1.5, 2.5, -2.5}, (double[]){10.0, 9.0, 8.0, 7.0, 6.0, 5.0}, 0.0, 6},
    {(double[]){3.14}, (double[]){2.71}, 3.0, 1},
    {(double[]){1.1, 2.2, 3.3, 4.4}, (double[]){4.4, 3.3, 2.2, 1.1}, 2.0, 4},
    {(double[]){-10.0, -5.0, 0.0, 5.0, 10.0}, (double[]){0.0, 1.0, 2.0, 3.0, 4.0}, -3.0, 5},
    {(double[]){0.01, 0.02, 0.03}, (double[]){1000.0, -1000.0, 500.0}, 0.025, 3},
    {(double[]){-100.0, 100.0}, (double[]){0.5, -0.5}, 0.0, 2},
    {(double[]){7.0, 3.0, -2.0, 9.0}, (double[]){-7.0, 3.0, 2.0, -9.0}, 5.0, 4},
    {(double[]){2.0, 8.0, 5.0, 1.0, 7.0}, (double[]){1.5, -1.5, 2.5, -2.5, 0.0}, 6.0, 5},
    {(double[]){-0.5, 0.5, 1.5}, (double[]){0.0, 0.0, 0.0}, 0.0, 3},
    {(double[]){10.0, 20.0, 30.0, 40.0, 50.0, 60.0}, (double[]){1.0, 2.0, 3.0, 4.0, 5.0, 6.0}, 35.0, 6},
    {(double[]){-3.0, -1.0, 2.0, 4.0}, (double[]){4.0, -2.0, 0.0, 1.0}, -2.0, 4},
    {(double[]){0.0, 1.0, 4.0, 9.0, 16.0}, (double[]){5.0, 4.0, 3.0, 2.0, 1.0}, 3.0, 5},
    {(double[]){0.5, 0.5001}, (double[]){1.0, 2.0}, 0.5, 2},
    {(double[]){-100.0, 0.0, 100.0}, (double[]){10.0, 0.0, -10.0}, 50.0, 3},
    {(double[]){0.2, -0.2, 0.4, -0.4}, (double[]){2.0, -2.0, 2.5, -2.5}, 0.0, 4},
    {(double[]){3.14, 2.71, 1.62, 0.58, -0.5}, (double[]){-1.0, -2.0, -3.0, -4.0, -5.0}, 1.0, 5},
    {(double[]){9.0, 3.0, 6.0}, (double[]){0.0, 1.0, 2.0}, 4.5, 3},
    {(double[]){-5.0, -3.0, -1.0, 1.0, 3.0, 5.0}, (double[]){5.0, 4.0, 3.0, 2.0, 1.0, 0.0}, 0.0, 6},
    {(double[]){1.5, 2.5, 3.5, 4.5}, (double[]){10.0, 20.0, 30.0, 40.0}, 2.0, 4},
    {(double[]){-0.1, 0.1}, (double[]){0.5, -0.5}, 0.0, 2},
    {(double[]){5.0, -5.0, 10.0, -10.0, 15.0}, (double[]){1.0, 2.0, 3.0, 4.0, 5.0}, -7.0, 5},
    {(double[]){0.001, 0.002, 0.003}, (double[]){100.0, 200.0, 300.0}, 0.0025, 3},
    {(double[]){-2.0, 2.0, -1.0, 1.0}, (double[]){-10.0, 10.0, -20.0, 20.0}, 0.0, 4},
    {(double[]){-0.75, 0.25, 1.25, 2.25, 3.25}, (double[]){0.0, 1.0, 2.0, 3.0, 4.0}, 1.0, 5},
    {(double[]){8.0, 3.0, -2.0}, (double[]){-3.0, 0.0, 3.0}, 5.0, 3}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    // Reuse original arrays; create a new y array to modify
    double* new_y = new double[tc.n];
    for (int i = 0; i < tc.n; i++) {
        new_y[i] = tc.y[i];
    }
    // Find nearest index same as in evaluateInternal logic
    int nearest = 0;
    double min_dist = INFINITY;
    for (int i = 0; i < tc.n; i++) {
        double dist = abs(tc.z - tc.x[i]);
        if (dist < min_dist) {
            nearest = i;
            min_dist = dist;
        }
    }
    // Find max value of y array
    double max_val = new_y[0];
    for (int i = 1; i < tc.n; i++) {
        if (new_y[i] > max_val) max_val = new_y[i];
    }
    // Set new_y[nearest] to max_val
    new_y[nearest] = max_val;
    tf.y = new_y;
    return tf;
}

int check(TestCase tc) {
    // Source output Os
    double Os = evaluateInternal(tc.x, tc.y, tc.z, tc.n);
    // Follow-up test case
    TestCase Tf_case = change(tc);
    double Of = evaluateInternal(Tf_case.x, Tf_case.y, Tf_case.z, Tf_case.n);
    // Metamorphic relation: Of >= Os
    int is_valid = (Of >= Os) ? 1 : 0;
    // Free dynamically allocated memory in Tf_case (only y allocated in change)
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