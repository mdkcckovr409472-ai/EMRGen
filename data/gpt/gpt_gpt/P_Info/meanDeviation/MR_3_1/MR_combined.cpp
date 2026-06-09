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
    double Os = meanDeviation(tc.elements, tc.mean, tc.n);

    TestCase Tf_case = change(tc);
    double Of = meanDeviation(Tf_case.elements, Tf_case.mean, Tf_case.n);

    int is_valid = 0;
    if (Os == Of) {
        is_valid = 1;
    }

    delete[] Tf_case.elements;

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