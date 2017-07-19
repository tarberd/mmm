#ifndef MMM_H
#define MMM_H

#include <algorithm>
#include <numeric>
#include <utility>

using std::pair;
using std::sort;
using std::begin;
using std::end;

namespace clk_router {
    template< class RandomIt >
    void means_medians_y(RandomIt begin, RandomIt end, pair<float,float> first);
    
    template<class RandomIt>
    pair<float,float> section_mean(RandomIt begin, RandomIt end);

    template<class RandomIt>
    RandomIt section_median(RandomIt begin, RandomIt end);

    template< class RandomIt >
    void means_medians_x(RandomIt begin, RandomIt end, pair<float,float> first)
    {
        sort(
            begin, 
            end,
            [](const pair<float,float> & a, const pair<float,float>& b){
                return a.first < b.first;
            }
        );

        auto section_center = section_mean(begin, end);
        //rout first section_center
        auto median = section_median(begin,end);

        means_medians_y(begin, median, section_center);
        means_medians_y(median, end, section_center);
    }

    template< class RandomIt >
    void means_medians_y(RandomIt begin, RandomIt end, pair<float,float> first)
    {
        sort(
            begin, 
            end,
            [](const pair<float,float> & a, const pair<float,float>& b){
                return a.second < b.second;
            }
        );

        auto section_center = section_mean(begin, end);
        //rout first section_center
        auto median = section_median(begin,end);

        means_medians_x(begin, median, section_center);
        means_medians_x(median, end, section_center);
    }
    
    template<class RandomIt>
    pair<float,float> section_mean(RandomIt begin, RandomIt end){
        auto mean = std::accumulate(begin,end, std::make_pair(0.0f,0.0f),
                [](pair<float,float> a, pair<float,float> b){
                    return std::make_pair(a.first + b.first, a.second + b.second);
                });
        return {mean.first / std::distance(begin, end), mean.second / std::distance(begin,end)}; 
    }
           
    template<class RandomIt>
    RandomIt section_median(RandomIt begin, RandomIt end){
        return begin + std::distance(begin,end) / 2;
    }
};

#endif
