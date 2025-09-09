#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iomanip>
using namespace std;

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

    unsigned int a=31051;
    unsigned int c=997;   
    unsigned int shrt=1<<15-1; 
    unsigned int m=1<<31-1;    
    static int Xn=30937;       
    static int cnt=0;          
    if(cnt==0&&seed<=shrt)Xn=seed;
    cnt++;
    Xn=(a*Xn+c)%m;
    return Xn;
}

// #7 The constructor is called, here the object is of type RowAray (not AbsRow,
// which is abstract and cannot be instantiated). Inside that class there is
// rowData, a protected member of AbsRow, inherited and initialized by RowAray
// according to the row size and the mrkRand function, which is a function in
// the RowAray class that generates random values.
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

// #4 Since our declaration had the two arguments we use this constructor
// Here the szRow and szCol are initialized to what our user entered as
// values. Those variables aren’t in the Table class but since Table inherits
// AbsTabl and those variables are in there, they are able to get set.
Table::Table(unsigned int rows,unsigned int cols){
    szRow=rows;
    szCol=cols;
    // #5 Columns is also in the AbsTab1 and its a double pointer of the type RowAray
    // Here we dynamically allocate new memory of type RowAray. Think of the outer pointer
    // pointing to an array of pointers objects
    columns=new RowAray*[cols];
    for(int col=0;col<cols;col++){
        // #6 each individual pointer in the array of pointers is initialized to an object of type
        // RowAray and that object gets initialized by calling the constructor
        columns[col]=new RowAray(rows);
    }
}

// #9 This is the copy constructor, invoked when PlusTab tab2(tab1) is executed
// in main. It doesn’t require a separate constructor because it’s automatically
// called when an object is initialized with another object of the same type
// (copy construction). Here we are essentially just taking that new object,
// since Table inherits AbsTabl, and the variables in there are szRow and szCol,
// they get initialized to the values from the object we passed in as a const
// by reference.
Table::Table(const Table &a){

    szRow = a.szRow;
    szCol = a.szCol;

    // #10 Our object columns variable in the Abs class get dynamcially allocate memory
    // A pointer of pointers with the outer pointer pointing to the first element in an array
    // of pointer objects of the type RowAray
    columns = new RowAray*[szCol];

    for(int i = 0; i < szCol; i++){

        // #11 Looping through the outer array and initializing each pointer to an object RowAray
        // same as step 6
        columns[i] = new RowAray(szRow);
        
        // #12 We then loop throught the new table we created and reinitialize all the data to the
        // same data as the table we passed in
        for(int j = 0; j < szRow; j++){
            
            int data = a.getData(j, i);

            // #13 This part was a bit tricky but essentially when you call columns[i]->setData,
            // because columns[i] is a pointer to a RowAray object, that is the setData
            // function that is used from the RowAray class.
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

    return (*columns[col]).getData(row);
}

void Table::setData(int row,int col,int val){

    columns[col]->setData(row, val);

}


class PlusTab:public Table{
    public:

        // #3 In the PlusTab class we have a constructor that takes in two parameters, and because
        // PlusTab inherits Table we use the Table constructor
        PlusTab(unsigned int r,unsigned int c):Table(r,c){};
        PlusTab operator+(const PlusTab &);
};

// #15 The object to the left of the operation gets treated as the "this" object,
// the object to the right gets treated as the object that gets passed into the
// function, essentially the &a.
PlusTab PlusTab::operator+(const PlusTab &a){

    // #16 Creating a new object called result, and essentiall runs through steps 3-7 to get all its
    // inner object initialized
    PlusTab result(this->szRow, this->szCol);

    // #17 Looping through the entire table, adding and setting data. Using the getData functions
    // from the table scope since "this->" is the tab1 object so its calling from its class scope
    for(int i = 0; i < this->szCol; i++){
        for(int j = 0; j < this->szRow; j++){
            int sum = (this->getData(j, i) + a.getData(j, i));

            // #18 The last function to use, uses the function to access the RowAray object to 
            // then get to the right pointer of pointer to set the data
            result.setData(j, i, sum);
        }
    }
    return result;
}

void prntTab(const Table &);

// #0 The idea behind this program is to display a table of values, the key here is the way in which
// the tables are constructed. We use abstract classes and class inheritance to provide polymorphism
// and enforce a consistent interface, allowing flexibility and extensibility. We also use overloaded
// operators (like operator+) to allow intuitive syntax (e.g., tab1 + tab2) for custom operations,
// enhancing readability and usability.

int main(int argc, char** argv) {

   srand(static_cast<unsigned int>(time(0)));
   
   int rows,cols;

   // #1 Here we start by getting input from the user, we ask for the rows and columns
   cout<<"Input the Rows and Cols"<<endl;
   cout<<"For a 2-D Array composed of 1-D Rows"<<endl;
   cout<<"Created from Abstract Classes"<<endl;
   cout<<"Inherited to include Overloaded Operators"<<endl;
   cin>>rows>>cols;

   // #2 We create our first object of the class type "PlusTab" and call it "tab1"
   PlusTab tab1(rows,cols);
   // #8 The tab1 object has been initialized, here we are initializing a another 
   // object but the key here is that the argument is another object
   PlusTab tab2(tab1);
   // #14 We have successfully copied all the data over from one object to another
   // Now to use the fancy operational analysis we just learned about the other 
   // day
   PlusTab tab3=tab1+tab2;
   
   // #19 All the printing, nothing special
   cout<<"Abstracted and Polymorphic Print Table 1 size is [row,col] = ["
           <<rows<<","<<cols<<"]";
   prntTab(tab1);
   cout<<"Copy Constructed Table 2 size is [row,col] = ["
           <<rows<<","<<cols<<"]";
   prntTab(tab2);
   cout<<"Operator Overloaded Table 3 size is [row,col] = ["
           <<rows<<","<<cols<<"]";
   prntTab(tab3);

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
