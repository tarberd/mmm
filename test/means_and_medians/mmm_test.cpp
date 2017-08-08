#include <catch.hpp>
#include <mmm.h>
#include <vector>
#include <utility>
#include <lemon/list_graph.h>

TEST_CASE("too much m's in one algorithim", "[clk_router]"){
    std::vector<std::pair<float,float>> v;
    
    lemon::ListDigraph g;
    auto fountain = g.addNode();
    lemon::ListDigraph::NodeMap<std::pair<float,float>> node_to_pin(g);
    node_to_pin[fountain] = std::make_pair(0.0f,0.0f);

    clk_router::means_and_medians(std::begin(v), std::end(v), fountain, &g, &node_to_pin);

    REQUIRE(0 == 0);
}
