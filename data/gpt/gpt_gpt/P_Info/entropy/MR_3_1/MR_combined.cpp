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


double entropy(double k[], int n){
    double h = 0;
    double sum_k = 0;
    for (int i = 0; i < n; i++) {
        sum_k += (double) k[i];
    }
    for (int i = 0; i < n; i++) {
        if (k[i] != 0) {
            double p_i = (double) k[i] / sum_k;
            h += p_i * log(p_i);
        }
    }
    return -h;
}


typedef struct {
    double* k; int n;
} TestCase;

TestCase test_cases[] = {
    { (double[]){}, 0 },
    { (double[]){1.0}, 1 },
    { (double[]){0.0}, 1 },
    { (double[]){2.5, 2.5}, 2 },
    { (double[]){3.0, 1.0}, 2 },
    { (double[]){0.0, 4.0, 2.0}, 3 },
    { (double[]){5.5, 1.2, 3.3}, 3 },
    { (double[]){7.0, 0.0, 2.0, 5.0}, 4 },
    { (double[]){1.0, 1.0, 2.0, 2.0, 3.0}, 5 },
    { (double[]){0.5, 2.5, 1.5, 3.5, 4.5, 0.5}, 6 },
    { (double[]){1.0, 0.0, 0.0, 2.0, 3.0, 0.0, 4.0}, 7 },
    { (double[]){2.2, 3.3, 1.1, 4.4, 0.0, 5.5, 6.6, 1.0}, 8 },
    { (double[]){0.0, 1.0, 0.0, 2.0, 0.0, 3.0, 0.0, 4.0, 0.0}, 9 },
    { (double[]){5.0, 4.0, 3.0, 2.0, 1.0, 0.5, 0.5, 1.5, 2.5, 3.5}, 10 },
    { (double[]){1.0, 2.0, 1.0, 2.0, 1.0, 2.0, 1.0, 2.0, 1.0, 2.0, 1.0}, 11 },
    { (double[]){0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2}, 12 },
    { (double[]){3.0, 0.0, 3.0, 0.0, 3.0, 0.0, 3.0, 0.0, 3.0, 0.0, 3.0, 0.0, 3.0}, 13 },
    { (double[]){2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0, 16.0, 18.0, 20.0, 22.0, 24.0, 26.0, 28.0}, 14 },
    { (double[]){1.5, 2.5, 3.5, 4.5, 5.5, 6.5, 7.5, 8.5, 9.5, 10.5, 11.5, 12.5, 13.5, 14.5, 15.5}, 15 },
    { (double[]){0.0, 0.0, 0.0, 1.0}, 4 },
    { (double[]){5.0, 5.0, 5.0, 5.0, 5.0}, 5 },
    { (double[]){9.9, 0.1, 9.8, 0.2, 9.7, 0.3}, 6 },
    { (double[]){3.1415, 2.7182, 1.618, 0.5772, 0.0}, 5 },
    { (double[]){0.25, 0.75, 0.5, 0.25, 0.75, 0.5}, 6 },
    { (double[]){4.0, 2.0, 0.0, 2.0, 4.0}, 5 },
    { (double[]){1.0, 3.0, 5.0, 7.0, 9.0, 11.0, 13.0}, 7 },
    { (double[]){2.0, 2.0, 0.0, 2.0, 2.0, 0.0, 2.0}, 7 },
    { (double[]){0.0, 1.0, 2.0, 0.0, 1.0, 2.0, 0.0, 1.0}, 8 },
    { (double[]){6.0, 3.0, 0.0, 3.0, 6.0, 9.0, 12.0, 15.0, 0.0}, 9 },
    { (double[]){0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5}, 10 }
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    // Multiply all elements by 2 according to MR
    for (int i = 0; i < tf.n; i++) {
        tf.k[i] = tf.k[i] * 2;
    }
    return tf;
}

int check(TestCase tc) {
    // (1) Extract the source input
    double* Ts = tc.k;
    int n = tc.n;
    
    // (2) Call the function under test to get the source output
    double Os = entropy(Ts, n);
    
    // (3) Call change to construct follow-up test case
    TestCase Tf_case = change(tc);
    
    // (4) Extract the follow-up input and get follow-up output
    double* Tf = Tf_case.k;
    double Of = entropy(Tf, n);
    
    // (5) Verify Os == Of according to MR
    // Use a tolerance for floating point comparison
    double epsilon = 1e-12;
    int is_valid = (fabs(Os - Of) < epsilon) ? 1 : 0;
    
    // (6) No dynamic memory allocated in change(), so no deallocation required here
    
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