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
    // Sort the array in ascending order according to MR
    // Since we must reuse the data pointer, sort in place
    std::sort(tf.data, tf.data + tf.n);
    return tf;
}

int check(TestCase tc) {
    // (1) Extract source input
    double* Ts = tc.data;
    int n = tc.n;
    // (2) Get source output
    double Os = skew(Ts, n);
    // (3) Construct follow-up test case object
    TestCase Tf_case = change(tc);
    // (4) Extract follow-up input and output
    double* Tf = Tf_case.data;
    double Of = skew(Tf, n);
    // (5) Verify relation Os == Of with a tolerance for floating-point errors
    int is_valid = 0;
    double tolerance = 1e-12;
    if (fabs(Os - Of) <= tolerance) {
        is_valid = 1;
    }
    // (6) No dynamic memory allocated in change() or here, so no deallocation needed
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