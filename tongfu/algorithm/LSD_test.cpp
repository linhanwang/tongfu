#include "tongfu/algorithm/LSD.h"

#include <algorithm>
#include <iostream>
#include <random>
#include <string>
#include <vector>

using namespace tongfu;

int main() {
    {
        std::vector<std::string> a = {"ujdwk", "sankw", "ooljz",
                                      "wwiiq", "aaikb", "abijw"};

        LSD::sort(a, 5);

        for (int i = 0; i < a.size(); ++i) {
            std::cout << a[i] << ",";
        }
        std::cout << std::endl;
    }

    {
        std::vector<std::string> a;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(10000, 99999);

        for (int i = 0; i < 1024; ++i) {
            int v = distrib(gen);
            a.push_back(std::to_string(v));
        }

        LSD::sort(a, 5);

        std::cout << "a should be sorted: "
                  << std::is_sorted(a.begin(), a.end()) << std::endl;
    }

    return 0;
}
