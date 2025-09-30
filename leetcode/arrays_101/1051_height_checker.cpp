class Solution {
public:
    int heightChecker(vector<int>& heights) {
        int size = heights.size();
        
        vector<int> expected = heights;
        
        // bubble sort the array
        for(int j = 0; j < size-1; j++){
            for(int k = j+1; k < size; k++){
                if(expected[j] > expected[k]){
                    int temp = expected[k];
                    expected[k] = expected[j];
                    expected[j] = temp;
                }
            }
        }
        
        int nonEqual = 0;
        
        for(int i = 0; i < size; i++){
            if(heights[i]!=expected[i])
                nonEqual++;
        }
        return nonEqual;
    }
};