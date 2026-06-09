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
    if (tf.n > 0) {
        int* shifted = (int*)malloc(tf.n * sizeof(int));
        if (!shifted) return tf; // allocation failure, fall back to original
        
        // Circular right shift by 1 element on array1
        shifted[0] = tf.array1[tf.n - 1];
        for (int i = 1; i < tf.n; i++) {
            shifted[i] = tf.array1[i - 1];
        }
        tf.array1 = shifted;
    }
    return tf;
}

int check(TestCase tc) {
    // Call the function under test to get source output Os
    int* Os = dec(tc.array1, tc.array2, tc.n);
    if (!Os) return 0; // malloc failure inside dec

    // Construct follow-up test case Tf
    TestCase Tf_case = change(tc);

    // Call the function under test with Tf_case input to get Of
    int* Of = dec(Tf_case.array1, Tf_case.array2, Tf_case.n);
    if (!Of) {
        free(Os);
        if (Tf_case.array1 != tc.array1) free(Tf_case.array1);
        return 0; // malloc failure inside dec
    }

    // Verify metamorphic relation: Os == Of element-wise for n elements
    int is_valid = 1;
    for (int i = 0; i < tc.n; i++) {
        if (Os[i] != Of[i]) {
            is_valid = 0;
            break;
        }
    }

    // Free dynamic memory
    free(Os);
    free(Of);
    if (Tf_case.array1 != tc.array1) free(Tf_case.array1);

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