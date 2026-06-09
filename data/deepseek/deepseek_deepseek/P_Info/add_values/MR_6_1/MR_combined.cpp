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


int add_values(int a[], int n) {
    int sum = 0;

    for (int i = 0; i < n; i++) {
        sum += a[i];
    }
    return sum;
}


typedef struct {
    int* a; int n;
} TestCase;

TestCase test_cases[] = {
    {(int[]){1, 2, 3}, 3},
    {(int[]){5}, 1},
    {(int[]){-1, 0, 1}, 3},
    {(int[]){10, 20, 30, 40}, 4},
    {(int[]){-10, -20, -30}, 3},
    {(int[]){100, 200, 300, 400, 500}, 5},
    {(int[]){0, 0, 0, 0}, 4},
    {(int[]){2, 4, 6, 8, 10, 12}, 6},
    {(int[]){-5, 10, -15, 20}, 4},
    {(int[]){1}, 1},
    {(int[]){-1, -2, -3, -4, -5}, 5},
    {(int[]){7, 14, 21}, 3},
    {(int[]){0}, 1},
    {(int[]){50, 25, 12, 6}, 4},
    {(int[]){-100, 100, -200, 200}, 4},
    {(int[]){9, 8, 7, 6, 5, 4, 3, 2, 1}, 9},
    {(int[]){15, 30, 45, 60, 75}, 5},
    {(int[]){-3, -6, -9, -12}, 4},
    {(int[]){11, 22, 33, 44, 55, 66}, 6},
    {(int[]){0, 10, 0, 20, 0}, 5},
    {(int[]){999, 1}, 2},
    {(int[]){-50, 0, 50}, 3},
    {(int[]){4, 8, 12, 16, 20, 24, 28}, 7},
    {(int[]){-1, 1, -2, 2, -3, 3}, 6},
    {(int[]){19, 27, 35}, 3},
    {(int[]){1000, 2000, 3000}, 3},
    {(int[]){-8, -4, 0, 4, 8}, 5},
    {(int[]){6, 12, 18, 24, 30, 36}, 6},
    {(int[]){-25, 50, -75, 100}, 4},
    {(int[]){13, 26, 39, 52, 65, 78, 91}, 7}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    int* new_array = new int[tc.n];
    for (int i = 0; i < tc.n; i++) {
        new_array[i] = tc.a[i];
    }
    std::sort(new_array, new_array + tf.n, std::greater<int>());
    tf.a = new_array;
    return tf;
}

int check(TestCase tc) {
    int Os = add_values(tc.a, tc.n);
    TestCase Tf_case = change(tc);
    int Of = add_values(Tf_case.a, Tf_case.n);
    int is_valid = 0;
    if (Os == Of) {
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