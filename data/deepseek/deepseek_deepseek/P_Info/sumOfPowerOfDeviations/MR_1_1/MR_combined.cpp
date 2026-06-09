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


double sumOfPowerOfDeviations(double data[], int k, double c, int n) {
    double sum = 0;
    for(int i = 0; i < n; i++) {
        sum += pow(data[i] - c, k);
        }
    return sum;
}


typedef struct {
    double* data; int k; double c; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0, 2.0, 3.0}, 1, 2.5, 3},
    {(double[]){1.0, 2.0, 3.0}, 2, 2.5, 3},
    {(double[]){1.0, 2.0, 3.0}, 3, 2.5, 3},
    {(double[]){1.0, 2.0, 3.0}, 4, 2.5, 3},
    {(double[]){1.0, 2.0, 3.0}, 0, 2.5, 3},
    {(double[]){-1.0, -2.0, -3.0}, 1, -2.0, 3},
    {(double[]){-1.0, -2.0, -3.0}, 2, -2.0, 3},
    {(double[]){-1.0, -2.0, -3.0}, 3, -2.0, 3},
    {(double[]){-1.0, -2.0, -3.0}, 4, -2.0, 3},
    {(double[]){-1.0, -2.0, -3.0}, 0, -2.0, 3},
    {(double[]){0.0, 0.0, 0.0}, 1, 0.0, 3},
    {(double[]){0.0, 0.0, 0.0}, 2, 0.0, 3},
    {(double[]){0.0, 0.0, 0.0}, 3, 0.0, 3},
    {(double[]){0.0, 0.0, 0.0}, 4, 0.0, 3},
    {(double[]){0.0, 0.0, 0.0}, 0, 0.0, 3},
    {(double[]){2.5, 2.5, 2.5}, 1, 2.5, 3},
    {(double[]){2.5, 2.5, 2.5}, 2, 2.5, 3},
    {(double[]){2.5, 2.5, 2.5}, 3, 2.5, 3},
    {(double[]){2.5, 2.5, 2.5}, 4, 2.5, 3},
    {(double[]){2.5, 2.5, 2.5}, 0, 2.5, 3},
    {(double[]){1.1, 2.2, 3.3, 4.4}, 1, 2.75, 4},
    {(double[]){1.1, 2.2, 3.3, 4.4}, 2, 2.75, 4},
    {(double[]){1.1, 2.2, 3.3, 4.4}, 3, 2.75, 4},
    {(double[]){1.1, 2.2, 3.3, 4.4}, 4, 2.75, 4},
    {(double[]){1.1, 2.2, 3.3, 4.4}, 0, 2.75, 4},
    {(double[]){-1.5, 0.0, 1.5}, 1, 0.0, 3},
    {(double[]){-1.5, 0.0, 1.5}, 2, 0.0, 3},
    {(double[]){-1.5, 0.0, 1.5}, 3, 0.0, 3},
    {(double[]){-1.5, 0.0, 1.5}, 4, 0.0, 3},
    {(double[]){-1.5, 0.0, 1.5}, 0, 0.0, 3}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    if (tf.n > 0 && tf.data != nullptr) {
        double* reversed_data = new double[tf.n];
        for (int i = 0; i < tf.n; i++) {
            reversed_data[i] = tc.data[tf.n - 1 - i];
        }
        tf.data = reversed_data;
    }
    return tf;
}

int check(TestCase tc) {
    double Os = sumOfPowerOfDeviations(tc.data, tc.k, tc.c, tc.n);
    TestCase Tf_case = change(tc);
    double Of = sumOfPowerOfDeviations(Tf_case.data, Tf_case.k, Tf_case.c, Tf_case.n);
    int is_valid = 0;
    if (Os == Of) {
        is_valid = 1;
    }
    if (Tf_case.data != tc.data && Tf_case.data != nullptr) {
        delete[] Tf_case.data;
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