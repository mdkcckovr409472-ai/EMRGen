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


double sumOfLogarithms(double elements[], int n) {
    double logsum = 0;
    for(int i = 0; i < n; i++) {
        logsum += log(elements[i]);
    }
    return logsum;
}


typedef struct {
    double* elements; int n;
} TestCase;

TestCase test_cases[] = {
    { (double[]){}, 0 },
    { (double[]){1.0}, 1 },
    { (double[]){2.71828}, 1 },
    { (double[]){0.5, 4.0}, 2 },
    { (double[]){3.0, 0.2, 5.5}, 3 },
    { (double[]){10.0, 0.1, 7.2, 2.5}, 4 },
    { (double[]){1.5, 1.5, 1.5}, 3 },
    { (double[]){9.9, 0.3, 4.4, 8.8, 2.2}, 5 },
    { (double[]){0.75, 3.33, 0.66, 5.55}, 4 },
    { (double[]){4.0, 1.0, 5.0, 2.0, 6.0, 3.0}, 6 },
    { (double[]){0.7, 0.9, 0.5, 0.8, 0.6}, 5 },
    { (double[]){12.5, 3.3, 7.7, 2.2, 9.9, 5.5, 1.1}, 7 },
    { (double[]){1.75, 0.25, 2.25, 0.75, 1.25}, 5 },
    { (double[]){25.0, 100.0, 12.5, 50.0}, 4 },
    { (double[]){6.66, 0.33, 10.0, 4.44, 2.22, 8.88}, 6 },
    { (double[]){1.618, 3.1415, 0.5772, 2.718}, 4 },
    { (double[]){0.55, 0.99, 0.11, 0.77, 0.33, 0.88, 0.22, 0.66, 0.44}, 9 },
    { (double[]){5.5, 5.5, 5.5, 5.5, 5.5}, 5 },
    { (double[]){8.0, 2.0, 16.0, 4.0}, 4 },
    { (double[]){0.4, 1.0, 0.2, 0.9, 0.5, 0.1, 0.8, 0.3, 0.7, 0.6}, 10 },
    { (double[]){5.5, 0.1, 7.7, 2.2, 4.4, 3.3, 1.1, 6.6}, 8 },
    { (double[]){12.0, 9.0, 24.0, 3.0, 6.0}, 5 },
    { (double[]){1.345, 0.456, 0.123, 1.012, 0.789}, 5 },
    { (double[]){19.0, 3.14, 13.37, 7.13, 42.0}, 5 },
    { (double[]){0.85, 0.95, 0.75, 0.9, 0.8}, 5 },
    { (double[]){5.0, 2.5, 10.0, 2.5, 7.5}, 5 },
    { (double[]){3.33, 0.33, 5.33, 2.33, 1.33, 4.33}, 6 },
    { (double[]){10.0, 0.01, 100.0, 1.0, 0.1}, 5 },
    { (double[]){0.8, 0.2, 1.2, 0.6, 0.4}, 5 },
    { (double[]){3.0, 3.0, 3.0, 3.0, 3.0, 3.0}, 6 }
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    // Allocate new memory to hold a copy of the original array
    double* new_elements = new double[tc.n];
    for (int i = 0; i < tc.n; i++) {
        new_elements[i] = tc.elements[i];
    }
    // Sort in descending order
    std::sort(new_elements, new_elements + tc.n, std::greater<double>());
    tf.elements = new_elements;
    return tf;
}

int check(TestCase tc) {
    // (1) Extract source input Ts
    double* Ts = tc.elements;
    int n = tc.n;
    // (2) Call function under test to get Os
    double Os = sumOfLogarithms(Ts, n);
    // (3) Construct follow-up test case object
    TestCase Tf_case = change(tc);
    // (4) Extract follow-up input and get Of
    double* Tf = Tf_case.elements;
    int n_f = Tf_case.n;
    double Of = sumOfLogarithms(Tf, n_f);
    // (5) Verify MR: Os == Of (allow a small floating point tolerance)
    int is_valid = 0;
    if (std::abs(Os - Of) < 1e-12) {
        is_valid = 1;
    }
    // (6) Free allocated memory
    if (Tf_case.elements != tc.elements) {
        delete[] Tf_case.elements;
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