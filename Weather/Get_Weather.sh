#!/bin/bash

# When called, this script gets weather info from the weather utility and
# writes relevant data to ./Weather.txt
# TODO: Permissions?

# Get user's location from Weather.txt
location = $(head -n 1 ./Weather.txt)



# Gather weather info and output relevant parts.
info = `weather $location`
