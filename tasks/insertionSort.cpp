#include <iostream>
using namespace std;

void insertionSort(int a[], int n) {
    for (int i = 1; i < n; ++i) {
        int idx = i;
        while (idx >= 1 && a[idx] < a[idx - 1]) {
            swap(a[idx], a[idx - 1]);
            --idx;
        }
    }
}

int main() {
    int n;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; ++i) cin >> a[i];

    insertionSort(a, n);

    for (int i = 0; i < n; ++i)
        cout << a[i] << " ";
    return 0;
}
