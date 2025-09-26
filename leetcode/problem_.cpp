

bool hasDuplicates(const vector<int>& arr){

    bool result = true;
    
    for(int i = 0; i<arr.size(); i++){
        for(int j = 0; j<arr.size(); j++){
            if(i == j);
                continue;
            if(arr[i]!=arr[j])
                continue;
            else
                break;
        }
        if (i==arr.siz() && result == true){
            result = false;
            break;
        }
    }
    return result;
}