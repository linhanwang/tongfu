#include <iostream>
#include "tongfu/container/search_tree.h"

using namespace tongfu;

int main() {
    SearchTree<int, int> st;

    st.insert(1, 1);

    std::cout << "size should be 1: " << st.size() << std::endl;

    st.insert(2,2);
    st.insert(6,6);
    st.insert(4,4);
    st.insert(3,3);
    st.insert(3, 6);
    st.insert(5,5);

    std::cout << "size should be 7: " << st.size() << std::endl;

    auto iter = st.begin();
    while (iter != st.end()) {
        std::cout << (*iter).key() << " : " << (*iter).value() << std::endl;
        ++iter;
    }
    
    std::cout << "find(3) should be 3: " << (*st.find(3)).value() << std::endl;

    st.erase(2);
    st.erase(4);

    std::cout << "size should be 5: " << st.size() << std::endl;
    std::cout << "find(3) should be 3: " << (*st.find(3)).value() << std::endl;

    st.erase(3);
    std::cout << "find(3) should be 6: " << (*st.find(3)).value() << std::endl;
    std::cout << "size should be 4: " << st.size() << std::endl;

    return 0;
}
