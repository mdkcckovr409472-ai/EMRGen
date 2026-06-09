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


double kurtosis(double data[], int n) {
    double sum = 0;
    double sumPD = 0;
    double sumSq = 0;
    for (int i = 0; i < n; i++) {
        sum += data[i];
        sumSq += data[i] * data[i];
    }
    double mean = sum / n;
    double standardDeviation = sqrt((sumSq - mean * sum) / n);
    for (int i = 0; i < n; i++) {
        sumPD += pow(data[i] - mean, 4);
    }
    double moment4 = sumPD / n;
    return -3 + moment4 / (standardDeviation * standardDeviation * standardDeviation * standardDeviation);
}


typedef struct {
    double* data; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0, 2.0}, 2},
    {(double[]){-1.5, 0.5, 2.5}, 3},
    {(double[]){0.0, 0.0, 1.0, -1.0}, 4},
    {(double[]){3.3, -2.2, 5.5, -4.4, 0.0}, 5},
    {(double[]){10.0, -10.0, 5.0, -5.0, 2.5, -2.5}, 6},
    {(double[]){1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7}, 7},
    {(double[]){-3.0, -1.0, 0.0, 1.0, 3.0, 5.0, -5.0, 2.0}, 8},
    {(double[]){0.5, -0.5, 0.25, -0.25, 0.75, -0.75, 1.0, -1.0, 0.0}, 9},
    {(double[]){20.0, 2.0, 18.0, 4.0, 16.0, 6.0, 14.0, 8.0, 12.0, 10.0}, 10},
    {(double[]){-20.0, -2.0, -18.0, -4.0, -16.0, -6.0, -14.0, -8.0, -12.0, -10.0}, 10},
    {(double[]){0.0, 1.0, 0.0, 1.0, 0.0, 1.0}, 6},
    {(double[]){5.5, 5.5, -5.5, -5.5, 0.0, 0.0}, 6},
    {(double[]){3.1415, 2.718, 1.618, -1.0, -2.0, -3.0}, 6},
    {(double[]){-0.1, 0.2, -0.3, 0.4, -0.5, 0.6, -0.7, 0.8}, 8},
    {(double[]){100.0, -50.0, 25.0, -12.5, 6.25, -3.125, 1.5625}, 7},
    {(double[]){0.03, 0.01, 0.05, 0.02, 0.04}, 5},
    {(double[]){-0.04, -0.01, -0.05, -0.02, -0.03}, 5},
    {(double[]){9.9, -9.9, 8.8, -8.8, 7.7, -7.7, 6.6, -6.6}, 8},
    {(double[]){1.0, 1.0, 1.0, 2.0, 2.0, 2.0}, 6},
    {(double[]){-1.0, -1.0, -1.0, 0.0, 0.0, 1.0, 1.0, 1.0}, 8},
    {(double[]){2.5, -2.5, 2.5, -2.5, 2.5, -2.5}, 6},
    {(double[]){3.0, 3.0, 3.0, 3.0, 4.0}, 5},
    {(double[]){-3.0, -3.0, -3.0, -3.0, -4.0}, 5},
    {(double[]){0.0, 0.0, 0.0, 1.0, -1.0, 2.0, -2.0}, 7},
    {(double[]){5.0, -5.0, 5.0, -5.0, 5.0, -5.0, 5.0, -5.0}, 8},
    {(double[]){4.8, 1.2, 6.0, 2.4, 7.2, 3.6}, 6},
    {(double[]){-4.8, -1.2, -6.0, -2.4, -7.2, -3.6}, 6},
    {(double[]){0.0, 2.0, -2.0, 4.0, -4.0, 6.0, -6.0}, 7},
    {(double[]){100.0, 0.0, -100.0, 50.0, -50.0}, 5},
    {(double[]){0.123, -0.456, 0.789, -0.321, 0.654}, 5}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    // Reuse original TestCase struct, only sort data array ascending
    std::sort(tc.data, tc.data + tc.n);
    return tc;
}

int check(TestCase tc) {
    // Source output
    double Os = kurtosis(tc.data, tc.n);

    // Construct follow-up input
    TestCase Tf_case = change(tc);

    // Follow-up output
    double Of = kurtosis(Tf_case.data, Tf_case.n);

    // Verify Os == Of, allow tiny floating point tolerance
    int is_valid = (fabs(Os - Of) < 1e-12) ? 1 : 0;

    // No new dynamic memory allocated in change(), so no free needed here

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