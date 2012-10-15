/*=============================================================================
author        :Walter Schreppers
filename      :Date.h
created       :/
modified      :14/01/1998
version       :13
copyright     :Walter Schreppers
bugreport(log):/
=============================================================================*/

#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <string>

// include extern c header-file 
extern "C" {
	#include <time.h>
	#include <ctype.h>
}

using namespace std;

class Date {

   public:
      
      // exeption class
      // ==============
      
     struct Invalid_Date {
      	int fDay, fMonth, fYear;
      	string fError;
      	Invalid_Date(int d, int m, int y, string s): fDay(d), fMonth(m), fYear(y), fError(s) {};
        // 'fDay(d), ..., fYear(y)' = initializatielijst waarbij er een bitwise copy (default copy-constructor)
      	// wordt gedaan. (Hier o.a. een copy v/d variabele 'd' naar 'fDay'.)
     };
   
      // constructors/destructor
      // =======================
      
      Date();				// take current date
      Date(int d);			// give day rest is current
      Date(int d,int m);		// give day and month year is current
      Date(int d, int m, int y);        // give day, month and year
      Date(const Date&); 		// give Date = copy constructor         			 

      
      // members
      // =======
      int dow() const;				// day of week - integer
      string str_dow() const;			// day of week - short string 
      string str_ldow() const;			// day of week - long string
      
      int day() const;				// get day
      int month() const;			// get month
      int year() const; 			// get year
      int dayofyear() const;			// get day of year
      int weekofyear() const;			// get week in year
      bool isleapyear() const;                  // is year a leapyear?
      
      string str_month() const;			// month as short string
      string str_lmonth() const;		// month as long string
      
      string str() const;			// Date als een string

      // friends
      // =======
      
      friend ostream& operator <<(ostream&,const Date&);
      friend istream& operator >>(istream&,Date&);

      
      // operators
      // =========
      
      Date& operator=(const Date&); 	// copy constructor
      Date& operator+=(int);		// met return *this
      Date& operator-=(int);
      
      Date& operator++();  	// prefix
      Date operator++(int); 	// postfix 
      Date& operator--();	// prefix
      Date operator--(int);	// postfix
            
      
      
      Date operator-(int);	// ex: Date = Date - 5
      Date operator+(int);
      long operator-(const Date&);
     
      
      bool operator==(const Date&) const;
      bool operator!=(const Date&) const;
      bool operator<(const Date&) const;
      bool operator<=(const Date&) const;
      bool operator>(const Date&) const;
      bool operator>=(const Date&) const;
       	
   private:

     // locals
     // ======
     
     double JEDay;
     
     // private members
     // ===============
     
    void ConvertToJEDay(int,int,int,double&);
    void ConvertToCalendar(double,int&,int&,int&) const;
    void TestInput(int,int,int);	//throws Invalid_Date if input not satisfied         	     
    string ltostr(int n)const; //integer to string conversion
};   


#endif
 
