cmake_minimum_required(VERSION 2.8.3)
project(map_generator)

find_package(catkin REQUIRED COMPONENTS
  nav_msgs
  roscpp
)
catkin_package()


include_directories(include
  ${catkin_INCLUDE_DIRS}
)

set(CMAKE_CXX_FLAGS -std=c++14)


add_executable(mapGenerator src/main.cpp src/mapGenerator.cpp)
target_link_libraries(mapGenerator ${catkin_LIBRARIES})
