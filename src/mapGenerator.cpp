#include <random>
#include <stack>
#include "mapGenerator.h"

using namespace std;
using namespace mapGen;

mapGenerator::mapGenerator(size_t width, size_t height) : map_width_(width / 10),
                                                          map_height_(height / 10),
                                                          threshold_(min(width, height) / 10),
                                                          real_map_(width, vector<int8_t>(height, 0)),
                                                          algo_map_(map_width_, vector<cell>(map_height_)),
                                                          used_(map_width_, vector<bool>(map_height_, 0)),
                                                          mt(rd()) {}

vector <int8_t> mapGenerator::generate_2d_map() {
    int x = mt() % map_width_;
    int y = mt() % map_height_;

    for (int i = 0; i < 10 * map_width_; i++)
        for (int j = 0; j < 10 * map_height_; j++)
            real_map_[i][j] = 1;

    for (int i = 0; i < map_width_; i++)
        for (int j = 0; j < map_height_; j++)
            used_[i][j] = 0;

    carve_passage(x, y);

    return create_real_map();
}

void mapGenerator::carve_passage(int x, int y) {
    used_[x][y] = 1;
    stack <pair<int, int>> cells;
    vector < pair < pair < int, int >, char >> directions = {
            {{1,  0},  'e'},
            {{0,  -1}, 'n'},
            {{-1, 0},  'w'},
            {{0,  1},  's'}
    };


    cells.push({x, y});

    int ways = 0;
    int nx, ny;


    while (!cells.empty()) {
        ways = 0;
        used_[x][y] = 1;

        random_shuffle(directions.begin(), directions.end());

        for (auto move:directions) {
            nx = x + move.first.first;
            ny = y + move.first.second;

            if (nx >= 0 && nx < map_width_ && ny >= 0 && ny < map_height_ && !used_[nx][ny]) {
                if (move.second == 'e') {
                    algo_map_[x][y].east_way_ = 1;
                    algo_map_[nx][ny].west_way_ = 1;
                }

                if (move.second == 's') {
                    algo_map_[x][y].south_way_ = 1;
                    algo_map_[nx][ny].north_way_ = 1;
                }

                if (move.second == 'w') {
                    algo_map_[x][y].west_way_ = 1;
                    algo_map_[nx][ny].east_way_ = 1;
                }

                if (move.second == 'n') {
                    algo_map_[x][y].north_way_ = 1;
                    algo_map_[nx][ny].south_way_ = 1;
                }

                cells.push({nx, ny});
                ways = 1;
                break;
            }
        }


        x = cells.top().first;
        y = cells.top().second;

        if (!ways) {
            cells.pop();
        }

    }
}

vector <int8_t> mapGenerator::create_real_map() {
    for (int x = 0; x < map_width_; x++) {
        for (int y = 0; y < map_height_; y++) {

            int rx = 10 * x;
            int ry = 10 * y;


            for (int i = 0; i < 4; i++)
                for (int j = 0; j < 4; j++)
                    if (rx + j >= 0 && ry + i >= 0 && rx + j < map_width_ * 10 && ry + i < map_height_ * 10)
                        real_map_[rx + i][ry + j] = 0;


            if (algo_map_[x][y].east_way_) {
                for (int i = 0; i <= 3; i++)
                    for (int j = 4; j <= 9; j++)
                        if (rx + j >= 0 && ry + i >= 0 && rx + j < map_width_ * 10 && ry + i < map_height_ * 10)
                            real_map_[rx + j][ry + i] = 0;
            }


            if (algo_map_[x][y].west_way_) {
                for (int i = 0; i <= 3; i++)
                    for (int j = -6; j <= -1; j++)
                        if (rx + j >= 0 && ry + i >= 0 && rx + j < map_width_ * 10 && ry + i < map_height_ * 10)
                            real_map_[rx + j][ry + i] = 0;
            }


            if (algo_map_[x][y].north_way_) {
                for (int i = -6; i <= -1; i++)
                    for (int j = 0; j <= 3; j++)
                        if (rx + j >= 0 && ry + i >= 0 && rx + j < map_width_ * 10 && ry + i < map_height_ * 10)
                            real_map_[rx + j][ry + i] = 0;
            }


            if (algo_map_[x][y].south_way_) {
                for (int i = 4; i <= 9; i++)
                    for (int j = 0; j <= 3; j++)
                        if (rx + j >= 0 && ry + i >= 0 && rx + j < map_width_ * 10 && ry + i < map_height_ * 10)
                            real_map_[rx + j][ry + i] = 0;
            }

        }
    }

    spawn_random_rectangles(0, 10 * map_width_, 0, 10 * map_height_);

    for (int x = 0; x < 10 * map_width_; x++)
        for (int y = 1; y <= 6; y++) {
            if (y - 1 < map_height_ * 10)
                real_map_[x][y - 1] = 1;
            if (map_height_ * 10 - y >= 0)
                real_map_[x][map_height_ * 10 - y] = 1;

        }

    for (int y = 0; y < 10 * map_height_; y++)
        for (int x = 1; x <= 6; x++) {
            if (x - 1 < map_width_ * 10)
                real_map_[x - 1][y] = 1;
            if (map_width_ * 10 - x >= 0)
                real_map_[map_width_ * 10 - x][y] = 1;

        }

    vector <int8_t> realm;
    for (int x = 0; x < 10 * map_width_; x++) {
        for (int y = 0; y < 10 * map_height_; y++) {
            if (real_map_[x][y]) {
                realm.push_back(100);
            } else {
                realm.push_back(0);
            }
        }
    }
    return realm;
}

void mapGenerator::spawn_random_rectangles(int l, int r, int u, int d) {
    int x1;
    int y1;
    if ((r - l <= threshold_ && d - u <= threshold_)) {
        if ((r - l) > 10 && d - u > 10) {

            x1 = 10 + mt() % (r - l - 10);
            y1 = 10 + mt() % (d - u - 10);

            for (int x = l; x <= l + x1; x++)
                for (int y = u; y <= u + y1; y++)
                    real_map_[x][y] = 0;
        }

    } else if ((r - l) && (d - u)) {
        int x1 = mt() % (r - l);
        int y1 = mt() % (d - u);

        spawn_random_rectangles(l, l + x1, u, u + y1);
        spawn_random_rectangles(l, l + x1, u + y1, d);
        spawn_random_rectangles(l + x1, r, u, u + y1);
        spawn_random_rectangles(l + x1, r, u + y1, d);
    }
}