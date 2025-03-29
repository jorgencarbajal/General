#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

void storeData(fstream &, fstream &, vector<int>&, vector<float>&);
void prntResults(const vector<float>&);
vector<float> getSlope(const vector<int>&, const vector<float>&);

int main(int argc, char** argv){

    int numValues;
    vector<int> dataF;
    vector<float> dataC, finalValues(2);

    // Declare fstream objects for reading and writing data from "fahren.txt" and "cel_wError.txt"
    fstream fahren, cel_wError;

    //Opening the "fahren.txt" and "cel_wError.txt" files for input and output
    fahren.open("fahren.txt", ios::in | ios::out );
    cel_wError.open("cel_wError.txt", ios::in | ios::out );
    
    //A function that stores the data in two vectors
    storeData(fahren, cel_wError, dataF, dataC);

    finalValues = getSlope(dataF, dataC);

    prntResults(finalValues);

    return 0;
}

void storeData(fstream& far, fstream& cel, vector<int> &d1, vector<float> &d2) {

    int num1;
    float num2;

    while (far >> num1) {
        d1.push_back(num1);
    }
    while (cel >> num2) {
        d2.push_back(num2);
    }
}

void prntResults(const vector<float>& values){
    cout << endl;
    cout << "The slope is: " << values[0] << endl;
    cout << "The intercept is: " << values[1] << endl;
    cout << endl;
}

vector<float> getSlope(const vector<int>& fahr, const vector<float>& cel){
    //Declare and Initialize
    float slope = 0, intercept = 0, sum_X = 0, sum_Y = 0, sum_XxY = 0, sum_XX = 0, sumXsquared;

    //A Vector containing the slope and intercept
    vector<float> finalValues;

    //Find the sum Values
    for (int i = 0; i < fahr.size(); i++) {
        sum_X += fahr[i];
        sum_XxY += (fahr[i] * cel[i]);
        sum_XX += (fahr[i] * fahr[i]);
    }
    for (int i = 0; i < cel.size(); i++) {
        sum_Y += cel[i];
    }
    sumXsquared = sum_X * sum_X;

    //Calculating slope and intercept from our first order equation
    slope = ((fahr.size() * sum_XxY) - (sum_X * sum_Y))/((fahr.size() * sum_XX) - sumXsquared);
    intercept = (sum_Y - (slope * sum_X))/fahr.size();

    finalValues.push_back(slope);
    finalValues.push_back(intercept);

    return finalValues;
}
