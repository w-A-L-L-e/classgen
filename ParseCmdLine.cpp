/*=============================================================================
author        :Walter Schreppers
filename      :ParseCmdLine.cpp
created       :/
modified      :25/02/2002
version       :1
copyright     :Walter Schreppers
bugreport(log):/
=============================================================================*/

#include "ParseCmdLine.h"




/*-----------------------------------------------------------------------------
name        :ParseCmdLine
description :constructor
parameters  :/
return      :ParseCmdLine
exceptions  :/
algorithm   :trivial
-----------------------------------------------------------------------------*/
ParseCmdLine::ParseCmdLine(){
  init();
}



/*-----------------------------------------------------------------------------
name        :init
description :initialization
parameters  :/
return      :/
exceptions  :/
algorithm   :initialize locals
-----------------------------------------------------------------------------*/
void ParseCmdLine::init(){
  bOps=false;
  bStl=false;
  bVerbose=false;
  progName="";
  className="";
}








/*-----------------------------------------------------------------------------
name        :getUsage
description :return Usage info as a string
parameters  :/
return      :string
exceptions  :/
algorithm   :return string with info about usage of the command line
-----------------------------------------------------------------------------*/
string ParseCmdLine::getUsage() const{
  string strProg=progName;
  return "Usage: "+strProg+" [options] <classname>\n\n"+
         "Options:\n"+
         "  -ops      add assign and relational operator\n"+
         "  -stl      adds typical stl includes and sets stl namespace\n"+
         "  -verbose  show output files\n"+
         "  -help     show this usage \n";
}



/*-----------------------------------------------------------------------------
name        :parse
description :parse command line arguments 
parameters  :/
return      :bool
exceptions  :/
algorithm   :Parse argtable and set local vars, if commandline is
             successfully parsed true is returned.
-----------------------------------------------------------------------------*/
bool ParseCmdLine::parse(int argsize,char *argtable[]){
        init();
        int i = 1;
        progName=string( argtable[0] );
        string arg;
        bool ok=1,bClass=0;
                
        while (i < argsize ) {
            arg="";
            arg+= argtable[i++];
            if ( arg == "-ops" ) {
              bOps = true;
            }
            else if ( arg == "-stl" ) {
              bStl = true;
            }
            else if( arg == "-verbose" ){
              bVerbose = true;
            }
            else if( arg == "-help" ){
              ok=0; //show usage
            }
            else if(!bClass){
              bClass=1;
              className=string( argtable[i-1] );
            }
            else{
              ok=0;
            }
        }
        
        return ok&&bClass;
}



