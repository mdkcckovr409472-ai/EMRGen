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


int dot_product(int a[], int b[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
            sum += a[i] * b[i];
        }
    return sum;
}


typedef struct {
    int* a; int* b; int n;
} TestCase;

TestCase test_cases[] = {
    {(int[]){1, 2, 3}, (int[]){4, 5, 6}, 3},
    {(int[]){}, (int[]){}, 0},
    {(int[]){0}, (int[]){5}, 1},
    {(int[]){-3}, (int[]){7}, 1},
    {(int[]){-1, 2, -3}, (int[]){4, -5, 6}, 3},
    {(int[]){0, 0, 0, 0}, (int[]){0, 0, 0, 0}, 4},
    {(int[]){2, 2, 2}, (int[]){3, 3, 3}, 3},
    {(int[]){1, 1, 1, 1}, (int[]){5, 6, 7, 8}, 4},
    {(int[]){-2, -2, -2}, (int[]){-1, -1, -1}, 3},
    {(int[]){1, 2, 3, 4, 5}, (int[]){5, 4, 3, 2, 1}, 5},
    {(int[]){10, -10}, (int[]){-1, 1}, 2},
    {(int[]){1, 0, -1, 2, -2, 3}, (int[]){3, -3, 2, -2, 1, 0}, 6},
    {(int[]){100, -100}, (int[]){1, 1}, 2},
    {(int[]){1, 1, 1, 1, 1}, (int[]){1, 1, 1, 1, 1}, 5},
    {(int[]){1, -1, 1, -1}, (int[]){-1, 1, -1, 1}, 4},
    {(int[]){7, 8, 9}, (int[]){1, 2, 3}, 3},
    {(int[]){0, 5, 0}, (int[]){10, 0, 20}, 3},
    {(int[]){-5}, (int[]){-5}, 1},
    {(int[]){3, 3}, (int[]){4, 4}, 2},
    {(int[]){-2, 5, -3}, (int[]){7, -8, 9}, 3},
    {(int[]){2, -3, 4, -5}, (int[]){-2, 3, -4, 5}, 4},
    {(int[]){1, 0, 2}, (int[]){3, 4, 5}, 3},
    {(int[]){-1, 2, -3, 4, -5}, (int[]){5, -4, 3, -2, 1}, 5},
    {(int[]){0, 0}, (int[]){0, 0}, 2},
    {(int[]){50, -50, 25}, (int[]){2, 2, 2}, 3},
    {(int[]){1, 2, 1, 2}, (int[]){2, 1, 2, 1}, 4},
    {(int[]){9, 9, 9, 9, 9}, (int[]){1, 2, 3, 4, 5}, 5},
    {(int[]){-10, 1, 1}, (int[]){1, 1, 1}, 3},
    {(int[]){-3, 0, 3, -3}, (int[]){3, 0, -3, 3}, 4},
    {(int[]){0}, (int[]){0}, 1}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    // Allocate new array for a with doubled values
    int* new_a = new int[tc.n];
    for (int i = 0; i < tc.n; i++) {
        new_a[i] = 2 * tc.a[i];
    }
    tf.a = new_a;
    return tf;
}

int check(TestCase tc) {
    int Os = dot_product(tc.a, tc.b, tc.n);
    TestCase Tf_case = change(tc);
    int Of = dot_product(Tf_case.a, Tf_case.b, Tf_case.n);
    int is_valid = 0;
    if (Of == 2 * Os) {
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