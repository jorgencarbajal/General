//System Libraries
#include <iostream>   //Input/Output Library
#include <cstdlib>    //Random function location
#include <ctime>      //Time Library
using namespace std;  //STD Name-space where Library is compiled

//Global Constants not Variables
//Math/Physics/Science/Conversions/Dimensions

//Function Prototypes
void fillAry(int [],int);
void prntAry(int [],int,int);
void markSrt(int [],int);

//Something you didnt know but the purpose of this part her is to take in arguments from the terminal
// argc, counts the number of arguments sent over, char** argv is an array of chars that stores
// those values
int main(int argc, char** argv) {
    
    //Set random number seed
    srand(static_cast<unsigned int>(time(0)));
    
    //Declare SIZE to be a constant size of 100
    //Declaring an array and initializing it of that size
    const int SIZE=100;
    int array[SIZE];
    
    //Sending that array into a function called fillAry
    //Arguments are the array and the size
    fillAry(array,SIZE);
    
    //Display the results
    cout<<"Display the Original Random Array"<<endl;
    //The array print function that takes in the array, size, 
    // and the number of columns the table will have
    prntAry(array, SIZE, 10);

    //markSrt function that takes in the array and the size as arguments
    markSrt(array,SIZE);
    
    //Display the results
    cout<<"Apply a loop on smallest in the list n times = Mark Sort"<<endl;
    prntAry(array, SIZE, 10);

    // Exit stage left
    return 0;
}

//We compare the current element to all subsequent elements and swap when needed, ensuring the smallest 
// values move to the front, repeating for each position until the end.
void markSrt(int a[],int n){

    //We start at the beginning of the array and are working all the way to the end.
    for(int pos=0;pos<n-1;pos++){
        
        //Pos is at the first element and i is the next
        //Going all the way to in this case n because we are starting at 1
        for(int i=pos+1;i<n;i++){

            //if the first one is greater than the second one, swap them
            // The carrot ^ is used for swapping without a temporary variable
            if(a[pos]>a[i]){//Swap
                //a[pos] now holds the XOR of both values.
                a[pos]=a[pos]^a[i];
                //(a[pos] ^ a[i]) ^ a[i]   →  a[pos] ^ (a[i] ^ a[i])   →  a[pos] ^ 0  →  a[pos]
                //So now a[i] gets the original value of a[pos].
                a[i]=a[pos]^a[i];
                //(a[pos] ^ a[i]) ^ a[pos]   →  a[i] ^ (a[pos] ^ a[pos])   →  a[i] ^ 0  →  a[i]
                //So now a[pos] gets the original value of a[i].
                a[pos]=a[pos]^a[i];
            }
        }
    }
}

//n being the size of the array,
void prntAry(int a[],int n,int perLine){
    cout<<endl;
    for(int i=0;i<n;i++){
        cout<<a[i]<<" ";
        //This modulus operation is going to execute when i%10
        // is equal to 9 because per line minus 1 is nine.
        //This will continure to indent a line for every 9th remainding 
        // digit
        if(i%perLine==perLine-1)cout<<endl;
    }
    cout<<endl;
}

//The function simply fills the array sequentially, with a
// random number between 10-99
void fillAry(int a[],int n){
    for(int i=0;i<n;i++){
        a[i]=rand()%90+10;//[10,99]
    }
}
