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


bool checkPositive(double a[], int n){
    
    for (int i = 0; i < n; i++)
    {
        if (a[i] <= 0)
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
    {(double[]){0.1, 0.001, 1e-10}, 3},
    {(double[]){100.0, 200.0, 300.0}, 3},
    {(double[]){5.0}, 1},
    {(double[]){1.1, 2.2, 3.3, 4.4, 5.5}, 5},
    {(double[]){2.0}, 1},
    {(double[]){3.14, 2.71}, 2},
    {(double[]){10.5, 20.3, 30.9, 40.1}, 4},
    {(double[]){0.5, 1.5, 2.5}, 3},
    {(double[]){7.0, 8.0, 9.0, 10.0, 11.0, 12.0}, 6},
    {(double[]){1.0}, 1},
    {(double[]){2.2, 4.4, 6.6, 8.8}, 4},
    {(double[]){15.0, 25.0, 35.0}, 3},
    {(double[]){0.8, 0.9, 1.0, 1.1}, 4},
    {(double[]){12.34, 56.78}, 2},
    {(double[]){9.99}, 1},
    {(double[]){1.2, 3.4, 5.6, 7.8, 9.0}, 5},
    {(double[]){6.0, 7.0, 8.0}, 3},
    {(double[]){0.25, 0.5, 0.75, 1.0}, 4},
    {(double[]){1000.0, 2000.0}, 2},
    {(double[]){4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0}, 7},
    {(double[]){1.111, 2.222, 3.333}, 3},
    {(double[]){50.0, 60.0, 70.0, 80.0}, 4},
    {(double[]){0.3, 0.6, 0.9}, 3},
    {(double[]){8.5, 9.5}, 2},
    {(double[]){11.11, 22.22, 33.33, 44.44, 55.55}, 5},
    {(double[]){0.01, 0.02, 0.03}, 3},
    {(double[]){6.66, 7.77}, 2},
    {(double[]){1.5, 2.5, 3.5, 4.5, 5.5, 6.5}, 6},
    {(double[]){0.99, 1.99, 2.99}, 3}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    if (tf.n > 0 && tf.a != nullptr) {
        double* new_a = new double[tf.n];
        for (int i = 0; i < tf.n; i++) {
            new_a[i] = tf.a[i] * 0.5;
        }
        tf.a = new_a;
    }
    return tf;
}

int check(TestCase tc) {
    bool Os = checkPositive(tc.a, tc.n);
    TestCase Tf_case = change(tc);
    bool Of = checkPositive(Tf_case.a, Tf_case.n);
    int is_valid = 0;
    if (Os == Of) {
        is_valid = 1;
    }
    if (Tf_case.a != tc.a) {
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