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


double g( double expected[],  double observed[], int n) {
    double sumExpected = 0;
    double sumObserved = 0;
    for (int i = 0; i < n; i++) {
        sumExpected += expected[i];
        sumObserved += observed[i];
    }
    double ratio = 1;
    bool rescale = false;
    if (fabs(sumExpected - sumObserved) > 10E-6) {
        ratio = sumObserved / sumExpected;
        rescale = true;
    }
    double sum = 0;
        for (int i = 0; i < n; i++) {
            double dev = rescale ? log((double) observed[i] / (ratio * expected[i])) : log((double) observed[i] / expected[i]);
            sum += (double) observed[i] * dev;
        }
    return 2 * sum;
}



typedef struct {
    double* expected; double* observed; int n;
} TestCase;

TestCase test_cases[] = {
    { (double[]){1.0, 2.0, 3.0}, (double[]){1.0, 2.0, 3.0}, 3 },
    { (double[]){2.5, 4.0}, (double[]){5.0, 8.0}, 2 },
    { (double[]){0.5, 1.5, 2.5}, (double[]){0.6, 1.4, 2.4}, 3 },
    { (double[]){10.0}, (double[]){5.0}, 1 },
    { (double[]){3.3, 7.7}, (double[]){6.6, 15.4}, 2 },
    { (double[]){1.2, 2.8, 4.6, 5.0}, (double[]){1.2, 2.8, 4.6, 5.0}, 4 },
    { (double[]){9.0, 1.0}, (double[]){3.0, 7.0}, 2 },
    { (double[]){0.1, 0.2, 0.3, 0.4, 0.5}, (double[]){0.2, 0.1, 0.4, 0.3, 0.6}, 5 },
    { (double[]){5.5, 6.5, 7.5}, (double[]){5.5, 6.5, 7.5}, 3 },
    { (double[]){2.0, 3.0, 5.0}, (double[]){4.0, 6.0, 10.0}, 3 },
    { (double[]){1.0, 4.0, 9.0}, (double[]){2.0, 8.0, 18.0}, 3 },
    { (double[]){0.9, 1.1}, (double[]){0.9, 1.1}, 2 },
    { (double[]){8.0, 2.0, 6.0}, (double[]){4.0, 1.0, 3.0}, 3 },
    { (double[]){1.5, 2.5, 3.5, 4.5}, (double[]){3.0, 5.0, 7.0, 9.0}, 4 },
    { (double[]){0.3, 0.7, 1.2}, (double[]){0.6, 1.4, 2.4}, 3 },
    { (double[]){100.0, 200.0}, (double[]){150.0, 250.0}, 2 },
    { (double[]){0.01, 0.02}, (double[]){0.02, 0.04}, 2 },
    { (double[]){3.1415, 2.7182}, (double[]){6.2830, 5.4364}, 2 },
    { (double[]){5.0, 5.0, 5.0}, (double[]){5.0, 5.0, 5.0}, 3 },
    { (double[]){7.0, 3.0, 9.0}, (double[]){14.0, 6.0, 18.0}, 3 },
    { (double[]){1.0, 2.0}, (double[]){1.5, 2.5}, 2 },
    { (double[]){4.4, 5.5, 6.6, 7.7}, (double[]){8.8, 11.0, 13.2, 15.4}, 4 },
    { (double[]){0.25, 0.75, 1.25}, (double[]){0.5, 1.5, 2.5}, 3 },
    { (double[]){2.2, 3.3, 4.4}, (double[]){2.2, 3.3, 4.4}, 3 },
    { (double[]){9.9, 8.8, 7.7}, (double[]){9.9, 8.8, 7.7}, 3 },
    { (double[]){0.6, 1.2, 1.8}, (double[]){0.9, 1.8, 2.7}, 3 },
    { (double[]){1.0, 1.0, 1.0, 1.0}, (double[]){2.0, 2.0, 2.0, 2.0}, 4 },
    { (double[]){3.0, 6.0, 9.0, 12.0}, (double[]){3.0, 6.0, 9.0, 12.0}, 4 },
    { (double[]){0.5, 1.5, 2.5, 3.5}, (double[]){0.75, 2.25, 3.75, 5.25}, 4 },
    { (double[]){ }, (double[]){ }, 0 }
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    for (int i = 0; i < tf.n; i++) {
        tf.observed[i] = 1.0;
    }
    return tf;
}

int check(TestCase tc) {
    double Os = g(tc.expected, tc.observed, tc.n);
    TestCase Tf_case = change(tc);
    double Of = g(Tf_case.expected, Tf_case.observed, Tf_case.n);
    int is_valid = (Os != Of) ? 1 : 0;
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