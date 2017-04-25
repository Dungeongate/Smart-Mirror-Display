#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "WeatherWidget.h"
using namespace std;

// Constructor
Weather::Weather() {
    // Initialize weather
    // All bash scripts should be chmod x+
    system("./Weather/Weather_Setup.sh");
    // Inits currentTemp
    updateWeather();
}

string Weather::getCurrentTemp() {
    return currentTemp;
}

Weather::updateWeather() {
    // Call update script (should be chmod +x)
    system("./Weather/Get_Weather.sh");
    // Open Weather.txt in read mode
    ifstream f ("./Weather/Weather.txt");

    // Read first line of file
    string updatedTemp;
    f >> updatedTemp;
    updatedTemp.append(" °F");

    currentTemp = updatedTemp;
    f.close();
}

Weather::changeLocation(string newLocation) {
    //TODO
}

Weather::~Weather() {
}
