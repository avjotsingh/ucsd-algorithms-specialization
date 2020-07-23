#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;

class HeapBuilder {
 private:
  vector<int> data_;
  vector< pair<int, int> > swaps_;

  void WriteResponse() const {
    cout << swaps_.size() << "\n";
    for (int i = 0; i < swaps_.size(); ++i) {
      cout << swaps_[i].first << " " << swaps_[i].second << "\n";
    }
  }

  void ReadData() {
    int n;
    cin >> n;
    data_.resize(n);
    for(int i = 0; i < n; ++i)
      cin >> data_[i];
  }

  void GenerateSwaps_naive() {
    swaps_.clear();
    // The following naive implementation just sorts 
    // the given sequence using selection sort algorithm
    // and saves the resulting sequence of swaps.
    // This turns the given array into a heap, 
    // but in the worst case gives a quadratic number of swaps.
    for (int i = 0; i < data_.size(); ++i)
      for (int j = i + 1; j < data_.size(); ++j) {
        if (data_[i] > data_[j]) {
          swap(data_[i], data_[j]);
          swaps_.push_back(make_pair(i, j));
        }
      }
  }

  void GenerateSwaps() {
    swaps_.clear();
    for(int i = data_.size() / 2 - 1; i >= 0; --i) {
      heapify(i);
    }
  }

  void heapify(int n) {
    while(2*n + 1 < data_.size()) {
      int parent = data_[n];
      int left_child = data_[2*n + 1];
      int right_child = (2*n + 2 < data_.size()) ? data_[2*n + 2] : 1000000001;

      if(parent <= left_child && parent <= right_child)
        break;
      else if(left_child < parent && left_child < right_child) {
        swap(data_[n], data_[2*n + 1]);
        swaps_.push_back(make_pair(n, 2*n + 1));
        n = 2*n + 1;
      }
      else {
        swap(data_[n], data_[2*n + 2]);
        swaps_.push_back(make_pair(n, 2*n + 2));
        n = 2*n + 2;
      }
    }
  }

 public:
  void Solve() {
    ReadData();
    GenerateSwaps();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  HeapBuilder heap_builder;
  heap_builder.Solve();
  return 0;
}
