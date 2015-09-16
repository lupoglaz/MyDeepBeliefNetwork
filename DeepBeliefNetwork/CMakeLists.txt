cmake_minimum_required(VERSION 2.8.4)
project(DeepBeliefNetwork)

include_directories(../../../../Programs/eigen ../../../../Projects/Shark ../../../../Programs/boost_1_53_0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    cDBN.cpp
    cDBN.h
    cRBLayer.cpp
    cRBLayer.h
    cTrainingSet.cpp
    cTrainingSet.h
    main.cpp)

add_executable(DeepBeliefNetwork ${SOURCE_FILES})