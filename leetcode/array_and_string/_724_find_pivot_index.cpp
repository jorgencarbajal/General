class Solution {
public:
    int pivotIndex(vector<int>& nums) {
        int size = nums.size(),
            leftMost = -1;

        vector<int> sumLeft(size, 0);  // Initialize with 0
        vector<int> sumRight(size, 0);

        // iterate through the vector, at each postion
        // update the arrays holding sums
        for(int i = 0; i < size; i++){
            // for the scenario where the index is inbetween
            if(i != 0 && i != (size-1)){
                // calculate the sum of the left values
                int totalL = 0;
                for(int j = 0; j < i; j++){
                    totalL+=nums[j];
                }
                sumLeft[i]=totalL;
                // calculate the sum of the right values
                int totalR = 0;
                for(int m = i+1; m < size; m++){
                    totalR+=nums[m];
                }
                sumRight[i]=totalR;
            }
            // We know that at index 0 is the left edge so the sum is 
            // zero
            // we still need to at the right, so the inner loop is for the right
            else if(i == 0){
                int total = 0;
                sumLeft[i] = 0;
                for(int k = 1; k < size; k++){
                    total+=nums[k];
                }
                sumRight[i]=total;
            }
            // We know that at index (size-1) is the right edge so the sum is 
            // zero
            // we still need to at the right, so the inner loop is for the right
            else{
                int total = 0;
                sumRight[i]=0;
                for(int n = 0; n < size-1; n++){
                    total+=nums[n];
                }
                sumLeft[i]=total;
            }      
        }
        for(int j = 0; j < size; j++){
            if(sumLeft[j] == sumRight[j]){
                leftMost = j;
                break;
            }
        }
        return leftMost;
    }
};


// BEST SOLUTION

class Solution {
public:
    int pivotIndex(vector<int>& nums) {
        int total = accumulate(nums.begin(), nums.end(), 0); 
        int leftsum = 0;
        for(int i = 0; i < nums.size(); i++)
    {
        int rightsum = total - leftsum - nums[i];
        if(leftsum == rightsum){
            return i;
             }
        leftsum = leftsum+nums[i];
    }
    return -1;
        
    }
};