// Given a binary array nums, return the maximum number of consecutive 1's in the array

class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int currPos = 0,
            max = 0;

        for(int i=0; i<nums.size(); i++){
            if(nums[i]==1){
                currPos += 1;
                if(currPos>max)
                    max = currPos;
            }
            else
                currPos = 0;
        }
        return max;
    }
};

