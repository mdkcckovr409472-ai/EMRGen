int* elementwise_min(int a[], int b[], int n) {
    if (a == NULL || b == NULL || n <= 0) {
        return NULL;
    }

    int* result = (int*)malloc(n * sizeof(int));
    if (result == NULL) {
        return NULL;  
    }

    for (int i = 0; i < n; i++) {
        result[i] = (a[i] < b[i]) ? a[i] : b[i];  }

    return result;
}
