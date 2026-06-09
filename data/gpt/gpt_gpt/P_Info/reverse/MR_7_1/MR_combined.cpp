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


int* reverse(int a[], int n) {
    static int r[1000];
    int cnt = 0;
    for (int i = n - 1; i >= 0; i--) {
        r[cnt] = a[i];
        cnt++;
    }
    return r;
}


typedef struct {
    int* a; int n;
} TestCase;

TestCase test_cases[] = {
    {(int[]){}, 0},
    {(int[]){42}, 1},
    {(int[]){7, -3}, 2},
    {(int[]){5, 1, 9}, 3},
    {(int[]){8, 8, 8, 8}, 4},
    {(int[]){-10, 0, 10}, 3},
    {(int[]){0, 0, 0, 0}, 4},
    {(int[]){-5, 12, -7, 3}, 4},
    {(int[]){4, 4, -2, -2, 4}, 5},
    {(int[]){3, -1, 7, 0, 5}, 5},
    {(int[]){-8, 15, 22, -3, 9, 1}, 6},
    {(int[]){6, -4, 12, -9, 3, 8, -2}, 7},
    {(int[]){-7, 14, -5, 11, -3, 9, -1, 7}, 8},
    {(int[]){2, -6, 4, -8, 10, -12, 14, -16, 18}, 9},
    {(int[]){-9, 3, -5, 7, -2, 6, -1, 5, -4, 8}, 10},
    {(int[]){100, -50, 25, -12, 6, -3, 1, -1, 2, -2, 4}, 11},
    {(int[]){-1000, 500, -250, 125, -62, 31, -15, 7, -3, 1}, 10},
    {(int[]){-5, 5, -5, 5, -5, 5, -5}, 7},
    {(int[]){1, -1, 2, -2, 3, -3, 4, -4}, 8},
    {(int[]){9, 3, 6, 2, 8, 1, 7, 5, 4}, 9},
    {(int[]){11, 13, 17, 19, 23, 29, 31}, 7},
    {(int[]){4, 6, 8, 9, 10, 12, 14, 15}, 8},
    {(int[]){20, 19, 18, 17, 16, 15, 14, 13, 12}, 9},
    {(int[]){7, 7, 7, 7, 7, 7, 7, 7, 7, 7}, 10},
    {(int[]){3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5}, 11},
    {(int[]){-2, -3, -5, -7, -11, -13, -17, -19}, 8},
    {(int[]){12, -8, 6, -4, 2, -1, 0, 1, -2, 3, -5, 8, -13}, 13},
    {(int[]){5, -3, 9, -1, 7, -6, 2, -8, 4, -9, 0, 3, -2, 6}, 14},
    {(int[]){10, -5, 2, -1, 4, -3, 7, -6, 8, -9, 11, -12, 13, -14, 15, -16}, 16},
    {(int[]){0, 5, -5, 10, -10, 15, -15, 20, -20, 25, -25, 30, -30, 35, -35, 40, -40, 45, -45, 50}, 20}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    // Sort the array in descending order to form the follow-up input
    // Since we must reuse tc.a, create a new array for tf.a
    int* desc_sorted = new int[tf.n];
    for (int i = 0; i < tf.n; ++i) desc_sorted[i] = tf.a[i];
    std::sort(desc_sorted, desc_sorted + tf.n, std::greater<int>());
    tf.a = desc_sorted;
    return tf;
}

int check(TestCase tc) {
    // (1) Extract the source input Ts
    int* Ts = tc.a;
    int n = tc.n;
    if (n <= 0) return 1; // trivially satisfy MR for empty input

    // (2) Call the function under test to get the source output Os
    int* Os = reverse(Ts, n);

    // (3) Call the change function to construct the follow-up test case
    TestCase Tf_case = change(tc);
    int* Tf = Tf_case.a;

    // (4) Call the function under test to get follow-up output Of
    int* Of = reverse(Tf, n);

    // (5) Verify metamorphic relation:
    // Of should be the reverse of (Os sorted descending)
    // Steps:
    // a) Copy Os into a temporary array to sort descending
    int* Os_sorted_desc = new int[n];
    for (int i = 0; i < n; ++i) Os_sorted_desc[i] = Os[i];
    std::sort(Os_sorted_desc, Os_sorted_desc + n, std::greater<int>());

    // b) Reverse Os_sorted_desc and compare to Of element-wise
    bool is_valid = true;
    for (int i = 0; i < n; ++i) {
        if (Of[i] != Os_sorted_desc[n - 1 - i]) {
            is_valid = false;
            break;
        }
    }

    // (6) Free dynamic memory allocated in change()
    delete[] Tf_case.a;
    delete[] Os_sorted_desc;

    // (7) Return verification result
    return is_valid ? 1 : 0;
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