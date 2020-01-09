# CMake version
cmake_minimum_required(VERSION 3.0)

# Project name
project(ALFE)

# Define the search path for header files
include_directories(inc)

# Specify the required C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#set(THREADS_PREFER_PTHREAD_FLAG ON)
#find_package(Threads REQUIRED)
#target_link_libraries(my_app Threads::Threads)

# Define the executable
add_executable(exec 
	src/main.cpp src/alfe.cpp src/server.cpp)

target_link_libraries(exec pthread)
target_link_libraries(exec pigpio)
target_link_libraries(exec rt)
