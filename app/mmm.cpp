#include <iostream>
#include <fstream>
#include <random>
#include <chrono>
#include <vector>
#include <string>
#include <utility>
#include <cstdlib>

#include <mmm.h>

#include <lemon/list_graph.h>
#include <ophidian/geometry/Models.h>

using ophidian::geometry::Point;

using Node = lemon::ListDigraph::Node;
using Arc = lemon::ListDigraph::Arc;
using NodeIt = lemon::ListDigraph::NodeIt;
using ArcIt = lemon::ListDigraph::ArcIt;

double mahatan_distance(const Point & a, const Point & b){
    return std::abs(a.x() - b.x()) + std::abs(a.y() - b.y());
}

int main(int argc, char* argv[]){

    if(argc != 2){
        std::cout << "usage: ./mmm <file>" << std::endl;
        return -1;
    }

    
    std::ifstream myfile(argv[1]);

    if(!myfile.is_open())
    {
        std::cout << "no valid <file>" << std::endl;
        return -1;
    }

    std::vector<Point> v;
    
    int x,y;
    while(myfile >> x >> y){
        v.push_back(Point{x,y});
    }

    lemon::ListDigraph g;
    auto fountain = g.addNode();
    lemon::ListDigraph::NodeMap<Point> node_to_point(g);
    node_to_point[fountain] = Point{0,0};
    
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();

    clk_router::means_and_medians(std::begin(v), std::end(v), fountain, &g, &node_to_point);

    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;

    std::cout << elapsed_seconds.count() << " ";

    auto distance = 0.0;
    for(ArcIt it(g); it != lemon::INVALID; ++it){
        Arc arc(it);
        auto father = g.source(arc);
        auto son = g.target(arc);
        //std::cout << node_to_point[father].x() << " " << node_to_point[father].y() << std::endl;
        //std::cout << node_to_point[son].x() << " " << node_to_point[son].y() << std::endl;
        
        distance += mahatan_distance(node_to_point[father], node_to_point[son]);
        //std::cout << distance << std::endl;
    }
    std::cout << distance << std::endl;

    return 0;
}
