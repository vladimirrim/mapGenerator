#include "mapGenerator.h"
#include <gtest/gtest.h>
#include <vector>

using namespace mapGen;
using namespace std;

TEST(horizontal_tunnel, short_width) {
    mapGenerator mg(100, 10);
    ASSERT_EQ(mg.generate_2d_map(), mg.generate_2d_map());
}

TEST(horizontal_tunnel, long_width) {
    mapGenerator mg(20000, 10);
    ASSERT_EQ(mg.generate_2d_map(), mg.generate_2d_map());
}

TEST(vertical_tunnel, short_height) {
    mapGenerator mg(10, 100);
    ASSERT_EQ(mg.generate_2d_map(), mg.generate_2d_map());
}

TEST(vertical_tunnel, long_height) {
    mapGenerator mg(10, 20000);
    ASSERT_EQ(mg.generate_2d_map(), mg.generate_2d_map());
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
