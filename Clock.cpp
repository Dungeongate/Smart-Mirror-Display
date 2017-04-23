#include "Clock.h"
#include <ctime>
#include <iostream>
#include <string>
#include <SDL.h>
#include <sstream>
#include <iomanip>


using namespace std;

int hour, min, sec;
string  TIME;
string AMPM;

Clock::Clock() {

	time_t current = time(0);
	struct tm * now = localtime(&current);
	hour = now->tm_hour;
	convertHour(hour);
	min = now->tm_min;
	sec = now->tm_sec;
	stringstream SSmin,SSsec;
	SSmin << setw(2) << setfill('0') << min;
	SSsec << setw(2) << setfill('0') << sec;
	string smin = SSmin.str();
	string ssec = SSsec.str();
	TIME = to_string(hour) + " : " + smin + " : " + ssec + AMPM;

}

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

void Clock::updateClock()
{
	time_t next = time(0);
	struct tm * n = localtime(&next);

	if (hour < n->tm_hour) {
		hour = n->tm_hour;
		convertHour(hour);
		stringstream SSmin, SSsec;
		SSmin << setw(2) << setfill('0') << min;
		SSsec << setw(2) << setfill('0') << sec;
		string smin = SSmin.str();
		string ssec = SSsec.str();
		TIME = to_string(hour) + " : " + smin + " : " + ssec + AMPM;
	}

	if (n->tm_hour == 0) {
		hour = 0;
		convertHour(hour);
		stringstream SSmin, SSsec;
		SSmin << setw(2) << setfill('0') << min;
		SSsec << setw(2) << setfill('0') << sec;
		string smin = SSmin.str();
		string ssec = SSsec.str();
		TIME = to_string(hour) + " : " + smin + " : " + ssec + AMPM;
	}

	if (min < n->tm_min) {
		min = n->tm_min;
		stringstream SSmin, SSsec;
		SSmin << setw(2) << setfill('0') << min;
		SSsec << setw(2) << setfill('0') << sec;
		string smin = SSmin.str();
		string ssec = SSsec.str();
		TIME = to_string(hour) + " : " + smin + " : " + ssec + AMPM;
	}

	if (n->tm_min == 0) {
		min = 0;
		stringstream SSmin, SSsec;
		SSmin << setw(2) << setfill('0') << min;
		SSsec << setw(2) << setfill('0') << sec;
		string smin = SSmin.str();
		string ssec = SSsec.str();
		TIME = to_string(hour) + " : " + smin + " : " + ssec + AMPM;
	}

	if (sec < n->tm_sec) {
		sec = n->tm_sec;
		convertHour(hour);
		stringstream SSmin, SSsec;
		SSmin << setw(2) << setfill('0') << min;
		SSsec << setw(2) << setfill('0') << sec;
		string smin = SSmin.str();
		string ssec = SSsec.str();
		TIME = to_string(hour) + " : " + smin + " : " + ssec + AMPM;
	}
	if (hour == 0 || min == 0 || sec == 0) {
		return;
	}
	if (n->tm_sec == 0) {
		sec = 0;
		convertHour(hour);
		stringstream SSmin, SSsec;
		SSmin << setw(2) << setfill('0') << min;
		SSsec << setw(2) << setfill('0') << sec;
		string smin = SSmin.str();
		string ssec = SSsec.str();
		TIME = to_string(hour) + " : " + smin + " : " + ssec + AMPM;

	}
}

string Clock::getTime()
{
	return TIME;
}




Clock::~Clock()
{
}
