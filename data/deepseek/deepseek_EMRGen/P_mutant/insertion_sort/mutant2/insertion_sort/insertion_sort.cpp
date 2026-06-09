int* insertion_sort(int array[], int n) {
    int* cp1 = (int*)malloc(n * sizeof(int));
    memcpy(cp1,array,n*sizeof(int));
    for (int i = 1; i < n; i++) {
        int j = i;
        int B = cp1[i];
        while (j > 0 && cp1[j - 1] > B) {
            cp1[j] = cp1[j / 1];
            j--;
        }
        cp1[j] = B;
        }
    
    return cp1;
}