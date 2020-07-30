#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <forward_list>

using std::string;
using std::vector;
using std::cin;
using std::forward_list;

struct Query {
    string type, s;
    size_t ind;
};

class QueryProcessor {
    int bucket_count;
    // store all strings in one vector
    vector<forward_list<string>> hash_table;
    size_t hash_func(const string& s) const {
        static const size_t multiplier = 263;
        static const size_t prime = 1000000007;
        unsigned long long hash = 0;
        for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
            hash = (hash * multiplier + s[i]) % prime;
        return hash % bucket_count;
    }

public:
    explicit QueryProcessor(int bucket_count): bucket_count(bucket_count), hash_table(vector<forward_list<string>>(bucket_count)) {}

    Query readQuery() const {
        Query query;
        cin >> query.type;
        if (query.type != "check")
            cin >> query.s;
        else
            cin >> query.ind;
        return query;
    }

    void writeSearchResult(bool was_found) const {
        std::cout << (was_found ? "yes\n" : "no\n");
    }

    void processQuery(const Query& query) {
        if (query.type == "check") {
            size_t bucket_number = query.ind;
            for(auto elem : hash_table[bucket_number])
                std::cout << elem << " ";
            std::cout << "\n";
        } else {
            size_t hash_value = hash_func(query.s);
            forward_list<string> &chain = hash_table[hash_value];
            forward_list<string>::iterator it = std::find(chain.begin(), chain.end(), query.s);
            if (query.type == "find")
                writeSearchResult(it != chain.end());
            else if (query.type == "add") {
                if (it == chain.end())
                    chain.push_front(query.s);
            } else if (query.type == "del") {
                if (it != chain.end())
                    chain.remove(*it);
            }
        }
    }

    void processQueries() {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i)
            processQuery(readQuery());
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    int bucket_count;
    cin >> bucket_count;
    QueryProcessor proc(bucket_count);
    proc.processQueries();
    return 0;
}
