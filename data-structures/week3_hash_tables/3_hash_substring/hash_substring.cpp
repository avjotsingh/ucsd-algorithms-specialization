#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::cout;
typedef unsigned long long ull;

struct Data {
    string pattern, text;
};

class StringPolyHash {
private:
    size_t prime_ = 10000007;
    size_t multiplier_ = rand() % prime_;

public:
    size_t get_multiplier() {
        return multiplier_;
    }
    size_t get_prime() {
        return prime_;
    }
    size_t compute_hash(const string &s) {
        size_t hash = 0;
        for(size_t i = 0; i < s.size(); ++i)
            hash = (hash * multiplier_ + s[i]) % prime_;
        return hash;
    }
};

Data read_input() {
    Data data;
    std::cin >> data.pattern >> data.text;
    return data;
}

void print_occurrences(const std::vector<int>& output) {
    for (size_t i = 0; i < output.size(); ++i)
        std::cout << output[i] << " ";
    std::cout << "\n";
}

std::vector<int> get_occurrences(const Data& input) {
    const string& s = input.pattern, t = input.text;
    StringPolyHash h = StringPolyHash();
    size_t pmultplier = 1;
    for(size_t i = 0; i < s.size() - 1; ++i)
        pmultplier = (pmultplier * h.get_multiplier()) % h.get_prime();

    std::vector<int> ans;
    size_t phash = h.compute_hash(s);
    size_t hash = h.compute_hash(t.substr(0, s.size()));
    for (size_t i = 0; i + s.size() <= t.size(); ++i) {
        if(i > 0) {
            size_t a = (t[i - 1] * pmultplier) % h.get_prime();
            if(hash >= a)
                hash = hash - a;
            else
                hash = hash + h.get_prime() - a;
            hash = (hash * h.get_multiplier() + t[i + s.size() - 1]) % h.get_prime();
        }
        if (hash == phash) {
            bool equal = true;
            for(int j = 0; j < s.size(); ++j) {
                if(s[j] != t[i + j]) {
                    equal = false;
                    break;
                }
            }
            if(equal)
                ans.push_back(i);
        }
    }
    return ans;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    print_occurrences(get_occurrences(read_input()));
    return 0;
}
