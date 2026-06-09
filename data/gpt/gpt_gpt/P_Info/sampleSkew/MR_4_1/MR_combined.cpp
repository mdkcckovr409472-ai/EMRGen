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
    {0.0, 1.0, 5},
    {1.0, 1.0, 5},
    {-1.0, 1.0, 5},
    {2.5, 0.5, 5},
    {-2.5, 0.5, 5},
    {0.0, 2.0, 10},
    {1.5, 2.0, 10},
    {-1.5, 2.0, 10},
    {3.0, 3.0, 15},
    {-3.0, 3.0, 15},
    {0.5, 0.2, 3},
    {-0.5, 0.2, 3},
    {1.0, 0.1, 2},
    {0.0, 0.1, 2},
    {5.0, 4.0, 20},
    {-5.0, 4.0, 20},
    {1.2, 0.8, 8},
    {-1.2, 0.8, 8},
    {0.0, 1.5, 1},
    {2.0, 1.5, 1},
    {-2.0, 1.5, 1},
    {0.3, 0.3, 7},
    {-0.3, 0.3, 7},
    {4.5, 2.2, 12},
    {-4.5, 2.2, 12},
    {0.0, 0.01, 6},
    {0.1, 0.01, 6},
    {-0.1, 0.01, 6},
    {3.1415, 1.618, 9},
    {-3.1415, 1.618, 9}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    tf.moment3 = tc.moment3 / 2.0;
    return tf;
}

int check(TestCase tc) {
    double Os = sampleSkew(tc.moment3, tc.sampleVariance, tc.size);
    TestCase Tf_case = change(tc);
    double Of = sampleSkew(Tf_case.moment3, Tf_case.sampleVariance, Tf_case.size);
    int is_valid = 0;
    if (fabs(2.0 * Of - Os) < 1e-8) {
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