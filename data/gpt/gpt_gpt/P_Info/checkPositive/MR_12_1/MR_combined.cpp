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
    { (double[]){1.0, 2.5, 3.3}, 3 },
    { (double[]){0.1}, 1 },
    { (double[]){3.3, 1.1, 4.4, 2.2, 5.5}, 5 },
    { (double[]){-0.5, 2.0, 3.0}, 3 },
    { (double[]){0.0, 1.0}, 2 },
    { (double[]){10.0, 20.0, 30.0, 40.0}, 4 },
    { (double[]){-1.0, -2.0, -3.0}, 3 },
    { (double[]){0.00001, 0.00002}, 2 },
    { (double[]){100.0, -100.0}, 2 },
    { (double[]){}, 0 },
    { (double[]){7.7, 8.8, 9.9, 6.6}, 4 },
    { (double[]){2.5, -2.5, 2.5}, 3 },
    { (double[]){3.1415, 2.718, 1.618}, 3 },
    { (double[]){-0.000001, 0.5}, 2 },
    { (double[]){5.0, 5.0, 5.0}, 3 },
    { (double[]){9.99, 0.01, 5.55}, 3 },
    { (double[]){-10.0}, 1 },
    { (double[]){0.5, 0.0, 0.5}, 3 },
    { (double[]){123.456, 654.321}, 2 },
    { (double[]){-3.3, -2.2, -1.1, 0.1}, 4 },
    { (double[]){0.2, 0.4, 0.6, 0.8, 1.0}, 5 },
    { (double[]){-0.9, 0.9}, 2 },
    { (double[]){0.001, 0.002, 0.003}, 3 },
    { (double[]){-5.5, 5.5}, 2 },
    { (double[]){0.123, 0.456, 0.789}, 3 },
    { (double[]){-0.001, -0.002}, 2 },
    { (double[]){9.0, 8.0, 7.0, 6.0}, 4 },
    { (double[]){0.333, 0.666, 0.999}, 3 },
    { (double[]){-100.0, 0.0}, 2 },
    { (double[]){2.2, 4.4, 6.6, 8.8, 1.1}, 5 }
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    int half = tf.n / 2;
    for (int i = half; i < tf.n; ++i) {
        tf.a[i] -= 0.5;
    }
    return tf;
}

int check(TestCase tc) {
    bool Os = checkPositive(tc.a, tc.n);
    TestCase Tf_case = change(tc);
    
    bool Of = checkPositive(Tf_case.a, Tf_case.n);
    
    int is_valid = (Os >= Of) ? 1 : 0;
    
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