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
    { (double[]){5.0, 7.0}, (double[]){3.0, 4.0}, 2 },
    { (double[]){-2.5, 0.0, 1.5}, (double[]){4.0, -1.0, 2.0}, 3 },
    { (double[]){10.0, 10.0, 10.0, 10.0}, (double[]){5.0, 5.0, 5.0, 5.0}, 4 },
    { (double[]){-3.0, 2.0, -1.0, 4.0, 0.0}, (double[]){1.0, -2.0, 3.0, -4.0, 5.0}, 5 },
    { (double[]){0.0, 0.0}, (double[]){0.0, 0.0}, 2 },
    { (double[]){8.2, -3.1, 4.5, -6.7}, (double[]){-2.2, 7.3, -1.5, 3.1}, 4 },
    { (double[]){1.0, 2.0, 3.0}, (double[]){3.0, 2.0, 1.0}, 3 },
    { (double[]){-10.0, 20.0, -30.0, 40.0, -50.0, 60.0}, (double[]){60.0, -50.0, 40.0, -30.0, 20.0, -10.0}, 6 },
    { (double[]){0.5, -0.5, 0.5, -0.5}, (double[]){-0.5, 0.5, -0.5, 0.5}, 4 },
    { (double[]){3.3, 3.3, 3.3}, (double[]){-1.1, -1.1, -1.1}, 3 },
    { (double[]){7.0, 2.0, 9.0, 4.0, 6.0}, (double[]){1.0, 5.0, 2.0, 8.0, 3.0}, 5 },
    { (double[]){-4.0, -2.0, -6.0}, (double[]){-1.0, -3.0, -5.0}, 3 },
    { (double[]){12.5, 0.0, -12.5}, (double[]){-12.5, 0.0, 12.5}, 3 },
    { (double[]){1.1, 2.2, 3.3, 4.4, 5.5, 6.6}, (double[]){6.6, 5.5, 4.4, 3.3, 2.2, 1.1}, 6 },
    { (double[]){-0.1, 0.2, -0.3, 0.4, -0.5}, (double[]){0.5, -0.4, 0.3, -0.2, 0.1}, 5 },
    { (double[]){100.0, -100.0}, (double[]){-100.0, 100.0}, 2 },
    { (double[]){9.9, 8.8, 7.7, 6.6}, (double[]){6.6, 7.7, 8.8, 9.9}, 4 },
    { (double[]){0.0, 5.0, 10.0, 15.0, 20.0}, (double[]){20.0, 15.0, 10.0, 5.0, 0.0}, 5 },
    { (double[]){3.1415, 2.7182, 1.6180}, (double[]){1.4142, 0.5772, 0.6931}, 3 },
    { (double[]){-7.0, 14.0, -21.0, 28.0}, (double[]){28.0, -21.0, 14.0, -7.0}, 4 },
    { (double[]){0.25, 0.5, 0.75, 1.0}, (double[]){1.0, 0.75, 0.5, 0.25}, 4 },
    { (double[]){-5.5, 5.5, -5.5, 5.5}, (double[]){5.5, -5.5, 5.5, -5.5}, 4 },
    { (double[]){2.0, 4.0, 6.0, 8.0, 10.0}, (double[]){1.0, 3.0, 5.0, 7.0, 9.0}, 5 },
    { (double[]){-1.0, 2.0, -3.0, 4.0, -5.0, 6.0}, (double[]){6.0, -5.0, 4.0, -3.0, 2.0, -1.0}, 6 },
    { (double[]){0.0, 1.0, 0.0, 1.0, 0.0}, (double[]){1.0, 0.0, 1.0, 0.0, 1.0}, 5 },
    { (double[]){-2.2, -2.2, -2.2, -2.2}, (double[]){3.3, 3.3, 3.3, 3.3}, 4 },
    { (double[]){5.5, -4.5, 3.5, -2.5, 1.5}, (double[]){-1.5, 2.5, -3.5, 4.5, -5.5}, 5 },
    { (double[]){0.0, -0.0, 0.0, -0.0}, (double[]){0.0, 0.0, 0.0, 0.0}, 4 }
};
int num_test_cases = 28;


TestCase change(TestCase tc) {
    TestCase tf = tc;

    // Allocate new memory for elements1 in tf
    double* new_elements1 = new double[tc.n];
    for (int i = 0; i < tc.n; ++i) {
        new_elements1[i] = tc.elements1[i] - 1.0;
    }
    tf.elements1 = new_elements1;

    // elements2 and n remain the same, reuse original pointers

    return tf;
}

int check(TestCase tc) {
    double Os = covariance(tc.elements1, tc.elements2, tc.n);

    TestCase Tf_case = change(tc);
    double Of = covariance(Tf_case.elements1, Tf_case.elements2, Tf_case.n);

    int is_valid = 0;
    if (Os == Of) {
        is_valid = 1;
    }

    // Free any dynamic memory allocated in change()
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