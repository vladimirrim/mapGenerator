#include <vector>
#include <stdint.h>
#include <random>
#include <algorithm>

namespace mapGen {

    class mapGenerator {
    public:
        std::vector <std::int8_t> generate_2d_map();

        mapGenerator(std::size_t width, std::size_t height);

    private:
        struct cell {
            bool west_way_, south_way_, east_way_, north_way_;
        };

        void carve_passage(int x, int y);

        void spawn_random_rectangles(int l, int r, int u, int d);

        std::vector <std::int8_t> create_real_map();

        std::random_device rd;
        std::mt19937 mt;

        std::size_t map_width_;
        std::size_t map_height_;
        std::size_t threshold_;

        std::vector <std::vector<bool>> used_;
        std::vector <std::vector<cell>> algo_map_;
        std::vector <std::vector<std::int8_t>> real_map_;
    };
}