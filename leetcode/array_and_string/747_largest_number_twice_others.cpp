class Solution {
public:
    int dominantIndex(vector<int>& nums) {
        int maxIndex = -1,
            maxValue = -1,
            n = nums.size();

        for(int i = 0; i < n; i++){
            if(nums[i] > maxValue){
                maxValue = nums[i];
                maxIndex = i;
            }
        }
        for(int j = 0; j < n; j++){
            if(j!=maxIndex){
                nums[j] = 2*nums[j];
                if(nums[j] > nums[maxIndex]){
                    maxIndex = -1; 
                    break;
                }
            }
        }
        return maxIndex;
    }
};