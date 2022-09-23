#include "tongfu/algorithm/LSD.h"
#include <iostream>

using namespace tongfu;

int main() {
    std::vector<std::string> a = {"ujdwk", "sankw", "ooljz", "wwiiq", "aaikb", "abijw"};

    LSD::sort(a, 5);

    for (int i = 0; i < a.size(); ++i) {
        std::cout << a[i] << ",";
    }
    std::cout << std::endl;

    return 0;
}
