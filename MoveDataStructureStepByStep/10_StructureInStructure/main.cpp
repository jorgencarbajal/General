//System Level Libraries
#include <iostream>   //I/O Library
#include <cstdlib>    //Random Number Generator, Setting seed, etc....
#include <iomanip>    //Formatting Library
using namespace std;  //Libraries compiled under std

//User Level Libraries/Includes here.  On Code-E we have to put
//structures and classes here before main but you would never do this
//for normal projects.  We would just include many .h files

//Note:  The ADT should start with a capital letter and be as close to
//7 characters in length.  
struct MovieInfo{
    string movName;//Strings are good
    char *dirName;//You should know how to deal with dynamic character arrays
    unsigned short yrRlsd; //Don't need a larger data size and always > 0
    unsigned short runTime;//Don't need a larger data size and always > 0
};

//We will combine the Dynamic Structure with it's Size to minimize variables
//needed to be passed into functions, etc....
struct Movies{
    int nMovies;
    MovieInfo *mveInfo;
};

//Global Constants Only - Science/Math Related, Conversions, Array and Higher
//Dimensions.  Put Global Variables anywhere in your program i.e. variables
//not contained in functions and I will give you an F!  Local variables
//only allowed.

//Function Prototypes here, Function implementations after main!
Movies *fillDat();//Fill the Structure with Data
void display(Movies *);//Display the info in the Structure Array
void destroy(Movies *);//Deallocate Memory

//Execution Begins Here!
int main(int argc, char** argv) {
    //Variable Declarations
    Movies *movies;//Pointer to the dynamic Movie structure.
    
    //Initialize the Data Structure
    movies=fillDat();
    
    //Now you can loop on the data as many times as it takes!
    display(movies);
    
    //Clean Up the Dynamic Stuff
    destroy(movies);

    //Exit stage right!
    return 0;
}

void destroy(Movies *movies){
    //Clean Up the Dynamic Stuff
    for(int mvees=0;mvees<movies->nMovies;mvees++){
        delete [] movies->mveInfo[mvees].dirName;//The character arrays in the Stucture
    }
    delete [] movies->mveInfo;//Now the array of Structures
    delete movies;//Now deallocate the final Movie Structure
}

//Just copy, cut, and paste into a function.  Code already checked out in main.
void display(Movies *movies){
    //Now you can loop on the data as many times as it takes!
    for(int mvees=0;mvees<movies->nMovies;mvees++){
        //I copied the output from Code-E then applied formatting
        cout<<left<<endl;
        cout<<setw(11)<<"Title:"<<movies->mveInfo[mvees].movName<<endl;
        cout<<setw(11)<<"Director:"<<movies->mveInfo[mvees].dirName<<endl;
        cout<<setw(11)<<"Year:"<<movies->mveInfo[mvees].yrRlsd<<endl;
        cout<<setw(11)<<"Length:"<<movies->mveInfo[mvees].runTime<<endl;
    }
}

//This implementation of this function was thoroughly tested out already
//in main.
Movies *fillDat(){
    //Movies *movies declares a pointer to a Movies structure.
    //New Movies dynamically allocates memory for one Movies structure and 
    //returns a pointer to it, which is assigned to movies.
    Movies *movies=new Movies;
    //I copied the output from Code-E so I wouldn't make any typing mistakes
    //Then I just formatted.
    cout<<"This program reviews structures"<<endl;
    cout<<"Input how many movies, the Title of the Movie, Director, Year "<<
          "Released, and the Running Time in (minutes)."<<endl;
    cin>>movies->nMovies;                //Integer Read
    
    //This line dynamically allocates an array of MovieInfo structures with a size of movies->nMovies 
    // and assigns the address of the first element of the array to movies->mveInfo.
    movies->mveInfo=new MovieInfo[movies->nMovies];
    //(*movies).mveInfo=new MovieInfo[(*movies).nMovies];)

    //Now you can loop on the data as many times as it takes!
    for(int mvees=0;mvees<movies->nMovies;mvees++){//Gotta frickin indent!!!!!
        cin.ignore();              //Oh Yea, Gotta do this for the buffer
        getline(cin,movies->mveInfo[mvees].movName);//Movie Name In an Array Structure
        int size=81;//Make it Dynamic
        movies->mveInfo[mvees].dirName=new char[size];
        cin.getline(movies->mveInfo[mvees].dirName,size-1);//Array Structure element
        cin>>movies->mveInfo[mvees].yrRlsd;//Look ma, no ignore after gets!!!!
        cin>>movies->mveInfo[mvees].runTime;//Look again,no ignore after gets,only before
    }
    
    //Return what you filled
    return movies;
}
