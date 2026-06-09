int* array_calc1(int a[], int k, int n) {
    int* b = (int*)malloc(n * sizeof(int));
    if (b == NULL) return NULL;

    for (int i = 0; i < n; i++) {
        double val = (double)a[i] / k;
        b[i] = (int)round(val); 
    }
    return b;
}
