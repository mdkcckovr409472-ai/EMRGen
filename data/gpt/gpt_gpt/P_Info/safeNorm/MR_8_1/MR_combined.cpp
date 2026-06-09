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


double safeNorm(double v[], int n) {
    double rdwarf = 3.834e-20;
    double rgiant = 1.304e+19;
    double s1 = 0;
    double s2 = 0;
    double s3 = 0;
    double x1max = 0;
    double x3max = 0;
    double floatn = n;
    double agiant = rgiant / floatn;
    
    for (int i = 0; i < n; i++) {
        double xabs = abs(v[i]);
        if (xabs < rdwarf || xabs > agiant) {
            if (xabs > rdwarf) {
                if (xabs > x1max) {
                    double r = x1max / xabs;
                    s1 = 1 + s1 * r * r;
                    x1max = xabs;
                } else {
                    double r = xabs / x1max;
                    s1 += r * r;
                }
            } else {
                if (xabs > x3max) {
                    double r = x3max / xabs;
                    s3 = 1 + s3 * r * r;
                    x3max = xabs;
                } else {
                    if (xabs != 0) {
                        double r = xabs / x3max;
                        s3 += r * r;
                    }
                }
            }
        } else {
            s2 += xabs * xabs;
        }
    }
    double norm;
    if (s1 != 0) {
        norm = x1max * sqrt(s1 + s2 / x1max / x1max);
    } else {
        if (s2 == 0) {
            norm = x3max * sqrt(s3);
        } else {
            if (s2 >= x3max) {
                norm = sqrt(s2 * (1 + x3max / s2 * (x3max * s3)));
            } else {
                norm = sqrt(x3max * (s2 / x3max + x3max * s3));
            }
        }
    }
    return norm;
}


typedef struct {
    double* v; int n;
} TestCase;

TestCase test_cases[] = {
    { (double[]){0.0}, 1 },
    { (double[]){}, 0 },
    { (double[]){-3.5, 2.1, 0.0, 4.8}, 4 },
    { (double[]){1e-10, -2e-10, 3e-10}, 3 },
    { (double[]){5.0, -5.0, 5.0, -5.0, 5.0}, 5 },
    { (double[]){123.456, -987.654}, 2 },
    { (double[]){0.001, 0.002, 0.003, 0.004}, 4 },
    { (double[]){-0.1, 0.2, -0.3, 0.4, -0.5}, 5 },
    { (double[]){7.89, 0.0, -7.89}, 3 },
    { (double[]){1000.0, -1000.0, 500.0}, 3 },
    { (double[]){0.000001, 0.000002, 0.000003}, 3 },
    { (double[]){-250.0, 250.0, -125.0, 125.0}, 4 },
    { (double[]){3.14, 2.71, 1.62, 0.577, 1.414}, 5 },
    { (double[]){-0.0005, 0.0005}, 2 },
    { (double[]){42.0}, 1 },
    { (double[]){-42.0, 42.0}, 2 },
    { (double[]){0.9, 1.1, 0.95, 1.05}, 4 },
    { (double[]){-9999.9, 9999.9, -0.01, 0.01}, 4 },
    { (double[]){0.123, -0.456, 0.789}, 3 },
    { (double[]){-1e5, 1e5, 0.0}, 3 },
    { (double[]){0.333, 0.666, 0.999}, 3 },
    { (double[]){-3.3, 3.3, -6.6, 6.6}, 4 },
    { (double[]){0.05, -0.05, 0.15, -0.15, 0.25}, 5 },
    { (double[]){500.5, -500.5, 250.25}, 3 },
    { (double[]){-0.000001, 0.000002, -0.000003, 0.000004}, 4 },
    { (double[]){2.71828, -2.71828, 3.14159}, 3 },
    { (double[]){-0.777, 0.777, -0.888, 0.888}, 4 },
    { (double[]){12345.6, -12345.6, 0.0, 1.0}, 4 },
    { (double[]){0.0001, 0.0002, 0.0003, 0.0004, 0.0005}, 5 },
    { (double[]){-50.0, 0.0, 50.0, -25.0, 25.0}, 5 }
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    // Allocate new array for follow-up input to avoid modifying the original input array
    double* new_v = new double[tc.n];
    for (int i = 0; i < tc.n; i++) {
        new_v[i] = tc.v[i];
    }
    if (tc.n > 0) {
        new_v[0] = new_v[0] * 2;
    }
    tf.v = new_v;
    return tf;
}

int check(TestCase tc) {
    double Os = safeNorm(tc.v, tc.n);

    TestCase Tf_case = change(tc);
    double Of = safeNorm(Tf_case.v, Tf_case.n);

    int is_valid = 0;
    if (Os <= Of) {
        is_valid = 1;
    }

    delete[] Tf_case.v;

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