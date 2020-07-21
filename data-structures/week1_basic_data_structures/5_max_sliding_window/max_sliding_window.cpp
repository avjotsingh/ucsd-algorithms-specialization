#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <cassert>

using std::cin;
using std::cout;
using std::vector;
using std::max;

class QueueWithMax {
private:
    std::queue<int> queue;
    std::deque<int> queue_max;
public:
    void Push(int value) {
        queue.push(value);
        while(!queue_max.empty() && queue_max.back() < value)
            queue_max.pop_back();
        queue_max.push_back(value);
    }

    void Pop() {
        assert(queue.size());
        if(queue.front() == queue_max.front())
            queue_max.pop_front();
        queue.pop();
    }

    int Max() {
        assert(queue.size());
        return queue_max.front();
    }

};

void max_sliding_window_naive(vector<int> const & A, int w) {
    for (size_t i = 0; i < A.size() - w + 1; ++i) {
        int window_max = A.at(i);
        for (size_t j = i + 1; j < i + w; ++j)
            window_max = max(window_max, A.at(j));

        cout << window_max << " ";
    }

    return;
}

void max_sliding_window_fast(vector<int> const & A, int w) {
    QueueWithMax queue;
    for (size_t i = 0; i < A.size(); ++i) {
        queue.Push(A[i]);
        if(i >= w - 1) {
            std::cout << queue.Max() << ' ';
            queue.Pop();
        }
    }

    return;
}


int main() {
    int n = 0;
    cin >> n;

    vector<int> A(n);
    for (size_t i = 0; i < n; ++i)
        cin >> A.at(i);

    int w = 0;
    cin >> w;

    max_sliding_window_fast(A, w);

    return 0;
}
