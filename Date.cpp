/*=============================================================================
author        :Walter Schreppers
filename      :Date.cpp
created       :/
modified      :14/01/1998
version       :13
copyright     :Walter Schreppers
bugreport(log):/
=============================================================================*/


#include "Date.h"


/*-----------------------------------------------------------------------------
name        :Date
description :constructor
parameters  :/
return      :Date
exceptions  :calls TestInput this may throw a exception
algorithm   :use <time.h> to get current day,month and year and then test it 
             with TestInput if it's satisfactory ConvertToJEDay is called
             else an exception is throwed by TestInput.
-----------------------------------------------------------------------------*/
Date::Date(){
	time_t timer = time (0);
	struct tm *tblock = localtime(&timer);
	int y = tblock->tm_year + 1900;
	int m = tblock->tm_mon + 1;
	int d = tblock->tm_mday;
	TestInput(d,m,y);
	ConvertToJEDay(d,m,y,JEDay);
}



/*-----------------------------------------------------------------------------
name        :Date
description :constructor
parameters  :int d
return      :Date
exceptions  :calls TestInput this may throw a exception
algorithm   :day=d, use <time.h> to get current month and year and then test values
             with TestInput if it's satisfactory ConvertToJEDay is called
             else an exception is throwed by TestInput.
-----------------------------------------------------------------------------*/
Date::Date(int d){
	time_t timer = time (0);
	struct tm *tblock = localtime(&timer);
	int y = tblock->tm_year + 1900;
	int m = tblock->tm_mon + 1;
	TestInput(d,m,y);
	ConvertToJEDay(d,m,y,JEDay);
}



/*-----------------------------------------------------------------------------
name        :Date
description :constructor
parameters  :int d, int m
return      :Date
exceptions  :calls TestInput this may throw a exception
algorithm   :day=d, month=m,use <time.h> to get current year and then test values
             with TestInput if it's satisfactory ConvertToJEDay is called
             else an exception is throwed by TestInput.
-----------------------------------------------------------------------------*/
Date::Date(int d, int m){
	time_t timer = time (0);
	struct tm *tblock = localtime(&timer);
	int y = tblock->tm_year + 1900;
	TestInput(d,m,y);
	ConvertToJEDay(d,m,y,JEDay);
}



/*-----------------------------------------------------------------------------
name        :Date
description :constructor
parameters  :int d, int m, int y
return      :Date
exceptions  :calls TestInput this may throw a exception
algorithm   :day=d, month=m, year=m  then test values
             with TestInput if it's satisfactory ConvertToJEDay is called
             else an exception is throwed by TestInput.
-----------------------------------------------------------------------------*/
Date::Date(int d, int m , int y){
	TestInput(d,m,y);
	ConvertToJEDay(d,m,y,JEDay);
}



/*-----------------------------------------------------------------------------
name        :Date
description :copy constructor
parameters  :const Date&
return      :Date
exceptions  :/
algorithm   :Test if given Date not equal to 'this' pointer 
             -> to prevent a copy into itself
             Use private local var JEDay of given Date d to copy 
             into new Date.
-----------------------------------------------------------------------------*/
Date::Date(const Date& d){
	if(&d != this){
		JEDay=d.JEDay;
	}
}



/*-----------------------------------------------------------------------------
name        :dow
description :give day of week as an int 0=Sunday, 1=Monday, ... , 6=Saturday
parameters  :/
return      :Date
exceptions  :/
algorithm   :compute Day of Week by using private local var JEDay and return it 
-----------------------------------------------------------------------------*/
int Date::dow() const{
	int DayOfWeek=int(JEDay+1.5)%7;
	return DayOfWeek;
}



/*-----------------------------------------------------------------------------
name        :str_dow
description :give day of week as a string Mon, ..., Sun
parameters  :/
return      :string
exceptions  :/
algorithm   :call dow() use this int in a case structure to give back
             correct string
-----------------------------------------------------------------------------*/
string Date::str_dow() const{
	int d;
	d=dow();
	switch (d){
		case 0: return "Sun"; break;
		case 1: return "Mon"; break;
		case 2: return "Tue"; break;
		case 3: return "Wed"; break;
		case 4: return "Thu"; break;
		case 5: return "Fri"; break;
		default: return "Sat"; break;
	}
	
}



/*-----------------------------------------------------------------------------
name        :str_ldow
description :give day of week as a string Monday, ..., Sunday
parameters  :/
return      :string
exceptions  :/
algorithm   :call dow() use this int in a case structure to give back
             correct string
-----------------------------------------------------------------------------*/
string Date::str_ldow() const{
	int d;
	d=dow();
	switch (d){
		case 0: return "Sunday"; break;
		case 1: return "Monday"; break;
		case 2: return "Tuesday"; break;
		case 3: return "Wednesday"; break;
		case 4: return "Thursday"; break;
		case 5: return "Friday"; break;
		default: return "Saturday"; break;
	}
}



/*-----------------------------------------------------------------------------
name        :day
description :give day of month as an int
parameters  :/
return      :int
exceptions  :/
algorithm   :call ConvertToCalendar and return the day value
-----------------------------------------------------------------------------*/
int Date::day() const{
	int d,m,y;
	ConvertToCalendar(JEDay,d,m,y);
	return d;
}



/*-----------------------------------------------------------------------------
name        :month
description :give month as an int
parameters  :/
return      :int
exceptions  :/
algorithm   :call ConvertToCalendar and return the month value
-----------------------------------------------------------------------------*/
int Date::month() const{
	int d,m,y;
	ConvertToCalendar(JEDay,d,m,y);
	return m;
}



/*-----------------------------------------------------------------------------
name        :year
description :give year as an int
parameters  :/
return      :int
exceptions  :/
algorithm   :call ConvertToCalendar and return the year value
-----------------------------------------------------------------------------*/
int Date::year() const{
	int d,m,y;
	ConvertToCalendar(JEDay,d,m,y);
	return y;
}



/*-----------------------------------------------------------------------------
name        :dayofyear
description :give day of year as an int (1..364 or 1..365 for leapyear)
parameters  :/
return      :int
exceptions  :/
algorithm   :call ConvertToCalendar, call isleapyear and compute day of year
             this is done by an algorithm for a julian day copied from a book
-----------------------------------------------------------------------------*/
int Date::dayofyear() const{
	int d,m,y;
	ConvertToCalendar(JEDay,d,m,y);
	int K;
	if (isleapyear()){
		K=1;
	} 	
	else{
		K=2;
	};
	int N = int((275*m)/9)- K * int((m+9)/12) + d - 30;
	return N;
}



/*-----------------------------------------------------------------------------
name        :weekofyear
description :give week of year as an int (1..52)
parameters  :/
return      :int
exceptions  :/
algorithm   :call day of year then divide this by seven... gives week 0..51
             so +1 to get 1..52
-----------------------------------------------------------------------------*/
int Date::weekofyear() const {
	return ((dayofyear()/7) + 1);
}



/*-----------------------------------------------------------------------------
name        :isleapyear
description :return boolean true if year is leapyear
parameters  :/
return      :bool
exceptions  :/
algorithm   :algorithm from book for Julian Day
-----------------------------------------------------------------------------*/
bool Date::isleapyear() const{
	int y=year();
	if ( (y%4==0) & (y%400!=0) ){
		return true;
	}
	else{
		return false;
	}
}



/*-----------------------------------------------------------------------------
name        :str_month
description :return month as a string "Jan".."Dec"
parameters  :/
return      :string
exceptions  :/
algorithm   :call ConverToCalander use month integer in a case to return
             month string
-----------------------------------------------------------------------------*/
string Date::str_month() const{
	int d,m,y;
	ConvertToCalendar(JEDay,d,m,y);
	switch (m){
		case 1: return "Jan"; break;
		case 2: return "Feb"; break;
		case 3: return "Mar"; break;
		case 4: return "Apr"; break;
		case 5: return "May"; break;
		case 6: return "Jun"; break;
		case 7: return "Jul"; break;
		case 8: return "Aug"; break;
		case 9: return "Sep"; break;
		case 10: return "Oct"; break;
		case 11: return "Nov"; break;
		default: return "Dec"; break;	
	}
	
}



/*-----------------------------------------------------------------------------
name        :str_lmonth
description :return month as a string "January".."December"
parameters  :/
return      :string
exceptions  :/
algorithm   :call ConverToCalander use month integer in a case to return
             month string
-----------------------------------------------------------------------------*/
string Date::str_lmonth() const{
	int d,m,y;
	ConvertToCalendar(JEDay,d,m,y);
	switch (m){
		case 1: return "January"; break;
		case 2: return "February"; break;
		case 3: return "March"; break;
		case 4: return "April"; break;
		case 5: return "May"; break;
		case 6: return "June"; break;
		case 7: return "Juli"; break;
		case 8: return "August"; break;
		case 9: return "September"; break;
		case 10: return "October"; break;
		case 11: return "November"; break;
		default: return "December"; break;	
	}
	
}



/*-----------------------------------------------------------------------------
name        :str
description :return a string representation of the Date 
             example: Thu Jan 15 1998
parameters  :/
return      :string
exceptions  :/
algorithm   :Use ltostr to convert integers to strings then concatenate all
             needed strings.
             It would have been easier to use ostrstream but this gave
             unexplanable problems, problems not in compiling but during
             execution in a program the strings were messy.
-----------------------------------------------------------------------------*/
string Date::str() const {
	string lDate;
	string dayofmonth=ltostr(day());
	string years=ltostr(year());
	lDate = str_dow()+ " " + str_month() + " " + dayofmonth + " " + years;
	return lDate;
}



/*-----------------------------------------------------------------------------
name        :operator<<
description :overload << operator for use in cout ... or filestreams
             output will be ex: 15/1/1998
parameters  :ostream& s, const Date& d
return      :ostream&
exceptions  :/
algorithm   :call day() month() and year() of given Date and put everything
             into a ostream and return it
-----------------------------------------------------------------------------*/
ostream& operator<<(ostream& s,const Date& d){
	return s << d.day() <<"/"<<d.month()<<"/"<<d.year();
}



/*-----------------------------------------------------------------------------
name        :operator>>
description :overload >> operator for use in cin ... or filestreams
             input may three numbers seperated by a nonnumber char,
             two numbers seperated by a nonnumber char, -> call Date(day,mont,year)
             one number, -> call Date(day,month)
             empty or 1 nonnumber char -> call Date();
parameters  :istream& s, Date& d
return      :istream& and Date through the reference
exceptions  :/
algorithm   :read a char from istream test if its a number if so put it back
             and read the number else abort reading istream... see code
             below 
-----------------------------------------------------------------------------*/
istream& operator>>(istream& s,Date& d){
	int da,mo,ye;
	int temp;
	temp=s.get();
	while(temp==' '){                       //skip leading blanks
		temp=s.get();
	}
	if( isdigit(temp)||(temp=='-')){
		s.putback(temp);
		s >>da;	                         //read first int
		temp=s.get();
		while( !isdigit(temp) && (temp!='-') && (temp!='\n') ){
			temp=s.get();
		}
		if(temp!='\n'){ 
			if(isdigit(temp)||(temp=='-')){ 
				s.putback(temp);
			}
			s >> mo;                 //read second int
			temp=s.get();
			while( !isdigit(temp) && (temp!='-') && (temp!='\n') ){
				temp=s.get();
			}
			if(temp!='\n'){
				if(isdigit(temp)||(temp=='-')){ 
					s.putback(temp);
				}
				s >> ye;
				d=Date(da,mo,ye);
						//remove blanks followed by CR
				temp=s.get();
				while(temp==' '){
					temp=s.get();
				}
				if(temp!='\n'){
					s.putback(temp);
				}	
			}
			else{     // day and month given
				d=Date(da,mo);   
			}
		}
		else{       // only day given
			d=Date(da);          
		}
		
	}	
	else{        //nothing usefull was given
			d=Date();
	}
	return s;
      
}



/*-----------------------------------------------------------------------------
name        :operator =
description := operator overloading
parameters  :const Date& d
return      :Date&
exceptions  :/
algorithm   :copy JEDay of given Date into local private var JEDay and 
             return Date by using this pointer
-----------------------------------------------------------------------------*/
Date& Date::operator=(const Date& d){
	JEDay=d.JEDay;
	return *this;
}



/*-----------------------------------------------------------------------------
name        :operator +=
description :+= operator overloading for increasing a Date
parameters  :int n
return      :Date&
exceptions  :/
algorithm   :add n to global private local var JEDay and
             return Date by using this pointer
-----------------------------------------------------------------------------*/
Date& Date::operator+=(int n){
	JEDay=JEDay+n;
	return *this;
}



/*-----------------------------------------------------------------------------
name        :operator -=
description :-= operator overloading for decreasing a Date
parameters  :int n
return      :Date&
exceptions  :/
algorithm   :subtract n from global private local var JEDay and
             return Date by using this pointer
-----------------------------------------------------------------------------*/
Date& Date::operator-=(int n){
	JEDay=JEDay-n;
	return *this;
}



/*-----------------------------------------------------------------------------
name        :operator ++
description :++ operator overloading for increasing a Date (prefix)
parameters  :/
return      :Date&
exceptions  :/
algorithm   :add 1 to global private local var JEDay and
             return Date by using this pointer
-----------------------------------------------------------------------------*/
Date& Date::operator++(){
	JEDay=JEDay+1;
	return *this;
}



/*-----------------------------------------------------------------------------
name        :operator ++
description :++ operator overloading for increasing a Date (postfix)
parameters  :int
return      :Date
exceptions  :/
algorithm   :store current Date in 'a' by using this pointer
             add 1 to local private var JEDay and return a
-----------------------------------------------------------------------------*/
Date Date::operator++(int){
	Date a=*this;
	JEDay=JEDay+1;
	return a;
}



/*-----------------------------------------------------------------------------
name        :operator --
description :-- operator overloading for decreasing a Date (prefix)
parameters  :/
return      :Date&
exceptions  :/
algorithm   :subtract 1 from local private var JEDay and
             return Date by using this pointer
-----------------------------------------------------------------------------*/
Date& Date::operator--(){
	JEDay=JEDay-1;
	return *this;
}



/*-----------------------------------------------------------------------------
name        :operator --
description :-- operator overloading for decreasing a Date (postfix)
parameters  :int
return      :Date
exceptions  :/
algorithm   :store current Date in 'a' by using this pointer
             subtract 1 from local private var JEDay and return a
-----------------------------------------------------------------------------*/
Date Date::operator--(int){
	Date a=*this;
	JEDay=JEDay-1;
	return a;
}



/*-----------------------------------------------------------------------------
name        :operator -
description :- operator overloading for decreasing a Date
             example: DateA=DateB-5
parameters  :int n
return      :Date
exceptions  :/
algorithm   :store current Date in 'a' by using this pointer
             subtract n from 'a' and return 'a'
-----------------------------------------------------------------------------*/
Date Date::operator-(int n){
	Date a(*this);
	a.JEDay=JEDay-n;
	return a;
	
} 


/*-----------------------------------------------------------------------------
name        :operator +
description :+ operator overloading for increasing a Date
             example: DateA=DateB+5
parameters  :int n
return      :Date
exceptions  :/
algorithm   :store current Date in 'a' by using this pointer
             add n to 'a' and return 'a'
-----------------------------------------------------------------------------*/
Date Date::operator+(int n){
	Date a(*this);
	a.JEDay=JEDay+n;
	return a;
}



/*-----------------------------------------------------------------------------
name        :operator -
description :- operator overloading for making a subtraction of 2 Dates
             giving back a long. which represents the difference in days.
	     example: 14/3/1997 - 10/3/1997 must give back a long value 4
parameters  :const Date& d
return      :long
exceptions  :/
algorithm   :subtract d.JEDay from local private var JEDay and convert this
             value to a long then return this long
-----------------------------------------------------------------------------*/
long Date::operator-(const Date& d){
	long verschil;
	verschil=long(JEDay-d.JEDay);
	return verschil;
}


/*-----------------------------------------------------------------------------
name        :operator ==
description :== operator overloading for comparing 2 Dates
parameters  :const Date& a
return      :boolean
exceptions  :/
algorithm   :compare the JEDay values of the two Dates in question
-----------------------------------------------------------------------------*/
bool Date::operator==(const Date& a) const {
	return (JEDay == a.JEDay);
}


/*-----------------------------------------------------------------------------
name        :operator !=
description :!= operator overloading for comparing 2 Dates
parameters  :const Date& a
return      :boolean
exceptions  :/
algorithm   :compare the JEDay values of the two Dates in question
-----------------------------------------------------------------------------*/
bool Date::operator!=(const Date& a) const {
	return (JEDay != a.JEDay);
}


/*-----------------------------------------------------------------------------
name        :operator <
description :< operator overloading for comparing 2 Dates
parameters  :const Date& a
return      :boolean
exceptions  :/
algorithm   :compare the JEDay values of the two Dates in question
-----------------------------------------------------------------------------*/
bool Date::operator<(const Date& a) const {
	return (JEDay < a.JEDay);
}


/*-----------------------------------------------------------------------------
name        :operator <=
description :<= operator overloading for comparing 2 Dates
parameters  :const Date& a
return      :boolean
exceptions  :/
algorithm   :compare the JEDay values of the two Dates in question
-----------------------------------------------------------------------------*/
bool Date::operator<=(const Date& a) const {
	return (JEDay <= a.JEDay);
}


/*-----------------------------------------------------------------------------
name        :operator >
description :> operator overloading for comparing 2 Dates
parameters  :const Date& a
return      :boolean
exceptions  :/
algorithm   :compare the JEDay values of the two Dates in question
-----------------------------------------------------------------------------*/
bool Date::operator>(const Date& a) const {
	return (JEDay > a.JEDay);
}


/*-----------------------------------------------------------------------------
name        :operator >=
description :>= operator overloading for comparing 2 Dates
parameters  :const Date& a
return      :boolean
exceptions  :/
algorithm   :compare the JEDay values of the two Dates in question
-----------------------------------------------------------------------------*/
bool Date::operator>=(const Date& a) const {
	return (JEDay >= a.JEDay);
}






/*-----------------------------------------------------------------------------
name        :ConvertToJEDay
description :convert Gregorian day,month,year to a julian Date value
parameters  :int d, int m int y, double& julian
return      :double& julian
exceptions  :/
algorithm   :algorithm copied from book to convert Gregorian Date to Julian
             Date
-----------------------------------------------------------------------------*/
void Date::ConvertToJEDay(int d,int m, int y,double& julian){
	if (m==1 || m==2){
		y=y-1;
		m=m+12;
	};
	int A=int(y/100);
	int B=2-A+int(A/4);
	julian= int(365.25*(y+4716)) + int(30.6001*(m+1))+d+B-1524.5;
}



/*-----------------------------------------------------------------------------
name        :ConvertToCalender
description :convert julian Date value to Gregorion day, month , year
parameters  :double julian, int& d, int& m int& y
return      :int& d, int& m, int& y
exceptions  :/
algorithm   :algorithm copied from book to convert Julian Date to Gregorian
             Date day,month,year...
-----------------------------------------------------------------------------*/
void Date::ConvertToCalendar(double julian,int& d,int& m, int& y)const{
	julian = julian+0.5;
	int Z    = int(julian); // Z is integer part
	double F = julian - int (julian); // F is fractional part
	int A;
	if (Z < 2299161){
		A=Z;
	}
	else{
		int alpha = int((Z-1867216.25)/36524.25);
		A	  = Z + 1 + alpha - int(alpha/4);
	};
	int B = A + 1524;
	int C = int((B-122.1)/365.25);
	int D = int(365.25*C);
	int E = int((B-D)/30.6001);
	d=int(B - D - int(30.6001*E) + F);
	
	if (E<14){
		m= E-1;
	}
	else if(E==14 || E==15){
		m= E-13;
	};
	
	if (m>2){
		y=C-4716;
	}
	else if( m==1 || m==2 ){
		y=C-4715;
	};
}

/*-----------------------------------------------------------------------------
name        :TestInput
description :test if given day,month,year is a correct Gregorian Date
parameters  :int dd, int mm, int year
return      :/
exceptions  :throw exception Invalid_Date with the incorrect d,m,y values
             and an apropriate string
             Added an extra exception for years<1583 because in this year
             a correction had to be made for the julian Date. 
algorithm   :A case and a couple of if's to check the dd,mm and yyyy values
             see below...
-----------------------------------------------------------------------------*/
void Date::TestInput(int dd,int mm ,int year){
	int max;
	switch(mm){
		case 2:                 //february has normally 28 days
					//except in leapyear it has 29 days
			max=28+isleapyear();
			break;
		case 4: case 6: case 9: case 11:  //april,june,september,november have 30 days
			max=30; //maanden met 30 dagen
			break;
		case 1: case 3: case 5: case 7: case 8: case 10: case 12: //other months have 31 days
			max=31;
			break;
		default:
			throw(Invalid_Date(dd,mm,year," month is wrong"));  
	}
	if ( dd<1 ){ //voor 1583 zijn er probz
		throw(Invalid_Date(dd,mm,year," day must be greater than zero "));
	}
	else if(max<dd){
		throw(Invalid_Date(dd,mm,year," day too large"));
	}
	else if(year<1583){
		throw(Invalid_Date(dd,mm,year," year must be greater than 1582"));
	}
}



/*-----------------------------------------------------------------------------
name        :ltostr
description :convert an integer to a string
parameters  :int n
return      :string
exceptions  :/
algorithm   :use modulo 10 and div 10 to convert to string
-----------------------------------------------------------------------------*/
string Date::ltostr(int n)const{
	string nstring;
	if (n==0){
		nstring="0";
	}
	else{
                int onedigit;
		string digitstr;
		while(n!=0){
                        onedigit=n%10;
			n=n/10;
			switch(onedigit){
				case 1:digitstr="1";break;
				case 2:digitstr="2";break;
				case 3:digitstr="3";break;
				case 4:digitstr="4";break;
				case 5:digitstr="5";break;
				case 6:digitstr="6";break;
				case 7:digitstr="7";break;
				case 8:digitstr="8";break;
				case 9:digitstr="9";break;
				default:digitstr="0";
			}
			nstring=digitstr+nstring;
		}
	}
	return nstring;
}

