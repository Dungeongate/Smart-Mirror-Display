#!/bin/bash

# When called, this script gets weather info from the weather utility and
# writes relevant data to ./Weather.txt
# Weather information must be searched
# NOTE: The first time a location is entered, this script will run slow
# TODO: Permissions?

# If an argument is passed, make it the new location, else use Weather.txt

station=$(head -n 1 ./Weather.txt)

# Gather weather info
#info=`weather -f $station`
currentTemp=`weather -f $station | egrep -o "Temperature: .{5}"`

# Update Weather.txt
sed -i '2s/.*/'"$currentTemp"'/' Weather.txt
