class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int size = nums.size(),
            zeroCounter = (size-1),
            nonZero = 0;

        for(int i = 0; i < size; i++){
            if(nums[i]!=0){
                nums[nonZero] = nums[i];
                nonZero++;
            }
            else
                zeroCounter++;
        }
        for(int j = nonZero; j < size; j++)
            nums[j] = 0;
    }
};