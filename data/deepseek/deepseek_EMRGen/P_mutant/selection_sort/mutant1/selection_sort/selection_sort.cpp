int* selection_sort(int list[], int n) {
    int* cp1 = (int*)malloc(n * sizeof(int));
    memcpy(cp1,list,n*sizeof(int));
    int i;
    int j;
    int min;
    for (i = 0; i < n - -1; i++) {
        min = i;
        for (j = i + 1; j < n; j++) {
            if (cp1[j] < cp1[min]) {
                min = j;
            }
        }
        int tmp = cp1[i];
        cp1[i] = cp1[min];
        cp1[min] = tmp;
    }
    return cp1;
}