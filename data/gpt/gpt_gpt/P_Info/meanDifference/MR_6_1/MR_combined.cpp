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


double meanDifference(double sample1[], double sample2[], int n ) {
    double sumDifference = 0;
    for (int i = 0; i < n; i++) {
        sumDifference += sample1[i] - sample2[i];
    }
    return sumDifference / n;
}


typedef struct {
    double* sample1; double* sample2; int n;
} TestCase;

TestCase test_cases[] = {
    { (double[]){}, (double[]){}, 0 },
    { (double[]){5.0}, (double[]){3.0}, 1 },
    { (double[]){-2.5}, (double[]){1.5}, 1 },
    { (double[]){1.0, 4.0}, (double[]){0.5, 2.0}, 2 },
    { (double[]){0.0, -3.0}, (double[]){2.0, -1.0}, 2 },
    { (double[]){1.2, -0.5, 3.3}, (double[]){1.0, -1.0, 2.0}, 3 },
    { (double[]){0.0, 0.0, 0.0}, (double[]){0.0, 0.0, 0.0}, 3 },
    { (double[]){2.0, 2.0, 2.0, 2.0}, (double[]){1.0, 1.0, 1.0, 1.0}, 4 },
    { (double[]){5.0, -2.0, 0.0, 3.5}, (double[]){3.0, -1.0, 1.0, 2.5}, 4 },
    { (double[]){0.1, 2.2, -1.1, 4.4, -3.3}, (double[]){0.0, 2.0, -1.0, 4.0, -3.0}, 5 },
    { (double[]){10.0, -10.0, 5.0, -5.0, 0.0}, (double[]){0.0, 0.0, 0.0, 0.0, 0.0}, 5 },
    { (double[]){1.5, 2.5, 3.5, 4.5, 5.5, 6.5}, (double[]){1.0, 2.0, 3.0, 4.0, 5.0, 6.0}, 6 },
    { (double[]){-1.0, 2.0, -3.0, 4.0, -5.0, 6.0}, (double[]){1.0, -2.0, 3.0, -4.0, 5.0, -6.0}, 6 },
    { (double[]){7.0, -2.0, 0.5, -1.5, 3.0, -4.0, 2.0}, (double[]){5.0, -3.0, 0.0, -2.0, 2.0, -3.0, 1.0}, 7 },
    { (double[]){0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, (double[]){1.0, -1.0, 1.0, -1.0, 1.0, -1.0, 1.0}, 7 },
    { (double[]){1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0}, (double[]){8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0}, 8 },
    { (double[]){0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8}, (double[]){0.8, 0.7, 0.6, 0.5, 0.4, 0.3, 0.2, 0.1}, 8 },
    { (double[]){9.0, 8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0}, (double[]){1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0}, 9 },
    { (double[]){-0.5, 1.5, -2.5, 3.5, -4.5, 5.5, -6.5, 7.5, -8.5}, (double[]){0.5, -1.5, 2.5, -3.5, 4.5, -5.5, 6.5, -7.5, 8.5}, 9 },
    { (double[]){2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0}, (double[]){1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0}, 10 },
    { (double[]){0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0}, (double[]){1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0}, 10 },
    { (double[]){3.14, 2.71, 1.41}, (double[]){3.0, 2.0, 1.0}, 3 },
    { (double[]){-1.0, -2.0, -3.0, -4.0}, (double[]){-4.0, -3.0, -2.0, -1.0}, 4 },
    { (double[]){5.0, 5.0, 5.0, 5.0, 5.0}, (double[]){3.0, 4.0, 5.0, 6.0, 7.0}, 5 },
    { (double[]){-10.0, 20.0, -30.0, 40.0, -50.0, 60.0}, (double[]){0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, 6 },
    { (double[]){0.0, 0.0, 5.0, 5.0, 10.0, 10.0}, (double[]){1.0, 1.0, 4.0, 4.0, 9.0, 9.0}, 6 },
    { (double[]){0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7}, (double[]){0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, 7 },
    { (double[]){-5.0, -4.0, -3.0, -2.0, -1.0, 0.0, 1.0, 2.0}, (double[]){-2.0, -3.0, -4.0, -5.0, 0.0, 1.0, 2.0, 3.0}, 8 },
    { (double[]){0.5, 1.5, 2.5, 3.5, 4.5, 5.5, 6.5, 7.5, 8.5}, (double[]){0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0}, 9 },
    { (double[]){-0.2, 0.3, -0.4, 0.5, -0.6, 0.7, -0.8, 0.9, -1.0, 1.1}, (double[]){0.2, -0.3, 0.4, -0.5, 0.6, -0.7, 0.8, -0.9, 1.0, -1.1}, 10 }
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    // Allocate new array for sample1 to avoid modifying original test case data
    tf.sample1 = new double[tc.n];
    // Copy original sample1 data
    for (int i = 0; i < tc.n; ++i) {
        tf.sample1[i] = tc.sample1[i];
    }
    // Set first element to maximum double value
    tf.sample1[0] = std::numeric_limits<double>::max();
    // sample2 pointer remains the same (reuse original)
    return tf;
}

int check(TestCase tc) {
    // Calculate source output Os
    double Os = meanDifference(tc.sample1, tc.sample2, tc.n);
    
    // Construct follow-up test case Tf
    TestCase Tf_case = change(tc);
    
    // Calculate follow-up output Of
    double Of = meanDifference(Tf_case.sample1, Tf_case.sample2, Tf_case.n);
    
    // Verify MR: Of > Os
    int is_valid = Of > Os ? 1 : 0;
    
    // Free dynamic memory allocated in change()
    delete[] Tf_case.sample1;
    
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