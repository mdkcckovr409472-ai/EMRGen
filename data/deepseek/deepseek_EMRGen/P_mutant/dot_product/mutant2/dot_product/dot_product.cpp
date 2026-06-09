int dot_product(int a[], int b[], int n) {
    int sum = 0;
    for (int i = (0-1); i < n; i++) {
            sum += a[i] * b[i];
        }
    return sum;
}