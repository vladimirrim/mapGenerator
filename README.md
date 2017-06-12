# map_generator

This program generates random 2d occupancy grid maps.

# Algorithm

It creates random maze using Recursive Backtracking algorithm and spawns random rectangles on top of it.

# Interface

--help - Print interface.

-w, --weight - Weight of the map in pixels. It must be divisible by 10.

-h, --height - Height of the map in pixels. It must me divisible by 10.

-r, --resolution - Resolution of the map in metres per pixel.

-o, --output - Output filename.

# Compilation

Use catkin_make to compile."catkin_make" must be invoked in the root of catkin workspace.You need to copy all files in src/map_generator folder.

# Example

mapGenerator is located in devel/lib/map_generator/

```
./mapGenerator -h 1000 -w 1000 -o map -r 0.01
```

# Output

Program creates .yaml and .pgm files.

.yaml example:

    image: map.pgm
    resolution: 0.010000 
    origin: [0.000000, 0.000000, 0.000000]
    negate: 0
    occupied_thresh: 0.65
    free_thresh: 0.196

.pgm example:
![Map example](https://user-images.githubusercontent.com/22059171/27036564-d94fa4a8-4f8d-11e7-9a9a-3b48231028bb.jpg)



# Testing

* gtest libraries required

Use
```
catkin_make run_tests_map_generator_gtest_map_generator_unit_tests 
```
in the root of workspace to run unit tests and
```
catkin_make run_tests_map_generator_gtest_map_generator_functional_tests 
```
to run functional tests.
