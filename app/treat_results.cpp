#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <cmath>

template<class RandomIt>
double region_mean(RandomIt begin, RandomIt end){
    auto mean = std::accumulate(begin,end, 0.0,
            [](double  a, double b) -> double {
                return a + b;
            });
    return mean / std::distance(begin,end); 
}

template<class RandomIt>
double std_deviation(RandomIt begin, RandomIt end,const double mean){
    auto dev = std::accumulate(begin,end, 0.0,
            [mean](double init, double first) -> double {
                return std::pow(first - mean,2);
            });
    return std::sqrt(dev / std::distance(begin,end));
}

int main(int argc, char* argv[]){
    
    if(argc != 2){
        std::cout << "usage: ./treat_results <file>" << std::endl;
        return -1;
    }

    std::ifstream myfile(argv[1]);

    if(!myfile.is_open())
    {
        std::cout << "no valid <file>" << std::endl;
        return -1;
    }

    std::vector<double> v;
    
    double x,y;
    while(myfile >> x >>y){
        v.push_back(x);
    }

    myfile.close();

    auto mean = region_mean( std::begin(v), std::end(v));
    std::cout << "mean: " << mean<< std::endl;

    std::cout << "std deviation: " << std_deviation(std::begin(v),std::end(v),mean) << std::endl;

    std::cout << "wire length: " << y << std::endl;

    return 0;
}
