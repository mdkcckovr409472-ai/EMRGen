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
    {(double[]){1.0, 2.0, 3.0}, 3},
    {(double[]){0.0, 0.0, 0.0}, 3},
    {(double[]){-1.0, -2.0, -3.0}, 3},
    {(double[]){1.0, -2.0, 3.0, -4.0}, 4},
    {(double[]){1.5, 2.5, 3.5}, 3},
    {(double[]){1.0e-10, 2.0e-10, 3.0e-10}, 3},
    {(double[]){1.0e-15, 2.0e-15, 3.0e-15}, 3},
    {(double[]){1.0e10, 2.0e10, 3.0e10}, 3},
    {(double[]){1.0e15, 2.0e15, 3.0e15}, 3},
    {(double[]){1.304e19}, 1},
    {(double[]){3.834e-20}, 1},
    {(double[]){1.304e19 / 2.0}, 1},
    {(double[]){3.834e-20 * 2.0}, 1},
    {(double[]){1.0, 1.304e19, 1.0}, 3},
    {(double[]){1.0, 3.834e-20, 1.0}, 3},
    {(double[]){1.304e19, 3.834e-20}, 2},
    {(double[]){1.0, 2.0, 1.304e19, 3.834e-20}, 4},
    {(double[]){}, 0},
    {(double[]){0.5}, 1},
    {(double[]){-0.5}, 1},
    {(double[]){100.0, 200.0, 300.0}, 3},
    {(double[]){-100.0, -200.0, -300.0}, 3},
    {(double[]){1.0e-5, 1.0e5}, 2},
    {(double[]){1.0e-8, 1.0e8}, 2},
    {(double[]){1.0, 2.0, 3.0, 4.0, 5.0}, 5},
    {(double[]){-1.0, 2.0, -3.0, 4.0, -5.0}, 5},
    {(double[]){1.1, 2.2, 3.3, 4.4, 5.5, 6.6}, 6},
    {(double[]){1.0e-12, 2.0e-12, 1.0e12, 2.0e12}, 4},
    {(double[]){1.0, 1.304e19 / 10.0, 3.834e-20 * 10.0}, 3},
    {(double[]){1.5e-19, 2.5e-19, 1.5e18, 2.5e18}, 4}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    if (tf.n > 1) {
        std::vector<double> vec(tf.v, tf.v + tf.n);
        std::random_shuffle(vec.begin(), vec.end());
        double* new_v = new double[tf.n];
        std::copy(vec.begin(), vec.end(), new_v);
        tf.v = new_v;
    }
    return tf;
}

int check(TestCase tc) {
    double Os = safeNorm(tc.v, tc.n);
    TestCase Tf_case = change(tc);
    double Of = safeNorm(Tf_case.v, Tf_case.n);
    int is_valid = 0;
    if (Os == Of) {
        is_valid = 1;
    }
    if (Tf_case.v != tc.v) {
        delete[] Tf_case.v;
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