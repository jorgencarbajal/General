#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;


//A function(s) that returns a pointer to an integer
// ,this integer is holding the memory address of the
// first element in an array
int *filAray(int);
int *fil1t2(int,int);
//Same as above but now instead this return a pointer to the address
// of a pointer and that pointer is pointing to the address of the
// first element of an array.
//The idea here is that one pointer points to pointer of rows, and the other
// to first element address in an array representing columns
int **filAray(int,int);
//A function that takes in an integer pointer and two ints
void prntAry(int *,int,int);
void prnt1t2(int *,int,int);
void prntAry(int **,int,int);
void destroy(int *);
void destroy(int **,int);

//Program Execution Begins Here
int main(int argc, char** argv) {

    //Set the random number seed
    srand(static_cast<unsigned int>(time(0)));

    //Declare all Variables Here
    int row,col,perLine,*a1D,**a2D,*a12D;
    
    //Input or initialize values Here
    row=5,perLine=col=10;

    //Here we are calling a function that fills a 1D array
    //a1D points to the address of the first element in and array
    a1D=filAray(row*col);

    //To my best guess this is a way of showing you a way in using
    // rows and colums to simulate filling a 2D array
    //The indexing is key, and using the formula row*col+c is necessary
    a12D=fil1t2(row,col);

    //Function that takes in two parameters filling a 2D array
    a2D=filAray(row,col);
    
    //Print function taking in a single dimension array pointer, some other stuff
    // and easily printing with the end of row being met with a cout<<endl; to 
    // begin the next row
    prntAry(a1D,row*col,perLine);

    //Same as above now instead of the total number of elements row*col
    // we have the actual rows and columns
    prnt1t2(a12D,row,col);

    //2D array, shows how the 2D array is simply printed, the trick part about here
    // is understanding the dynamic structure in the fille process
    prntAry(a2D,row,col);
    
    //Clean up
    destroy(a1D);
    destroy(a12D);
    destroy(a2D,row);

    //Exit
    return 0;
}

void destroy(int **array,int row){
    for(int r=0;r<row;r++){
        delete []array[r];
    }
    delete []array;
}

void destroy(int *a){
    delete []a;
}

void prntAry(int **a,int row,int col){
    cout<<endl;
    for(int r=0;r<row;r++){
        for(int c=0;c<col;c++){
            cout<<a[r][c]<<" ";//2 digit numbers
        }
        cout<<endl;
    }
    cout<<endl;
}

void prnt1t2(int *a,int row,int col){
    cout<<endl;
    for(int r=0;r<row;r++){
        //I new it was going to be this bs
        for(int c=0;c<col;c++){
            //I think the reason behind this is two show you that passing in the parameters
            // rows and columns can still construct you a 2D array with a 1D array
            cout<<a[r*col+c]<<" ";//2 digit numbers
        }
        cout<<endl;
    }
    cout<<endl;
}

void prntAry(int *a,int n,int perLine){
    cout<<endl;
    for(int i=0;i<n;i++){
        cout<<a[i]<<" ";
        //Only interesting thing here is that once we get to the end of the row
        // the cout<<endl; is printed
        if(i%perLine==(perLine-1))cout<<endl;
    }
    cout<<endl;
}

int **filAray(int row,int col){
    //Ensure rows and col are within bounds
    row=row<2?2:
      row>1000?1000:row;
    col=col<2?2:
      col>1000?1000:col;

    //This dynamically allocates a 2D array that points to the address of the first
    // element of an array of pointers
    //This first part only dynamically allocates the row pointers
    int **array=new int*[row];

    for(int r=0;r<row;r++){
        //This part right here dynamically allocates the columns
        //Which in this case is simply a pointer pointing to the address of the first
        // element in this "row"
        //Through each iteration of the for loop the new column array is dynamically allocated
        //Since we already initialized above, here we are just initializing the columns
        array[r]=new int[col];
        for(int c=0;c<col;c++){
            array[r][c]=rand()%90+10;//2 digit numbers
        }
    }
    return array;
}

int *fil1t2(int row,int col){
    int n=row*col;
    n=n<2?2:
      n>1000?1000:n;
    int *array=new int[n];
    for(int r=0;r<row;r++){
        for(int c=0;c<col;c++){
            array[r*col+c]=rand()%90+10;//2 digit numbers
        }   
    }
    return array;
}

//Dynamically fills the pointer array
int *filAray(int n){
    n=n<2?2:
      n>1000?1000:n;
    //Dynamically allocate memory to a new pointer to an array
    // with n elements
    int *array=new int[n];
    for(int i=0;i<n;i++){
        array[i]=rand()%90+10;//2 digit numbers
    }
    return array;
}
