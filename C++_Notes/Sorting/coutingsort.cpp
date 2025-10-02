#include <bits/stdc++.h>
using namespace std;

// Implementation of counting sort algorithm
void countingSort(vector<int>& v) {
    int m = *max_element(v.begin(), v.end());
    vector<int> count(m + 1, 0);
    for (int i : v) {
        count[i]++;
    }

    int index = 0;
    for (int i = 0; i <= m; i++) {
        while (count[i] > 0) {
            v[index++] = i;
            count[i]--;
        }
    }
}

int main() {
    vector<int> v = {5, 3, 1, 4, 2};

    // Use Counting Sort to sort vector v
    countingSort(v);

    for (int i : v) cout << i << " ";
    return 0;
}