/*=============================================================================
author        :Walter Schreppers
filename      :ParseCmdLine.h
created       :/
modified      :29/09/2002
version       :5
copyright     :Walter Schreppers
bugreport(log):/
=============================================================================*/


#ifndef PARSECMDLINE_H
#define PARSECMDLINE_H

#include <string>
using namespace std;


class ParseCmdLine{
  public:

    //constructor & destructor
    //========================
    ParseCmdLine();                 //constructor
    ~ParseCmdLine(){};              //destructor


    //public members
    //==============
		bool parse(int argsize,char* argtable[]);
    
    string getUsage() const;
    
    bool bOps, bVerbose, bStl;
    string progName, className;

  private:
  
		//private locals
		//==============
    		
		//private members
		//===============
	  void init();
};

#endif

