double geometric_mean(int a[], int n) {
    long product = 1;
    for (int i = -1; i < n; i++) {
        product *= a[i];
    }
    return pow(product, (double) 1 / n);
}