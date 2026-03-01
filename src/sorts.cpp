#include "sorts.h"

void insertionSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void selectionSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx])
                minIdx = j;
        }
        std::swap(arr[i], arr[minIdx]);
    }
}

// Partição de Hoare: dois ponteiros convergem do início e fim do subarray,
// trocando elementos que estão do lado errado do pivô.
static int hoarePartition(std::vector<int>& arr, int lo, int hi) {
    int pivot = arr[lo + (hi - lo) / 2];
    int i = lo - 1;
    int j = hi + 1;

    while (true) {
        do { i++; } while (arr[i] < pivot);
        do { j--; } while (arr[j] > pivot);

        if (i >= j) return j;
        std::swap(arr[i], arr[j]);
    }
}

void quickSort(std::vector<int>& arr, int lo, int hi) {
    if (lo >= hi) return;
    int p = hoarePartition(arr, lo, hi);
    quickSort(arr, lo, p);
    quickSort(arr, p + 1, hi);
}

static void merge(std::vector<int>& arr, int lo, int mid, int hi) {
    std::vector<int> tmp(arr.begin() + lo, arr.begin() + mid + 1);

    int i = 0, j = mid + 1, k = lo;
    while (i < (int)tmp.size() && j <= hi) {
        if (tmp[i] <= arr[j])
            arr[k++] = tmp[i++];
        else
            arr[k++] = arr[j++];
    }
    while (i < (int)tmp.size())
        arr[k++] = tmp[i++];
}

void mergeSort(std::vector<int>& arr, int lo, int hi) {
    if (lo >= hi) return;
    int mid = lo + (hi - lo) / 2;
    mergeSort(arr, lo, mid);
    mergeSort(arr, mid + 1, hi);
    merge(arr, lo, mid, hi);
}
