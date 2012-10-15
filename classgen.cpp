/*=============================================================================
author        :Walter Schreppers
filename      :precompile.cpp
created       :/
modified      :15/05/2001
version       :4
copyright     :Walter Schreppers
bugreport(log):/
=============================================================================*/

#include <iostream>
#include <fstream> 

using namespace std;

#include "ParseCmdLine.h"
#include "Generator.h"

void genclass( const ParseCmdLine& commands ){
  Generator gen( commands );
  if( commands.bVerbose ){
    cout<<gen.getHeader();
    cout<<gen.getImplementation();
  }
  
  //TODO check if files can be written
  ofstream header( gen.headerName().c_str() );
  header<<gen.getHeader();
  header.close();
  
  ofstream impl( gen.implementationName().c_str() );
  impl<<gen.getImplementation();
  impl.close();
}

/*-----------------------------------------------------------------------------
name        :main
description :We parse the input and open the needed input and output file and pass
             them to the Precompile function which does the convertion. 
parameters  :int argc , char*argv[]
return      :int
exceptions  :/
algorithm   :- use ParseCmdLine to parse the command line
             - use ClassGen to generate class files
-----------------------------------------------------------------------------*/
int main(int argc,char *argv[]){
  try{

	  ParseCmdLine commands;
	  if(commands.parse(argc,argv)){
      genclass( commands );
	  }
	  else{
	    cout<<commands.getUsage();
	  } 

  }
  catch(...){
    cerr<<"generator caught an exception."<<endl;
  }
  return 0;
} // main end

		
