int* clip(int a[], int lowerLim , int n, int upperLim) {
    static int r[100];
        for (int i = 0; i < n; i++) {
            if (a[i] < lowerLim) {
                r[i] = lowerLim;
            } else {
                if (a[i] > upperLim) {
                    r[i] = upperLim;
                } else {
                    r[i] = a[i];
                }
            }
        }
        return r;
    }