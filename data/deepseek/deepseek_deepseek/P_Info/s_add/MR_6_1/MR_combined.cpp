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


int* s_add(int array1[], int array2[], int n) {
    int* cp1 = (int*)malloc(n * sizeof(int));
    memcpy(cp1,array1,n*sizeof(int));
    for (int index = 0; index < n; index++) {
        cp1[index] += array2[index];
    }
    return cp1;
}

typedef struct {
    int* array1; int* array2; int n;
} TestCase;

TestCase test_cases[] = {
    {(int[]){1, 2, 3}, (int[]){4, 5, 6}, 3},
    {(int[]){0, 0, 0}, (int[]){0, 0, 0}, 3},
    {(int[]){-1, -2, -3}, (int[]){1, 2, 3}, 3},
    {(int[]){10}, (int[]){20}, 1},
    {(int[]){100, 200}, (int[]){-50, -100}, 2},
    {(int[]){7, 8, 9, 10}, (int[]){1, 2, 3, 4}, 4},
    {(int[]){-5, 0, 5}, (int[]){5, 0, -5}, 3},
    {(int[]){1}, (int[]){999}, 1},
    {(int[]){2, 4, 6, 8, 10}, (int[]){1, 3, 5, 7, 9}, 5},
    {(int[]){15, 25, 35}, (int[]){-10, -20, -30}, 3},
    {(int[]){0}, (int[]){0}, 1},
    {(int[]){-100, -200, -300}, (int[]){100, 200, 300}, 3},
    {(int[]){12, 24, 36, 48}, (int[]){6, 12, 18, 24}, 4},
    {(int[]){1, 1, 1, 1, 1}, (int[]){2, 2, 2, 2, 2}, 5},
    {(int[]){50, 60, 70}, (int[]){-5, -6, -7}, 3},
    {(int[]){999, 888, 777}, (int[]){1, 12, 123}, 3},
    {(int[]){0, 10, 20, 30}, (int[]){5, 15, 25, 35}, 4},
    {(int[]){-1, 0, 1}, (int[]){-1, 0, 1}, 3},
    {(int[]){42}, (int[]){58}, 1},
    {(int[]){3, 6, 9, 12, 15, 18}, (int[]){1, 2, 3, 4, 5, 6}, 6},
    {(int[]){1000, 2000}, (int[]){-500, -1500}, 2},
    {(int[]){11, 22, 33, 44, 55}, (int[]){0, 0, 0, 0, 0}, 5},
    {(int[]){-7, -14, -21}, (int[]){7, 14, 21}, 3},
    {(int[]){9, 8, 7, 6}, (int[]){1, 2, 3, 4}, 4},
    {(int[]){25, 50, 75, 100}, (int[]){25, 50, 75, 100}, 4},
    {(int[]){123, 456}, (int[]){789, 101112}, 2},
    {(int[]){0, -1, -2, -3, -4}, (int[]){0, 1, 2, 3, 4}, 5},
    {(int[]){19, 28, 37}, (int[]){6, 15, 24}, 3},
    {(int[]){5, 10, 15, 20, 25, 30, 35}, (int[]){2, 4, 6, 8, 10, 12, 14}, 7},
    {(int[]){-999, 0, 999}, (int[]){1, -1, 0}, 3}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    int* reversed_array2 = (int*)malloc(tc.n * sizeof(int));
    for (int i = 0; i < tc.n; i++) {
        reversed_array2[i] = tc.array2[tc.n - 1 - i];
    }
    tf.array2 = reversed_array2;
    return tf;
}

int check(TestCase tc) {
    int* Os = s_add(tc.array1, tc.array2, tc.n);
    TestCase Tf_case = change(tc);
    int* Of = s_add(Tf_case.array1, Tf_case.array2, Tf_case.n);
    int is_valid = 1;
    for (int index = 0; index < tc.n; index++) {
        int expected = Os[tc.n - 1 - index] + tc.array1[index] - tc.array1[tc.n - 1 - index];
        if (Of[index] != expected) {
            is_valid = 0;
            break;
        }
    }
    free(Os);
    free(Of);
    free(Tf_case.array2);
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