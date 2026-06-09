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


double average(int a[], int n){
    double suma = 0;
    for (int i = 0; i < n; i++)
    {
        suma += a[i];
    }
    return suma/n;
}


typedef struct {
    int* a; int n;
} TestCase;

TestCase test_cases[] = {
    {(int[]){1, 2, 3, 4, 5}, 5},
    {(int[]){10}, 1},
    {(int[]){0, 0, 0}, 3},
    {(int[]){-1, 0, 1}, 3},
    {(int[]){2, 4, 6, 8}, 4},
    {(int[]){-5, -4, -3, -2, -1}, 5},
    {(int[]){100, 200, 300}, 3},
    {(int[]){1, -1, 2, -2}, 4},
    {(int[]){7, 11, 13, 17, 19}, 5},
    {(int[]){0}, 1},
    {(int[]){15, 25, 35, 45}, 4},
    {(int[]){-10, -20, -30}, 3},
    {(int[]){1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 10},
    {(int[]){50, 100, 150, 200, 250}, 5},
    {(int[]){-7, 7, -14, 14}, 4},
    {(int[]){3, 6, 9, 12, 15, 18}, 6},
    {(int[]){-100, 0, 100}, 3},
    {(int[]){1, 3, 5, 7, 9, 11, 13}, 7},
    {(int[]){20, 40, 60, 80, 100, 120}, 6},
    {(int[]){-2, -1, 0, 1, 2}, 5},
    {(int[]){5, 10, 15, 20, 25, 30, 35}, 7},
    {(int[]){-50, -25, 0, 25, 50}, 5},
    {(int[]){8, 4, 2, 1}, 4},
    {(int[]){12, 24, 36, 48, 60}, 5},
    {(int[]){-3, -6, -9, -12}, 4},
    {(int[]){9, 18, 27}, 3},
    {(int[]){0, 5, 10, 15, 20, 25}, 6},
    {(int[]){-15, -10, -5, 0, 5, 10, 15}, 7},
    {(int[]){6, 12, 18, 24, 30, 36, 42, 48}, 8},
    {(int[]){1, 4, 9, 16, 25}, 5}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    int k = 5;
    int* new_a = new int[tf.n];
    for (int i = 0; i < tf.n; i++) {
        new_a[i] = tf.a[i] + k;
    }
    tf.a = new_a;
    return tf;
}

int check(TestCase tc) {
    double Os = average(tc.a, tc.n);
    TestCase Tf_case = change(tc);
    double Of = average(Tf_case.a, Tf_case.n);
    int k = 5;
    int is_valid = 0;
    if (Os + k == Of) {
        is_valid = 1;
    }
    delete[] Tf_case.a;
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