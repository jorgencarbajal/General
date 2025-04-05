/* 
 * Author: Dr. Mark E. Lehr
 * Purpose:  Template aggregates
 * 
 * Complete the code for the 2 classes, RowArray and Table Template
 * Go to Code-e and do the Template Problem based upon the last 2 assignments on the Row and Table classes.

You can also refer to Hmwk directory in the Class Repository in Github.
As in the previous homework review, you supply in this case the templates.  
You will find in the folder the driver program main as well as the guidelines for the templates.  
Create the template .h files and run.  Compare to the output results also included.
Solve the problem on Code-e and create a Netbeans project to submit the .zip file here and attach.

 */

//User Libraries
#include <iostream>
#include <iomanip>
using namespace std;

//User Libraries
template<class T>
class RowAray{
    protected:
        int size;
        T *rowData;
    public:
        RowAray(int);
        virtual ~RowAray();
        int mrkRand(int);
        int getSize()const{return size;}
        T getData(int i)const{
            if(i>=0&&i<size)return rowData[i];
            else return 0;}
        void setData(int,T);
};

template<class T>
int RowAray<T>::mrkRand(int seed){
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

template<class T>
RowAray<T>::RowAray(int n){
    size=n;
    rowData=new T[size];
    for(int i=0;i<size;i++){
        rowData[i]=mrkRand(size)%90+10;
    }
}

template<class T>
RowAray<T>::~RowAray(){
    delete []rowData;
}

template<class T>
void RowAray<T>::setData(int row,T val){
    if(row>=0&&row<size)rowData[row]=val;
    else rowData[row]=0;
}

template<class T>
class Table{
    protected:
        int szRow;
        int szCol;
        RowAray<T> **columns;
    public:
        Table(unsigned int,unsigned int);
        Table(const Table<T> &);
        virtual ~Table();
        int getSzRow()const {return szRow;}
        int getSzCol()const {return szCol;}
        T getData(int,int)const;
        void setData(int,int,T);
        Table<T> operator+(const Table<T> &);
};

// #3 Here the columns member is declared, its a double pointer. The outer pointer points 
// to the first element of the array of objects of type RowAray. In the for loop, 
// each object is getting initialized
template<class T>
Table<T>::Table(unsigned int rows,unsigned int cols){
    //Student to correct/complete
    szRow=rows;
    szCol=cols;

    columns=new RowAray<T>*[szCol];

    for(int i = 0; i < szCol; i++){
        columns[i]=new RowAray<T>(rows);
    }
    
}

// #4 Here we copy the objects. Passing in the object by reference and usin it to copy
// into the "this" object
template<class T>
Table<T>::Table(const Table &a){
    //Student to correct/complete
    szRow=a.getSzRow();
    szCol=a.getSzCol();

    columns=new RowAray<T>*[szCol];
    
    for(int i = 0; i < szCol; i++){
        columns[i]=new RowAray<T>(szRow);
        for(int j = 0; j < szRow; j++){
            int data = a.getData(j, i);

            columns[i]->setData(j, data);
        }
    }
    
}

template<class T>
Table<T>::~Table(){
    for(int i = 0; i < szCol; i++){
        // Deleting each individual pointer (inner pointers)
        delete columns[i];
    }
    // Deleting the outer pointer array
    delete []columns;
}

template<class T>
T Table<T>::getData(int row,int col)const{
    return columns[col]->getData(row);
}

template<class T>
void Table<T>::setData(int row,int col,T val){
    //Student to correct/complete
    columns[col]->setData(row, val);
}

template<class T>
Table<T> Table<T>::operator+(const Table<T> &a){
    //Student to correct/complete

    Table result(szRow, szCol);

    for(int i = 0; i < szCol; i++){
        for(int j = 0; j < szRow; j++){
            int data = (this->getData(j, i) + a.getData(j, i));

            result.setData(j, i, data);
        }
    }
    return result;
}

//Global Constants

//Function Prototype
template<class T>
void prntRow(T *,int);
template<class T>
void prntTab(const Table<T> &);

//Execution Begins Here!
int main(int argc, char** argv) {
   //Initialize the random seed
   srand(static_cast<unsigned int>(time(0)));
   
   //Declare Variables
   int rows,cols;
   
   //Input the rows and the cols
   cout<<"Input the Rows and Columns for the Row and Table Arrays"<<endl;
   cin>>rows>>cols;
   
   // #1 Creating a RowAray using the int template, calling the object a and
   // passing in rows as a parameter, doing the same for b, except this object 
   // is using the float template type intstead. We start by simply filling the
   // objects private member of rowData with data and displaying it.
   RowAray<int> a(rows);RowAray<float> b(cols);
   cout<<"Test the Integer Row with Rows"<<endl;
   prntRow(&a,rows);
   cout<<"Test the Float Row with Columns"<<endl;
   prntRow(&b,cols);
   
   // #2 Creating all the objects of type Table using the template float
   Table<float> tab1(rows,cols);
   Table<float> tab2(tab1);
   Table<float> tab3=tab1+tab2;
   
   cout<<"Float Table 3 size is [row,col] = Table 1 + Table 2 ["
           <<rows<<","<<cols<<"]";
   cout<<endl<<"Table 1"<<endl;
   prntTab(tab1);
   cout<<"Table 2 copy of Table 1"<<endl;
   prntTab(tab2);
   cout<<"Table 3 addition of Table 1 and Table 2"<<endl;
   prntTab(tab3);
   
   //Exit Stage Right
   return 0;
}

template<class T>
void prntRow(T *a,int perLine){
    cout<<fixed<<setprecision(1)<<showpoint<<endl;
    for(int i=0;i<a->getSize();i++){
        cout<<a->getData(i)<<" ";
        if(i%perLine==(perLine-1))cout<<endl;
    }
    cout<<endl;
}

template<class T>
void prntTab(const Table<T> &a){
    cout<<fixed<<setprecision(1)<<showpoint<<endl;
    for(int row=0;row<a.getSzRow();row++){
        for(int col=0;col<a.getSzCol();col++){
            cout<<setw(8)<<a.getData(row,col);
        }
        cout<<endl;
    }
    cout<<endl;
}
