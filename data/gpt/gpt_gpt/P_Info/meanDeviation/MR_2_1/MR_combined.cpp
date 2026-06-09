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


double meanDeviation(double elements[], double mean, int n) {
    int size = n;
    double sum = 0;
    for (int i = size; --i >= 0; ) {
        sum += fabs(elements[i] - mean);
    }
    return sum / size;
}


typedef struct {
    double* elements; double mean; int n;
} TestCase;

TestCase test_cases[] = {
    { (double[]){1.0, 2.0, 3.0}, 2.0, 3 },
    { (double[]){5.5, 5.5, 5.5}, 5.5, 3 },
    { (double[]){-1.0, 0.0, 1.0}, 0.0, 3 },
    { (double[]){10.0, -10.0, 5.0, -5.0}, 0.0, 4 },
    { (double[]){2.5, 3.5}, 3.0, 2 },
    { (double[]){0.0}, 0.0, 1 },
    { (double[]){1.2, -1.2, 3.4, -3.4, 0.0}, 0.0, 5 },
    { (double[]){4.0, 4.0, 2.0, 6.0}, 4.0, 4 },
    { (double[]){7.0, 2.0, 5.0}, 5.0, 3 },
    { (double[]){-5.0, -3.0, -1.0, 1.0, 3.0, 5.0}, 0.0, 6 },
    { (double[]){8.0, 6.0, 4.0, 2.0, 0.0}, 4.0, 5 },
    { (double[]){1.0, 2.0, 1.0, 2.0}, 1.5, 4 },
    { (double[]){-2.0, -2.0, -2.0, -2.0}, -2.0, 4 },
    { (double[]){3.1415, 2.718, 1.618}, 2.5, 3 },
    { (double[]){0.5, -0.5, 0.5, -0.5}, 0.0, 4 },
    { (double[]){9.0, 1.0, 5.0, 5.0}, 5.0, 4 },
    { (double[]){-1.0, 2.0, -3.0, 4.0}, 0.5, 4 },
    { (double[]){6.0, -6.0, 3.0, -3.0}, 0.0, 4 },
    { (double[]){2.0, 2.1, 1.9, 2.05, 1.95}, 2.0, 5 },
    { (double[]){-0.1, 0.1, -0.2, 0.2}, 0.0, 4 },
    { (double[]){5.0, 5.0, 5.0, 5.0, 5.0}, 5.0, 5 },
    { (double[]){-4.0, 0.0, 4.0}, 0.0, 3 },
    { (double[]){1.0, 3.0, 5.0, 7.0}, 4.0, 4 },
    { (double[]){-2.5, 0.0, 2.5}, 0.0, 3 },
    { (double[]){0.0, 0.0, 0.0}, 1.0, 3 },
    { (double[]){-3.3, -1.1, 0.0, 1.1, 3.3}, 0.0, 5 },
    { (double[]){2.0, -2.0, 2.0, -2.0, 2.0}, 0.0, 5 },
    { (double[]){0.25, 0.75, 0.5}, 0.5, 3 },
    { (double[]){-1.5, -0.5, 0.5, 1.5}, 0.0, 4 },
    { (double[]){3.0, 3.0, 6.0, 0.0}, 3.0, 4 }
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    // Sort the elements array in ascending order to construct Tf
    // Since we must reuse the original data, and cannot modify tc.elements directly (to keep ts input intact),
    // we allocate new dynamic memory for sorted array
    double* sorted_elements = new double[tc.n];
    for (int i = 0; i < tc.n; ++i) {
        sorted_elements[i] = tc.elements[i];
    }
    // Simple std::sort requires <algorithm> header; 
    // If allowed, include and use it, otherwise implement basic sort here.
    // Assuming including <algorithm> is allowed.
    std::sort(sorted_elements, sorted_elements + tc.n);

    tf.elements = sorted_elements;
    return tf;
}

int check(TestCase tc) {
    // (1) Extract the source input (Ts)
    double* Ts = tc.elements;
    int n = tc.n;
    double mean = tc.mean;

    // (2) Call the function under test to get the source output (Os)
    double Os = meanDeviation(Ts, mean, n);

    // (3) Call change() to construct the follow-up test case object
    TestCase Tf_case = change(tc);

    // (4) Extract the follow-up input and get the follow-up output (Of)
    double* Tf = Tf_case.elements;
    double Of = meanDeviation(Tf, mean, n);

    // (5) Verify whether Os and Of satisfy MR: Os == Of
    // Because double equality can be unstable, use a small epsilon for comparison
    const double EPSILON = 1e-12;
    int is_valid = (fabs(Os - Of) < EPSILON) ? 1 : 0;

    // (6) Free dynamic memory allocated in change()
    if (Tf_case.elements != tc.elements) {
        delete[] Tf_case.elements;
        Tf_case.elements = nullptr;
    }

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