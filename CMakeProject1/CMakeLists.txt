cmake_minimum_required(VERSION 3.11)
project(CasinoGambler)

set(CMAKE_CXX_STANDARD 11)

include_directories(GamblerLib)
add_library(GamblerLib GamblerLib/Gambler.cpp GamblerLib/Gambler.h "GamblerTest/GamblerTest.cpp")

message("CLion > Visual Studio")