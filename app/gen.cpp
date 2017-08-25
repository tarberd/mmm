#include <iostream>
#include <fstream>
#include <string>
#include <random>

int main(int argc, char* argv[]){
    
    if(argc != 3){
        std::cout << "usage: ./gen <seed> <size>" << std::endl;
        return -1;
    }

    int seed = 0;
    int size = 0;

    std::string seed_char(argv[1]);
    std::string size_char(argv[2]);

    std::default_random_engine gen(std::stoi(seed_char));
    auto uniform_dist = std::uniform_int_distribution<>{0,1024};

    std::ofstream myfile;
    myfile.open ("input.txt");

    for(int i = 0; i < std::stoi(size_char); ++i){
        myfile << uniform_dist(gen) << " " << uniform_dist(gen) << std::endl;
    }

    myfile.close();

    return 0;
}
