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


int find_max2(int a[], int n) {
    int max = a[0] + a[1];
    for (int i = 0; i < n - 1; i++) {
        if (a[i] + a[i + 1] > max) {
            max = a[i] + a[i + 1];
        }
    }
    return max;
}


typedef struct {
    int* a; int n;
} TestCase;

TestCase test_cases[] = {
    {(int[]){1, 2, 3, 4}, 4},
    {(int[]){-1, -2, -3}, 3},
    {(int[]){5, 5, 5, 5}, 4},
    {(int[]){10, -10, 20, -20}, 4},
    {(int[]){0, 0, 0, 0, 0}, 5},
    {(int[]){100, 200}, 2},
    {(int[]){-5, 10, -2, 8}, 4},
    {(int[]){1, 2}, 2},
    {(int[]){3, 1, 4, 1, 5}, 5},
    {(int[]){-100, 50, 0, 75}, 4},
    {(int[]){2, 4, 6, 8, 10}, 5},
    {(int[]){9, 8, 7, 6, 5}, 5},
    {(int[]){15, 30, 15}, 3},
    {(int[]){-1, 0, 1, 2, 3}, 5},
    {(int[]){6, 2, 9, 4, 7}, 5},
    {(int[]){20, 10, 30, 5}, 4},
    {(int[]){-8, -3, -7, -1}, 4},
    {(int[]){12, 24, 36, 48}, 4},
    {(int[]){1, 3, 2, 4, 5, 7}, 6},
    {(int[]){-10, 20, -30, 40, -50}, 5},
    {(int[]){50, 40, 30, 20, 10}, 5},
    {(int[]){0, 5, 10, 15, 20}, 5},
    {(int[]){7, 3, 8, 2, 9, 1}, 6},
    {(int[]){-2, -4, -6, -8}, 4},
    {(int[]){11, 22, 33, 44, 55}, 5},
    {(int[]){4, 9, 1, 6, 3}, 5},
    {(int[]){25, 15, 35, 5}, 4},
    {(int[]){-9, -5, -1, -3}, 4},
    {(int[]){13, 17, 19, 23}, 4},
    {(int[]){8, 6, 4, 2, 0}, 5}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    int Os = find_max2(tc.a, tc.n);
    int q = 10;
    bool modified = false;
    for (int i = 0; i < tc.n - 1; i++) {
        if (tc.a[i] + tc.a[i + 1] == Os && !modified) {
            int* new_a = new int[tc.n];
            for (int j = 0; j < tc.n; j++) {
                new_a[j] = tc.a[j];
            }
            new_a[i] += q;
            tf.a = new_a;
            modified = true;
        }
    }
    if (!modified) {
        tf.a = tc.a;
    }
    return tf;
}

int check(TestCase tc) {
    int Os = find_max2(tc.a, tc.n);
    TestCase Tf_case = change(tc);
    int Of = find_max2(Tf_case.a, Tf_case.n);
    int q = 10;
    int is_valid = 0;
    if (Os + q <= Of) {
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