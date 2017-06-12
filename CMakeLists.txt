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

if (CATKIN_ENABLE_TESTING)

include_directories(include 
  ${GTEST_INCLUDE_DIRS}
) 

catkin_add_gtest(map_generator_unit_tests tests/unit_tests.cpp src/mapGenerator.cpp)
target_link_libraries(map_generator_unit_tests ${catkin_LIBRARIES})

catkin_add_gtest(map_generator_functional_tests tests/functional_tests.cpp src/mapGenerator.cpp)
target_link_libraries(map_generator_functional_tests ${catkin_LIBRARIES})

endif()
