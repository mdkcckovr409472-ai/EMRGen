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


int partition(double work[], int begin, int end, int pivot) {
    double value = work[pivot];
    work[pivot] = work[begin];
    int i = begin + 1;
    int j = end - 1;
    while (i < j) {
        while (i < j && work[j] > value) {
            --j;
        }
        while (i < j && work[i] < value) {
            ++i;
        }
        if (i < j) {
            double tmp = work[i];
            work[i++] = work[j];
            work[j--] = tmp;
        }
    }
    if (i >= end || work[i] > value) {
        --i;
    }
    work[begin] = work[i];
    work[i] = value;
    return i;
}


typedef struct {
    double* work; int begin; int end; int pivot;
} TestCase;

TestCase test_cases[] = {
    { (double[]){5.0, 2.0, 8.0, 6.0, 3.0}, 0, 5, 2 },
    { (double[]){1.0, 4.0, 3.0, 2.0, 5.0}, 0, 5, 1 },
    { (double[]){10.0, -1.0, 7.0, 3.0, 0.0, 2.0}, 1, 5, 3 },
    { (double[]){0.0, 0.0, 0.0, 0.0}, 0, 4, 2 },
    { (double[]){9.5, -3.2, 4.1, 6.6, -2.0, 7.7}, 0, 6, 5 },
    { (double[]){2.5, 3.5, 1.5, 4.5, 0.5}, 0, 5, 0 },
    { (double[]){8.0, 6.0, 7.0, 5.0, 9.0, 1.0, 2.0}, 2, 7, 4 },
    { (double[]){3.3, 2.2, 1.1, 4.4, 5.5}, 1, 5, 3 },
    { (double[]){100.0, -50.0, 25.0, -75.0, 0.0}, 0, 5, 4 },
    { (double[]){1.0, 2.0, 3.0, 4.0, 5.0}, 0, 5, 2 },
    { (double[]){5.0, 4.0, 3.0, 2.0, 1.0}, 0, 5, 2 },
    { (double[]){7.0, 7.0, 2.0, 7.0, 5.0, 7.0}, 0, 6, 3 },
    { (double[]){-10.0, 20.0, -30.0, 40.0, -50.0, 60.0}, 0, 6, 1 },
    { (double[]){0.1, -0.2, 0.3, -0.4, 0.5}, 0, 5, 2 },
    { (double[]){3.14, 2.71, 1.41, 1.73, 2.58}, 0, 5, 0 },
    { (double[]){9.0, 8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0}, 0, 9, 8 },
    { (double[]){1.5, 2.5, 1.5, 2.5, 1.5}, 0, 5, 1 },
    { (double[]){-5.0, -10.0, -3.0, -8.0, -1.0}, 0, 5, 3 },
    { (double[]){0.0, 100.0, -100.0, 50.0, -50.0}, 0, 5, 2 },
    { (double[]){2.0, 2.0, 2.0, 2.0, 2.0}, 0, 5, 4 },
    { (double[]){-1.0, 1.0, -1.0, 1.0, -1.0, 1.0}, 0, 6, 5 },
    { (double[]){10.0, 20.0, 30.0, 40.0, 5.0, 35.0}, 2, 6, 4 },
    { (double[]){3.0, 1.0, 4.0, 1.5, 2.5, 0.5}, 1, 5, 2 },
    { (double[]){6.0, 2.0, 8.0, 3.0, 7.0, 4.0, 5.0}, 0, 7, 6 },
    { (double[]){-2.0, -3.0, -1.0, -4.0, -5.0}, 0, 5, 2 },
    { (double[]){0.0, 1.0, 0.0, 1.0, 0.0}, 0, 5, 1 },
    { (double[]){12.0, 6.0, 18.0, 3.0, 9.0, 15.0}, 0, 6, 3 },
    { (double[]){4.0, 5.0, 6.0, 7.0, 8.0}, 0, 5, 4 },
    { (double[]){8.0, 7.0, 6.0, 5.0, 4.0}, 0, 5, 1 },
    { (double[]){1.0, 3.0, 2.0, 4.0, 0.0, 5.0}, 0, 6, 0 }
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    // Divide each non-zero element in work by 2.0 as per MR
    for (int i = tf.begin; i < tf.end; ++i) {
        if (tf.work[i] != 0.0) {
            tf.work[i] /= 2.0;
        }
    }
    return tf;
}

int check(TestCase tc) {
    int Os = partition(tc.work, tc.begin, tc.end, tc.pivot);

    TestCase Tf_case = change(tc);

    int Of = partition(Tf_case.work, Tf_case.begin, Tf_case.end, Tf_case.pivot);

    int is_valid = (Os == Of) ? 1 : 0;

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