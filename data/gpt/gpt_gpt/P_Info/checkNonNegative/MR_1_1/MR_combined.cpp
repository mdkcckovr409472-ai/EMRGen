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
    { (double[]){}, 0 },
    { (double[]){0.0}, 1 },
    { (double[]){2.5}, 1 },
    { (double[]){-1.0}, 1 },
    { (double[]){3.1, 4.2, 5.0}, 3 },
    { (double[]){0.0, 0.0, 0.0}, 3 },
    { (double[]){1.0, 0.0, 2.5}, 3 },
    { (double[]){5.5, 2.2, -0.5}, 3 },
    { (double[]){-0.3, 1.1, 2.2}, 3 },
    { (double[]){1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0}, 10 },
    { (double[]){1.0, -2.0, 3.0, -4.0, 5.0, -6.0, 7.0, -8.0, 9.0, -10.0}, 10 },
    { (double[]){0.5, 2.3, 4.1, 3.3, 1.0}, 5 },
    { (double[]){5.0, 3.0, -1.0, 2.0, 4.0}, 5 },
    { (double[]){7.7, 7.7, 7.7}, 3 },
    { (double[]){2.0, 0.5, 2.0}, 3 },
    { (double[]){-2.2, -2.2, -2.2}, 3 },
    { (double[]){1.0, 0.0, 2.0, 0.0}, 4 },
    { (double[]){1.0, -1.0, 2.0, -2.0}, 4 },
    { (double[]){3.3, 2.2, 1.1, 4.4, 5.5, 6.6}, 6 },
    { (double[]){3.3, -2.2, 1.1, -4.4, 5.5, -6.6}, 6 },
    { (double[]){0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8}, 8 },
    { (double[]){0.1, -0.2, 0.3, -0.4, 0.5, -0.6, 0.7, -0.8}, 8 },
    { (double[]){12345.6}, 1 },
    { (double[]){-9876.5}, 1 },
    { (double[]){2.2, 3.3}, 2 },
    { (double[]){-2.2, -3.3}, 2 },
    { (double[]){0.0, -1.0}, 2 },
    { (double[]){4.4, -3.3, 2.2, -1.1, 0.0, 1.1, -2.2, 3.3, -4.4}, 9 },
    { (double[]){4.4, 3.3, 2.2, 1.1, 0.0, 1.1, 2.2, 3.3, 4.4}, 9 },
    { (double[]){-5.5, 0.0, 2.2, -1.1, 3.3, 0.0, -0.5}, 7 }
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    double* new_a = new double[tf.n];
    for (int i = 0; i < tf.n; ++i) {
        new_a[i] = tf.a[i] * 2.0;
    }
    tf.a = new_a;
    return tf;
}

int check(TestCase tc) {
    bool Os = checkNonNegative(tc.a, tc.n);
    TestCase Tf_case = change(tc);
    bool Of = checkNonNegative(Tf_case.a, Tf_case.n);
    int is_valid = (Os == Of) ? 1 : 0;
    delete[] Tf_case.a;
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