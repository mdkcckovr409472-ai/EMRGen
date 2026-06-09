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
                if (!(cp1[i + m] >= cp1[i])) {
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