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


double sampleVariance(double elements[], double mean, int n) {
    int size = n;
    double sum = 0;
    for (int i = size; --i >= 0; ) {
        double delta = elements[i] - mean;
        sum += delta * delta;
    }
    return sum / (size - 1);
}


typedef struct {
    double* elements; double mean; int n;
} TestCase;

TestCase test_cases[] = {
    { (double[]){1.0, 2.0, 3.0}, 2.0, 3 },
    { (double[]){5.5, -2.2, 7.1, 0.0}, 2.6, 4 },
    { (double[]){10.0, 10.0, 10.0, 10.0}, 10.0, 4 },
    { (double[]){-1.0, 2.5, -3.5, 4.0, -5.0}, -0.6, 5 },
    { (double[]){0.1, 0.2, 0.3, 0.4}, 0.25, 4 },
    { (double[]){100.0, -100.0, 50.0, -50.0}, 0.0, 4 },
    { (double[]){3.1415, 2.7182, 1.618, 0.5772}, 2.013725, 4 },
    { (double[]){-0.5, -0.1, 0.2, 0.8, -0.3}, 0.02, 5 },
    { (double[]){9.9, 8.8, 7.7, 6.6, 5.5, 4.4}, 7.15, 6 },
    { (double[]){1.0, 1.0, 2.0, 2.0, 3.0, 3.0}, 2.0, 6 },
    { (double[]){-10.0, 10.0}, 0.0, 2 },
    { (double[]){0.0, 0.0}, 0.0, 2 },
    { (double[]){0.5, -0.5}, 0.0, 2 },
    { (double[]){1.5, 2.5, 3.5}, 2.5, 3 },
    { (double[]){-2.0, -1.0, 0.0, 1.0, 2.0}, 0.0, 5 },
    { (double[]){0.001, 0.002, 0.003, 0.004}, 0.0025, 4 },
    { (double[]){99.9, 0.1, -99.8, -0.2}, 0.0, 4 },
    { (double[]){5.0, 6.0, 7.0, 8.0, 9.0}, 7.0, 5 },
    { (double[]){-3.3, 4.4, -5.5, 6.6, -7.7, 8.8}, 0.55, 6 },
    { (double[]){2.0, 2.0, 2.0, 3.0}, 2.25, 4 },
    { (double[]){-0.01, 0.01, -0.02, 0.02}, 0.0, 4 },
    { (double[]){1.0, 4.0, 9.0, 16.0}, 7.5, 4 },
    { (double[]){0.0, 1.0, 0.0, 1.0}, 0.5, 4 },
    { (double[]){-1.5, 0.0, 1.5}, 0.0, 3 },
    { (double[]){3.0, -3.0, 3.0, -3.0, 3.0}, 0.6, 5 },
    { (double[]){0.123, 0.456, 0.789}, 0.456, 3 },
    { (double[]){-100.0, -50.0, 0.0, 50.0, 100.0}, 0.0, 5 },
    { (double[]){0.25, 0.75, 0.5}, 0.5, 3 },
    { (double[]){8.0, 6.0, 7.0, 5.0, 9.0}, 7.0, 5 },
    { (double[]){-2.2, -3.3, -4.4, -5.5}, -3.85, 4 }
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    // Reuse the same elements pointer, sort the elements in descending order in place
    double* arr = tc.elements;
    int size = tc.n;
    // Simple in-place sort descending (e.g. std::sort with custom comparator)
    // Since only standard C++ code, implement a simple bubble sort descending
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1 - i; j++) {
            if (arr[j] < arr[j + 1]) {
                double tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
    // Construct tf with the same pointer but array now sorted descending
    TestCase tf = tc;
    // elements pointer reused but content reordered
    return tf;
}

int check(TestCase tc) {
    // Extract source input Ts
    double* Ts_elements = tc.elements;
    double mean = tc.mean;
    int n = tc.n;
    // Calculate source output Os
    double Os = sampleVariance(Ts_elements, mean, n);
    // Construct follow-up input Tf
    TestCase Tf_case = change(tc);
    double* Tf_elements = Tf_case.elements;
    double Of = sampleVariance(Tf_elements, mean, n);
    // Verify metamorphic relation Os == Of with a tolerance (due to double precision)
    int is_valid = 0;
    const double EPSILON = 1e-12;
    if ((Os - Of) < EPSILON && (Of - Os) < EPSILON) {
        is_valid = 1;
    }
    // No dynamic memory allocated in change(), nothing to free here
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