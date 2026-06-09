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


bool checkNonNegative(double a[], int n){
    
    for (int i = 0; i < n; i++)
    {
        if (a[i] < 0)
        {
            return false;
        }
    }
    return true; 
}


typedef struct {
    double* a; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0, 2.5, 3.7}, 3},
    {(double[]){0.0, 0.0, 0.0}, 3},
    {(double[]){0.1, 0.01, 0.001}, 3},
    {(double[]){100.0, 200.0, 300.0}, 3},
    {(double[]){1.0}, 1},
    {(double[]){}, 0},
    {(double[]){0.0}, 1},
    {(double[]){1.2, 3.4}, 2},
    {(double[]){5.0}, 1},
    {(double[]){10.5, 20.3, 30.9, 40.1}, 4},
    {(double[]){0.5, 1.5, 2.5, 3.5, 4.5}, 5},
    {(double[]){1.1, 2.2, 3.3, 4.4, 5.5, 6.6}, 6},
    {(double[]){7.7, 8.8, 9.9}, 3},
    {(double[]){15.0, 25.0, 35.0}, 3},
    {(double[]){0.2, 0.4, 0.6, 0.8}, 4},
    {(double[]){12.34, 56.78}, 2},
    {(double[]){999.999}, 1},
    {(double[]){1.0, 0.0, 2.0}, 3},
    {(double[]){0.001, 0.002, 0.003}, 3},
    {(double[]){50.0, 60.0, 70.0, 80.0, 90.0}, 5},
    {(double[]){1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5}, 7},
    {(double[]){0.0, 1.0, 2.0, 3.0, 4.0, 5.0}, 6},
    {(double[]){1000.0, 2000.0}, 2},
    {(double[]){0.25, 0.5, 0.75}, 3},
    {(double[]){8.0, 6.0, 4.0, 2.0}, 4},
    {(double[]){9.9, 8.8, 7.7, 6.6, 5.5}, 5},
    {(double[]){0.0001, 0.0002}, 2},
    {(double[]){33.33, 66.66}, 2},
    {(double[]){1.0, 1.0, 1.0, 1.0, 1.0}, 5},
    {(double[]){2.718, 3.141}, 2}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    if (tf.n > 1) {
        for (int i = tf.n - 1; i > 0; --i) {
            int j = rand() % (i + 1);
            double temp = tf.a[i];
            tf.a[i] = tf.a[j];
            tf.a[j] = temp;
        }
    }
    return tf;
}

int check(TestCase tc) {
    bool Os = checkNonNegative(tc.a, tc.n);
    TestCase Tf_case = change(tc);
    bool Of = checkNonNegative(Tf_case.a, Tf_case.n);
    int is_valid = 0;
    if (Os == Of) {
        is_valid = 1;
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