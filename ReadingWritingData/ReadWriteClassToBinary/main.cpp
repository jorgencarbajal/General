//System Libraries Here
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <fstream>
using namespace std;

//User Libraries Here
#include "Test.h"

//Global Constants Only, No Global Variables
//Like PI, e, Gravity, or conversions

//Function Prototypes Here
//fstream, reading from and writing to files
//ofstream writes to files (output)
//ifstream reads from files (input)
void wrtTxt(fstream &,Test *,int);
void wrtBin(fstream &,Test *);
//A function returning a class of type Test. Public variable: char c; short s; int i;
Test *readBin(fstream &,int);
void prntTxt(Test *);

//Program Execution Begins Here
int main(int argc, char** argv) {

    //Set the random number seed
    srand(static_cast<unsigned int>(time(0)));
    
    // Declare txtFile and binFile, which are fstream objects used
    // for reading from and writing to text and binary files respectively.
    fstream txtFile,binFile;
    txtFile.open("data.txt",ios::in|ios::out);
    binFile.open("data.bin",ios::in|ios::out|ios::binary);
    
    //100 record created
    int nRecords=100;
    
    //Fill a binary and text file with a bunch of regular size structures
    for(int record=0;record<nRecords;record++){
        //This dynamically allocates memory for a Test structure.
        Test *test=new Test;
        //That same test structure is initializing its public variables
        test->c=rand()%26+65; // 65-95 represents A-Z
        test->s=rand()%900+100;
        test->i=rand()%900+1000;
        
        //The function that right to a txtfile
        wrtTxt(txtFile,test,record);
        //The funciton that dumps the data into the binfile
        wrtBin(binFile,test);
        delete test;
    }
    
    //Read back in the array, then print out
    //Pick a random record
    int randRec=rand()%nRecords;
    cout<<"Random record to find = "<<randRec<<endl;
    //create a pointer to an array structure and initialize it to the function return
    Test *test=readBin(binFile,randRec);
    prntTxt(test);
    cout<<"The size of the test structure = "<<sizeof(Test)<<" bytes"<<endl;
    
    //Delete the array
    delete test;
    
    //Close the files
    txtFile.close();
    binFile.close();
    
    //Exit
    return 0;
}

Test *readBin(fstream &in,int record){
    //Declare and initialize variables
    long cursor=0L;    //Where to place the cursor
    Test *a=new Test;//Declare the array to return
    
    //Find the record
    //The byte offset ensures that the right 
    // data is being read by correctly positioning the file pointer at the exact 
    // location where the desired record starts.
    cursor=record*sizeof(Test);
    
    //Fill the structure
    //This is important because it postions where we will be reading from
    in.seekg(cursor,ios::beg);
    //This then reads it into the structure we dynamically allocated
    in.read(reinterpret_cast<char *>(a),sizeof(Test));
    return a;
}

void wrtBin(fstream &out,Test *a){

    //The first is a pointer to the data to write (reinterpret_cast<char *>(a)), 
    // converting the Test structure to a char pointer.

    //The second is the size of the data (sizeof(Test)), telling .write how much data to write
    //reinterpret_cast is a C++ type casting operator that allows you to cast one pointer type to 
    // another, even if the types are completely unrelated.
    //By casting a to char*, you're essentially saying, "Treat the memory that holds the Test structure as a block of char-sized data."
    out.write(reinterpret_cast<char *>(a),sizeof(Test));
}

/*The wrtTxt function writes the contents of the Test 
structure to the text file. It outputs the values of the c, s, and i members of the Test structure, 
formatted with setw(6) to ensure each value occupies a width of 6 characters. It also includes the 
record number in the output. This function does not read from the file, but rather writes the 
structure's values to the text file. */
void wrtTxt(fstream &out,Test *a,int record){
    out<<endl;
    out<<"Structure Contents Record = "<<record<<endl;
    out<<setw(6)<<a->c<<endl;
    out<<setw(6)<<a->s<<endl;
    out<<setw(6)<<a->i<<endl;
    out<<endl;
}

void prntTxt(Test *a){
    cout<<endl;
    cout<<"Structure Contents "<<endl;
    cout<<setw(6)<<a->c<<endl;
    cout<<setw(6)<<a->s<<endl;
    cout<<setw(6)<<a->i<<endl;
    cout<<endl;
}
