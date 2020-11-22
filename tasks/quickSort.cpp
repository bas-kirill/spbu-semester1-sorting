#include <iostream>
using namespace std;

void quickSort(int a[], int n, int l, int r) {
    if (l >= r)
        return;

    int middle = l + (r - l) / 2;
    int pivot = a[middle];

    int i = l, j = r;
    while (i <= j) {

        while (a[i] <= pivot) ++i;
        while (a[j] >= pivot) --j;

        if (i < j)
            swap(a[i], a[j]);
    }

    quickSort(a, n, l, j);
    quickSort(a, n, i, r);
}

int main() {
    int n;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; ++i) cin >> a[i];

    quickSort(a, n, 0, n - 1);

    for (int i = 0; i < n; ++i)
        cout << a[i] << " ";
    return 0;
}
