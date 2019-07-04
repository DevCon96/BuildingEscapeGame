cmake_minimum_required(VERSION 3.13)
project(FBullCowGame)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(FBullCowGame
        FBullCowGame.cpp
        FBullCowGame.h
        main.cpp)
