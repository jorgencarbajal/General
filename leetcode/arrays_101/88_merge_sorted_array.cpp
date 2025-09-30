class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int size = nums1.size();

        // Since nums1 is alread the appropriate size, push nums2 onto nums1?
        for(int i = 0; i < n; i++){
            nums1[m + i] = nums2[i];
        }

        // Then sort the hoe using bubble sort
        for(int j = 0; j < size-1; j++){
            for(int k = (j+1); k < size; k++){
                if(nums1[k] < nums1[j]){
                    int temp = nums1[j];
                    nums1[j] = nums1[k];
                    nums1[k] = temp;
                }
            }
        }
    }
};