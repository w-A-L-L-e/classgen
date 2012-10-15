/*=============================================================================
author        :Walter Schreppers
filename      :Time.cpp
created       :/
modified      :14/01/1998
version       :13
copyright     :Walter Schreppers
bugreport(log):/
=============================================================================*/

#include "Time.h"



/*-----------------------------------------------------------------------------
name        :Time
description :constructor
parameters  :/
return      :Time
exceptions  :calls TestInput this may throw an exception
algorithm   :use <time.h> to get current hour,min and second and then test values
             with TestInput if it's satisfactory ConvertToSeconds is called
             else an exception is throwed by TestInput.
-----------------------------------------------------------------------------*/
Time::Time(){
	time_t timer = time (0);
	struct tm *tblock = localtime(&timer);
	int h = tblock->tm_hour;
	int m = tblock->tm_min;
	int s = tblock->tm_sec;	
	TestInput(h,m,s);
	ConvertToSeconds(h,m,s,seconds);
	overflow=0;
}



/*-----------------------------------------------------------------------------
name        :Time
description :constructor
parameters  :int s
return      :Time
exceptions  :calls TestInput this may throw an exception
algorithm   :s=sec ,use <time.h> to get current hour,min and then test values 
             with TestInput if it's satisfactory ConvertToSeconds is called
             else an exception is throwed by TestInput.
-----------------------------------------------------------------------------*/
Time::Time(int s){
	time_t timer = time (0);
	struct tm *tblock = localtime(&timer);
	int h = tblock->tm_hour;	
	int m = tblock->tm_min;
	TestInput(h,m,s);
	ConvertToSeconds(h,m,s,seconds);
	overflow=0;
}



/*-----------------------------------------------------------------------------
name        :Time
description :constructor
parameters  :int m, int s
return      :Time
exceptions  :calls TestInput this may throw an exception
algorithm   :m=min,s=sec ,use <time.h> to get current hour then test values 
             with TestInput if it's satisfactory ConvertToSeconds is called
             else an exception is throwed by TestInput.
-----------------------------------------------------------------------------*/
Time::Time(int m , int s){
	time_t timer = time (0);
	struct tm *tblock = localtime(&timer);
	int h = tblock->tm_hour;
	TestInput(h,m,s);
	ConvertToSeconds(h,m,s,seconds);
	overflow=0;
}



/*-----------------------------------------------------------------------------
name        :Time
description :constructor
parameters  :int h,int m, int s
return      :Time
exceptions  :calls TestInput this may throw an exception
algorithm   :h=hour,m=minute,y=year then test values
             with TestInput if it's satisfactory ConvertToSeconds is called
             else an exception is throwed by TestInput.
-----------------------------------------------------------------------------*/
Time::Time(int h, int m, int s){
	TestInput(h,m,s);
	ConvertToSeconds(h,m,s,seconds);
	overflow=0;
}



/*-----------------------------------------------------------------------------
name        :Time
description :copy constructor
parameters  :const Time&
return      :Time
exceptions  :/
algorithm   :Test if given Time not equal to 'this' pointer 
             -> to prevent a copy into itself
             Use private local var seconds and overflow of given time t 
             to copy into new time.
-----------------------------------------------------------------------------*/
Time::Time(const Time& t){
	if(&t != this){
		seconds=t.seconds;
		overflow=t.overflow;
	}
}



/*-----------------------------------------------------------------------------
name        :sec
description :give seconds of time as int
parameters  :/
return      :int
exceptions  :/
algorithm   :call ConvertToTime and return the sec value
-----------------------------------------------------------------------------*/
int Time::sec() const{
	int h,m,s;
	ConvertToTime(seconds,h,m,s);
	return s;
}



/*-----------------------------------------------------------------------------
name        :min
description :give minutes of time as int
parameters  :/
return      :int
exceptions  :/
algorithm   :call ConvertToTime and return the min value
-----------------------------------------------------------------------------*/
int Time::min() const{
	int h,m,s;
	ConvertToTime(seconds,h,m,s);
	return m;
}



/*-----------------------------------------------------------------------------
name        :hour
description :give hours of time as int
parameters  :/
return      :int
exceptions  :/
algorithm   :call ConvertToTime and return the hour value
-----------------------------------------------------------------------------*/
int Time::hour() const{
	int h,m,s;
	ConvertToTime(seconds,h,m,s);
	return h;
}



/*-----------------------------------------------------------------------------
name        :str
description :return a string representation of the time 
             example: 23:56:20
parameters  :/
return      :string
exceptions  :/
algorithm   :Use ltostr to convert integers to strings and 'ad' the private member
             function for nice output then concatenate all needed strings.
             It would have been easier to use ostrstream but this gave
             unexplanable problems, problems not in compiling but during
             execution in a program the strings were messy.
-----------------------------------------------------------------------------*/
string Time::str() const{
	string hours=ltostr(hour());
	string mins=ltostr(min());
	string secs=ltostr(sec());
	return ad(hour())+hours+":"+ad(min())+mins+":"+ad(sec())+secs; 
}



/*-----------------------------------------------------------------------------
name        :operator<<
description :overload << operator for use in cout ... or filestreams
             output will be for example: 23:30:40
parameters  :ostream& s, const Time& t
return      :ostream&
exceptions  :/
algorithm   :call hour(), min(), sec() of given time 
	     also use the ad private member function for nice output
             and put everything into a ostream and return it
-----------------------------------------------------------------------------*/
ostream& operator<<(ostream& s,const Time& t){
	return s << t.ad(t.hour()) << t.hour() << ":" << t.ad(t.min()) << t.min() <<":"<<t.ad(t.sec())<<t.sec();
}



/*-----------------------------------------------------------------------------
name        :operator>>
description :overload >> operator for use in cin ... or filestreams
             input may three numbers seperated by a nonnumber char,
             two numbers seperated by a nonnumber char, -> call Time(hour,min,sec)
             one number, -> call Time(min,sec);
             empty or 1 nonnumber char -> call Time();
parameters  :istream& s, Time& t
return      :istream& and Time t through the reference
exceptions  :/
algorithm   :read a char from istream test if its a number if so put it back
             and read the number else abort reading istream... see code
             below 
-----------------------------------------------------------------------------*/
istream& operator>>(istream& s,Time& t){
	int a,b,c;
	int temp;
	temp=s.get();
	while(temp==' '){ 		//remove leading blanks
		temp=s.get();
	}
	if( isdigit(temp)||(temp=='-')){
		s.putback(temp);
		s >>a;			//read first int
		temp=s.get();
		while( !isdigit(temp) && (temp!='-') && (temp!='\n') ){
			temp=s.get();
		}
		if(temp!='\n'){ 
			if(isdigit(temp)||(temp=='-')){ 
				s.putback(temp);
			}
			s >> b;		//read second int
			temp=s.get();
			while( !isdigit(temp) && (temp!='-') && (temp!='\n') ){
				temp=s.get();
			}
			if(temp!='\n'){
				if(isdigit(temp)||(temp=='-')){ 
					s.putback(temp);
				}
				s >> c;		//read last int
				t=Time(a,b,c);	//create t Time
				//dump blanks and CR
				temp=s.get();
				while(temp==' '){
					temp=s.get();
				}
				if(temp!='\n'){
					s.putback(temp);
				}	
			}
			else{ //seconds and minutes are given a=min b=sec
				t=Time(a,b);
			}
		}
		else{ //only seconds given a=sec
			t=Time(a);
		}
		
	}	
	else{	//nothing given
			t=Time();
	}
	return s;
}



/*-----------------------------------------------------------------------------
name        :operator =
description := operator overloading
parameters  :const Time& t
return      :Time&
exceptions  :/
algorithm   :copy seconds and overflow values of given Time 
             into the local private vars seconds and overflow
             return Time by using this pointer
-----------------------------------------------------------------------------*/
Time& Time::operator=(const Time& t){
	seconds=t.seconds;
	overflow=t.overflow;
	return *this;
}



/*-----------------------------------------------------------------------------
name        :operator +=
description :+= operator overloading for increasing a time
parameters  :int n
return      :Time&
exceptions  :/
algorithm   :-add n to global private local var seconds 
             -call TestOverflow which will set the overflow bit to the
              right value and 
             -add a number of times 86400 to the time and then do a modulo
              86400 to keep time positive and circular
             -return time by using this pointer
-----------------------------------------------------------------------------*/
Time& Time::operator+=(int n){
	seconds=seconds+n;
	TestOverflow(seconds);
	seconds=(seconds+( ((abs(seconds) /86400) +1) *86400) ) %86400;
	return *this;
}



/*-----------------------------------------------------------------------------
name        :operator -=
description :-= operator overloading for increasing a time
parameters  :int n
return      :Time&
exceptions  :/
algorithm   :-subtract n from global private local var seconds 
             -call TestOverflow which will set the overflow bit to the
              right value and 
             -add a number of times 86400 to the time and then do a modulo
              86400 to keep time positive and circular
             -return time by using this pointer
-----------------------------------------------------------------------------*/
Time& Time::operator-=(int n){
	seconds=seconds-n;
	TestOverflow(seconds);
	seconds=(seconds+( ((abs(seconds) /86400) +1) *86400) ) %86400;
	return *this;
}



/*-----------------------------------------------------------------------------
name        :operator ++
description :++ operator overloading for increasing a time (prefix)
parameters  :/
return      :Time&
exceptions  :/
algorithm   :-add 1 to global private local var seconds 
             -call TestOverflow which will set the overflow bit to the
              right value and 
             -do a modulo 86400 on seconds so that 24:00:00 -> 00:00:00
             -return time by using this pointer
-----------------------------------------------------------------------------*/
Time& Time::operator++(){
	seconds=seconds+1;
	TestOverflow(seconds);
	seconds=seconds%86400;
	return *this;
}



/*-----------------------------------------------------------------------------
name        :operator ++
description :++ operator overloading for increasing a time (postfix)
parameters  :int 
return      :Time
exceptions  :/
algorithm   :-store current time in 'a' by using this pointer
             -add 1 to global private local var seconds 
             -call TestOverflow which will set the overflow bit to the
              right value and 
             -do a modulo 86400 on seconds so that 24:00:00 -> 00:00:00
             -return 'a'
-----------------------------------------------------------------------------*/
Time Time::operator++(int){
	Time a=*this;
	seconds=seconds+1;
	TestOverflow(seconds);
	seconds=seconds%86400;
	return a;
}


/*-----------------------------------------------------------------------------
name        :operator --
description :-- operator overloading for decreasing a time (prefix)
parameters  :/
return      :Time&
exceptions  :/
algorithm   :-subtract 1 from global private local var seconds 
             -call TestOverflow which will set the overflow bit to the
              right value and 
             -add a number of times 86400 to the time and then do a modulo
              86400 to keep time positive and circular
             -return time by using this pointer
-----------------------------------------------------------------------------*/
Time& Time::operator--(){
	seconds=seconds-1;
	TestOverflow(seconds);
	seconds=(seconds+( ((abs(seconds) /86400) +1) *86400) ) %86400;
	return *this;
}



/*-----------------------------------------------------------------------------
name        :operator --
description :-- operator overloading for decreasing a time (postfix)
parameters  :/
return      :Time
exceptions  :/
algorithm   :-store current Time into 'a' with this pointer
             -subtract 1 from global private local var seconds 
             -call TestOverflow which will set the overflow bit to the
              right value and 
             -add a number of times 86400 to the time and then do a modulo
              86400 to keep time positive and circular
             -return 'a'
-----------------------------------------------------------------------------*/
Time Time::operator--(int){
	Time a=*this;
	seconds=seconds-1;
	TestOverflow(seconds);
	seconds=(seconds+( ((abs(seconds) /86400) +1) *86400) ) %86400;
	return a;
}



/*-----------------------------------------------------------------------------
name        :operator -
description :- operator overloading for decreasing a time
             example TimeA=TimeB-5;  
parameters  :/
return      :Time
exceptions  :/
algorithm   :-store current Time into 'a' with this pointer
             -call -= operator for 'a'
             -return a;
-----------------------------------------------------------------------------*/
Time Time::operator-(int n){
	Time a(*this);
	a-=n;
	return a;
	
} 



/*-----------------------------------------------------------------------------
name        :operator +
description :+ operator overloading for increasing a time
             example TimeA=TimeB+5;  
parameters  :/
return      :Time
exceptions  :/
algorithm   :-store current Time into 'a' with this pointer
             -call += operator for 'a'
             -return a;
-----------------------------------------------------------------------------*/
Time Time::operator+(int n){
	Time a(*this);
	a+=n;
	return a;
}



/*-----------------------------------------------------------------------------
name        :operator -
description :- operator overloading to subtract two times from eachother
parameters  :const Time& t
return      :long
exceptions  :/
algorithm   :subtract t.seconds from local private var seconds and return
             this value as a long
-----------------------------------------------------------------------------*/
long Time::operator-(const Time& t){
	long verschil=seconds-t.seconds;
	return verschil;
}



/*-----------------------------------------------------------------------------
name        :operator ==
description :== operator overloading for comparing 2 times
parameters  :const Time& a
return      :boolean
exceptions  :/
algorithm   :compare the private 'second' values of the two times in question
-----------------------------------------------------------------------------*/
bool Time::operator==(const Time& a) const {
	return (seconds == a.seconds);
}



/*-----------------------------------------------------------------------------
name        :operator !=
description :!= operator overloading for comparing 2 times
parameters  :const Time& a
return      :boolean
exceptions  :/
algorithm   :compare the private 'second' values of the two times in question
-----------------------------------------------------------------------------*/
bool Time::operator!=(const Time& a) const {
	return (seconds != a.seconds);
}



/*-----------------------------------------------------------------------------
name        :operator <
description :< operator overloading for comparing 2 times
parameters  :const Time& a
return      :boolean
exceptions  :/
algorithm   :compare the private 'second' values of the two times in question
-----------------------------------------------------------------------------*/
bool Time::operator<(const Time& a) const {
	return (seconds < a.seconds);
}



/*-----------------------------------------------------------------------------
name        :operator <=
description :<= operator overloading for comparing 2 times
parameters  :const Time& a
return      :boolean
exceptions  :/
algorithm   :compare the private 'second' values of the two times in question
-----------------------------------------------------------------------------*/
bool Time::operator<=(const Time& a) const {
	return (seconds <= a.seconds);
}



/*-----------------------------------------------------------------------------
name        :operator >
description :> operator overloading for comparing 2 times
parameters  :const Time& a
return      :boolean
exceptions  :/
algorithm   :compare the private 'second' values of the two times in question
-----------------------------------------------------------------------------*/
bool Time::operator>(const Time& a) const {
	return (seconds > a.seconds);
}



/*-----------------------------------------------------------------------------
name        :operator >=
description :>= operator overloading for comparing 2 times
parameters  :const Time& a
return      :boolean
exceptions  :/
algorithm   :compare the private 'second' values of the two times in question
-----------------------------------------------------------------------------*/
bool Time::operator>=(const Time& a) const {
	return (seconds >= a.seconds);
}



/*-----------------------------------------------------------------------------
name        :getoverflow
description :this will return an int value representing the number of days
             that can be added to a date if one uses time's and date's together
parameters  :/
return      :integer
exceptions  :/
algorithm   :return the private local var overflow
-----------------------------------------------------------------------------*/
int Time::getoverflow() const{
	return overflow;
}



/*-----------------------------------------------------------------------------
name        :resetoverflow
description :acknoledge you have processed the overflow setting it to 0
parameters  :/
return      :/
exceptions  :/
algorithm   :set the private local var overflow to 0
-----------------------------------------------------------------------------*/
void Time::resetoverflow(){
	overflow=0;
}



/*-----------------------------------------------------------------------------
name        :ConvertToSeconds
description :convert hours,minutes,seconds of time to one large long called seconds
parameters  :int h, int m, int s, long& seconds
return      :seconds through a reference
exceptions  :/
algorithm   :a minute has 60 seconds and an hour has 3600 seconds
             so the number of seconds in a number of hours, minutes and seconds
             is seconds+minutes*60+hours*3600
-----------------------------------------------------------------------------*/
void Time::ConvertToSeconds(int h,int m, int s,long& seconds){
	h=h%24;
	seconds=s+(m*60)+(h*3600);
}



/*-----------------------------------------------------------------------------
name        :ConvertToTime
description :convert the internal representation (seconds) to hours,minutes
             and seconds
parameters  :int& h, int& m, int& s
return      :hours minutes and seconds through references
exceptions  :/
algorithm   :see below
-----------------------------------------------------------------------------*/
void Time::ConvertToTime(long seconds,int& h,int& m, int& s) const{
	s=seconds%60;
	m=(seconds/60)%60;
	h=(seconds/3600)%24; 
}



/*-----------------------------------------------------------------------------
name        :TestInput
description :test if input is a correct time
parameters  :int hh, int mm, int ss
return      :/
exceptions  :throws exception Invalid_Time if necessary
algorithm   :test if hours are between 0 and 23
                     minutes are between 0 and 59
                     seconds are between 0 and 59
             if not throw Invalid_Time 
-----------------------------------------------------------------------------*/
void Time::TestInput(int hh,int mm ,int ss){
	if ( hh<0 || mm<0 || ss<00 || hh>23 || mm>59 || ss>59 ){
		throw(Invalid_Time(hh,mm,ss));
	}
}



/*-----------------------------------------------------------------------------
name        :TestOverflow
description :if time went under 0 or over 23:59:59 calculate the number of
             days to be added (or subtracted then value overflow is negative)
parameters  :long s
return      :/
exceptions  :/
algorithm   :test if s<0 or >=86400
             ...86400=24*3600 --> one day
 	      if so calculate the overflow days
              if s is positive then the number of overflow days is
              the number of times that 86400 goes into s
              if s is negative the number of underflow days is
                 the number of times that 86400 goes into s
                 +1 extra day
-----------------------------------------------------------------------------*/

void Time::TestOverflow(long s){
	if(s<0){	//time went under 00:00:00
		overflow=(s/86400)-1; //watch out now s/86400 is <=0 !
	}
	else if(s>=86400){	//time went above 23:59:59
		overflow=s/86400;
	}
}



/*-----------------------------------------------------------------------------
name        :ad
description :this function will return a string 0 for numbers 1 through 9
parameters  :int n
return      :string
exceptions  :/
algorithm   :return "0" if number given<10 return "" if number >=10
             negative numbers dont get inserted into a time so we dont
             have to test for neg n's
-----------------------------------------------------------------------------*/
string Time::ad(int n)const {		//deze functie zorgt dat output bv 04:08:01
					//is in plaats van 4:8:1
	if (n<10){
		return "0";
	}
	else{
		return "";
	} 	
}



/*-----------------------------------------------------------------------------
name        :abs
description :return absolute value of a long
parameters  :long n
return      :long
exceptions  :/
algorithm   :if long is negative subtract it from zero giving a positive
             number
-----------------------------------------------------------------------------*/
long Time::abs(long n) const{
	if (n<0){
		n = 0-n;
	}
	return n;
}


/*-----------------------------------------------------------------------------
name        :ltostr
description :convert an integer to a string
parameters  :int n
return      :string
exceptions  :/
algorithm   :use modulo 10 and div 10 to convert to string
-----------------------------------------------------------------------------*/
string Time::ltostr(int n)const{
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
