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
    {1.0, 1.0, 4},
    {2.5, 0.5, 5},
    {0.0, 0.1, 6},
    {10.0, 2.0, 7},
    {0.25, 0.25, 8},
    {5.0, 1.0, 9},
    {1.5, 3.0, 10},
    {8.0, 4.0, 11},
    {0.01, 0.05, 12},
    {15.0, 2.5, 13},
    {0.1, 1.0, 14},
    {4.0, 1.0, 15},
    {20.0, 5.0, 16},
    {0.5, 0.2, 17},
    {12.0, 3.0, 18},
    {0.0, 2.0, 19},
    {7.0, 1.4, 20},
    {0.75, 0.75, 21},
    {30.0, 6.0, 22},
    {0.2, 0.1, 23},
    {9.0, 1.8, 24},
    {0.0, 0.01, 25},
    {6.0, 1.2, 26},
    {1.0, 0.5, 27},
    {25.0, 5.0, 28},
    {0.05, 0.25, 29},
    {3.0, 0.6, 30},
    {18.0, 3.6, 31},
    {0.3, 0.15, 32},
    {11.0, 2.2, 33}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    tf.moment4 = tc.moment4 - 1.0;
    return tf;
}

int check(TestCase tc) {
    double Os = sampleKurtosis(tc.moment4, tc.sampleVariance, tc.size);
    TestCase Tf_case = change(tc);
    double Of = sampleKurtosis(Tf_case.moment4, Tf_case.sampleVariance, Tf_case.size);
    int is_valid = 0;
    if (Os > Of) {
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