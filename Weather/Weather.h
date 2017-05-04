#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "..\Widget.h"
using namespace std;

class Weather {
public:
    Weather();
    string getCurrentTemp();
    void updateWeather();
    void changeLocation(string); //TODO
    ~Weather();
private:
    string currentTemp;
};
