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
    { (int[]){10, 20, 30, 40, 50}, 1, 3, 5 },
    { (int[]){5, -5, 15, -15}, 2, 2, 4 },
    { (int[]){1, 2, 3}, -1, 1, 3 },
    { (int[]){4, 5, 6}, 3, 0, 3 },
    { (int[]){7, 8}, 0, -2, 2 },
    { (int[]){9, 10}, 1, 2, 2 },
    { (int[]){100}, -1, 2, 1 },
    { (int[]){}, 0, 0, 0 },
    { (int[]){42}, 0, 0, 1 },
    { (int[]){-10, 20}, 0, 1, 2 },
    { (int[]){7, -3, 9}, 2, 0, 3 },
    { (int[]){1000, -1000, 500, -500}, 1, 2, 4 },
    { (int[]){3, 8, -2, 7, 0}, 4, 3, 5 },
    { (int[]){-20, 15, 30, -5, 10, 25}, 0, 5, 6 },
    { (int[]){1, 2, 3, 4, 5, 6}, 2, 2, 6 },
    { (int[]){-100, 0, 100}, 1, 2, 3 },
    { (int[]){-1, -2, -3, -4}, 3, 0, 4 },
    { (int[]){9, 8, 7, 6, 5}, 2, 4, 5 },
    { (int[]){0, 0, 0, 0, 0}, 0, 4, 5 },
    { (int[]){-5, 5, 10}, 0, 1, 3 },
    { (int[]){123, -123}, 1, 1, 2 },
    { (int[]){50, 60, 70, 80}, 2, 1, 4 },
    { (int[]){3, -3, 6, -6, 9, -9, 12}, 3, 6, 7 },
    { (int[]){1, 2, 3, 4, 5, 6, 7, 8}, 0, 7, 8 },
    { (int[]){-10, -9, -8, -7, -6, -5, -4, -3, -2}, 4, 5, 9 },
    { (int[]){100, 200, 300, 400, 500}, 2, 3, 5 },
    { (int[]){-200, -100, 0, 100, 200}, 1, 4, 5 },
    { (int[]){0, 1, 2, 3, 4, 5}, 5, 5, 6 },
    { (int[]){7, 14, 21}, 1, 1, 3 },
    { (int[]){-7, 0, 7, 14}, 0, 2, 4 }
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    int* new_a = new int[tc.n];
    for (int idx = 0; idx < tc.n; ++idx) {
        new_a[idx] = tc.a[idx] / 2;
    }
    tf.a = new_a;
    return tf;
}

int check(TestCase tc) {
    double Os = add_two_array_values(tc.a, tc.i, tc.j, tc.n);
    TestCase Tf_case = change(tc);
    double Of = add_two_array_values(Tf_case.a, Tf_case.i, Tf_case.j, Tf_case.n);
    int is_valid = 0;
    if (Of != -100000 && Os != -100000 && (2 * Of <= Os && Os <= 2 * Of + 1)) {
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