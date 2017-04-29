#include "Clock.h"
#include <ctime>
#include <iostream>
#include <string>
#include <SDL.h>
#include <sstream>
#include <iomanip>


using namespace std;

int hour,minute,sec, month,day,year;
string  TIME;
string AMPM;
string date;


//Constructor for the clock class
Clock::Clock() {

	// ctime utility type set at time of creation
	time_t current = time(0);

	// Structure tm, which holds time values in various aeriables within, 
	// set to the local for the local varient of the time_t vairable before
	struct tm * now = localtime(&current);

	//setting int hour to the values contained in the now structure containing the hour at the time of creation of the structure 
	hour = now->tm_hour;

	//method call to convert the int hour between 12 - 24 hour format
	convertHour(hour);

	// setting the minute variable to the value of the tm_sec variable within the now structure, 
	// which contains the minute of the structures creation
	minute = now->tm_min;

	// setting the sec variable to the second at the creation of the now structure
	sec = now->tm_sec;

	// stringstream used to format the string out put of minute and sec to accomadate the HH:MM:SS format even for one digit values, 
	// ex. 12:02:02
	// declaring the variables of type stringstream 
	stringstream SSmin,SSsec;

	// setting their values formatted to 2 width with filling zeros
	SSmin << setw(2) << setfill('0') << minute;
	SSsec << setw(2) << setfill('0') << sec;

	// converting the stringstring to string for displaying
	string smin = SSmin.str();
	string ssec = SSsec.str();
	
	// setting the string variable time to the value of the combined variables containing the hour, minute, sec and the AM/PM string
	TIME = to_string(hour) + " : " + smin + " : " + ssec + AMPM;
	//delete now;
	//now  = NULL;
	month = now->tm_mon+1;
	day = now->tm_mday;
	year = now->tm_year-100;

	date = to_string(month) + "-" + to_string(day) + "-" + to_string(year);

}

// method for converting 24 hour clock to 12 hour clock
void Clock::convertHour(int nonhour) {

	if (nonhour >= 12) {
		AMPM = " PM";
	}
	else {
		AMPM = " AM";
	}

	if (nonhour > 12) {
		hour -= 12;
	}
	else if(nonhour == 0) {
		hour = 12;
	}
}

// method to update the string TIME to the cuurent time 
void Clock::updateClock()
{
	// time_t variable created set to time at intialization 
	time_t next = time(0);

	// tm structure n set to the localtime variant of the next
	struct tm * n = localtime(&next);

	// comparison of the hour / minute / sec variable to the same variable of the most current time_t structure
	// if passes the TIME string is incorrect and must be updated 
	if (hour < n->tm_hour || minute < n->tm_min || sec < n->tm_sec) {

		// the hour, just resets if not changed
		hour = n->tm_hour;

		// method call for 24 - 12 hour formaat
		convertHour(hour);

		// updates the min, reset if not changed
		minute = n->tm_min;
		
		// updates the sec, resets if not changed
		sec = n->tm_sec;

		// stringstream used to format the string out put of minute and sec to accomadate the HH:MM:SS format even for one digit values, 
		// ex. 12:02:02
		// declaring the variables of type stringstream 
		stringstream SSmin, SSsec;

		// setting their values formatted to 2 width with filling zeros
		SSmin << setw(2) << setfill('0') << minute;
		SSsec << setw(2) << setfill('0') << sec;

		// converting the stringstring to string for displaying
		string smin = SSmin.str();
		string ssec = SSsec.str();

		// setting the string variable time to the value of the combined variables containing the hour, minute, sec and the AM/PM string
		TIME = to_string(hour) + " : " + smin + " : " + ssec + AMPM;
	}


	// used for not doing redunant computations if the hour/minute/sec are already zero, do nothing;
	if (hour == 0 || minute == 0 || sec == 0) {
		//n = NULL;
		//delete n;
		//n = NULL;
		return;
	}

	// if check to the change hour from 23 to 0, will set hour to 0, which will then not be recalled becuase of the if statement above
	if (n->tm_hour == 0) {

		// set hour to 0, then convert hour to 12 hour format
		hour = 0;
		convertHour(hour);

		// convert int to string with 2 width and sets them to smin, ssec
		stringstream SSmin, SSsec;
		SSmin << setw(2) << setfill('0') << minute;
		SSsec << setw(2) << setfill('0') << sec;
		string smin = SSmin.str();
		string ssec = SSsec.str();

		// set string TIME to the values of hour, min, and sec in HH:MM:SS AM/PM format
		TIME = to_string(hour) + " : " + smin + " : " + ssec + AMPM;
	}

	// case to check for minute 59 going to 0 for a new minute
	if (n->tm_min == 0) {
		minute = 0;
		stringstream SSmin, SSsec;
		SSmin << setw(2) << setfill('0') << minute;
		SSsec << setw(2) << setfill('0') << sec;
		string smin = SSmin.str();
		string ssec = SSsec.str();
		TIME = to_string(hour) + " : " + smin + " : " + ssec + AMPM;
	}

	// check to see if 59 going to 0 for a new cycle of sec
	if (n->tm_sec == 0) {
		sec = 0;
		convertHour(hour);
		stringstream SSmin, SSsec;
		SSmin << setw(2) << setfill('0') << minute;
		SSsec << setw(2) << setfill('0') << sec;
		string smin = SSmin.str();
		string ssec = SSsec.str();
		TIME = to_string(hour) + " : " + smin + " : " + ssec + AMPM;
	}
	//delete n;
	//n = NULL;
}

// returns the TIME string
string Clock::getTime()
{
	return TIME;
}

string Clock::getDate() {
	return date;
}
Clock::~Clock()
{
}
