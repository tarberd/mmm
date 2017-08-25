#ifndef MMM_H
#define MMM_H

#include <algorithm>
#include <numeric>
#include <iterator>

#include <lemon/list_graph.h>
#include <ophidian/geometry/Models.h>

using lemon::ListDigraph;
using ophidian::geometry::Point;

namespace clk_router {
    template<class RandomIt>
    Point region_mean(RandomIt begin, RandomIt end){
        auto mean = std::accumulate(begin,end, Point{0,0},
                [](const Point & a, const Point & b) -> Point {
                    return Point{a.x() + b.x(), a.y() + b.y()};
                });
        return Point{mean.x() / std::distance(begin, end), mean.y() / std::distance(begin,end)}; 
    }

    template<bool inverted = false>
    struct first_less_then{
        const bool operator () (const Point &a, const Point &b) const {
            return a.x() < b.x();
        }; 
    };

    template<>
    struct first_less_then<true>{
        const bool operator () (const Point &a, const Point &b) const {
            return a.y() < b.y();    
        };
    };

    template<class RandomIt, bool inverted = false> 
    void means_and_medians(
        RandomIt begin, 
        RandomIt end, 
        ListDigraph::Node father, 
        ListDigraph * clk_tree, 
        ListDigraph::NodeMap< Point > * node_to_pair
    )
    {
        auto distance = std::distance(begin,end);
        if(distance == 0){
            return;
        }

        auto region_mass_center = region_mean(begin, end);
        auto son = clk_tree->addNode();
        clk_tree->addArc(father, son);
        node_to_pair->set(son, region_mass_center); 

        std::sort(begin, end, first_less_then<inverted>{});

        auto median = begin + distance / 2;
        
        means_and_medians<RandomIt,!inverted>(begin, median, son, clk_tree, node_to_pair);
        means_and_medians<RandomIt,!inverted>(median+1, end, son, clk_tree, node_to_pair);
    }
};

#endif
