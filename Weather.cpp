#include <iostream>
#include <fstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Weather.h"
using namespace std;

// Constructor
Weather::Weather() {
    // Initialize weather
    // All bash scripts should be chmod x+
    system("./Weather_Setup.sh");
    // Inits currentTemp
    updateWeather();
}

string Weather::getCurrentTemp() {
    return currentTemp;
}

void Weather::updateWeather() {
    // Call update script (should be chmod +x)
    system("./Get_Weather.sh");
    // Open Weather.txt in read mode
    ifstream f ("Weather.txt");

    // Read first line of file
    string updatedTemp, dummy;
    getline(f, dummy);
    getline(f, updatedTemp);

    updatedTemp.append(" °F");

    currentTemp = updatedTemp;
    f.close();
}

void Weather::changeLocation(string newLocation) {
    //TODO
}

Weather::~Weather() {
}
