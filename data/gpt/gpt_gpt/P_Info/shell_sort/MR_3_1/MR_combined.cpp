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


int* shell_sort(int a[], int n) {
    int* cp1 = (int*)malloc(n * sizeof(int));
    memcpy(cp1,a,n*sizeof(int));
    int j;
    int i;
    int k;
    int m;
    int mid;
        
    for (m = n/2; m > 0; m /= 2) {
        for (j = m; j < n; j++) {
            for (i = j - m; i >= 0; i -= m) {
                if (cp1[i + m] >= cp1[i]) {
                    break;
                } else {
                    mid = cp1[i];
                    cp1[i] = cp1[i + m];
                    cp1[i + m] = mid;
                }
            }
        }
    }
    return cp1;
}


typedef struct {
    int* a; int n;
} TestCase;

TestCase test_cases[] = {
    { (int[]){5, 2, 9, 1, 5, 6}, 6 },
    { (int[]){1, 2, 3, 4, 5}, 5 },
    { (int[]){9, 8, 7, 6, 5, 4}, 6 },
    { (int[]){3, 3, 3, 3}, 4 },
    { (int[]){-3, -1, -7, 2, 0}, 5 },
    { (int[]){42}, 1 },
    { (int[]){1, 2}, 2 },
    { (int[]){2, 1}, 2 },
    { (int[]){}, 0 },
    { (int[]){0, 5, 0, 3, 0}, 5 },
    { (int[]){12, 4, 7, 3, 9, 1, 8, 6, 2, 10, 5, 11}, 12 },
    { (int[]){4, 2, 4, 2, 4}, 5 },
    { (int[]){-10, 5, -3, 8, -2, 0}, 6 },
    { (int[]){1, 1, 2, 2, 3, 3}, 6 },
    { (int[]){5, 5, 4, 4, 3, 3, 2, 2, 1, 1}, 10 },
    { (int[]){100, -50, 30, -20, 0, 50}, 6 },
    { (int[]){2, 3, 5, 7, 11, 13, 17}, 7 },
    { (int[]){0, 1, 1, 2, 3, 5, 8, 13, 21}, 9 },
    { (int[]){100, 1, 99, 2, 98, 3, 97, 4}, 8 },
    { (int[]){0, 0, 0, 0, 0}, 5 },
    { (int[]){-1, -2, -3, -4, -5}, 5 },
    { (int[]){-5, -3, 0, 2, 4}, 5 },
    { (int[]){5, 3, 0, -2, -4}, 5 },
    { (int[]){7, -2, 5}, 3 },
    { (int[]){3, 1, 4, 1, 5, 9, 2, 6, 5}, 9 },
    { (int[]){8, 3, 6, 2, 7, 5, 1, 4}, 8 },
    { (int[]){-1000, 500, -250, 250, 0}, 5 },
    { (int[]){-10, -5, 0, 5, 10}, 5 },
    { (int[]){10, 5, 0, -5, -10}, 5 },
    { (int[]){200, -150, 75, -25, 50, -75, 125}, 7 }
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    // Reuse original array but create a new descending sorted array for tf.a
    // Allocate new array for tf.a
    int* desc_a = (int*)malloc(tc.n * sizeof(int));
    memcpy(desc_a, tc.a, tc.n * sizeof(int));

    // Sort desc_a in descending order
    for (int i = 0; i < tc.n -1; i++) {
        for (int j = i + 1; j < tc.n; j++) {
            if (desc_a[i] < desc_a[j]) {
                int tmp = desc_a[i];
                desc_a[i] = desc_a[j];
                desc_a[j] = tmp;
            }
        }
    }

    TestCase tf = tc;
    tf.a = desc_a;  // overwrite with descending sorted array

    return tf;
}

int check(TestCase tc) {
    // Source input
    int* Ts = tc.a;
    int n = tc.n;

    // Source output
    int* Os = shell_sort(Ts, n);

    // Generate follow-up test case (descending order array)
    TestCase Tf_case = change(tc);
    int* Tf = Tf_case.a;

    // Follow-up output
    int* Of = shell_sort(Tf, n);

    // Verify Os and Of satisfy MR: Os == Of element-wise
    int is_valid = 1;
    for (int i = 0; i < n; i++) {
        if (Os[i] != Of[i]) {
            is_valid = 0;
            break;
        }
    }

    // Free all dynamically allocated memory
    free(Os);
    free(Of);
    free(Tf);

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