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

Use catkin_make to compile.
