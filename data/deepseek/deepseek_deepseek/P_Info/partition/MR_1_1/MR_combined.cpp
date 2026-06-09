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
    {(double[]){1.0, 2.0, 3.0, 4.0, 5.0}, 0, 5, 2},
    {(double[]){5.0, 4.0, 3.0, 2.0, 1.0}, 0, 5, 2},
    {(double[]){3.0, 1.0, 4.0, 1.0, 5.0}, 0, 5, 0},
    {(double[]){3.0, 1.0, 4.0, 1.0, 5.0}, 0, 5, 4},
    {(double[]){2.5}, 0, 1, 0},
    {(double[]){9.8, 1.2}, 0, 2, 1},
    {(double[]){-1.5, -3.0, 0.0, 2.2}, 0, 4, 1},
    {(double[]){1.1, 2.2, 3.3}, 1, 3, 1},
    {(double[]){1.1, 2.2, 3.3}, 1, 3, 2},
    {(double[]){5.5, 4.4, 3.3, 2.2, 1.1, 0.0}, 1, 5, 3},
    {(double[]){0.0, 1.0, 2.0, 3.0, 4.0}, 0, 5, 0},
    {(double[]){0.0, 1.0, 2.0, 3.0, 4.0}, 0, 5, 4},
    {(double[]){2.0, 2.0, 2.0, 2.0}, 0, 4, 1},
    {(double[]){3.14, 1.59, 2.65}, 0, 3, 0},
    {(double[]){3.14, 1.59, 2.65}, 0, 3, 2},
    {(double[]){10.1, 20.2, 30.3, 40.4}, 0, 4, 2},
    {(double[]){-5.0, 0.0, 5.0}, 0, 3, 1},
    {(double[]){1.0}, 0, 1, 0},
    {(double[]){7.0, 3.0, 9.0, 5.0, 1.0}, 0, 5, 2},
    {(double[]){6.6, 7.7, 8.8, 9.9}, 1, 4, 2},
    {(double[]){0.5, 1.5, 2.5, 3.5}, 0, 4, 1},
    {(double[]){100.0, 200.0, 150.0}, 0, 3, 0},
    {(double[]){100.0, 200.0, 150.0}, 0, 3, 2},
    {(double[]){-2.0, -1.0, 0.0, 1.0, 2.0}, 1, 4, 2},
    {(double[]){9.0, 8.0, 7.0, 6.0}, 0, 4, 3},
    {(double[]){1.2, 3.4, 5.6, 7.8}, 0, 4, 1},
    {(double[]){0.1, 0.01, 0.001}, 0, 3, 0},
    {(double[]){0.1, 0.01, 0.001}, 0, 3, 2},
    {(double[]){2.0, 4.0, 6.0, 8.0, 10.0}, 2, 5, 3},
    {(double[]){3.0, 6.0, 9.0, 12.0}, 0, 4, 1}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    int length = tf.end - tf.begin;
    double* new_work = new double[length];
    for (int i = 0; i < length; ++i) {
        new_work[i] = tf.work[i] + 1.0;
    }
    tf.work = new_work;
    return tf;
}

int check(TestCase tc) {
    int Os = partition(tc.work, tc.begin, tc.end, tc.pivot);
    TestCase Tf_case = change(tc);
    int Of = partition(Tf_case.work, Tf_case.begin, Tf_case.end, Tf_case.pivot);
    int is_valid = 0;
    if (Os == Of) {
        is_valid = 1;
    }
    delete[] Tf_case.work;
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