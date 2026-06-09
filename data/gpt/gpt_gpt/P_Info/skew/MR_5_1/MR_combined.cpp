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


double skew(double data[], int n) {
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
        sumPD += pow(data[i] - mean, 3);
    }
    double moment3 = sumPD / n;
    
    return moment3 / (standardDeviation * standardDeviation * standardDeviation);
}



typedef struct {
    double* data; int n;
} TestCase;

TestCase test_cases[] = {
    { (double[]){0.0}, 1 },
    { (double[]){1.0, 2.0, 3.0, 2.0, 1.0}, 5 },
    { (double[]){-1.5, -0.5, 0.0, 0.5, 1.5}, 5 },
    { (double[]){2.0, 2.0, 2.0, 2.0}, 4 },
    { (double[]){-3.0, -1.0, 0.0, 4.0, 5.0}, 5 },
    { (double[]){0.2, -0.4, 0.6, -0.8, 1.0}, 5 },
    { (double[]){5.0, 1.0, 4.0, 2.0, 3.0}, 5 },
    { (double[]){-2.0, -2.0, -1.0, 0.0, 1.0, 2.0}, 6 },
    { (double[]){0.0, 0.0, 0.0}, 3 },
    { (double[]){1.0, -1.0, 1.0, -1.0, 1.0}, 5 },
    { (double[]){3.5, 2.1, -4.2, 0.0, 1.7, -2.3}, 6 },
    { (double[]){-0.1, 0.2, -0.3, 0.4, -0.5}, 5 },
    { (double[]){10.0, -10.0, 10.0, -10.0}, 4 },
    { (double[]){0.5, 0.5, -0.5, -0.5}, 4 },
    { (double[]){1.2, 3.4, 5.6, 7.8}, 4 },
    { (double[]){-5.0, -3.0, -1.0, 1.0, 3.0, 5.0}, 6 },
    { (double[]){4.0, 1.0, 0.0, -1.0, -4.0}, 5 },
    { (double[]){2.5, -2.5, 2.5, -2.5, 0.0}, 5 },
    { (double[]){0.0, 1.0, 0.0, -1.0, 0.0}, 5 },
    { (double[]){-2.2, 3.3, -4.4, 5.5, -6.6}, 5 },
    { (double[]){1.0, 2.0, 1.0, 2.0, 1.0, 2.0}, 6 },
    { (double[]){-1.0, -2.0, -3.0, -2.0, -1.0}, 5 },
    { (double[]){0.9, 0.7, 0.5, 0.3, 0.1}, 5 },
    { (double[]){-0.9, -0.7, -0.5, -0.3, -0.1}, 5 },
    { (double[]){3.0, 3.0, -3.0, -3.0, 0.0}, 5 },
    { (double[]){1.0, 1.0, 1.0, 2.0, 2.0, 2.0}, 6 },
    { (double[]){-0.2, 0.0, 0.2, 0.4, -0.4}, 5 },
    { (double[]){5.5, -5.5, 5.5, -5.5, 5.5}, 5 },
    { (double[]){0.0, 2.0, -2.0, 4.0, -4.0, 6.0, -6.0}, 7 },
    { (double[]){1.1, -1.1, 2.2, -2.2, 3.3, -3.3}, 6 }
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    // Allocate new array for follow-up input
    double* newData = new double[tc.n];
    for (int i = 0; i < tc.n; ++i) {
        newData[i] = tc.data[i] / 2.0;
    }
    tf.data = newData;
    return tf;
}

int check(TestCase tc) {
    double Os = skew(tc.data, tc.n);
    TestCase Tf_case = change(tc);
    double Of = skew(Tf_case.data, Tf_case.n);
    
    // Check metamorphic relation Os == Of with tolerance for floating point comparisons
    bool is_valid = false;
    const double epsilon = 1e-12;
    if (std::abs(Os - Of) <= epsilon) {
        is_valid = true;
    }
    
    delete[] Tf_case.data;
    return is_valid ? 1 : 0;
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