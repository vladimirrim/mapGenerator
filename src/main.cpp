#include <ros/ros.h>
#include <nav_msgs/GetMap.h>
#include <stdio.h>
#include "mapGenerator.h"
#include "cxxopts.h"
#include <string>

void save_map(const nav_msgs::OccupancyGrid &map, const std::string &filename) {

    std::string mapdatafile = filename + ".pgm";
    FILE *out = fopen(mapdatafile.c_str(), "w");

    fprintf(out, "P5\n# CREATOR: mapGenerator %.3f m/pix\n%d %d\n255\n",
            map.info.resolution, map.info.width, map.info.height);

    for (unsigned int y = 0; y < map.info.height; y++) {
        for (unsigned int x = 0; x < map.info.width; x++) {
            unsigned int i = x + (map.info.height - y - 1) * map.info.width;

            if (map.data[i] == 0) {//occ [0,0.1)

                fputc(254, out);

            } else if (map.data[i] == +100) { //occ (0.65,1]

                fputc(000, out);

            } else { //occ [0.1,0.65]

                fputc(205, out);

            }
        }
    }

    fclose(out);

    std::string mapmetadatafile = filename + ".yaml";
    FILE *yaml = fopen(mapmetadatafile.c_str(), "w");


    fprintf(yaml,
            "image: %s\nresolution: %f\norigin: [%f, %f, %f]\nnegate: 0\noccupied_thresh: 0.65\nfree_thresh: 0.196\n\n",
            mapdatafile.c_str(), map.info.resolution, map.info.origin.position.x, map.info.origin.position.y, 0.0);

    fclose(yaml);
}

int main(int argc, char **argv) {
    std::string output;
    size_t w, h;
    double resolution;


    try {
        cxxopts::Options options(argv[0], "This program generates random 2d occupancy grid map.");

        options.add_options()
                ("help", "Print available keys.")
                ("o,output", "Output filename.", cxxopts::value<std::string>(output)->default_value("map"))
                ("h,height", "Height of the map in pixels. It must be divisible by 10.",
                 cxxopts::value<size_t>(h)->default_value("600"))
                ("w,width", "Width of the map in pixels. It must be divisible by 10.",
                 cxxopts::value<size_t>(w)->default_value("600"))
                ("r,resolution", "Resolution of the map in metres per pixel.",
                 cxxopts::value<double>(resolution)->default_value("0.01"));


        options.parse(argc, argv);

        if (options.count("help")) {
            std::cout << options.help({""}) << "\n";
            return 0;
        }

    } catch (const cxxopts::OptionException &e) {
        std::cout << e.what() << "\n";
        return -1;
    }

    mapGen::mapGenerator mg(h, w);


    nav_msgs::OccupancyGrid mapGrid;
    nav_msgs::MapMetaData metaData;

    metaData.resolution = resolution;
    metaData.width = w;
    metaData.height = h;

    mapGrid.data = mg.generate_2d_map();
    mapGrid.info = metaData;


    save_map(mapGrid, output);

    return 0;
}