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
    {(double[]){1.0, 2.0, 3.0}, (double[]){1.0, 2.0, 3.0}, 3},
    {(double[]){10.0, 10.0, 10.0}, (double[]){9.0, 10.0, 11.0}, 3},
    {(double[]){5.0, 5.0}, (double[]){5.0, 5.0}, 2},
    {(double[]){2.5, 7.5}, (double[]){3.0, 7.0}, 2},
    {(double[]){100.0, 200.0, 300.0}, (double[]){95.0, 210.0, 295.0}, 3},
    {(double[]){1.0}, (double[]){1.5}, 1},
    {(double[]){0.1, 0.2, 0.3}, (double[]){0.12, 0.18, 0.3}, 3},
    {(double[]){8.0, 8.0, 8.0, 8.0}, (double[]){7.0, 8.0, 9.0, 8.0}, 4},
    {(double[]){15.0, 25.0}, (double[]){14.0, 26.0}, 2},
    {(double[]){3.0, 3.0, 3.0, 3.0, 3.0}, (double[]){2.0, 3.0, 4.0, 3.0, 3.0}, 5},
    {(double[]){50.0, 30.0, 20.0}, (double[]){52.0, 28.0, 20.0}, 3},
    {(double[]){7.2, 3.6}, (double[]){7.0, 3.8}, 2},
    {(double[]){0.5, 1.5, 2.5, 3.5}, (double[]){0.6, 1.4, 2.6, 3.4}, 4},
    {(double[]){12.0, 12.0}, (double[]){12.0, 12.0}, 2},
    {(double[]){9.0, 6.0, 3.0}, (double[]){10.0, 5.0, 3.0}, 3},
    {(double[]){4.0, 4.0, 4.0, 4.0}, (double[]){4.0, 4.0, 4.0, 4.0}, 4},
    {(double[]){1.2, 2.4, 3.6}, (double[]){1.0, 2.5, 3.7}, 3},
    {(double[]){20.0, 30.0, 50.0}, (double[]){22.0, 33.0, 45.0}, 3},
    {(double[]){6.0, 6.0}, (double[]){5.5, 6.5}, 2},
    {(double[]){0.01, 0.02, 0.03}, (double[]){0.01, 0.02, 0.03}, 3},
    {(double[]){11.0, 22.0, 33.0}, (double[]){10.0, 23.0, 32.0}, 3},
    {(double[]){2.0, 4.0, 6.0, 8.0}, (double[]){1.0, 5.0, 7.0, 8.0}, 4},
    {(double[]){5.5, 5.5}, (double[]){5.0, 6.0}, 2},
    {(double[]){14.0, 28.0, 42.0}, (double[]){13.0, 29.0, 42.0}, 3},
    {(double[]){0.25, 0.75}, (double[]){0.3, 0.7}, 2},
    {(double[]){18.0, 12.0, 6.0}, (double[]){17.0, 13.0, 6.0}, 3},
    {(double[]){40.0, 60.0}, (double[]){38.0, 62.0}, 2},
    {(double[]){1.8, 3.6, 5.4}, (double[]){2.0, 3.5, 5.5}, 3},
    {(double[]){7.0, 14.0, 21.0}, (double[]){6.5, 14.5, 21.0}, 3},
    {(double[]){0.0, 0.0, 0.0}, (double[]){0.0, 0.0, 0.0}, 3}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    tf.expected = new double[tf.n];
    for (int i = 0; i < tf.n; i++) {
        tf.expected[i] = tc.expected[i] * 2.0;
    }
    return tf;
}

int check(TestCase tc) {
    double Os = chiSquate(tc.expected, tc.observed, tc.n);
    TestCase Tf_case = change(tc);
    double Of = chiSquate(Tf_case.expected, Tf_case.observed, Tf_case.n);
    int is_valid = 0;
    if (abs(Os - Of) < 10E-6) {
        is_valid = 1;
    }
    delete[] Tf_case.expected;
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