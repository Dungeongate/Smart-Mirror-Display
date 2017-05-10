cmake_minimum_required( VERSION 2.8 )
project( Projec1 )
find_package( SDL )
add_executable( Projec1 Source.cpp )
target_link_libraries( Projec1 ${SDL.dll} )
