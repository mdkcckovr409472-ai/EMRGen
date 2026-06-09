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


double quantile(double sortedElements[], double phi, int n) {      
    double index = phi * (n - 1);
    int lhs = (int) index;
    double delta = index - lhs;
    double result;
    if (n == 0) {
        return 0.0;
    }
    if (lhs == n - 1) {
        result = sortedElements[lhs];
    } else {
        result = (1 - delta) * sortedElements[lhs] + delta * sortedElements[lhs + 1];
    }
    return result;
}


typedef struct {
    double* sortedElements; double phi; int n;
} TestCase;

TestCase test_cases[] = {
    { (double[]){}, 0.5, 0 },
    { (double[]){5.0}, 0.0, 1 },
    { (double[]){5.0}, 0.5, 1 },
    { (double[]){5.0}, 1.0, 1 },
    { (double[]){1.0, 3.0}, 0.0, 2 },
    { (double[]){1.0, 3.0}, 1.0, 2 },
    { (double[]){1.0, 3.0}, 0.5, 2 },
    { (double[]){-2.5, 0.0, 4.5}, 0.0, 3 },
    { (double[]){-2.5, 0.0, 4.5}, 1.0, 3 },
    { (double[]){-2.5, 0.0, 4.5}, 0.5, 3 },
    { (double[]){1.0, 2.0, 3.0, 4.0}, 0.25, 4 },
    { (double[]){1.0, 2.0, 3.0, 4.0}, 0.75, 4 },
    { (double[]){1.0, 1.0, 2.0, 2.0, 3.0}, 0.4, 5 },
    { (double[]){-10.0, -5.0, 0.0, 5.0, 10.0}, 0.6, 5 },
    { (double[]){0.1, 0.4, 0.9, 2.5, 5.0, 9.0}, 0.33, 6 },
    { (double[]){0.1, 0.4, 0.9, 2.5, 5.0, 9.0}, 0.9, 6 },
    { (double[]){-3.2, -1.1, 0.0, 0.5, 2.2, 3.8, 7.7}, 0.123, 7 },
    { (double[]){-3.2, -1.1, 0.0, 0.5, 2.2, 3.8, 7.7}, 0.987, 7 },
    { (double[]){1.5, 1.5, 2.5, 3.5, 3.5, 4.5, 5.5, 5.5}, 0.5, 8 },
    { (double[]){1.5, 1.5, 2.5, 3.5, 3.5, 4.5, 5.5, 5.5}, 0.0, 8 },
    { (double[]){1.5, 1.5, 2.5, 3.5, 3.5, 4.5, 5.5, 5.5}, 1.0, 8 },
    { (double[]){-8.0, -3.0, -1.0, 0.0, 1.0, 4.0, 6.0, 9.0, 12.0}, 0.45, 9 },
    { (double[]){-8.0, -3.0, -1.0, 0.0, 1.0, 4.0, 6.0, 9.0, 12.0}, 0.55, 9 },
    { (double[]){0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0}, 0.2, 10 },
    { (double[]){0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0}, 0.8, 10 },
    { (double[]){0.01, 0.02, 0.05, 0.1, 0.2, 0.4, 0.8, 1.6, 3.2, 6.4}, 0.75, 10 },
    { (double[]){0.01, 0.02, 0.05, 0.1, 0.2, 0.4, 0.8, 1.6, 3.2, 6.4}, 0.33, 10 },
    { (double[]){-5.0, -3.0, -1.0, 0.0, 2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0}, 0.5, 11 },
    { (double[]){-5.0, -3.0, -1.0, 0.0, 2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0}, 0.999, 11 },
    { (double[]){0.0, 0.5, 1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0, 5.5}, 0.001, 12 }
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    if (tf.phi - 0.1 >= 0) {
        tf.phi = tf.phi - 0.1;
    }
    return tf;
}

int check(TestCase tc) {
    double Os = quantile(tc.sortedElements, tc.phi, tc.n);
    TestCase Tf_case = change(tc);
    double Of = quantile(Tf_case.sortedElements, Tf_case.phi, Tf_case.n);
    int is_valid = 0;
    if (Os >= Of) {
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