#!/bin/bash

# One-time setup script to correct deprecated links in weather-util
# Must be run w/ sudo
# TODO: Permissions?

# If weather-util isn't an installed package, install it
weatherCheck=`dpkg-query -W --showformat='${Status}\n' weather-util \
| grep "install ok installed"`

if [[ $weatherCheck == "" ]]; then
  sudo apt-get install weather-util
fi

# If version is less than 2.1, replace certain files
version=`dpkg -s weather-util | egrep -o "Version: .{3}" | egrep -o ".{3}$"`
bigVersion=${version:0:1}
littleVersion=${version:2}
if (( "$bigVersion" < "2" )) ||
    (( ("$bigVersion" == "2") && ("$littleVersion" == "0") )); then
  # Replace files containing deprecated links
  cd /usr/share/weather-util
  sudo rm -f stations.gz zones.gz airports.gz
  sudo wget fungi.yuggoth.org/weather/src/weather/stations \
  fungi.yuggoth.org/weather/src/weather/zones \
  fungi.yuggoth.org/weather/src/weather/airports
fi

# TODO: Pray to your personal Higher Power that this script works
