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
    {(double[]){1.0, 2.0, 3.0}, 2, 0.0, 3},
    {(double[]){}, 1, 5.0, 0},
    {(double[]){-1.5, 0.0, 2.5}, 1, 1.0, 3},
    {(double[]){3.0, -3.0, 3.0}, 3, 0.0, 3},
    {(double[]){0.5, -0.5, 0.5, -0.5}, 2, 0.0, 4},
    {(double[]){10.0, -10.0}, 1, 5.0, 2},
    {(double[]){2.0, 2.0, 2.0}, 0, 2.0, 3},
    {(double[]){-2.0, -4.0, -6.0}, 2, -3.0, 3},
    {(double[]){1.1, 2.2, 3.3, 4.4}, 1, 2.5, 4},
    {(double[]){5.0, 0.0, -5.0}, 4, 1.0, 3},
    {(double[]){0.0}, 5, 0.0, 1},
    {(double[]){-1.0, 1.0, -1.0, 1.0}, 3, 0.0, 4},
    {(double[]){3.5, -2.5, 0.0}, -1, 1.0, 3},
    {(double[]){7.0, 8.0, 9.0}, 2, 8.0, 3},
    {(double[]){-3.3, 3.3}, 1, -3.3, 2},
    {(double[]){0.1, 0.2, 0.3}, 2, 0.15, 3},
    {(double[]){4.0, -1.0, 2.0, -3.0}, 1, -0.5, 4},
    {(double[]){6.0, 6.0}, 0, 0.0, 2},
    {(double[]){-0.7, 0.7, -0.7}, 2, 0.0, 3},
    {(double[]){2.5, -2.5, 2.5, -2.5, 0.0}, 3, 1.0, 5},
    {(double[]){1.0, 2.0}, 10, 0.0, 2},
    {(double[]){-5.0, 5.0, -5.0, 5.0}, 2, 0.0, 4},
    {(double[]){3.14, -3.14}, 1, 0.0, 2},
    {(double[]){0.0, 0.0, 0.0}, 5, 0.0, 3},
    {(double[]){9.0, -9.0, 1.0}, 2, 5.0, 3},
    {(double[]){1.5, -1.5, 2.5, -2.5}, 1, 0.0, 4},
    {(double[]){-2.2, 3.3, -4.4, 5.5}, 3, -1.0, 4},
    {(double[]){0.25, -0.25, 0.75, -0.75}, 2, 0.5, 4},
    {(double[]){8.0}, 0, 8.0, 1},
    {(double[]){-1.0, 0.0, 1.0}, 1, 0.0, 3}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    if (tf.n > 1) {
        double* reversedData = new double[tf.n];
        for (int i = 0; i < tf.n; i++) {
            reversedData[i] = tf.data[tf.n - 1 - i];
        }
        tf.data = reversedData;
    }
    return tf;
}

int check(TestCase tc) {
    double Os = sumOfPowerOfDeviations(tc.data, tc.k, tc.c, tc.n);
    TestCase Tf_case = change(tc);
    double Of = sumOfPowerOfDeviations(Tf_case.data, Tf_case.k, Tf_case.c, Tf_case.n);
    int is_valid = (Os == Of) ? 1 : 0;
    if (Tf_case.data != tc.data) {
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