class Solution {
public:
    vector<int> sortArrayByParity(vector<int>& nums) {
        int size = nums.size();

        for(int i = 0; i < size; i++){
            if(nums[i]%2 != 0){
                for(int j = (i+1); j < size; j++){
                    if(nums[j]%2==0){
                        swap(nums[j], nums[i]);
                        break;
                    }     
                }
            }
        }
        return nums;
    }
};