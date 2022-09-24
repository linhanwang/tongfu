#include "tongfu/container/trie.h"

#include <iostream>
#include <vector>

using namespace tongfu;

int main() {
    TrieST trie;

    trie.put("abc", 1);
    trie.put("abcd", 2);
    trie.put("abe", 3);
    trie.put("ccf", 4);
    trie.put("accd", 5);

    std::cout << (trie.get("abc") == 1) << std::endl;
    std::cout << (trie.get("abcd") == 2) << std::endl;
    std::cout << (trie.get("ccf") == 4) << std::endl;

    auto a_prefix = trie.keysWithPrefix("a");
    auto ab_prefix = trie.keysWithPrefix("ab");
    auto keys = trie.keys();
    auto keys_match = trie.keysThatMatch("a.cd");

    std::cout << "all keys: " << std::endl;
    for (auto& s : keys) std::cout << s << ",";
    std::cout << std::endl;

    std::cout << "keys with prefix a: " << std::endl;
    for (auto& s : a_prefix) std::cout << s << ",";
    std::cout << std::endl;

    std::cout << "keys with prefix ab: " << std::endl;
    for (auto& s : ab_prefix) std::cout << s << ",";
    std::cout << std::endl;

    std::cout << "keys that match a.cd: " << std::endl;
    for (auto& s : keys_match) std::cout << s << ",";
    std::cout << std::endl;

    std::cout << "longestPrefixOf abcde should be abcd: "
              << trie.longestPrefixOf("abcde") << std::endl;

    trie.remove("abcd");
    trie.put("abae", 2);

    a_prefix = trie.keysWithPrefix("a");
    ab_prefix = trie.keysWithPrefix("ab");
    keys = trie.keys();
    keys_match = trie.keysThatMatch("a.cd");

    std::cout << "all keys: " << std::endl;
    for (auto& s : keys) std::cout << s << ",";
    std::cout << std::endl;

    std::cout << "keys with prefix a: " << std::endl;
    for (auto& s : a_prefix) std::cout << s << ",";
    std::cout << std::endl;

    std::cout << "keys with prefix ab: " << std::endl;
    for (auto& s : ab_prefix) std::cout << s << ",";
    std::cout << std::endl;

    std::cout << "keys that match a.cd: " << std::endl;
    for (auto& s : keys_match) std::cout << s << ",";
    std::cout << std::endl;

    for (auto& key : keys) {
        trie.remove(key);
    }

    return 0;
}
