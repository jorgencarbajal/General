class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int k = 0; // Pointer for next non-val element position
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] != val) {
                nums[k] = nums[i]; // Place non-val element at index k
                k++; // Increment k for next non-val position
            }
        }
        return k; // k is the count of non-val elements
    }
};