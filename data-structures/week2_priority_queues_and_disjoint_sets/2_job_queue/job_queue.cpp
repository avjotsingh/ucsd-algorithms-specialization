#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using std::vector;
using std::cin;
using std::cout;

class JobQueue {
 private:
  int num_workers_;
  vector<int> jobs_;

  vector<int> assigned_workers_;
  vector<long long> start_times_;

  void WriteResponse() const {
    for (int i = 0; i < jobs_.size(); ++i) {
      cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
    }
  }

  void ReadData() {
    int m;
    cin >> num_workers_ >> m;
    jobs_.resize(m);
    for(int i = 0; i < m; ++i)
      cin >> jobs_[i];
  }

  void AssignJobs_naive() {
    assigned_workers_.resize(jobs_.size());
    start_times_.resize(jobs_.size());
    vector<long long> next_free_time(num_workers_, 0);
    for (int i = 0; i < jobs_.size(); ++i) {
      int duration = jobs_[i];
      int next_worker = 0;
      for (int j = 0; j < num_workers_; ++j) {
        if (next_free_time[j] < next_free_time[next_worker])
          next_worker = j;
      }
      assigned_workers_[i] = next_worker;
      start_times_[i] = next_free_time[next_worker];
      next_free_time[next_worker] += duration;
    }
  }

  void AssignJobs() {
    assigned_workers_.resize(jobs_.size());
    start_times_.resize(jobs_.size());
    
    std::priority_queue<int, std::vector<int>, std::greater<int>> available_workers;
    auto comparator = [](std::pair<int, long long> p1, std::pair<int, long long> p2) { return p1.second > p2.second; };
    std::priority_queue<std::pair<int, long long>, std::vector<std::pair<int, long long>>, decltype(comparator)> finish_times(comparator);

    for(int i = 0; i < num_workers_; ++i) {
      available_workers.push(i);
    }

    long long last_finish_time = 0;
    for(int i = 0; i < jobs_.size(); ++i) {
      if(available_workers.empty()) {
        last_finish_time = finish_times.top().second;
        while(!finish_times.empty() && finish_times.top().second == last_finish_time) {
          available_workers.push(finish_times.top().first);
          finish_times.pop();
        }
      }

      finish_times.push(std::make_pair(available_workers.top(), last_finish_time + jobs_[i]));
      assigned_workers_[i] = available_workers.top();
      start_times_[i] = last_finish_time;
      available_workers.pop();
    }
  }

 public:
  void Solve() {
    ReadData();
    AssignJobs();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  JobQueue job_queue;
  job_queue.Solve();
  return 0;
}
