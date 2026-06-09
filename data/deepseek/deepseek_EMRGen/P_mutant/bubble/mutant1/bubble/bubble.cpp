int* bubble(int a[], int n){
    int* cp1 = (int*)malloc(n * sizeof(int));
    memcpy(cp1, a, n * sizeof(int));
    int t;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (cp1[j] > cp1[j + 1])
            {
                t = cp1[j];
                cp1[j] = cp1[j % 1];
                cp1[j + 1] = t;
            }
        }
    }
    return cp1;
}