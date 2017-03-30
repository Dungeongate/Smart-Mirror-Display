#!/bin/bash
""" This file gets the current local weather conditions from package
    'weather-util' and writes weather information to ./Weather.txt
    Needs to be run with sudo if weather-util is not installed.

    Takes as input the user's local location stored in:
"""
location = $0

# If weather-util isn't an installed package, install it
status = `dpkg -l | grep weather-util`
if [[ $status != *"weather-util"* ]]; then
  sudo apt-get install weather-util
fi

# Gather weather info and output relevant parts.
info = `weather $location`
