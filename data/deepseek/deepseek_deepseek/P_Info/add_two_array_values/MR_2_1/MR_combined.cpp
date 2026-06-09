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


double add_two_array_values(int a[], int i, int j, int n)
{
    if (i < 0 || i >= n || j < 0 || j >= n)
    {
        return -100000;
    }
    else {
        return (a[i] + a[j]) / 2;
    }
    
}


typedef struct {
    int* a; int i; int j; int n;
} TestCase;

TestCase test_cases[] = {
    {(int[]){1, 2, 3, 4, 5}, 0, 1, 5},
    {(int[]){1, 2, 3, 4, 5}, 2, 3, 5},
    {(int[]){1, 2, 3, 4, 5}, 4, 0, 5},
    {(int[]){10, 20}, 0, 1, 2},
    {(int[]){10, 20}, 1, 0, 2},
    {(int[]){-5, 0, 5}, 0, 2, 3},
    {(int[]){-5, 0, 5}, 1, 1, 3},
    {(int[]){100, 200, 300, 400}, 0, 3, 4},
    {(int[]){100, 200, 300, 400}, 1, 2, 4},
    {(int[]){7}, 0, 0, 1},
    {(int[]){1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 4, 5, 10},
    {(int[]){1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 9, 0, 10},
    {(int[]){0, 0, 0, 0}, 0, 2, 4},
    {(int[]){0, 0, 0, 0}, 3, 3, 4},
    {(int[]){-10, -20, -30}, 0, 1, 3},
    {(int[]){-10, -20, -30}, 2, 2, 3},
    {(int[]){2, 4, 6, 8}, 0, 2, 4},
    {(int[]){2, 4, 6, 8}, 3, 1, 4},
    {(int[]){1, 3, 5, 7, 9}, 2, 4, 5},
    {(int[]){1, 3, 5, 7, 9}, 0, 4, 5},
    {(int[]){15, 25, 35, 45}, 0, 0, 4},
    {(int[]){15, 25, 35, 45}, 3, 3, 4},
    {(int[]){-1, 1}, 0, 1, 2},
    {(int[]){-1, 1}, 1, 0, 2},
    {(int[]){1000, 2000, 3000}, 0, 2, 3},
    {(int[]){1000, 2000, 3000}, 1, 1, 3},
    {(int[]){8, 6, 4, 2, 0}, 0, 4, 5},
    {(int[]){8, 6, 4, 2, 0}, 2, 3, 5},
    {(int[]){12, 24, 36}, 0, 1, 3},
    {(int[]){12, 24, 36}, 2, 0, 3}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    int* new_a = new int[tf.n];
    for (int idx = 0; idx < tf.n; ++idx) {
        new_a[idx] = -tf.a[idx];
    }
    tf.a = new_a;
    return tf;
}

int check(TestCase tc) {
    double Os = add_two_array_values(tc.a, tc.i, tc.j, tc.n);
    TestCase Tf_case = change(tc);
    double Of = add_two_array_values(Tf_case.a, Tf_case.i, Tf_case.j, Tf_case.n);
    int is_valid = 0;
    if (Os == -Of) {
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