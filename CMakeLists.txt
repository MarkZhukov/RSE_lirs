cmake_minimum_required(VERSION 3.10)
project(RSE_lirs)

#find_package(OpenCV REQUIRED) # after project()

#set(CMAKE_CXX_STANDARD 11)

#add_executable(RSE_lirs main.cpp)


#At the end
#include_directories(${OpenCV_INCLUDE_DIRS})
#target_link_libraries(opencv ${OpenCV_LIBS})
find_package(OpenCV REQUIRED)
find_package(PCL 1.8 REQUIRED COMPONENTS common io)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES src/edges.cpp src/cstyle.cpp src/pcl/pcl.cpp src/calibration/stereo/calib_from_yaml.cpp src/grid.cpp)
add_executable(RSE_lirs ${SOURCE_FILES})



include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})
target_link_libraries(RSE_lirs ${PCL_COMMON_LIBRARIES} ${PCL_IO_LIBRARIES})


include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(RSE_lirs ${OpenCV_LIBS})