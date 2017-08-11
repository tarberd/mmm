#include <catch.hpp>
#include <mmm.h>
#include <vector>
#include <utility>

#include <lemon/list_graph.h>
#include <ophidian/geometry/Models.h>

using ophidian::geometry::Point;

typedef lemon::ListDigraph::Node Node;
typedef lemon::ListDigraph::Arc Arc;
typedef lemon::ListDigraph::NodeIt Nodeit;
typedef lemon::ListDigraph::ArcIt ArcIt;

TEST_CASE("Routing one Point", "[clk_router][mmm]"){
    std::vector<Point> v;
   
    v.push_back(Point{2,2});

    lemon::ListDigraph g;
    auto fountain = g.addNode();
    lemon::ListDigraph::NodeMap<Point> node_to_pin(g);
    node_to_pin[fountain] = Point{0,0};

    clk_router::means_and_medians(std::begin(v), std::end(v), fountain, &g, &node_to_pin);

    REQUIRE(node_to_pin[fountain].x() == 0.0 );
    REQUIRE(node_to_pin[fountain].y() == 0.0 );

    int count = 0;
    for(ArcIt it(g); it != lemon::INVALID; ++it){
        Arc arc(it);     
        Node oppositeNode(g.oppositeNode(fountain, arc)) ;
        REQUIRE(node_to_pin[oppositeNode].x() == 2.0 );
        REQUIRE(node_to_pin[oppositeNode].y() == 2.0 );
        count++;
    }
    REQUIRE(count ==1);
}

TEST_CASE("Routing many Points", "[clk_router][mmm]"){
    
}
