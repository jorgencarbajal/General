//System Libraries Here
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

//Global Constants, COL does not exceed 505
const int COL=505;

//Function Prototypes Here
void filAray(int [],int);
void fil1t2(int [],int,int);
void filAray(int [][COL],int,int);
void prntAry(int [],int,int);
void prnt1t2(int [],int,int);
void prntAry(int [][COL],int,int);

int main(int argc, char** argv) {
    //Set the random number seed, time(0) seeds the time in seconds
    //has passed since a 01/01/1970, static cast converts that 
    //number type into the correct int type
    srand(static_cast<unsigned int>(time(0)));

    //Both ROW and COL have a max number of rows and colums
    const int ROW=COL;

    //Here we are declaring some arrays
    //a1s is a one dimensional array
    //a2s a two dimensional
    //a12s is a one dimensional, two dimensional array with
    // 505*505 elements
    int a1S[ROW],a2S[ROW][COL],a12S[ROW*COL];
    int row,col,perLine;
    
    //Input or initialize values Here
    row=10,perLine=col=20;

    //Here filAray is a function that files the array as a
    // one dimensional array, takes in the array and the 
    // total elements at parameters
    filAray(a1S,row*col);

    //Here a function with 3 parameters, the first takes in
    // a onwdimensinal array, we also push the rows and cols
    fil1t2(a12S,row,col);

    //A function that take in a two dimensional array and
    // the rows and cols
    filAray(a2S,row,col);
    
    //Output Located Here
    prntAry(a1S,row*col,perLine);
    prnt1t2(a12S,row,col);
    prntAry(a2S,row,col);

    //Exit
    return 0;
}

void prntAry(int a[][COL],int row,int col){
    cout<<endl;
    for(int r=0;r<row;r++){
        for(int c=0;c<col;c++){
            cout<<a[r][c]<<" ";//2 digit numbers
        }
        cout<<endl;
    }
    cout<<endl;
}

void prnt1t2(int a[],int row,int col){
    cout<<endl;
    for(int r=0;r<row;r++){
        for(int c=0;c<col;c++){
            cout<<a[r*col+c]<<" ";//2 digit numbers
        }
        cout<<endl;
    }
    cout<<endl;
}

void prntAry(int a[],int n,int perLine){
    cout<<endl;
    for(int i=0;i<n;i++){
        cout<<a[i]<<" ";
        if(i%perLine==(perLine-1))cout<<endl;
    }
    cout<<endl;
}

void filAray(int array[][COL],int row,int col){
    //Prevents the array from going out of bounds
    row=row<2?2:
      row>COL?COL:row;
    col=col<2?2:
      col>COL?COL:col;
    
    for(int r=0;r<row;r++){
        for(int c=0;c<col;c++){
            array[r][c]=rand()%90+10;//2 digit numbers
        }
    }
}

void fil1t2(int array[],int row,int col){
    //Prevents the array from going out of bounds
    int n=row*col;
    n=n<2?2:
      n>COL?COL:n;
    for(int r=0;r<row;r++){
        for(int c=0;c<col;c++){
            //Essentiall what this array[r*col+c] is doing is its
            //filling a one dimensional array in a 2D style
            //Think, what row?, there are always this many columns, 
            // then the +c will be that spot
            array[r*col+c]=rand()%90+10;//2 digit numbers
        }   
    }
}

void filAray(int array[],int n){
    //Just filling a one dimensional array, nothing special
    n=n<2?2:
      n>COL?COL:n;
    for(int i=0;i<n;i++){
        array[i]=rand()%90+10;//2 digit numbers
    }
}
