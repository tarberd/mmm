#ifndef MMM_H
#define MMM_H

#include <algorithm>
#include <numeric>
#include <iterator>
#include <lemon/list_graph.h>

using lemon::ListDigraph;
using std::pair;

namespace clk_router {
    template<class RandomIt, class Pair>
    Pair region_mean(RandomIt begin, RandomIt end){
        auto mean = std::accumulate(begin,end, Pair{0,0},
                [](const Pair & a, const Pair & b){
                    return Pair{a.first + b.first, a.second + b.second};
                });
        return Pair{mean.first / std::distance(begin, end), mean.second / std::distance(begin,end)}; 
    }

    template <typename T>
    static const std::function< bool(pair<T,T>, Pair)> first_less_then = [](const Pair & a, const Pair & b){
        return a.first < b.first;
    };

    template <typename T>
    static const std::function< bool(pair<T,T>, pair<T,T>) > second_less_then = [](const Pair & a, const Pair & b){
        return a.second < b.second;
    };

    template<
        class RandomIt,
        typename T 
    >
    void means_and_medians(
        RandomIt begin, 
        RandomIt end, 
        ListDigraph::Node father, 
        ListDigraph * clk_tree, 
        ListDigraph::NodeMap< pair<T,T> > * node_to_pair,
        const std::function< bool(pair<T,T>, pair<T,T>) > & comp = first_less_then<T> 
    ){
        auto distance = std::distance(begin,end);
        if(distance == 0){
            return;
        }

        auto region_mass_center = region_mean<Pair>(begin, end);
        
        auto son = clk_tree->addNode();
        clk_tree->addArc(father, son);
        (*node_to_pair)[son] = region_mass_center; 

        std::sort(begin, end, comp);

        auto median = begin + distance / 2;
        comp = comp == first_less_then<Pair> ? second_less_then<Pair> : first_less_then<Pair>;

        means_and_medians(begin, median, son, clk_tree, node_to_pair, comp);
        means_and_medians(median, end, son, clk_tree, node_to_pair, comp);
    }
};

#endif
