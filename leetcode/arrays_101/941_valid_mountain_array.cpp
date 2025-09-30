class Solution {
public:
    bool validMountainArray(vector<int>& arr) {
        int n = arr.size();
        if (n < 3) return false; // Must have at least 3 elements
        
        int i = 0; // Track current position
        
        // Find strictly increasing part
        while (i + 1 < n && arr[i] < arr[i + 1]) {
            i++;
        }
        
        // Check if peak is at start or end (invalid)
        if (i == 0 || i == n - 1) return false;
        
        // Check strictly decreasing part
        while (i + 1 < n && arr[i] > arr[i + 1]) {
            i++;
        }
        
        // Valid mountain if we reached the end
        return i == n - 1;
    }
};