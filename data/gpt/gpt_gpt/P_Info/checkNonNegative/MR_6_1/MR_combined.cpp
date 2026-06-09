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


bool checkNonNegative(double a[], int n){
    
    for (int i = 0; i < n; i++)
    {
        if (a[i] < 0)
        {
            return false;
        }
    }
    return true; 
}


typedef struct {
    double* a; int n;
} TestCase;

TestCase test_cases[] = {
    { (double[]){}, 0 },
    { (double[]){0.0}, 1 },
    { (double[]){2.5}, 1 },
    { (double[]){-1.0}, 1 },
    { (double[]){3.1, 4.2, 5.0}, 3 },
    { (double[]){0.0, 0.0, 0.0}, 3 },
    { (double[]){1.0, 0.0, 2.5}, 3 },
    { (double[]){5.5, 2.2, -0.5}, 3 },
    { (double[]){-0.3, 1.1, 2.2}, 3 },
    { (double[]){1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0}, 10 },
    { (double[]){1.0, -2.0, 3.0, -4.0, 5.0, -6.0, 7.0, -8.0, 9.0, -10.0}, 10 },
    { (double[]){0.5, 2.3, 4.1, 3.3, 1.0}, 5 },
    { (double[]){5.0, 3.0, -1.0, 2.0, 4.0}, 5 },
    { (double[]){7.7, 7.7, 7.7}, 3 },
    { (double[]){2.0, 0.5, 2.0}, 3 },
    { (double[]){-2.2, -2.2, -2.2}, 3 },
    { (double[]){1.0, 0.0, 2.0, 0.0}, 4 },
    { (double[]){1.0, -1.0, 2.0, -2.0}, 4 },
    { (double[]){3.3, 2.2, 1.1, 4.4, 5.5, 6.6}, 6 },
    { (double[]){3.3, -2.2, 1.1, -4.4, 5.5, -6.6}, 6 },
    { (double[]){0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8}, 8 },
    { (double[]){0.1, -0.2, 0.3, -0.4, 0.5, -0.6, 0.7, -0.8}, 8 },
    { (double[]){12345.6}, 1 },
    { (double[]){-9876.5}, 1 },
    { (double[]){2.2, 3.3}, 2 },
    { (double[]){-2.2, -3.3}, 2 },
    { (double[]){0.0, -1.0}, 2 },
    { (double[]){4.4, -3.3, 2.2, -1.1, 0.0, 1.1, -2.2, 3.3, -4.4}, 9 },
    { (double[]){4.4, 3.3, 2.2, 1.1, 0.0, 1.1, 2.2, 3.3, 4.4}, 9 },
    { (double[]){-5.5, 0.0, 2.2, -1.1, 3.3, 0.0, -0.5}, 7 }
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;

    if (tf.n > 0) {
        double* rotated = new double[tf.n];
        rotated[0] = tf.a[tf.n - 1];
        for (int i = 1; i < tf.n; i++) {
            rotated[i] = tf.a[i - 1];
        }
        tf.a = rotated;
    }
    return tf;
}

int check(TestCase tc) {
    // (1) Extract the source input (Ts)
    double* Ts = tc.a;
    int n = tc.n;

    // (2) Call the function under test from [Information 1] to get the source output (Os)
    bool Os = checkNonNegative(Ts, n);

    // (3) Call the change function to construct the follow-up test case object
    TestCase Tf_case = change(tc);

    // (4) Extract the follow-up input and get the follow-up output (Of)
    bool Of = checkNonNegative(Tf_case.a, Tf_case.n);

    // (5) Verify whether Os and Of satisfy the metamorphic relation based on [Information 2]
    int is_valid = 0;
    if (Os == Of) {
        is_valid = 1;
    }

    // (6) Free Tf_case or any dynamic memory generated during the process
    if (Tf_case.a != tc.a) {
        delete[] Tf_case.a;
    }

    // (7) Return the verification result
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