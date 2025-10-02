#include <bits/stdc++.h>
using namespace std;

// Implementation of bubble sort algorithm
void bubbleSort(vector<int>& v) {
    int n = v.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (v[j] > v[j + 1]) {
              
                // Swap element if in wrong order
                swap(v[j], v[j + 1]);
            }
        }
    }
}

int main() {
    vector<int> v = {5, 3, 1, 4, 2};

    // Use Bubble Sort to sort vector v
    bubbleSort(v);

    for (int i : v) cout << i << " ";
    return 0;
}