#include <catch.hpp>
#include <mmm.h>
#include <vector>
#include <utility>

TEST_CASE("too much m's in one algorithim", "[clk_router]"){
    std::vector<std::pair<float,float>> v;
    
    clk_router::means_medians_x(std::begin(v), std::end(v), std::make_pair(0.0f, 0.0f));

    REQUIRE( 0 == 0);
}
