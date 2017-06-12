#include "mapGenerator.h"
#include <gtest/gtest.h>
#include <vector>

using namespace mapGen;
using namespace std;

TEST(carve_passage_test, one_cell) {
    mapGenerator mg(10, 10);
    vector<int8_t> vec = mg.generate_2d_map();
    vector<int8_t> res(100, 100);
    ASSERT_EQ(res, vec);
}

TEST(carve_passage_test, four_cells) {
    mapGenerator mg(20, 20);
    vector<int8_t> vec = mg.generate_2d_map();
    ASSERT_EQ(0, vec[210]);
    ASSERT_EQ(0, vec[211]);
    ASSERT_EQ(0, vec[212]);
}

TEST(carve_passage_test, eight_cells_horizontal) {
    mapGenerator mg(20, 40);
    vector<int8_t> vec = mg.generate_2d_map();
    ASSERT_EQ(0, vec[420]);
    ASSERT_EQ(0, vec[421]);
    ASSERT_EQ(0, vec[422]);
    ASSERT_EQ(0, vec[423]);
}

TEST(carve_passage_test, eight_cells_vertical) {
    mapGenerator mg(40, 20);
    vector<int8_t> vec = mg.generate_2d_map();
    vector<int8_t> res(400, 100);
    ASSERT_EQ(0, vec[410]);
    ASSERT_EQ(0, vec[411]);
    ASSERT_EQ(0, vec[412]);
    ASSERT_EQ(0, vec[413]);
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
