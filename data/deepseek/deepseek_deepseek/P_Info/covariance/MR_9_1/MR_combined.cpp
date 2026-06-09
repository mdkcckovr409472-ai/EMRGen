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


double covariance(double elements1[], double elements2[], int n) {

    double sumx = elements1[0];
    double sumy = elements2[0];
    double Sxy = 0;
    
    for (int i = 1; i < n; ++i) {
        double x = elements1[i];
        double y = elements2[i];
        sumx += x;
        Sxy += (x - sumx / (i + 1)) * (y - sumy / i);
        sumy += y;
    }
    return Sxy / (n - 1);
}


typedef struct {
    double* elements1; double* elements2; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0, 2.0, 3.0}, (double[]){4.0, 5.0, 6.0}, 3},
    {(double[]){0.0, 0.0, 0.0}, (double[]){0.0, 0.0, 0.0}, 3},
    {(double[]){-1.0, 0.0, 1.0}, (double[]){-1.0, 0.0, 1.0}, 3},
    {(double[]){10.5, 20.3, 30.7}, (double[]){15.2, 25.8, 35.1}, 3},
    {(double[]){1.0}, (double[]){2.0}, 1},
    {(double[]){2.5, 3.5}, (double[]){1.5, 4.5}, 2},
    {(double[]){1.1, 2.2, 3.3, 4.4}, (double[]){5.5, 6.6, 7.7, 8.8}, 4},
    {(double[]){-2.0, -1.0, 0.0, 1.0, 2.0}, (double[]){2.0, 1.0, 0.0, -1.0, -2.0}, 5},
    {(double[]){100.0, 200.0, 300.0}, (double[]){150.0, 250.0, 350.0}, 3},
    {(double[]){0.5, 1.5, 2.5, 3.5}, (double[]){3.5, 2.5, 1.5, 0.5}, 4},
    {(double[]){1.0, 1.0, 1.0, 1.0, 1.0}, (double[]){2.0, 2.0, 2.0, 2.0, 2.0}, 5},
    {(double[]){3.14, 6.28, 9.42}, (double[]){1.41, 2.82, 4.23}, 3},
    {(double[]){-10.0, -20.0, -30.0}, (double[]){-5.0, -15.0, -25.0}, 3},
    {(double[]){1.0, 2.0, 3.0, 4.0, 5.0, 6.0}, (double[]){6.0, 5.0, 4.0, 3.0, 2.0, 1.0}, 6},
    {(double[]){0.1, 0.2, 0.3}, (double[]){0.4, 0.5, 0.6}, 3},
    {(double[]){7.0, 14.0, 21.0}, (double[]){3.0, 6.0, 9.0}, 3},
    {(double[]){2.0, 4.0, 8.0, 16.0}, (double[]){1.0, 3.0, 7.0, 15.0}, 4},
    {(double[]){-1.5, -0.5, 0.5, 1.5}, (double[]){-1.5, -0.5, 0.5, 1.5}, 4},
    {(double[]){9.9, 8.8, 7.7}, (double[]){6.6, 5.5, 4.4}, 3},
    {(double[]){12.25, 24.5, 36.75}, (double[]){6.125, 12.25, 18.375}, 3},
    {(double[]){1.0, 4.0, 9.0, 16.0}, (double[]){1.0, 2.0, 3.0, 4.0}, 4},
    {(double[]){0.0, 1.0, 0.0, -1.0, 0.0}, (double[]){1.0, 0.0, -1.0, 0.0, 1.0}, 5},
    {(double[]){5.0, 10.0, 15.0, 20.0, 25.0, 30.0}, (double[]){30.0, 25.0, 20.0, 15.0, 10.0, 5.0}, 6},
    {(double[]){2.718, 3.142, 1.618}, (double[]){1.414, 1.732, 2.236}, 3},
    {(double[]){1.0, 2.0, 1.0, 2.0, 1.0}, (double[]){2.0, 1.0, 2.0, 1.0, 2.0}, 5},
    {(double[]){8.0, 6.0, 7.0, 5.0, 3.0}, (double[]){0.0, 9.0, 0.0, 9.0, 0.0}, 5},
    {(double[]){0.25, 0.5, 0.75, 1.0}, (double[]){4.0, 2.0, 1.333, 1.0}, 4},
    {(double[]){-3.0, -2.0, -1.0, 0.0, 1.0, 2.0, 3.0}, (double[]){9.0, 4.0, 1.0, 0.0, 1.0, 4.0, 9.0}, 7},
    {(double[]){1.0, 1.0, 2.0, 3.0, 5.0, 8.0}, (double[]){1.0, 2.0, 3.0, 5.0, 8.0, 13.0}, 6},
    {(double[]){10.0, 20.0, 30.0, 40.0, 50.0}, (double[]){2.0, 4.0, 6.0, 8.0, 10.0}, 5}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    double* new_elements1 = new double[tc.n];
    for (int i = 0; i < tc.n; ++i) {
        new_elements1[i] = tc.elements1[i] * -1.0;
    }
    tf.elements1 = new_elements1;
    return tf;
}

int check(TestCase tc) {
    double Os = covariance(tc.elements1, tc.elements2, tc.n);
    TestCase Tf_case = change(tc);
    double Of = covariance(Tf_case.elements1, Tf_case.elements2, Tf_case.n);
    int is_valid = 0;
    const double epsilon = 1e-9;
    if (fabs((-1.0 * Os) - Of) < epsilon) {
        is_valid = 1;
    }
    delete[] Tf_case.elements1;
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