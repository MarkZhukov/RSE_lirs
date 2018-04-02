cmake_minimum_required(VERSION 3.10)
project(RSE_lirs)

#find_package(OpenCV REQUIRED) # after project()

#set(CMAKE_CXX_STANDARD 11)

#add_executable(RSE_lirs main.cpp)


#At the end
#include_directories(${OpenCV_INCLUDE_DIRS})
#target_link_libraries(opencv ${OpenCV_LIBS})
find_package(OpenCV REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES main.cpp cstyle.cpp)
add_executable(RSE_lirs ${SOURCE_FILES})

include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(RSE_lirs ${OpenCV_LIBS})