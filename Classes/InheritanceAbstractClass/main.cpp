/* 
 * Author: Dr. Mark E. Lehr
 * Purpose:  Abstraction, Operator Overloading, 
 *           Copy Construction and Polymorphism
 */

//User Libraries
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iomanip>
using namespace std;

//User Libraries
class AbsRow{
    protected:
        int size;
        int *rowData;
    public:
        virtual int getSize()const = 0;
        virtual int getData(int)const = 0;
};

class RowAray:public AbsRow{
    public:
        RowAray(unsigned int);
        virtual ~RowAray();
        int mrkRand(int);
        int getSize()const{return size;}
        int getData(int i)const{
            if(i>=0&&i<size)return rowData[i];
            else return 0;}
        void setData(int,int);
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

RowAray::RowAray(unsigned int n){
    size=n;
    rowData=new int[size];
    for(int i=0;i<size;i++){
        rowData[i]=mrkRand(size)%90+10;
    }
}

RowAray::~RowAray(){
    delete []rowData;
}

void RowAray::setData(int row,int val){
    if(row>=0&&row<size)rowData[row]=val;
    else rowData[row]=0;
}

class AbsTabl{
    protected:
        int szRow;
        int szCol;
        RowAray **columns;
    public:
        virtual int getSzRow()const = 0;
        virtual int getSzCol()const = 0;
        virtual int getData(int,int)const = 0;
};

class Table:public AbsTabl{
    public:
        Table(unsigned int,unsigned int);
        Table(const Table &);
        virtual ~Table();
        int getSzRow()const {return szRow;}
        int getSzCol()const {return szCol;}
        int getData(int,int)const;
        void setData(int,int,int);
};

Table::Table(unsigned int rows,unsigned int cols){
    szRow=rows;
    szCol=cols;
    columns=new RowAray*[cols];
    for(int col=0;col<cols;col++){
        columns[col]=new RowAray(rows);
    }
}

Table::Table(const Table &a){
    //Student to supply
    szRow = a.szRow;
    szCol = a.szCol;

    //Creating the new columns array of pointers, size "szCol"
    columns = new RowAray*[szCol];

    for(int i = 0; i < szCol; i++){

        columns[i] = new RowAray(szRow);
        
        for(int j = 0; j < szRow; j++){
            //Get data from the a table
            int data = a.getData(j, i);
            //cout << data << endl;

            columns[i]->setData(j, data);
        }
    }
}

Table::~Table() {
    for(int i = 0; i < szCol; i++) {
        delete columns[i];
    }
    delete[] columns;
}

int Table::getData(int row,int col)const{
    //Student to supply
    //Here the table accesses the correct column array pointer
    // then uses the getdatafunction from the RowAray class since 
    // columns is of that class type

    //"getData" gets data from the RowAray class
    return (*columns[col]).getData(row);
}

void Table::setData(int row,int col,int val){
    //Student to supply
    //This function changes the current data in the slot to the val data.
    columns[col]->setData(row, val);

}

//Defining a new class called PlusTab, and it inherits publicly from another class called Table.
class PlusTab:public Table{
    public:
        //A delegating constructor that calls the parent constructor
        //Unsigned because we only care about positive numbers
        PlusTab(unsigned int r,unsigned int c):Table(r,c){};
        PlusTab operator+(const PlusTab &);
};

PlusTab PlusTab::operator+(const PlusTab &a){
    //Student to supply
    //The new PlusTab object, after this line the plustab object 
    // is filled with random data
    PlusTab result(this->szRow, this->szCol);

    for(int i = 0; i < this->szCol; i++){
        for(int j = 0; j < this->szRow; j++){
            int sum = (this->getData(j, i) + a.getData(j, i));

            result.setData(j, i, sum);
        }
    }
    return result;
}

//Global Constants

//Function Prototype
void prntTab(const Table &);

//Execution Begins Here!
int main(int argc, char** argv) {
   //Initialize the random seed
   srand(static_cast<unsigned int>(time(0)));
   
   //Declare Variables
   int rows,cols;
   
   //Initialize Variables
   cout<<"Input the Rows and Cols"<<endl;
   cout<<"For a 2-D Array composed of 1-D Rows"<<endl;
   cout<<"Created from Abstract Classes"<<endl;
   cout<<"Inherited to include Overloaded Operators"<<endl;
   cin>>rows>>cols;
   
   //Starts here essentially, we create an object tab1 of type "PlusTab"
   // taking in two arguments of rows and cols
   PlusTab tab1(rows,cols);
   //Now tab2 is created of the same type and takes in tab1 as an argument
   PlusTab tab2(tab1);
   PlusTab tab3=tab1+tab2;
   
   //Print the tables
   cout<<"Abstracted and Polymorphic Print Table 1 size is [row,col] = ["
           <<rows<<","<<cols<<"]";
   prntTab(tab1);
   cout<<"Copy Constructed Table 2 size is [row,col] = ["
           <<rows<<","<<cols<<"]";
   prntTab(tab2);
   cout<<"Operator Overloaded Table 3 size is [row,col] = ["
           <<rows<<","<<cols<<"]";
   prntTab(tab3);

   //Exit Stage Right
   return 0;
}

void prntTab(const Table &a){
    cout<<endl;
    for(int row=0;row<a.getSzRow();row++){
        for(int col=0;col<a.getSzCol();col++){
            cout<<setw(4)<<a.getData(row,col);
        }
        cout<<endl;
    }
    cout<<endl;
}
