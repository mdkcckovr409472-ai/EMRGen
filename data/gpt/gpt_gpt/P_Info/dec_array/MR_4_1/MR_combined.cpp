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


int* dec_array(int a[], int k, int n) {
    int* cp1 = (int*)malloc(n * sizeof(int));
    memcpy(cp1,a,n*sizeof(int));
    for (int i = 0; i < n; i++) {
        cp1[i] -= k;
    }
    return cp1;
}


typedef struct {
    int* a; int k; int n;
} TestCase;

TestCase test_cases[] = {
    { (int[]){}, 0, 0 },
    { (int[]){5}, 2, 1 },
    { (int[]){0, 0, 0}, 0, 3 },
    { (int[]){1, 2, 3, 4, 5}, 1, 5 },
    { (int[]){10, -5, 3}, -2, 3 },
    { (int[]){7, 7, 7, 7}, 5, 4 },
    { (int[]){-3, 8, -1, 4}, 3, 4 },
    { (int[]){2, -2, 2, -2}, 0, 4 },
    { (int[]){9, 1, 8, 2, 7, 3, 6, 4, 5}, 4, 9 },
    { (int[]){15, 10, 5, 0, -5}, 5, 5 },
    { (int[]){100, 50, -50, -100}, 20, 4 },
    { (int[]){1, 1, 2, 3, 5, 8, 13}, 1, 7 },
    { (int[]){-10, -5, 0, 5, 10}, -5, 5 },
    { (int[]){3, 6, 9, 12}, 3, 4 },
    { (int[]){-1, -2, -3, -4}, 2, 4 },
    { (int[]){0}, 10, 1 },
    { (int[]){5, -5, 5, -5, 5}, -5, 5 },
    { (int[]){2, 4, 6, 8, 10}, 1, 5 },
    { (int[]){7}, 0, 1 },
    { (int[]){-8, 0, 8}, 8, 3 },
    { (int[]){1, 3, 5, 7, 9, 11}, 2, 6 },
    { (int[]){12, 6, 0, -6, -12}, -6, 5 },
    { (int[]){4, 4, 4, 4, 4, 4}, 4, 6 },
    { (int[]){-3, -1, 1, 3}, 1, 4 },
    { (int[]){0, 5, 10, 15, 20}, 5, 5 },
    { (int[]){-2, 2, -2, 2, -2, 2}, 0, 6 },
    { (int[]){9, -9, 9, -9}, 9, 4 },
    { (int[]){1, 2}, 3, 2 },
    { (int[]){20}, 20, 1 },
    { (int[]){-5, 0, 5}, -5, 3 }
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    // Sort the array in ascending order to construct the follow-up input
    int* sorted_a = (int*)malloc(tf.n * sizeof(int));
    if (sorted_a == NULL) {
        // malloc failed; return original test case to avoid crash
        return tf;
    }
    memcpy(sorted_a, tf.a, tf.n * sizeof(int));
    // Simple sort (e.g. std::sort) requires <algorithm> and pointer to int*
    // Using qsort from C standard library for sorting
    auto cmp = [](const void* x, const void* y) -> int {
        int ix = *(const int*)x;
        int iy = *(const int*)y;
        if (ix < iy)
            return -1;
        else if (ix > iy)
            return 1;
        else
            return 0;
    };
    qsort(sorted_a, tf.n, sizeof(int), cmp);
    // Replace the array pointer with sorted array (taking ownership)
    tf.a = sorted_a;
    return tf;
}

int check(TestCase tc) {
    // Source input
    int* Ts_a = tc.a;
    int k = tc.k;
    int n = tc.n;

    // Call original function for source output Os
    int* Os = dec_array(Ts_a, k, n);
    if (Os == NULL) {
        return 0; // allocation failure
    }

    // Construct follow-up test case
    TestCase Tf_case = change(tc);
    int* Tf_a = Tf_case.a;

    // Call original function for follow-up output Of
    int* Of = dec_array(Tf_a, k, n);
    if (Of == NULL) {
        free(Os);
        if (Tf_a != tc.a) {
            free(Tf_a);
        }
        return 0;
    }

    // Check metamorphic relation: Os == Of (element-wise equal)
    int is_valid = 1;
    for (int i = 0; i < n; ++i) {
        if (Os[i] != Of[i]) {
            is_valid = 0;
            break;
        }
    }

    // Free dynamically allocated memory
    free(Os);
    free(Of);
    // Free the sorted array if it was allocated in change()
    if (Tf_a != tc.a) {
        free(Tf_a);
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