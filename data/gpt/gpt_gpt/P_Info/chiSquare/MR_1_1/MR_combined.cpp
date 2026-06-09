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


double chiSquate(double expected[], double observed[], int n){
    double sumExpected = 0;
    double sumObserved = 0;
    for (int i = 0; i < n; i++) {
        sumExpected += expected[i];
        sumObserved += observed[i];
        }
    double ratio = 1.0;
    bool rescale = false;
    if (abs(sumExpected - sumObserved) > 10E-6) {
        ratio = sumObserved / sumExpected;
        rescale = true;
    }
    double sumSq = 0.0;
    for (int i = 0; i < n; i++) {
        if (rescale) {
            double dev = observed[i] - ratio * expected[i];
            sumSq += dev * dev / (ratio * expected[i]);
        } else {
            double dev = observed[i] - expected[i];
            sumSq += dev * dev / expected[i];
            }
        }
        return sumSq;
    }


typedef struct {
    double* expected; double* observed; int n;
} TestCase;

TestCase test_cases[] = {
    { (double[]){1.0, 2.0, 3.0}, (double[]){1.0, 2.0, 3.0}, 3 },
    { (double[]){2.0, -1.5, 4.0}, (double[]){2.1, -1.4, 3.9}, 3 },
    { (double[]){}, (double[]){}, 0 },
    { (double[]){5.0, 5.0, 5.0}, (double[]){10.0, 0.0, 5.0}, 3 },
    { (double[]){0.5, -2.0, 1.5}, (double[]){0.6, -1.8, 1.4}, 3 },
    { (double[]){-3.0, 4.0}, (double[]){-2.5, 4.5}, 2 },
    { (double[]){7.2, -0.8, 3.3, 2.1}, (double[]){7.0, -0.9, 3.5, 2.0}, 4 },
    { (double[]){1.2}, (double[]){1.3}, 1 },
    { (double[]){-5.0, 2.5, -3.5, 4.0}, (double[]){-4.8, 2.7, -3.4, 4.2}, 4 },
    { (double[]){0.9, 0.9, 0.9}, (double[]){0.9, 0.9, 0.9}, 3 },
    { (double[]){3.5, -2.2, 1.1, -0.5, 2.0}, (double[]){3.6, -2.1, 1.0, -0.6, 2.1}, 5 },
    { (double[]){-1.0, 1.0}, (double[]){-0.9, 1.1}, 2 },
    { (double[]){4.4, 4.4, 4.4}, (double[]){4.5, 4.3, 4.4}, 3 },
    { (double[]){-2.5, -2.5, -2.5}, (double[]){-2.4, -2.6, -2.5}, 3 },
    { (double[]){0.2, 0.8, 1.5}, (double[]){0.3, 0.7, 1.6}, 3 },
    { (double[]){5.5, -3.3, 2.2}, (double[]){5.4, -3.2, 2.3}, 3 },
    { (double[]){-0.1, 0.1, -0.1, 0.1}, (double[]){-0.2, 0.2, -0.05, 0.15}, 4 },
    { (double[]){2.0, 2.0}, (double[]){2.0, 2.0}, 2 },
    { (double[]){-4.0, 3.0, -2.0, 1.0}, (double[]){-3.9, 3.1, -2.1, 0.9}, 4 },
    { (double[]){0.6, 1.2, 1.8}, (double[]){0.5, 1.3, 1.7}, 3 },
    { (double[]){-3.3, 0.0, 3.3}, (double[]){-3.2, 0.1, 3.4}, 3 },
    { (double[]){1.0, -1.0, 1.0, -1.0}, (double[]){0.9, -1.1, 1.1, -0.9}, 4 },
    { (double[]){2.5, 2.5, 2.5, 2.5}, (double[]){2.6, 2.4, 2.5, 2.5}, 4 },
    { (double[]){-0.5, 0.5, -0.5}, (double[]){-0.4, 0.6, -0.6}, 3 },
    { (double[]){3.0, 0.0, -3.0}, (double[]){3.1, -0.1, -2.9}, 3 },
    { (double[]){1.5, 2.5, 3.5, 4.5}, (double[]){1.6, 2.4, 3.6, 4.4}, 4 },
    { (double[]){-2.0, -1.0, 0.0, 1.0, 2.0}, (double[]){-1.9, -0.9, 0.1, 1.1, 2.1}, 5 }
};
int num_test_cases = 27;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    double* newExpected = new double[tc.n];
    for (int i = 0; i < tc.n; i++) {
        newExpected[i] = tc.expected[i] * 2.0;
    }
    tf.expected = newExpected;
    return tf;
}

int check(TestCase tc) {
    double Os = chiSquate(tc.expected, tc.observed, tc.n);
    TestCase Tf_case = change(tc);
    double Of = chiSquate(Tf_case.expected, Tf_case.observed, Tf_case.n);
    bool is_valid = (Os == Of);
    delete[] Tf_case.expected;
    return is_valid ? 1 : 0;
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