class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int n = digits.size();

        for(int i=n-1; i>=0; i--){
            if(digits[i]==9  && i!=0){
                digits[i]=0;
                continue;
            }
            else if(digits[i]==9 && i==0){
                digits[i]=0;
                digits.insert(digits.begin(), 1);
                break;
            } 
            else{
                digits[i]+=1;
                break;
            }
        }
        return digits;
    }
};


// BEST SOLUTION

class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        vector<int> result;
        int temp = 1;
        int i = digits.size() -1;
        while(i>=0 || temp){
           int digit = i>=0 ? digits[i] : 0;
           int sum = digit +temp;
           temp = sum /10;
           sum = sum %10;
           i--;
           result.push_back(sum);
        }
        reverse(result.begin() , result.end());
        return result;
    }
};