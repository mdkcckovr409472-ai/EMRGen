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


double durbinWatson(double elements[], int n) {
    
    double run = 0;
    for (int i = 1; i < n; ++i) {
        double x = elements[i] - elements[i - 1];
        run += x * x;
    }
    return run;
}


typedef struct {
    double* elements; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0, 2.0, 3.0, 4.0}, 4},
    {(double[]){4.0, 3.0, 2.0, 1.0}, 4},
    {(double[]){1.0, 1.0, 1.0, 1.0}, 4},
    {(double[]){-1.0, -2.0, -3.0, -4.0}, 4},
    {(double[]){-4.0, -3.0, -2.0, -1.0}, 4},
    {(double[]){0.0, 0.0, 0.0, 0.0}, 4},
    {(double[]){1.5, 2.5, 3.5, 4.5}, 4},
    {(double[]){100.0, 200.0, 150.0, 250.0}, 4},
    {(double[]){-100.0, -200.0, -150.0, -250.0}, 4},
    {(double[]){0.1, 0.2, 0.3, 0.4}, 4},
    {(double[]){-0.1, -0.2, -0.3, -0.4}, 4},
    {(double[]){1.0}, 1},
    {(double[]){-5.0}, 1},
    {(double[]){0.0}, 1},
    {(double[]){1.0, 2.0}, 2},
    {(double[]){2.0, 1.0}, 2},
    {(double[]){-1.0, -2.0}, 2},
    {(double[]){10.0, 20.0, 30.0}, 3},
    {(double[]){30.0, 20.0, 10.0}, 3},
    {(double[]){1.0, 3.0, 2.0, 5.0, 4.0}, 5},
    {(double[]){5.0, 4.0, 3.0, 2.0, 1.0}, 5},
    {(double[]){2.2, 3.3, 4.4, 5.5, 6.6, 7.7}, 6},
    {(double[]){-2.2, -3.3, -4.4, -5.5, -6.6, -7.7}, 6},
    {(double[]){1.1, -1.1, 1.1, -1.1}, 4},
    {(double[]){0.5, 1.0, 0.5, 1.0, 0.5}, 5},
    {(double[]){1000.0, 1001.0, 999.0, 1002.0}, 4},
    {(double[]){-1000.0, -1001.0, -999.0, -1002.0}, 4},
    {(double[]){1.0e-6, 2.0e-6, 3.0e-6}, 3},
    {(double[]){3.14159, 2.71828, 1.41421}, 3},
    {(double[]){}, 0}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    double c = 2.0; // 常数因子，可根据需要调整
    double* new_elements = new double[tf.n];
    for (int i = 0; i < tf.n; ++i) {
        new_elements[i] = tf.elements[i] * c;
    }
    tf.elements = new_elements;
    return tf;
}

int check(TestCase tc) {
    double Os = durbinWatson(tc.elements, tc.n);
    TestCase Tf_case = change(tc);
    double Of = durbinWatson(Tf_case.elements, Tf_case.n);
    int is_valid = 0;
    double c = 2.0;
    if (std::abs(c * c * Os - Of) < 1e-9) {
        is_valid = 1;
    }
    delete[] Tf_case.elements;
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