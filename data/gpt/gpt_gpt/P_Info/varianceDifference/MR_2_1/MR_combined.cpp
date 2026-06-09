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


double varianceDifference(double sample1[], double sample2[], int n) {
    double sum1 = 0;
    double sum2 = 0;
    double diff = 0;
    double sumDifference = 0;

    for (int i = 0; i < n; i++) {
        sumDifference += sample1[i] - sample2[i];
    }
    
    double meanDifference = sumDifference / n;
    for (int i = 0; i < n; i++) {
        diff = sample1[i] - sample2[i];
        sum1 += (diff - meanDifference) * (diff - meanDifference);
        sum2 += diff - meanDifference;
    }
    return (sum1 - sum2 * sum2 / n) / (n - 1);
}


typedef struct {
    double* sample1; double* sample2; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0, 2.0, 3.0}, (double[]){1.0, 2.0, 3.0}, 3},
    {(double[]){1.0, 2.0, 3.0}, (double[]){3.0, 2.0, 1.0}, 3},
    {(double[]){0.0, -1.0, 4.5}, (double[]){2.0, 3.0, -1.5}, 3},
    {(double[]){-2.5, 0.0, 2.5, 5.0}, (double[]){5.0, 2.5, 0.0, -2.5}, 4},
    {(double[]){3.3, -3.3, 1.1, -1.1, 0.0}, (double[]){0.0, 1.1, -1.1, 3.3, -3.3}, 5},
    {(double[]){10.0, -10.0}, (double[]){-10.0, 10.0}, 2},
    {(double[]){2.2, 4.4, 6.6, 8.8}, (double[]){1.1, 3.3, 5.5, 7.7}, 4},
    {(double[]){-0.5, 0.5, -0.5, 0.5}, (double[]){0.5, -0.5, 0.5, -0.5}, 4},
    {(double[]){7.0, 3.0, -2.0, 4.0, 1.0}, (double[]){1.0, 4.0, -2.0, 3.0, 7.0}, 5},
    {(double[]){0.0, 0.0, 0.0, 0.0}, (double[]){1.0, -1.0, 2.0, -2.0}, 4},
    {(double[]){5.5, 5.5, 5.5}, (double[]){5.5, 5.5, 5.5}, 3},
    {(double[]){-3.0, 2.0, -1.0, 4.0}, (double[]){4.0, -1.0, 2.0, -3.0}, 4},
    {(double[]){1.2, 3.4, 5.6, 7.8, 9.0}, (double[]){9.0, 7.8, 5.6, 3.4, 1.2}, 5},
    {(double[]){-1.0, -2.0, -3.0, -4.0}, (double[]){-4.0, -3.0, -2.0, -1.0}, 4},
    {(double[]){0.1, 0.2, 0.3, 0.4, 0.5}, (double[]){0.5, 0.4, 0.3, 0.2, 0.1}, 5},
    {(double[]){2.0, -2.0, 2.0, -2.0, 2.0}, (double[]){-2.0, 2.0, -2.0, 2.0, -2.0}, 5},
    {(double[]){3.14, 2.71, 1.41, 0.0}, (double[]){0.0, 1.41, 2.71, 3.14}, 4},
    {(double[]){-5.0, 0.0, 5.0}, (double[]){5.0, 0.0, -5.0}, 3},
    {(double[]){1.0, 1.0, 2.0, 2.0, 3.0, 3.0}, (double[]){3.0, 3.0, 2.0, 2.0, 1.0, 1.0}, 6},
    {(double[]){-0.1, 0.2, -0.3, 0.4}, (double[]){0.4, -0.3, 0.2, -0.1}, 4},
    {(double[]){4.5, -4.5, 4.5, -4.5}, (double[]){-4.5, 4.5, -4.5, 4.5}, 4},
    {(double[]){2.5, 3.5, 4.5}, (double[]){3.0, 3.0, 3.0}, 3},
    {(double[]){0.0, 1.0, 0.0, 1.0, 0.0}, (double[]){1.0, 0.0, 1.0, 0.0, 1.0}, 5},
    {(double[]){-2.2, 2.2, -2.2, 2.2}, (double[]){2.2, -2.2, 2.2, -2.2}, 4},
    {(double[]){5.0, 0.0, -5.0, 0.0}, (double[]){0.0, 5.0, 0.0, -5.0}, 4},
    {(double[]){1.5, 2.5, 3.5, 4.5}, (double[]){4.5, 3.5, 2.5, 1.5}, 4},
    {(double[]){-1.5, -0.5, 0.5, 1.5}, (double[]){1.5, 0.5, -0.5, -1.5}, 4},
    {(double[]){0.0, 0.0, 0.0, 0.0, 0.0}, (double[]){0.0, 0.0, 0.0, 0.0, 0.0}, 5},
    {(double[]){9.9, -9.9, 9.9, -9.9, 9.9}, (double[]){-9.9, 9.9, -9.9, 9.9, -9.9}, 5},
    {(double[]){3.0, 1.0, 4.0, 1.5}, (double[]){1.5, 4.0, 1.0, 3.0}, 4},
    {(double[]){2.0, 0.0, -2.0, 0.0, 2.0}, (double[]){0.0, 2.0, 0.0, -2.0, 0.0}, 5}
};
int num_test_cases = 31;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    if (tc.n > 0) {
        double* newSample1 = new double[tc.n];
        for (int i = 0; i < tc.n; i++) {
            newSample1[i] = tc.sample1[i] - 3.0;
        }
        tf.sample1 = newSample1;
    }
    return tf;
}

int check(TestCase tc) {
    double Os = varianceDifference(tc.sample1, tc.sample2, tc.n);
    TestCase Tf_case = change(tc);
    double Of = varianceDifference(Tf_case.sample1, Tf_case.sample2, Tf_case.n);

    int is_valid = (Os == Of) ? 1 : 0;

    if (Tf_case.sample1 != tc.sample1) {
        delete[] Tf_case.sample1;
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