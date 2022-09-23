#include "tongfu/algorithm/MSD.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <random>

using namespace tongfu;

int main() {
    {
        std::vector<std::string> a = {"asdf", "sfd", "as", "adfad", "asd", "gdd"};
    
        MSD::sort(a);
    
        for (int i = 0; i < a.size(); ++i)
            std::cout << a[i] << ",";
        std::cout << std::endl;
    }
    
    {
        std::vector<std::string> a;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, 100000);

        for (int i = 0; i < 124; ++i) {
            int v = distrib(gen);
            a.push_back(std::to_string(v));
        }

        MSD::sort(a);

        std::cout << "a should be sorted: " << std::is_sorted(a.begin(), a.end()) << std::endl;
    }

    return 0;
}
