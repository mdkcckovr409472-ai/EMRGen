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


double sampleKurtosis(double moment4, double sampleVariance,int size) {
    int n = size;
    double s2 = sampleVariance;
    double m4 = moment4 * n;
    return m4 * n * (n + 1) / ((n - 1) * (n - 2) * (n - 3) * s2 * s2) - 3.0 * (n - 1) * (n - 1) / ((n - 2) * (n - 3));
}


typedef struct {
    double moment4; double sampleVariance; int size;
} TestCase;

TestCase test_cases[] = {
    {1.0, 2.0, 5},
    {0.0, 1.0, 4},
    {-1.5, 0.5, 6},
    {2.5, 3.0, 8},
    {10.0, 5.0, 10},
    {0.1, 0.2, 7},
    {3.1415, 1.618, 9},
    {-2.0, 4.0, 12},
    {5.5, 2.5, 15},
    {0.0001, 0.0002, 4},
    {-0.75, 0.25, 11},
    {7.2, 3.3, 13},
    {1.23, 4.56, 14},
    {-3.33, 2.22, 16},
    {9.99, 0.99, 18},
    {0.5, 0.5, 20},
    {-0.1, 0.9, 22},
    {4.0, 1.0, 24},
    {2.718, 2.718, 26},
    {-5.5, 5.5, 28},
    {6.0, 0.1, 30},
    {0.333, 0.666, 32},
    {-1.0, 1.0, 34},
    {8.8, 2.2, 36},
    {0.125, 0.875, 38},
    {-2.5, 3.5, 40},
    {3.0, 0.75, 42},
    {1.0, 1.0, 44},
    {-0.5, 2.0, 46},
    {5.0, 0.2, 48}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc; 
    tf.sampleVariance = tc.sampleVariance * 2;
    return tf;
}

int check(TestCase tc) {
    double Os = sampleKurtosis(tc.moment4, tc.sampleVariance, tc.size);
    TestCase Tf_case = change(tc);
    double Of = sampleKurtosis(Tf_case.moment4, Tf_case.sampleVariance, Tf_case.size);
    int is_valid = 0;
    if (Of < Os) {
        is_valid = 1;
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