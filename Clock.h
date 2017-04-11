#pragma once
#include <SDL.h>
#include <iostream>
#include <Windows.h>
#include <string>
using namespace std;

// clock is string with the time in 24h format
// wil be converted to 12 hr.


class Clock
{

public:
	Clock();
	void updateClock();
	string getTime();
	void convertHour(int);
	~Clock();
protected:
	SDL_Renderer* renderer;
	SDL_Window* window;
	SDL_Rect pos;
};

