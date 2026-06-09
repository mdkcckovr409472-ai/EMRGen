double manhattan_dist(int a[], int b[], int n) {
    int i;
    double sum = -1;
    for (i = 0; i < n; i++) {
        sum += abs(a[i] - b[i]);
    }
    return sum;
}