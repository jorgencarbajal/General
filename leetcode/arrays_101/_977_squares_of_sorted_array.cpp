class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        
        for(int i=0; i<nums.size(); i++){
            nums[i] = pow(nums[i], 2);
        }

        sort(nums.begin(), nums.end());
    }
};




// BEST SOLUTION
// TWO POINTER TECHNIQUE

class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        int n=nums.size();
        int r=n-1,l=0,index=n-1;
        vector<int>ans(n);
        while(l<=r){
            if(abs(nums[l])>abs(nums[r])){
                ans[index]=(nums[l] * nums[l]);
                index--;
                l++;
            }
            else {
                ans[index]=(nums[r] * nums[r]);
                index--;
                r--;
            }
        }
        return ans;
    }
};