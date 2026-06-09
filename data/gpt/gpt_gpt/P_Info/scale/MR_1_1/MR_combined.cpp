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
    {0.0, (double[]){}, 0},
    {1.0, (double[]){2.5, -3.1, 4.0}, 3},
    {-2.0, (double[]){10.0, -5.5, 0.0, 3.3}, 4},
    {0.5, (double[]){-1.2, 2.8, -4.4, 5.5, -6.6}, 5},
    {3.14, (double[]){1.0, 1.0, 1.0}, 3},
    {-0.75, (double[]){8.8, -9.9, 0.1, -0.2, 0.3, -0.4}, 6},
    {2.0, (double[]){-7.0, 7.0}, 2},
    {1.5, (double[]){3.3, -2.2, 1.1, 0.0, -1.1, 2.2, -3.3}, 7},
    {-1.0, (double[]){5.5, 4.4, 3.3, 2.2, 1.1}, 5},
    {0.25, (double[]){-0.5, 0.5, -0.75, 0.75}, 4},
    {4.0, (double[]){9.9, -9.8, 9.7, -9.6, 9.5}, 5},
    {-3.5, (double[]){2.2, -2.2, 2.2, -2.2}, 4},
    {1.0, (double[]){0.0}, 1},
    {-0.1, (double[]){-0.1, 0.2, -0.3, 0.4, -0.5, 0.6, -0.7, 0.8}, 8},
    {2.5, (double[]){-1.0, -2.0, -3.0}, 3},
    {-2.5, (double[]){1.0, 2.0, 3.0, 4.0}, 4},
    {0.33, (double[]){7.7, -8.8, 9.9}, 3},
    {5.0, (double[]){-5.0, 0.0, 5.0}, 3},
    {-1.25, (double[]){-10.0, 10.0, -20.0, 20.0}, 4},
    {0.66, (double[]){3.14, 2.71, 1.41, 0.577, 0.0}, 5},
    {3.0, (double[]){-3.0, -2.0, -1.0, 0.0, 1.0, 2.0, 3.0}, 7},
    {-0.5, (double[]){0.25, -0.25, 0.5, -0.5}, 4},
    {1.2, (double[]){-4.4, 4.4, -2.2, 2.2, -1.1, 1.1}, 6},
    {-0.8, (double[]){9.0, -9.0, 8.0, -8.0, 7.0, -7.0, 6.0, -6.0}, 8},
    {0.0, (double[]){100.0, -100.0, 50.0, -50.0}, 4},
    {0.9, (double[]){0.1, 0.2, 0.3, 0.4, 0.5}, 5},
    {-0.3, (double[]){-0.3, 0.6, -0.9, 1.2, -1.5}, 5},
    {2.2, (double[]){-1.5, 2.5, -3.5, 4.5, -5.5, 6.5}, 6}
};
int num_test_cases = 28;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    tf.val = tc.val + 1.0;
    return tf;
}

int check(TestCase tc) {
    double* Os = scale(tc.val, tc.arr, tc.n);

    TestCase Tf_case = change(tc);
    double* Of = scale(Tf_case.val, Tf_case.arr, Tf_case.n);

    int is_valid = 1;
    for (int i = 0; i < tc.n; i++) {
        if (Of[i] != Os[i] + tc.arr[i] * 1.0) {
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