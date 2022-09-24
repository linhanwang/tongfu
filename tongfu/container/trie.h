#include <climits>
#include <string>
#include <vector>

namespace tongfu {

class TrieST {
   public:
    static constexpr int R = 256;
    static constexpr int kNull = INT_MAX;

   private:
    struct Node {
        Node() : val(kNull), next(TrieST::R, nullptr) {}

        int val;
        std::vector<Node*> next;
    };

    Node* root;
    int n;

   public:
    TrieST() : root(nullptr), n(0) {}

    bool contains(const std::string& key) const { return get(key) != kNull; }

    int get(const std::string& key) const {
        Node* x = get(root, key, 0);
        return x->val;
    }

    void put(const std::string& key, int val) { root = put(root, key, val, 0); }

    void remove(const std::string& key) { root = remove(root, key, 0); }

    int size() const { return n; }

    bool isEmpty() const { return n == 0; }

    std::vector<std::string> keys() const { return keysWithPrefix(""); }

    std::vector<std::string> keysWithPrefix(const std::string& prefix) const {
        std::vector<std::string> results;
        Node* x = get(root, prefix, 0);
        std::string cur = prefix;
        collect(x, cur, results);
        return results;
    }

    /*
     * Returns the string in the symbol table that is the longest prefix of qry
     * */
    std::string longestPrefixOf(const std::string& qry) {
        int length = longestPrefixOf(root, qry, 0, -1);
        if (length == -1)
            return "";
        else
            return qry.substr(0, length);
    }

    /*
     * Returns all of the keys in the symbole table that match pattern,
     * where the charater '.' is interpreted as a wildcard charater.
     * */
    std::vector<std::string> keysThatMatch(const std::string& pattern) {
        std::vector<std::string> results;
        std::string prefix;
        collect(root, prefix, pattern, results);
        return results;
    }

   private:
    Node* get(Node* x, const std::string& key, int d) const {
        if (x == nullptr) return nullptr;
        if (d == key.size()) return x;
        char c = key[d];
        return get(x->next[c], key, d + 1);
    }

    Node* put(Node* x, const std::string& key, int val, int d) {
        if (x == nullptr) x = new Node();
        if (d == key.size()) {
            if (x->val == kNull) ++n;
            x->val = val;
            return x;
        }
        char c = key[d];
        x->next[c] = put(x->next[c], key, val, d + 1);
        return x;
    }

    void collect(Node* x, std::string& prefix,
                 std::vector<std::string>& results) const {
        if (x == nullptr) return;
        if (x->val != kNull) results.push_back(prefix);
        for (int i = 0; i < R; i++) {
            prefix.push_back((char)i);
            collect(x->next[i], prefix, results);
            prefix.pop_back();
        }
    }

    void collect(Node* x, std::string& prefix, const std::string& pattern,
                 std::vector<std::string>& results) {
        if (x == nullptr) return;
        int d = prefix.size();
        if (d == pattern.size()) {
            if (x->val != kNull) results.push_back(prefix);
            return;
        }

        char c = pattern[d];
        if (c == '.') {
            for (int ch = 0; ch < R; ++ch) {
                prefix.push_back((char)ch);
                collect(x->next[ch], prefix, pattern, results);
                prefix.pop_back();
            }
        } else {
            prefix.push_back(c);
            collect(x->next[c], prefix, pattern, results);
            prefix.pop_back();
        }
    }

    Node* remove(Node* x, const std::string& key, int d) {
        if (x == nullptr) return nullptr;
        if (d == key.size()) {
            if (x->val != kNull) --n;
            x->val = kNull;
        } else {
            char c = key[d];
            x->next[c] = remove(x->next[c], key, d + 1);
        }

        // remove subtrie rooted at x if it is completely empty
        if (x->val != kNull) return x;
        for (int i = 0; i < R; ++i)
            if (x->next[i] != nullptr) return x;
        delete x;
        return nullptr;
    }

    int longestPrefixOf(Node* x, const std::string& qry, int d, int length) {
        if (x == nullptr) return length;
        if (x->val != kNull) length = d;
        if (d == qry.size()) return length;
        char c = qry[d];
        return longestPrefixOf(x->next[c], qry, d + 1, length);
    }
};

}  // namespace tongfu
