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


double weighted_average(double a[], double b[], int n) {
    double sum1 = 0;
    double sum2 = 0;
    for(int i = 0; i < n; i++) {
        sum1 += a[i] * b[i];
        sum2 += b[i];
    }
    return sum1 / sum2;
}


typedef struct {
    double* a; double* b; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0, 2.0, 3.0}, (double[]){1.0, 1.0, 1.0}, 3},
    {(double[]){5.0, 10.0, 15.0}, (double[]){2.0, 3.0, 5.0}, 3},
    {(double[]){-1.0, 0.0, 1.0}, (double[]){1.0, 2.0, 1.0}, 3},
    {(double[]){2.5, 3.5}, (double[]){4.0, 6.0}, 2},
    {(double[]){100.0, 200.0}, (double[]){0.5, 0.5}, 2},
    {(double[]){0.0, 0.0, 0.0}, (double[]){1.0, 2.0, 3.0}, 3},
    {(double[]){10.0}, (double[]){5.0}, 1},
    {(double[]){1.1, 2.2, 3.3, 4.4}, (double[]){0.1, 0.2, 0.3, 0.4}, 4},
    {(double[]){-2.0, -4.0, -6.0}, (double[]){1.0, 2.0, 3.0}, 3},
    {(double[]){3.0, 6.0, 9.0, 12.0}, (double[]){1.0, 2.0, 1.0, 2.0}, 4},
    {(double[]){7.0}, (double[]){3.0}, 1},
    {(double[]){0.5, 1.5, 2.5}, (double[]){2.0, 4.0, 6.0}, 3},
    {(double[]){8.0, 6.0, 4.0, 2.0}, (double[]){1.0, 1.0, 1.0, 1.0}, 4},
    {(double[]){9.0, 18.0}, (double[]){2.0, 4.0}, 2},
    {(double[]){1.0, 4.0, 9.0, 16.0}, (double[]){1.0, 2.0, 3.0, 4.0}, 4},
    {(double[]){2.0, 4.0, 8.0}, (double[]){0.25, 0.5, 0.25}, 3},
    {(double[]){-10.0, 10.0}, (double[]){3.0, 7.0}, 2},
    {(double[]){1.0, 2.0, 3.0, 4.0, 5.0}, (double[]){5.0, 4.0, 3.0, 2.0, 1.0}, 5},
    {(double[]){6.0, 12.0, 18.0}, (double[]){1.0, 2.0, 3.0}, 3},
    {(double[]){20.0, 40.0, 60.0}, (double[]){1.0, 2.0, 1.0}, 3},
    {(double[]){0.1, 0.2, 0.3}, (double[]){10.0, 20.0, 30.0}, 3},
    {(double[]){15.0, 25.0, 35.0}, (double[]){0.2, 0.3, 0.5}, 3},
    {(double[]){-1.5, -0.5, 0.5, 1.5}, (double[]){1.0, 2.0, 2.0, 1.0}, 4},
    {(double[]){50.0, 100.0}, (double[]){1.0, 3.0}, 2},
    {(double[]){1.0, 1.0, 1.0, 1.0}, (double[]){2.0, 3.0, 5.0, 7.0}, 4},
    {(double[]){12.0, 24.0, 36.0}, (double[]){0.5, 1.0, 1.5}, 3},
    {(double[]){0.0}, (double[]){5.0}, 1},
    {(double[]){2.0, 3.0, 5.0, 7.0}, (double[]){1.0, 1.0, 1.0, 1.0}, 4},
    {(double[]){30.0, 60.0, 90.0}, (double[]){1.0, 2.0, 3.0}, 3},
    {(double[]){4.0, 8.0, 12.0, 16.0, 20.0}, (double[]){1.0, 2.0, 3.0, 4.0, 5.0}, 5}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    double k = 5.0;
    if (tf.a != nullptr && tf.n > 0) {
        double* new_a = new double[tf.n];
        for (int i = 0; i < tf.n; i++) {
            new_a[i] = tf.a[i] - k;
        }
        tf.a = new_a;
    }
    return tf;
}

int check(TestCase tc) {
    double Os = weighted_average(tc.a, tc.b, tc.n);
    TestCase Tf_case = change(tc);
    double Of = weighted_average(Tf_case.a, Tf_case.b, Tf_case.n);
    int is_valid = 0;
    double k = 5.0;
    if (fabs((Os - k) - Of) < 1e-9) {
        is_valid = 1;
    }
    if (Tf_case.a != tc.a && Tf_case.a != nullptr) {
        delete[] Tf_case.a;
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