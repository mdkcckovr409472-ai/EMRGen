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


double meanDifference(double sample1[], double sample2[], int n ) {
    double sumDifference = 0;
    for (int i = 0; i < n; i++) {
        sumDifference += sample1[i] - sample2[i];
    }
    return sumDifference / n;
}


typedef struct {
    double* sample1; double* sample2; int n;
} TestCase;

TestCase test_cases[] = {
    { (double[]){}, (double[]){}, 0 },
    { (double[]){5.0}, (double[]){3.0}, 1 },
    { (double[]){-2.5}, (double[]){1.5}, 1 },
    { (double[]){1.0, 4.0}, (double[]){0.5, 2.0}, 2 },
    { (double[]){0.0, -3.0}, (double[]){2.0, -1.0}, 2 },
    { (double[]){1.2, -0.5, 3.3}, (double[]){1.0, -1.0, 2.0}, 3 },
    { (double[]){0.0, 0.0, 0.0}, (double[]){0.0, 0.0, 0.0}, 3 },
    { (double[]){2.0, 2.0, 2.0, 2.0}, (double[]){1.0, 1.0, 1.0, 1.0}, 4 },
    { (double[]){5.0, -2.0, 0.0, 3.5}, (double[]){3.0, -1.0, 1.0, 2.5}, 4 },
    { (double[]){0.1, 2.2, -1.1, 4.4, -3.3}, (double[]){0.0, 2.0, -1.0, 4.0, -3.0}, 5 },
    { (double[]){10.0, -10.0, 5.0, -5.0, 0.0}, (double[]){0.0, 0.0, 0.0, 0.0, 0.0}, 5 },
    { (double[]){1.5, 2.5, 3.5, 4.5, 5.5, 6.5}, (double[]){1.0, 2.0, 3.0, 4.0, 5.0, 6.0}, 6 },
    { (double[]){-1.0, 2.0, -3.0, 4.0, -5.0, 6.0}, (double[]){1.0, -2.0, 3.0, -4.0, 5.0, -6.0}, 6 },
    { (double[]){7.0, -2.0, 0.5, -1.5, 3.0, -4.0, 2.0}, (double[]){5.0, -3.0, 0.0, -2.0, 2.0, -3.0, 1.0}, 7 },
    { (double[]){0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, (double[]){1.0, -1.0, 1.0, -1.0, 1.0, -1.0, 1.0}, 7 },
    { (double[]){1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0}, (double[]){8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0}, 8 },
    { (double[]){0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8}, (double[]){0.8, 0.7, 0.6, 0.5, 0.4, 0.3, 0.2, 0.1}, 8 },
    { (double[]){9.0, 8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0}, (double[]){1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0}, 9 },
    { (double[]){-0.5, 1.5, -2.5, 3.5, -4.5, 5.5, -6.5, 7.5, -8.5}, (double[]){0.5, -1.5, 2.5, -3.5, 4.5, -5.5, 6.5, -7.5, 8.5}, 9 },
    { (double[]){2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0}, (double[]){1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0}, 10 },
    { (double[]){0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0}, (double[]){1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0}, 10 },
    { (double[]){3.14, 2.71, 1.41}, (double[]){3.0, 2.0, 1.0}, 3 },
    { (double[]){-1.0, -2.0, -3.0, -4.0}, (double[]){-4.0, -3.0, -2.0, -1.0}, 4 },
    { (double[]){5.0, 5.0, 5.0, 5.0, 5.0}, (double[]){3.0, 4.0, 5.0, 6.0, 7.0}, 5 },
    { (double[]){-10.0, 20.0, -30.0, 40.0, -50.0, 60.0}, (double[]){0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, 6 },
    { (double[]){0.0, 0.0, 5.0, 5.0, 10.0, 10.0}, (double[]){1.0, 1.0, 4.0, 4.0, 9.0, 9.0}, 6 },
    { (double[]){0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7}, (double[]){0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, 7 },
    { (double[]){-5.0, -4.0, -3.0, -2.0, -1.0, 0.0, 1.0, 2.0}, (double[]){-2.0, -3.0, -4.0, -5.0, 0.0, 1.0, 2.0, 3.0}, 8 },
    { (double[]){0.5, 1.5, 2.5, 3.5, 4.5, 5.5, 6.5, 7.5, 8.5}, (double[]){0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0}, 9 },
    { (double[]){-0.2, 0.3, -0.4, 0.5, -0.6, 0.7, -0.8, 0.9, -1.0, 1.1}, (double[]){0.2, -0.3, 0.4, -0.5, 0.6, -0.7, 0.8, -0.9, 1.0, -1.1}, 10 }
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    // Allocate new array for sample1 since we need to add 1 to all elements, reuse sample2 and n
    tf.sample1 = new double[tc.n];
    for (int i = 0; i < tc.n; i++) {
        tf.sample1[i] = tc.sample1[i] + 1;
    }
    // sample2 and n remain unchanged, reuse the pointer tc.sample2
    return tf;
}

int check(TestCase tc) {
    // (1) Extract source input parameters from tc
    double* sample1_s = tc.sample1;
    double* sample2_s = tc.sample2;
    int n = tc.n;

    // (2) Call function under test to get Os
    double Os = meanDifference(sample1_s, sample2_s, n);

    // (3) Construct the follow-up test case
    TestCase Tf_case = change(tc);

    // (4) Extract follow-up input and call function to get Of
    double* sample1_f = Tf_case.sample1;
    double* sample2_f = Tf_case.sample2;
    double Of = meanDifference(sample1_f, sample2_f, n);

    // (5) Verify MR: Of == Os + 1
    int is_valid = 0;
    const double EPS = 1e-9;
    if (std::abs(Of - (Os + 1)) < EPS) {
        is_valid = 1;
    }

    // (6) Free dynamic memory allocated in change()
    delete[] sample1_f;

    // (7) Return verification result
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