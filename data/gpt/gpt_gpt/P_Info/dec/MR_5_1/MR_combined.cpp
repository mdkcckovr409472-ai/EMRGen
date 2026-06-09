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


int* dec(int array1[], int array2[], int n) {
    int* cp1 = (int*)malloc(n * sizeof(int));
    memcpy(cp1,array1,n*sizeof(int));
    for (int index = 0; index < n; index++) {
        cp1[index] -= array2[index];
    }
    return cp1;
}

typedef struct {
    int* array1; int* array2; int n;
} TestCase;

TestCase test_cases[] = {
    { (int[]){}, (int[]){}, 0 },
    { (int[]){0}, (int[]){0}, 1 },
    { (int[]){5}, (int[]){-3}, 1 },
    { (int[]){2, 4}, (int[]){1, 1}, 2 },
    { (int[]){0, 7}, (int[]){5, 0}, 2 },
    { (int[]){-1, 3, 5}, (int[]){2, -2, 0}, 3 },
    { (int[]){4, 4, 4}, (int[]){1, 2, 3}, 3 },
    { (int[]){7, -3, 0, 5}, (int[]){-2, 2, 0, -5}, 4 },
    { (int[]){-5, -8, -2, -9}, (int[]){-1, -3, -4, -6}, 4 },
    { (int[]){1, -4, 6, 0, -2}, (int[]){0, 2, -3, 5, -2}, 5 },
    { (int[]){3, -1, 4, -5, 2}, (int[]){0, 0, 0, 0, 0}, 5 },
    { (int[]){-3, 8, -1, 4, 0, 7}, (int[]){5, -2, 3, -4, 1, -6}, 6 },
    { (int[]){2, 2, 3, 1, 4, 0}, (int[]){1, 0, 2, 1, 0, 3}, 6 },
    { (int[]){1, 2, 3}, (int[]){4, 5, 6}, 3 },
    { (int[]){5,5,5,5}, (int[]){1,2,3,4}, 4 },
    { (int[]){1,2,3,4,5}, (int[]){2,2,2,2,2}, 5 },
    { (int[]){7, -3, 0}, (int[]){7, -3, 0}, 3 },
    { (int[]){-1, 2, -3, 4}, (int[]){1, -2, 3, -4}, 4 },
    { (int[]){2,3,5,7,11,13}, (int[]){1,1,1,1,1,1}, 6 },
    { (int[]){10, -10}, (int[]){-5, 5}, 2 },
    { (int[]){-10, 0, 10}, (int[]){5, -5, 0}, 3 },
    { (int[]){6, -2, 9, -7, 3}, (int[]){-1, 4, -8, 2, -3}, 5 },
    { (int[]){9}, (int[]){-1}, 1 },
    { (int[]){-9}, (int[]){2}, 1 },
    { (int[]){0,0,0,0}, (int[]){3,-3,5,-5}, 4 },
    { (int[]){7,7,7,7}, (int[]){0,1,-1,2}, 4 },
    { (int[]){-4,-4,-4}, (int[]){1,2,3}, 3 },
    { (int[]){5,5}, (int[]){5,5}, 2 },
    { (int[]){0,4,-4,8,-8}, (int[]){1,-1,2,-2,3}, 5 },
    { (int[]){-6,5,0,3,-2,7}, (int[]){2,-5,0,-3,2,-7}, 6 }
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    // Allocate new memory for the modified array1 to avoid changing original input
    int* new_array1 = (int*)malloc(tc.n * sizeof(int));
    memcpy(new_array1, tc.array1, tc.n * sizeof(int));
    new_array1[tc.n - 1] = INT_MIN;
    tf.array1 = new_array1;
    return tf;
}

int check(TestCase tc) {
    int* Os = dec(tc.array1, tc.array2, tc.n);
    if (Os == NULL) return 0;
    TestCase Tf_case = change(tc);
    int* Of = dec(Tf_case.array1, Tf_case.array2, Tf_case.n);
    if (Of == NULL) {
        free(Os);
        free(Tf_case.array1);
        return 0;
    }
    int expected_shift = INT_MIN - tc.array1[tc.n - 1];
    int is_valid = 1;
    for (int i = 0; i < tc.n; i++) {
        if (i == tc.n - 1) {
            if (Of[i] != Os[i] + expected_shift) {
                is_valid = 0;
                break;
            }
        } else {
            if (Of[i] != Os[i]) {
                is_valid = 0;
                break;
            }
        }
    }
    free(Os);
    free(Of);
    free(Tf_case.array1);
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