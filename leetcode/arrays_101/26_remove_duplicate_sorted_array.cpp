class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int size = nums.size(),
            uniqueElement = 0;
        
        for(int i = 0; i < size; i++){
            if(i == 0){
                nums[uniqueElement] = nums[i];
                uniqueElement++;
            }
            else if(nums[uniqueElement-1] == nums[i]){
                continue;
            }
            else{
                if(nums[uniqueElement-1]!=nums[i]){
                    nums[uniqueElement] = nums[i];
                    uniqueElement++;
                }   
            }
        }
        return uniqueElement;
    }
};