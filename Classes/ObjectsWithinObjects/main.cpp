/* 
 * File:   main.cpp
 * Author: Dr. Mark E. Lehr
 * Created on Feb 23rd, 2022, 8:36 PM
 * Purpose:  Dynamic Object Arrays
 */

//User Libraries
#include <iostream>
using namespace std;

//User Libraries
class RowAray{
    private:
        int size;
        int *rowData;
        int mrkRand(int);
    public:
        RowAray(int);   //Student to Complete
        ~RowAray();     //Student to Complete
        int getSize(){return size;}
        int getData(int i){return rowData[i];}
};

int RowAray::mrkRand(int seed){
    //Xn+1 = (aXn + c) mod m
    //where X is the sequence of pseudo-random values
    //m, 0 < m  - modulus 
    //a, 0 < a < m  - multiplier
    //c, 0 ≤ c < m  - increment
    //x0, 0 ≤ x0 < m  - the seed or start value
    unsigned int a=31051;      //Short Prime
    unsigned int c=997;        //Another Prime
    unsigned int shrt=1<<15-1; //Range of positive signed short
    unsigned int m=1<<31-1;    //Range of positive signed int
    static int Xn=30937;       //Short Prime
    static int cnt=0;          //Initialize the seed
    if(cnt==0&&seed<=shrt)Xn=seed;
    cnt++;
    Xn=(a*Xn+c)%m;
    return Xn;
}

RowAray::RowAray(int n){
    //Size is now equal to the columns
    size=n;
    //"rowData" points to the address of the first element of an array
    // of length "size".
    rowData=new int[size];
    for(int i=0;i<size;i++){
        //Filling in that row with random data.
        rowData[i]=mrkRand(size)%90+10;
    }
}

RowAray::~RowAray(){
   //Student to complete
   delete []rowData;
}


class Table{
    private:
        int szRow;
        int szCol;
        RowAray **records;
    public:
        Table(int,int);  //Student to Complete
        ~Table();        //Student to Complete
        int getSzRow(){return szRow;}
        int getSzCol(){return szCol;}
        int getData(int,int); //Student to Complete
};

Table::Table(int rows,int cols){
    //Student to complete
    szRow = rows;
    szCol = cols;
    //Creating an array of pointers in records of size "szRow"
    // each slot itself points to a pointer, hense the double pointer
    records = new RowAray*[szRow];

    for (int i = 0; i < szRow; i++){
        //Each slot in 'records' points to a RowAray object, which holds an array of 'szCol' columns.
        //This is the aggregate part, where Table contains multiple RowAray objects.
        //When calling the RowAray object the array gets filled by the constructor
        records[i] = new RowAray(szCol);
    }
}

Table::~Table(){
    //Student to complete
    for (int i = 0; i < szRow; i++){
        delete records[i];
    }
    delete []records;
}

int Table::getData(int row,int col){
   //Student to complete
   //Accessing the specific row pointer and using the "getData" function to
   // get the data in the specific column
   return records[row]->getData(col);
}

class Triangle{
    private:
        int szRow;
        RowAray **records;
    public:
        Triangle(int);  //Student to Complete
        ~Triangle();    //Student to Complete
        int getSzRow(){return szRow;}
        int getData(int,int);  //Student to Complete
};

Triangle::Triangle(int rows){
    //Student to complete
    szRow = rows;
    records = new RowAray*[rows];

    for(int i = 0; i < rows; i++){
        records[i] = new RowAray(i + 1);
    }
}

Triangle::~Triangle(){
    //Student to complete
    for(int i = 0; i < szRow; i++){
        delete records[i];
    }
    delete []records;
}

int Triangle::getData(int row,int col){
    //Student to complete
    //Remember to treat "records[row]" as an object, then work on that object
    // like you would any other object with its functions.
    return records[row]->getData(col);
}

//Global Constants

//Function Prototype
void prntRow(RowAray *,int);
void prntTab(Table *);
void prntTri(Triangle *);

//Execution Begins Here!
int main(int argc, char** argv) {
   //Initialize the random seed
   srand(static_cast<unsigned int>(time(0)));
   
   //Declare Variables
   int rows,cols,perLine;
   
   //Read in Rows and Cols
   cout<<"Input Rows and Cols"<<endl;
   cin>>rows>>cols;
   perLine=cols/2;
   
   //Creating an object called row, the object uses the one parameter constructor
   // with "cols" in it.
   RowAray row(cols);
    
   //Print the RowAray
   cout<<"The Row Array size = "<<row.getSize()
           <<" printed "<<perLine<<" per Line";

   prntRow(&row,perLine);
   
   //Creating a Table called "tab"
   //Tab uses the constructor with rows and cols
   Table tab(rows,cols);
   
   //Print the Table
   cout<<"The table size is [row,col] = ["<<rows<<","<<cols<<"]";
   prntTab(&tab);
   
   //Creating a triangle object called tri, using the one parameter constructor to initialize it
   Triangle tri(rows);
   
   //Print the Triangular Table
   cout<<"The triangular table size is [row,row] = ["<<rows<<","<<rows<<"]";
   prntTri(&tri);
   
   //Exit Stage Right
   return 0;
}

void prntRow(RowAray *a,int perLine){
    cout<<endl;
    for(int i=0;i<a->getSize();i++){
        cout<<a->getData(i)<<" ";
        if(i%perLine==(perLine-1))cout<<endl;
    }
    cout<<endl;
}

void prntTab(Table *a){
    cout<<endl;
    for(int row=0;row<a->getSzRow();row++){
        for(int col=0;col<a->getSzCol();col++){
            cout<<a->getData(row,col)<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}

void prntTri(Triangle *a){
    cout<<endl;
    for(int row=0;row<a->getSzRow();row++){
        for(int col=0;col<=row;col++){
            cout<<a->getData(row,col)<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}
