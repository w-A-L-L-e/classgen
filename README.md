Classgen is a nice little tool I've used for years, never posted it cause it was implemented on a few hours and I needed to clean up the code. Still it is so useful (and never got the time to clean up the code). I'm posting it as is. Basically it is a generator that helps you pump out classes quickly command line. This thing is already 10 years old but nowadays it looks a lot like rails generators. So I just had to post it .

To build just do a make and optionally sudo make install.

Anyway here's me c++ scaffolding some classes Car, Mercedes, Audi etc: 

```
classgen -help

Usage: classgen [options] 



Options:

  -ops      add assign and relational operator

  -stl      adds typical stl includes and sets stl namespace

  -verbose  show output files

  -help     show this usage 



classgen -ops -stl Mercedes

classgen -ops -stl Audi

classgen -ops -stl Opel

```


This generates some classes (.h and .cpp header and implementation) with nice indentation, comments and empty implementation files.
The tool needs to be extended to add arbitrary members and private locals after which it acts much like a rails scaffold. We could even include some ORM library so that it auto generates coupling of the local variables to sql columns. 


```
wschrep@sitonrails:~/cpp-work/testgen$ g++ -c *.cpp

cat car.h

wschrep@sitonrails:~/cpp-work/testgen$ cat car.h

/*=============================================================================
author        : Walter Schreppers
filename      : car.h
created       : 31/3/2011 at 14:49:41
modified      : 
version       : 
copyright     : Walter Schreppers
bugreport(log): 
=============================================================================*/



#ifndef CAR_H
#define CAR_H


#include <iostream> 
#include <string>



using namespace std;



class Car {

  public:

    //constructor & destructor
    //==========================

    Car();
    ~Car();


    //public members
    //==============


    //operators
    //=========
    Car& operator=( const Car& );
    friend ostream& operator<<( ostream&, const Car& );
    friend istream& operator>>( istream&, Car& );


  private:
    //private members:
    //================
    void init();


    //private locals:
    //===============

}; //end of class Car


#endif


```



