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


int sum(int values[],  int n) {
    int sum = 0;
    for (int i = 0; i < n; i++){
        sum += values[i];
}
    return sum;
}


typedef struct {
    int* values; int n;
} TestCase;

TestCase test_cases[] = {
    { (int[]){1, 2, 3}, 3 },
    { (int[]){}, 0 },
    { (int[]){-5, 10}, 2 },
    { (int[]){0, 0, 0, 0}, 4 },
    { (int[]){5}, 1 },
    { (int[]){-1, -2, -3}, 3 },
    { (int[]){100, -50, 25, -75}, 4 },
    { (int[]){7, 7, 7, 7, 7}, 5 },
    { (int[]){3, 1, 4, 1, 5, 9}, 6 },
    { (int[]){-10, 20, -30, 40, -50}, 5 },
    { (int[]){2, -2, 2, -2}, 4 },
    { (int[]){99, 1}, 2 },
    { (int[]){-100, 0, 100}, 3 },
    { (int[]){8, 6, 7, 5, 3, 0, -1}, 7 },
    { (int[]){-3, -1, 0, 1, 3}, 5 },
    { (int[]){42, -42}, 2 },
    { (int[]){5, -5, 10, -10, 15, -15}, 6 },
    { (int[]){1, -1, 1, -1, 1}, 5 },
    { (int[]){0}, 1 },
    { (int[]){-7, 14, -21, 28}, 4 },
    { (int[]){3, -3, 3, -3, 3, -3}, 6 },
    { (int[]){11, 22, 33, 44, 55}, 5 },
    { (int[]){-9, -8, -7, -6, -5}, 5 },
    { (int[]){2, 4, 6, 8, 10, 12, 14, 16, 18, 20}, 10 },
    { (int[]){-2, -4, -6, -8, -10}, 5 },
    { (int[]){1, 2, 1, 2, 1, 2}, 6 },
    { (int[]){7, 0, 7, 0, 7}, 5 },
    { (int[]){-1, 0, 1}, 3 },
    { (int[]){13, -13, 26, -26}, 4 },
    { (int[]){5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, 10 }
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    if (tf.n > 1) {
        int* new_values = new int[tf.n];
        new_values[0] = tf.values[tf.n - 1];
        for (int i = 1; i < tf.n; i++) {
            new_values[i] = tf.values[i - 1];
        }
        tf.values = new_values;
    }
    return tf;
}

int check(TestCase tc) {
    int Os = sum(tc.values, tc.n);
    TestCase Tf_case = change(tc);
    int Of = sum(Tf_case.values, Tf_case.n);
    int is_valid = (Os == Of) ? 1 : 0;
    if (Tf_case.values != tc.values) {
        delete[] Tf_case.values;
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