#ifndef GENERATOR_H
#define GENERATOR_H

#include <string>
#include <sstream>
using namespace std;

#include "ParseCmdLine.h"

class Generator{
  public:
    Generator( const ParseCmdLine& p ){
      className=p.className;
      bOps=p.bOps;
      bStl=p.bStl;
    }

    ~Generator(){};

    string getHeader() const;
    string getImplementation() const;

    string headerName() const;
    string implementationName() const;
  
  private:
    string upper(const string&) const;
    string lower(const string&) const;
    
    string fileHead( const string& ) const;
    string getFunctionTail() const;
    string getFunctionComment(  const string& returns = "", 
                                const string& name    = "", 
                                const string& params  = "",
                                const string& descr   = "" ) const;

    string getFunctionHead(  const string& returns = "", 
                             const string& name    = "", 
                             const string& params  = "",
                             const string& descr   = "",
                             bool  bFriend=false         ) const;

    string getFunction(  const string& returns = "", 
                         const string& name    = "", 
                         const string& params  = "",
                         const string& descr   = "" ) const;
    
    string className;
    bool bOps, bStl;    
};
#endif
