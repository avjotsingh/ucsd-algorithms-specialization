#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

using std::vector;
using std::ios_base;
using std::cin;
using std::cout;

class TreeOrders {
  int n;
  vector <int> key;
  vector <int> left;
  vector <int> right;

public:
  void read() {
    cin >> n;
    key.resize(n);
    left.resize(n);
    right.resize(n);
    for (int i = 0; i < n; i++) {
      cin >> key[i] >> left[i] >> right[i];
    }
  }

  void inorder_traversal(int root, vector<int> &result) {
    if(root == -1)
      return;
    inorder_traversal(left[root], result);
    result.push_back(key[root]);
    inorder_traversal(right[root], result);
  }

  vector <int> in_order() {
    vector<int> result;
    inorder_traversal(0, result);
    return result;
  }

  void preorder_traversal(int root, vector<int> &result) {
    if(root == -1)
      return;

    result.push_back(key[root]);
    preorder_traversal(left[root],result);
    preorder_traversal(right[root], result);
  }

  vector <int> pre_order() {
    vector<int> result;    
    preorder_traversal(0, result);
    return result;
  }

  void postorder_traversal(int root, vector<int> &result) {
    if(root == -1)
      return;

    postorder_traversal(left[root], result);
    postorder_traversal(right[root], result);
    result.push_back(key[root]);
  }

  vector <int> post_order() {
    vector<int> result;
    postorder_traversal(0, result);
    return result;
  }
};

void print(vector <int> a) {
  for (size_t i = 0; i < a.size(); i++) {
    if (i > 0) {
      cout << ' ';
    }
    cout << a[i];
  }
  cout << '\n';
}

int main_with_large_stack_space() {
  ios_base::sync_with_stdio(0);
  TreeOrders t;
  t.read();
  print(t.in_order());
  print(t.pre_order());
  print(t.post_order());
  return 0;
}

int main (int argc, char **argv)
{
#if defined(__unix__) || defined(__APPLE__)
  // Allow larger stack space
  const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
  struct rlimit rl;
  int result;

  result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0)
  {
      if (rl.rlim_cur < kStackSize)
      {
          rl.rlim_cur = kStackSize;
          result = setrlimit(RLIMIT_STACK, &rl);
          if (result != 0)
          {
              std::cerr << "setrlimit returned result = " << result << std::endl;
          }
      }
  }
#endif

  return main_with_large_stack_space();
}

