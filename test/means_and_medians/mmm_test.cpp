#include <catch.hpp>

#include <mmm.h>

TEST_CASE("too much m's in one algorithim", [clk_router]){
    std::vector<std::pair<float,float>> v;
    REQUIRE( means&medians(v) == {0.0f,0.0f} )
}
