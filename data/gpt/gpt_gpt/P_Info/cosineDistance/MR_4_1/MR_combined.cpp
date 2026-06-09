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


double cosineDistance(double p1[], double p2[], int n) {
    double dotProduct = 0.0;
    double lengthSquaredp1 = 0.0;
    double lengthSquaredp2 = 0.0;

    for (int i = 0; i < n; i++) {
        lengthSquaredp1 += p1[i] * p1[i];
        lengthSquaredp2 += p2[i] * p2[i];
        dotProduct += p1[i] * p2[i];
    }
    
    double denominator = sqrt(lengthSquaredp1) * sqrt(lengthSquaredp2);
    if (denominator < dotProduct) {
        denominator = dotProduct;
    }
    if (denominator == 0 && dotProduct == 0) {
        return 0;
    }
    return 1.0 - dotProduct / denominator;
}


typedef struct {
    double* p1; double* p2; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){}, (double[]){}, 0},
    {(double[]){1.0}, (double[]){1.0}, 1},
    {(double[]){-1.0}, (double[]){1.0}, 1},
    {(double[]){1.0, 0.0}, (double[]){0.0, 1.0}, 2},
    {(double[]){2.0, 3.0}, (double[]){2.0, 3.0}, 2},
    {(double[]){1.0, 2.0}, (double[]){2.0, 4.0}, 2},
    {(double[]){1.0, -2.0, 3.0}, (double[]){-1.0, 2.0, -3.0}, 3},
    {(double[]){0.5, -1.2, 3.3}, (double[]){2.1, 0.0, -0.7}, 3},
    {(double[]){0.0, 0.0, 0.0}, (double[]){1.0, 2.0, 3.0}, 3},
    {(double[]){1.0, 2.0, 3.0, 4.0}, (double[]){1.0, 2.0, 3.0, 4.0}, 4},
    {(double[]){1.0, 0.0, 1.0, 0.0}, (double[]){0.0, 1.0, 0.0, 1.0}, 4},
    {(double[]){-0.3, 2.5, -1.7, 4.2}, (double[]){3.1, -0.8, 0.0, -2.6}, 4},
    {(double[]){5.0, 5.0, 5.0, 5.0, 5.0}, (double[]){5.0, 5.0, 5.0, 5.0, 5.0}, 5},
    {(double[]){-2.0, -4.0, -6.0, -8.0, -10.0}, (double[]){-2.0, -4.0, -6.0, -8.0, -10.0}, 5},
    {(double[]){3.0, -1.0, 4.0, -5.0, 2.0}, (double[]){-2.0, 6.0, -8.0, 10.0, -4.0}, 5},
    {(double[]){0.0, 1.0, 0.0, -1.0, 0.0, 1.0}, (double[]){1.0, 0.0, -1.0, 0.0, 1.0, 0.0}, 6},
    {(double[]){1.2, -3.4, 5.6, -7.8, 9.0, -0.1}, (double[]){-1.2, 3.4, -5.6, 7.8, -9.0, 0.1}, 6},
    {(double[]){2.5, 0.0, -2.5, 0.0, 2.5, 0.0}, (double[]){0.0, 2.5, 0.0, -2.5, 0.0, 2.5}, 6},
    {(double[]){0.0, 0.0, 0.0, 0.0}, (double[]){0.0, 0.0, 0.0, 0.0}, 4},
    {(double[]){1.0, 1.0, 1.0}, (double[]){-1.0, -1.0, -1.0}, 3},
    {(double[]){0.3, 0.6, 0.9}, (double[]){0.3, 0.6, 0.9}, 3},
    {(double[]){-0.5, 2.0, -1.5}, (double[]){0.5, -2.0, 1.5}, 3},
    {(double[]){4.0, -4.0, 4.0, -4.0}, (double[]){-4.0, 4.0, -4.0, 4.0}, 4},
    {(double[]){1.0, 2.0, 3.0, 4.0, 5.0}, (double[]){5.0, 4.0, 3.0, 2.0, 1.0}, 5},
    {(double[]){-3.0, 0.0, 3.0}, (double[]){3.0, 0.0, -3.0}, 3},
    {(double[]){0.1, 0.2, 0.3, 0.4}, (double[]){0.4, 0.3, 0.2, 0.1}, 4},
    {(double[]){2.0, -2.0, 2.0, -2.0, 2.0}, (double[]){-2.0, 2.0, -2.0, 2.0, -2.0}, 5},
    {(double[]){0.0, 1.0, 2.0, 3.0}, (double[]){3.0, 2.0, 1.0, 0.0}, 4},
    {(double[]){-1.0, -2.0, -3.0}, (double[]){-1.0, -2.0, -3.0}, 3},
    {(double[]){1.5, -0.5, 2.5, -1.5}, (double[]){-1.5, 0.5, -2.5, 1.5}, 4},
    {(double[]){0.0, 0.0, 0.0}, (double[]){0.0, 0.0, 0.0}, 3}
};
int num_test_cases = 31;


TestCase change(TestCase tc) {
    TestCase tf = tc; 

    // Overwrite p1 elements to 1, reusing the original array memory as per requirement
    for (int i = 0; i < tf.n; i++) {
        tf.p1[i] = 1.0;
    }

    return tf;
}

int check(TestCase tc) {
    // (1) Extract the source input (Ts)
    double* p1_s = tc.p1;
    double* p2_s = tc.p2;
    int n_s = tc.n;

    // (2) Call the function under test from [Information 1] to get the source output (Os)
    double Os = cosineDistance(p1_s, p2_s, n_s);

    // (3) Call the change function to construct the follow-up test case object
    TestCase Tf_case = change(tc);

    // (4) Extract the follow-up input and get the follow-up output (Of)
    double* p1_f = Tf_case.p1;
    double* p2_f = Tf_case.p2;
    int n_f = Tf_case.n;
    double Of = cosineDistance(p1_f, p2_f, n_f);

    // (5) Verify whether Os and Of satisfy the metamorphic relation based on [Information 2]
    int is_valid = 0;
    if (Os != Of) {
        is_valid = 1;
    }

    // (6) Free Tf_case or any dynamic memory generated during the process
    // No dynamic memory was allocated in change(), so nothing to free here.

    // (7) Return the verification result
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