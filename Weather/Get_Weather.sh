#!/bin/bash

# When called, this script gets weather info from the weather utility and
# writes relevant data to ./Weather.txt
# Weather information must be searched
# NOTE: The first time a location is entered, this script will run slow
# TODO: Permissions?

# If an argument is passed, make it the new location, else use Weather.txt
if [ $0 != ""]; then
  station=$0
  sed -i "1s/.*/$station/" Weather.txt
else
  station=$(tail -n 1 ./Weather.txt)
fi

# Gather weather info
info=`weather -f $station`
currentTemp=`info | egrep -o "Temperature: .{5}"`

# Update Weather.txt
sed -i "2s/.*/$currentTemp/" Weather.txt
