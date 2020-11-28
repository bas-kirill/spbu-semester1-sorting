#include <iostream>
#include <random>
using namespace std;

const int MAXN = 50'000;
const int INF = 2e9;

std::random_device device;
std::mt19937 generator(device());
std::uniform_int_distribution<int> distribution(-INF,INF);

unsigned long long bubbleSortComparsionsNumber = 0;
unsigned long long quickSortComparsionsNumber = 0;
unsigned long long mergeSortComparsionsNumber = 0;
unsigned long long insertionSortComparsionsNumber = 0;

unsigned long long bubbleSortPermutationsNumber = 0;
unsigned long long quickSortPermutationsNumber = 0;
unsigned long long mergeSortPermutationsNumber = 0;
unsigned long long insertionSortPermutationsNumber = 0;

void bubbleSort(int a[], int n) {
    bool flag = true;
    while (flag) {
        flag = false;
        for (int j = 0; j < n - 1; ++j) {
            ++bubbleSortComparsionsNumber;
            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
                ++bubbleSortPermutationsNumber;
                flag = true;
            }
        }
    }
}

void quickSort(int a[], int n, int l, int r) {
    if (l >= r) {
        ++quickSortComparsionsNumber;
        return;
    }

    int middle = l + (r - l) / 2;
    int pivot = a[middle];

    int i = l, j = r;
    while (i <= j) {
        ++quickSortComparsionsNumber;
        while (a[i] < pivot) { ++i; ++quickSortComparsionsNumber; } // <= -> <, coz 3 3 3
        while (a[j] > pivot) { --j; ++quickSortComparsionsNumber; }

        if (i <= j) {
            ++quickSortComparsionsNumber;
            ++quickSortPermutationsNumber;
            swap(a[i++], a[j--]);
        }
    }

    quickSort(a, n, l, j);
    quickSort(a, n, i, r);
}

void merge(int a[], int l1, int r1, int l2, int r2) {
    int n = r1 - l1 + 1;
    int m = r2 - l2 + 1;
    int c[n + m];
    int idx = 0;
    int i = l1, j = l2;
    while (i <= r1 || j <= r2) {
        ++mergeSortComparsionsNumber;
        if (j == (r2 + 1)) {
            ++mergeSortComparsionsNumber;
            ++mergeSortPermutationsNumber;
            c[idx++] = a[i++];
        } else if (i <= r1 && a[i] < a[j]) {
            mergeSortComparsionsNumber += 2;
            ++mergeSortPermutationsNumber;
            c[idx++] = a[i++];
        } else {
            ++mergeSortPermutationsNumber;
            c[idx++] = a[j++];
        }
    }

    for (int i = l1; i <= r2; ++i) {
        a[i] = c[i - l1];
        ++mergeSortPermutationsNumber;
    }
}

void mergeSort(int a[], int n, int l, int r) {
    if (l >= r) {
        ++mergeSortComparsionsNumber;
        return;
    }
    int middle = l + (r - l) / 2;
    mergeSort(a, n, l, middle);
    mergeSort(a, n, middle + 1, r);
    merge(a, l, middle, middle + 1, r);
}

void insertionSort(int a[], int n) {
    for (int i = 1; i < n; ++i) {
        int idx = i;
        while (idx >= 1 && a[idx] < a[idx - 1]) {
            insertionSortComparsionsNumber += 2;
            swap(a[idx], a[idx - 1]);
            ++insertionSortPermutationsNumber;
            --idx;
        }
    }
}

void fillRandomNumbers(int a[], int n) {
    std::random_device device;
    std::mt19937 generator(device());
    std::uniform_int_distribution<int> distribution(-INF,INF);
    for (int i = 0; i < n; ++i) {
        a[i] = distribution(generator);
    }
}

int main() {
    int n;
    int cnt = 0;
    while (cnt <= 4) {
        switch (cnt) {
            case 0:
                n = 1'000;
                break;
            case 1:
                n = 5'000;
                break;
            case 2:
                n = 10'000;
                break;
            case 3:
                n = 20'000;
                break;
            case 4:
                n = 50'000;
                break;
        }
        int a[MAXN];

        fillRandomNumbers(a, n);
        bubbleSort(a, n);

        fillRandomNumbers(a, n);
        quickSort(a, n, 0, n - 1);

        fillRandomNumbers(a, n);
        insertionSort(a, n);

        cout << "n = " << n << ":" << endl;
        cout << '\t' << "Bubble sort: " << bubbleSortComparsionsNumber << " " << bubbleSortPermutationsNumber << endl;
        cout << '\t' << "Quick sort:  " << quickSortComparsionsNumber << " " << quickSortPermutationsNumber << endl;
        cout << '\t' << "Insertion sort:  " << insertionSortComparsionsNumber << " " << insertionSortPermutationsNumber << endl;

        ++cnt;
    }
    return 0;
}
