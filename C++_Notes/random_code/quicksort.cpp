#include <iostream>
using namespace std;

void quicksort(int arr[], int left, int right) {
    if (left < right) {
        int pivot = arr[right]; // Rightmost element as pivot
        int i = left - 1;

        for (int j = left; j < right; ++j) {
            if (arr[j] < pivot) {
                ++i;
                std::swap(arr[i], arr[j]);
            }
        }
        std::swap(arr[i + 1], arr[right]);
        int pi = i + 1;

        quicksort(arr, left, pi - 1);
        quicksort(arr, pi + 1, right);
    }
}

int main() {
    int arr[] = {8, 4, 7, 3, 5, 2, 6, 1};
    int n = sizeof(arr) / sizeof(arr[0]);

    quicksort(arr, 0, n - 1);

    cout << "Sorted array: ";
    for (int i = 0; i < n; ++i)
        cout << arr[i] << " ";
    cout << endl;

    return 0;
}