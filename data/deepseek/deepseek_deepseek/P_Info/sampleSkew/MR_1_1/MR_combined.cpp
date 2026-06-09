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


double sampleSkew(double moment3, double sampleVariance,int size) {
    int n = size;
    double s = sqrt(sampleVariance);
    double m3 = moment3 * n;

    return n * m3 / ((n - 1) * (n - 2) * s * s * s);
}


typedef struct {
    double moment3; double sampleVariance; int size;
} TestCase;

TestCase test_cases[] = {
    {0.0, 1.0, 10},
    {1.0, 1.0, 10},
    {-1.0, 1.0, 10},
    {2.5, 4.0, 20},
    {-2.5, 4.0, 20},
    {0.0, 0.25, 15},
    {0.1, 0.01, 30},
    {-0.1, 0.01, 30},
    {10.0, 25.0, 100},
    {-10.0, 25.0, 100},
    {0.0, 100.0, 50},
    {50.0, 100.0, 50},
    {-50.0, 100.0, 50},
    {1.5, 2.25, 25},
    {-1.5, 2.25, 25},
    {0.0, 1.0e-6, 1000},
    {1.0e-6, 1.0e-6, 1000},
    {-1.0e-6, 1.0e-6, 1000},
    {100.0, 10000.0, 200},
    {-100.0, 10000.0, 200},
    {0.0, 0.0, 5},
    {0.5, 1.0, 3},
    {-0.5, 1.0, 3},
    {0.0, 0.1, 7},
    {0.2, 0.1, 7},
    {-0.2, 0.1, 7},
    {3.14159, 2.71828, 42},
    {-3.14159, 2.71828, 42},
    {0.0, 9.0, 12},
    {1.0, 9.0, 12}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    double k = 2.0;
    tf.moment3 = tc.moment3 * k;
    return tf;
}

int check(TestCase tc) {
    double Os = sampleSkew(tc.moment3, tc.sampleVariance, tc.size);
    TestCase Tf_case = change(tc);
    double Of = sampleSkew(Tf_case.moment3, Tf_case.sampleVariance, Tf_case.size);
    int is_valid = 0;
    double k = 2.0;
    if (fabs(k * Os - Of) < 1e-9) {
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