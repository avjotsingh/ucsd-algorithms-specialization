#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
using std::max;

int compute_min_refills(int dist, int tank, vector<int> & stops) {
    // write your code here
    int refills = 0;
    int last = 0;
    int last_stop = -1;

    stops.push_back(dist);
    while(last != dist) {
        int i = last_stop;
        while(i + 1 < stops.size() && stops[i + 1] - last <= tank)
            ++i;

        if(i == last_stop)
            return -1;
        else if(stops[i] == dist)
            break;
        else {
            last_stop = i;
            last = stops[last_stop];
            ++refills;
        }
    }

    return refills;
}


int main() {
    int d = 0;
    cin >> d;
    int m = 0;
    cin >> m;
    int n = 0;
    cin >> n;

    vector<int> stops(n);
    for (size_t i = 0; i < n; ++i)
        cin >> stops.at(i);

    cout << compute_min_refills(d, m, stops) << "\n";

    return 0;
}
