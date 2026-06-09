bool* elementwise_equal(int a[], int b[], int n) {
    if (a == NULL || b == NULL || n <= 0) {
        return NULL;
    }

    bool* result = (bool*)malloc(n * sizeof(bool));
    if (!result) return NULL;

    for (int i = 0; i < n; i++) {
        result[i] = (a[i] == b[i]);
    }
    return result;
}
