class Solution {
public:
    vector<int> replaceElements(vector<int>& arr) {

        int size = arr.size();

        // Looping through the array
        for(int i = 0; i < size; i++){
            int max = 0;

            // Condition for a single element
            if(i == (size-1)){
                arr[i] = -1;
            }

            // When more than one element, find the largest element
            // to the right
            else{
                for(int j = (i+1); j < size; j++){
                    if(arr[j] > max)
                        max = arr[j];
                }
                arr[i] = max;
            }
        }
        return arr;
    }
};