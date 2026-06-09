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


double* scale(double val, double arr[], int n) {
    static double  newArr[1000];

    for (int i = 0; i < n; i++) {
        newArr[i] = arr[i] * val;
    }
    return newArr;
}


typedef struct {
    double val; double* arr; int n;
} TestCase;

TestCase test_cases[] = {
    {1.0, (double[]){1.0, 2.0, 3.0}, 3},
    {0.5, (double[]){4.0, 6.0, 8.0}, 3},
    {2.0, (double[]){-1.0, 0.0, 1.0}, 3},
    {-1.0, (double[]){5.0, -5.0, 2.5}, 3},
    {0.0, (double[]){100.0, 200.0, 300.0}, 3},
    {1.5, (double[]){10.0}, 1},
    {0.25, (double[]){0.0, 0.0, 0.0, 0.0}, 4},
    {-2.0, (double[]){-2.0, -3.0, -4.0}, 3},
    {0.1, (double[]){1.1, 2.2, 3.3, 4.4, 5.5}, 5},
    {10.0, (double[]){0.001, 0.002, 0.003}, 3},
    {1.0, (double[]){}, 0},
    {-0.5, (double[]){8.0, 12.0, 16.0, 20.0}, 4},
    {3.0, (double[]){1.5}, 1},
    {0.333333, (double[]){9.0, 18.0, 27.0}, 3},
    {-1.5, (double[]){2.0, 4.0, 6.0, 8.0, 10.0}, 5},
    {1.0, (double[]){-10.5, 20.5}, 2},
    {0.01, (double[]){1000.0, 2000.0}, 2},
    {2.5, (double[]){0.4, 0.8, 1.2}, 3},
    {-0.2, (double[]){-50.0, 50.0}, 2},
    {1.0, (double[]){3.14159, 2.71828}, 2},
    {0.75, (double[]){12.0, 24.0, 36.0, 48.0}, 4},
    {-3.0, (double[]){1.0, -1.0, 2.0, -2.0}, 4},
    {1.2, (double[]){5.0, 10.0, 15.0, 20.0, 25.0, 30.0}, 6},
    {0.0, (double[]){-999.999, 999.999}, 2},
    {0.8, (double[]){7.5}, 1},
    {-1.0, (double[]){0.0}, 1},
    {1.0, (double[]){1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0}, 10},
    {0.5, (double[]){-6.0, -4.0, -2.0, 0.0, 2.0, 4.0, 6.0}, 7},
    {1.1, (double[]){0.1, 0.2, 0.3, 0.4}, 4},
    {2.0, (double[]){0.5, 1.0, 1.5, 2.0, 2.5, 3.0}, 6}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    tf.val = tc.val * 2.0;
    return tf;
}

int check(TestCase tc) {
    double* Os = scale(tc.val, tc.arr, tc.n);
    TestCase Tf_case = change(tc);
    double* Of = scale(Tf_case.val, Tf_case.arr, Tf_case.n);
    int is_valid = 1;
    for (int i = 0; i < tc.n; i++) {
        if (2.0 * Os[i] != Of[i]) {
            is_valid = 0;
            break;
        }
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