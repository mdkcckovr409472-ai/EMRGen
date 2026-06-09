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


double manhattan_dist(int a[], int b[], int n) {
    int i;
    double sum = 0;
    for (i = 0; i < n; i++) {
        sum += abs(a[i] - b[i]);
    }
    return sum;
}


typedef struct {
    int* a; int* b; int n;
} TestCase;

TestCase test_cases[] = {
    { (int[]){}, (int[]){}, 0 },
    { (int[]){5}, (int[]){5}, 1 },
    { (int[]){-3}, (int[]){7}, 1 },
    { (int[]){2, -2}, (int[]){-2, 2}, 2 },
    { (int[]){0, 0}, (int[]){0, 0}, 2 },
    { (int[]){1, 3, 5}, (int[]){5, 3, 1}, 3 },
    { (int[]){-1, -4, 2}, (int[]){3, 0, -2}, 3 },
    { (int[]){10, 20, 30, 40}, (int[]){40, 30, 20, 10}, 4 },
    { (int[]){7, 7, 7, 7}, (int[]){7, 7, 7, 7}, 4 },
    { (int[]){-5, 0, 5, -10}, (int[]){5, -5, 0, 10}, 4 },
    { (int[]){3, 1, 4, 1, 5}, (int[]){5, 9, 2, 6, 5}, 5 },
    { (int[]){-2, -2, -2, -2, -2}, (int[]){2, 2, 2, 2, 2}, 5 },
    { (int[]){0, 1, 0, 1, 0}, (int[]){1, 0, 1, 0, 1}, 5 },
    { (int[]){8, -3, 6, -1, 2, 4}, (int[]){-8, 3, -6, 1, -2, -4}, 6 },
    { (int[]){1, 2, 3, 2, 1, 0}, (int[]){0, 1, 2, 3, 4, 5}, 6 },
    { (int[]){-10, 20, -30, 40, -50}, (int[]){10, -20, 30, -40, 50}, 5 },
    { (int[]){5, 5, 5, 5, 5, 5, 5}, (int[]){5, 5, 5, 5, 5, 5, 5}, 7 },
    { (int[]){1, -1, 1, -1, 1, -1, 1}, (int[]){-1, 1, -1, 1, -1, 1, -1}, 7 },
    { (int[]){0, 0, 0, 0, 0, 0, 0, 0}, (int[]){0, 0, 0, 0, 0, 0, 0, 0}, 8 },
    { (int[]){3, -6, 9, -12, 15, -18}, (int[]){-3, 6, -9, 12, -15, 18}, 6 },
    { (int[]){2, 4, 6, 8, 10}, (int[]){1, 3, 5, 7, 9}, 5 },
    { (int[]){-1, -2, -3, -4, -5, -6}, (int[]){-6, -5, -4, -3, -2, -1}, 6 },
    { (int[]){7, 0, -7, 0, 7}, (int[]){-7, 0, 7, 0, -7}, 5 },
    { (int[]){100, -100, 50, -50}, (int[]){-100, 100, -50, 50}, 4 },
    { (int[]){1, 2, 3, 4, 5, 6, 7, 8, 9}, (int[]){9, 8, 7, 6, 5, 4, 3, 2, 1}, 9 },
    { (int[]){0, 5, 0, 5, 0, 5}, (int[]){5, 0, 5, 0, 5, 0}, 6 },
    { (int[]){-3, 0, 3, 0, -3}, (int[]){3, 0, -3, 0, 3}, 5 },
    { (int[]){2, -2, 2, -2, 2, -2, 2}, (int[]){-2, 2, -2, 2, -2, 2, -2}, 7 },
    { (int[]){1, 3, 5, 7, 9, 11, 13, 15}, (int[]){15, 13, 11, 9, 7, 5, 3, 1}, 8 },
    { (int[]){4, 4, 2, 2, 0, 0}, (int[]){0, 0, 2, 2, 4, 4}, 6 }
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc; 
    tf.a = new int[tc.n];
    for (int i = 0; i < tc.n; i++) {
        tf.a[i] = tc.a[i];
    }
    if (tf.n > 0) {
        tf.a[0] = INT_MIN;
    }
    return tf;
}

int check(TestCase tc) {
    double Os = manhattan_dist(tc.a, tc.b, tc.n);
    TestCase Tf_case = change(tc);
    double Of = manhattan_dist(Tf_case.a, Tf_case.b, Tf_case.n);
    int is_valid = 0;
    if (Os >= 0 && Of >= 0) {
        is_valid = 1;
    }
    if (Tf_case.a != tc.a) {
        delete[] Tf_case.a;
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