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


int* clip(int a[], int lowerLim, int upperLim, int n) {
    static int r[100];
        for (int i = 0; i < n; i++) {
            if (a[i] < lowerLim) {
                r[i] = lowerLim;
            } else {
                if (a[i] > upperLim) {
                    r[i] = upperLim;
                } else {
                    r[i] = a[i];
                }
            }
        }
        return r;
    }
    


typedef struct {
    int* a; int lowerLim; int upperLim; int n;
} TestCase;

TestCase test_cases[] = {
    { (int[]){5, 10, 15}, 7, 12, 3 },
    { (int[]){8, 9, 10}, 5, 15, 3 },
    { (int[]){1, 2, 3}, 5, 10, 3 },
    { (int[]){20, 25, 30}, 5, 15, 3 },
    { (int[]){-10, 0, 10, 20}, -5, 5, 4 },
    { (int[]){1, 2, 3}, 5, 5, 3 },
    { (int[]){}, 0, 10, 0 },
    { (int[]){7}, 5, 10, 1 },
    { (int[]){2}, 5, 10, 1 },
    { (int[]){12}, 5, 10, 1 },
    { (int[]){5, 10, 15}, 20, 10, 3 },
    { (int[]){12, 15, 18}, 20, 10, 3 },
    { (int[]){-20, -10, 0, 10, 20}, -15, 5, 5 },
    { (int[]){-5, 0, 5}, 0, 0, 3 },
    { (int[]){3, -1, 7, 12, 5, -8, 0, 9, 14, 2}, 4, 10, 10 },
    { (int[]){5, 5, 5, 5, 5}, 3, 7, 5 },
    { (int[]){1, 1, 9, 9, 10}, 3, 8, 5 },
    { (int[]){3, 7, 5}, 3, 7, 3 },
    { (int[]){2, 3, 4, 7, 8}, 3, 7, 5 },
    { (int[]){-3, 4, -1, 6, 2}, 0, 5, 5 },
    { (int[]){-10, -5}, -3, -7, 2 },
    { (int[]){-100, 0, 100}, -50, 50, 3 },
    { (int[]){0, 0, 0, 0}, -1, 1, 4 },
    { (int[]){9, -2, 5, -7, 3, 8}, 0, 6, 6 },
    { (int[]){2, 5, 8}, 8, 10, 3 },
    { (int[]){2, 5, 8}, 0, 2, 3 },
    { (int[]){-5, -2, 0, 2, 5}, -3, 3, 5 },
    { (int[]){1}, 5, 3, 1 },
    { (int[]){11, 12, 13, 14}, 10, 15, 4 },
    { (int[]){15, 10, 12, 8}, 10, 12, 4 }
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    // Reuse the input array pointer and other fields, only modify lowerLim by adding 1
    TestCase tf = tc;
    tf.lowerLim = tc.lowerLim + 1;
    return tf;
}

int check(TestCase tc) {
    // Get source output (Os)
    int* Os = clip(tc.a, tc.lowerLim, tc.upperLim, tc.n);
    // Change input according to MR
    TestCase Tf = change(tc);
    // Get follow-up output (Of)
    int* Of = clip(Tf.a, Tf.lowerLim, Tf.upperLim, Tf.n);

    // Verify MR: Os[i] <= Of[i] for all i in [0, n)
    for (int i = 0; i < tc.n; i++) {
        if (!(Os[i] <= Of[i])) {
            return 0;
        }
    }

    return 1;
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