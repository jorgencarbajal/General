//System Level Libraries
#include <iostream>   //I/O Library
#include <cstdlib>    //Random Number Generator, Setting seed, etc....
#include <iomanip>    //Formatting Library
using namespace std;  //Libraries compiled under std

//User Level Libraries/Includes here.  On Code-E we have to put
//structures and classes here before main but you would never do this
//for normal projects.  We would just include many .h files

//Global Constants Only - Science/Math Related, Conversions, Higher
//Dimensions.  Put Global Variables anywhere in your program i.e. variables
//not contained in functions and I will give you an F!  Local variables
//only allowed.

//Function Prototypes here, Function implementations after main!

//Execution Begins Here!
int main(int argc, char** argv) {
    //Variable Declarations
    int nMovies;       //Number of Movie structures I have to create!
    string movName;    //Movie Name
    const char SIZE=81;//Director Name Dimension Max
    char dirName[SIZE];//Director Name.  Why use a character array?
                       //Why not!  I should be able to use both, string/char[]
    int runTime,       //Runtime in minutes
            yrRlsd;    //Year Released AD
    
    //Variable Initialization
    cin>>nMovies;                //Integer Read
    //important for clearing input buffer
    cin.ignore();                //Oh Yea, Gotta do this for the buffer
    //one is used for strings
    getline(cin,movName);        //Then I can read in strings with spaces
    //the other is used for char characters
    cin.getline(dirName,SIZE-1); //Then I can read in chars with spaces
    cin>>runTime;                //Look ma, no ignore after gets!!!!
    cin>>yrRlsd;                 //Look again,no ignore after gets, only before

    //Mapping Process Inputs to Outputs

    //Display Outputs
    cout<<"Number of Movies:"<<nMovies<<endl;
    cout<<"Movie Name      :"<<movName<<endl;
    cout<<"Director Name   :"<<dirName<<endl;
    cout<<"Run Time        :"<<runTime<<endl;
    cout<<"Year Released   :"<<yrRlsd<<endl;
    
    //Clean Up

    //Exit stage right!
    return 0;
}
