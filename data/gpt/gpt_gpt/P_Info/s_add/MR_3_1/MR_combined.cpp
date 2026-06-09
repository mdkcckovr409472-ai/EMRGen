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
    { (int[]){1, 2, 3}, (int[]){4, 5, 6}, 3 },
    { (int[]){}, (int[]){}, 0 },
    { (int[]){0}, (int[]){0}, 1 },
    { (int[]){-5, 10}, (int[]){7, -3}, 2 },
    { (int[]){8, -2, 5, 1}, (int[]){-1, 3, -4, 0}, 4 },
    { (int[]){100, 200, 300}, (int[]){-100, -200, -300}, 3 },
    { (int[]){-10, -20, -30, -40}, (int[]){5, 5, 5, 5}, 4 },
    { (int[]){7, 0, -7}, (int[]){-7, 0, 7}, 3 },
    { (int[]){12, 34, 56, 78, 90}, (int[]){1, 2, 3, 4, 5}, 5 },
    { (int[]){9, 8, 7, 6}, (int[]){6, 7, 8, 9}, 4 },
    { (int[]){3, 3, 3}, (int[]){-3, -3, -3}, 3 },
    { (int[]){-1, 2, -3, 4, -5}, (int[]){5, -4, 3, -2, 1}, 5 },
    { (int[]){15, 25}, (int[]){-5, -15}, 2 },
    { (int[]){0, 0, 0, 0}, (int[]){1, -1, 2, -2}, 4 },
    { (int[]){42}, (int[]){-42}, 1 },
    { (int[]){11, 22, 33, 44, 55, 66}, (int[]){-11, -22, -33, -44, -55, -66}, 6 },
    { (int[]){5, -5, 10, -10}, (int[]){-5, 5, -10, 10}, 4 },
    { (int[]){2, 4, 6, 8, 10}, (int[]){1, 1, 1, 1, 1}, 5 },
    { (int[]){-3, -6, -9}, (int[]){9, 6, 3}, 3 },
    { (int[]){13, 26, 39, 52}, (int[]){-2, -4, -6, -8}, 4 },
    { (int[]){7, 14, 21}, (int[]){0, 0, 0}, 3 },
    { (int[]){-8, 16, -24, 32}, (int[]){8, -16, 24, -32}, 4 },
    { (int[]){1, 3, 5, 7, 9}, (int[]){9, 7, 5, 3, 1}, 5 },
    { (int[]){1000, -1000}, (int[]){-500, 500}, 2 },
    { (int[]){0, 1, 0, 1}, (int[]){1, 0, 1, 0}, 4 },
    { (int[]){-2, -4, -6, -8, -10}, (int[]){10, 8, 6, 4, 2}, 5 },
    { (int[]){3, -3, 3, -3}, (int[]){-3, 3, -3, 3}, 4 },
    { (int[]){50, 60, 70}, (int[]){-10, -20, -30}, 3 },
    { (int[]){9, 18, 27, 36, 45, 54}, (int[]){-9, -18, -27, -36, -45, -54}, 6 }
};
int num_test_cases = 29;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    // Allocate new array2 to modify the last element to INT_MIN
    int* new_array2 = (int*)malloc(tf.n * sizeof(int));
    if (new_array2 == NULL) return tf; // fallback: no change if malloc fails
    memcpy(new_array2, tf.array2, tf.n * sizeof(int));
    new_array2[tf.n - 1] = INT_MIN;
    tf.array2 = new_array2;
    return tf;
}

int check(TestCase tc) {
    int* Os = s_add(tc.array1, tc.array2, tc.n);
    if (Os == NULL) return 0;

    TestCase Tf = change(tc);
    int* Of = s_add(Tf.array1, Tf.array2, Tf.n);
    if (Of == NULL) {
        free(Os);
        if (Tf.array2 != tc.array2) free(Tf.array2);
        return 0;
    }

    int valid = 1;
    for (int i = 0; i < tc.n - 1; i++) {
        if (Of[i] != Os[i]) {
            valid = 0;
            break;
        }
    }
    if (valid) {
        if (Of[tc.n - 1] != tc.array1[tc.n - 1] + INT_MIN) {
            valid = 0;
        }
    }

    free(Os);
    free(Of);
    if (Tf.array2 != tc.array2) free(Tf.array2);

    return valid;
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