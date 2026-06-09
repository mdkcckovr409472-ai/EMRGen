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


double weightedMean(double elements[], double theWeights[], int n) {
    int size = n;
    double sum = 0.0;
    double weightsSum = 0.0;
    for(int i = size; --i >= 0; ) {
        double w = theWeights[i];
        sum += elements[i] * w;
        weightsSum += w;
    }
    return sum / weightsSum;
}


typedef struct {
    double* elements; double* theWeights; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0, 2.0, 3.0}, (double[]){1.0, 1.0, 1.0}, 3},
    {(double[]){5.5}, (double[]){2.0}, 1},
    {(double[]){-2.0, 4.0, -6.0}, (double[]){1.0, 0.5, 2.0}, 3},
    {(double[]){10.0, 20.0, 30.0}, (double[]){0.0, 1.0, 0.0}, 3},
    {(double[]){0.5, 1.5, 2.5}, (double[]){0.2, 0.3, 0.5}, 3},
    {(double[]){3.0, -1.0, 4.0, 0.0, 2.0}, (double[]){2.0, 1.0, 3.0, 0.5, 1.5}, 5},
    {(double[]){7.0, 7.0, 7.0, 7.0}, (double[]){1.0, 2.0, 3.0, 4.0}, 4},
    {(double[]){8.0, 2.0}, (double[]){0.75, 0.25}, 2},
    {(double[]){1.0, 2.0}, (double[]){-1.0, 2.0}, 2},
    {(double[]){0.001, 0.002}, (double[]){0.0001, 0.0002}, 2},
    {(double[]){0.0, -5.0, 10.0}, (double[]){1.0, 1.0, 1.0}, 3},
    {(double[]){4.0, 4.0, 4.0}, (double[]){1.0, 2.0, 3.0}, 3},
    {(double[]){9.0, -3.0, 5.0, 2.0}, (double[]){2.0, 1.0, 3.0, 4.0}, 4},
    {(double[]){1.2, 3.4, 5.6}, (double[]){0.1, 0.2, 0.7}, 3},
    {(double[]){-9.0, 8.0, -7.0}, (double[]){1.0, 1.0, 1.0}, 3},
    {(double[]){2.0, 5.0, 8.0, 11.0}, (double[]){2.0, 2.0, 2.0, 2.0}, 4},
    {(double[]){100.0, 200.0}, (double[]){0.0, 1.0}, 2},
    {(double[]){1.0, 2.0, 3.0}, (double[]){0.1, 0.2, 0.2}, 3},
    {(double[]){1.0, 2.0, 1.0, 2.0}, (double[]){1.0, 1.0, 1.0, 1.0}, 4},
    {(double[]){0.123456, 0.654321, 0.111111}, (double[]){0.333333, 0.333333, 0.333334}, 3},
    {(double[]){5.0, -5.0, 5.0, -5.0, 5.0}, (double[]){1.0, 1.0, 1.0, 1.0, 1.0}, 5},
    {(double[]){10.0, 20.0, 30.0}, (double[]){-1.0, -2.0, 1.0}, 3},
    {(double[]){1.0, 2.0, 3.0, 4.0}, (double[]){0.0, 0.0, 0.0, 5.0}, 4},
    {(double[]){0.0, 0.0}, (double[]){1.0, 2.0}, 2},
    {(double[]){3.0, 6.0, 9.0}, (double[]){0.2, 0.3, 0.5}, 3},
    {(double[]){-2.5, 3.5, -1.5, 4.5, 0.0}, (double[]){1.5, 0.5, 2.0, 1.0, 0.0}, 5},
    {(double[]){7.0, -2.0, 5.0, 1.0}, (double[]){3.0, 0.5, 2.0, 1.5}, 4},
    {(double[]){0.0, 5.0, 10.0}, (double[]){0.0, 1.0, 1.0}, 3},
    {(double[]){-3.0, 3.0}, (double[]){2.0, 2.0}, 2},
    {(double[]){1.0, 2.0, 3.0, 4.0, 5.0}, (double[]){-0.5, 0.5, -0.5, 0.5, 1.0}, 5}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    tf.elements = new double[tc.n];
    for (int i = 0; i < tc.n; ++i) {
        tf.elements[i] = tc.elements[i] * 2;
    }
    return tf;
}

int check(TestCase tc) {
    double Os = weightedMean(tc.elements, tc.theWeights, tc.n);
    TestCase Tf_case = change(tc);
    double Of = weightedMean(Tf_case.elements, Tf_case.theWeights, Tf_case.n);

    int is_valid = 0;
    if (fabs(2 * Os - Of) < 1e-9) {
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