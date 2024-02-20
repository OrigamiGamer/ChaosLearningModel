cmake_minimum_required(VERSION 3.7.5)
project(ChaosLearningModel VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

include_directories(Neuron)

add_executable(ChaosLearningModel main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
