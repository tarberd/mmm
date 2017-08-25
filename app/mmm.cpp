#include <iostream>
#include <fstream>
#include <random>
#include <chrono>
#include <vector>
#include <string>
#include <utility>

#include <mmm.h>

#include <lemon/list_graph.h>
#include <ophidian/geometry/Models.h>

using ophidian::geometry::Point;

using Node = lemon::ListDigraph::Node;
using Arc = lemon::ListDigraph::Arc;
using NodeIt = lemon::ListDigraph::NodeIt;
using ArcIt = lemon::ListDigraph::ArcIt;


int main(){

    std::vector<Point> v;
  
    
    std::ifstream myfile("input.txt");

    if(!myfile.is_open())
    {
        std::cout << "no input.txt" << std::endl;
    }

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
    std::chrono::duration<double> elapsed_seconds = end-start;

    std::cout << "delta t: " << elapsed_seconds.count() << std::endl;

    return 0;
}
