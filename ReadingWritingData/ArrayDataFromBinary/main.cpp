/* 
 * File:   main.cpp
 * Author: Dr. Mark E. Lehr
 * Created on April 6th, 2021, 1:30 PM
 * Purpose:  Create a database of array data
 * using binary files and irregular sized structures
 */

//System Libraries Here
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <fstream>
using namespace std;

//User Libraries Here
#include "Array.h"

//Global Constants Only, No Global Variables
//Like PI, e, Gravity, or conversions

//Returns a pointer to an Array Structure
Array *fillAry(int,int);
void prntAry(Array *,int);
//Writes into file from the structure
void wrtTxt(fstream &,Array *,int);
//Wries to bin from the structure
void wrtBin(fstream &,Array *);
//Reads whats in the bin into a structure and returns the structure
Array *readBin(fstream &,int,int);
//Destroy the pointer structure
void destroy(Array *);

//Program Execution Begins Here
int main(int argc, char** argv) {
    //Set the random number seed
    srand(static_cast<unsigned int>(time(0)));
    
    //Open the Text and binary files
    fstream txtFile,binFile;
    txtFile.open("data.txt",ios::out);
    binFile.open("data.bin",ios::out|ios::binary);
    
    //Declare all Variables Here and Loop
    int nRecords=100;//Number of records 
    int perLine=10;  //Number to print per Line
    int size=50;     //Fixed size
    
    //Fill a binary and text file with a bunch of irregular size structures
    for(int record=0;record<nRecords;record++){
        //Dynamically allocate the Array pointer structure
        //Fill it
        //Write it into files
        //Destroy it
        //100 times

        //Creating a dynamically allocated structure
        // taking in size and the current record as arguments into the function
        //That function then returns a pointer to a structure
        Array *array=fillAry(size,record);

        //Printout the sorted array
        //Once the structure has been filled with stuff
        //We write that data into a txt file
        wrtTxt(txtFile,array,perLine);
        //Same for the bin fill
        //We are essentially dumping the data into files then destroying the 
        // dynamically allocated arrays
        wrtBin(binFile,array);
        destroy(array);
    }
    
    //Read back in the array, then print out
    //Pick a random record
    int randRec=rand()%nRecords;

    cout<<"Random record to find = "<<randRec<<endl;
    Array *brray=readBin(binFile,size,randRec);
    prntAry(brray,perLine);
    
    //Delete the array
    destroy(brray);
    
    //Close the files
    txtFile.close();
    binFile.close();
    
    //Exit
    return 0;
}

Array *readBin(fstream &in,int size,int record){
    //Declare and initialize variables
    int count=0;       //Size of array and records
    long cursor;    //Where to place the cursor
    Array *a=new Array;//Declare the array to return
    
    //In the bin file the memory is allocated sequentially
    //Cursor needs to go to that spot according to that record
    //size plus 1 accounts for the additional memory for the size integer
    //50 for the array, +1 for the size integer
    //each Arrays structure holds 51*4 bytes of memory multiply be record and it
    // takes you to the spot
    cursor=record*((size+1)*sizeof(int));
    
    //is used to move the input file pointer (read cursor) to a specific position in the file
    in.seekg(cursor,ios::beg);
    // Reads the size of the array (stored as an integer) from the file and stores it in a->size.
    in.read(reinterpret_cast<char *>(&a->size),sizeof(int));
    // Dynamically allocates memory for the data array, with a size based on a->size, 
    // and makes a->data point to the first element of the array.
    a->data=new int[a->size];
    // Reads the binary data from the file into a->data, 
    // with the number of bytes based on a->size * sizeof(int).
    in.read(reinterpret_cast<char *>( a->data),a->size*sizeof(int));
    return a;
}

void wrtBin(fstream &out,Array *a){
    // Writing the size of the array to the binary file.
    // We use reinterpret_cast to treat the address of 'size' as a char* for writing raw bytes.
    out.write(reinterpret_cast<char *>(&a->size),sizeof(int));
    // Writing the array data to the binary file.
    // Since 'a->data' is already a pointer, we cast it to char* and write 'size' * sizeof(int) bytes.
    out.write(reinterpret_cast<char *>(a->data),a->size*sizeof(int));
}

//Simply filling the txt file with the structure data
void wrtTxt(fstream &out,Array *a,int perLine){
    out<<endl;
    out<<"Array Size = "<<a->size<<endl;
    for(int i=0;i<a->size;i++){
        out<<setw(6)<<a->data[i];
        if(i%perLine==(perLine-1))out<<endl;
    }
    out<<endl;
}

void destroy(Array *a){
    delete []a->data;
    delete a;
}

void prntAry(Array *a,int perLine){
    cout<<endl;
    cout<<"Array Size = "<<a->size<<endl;
    for(int i=0;i<a->size;i++){
        cout<<setw(6)<<a->data[i];
        if(i%perLine==(perLine-1))cout<<endl;
    }
    cout<<endl;
}

Array *fillAry(int n,int mod){
    //Declare the array and its components
    Array *a=new Array;
    a->size=n>1?n:2;
    a->data=new int[a->size];
    //Fill the components with data
    for(int i=0;i<a->size;i++){
        a->data[i]=mod*1000+rand()%100;
    }
    //Return the Array
    return a;
}
