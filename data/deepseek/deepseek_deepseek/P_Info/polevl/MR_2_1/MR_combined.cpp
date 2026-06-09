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


double polevl(double x, double coef[], int N){    
    double ans1;
    ans1 = coef[0];
    
    for (int i = 1; i <= N; i++) {
        ans1 = ans1 * x + coef[i];
    }
    return ans1;
}


typedef struct {
    double x; double* coef; int N;
} TestCase;

TestCase test_cases[] = {
    {0.0, (double[]){1.0}, 0},
    {1.0, (double[]){2.0}, 0},
    {-1.0, (double[]){3.0}, 0},
    {2.5, (double[]){1.5}, 0},
    {0.5, (double[]){0.0}, 0},
    {0.0, (double[]){1.0, 2.0}, 1},
    {1.0, (double[]){2.0, 3.0}, 1},
    {-1.0, (double[]){3.0, -1.0}, 1},
    {2.0, (double[]){0.0, 5.0}, 1},
    {-0.5, (double[]){-2.0, 4.0}, 1},
    {1.0, (double[]){1.0, 2.0, 3.0}, 2},
    {2.0, (double[]){3.0, 0.0, -2.0}, 2},
    {-1.0, (double[]){-1.0, -1.0, -1.0}, 2},
    {0.0, (double[]){0.0, 0.0, 0.0}, 2},
    {0.5, (double[]){4.0, -2.0, 1.0}, 2},
    {1.5, (double[]){1.0, 0.0, 0.0, 0.0}, 3},
    {-2.0, (double[]){2.0, -1.0, 0.5, -0.25}, 3},
    {0.0, (double[]){5.0, 10.0, 15.0, 20.0}, 3},
    {3.0, (double[]){-3.0, 2.0, -1.0, 1.0}, 3},
    {-0.25, (double[]){1.0, 2.0, 3.0, 4.0}, 3},
    {2.0, (double[]){1.0, 2.0, 3.0, 4.0, 5.0}, 4},
    {-1.0, (double[]){5.0, -4.0, 3.0, -2.0, 1.0}, 4},
    {0.0, (double[]){10.0}, 0},
    {1.0, (double[]){0.0, 1.0}, 1},
    {-1.0, (double[]){1.0, 0.0, -1.0}, 2},
    {0.5, (double[]){2.0, -4.0, 6.0, -8.0}, 3},
    {1.0, (double[]){1.0, 1.0, 1.0, 1.0, 1.0}, 4},
    {-2.0, (double[]){-1.0, 0.0, 1.0, 0.0, -1.0}, 4},
    {3.0, (double[]){1.0}, 0},
    {0.25, (double[]){3.0, 2.0, 1.0}, 2}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    int N = tc.N;
    double* new_coef = new double[N + 1];
    for (int i = 0; i <= N; i++) {
        new_coef[i] = tc.coef[i] * 0.5;
    }
    tf.coef = new_coef;
    return tf;
}

int check(TestCase tc) {
    double Os = polevl(tc.x, tc.coef, tc.N);
    TestCase Tf_case = change(tc);
    double Of = polevl(Tf_case.x, Tf_case.coef, Tf_case.N);
    int is_valid = 0;
    if (fabs(0.5 * Os - Of) < 1e-12) {
        is_valid = 1;
    }
    delete[] Tf_case.coef;
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