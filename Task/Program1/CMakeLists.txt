cmake_minimum_required (VERSION 2.6) 
 
set (PROJECT Program1) 
 
project (${PROJECT}) 

SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread")

set (HEADERS 
	Process1.h
    Process2.h
    Sender.h)
 
set (SOURCES 
    main.cpp
	Process1.cpp
    Process2.cpp
    Sender.cpp) 
 
add_executable (${PROJECT} ${HEADERS} ${SOURCES})