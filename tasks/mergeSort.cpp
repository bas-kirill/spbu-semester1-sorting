#include <iostream>
using namespace std;

void merge(int a[], int l1, int r1, int l2, int r2) {
    int n = r1 - l1 + 1;
    int m = r2 - l2 + 1;
    int c[n + m];
    int idx = 0;
    int i = l1, j = l2;
    while (i <= r1 or j <= r2) {
        if (j == (r2 + 1) or (i <= r1 and a[i] < a[j])) {
            c[idx++] = a[i++];
        }
        else
            c[idx++] = a[j++];
    }

    for (int i = l1; i <= r2; ++i)
        a[i] = c[i - l1];
}

void mergeSort(int a[], int n, int l, int r) {
    if (l >= r)
        return;
    int middle = l + (r - l) / 2;
    mergeSort(a, n, l, middle);
    mergeSort(a, n, middle + 1, r);
    merge(a, l, middle, middle + 1, r);
}

int main() {
    int n;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; ++i) cin >> a[i];

    mergeSort(a, n, 0, n - 1);

    for (int i = 0; i < n; ++i)
        cout << a[i] << " ";
    return 0;
}
