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


double lag1(double elements[], double mean, int n){
    double r1;
    double q = 0;
    double v = (elements[0] - mean) * (elements[0] - mean);
    for (int i = 1; i < n; i++) {
        double delta0 = elements[i - 1] - mean;
        double delta1 = elements[i] - mean;
        q += (delta0 * delta1 - q) / (i + 1);
        v += (delta1 * delta1 - v) / (i + 1);
    }
    r1 = q / v;
    return r1;
}


typedef struct {
    double* elements; double mean; int n;
} TestCase;

TestCase test_cases[] = {
    { (double[]){5.0}, 4.0, 1},
    { (double[]){1.0, 2.0}, 1.5, 2},
    { (double[]){1.0, -1.0, 1.0}, 0.0, 3},
    { (double[]){2.0, 2.0, 2.0, 2.0}, 1.9, 4},
    { (double[]){-3.0, 0.0, 3.0, 6.0, 9.0}, 3.0, 5},
    { (double[]){10.0, -10.0, 10.0, -10.0}, 0.0, 4},
    { (double[]){0.5, 0.5, 0.5}, 0.5, 3},
    { (double[]){-2.5, 1.5, -0.5, 2.5}, 0.0, 4},
    { (double[]){100.0, 200.0, 300.0}, 200.0, 3},
    { (double[]){-1.0, -2.0, -3.0, -4.0}, -2.5, 4},
    { (double[]){0.0, 1.0, 0.0, 1.0, 0.0}, 0.5, 5},
    { (double[]){3.14, 2.71, 1.41, 1.73}, 2.0, 4},
    { (double[]){-5.5, 5.5, -5.5, 5.5, -5.5}, 0.0, 5},
    { (double[]){0.1, 0.2, 0.3, 0.4, 0.5, 0.6}, 0.35, 6},
    { (double[]){-0.1, -0.2, -0.3, -0.4}, -0.25, 4},
    { (double[]){7.0, 7.5, 8.0, 8.5, 9.0}, 8.0, 5},
    { (double[]){-10.0, 0.0, 10.0}, 0.0, 3},
    { (double[]){1.0, 3.0, 5.0, 7.0, 9.0, 11.0}, 6.0, 6},
    { (double[]){2.2, 2.2, 2.2, 2.2, 2.2}, 2.0, 5},
    { (double[]){-3.3, 3.3, -3.3, 3.3, -3.3, 3.3}, 0.0, 6},
    { (double[]){0.0}, 1.0, 1},
    { (double[]){5.5, 5.5}, 5.0, 2},
    { (double[]){-2.0, 2.0, -2.0, 2.0, -2.0}, 0.0, 5},
    { (double[]){1.2, 2.4, 3.6, 4.8}, 3.0, 4},
    { (double[]){9.9, -9.9, 9.9}, 0.0, 3},
    { (double[]){0.25, 0.5, 0.75, 1.0}, 0.625, 4},
    { (double[]){-4.0, -3.0, -2.0, -1.0, 0.0}, -2.0, 5},
    { (double[]){1.0, 2.0, 1.0, 2.0, 1.0, 2.0}, 1.5, 6},
    { (double[]){3.0, -3.0, 3.0, -3.0, 3.0}, 0.0, 5},
    { (double[]){-1.5, 0.0, 1.5}, 0.0, 3}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    if (tc.n > 0) {
        double* reversed = new double[tc.n];
        for (int i = 0; i < tc.n; i++) {
            reversed[i] = tc.elements[tc.n - 1 - i];
        }
        tf.elements = reversed;
    }
    return tf;
}

int check(TestCase tc) {
    double Os = lag1(tc.elements, tc.mean, tc.n);
    TestCase Tf_case = change(tc);
    double Of = lag1(Tf_case.elements, Tf_case.mean, Tf_case.n);
    int is_valid = (Os == Of) ? 1 : 0;
    if (Tf_case.elements != tc.elements) {
        delete[] Tf_case.elements;
    }
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