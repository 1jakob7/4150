cmake_minimum_required(VERSION 3.10)

# set the project name
project(Rumor_Mill)

# add the executable
add_executable(rumor rumor.cpp)

# build for debugging purposes
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_BUILD_TYPE RelWithDebInfo)
