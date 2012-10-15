/*=============================================================================
author        :Walter Schreppers
filename      :Time.h
created       :/
modified      :14/01/1998
version       :13
copyright     :Walter Schreppers
bugreport(log):/
=============================================================================*/

#ifndef TIME_H                  
#define TIME_H

#include <string>
#include <iostream>

using namespace std;
// include externe c header-file
extern "C" {
	#include <time.h>
	#include <ctype.h>
}


class Time {

   public:
      // exeption class
      // ==============
      
   	struct Invalid_Time {
      		int fHour, fMin, fSec;
      		Invalid_Time(int h, int m, int s): fHour(h), fMin(m), fSec(s) {};
     	};
     	
      // constructors/destructor
      // =======================
      
      Time();				// current time
      Time(int s);			// give seconds rest is current
      Time(int m,int s);		// give mins,secs hour is current
      Time(int h, int m, int s);        // give hours,mins,secs
      Time(const Time& t); 		// geef tijd mee = copy constructor         			 
      
      // members
      // =======
      int sec() const;				// current second
      int min() const;				// current minute
      int hour() const; 			// current hour
      string str() const;			// Time as a string
      
      // friends
      // =======
      
      friend ostream& operator <<(ostream&,const Time&); // om met cout een tijd af te drukken
      friend istream& operator >>(istream&,Time&);
      
      // operators
      // =========
      
      Time& operator=(const Time&);
      Time& operator+=(int);
      Time& operator-=(int);
      
      Time& operator++();	
      Time operator++(int);	
      
      Time& operator--();	
      Time operator--(int);	
      
      
      Time operator-(int);
      Time operator+(int);
      long operator-(const Time&);
      
      bool operator==(const Time&) const;
      bool operator!=(const Time&) const;
      bool operator<(const Time&) const;
      bool operator<=(const Time&) const;
      bool operator>(const Time&) const;
      bool operator>=(const Time&) const;
      
      
      
      int getoverflow() const;
      void resetoverflow();
      
   
   private:

     // locals
     // ======
     
     long seconds;
     int overflow; //nr of days over or underflow

     // private members
     // ===============
    void ConvertToSeconds(int,int,int,long&);
    void ConvertToTime(long,int&,int&,int&) const;
    void TestInput(int,int,int);	//throws exception if input is bad
    void TestOverflow(long);            //sets overflow int reflecting the nr of days 
    string ad(int) const; //voor propere output vb 01:09:58
    long abs(long) const; // absolute value of a long 
    string ltostr(int n)const;
};    


#endif
 
