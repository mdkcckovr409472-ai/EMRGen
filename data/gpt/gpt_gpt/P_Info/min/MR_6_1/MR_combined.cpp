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


double min(double elements[], int n) {
    int size = n;
    double min = elements[size - 1];
    for (int i = size - 1; --i >= 0; ) {
        if (elements[i] < min) {
            min = elements[i];
        }
    }
    return min;
}


typedef struct {
    double* elements; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){5.0}, 1},
    {(double[]){-1.0, 2.0}, 2},
    {(double[]){0.0, 0.0, 0.0}, 3},
    {(double[]){3.2, 1.5, 4.8, 2.2}, 4},
    {(double[]){-5.5, -3.3, -9.9, -1.1}, 4},
    {(double[]){10.0, -10.0, 5.0, -5.0}, 4},
    {(double[]){2.2, 2.2, 2.2}, 3},
    {(double[]){7.7, 3.3, 5.5, 1.1, 9.9}, 5},
    {(double[]){-0.5, 0.5, -0.5, 0.5}, 4},
    {(double[]){100.0, 50.0, 75.0, 25.0, 0.0}, 5},
    {(double[]){-100.0, -50.0, -75.0, -25.0, -1.0}, 5},
    {(double[]){3.1415, 2.7182, 1.618, 0.5772}, 4},
    {(double[]){-2.0, 2.0, -2.0, 2.0, -2.0}, 5},
    {(double[]){9.9, 8.8, 7.7, 6.6, 5.5, 4.4}, 6},
    {(double[]){-1.1, -2.2, -3.3, -4.4, -5.5}, 5},
    {(double[]){0.001, 0.0001, 0.01, 0.1}, 4},
    {(double[]){-0.001, -0.0001, -0.01, -0.1}, 4},
    {(double[]){5.5, 3.3, 5.5, 3.3, 1.1}, 5},
    {(double[]){1.0, -1.0, 1.0, -1.0, 1.0, -1.0}, 6},
    {(double[]){8.0, 6.0, 7.0, 5.0, 3.0, 4.0, 2.0}, 7},
    {(double[]){2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0}, 7},
    {(double[]){-3.0, 0.0, 3.0, -6.0, 9.0}, 5},
    {(double[]){1.5, 2.5, 3.5, 4.5, 0.5}, 5},
    {(double[]){-2.5, -1.5, -0.5, 0.5, 1.5}, 5},
    {(double[]){0.0, -0.0, 0.0, -0.0}, 4},
    {(double[]){-9.9, 9.9, -8.8, 8.8, -7.7, 7.7}, 6},
    {(double[]){3.0, 1.0, 4.0, 1.5, 5.0, 9.0, 2.6}, 7},
    {(double[]){-1.2, 3.4, -5.6, 7.8, -9.0, 11.2}, 6},
    {(double[]){0.123, 0.456, 0.789, 0.012}, 4},
    {(double[]){-0.123, -0.456, -0.789, -0.012}, 4}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    // Reuse the original test case object and elements pointer
    // Sort the array elements in ascending order to construct follow-up input
    TestCase tf = tc;
    // Create a new array to avoid modifying original data
    double* sorted_elements = new double[tc.n];
    for (int i = 0; i < tc.n; i++) {
        sorted_elements[i] = tc.elements[i];
    }
    // Sort the copied array in ascending order
    std::sort(sorted_elements, sorted_elements + tc.n);
    tf.elements = sorted_elements;
    return tf;
}

int check(TestCase tc) {
    // (1) Extract source input Ts
    double* Ts = tc.elements;
    int n = tc.n;

    // (2) Call function under test to get Os
    double Os = min(Ts, n);

    // (3) Construct follow-up test case Tf
    TestCase Tf_case = change(tc);

    // (4) Extract follow-up input and get Of
    double* Tf = Tf_case.elements;
    double Of = min(Tf, Tf_case.n);

    // (5) Verify MR: Os == Of
    int is_valid = 0;
    if (Os == Of) {
        is_valid = 1;
    }

    // (6) Free dynamic memory allocated in change()
    delete[] Tf;

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