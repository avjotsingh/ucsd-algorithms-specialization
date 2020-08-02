#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

struct Node {
  int key;
  int left;
  int right;

  Node() : key(0), left(-1), right(-1) {}
  Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

const Node *leftLargest(const Node *root, const vector<Node> &tree) {
  if(root->left == -1)
    return NULL;
  else {
    const Node *left_largest = &tree[root->left];
    while(left_largest->right != -1)
      left_largest = &tree[left_largest->right];
    return left_largest;
  }
}

const Node *rightSmallest(const Node *root, const vector<Node> &tree) {
  if(root->right == -1)
    return NULL;
  else {
    const Node *right_smallest = &tree[root->right];
    while(right_smallest->left != -1)
      right_smallest = &tree[right_smallest->left];
    return right_smallest;
  }
}

bool IsBinarySearchTree(const vector<Node>& tree) {
  bool valid = true;
  for(const Node root : tree) {
    const Node *left_largest = leftLargest(&root, tree);
    const Node *right_smallest = rightSmallest(&root, tree);

    if((left_largest != NULL && left_largest->key > root.key) || (right_smallest != NULL && right_smallest->key < root.key)) {
      valid = false;
      break;
    }
  }

  return valid;
}

int main() {
  int nodes;
  cin >> nodes;
  vector<Node> tree;
  for (int i = 0; i < nodes; ++i) {
    int key, left, right;
    cin >> key >> left >> right;
    tree.push_back(Node(key, left, right));
  }
  if (IsBinarySearchTree(tree)) {
    cout << "CORRECT" << endl;
  } else {
    cout << "INCORRECT" << endl;
  }
  return 0;
}
