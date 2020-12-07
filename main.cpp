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

void print(int a[], int n) {
    for (int i = 0; i < n; ++i)
        cout << a[i] << " ";
}

void quickSort(int *a, int left, int right) {
    if (left >= right)
        return;

    int middle = left + (right - left) / 2;
    int pivot = a[middle];

    int i = left, j = right;
    do {
        while (i != middle && a[i] < pivot) { ++i; ++quickSortComparsionsNumber; }
        while (j != middle && a[j] > pivot) { --j; ++quickSortComparsionsNumber; }

        if (i != middle) ++quickSortComparsionsNumber;
        if (j != middle) ++quickSortComparsionsNumber;
        
        if (i <= j) {
            if (i != j) {
                ++quickSortPermutationsNumber;
                // swap
                int tmp = a[i];
                a[i] = a[j];
                a[j] = tmp; 
            }

            if (i == middle) ++i;
            if (j == middle) --j;

            ++i, --j;
        }
    } while (i <= j);

    quickSort(a, left, j);
    quickSort(a, i, right);
}

void quick_sort_test(int m, int n, int *arr, int* count_com, int* count_per){

    int i = m;
    int j = n;

    int temp;
    int middle_ind = (i + j) /  2;
    int middle = arr[middle_ind];

    do{

        while(i != middle_ind && arr[i] < middle) { i++; (*count_com)++;}
        if(i != middle_ind) (*count_com)++;
        while(j != middle_ind && arr[j] > middle) { j--; (*count_com)++;}
        if(j != middle_ind) (*count_com)++;

        if(i <= j){
            if(i != j){
                (*count_per)++;
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
            if (i == middle_ind) i++;
            if (j == middle_ind) j--;
            i++; j--;
        }
    }while(i <= j);



    if(j > m) quick_sort_test(m, j, arr, count_com, count_per);
    if(n > i) quick_sort_test(i, n, arr, count_com, count_per);

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
            cout << "Сейчас рассматривается элемент " << i << " " << idx << endl;
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
    int a[] = {1, 2, 4, 3, 5};
    quickSort(a, 0, 4);
    cout << quickSortComparsionsNumber << " " << quickSortPermutationsNumber;

//    int aa[] = {1, 2, 4, 3, 5};
//    insertionSort(aa, 5);
//    int n;
//    int cnt = 0;
//    while (cnt <= 4) {
//        switch (cnt) {
//            case 0:
//                n = 1'000;
//                break;
//            case 1:
//                n = 5'000;
//                break;
//            case 2:
//                n = 10'000;
//                break;
//            case 3:
//                n = 20'000;
//                break;
//            case 4:
//                n = 50'000;
//                break;
//        }
//        int a[MAXN];
//
//        fillRandomNumbers(a, n);
//        bubbleSort(a, n);
//
//        fillRandomNumbers(a, n);
//        quickSort(a, n, 0, n - 1);
//
//        fillRandomNumbers(a, n);
//        insertionSort(a, n);
//
//        cout << "n = " << n << ":" << endl;
//        cout << '\t' << "Bubble sort: " << bubbleSortComparsionsNumber << " " << bubbleSortPermutationsNumber << endl;
//        cout << '\t' << "Quick sort:  " << quickSortComparsionsNumber << " " << quickSortPermutationsNumber << endl;
//        cout << '\t' << "Insertion sort:  " << insertionSortComparsionsNumber << " " << insertionSortPermutationsNumber << endl;
//
//        ++cnt;
//    }
    return 0;
}
