#include "Generator.h"
#include "Date.h"
#include "Time.h"


string Generator::fileHead(const string& fileName) const {
  Date currentDate;
  Time currentTime;
  
  ostringstream out;
  out<<"/*============================================================================="<<endl;
  out<<"author        : Walter Schreppers"<<endl;
  out<<"filename      : "<<fileName<<endl;
  out<<"created       : "<<currentDate<<" at "<<currentTime<<endl;
  out<<"modified      : "<<endl;
  out<<"version       : "<<endl;
  out<<"copyright     : Walter Schreppers"<<endl;
  out<<"bugreport(log): "<<endl;
  out<<"=============================================================================*/"<<endl;
  out<<endl;

  return out.str();
}


string Generator::getHeader() const{
  ostringstream out;

  out << fileHead(headerName());  
  
  out << "#ifndef "<< upper( className ) << "_H" << endl;
  out << "#define "<< upper( className ) << "_H" << endl;
  out<<endl;
  if( bStl ){ //include these stl things
    out << "#include <string>"            << endl;
    out << "#include <vector>"            << endl;
    out << "#include <iostream>"          << endl;
    out << endl << "using namespace std;" << endl;
  }
  else if( bOps ){ //since we define << and >> operators we need iostream
    out << "#include <iostream>"          << endl;
    out << endl << "using namespace std;" << endl;
  }
  out << ""                                   << endl;
  out << "class "+className+" {"              << endl;
  out << ""                                   << endl;
  out << "  public:"                          << endl;
  out << "    //constructor & destructor"     << endl;
  out << "    //=========================="   << endl;
  out << "    "+className+"();"               << endl;
  out << "    ~"+className+"();"              << endl;
  out << ""                                   << endl;
  out << "    //public members"               << endl;
  out << "    //=============="               << endl;
  out << ""                                   << endl;
  
  if( bOps ){
    out << "    //operators"                                        << endl;
    out << "    //========="                                        << endl;
    out << "    "+className+"& operator=( const "+className+"& );"  << endl;
    out << "    friend ostream& operator<<( ostream&, const "+className+"& );"  << endl;
    out << "    friend istream& operator>>( istream&, "+className+"& );"        << endl;
    out << ""                                                                   << endl;
  }
  
  out << "  private:"                     << endl;
  out << "    //private members:"         << endl;
  out << "    //================"         << endl;
  out << "    void init();"               << endl;    
  out << ""                               << endl;
  out << "    //private locals:"          << endl;
  out << "    //==============="          << endl;
  out << ""                               << endl; 
  out << ""                               << endl;
  out << "}; //end of class "<<className  << endl;
  out << ""<<endl;
  out << "#endif"                         << endl;
  out << ""                               << endl;

  return out.str();
}


string Generator::getImplementation() const{
  ostringstream out;
  out<<fileHead( implementationName() );
    
  out<<"#include \""<<lower(className)<<".h"<<"\""<<endl<<endl;

  //init func called by constructor
  out<<getFunction("void","init","","initialize private locals");
    
  //constructor
  out<<getFunctionHead("",className,"")<<endl;
  out<<"  init();"<<endl;
  out<<getFunctionTail();
  
  //destructor
  out<<getFunction("","~"+className);
  
  if( bOps ){
    string param=lower(className.substr(0,1));
    
    //operator =
    out << getFunctionHead( className+"&", "operator=", "const "+className+"& "+ param) << endl
        << "  if( this != &"<<param<<" ){"        << endl
        << "    //copy values of private locals"  << endl << endl
        << "  }"                                  << endl
        << "  return *this;"                      << endl
        << getFunctionTail();
    
    //friend operator <<
    out << getFunctionHead( "ostream&", 
                            "operator<<", 
                            "ostream& os, const "+className+"& "+ param, 
                            "output operator", 
                            true 
                          ) 
        << endl << endl
        << "  return os;" << endl
        << getFunctionTail();
    
    //friend operator >>
    out << getFunctionHead( "istream&", 
                            "operator>>", 
                            "istream& is, "+className+"& "+ param, 
                            "input operator", 
                            true 
                          ) 
        << endl << endl
        << "  return is;" << endl
        << getFunctionTail();
    
  }
  return out.str();
}


string Generator::getFunctionComment( const string& returns, 
                                      const string& name, 
                                      const string& params,
                                      const string& descr ) const
{
  ostringstream out;
  
  out << "/*-----------------------------------------------------------------------------"<<endl;
  out << "name        : " << name <<endl;
  out << "description : " << descr;
  
  if( name == className )     out<<"constructor";
  if( name == "~"+className ) out<<"destructor";
  out << endl;
  
  out << "parameters  : " << params   << endl;
  out << "return      : " << returns  << endl;
  out << "exceptions  : "             << endl;
  out << "algorithm   : trivial"      << endl;
  out << "-----------------------------------------------------------------------------*/"<<endl;

  return out.str();
}

string Generator::getFunctionHead(  const string& returns, 
                                    const string& name, 
                                    const string& params,
                                    const string& descr,
                                    bool  bFriend          ) const
{
  ostringstream out;

  out << getFunctionComment(returns, name, params, descr);
    
  if( returns != "" ) out<<returns<<" ";
  
  if( !bFriend ) out << className << "::";
  out << name;

  out << "(";
  if( params != "" ) out << " " << params << " ";
  out << "){";
  
  return out.str();
}

string Generator::getFunctionTail() const{
  return "}\n\n\n";
}

string Generator::getFunction(  const string& returns, 
                                const string& name, 
                                const string& params , 
                                const string& descr) const
{
  ostringstream out;
  
  out << getFunctionHead( returns, name, params, descr ) << endl << endl;
  out << getFunctionTail();
  
  return out.str();
}


string Generator::headerName() const {
  return lower(className)+".h";
}

string Generator::implementationName() const {
  return lower(className)+".cpp";
}

string Generator::upper( const string& src ) const {
  string dest="";
  for(string::const_iterator i=src.begin(); i!=src.end(); ++i ){
    if( (*i >= 'a') && ( *i <= 'z' ) ){
      dest+=( *i - 'a' ) + 'A';
    }
    else{
      dest+=*i;
    }
  }
  return dest;
}

string Generator::lower( const string& src ) const {
  string dest="";
  for(string::const_iterator i=src.begin(); i!=src.end(); ++i ){
    if( (*i >= 'A') && ( *i <= 'Z' ) ){
      dest+=( *i - 'A' ) + 'a';
    }
    else{
      dest+=*i;
    }
  }
  return dest;
}
