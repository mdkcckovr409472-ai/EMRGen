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


double evaluateNewton(double a[], double c[], double z, int nc) {
    int n = nc - 1;
    double value = a[n];
    for (int i = n - 1; i >= 0; i--) {
        value = a[i] + (z - c[i]) * value;
    }
    return value;
}


typedef struct {
    double* a; double* c; double z; int nc;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0}, (double[]){0.0}, 0.5, 1},
    {(double[]){2.0, 3.0}, (double[]){1.0, 2.0}, 1.5, 2},
    {(double[]){1.0, 0.0, -1.0}, (double[]){-1.0, 0.0, 1.0}, 0.0, 3},
    {(double[]){5.0}, (double[]){10.0}, 10.0, 1},
    {(double[]){0.0, 0.0, 0.0}, (double[]){1.0, 2.0, 3.0}, 2.5, 3},
    {(double[]){-2.0, -1.0}, (double[]){-3.0, -2.0}, -2.5, 2},
    {(double[]){1.5, 2.5, 3.5}, (double[]){0.1, 0.2, 0.3}, 0.25, 3},
    {(double[]){10.0, 20.0, 30.0, 40.0}, (double[]){1.0, 2.0, 3.0, 4.0}, 2.5, 4},
    {(double[]){0.1, 0.2, 0.3}, (double[]){-0.5, 0.0, 0.5}, 0.1, 3},
    {(double[]){-1.0, 1.0, -1.0, 1.0}, (double[]){-2.0, -1.0, 0.0, 1.0}, -0.5, 4},
    {(double[]){100.0}, (double[]){50.0}, 49.9, 1},
    {(double[]){3.14, 2.71}, (double[]){0.0, 1.0}, 0.5, 2},
    {(double[]){1.0, 2.0, 1.0}, (double[]){-1.0, 0.0, 1.0}, 0.0, 3},
    {(double[]){7.0, 8.0, 9.0, 10.0, 11.0}, (double[]){2.0, 3.0, 4.0, 5.0, 6.0}, 4.5, 5},
    {(double[]){0.0}, (double[]){999.0}, 1000.0, 1},
    {(double[]){-5.0, 0.0, 5.0}, (double[]){-10.0, 0.0, 10.0}, 5.0, 3},
    {(double[]){2.0, 4.0, 6.0, 8.0}, (double[]){0.5, 1.0, 1.5, 2.0}, 1.25, 4},
    {(double[]){1.0, 1.0, 1.0, 1.0, 1.0}, (double[]){0.0, 1.0, 2.0, 3.0, 4.0}, 2.0, 5},
    {(double[]){-3.0, -2.0, -1.0}, (double[]){1.0, 2.0, 3.0}, 2.5, 3},
    {(double[]){9.8}, (double[]){4.9}, 9.8, 1},
    {(double[]){1.0, 0.5, 0.25}, (double[]){0.0, 1.0, 2.0}, 1.5, 3},
    {(double[]){12.0, 24.0, 36.0}, (double[]){3.0, 6.0, 9.0}, 7.5, 3},
    {(double[]){0.0, 1.0, 0.0}, (double[]){-2.0, 0.0, 2.0}, 1.0, 3},
    {(double[]){6.0, 7.0}, (double[]){-1.0, 1.0}, 0.0, 2},
    {(double[]){-10.0, 10.0, -10.0}, (double[]){-5.0, 0.0, 5.0}, 0.0, 3},
    {(double[]){2.2, 3.3, 4.4, 5.5}, (double[]){1.1, 2.2, 3.3, 4.4}, 2.2, 4},
    {(double[]){0.0, 0.0}, (double[]){100.0, 200.0}, 150.0, 2},
    {(double[]){8.0, 6.0, 4.0, 2.0}, (double[]){1.0, 2.0, 3.0, 4.0}, 2.5, 4},
    {(double[]){1.618, 2.718, 3.142}, (double[]){0.618, 1.718, 2.142}, 1.0, 3},
    {(double[]){15.0, 30.0, 45.0}, (double[]){5.0, 10.0, 15.0}, 12.0, 3}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    double m = 2.0; // 非零常数，示例值
    int nc = tf.nc;
    tf.a = new double[nc];
    for (int i = 0; i < nc; i++) {
        tf.a[i] = tc.a[i] / m;
    }
    return tf;
}

int check(TestCase tc) {
    double Os = evaluateNewton(tc.a, tc.c, tc.z, tc.nc);
    TestCase Tf_case = change(tc);
    double Of = evaluateNewton(Tf_case.a, Tf_case.c, Tf_case.z, Tf_case.nc);
    int is_valid = 0;
    double m = 2.0;
    if (fabs(Os / m - Of) < 1e-9) {
        is_valid = 1;
    }
    delete[] Tf_case.a;
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