#include <cstdio>
#include <string>
#include <iostream>
#include <cassert>

using namespace std;

struct STNode {
	char key;
	int size;
	STNode* parent;
	STNode* left;
	STNode* right;

	STNode(char key, int size, STNode* parent, STNode* left, STNode* right) 
	: key(key), size(size), parent(parent), left(left), right(right) { }
};

class STOps {
private:
	void update(STNode* v) {
		if(v == NULL)
			return;
		v->size = 1;
		if(v->left != NULL) {
			v->left->parent = v;
			v->size += v->left->size;
		}
		if(v->right != NULL) {
			v->right->parent = v;
			v->size += v->right->size;
		}
	}

	void splay(STNode*& root, STNode *v) {
		if(root == NULL || v == NULL)
			return;
		while(v->parent != NULL) {
			STNode* grandparent = v->parent->parent;
			if(grandparent != NULL) {
				big_rotation(v);
			}
			else {
				small_rotation(v);
			}
		}

		root = v;
	}

	STNode* find(STNode*& root, int i) {
		//return the pointer to the ith largest element
		STNode* v = root;
		STNode* last = root;
		while(v != NULL) {
			last = v;
			int n_left = (v->left == NULL) ? 0 : v->left->size;
			if(i == n_left + 1) {
				break;
			}
			else if(i < n_left + 1) {
				v = v->left;
			}
			else {
				i = i - n_left - 1;
				v = v->right;
			}
		}
		splay(root, last);
		return v;
	}

	void small_rotation(STNode*& v) {
		if(v == NULL || v->parent == NULL)
			return;

		STNode* parent = v->parent;
		STNode* grandparent = v->parent->parent;
		if(v == parent->left) {
			//rotate righ
			parent->left = v->right;
			v->right = parent;
		}
		else {
			//rotate left
			parent->right = v->left;
			v->left = parent;
		}
		update(parent);
		update(v);
		v->parent = grandparent;
		if(grandparent != NULL) {
			if(grandparent->left == parent) {
				grandparent->left = v;
			}
			else {
				grandparent->right = v;
			}
		}
	}

	void big_rotation(STNode*& v) {
		if(v == NULL || v->parent == NULL)
			return;
		STNode* parent = v->parent;
		STNode* grandparent = v->parent->parent;
		if(grandparent == NULL) {
			small_rotation(v);
		}
		else if(v == parent->left && parent == grandparent->left) {
			small_rotation(parent);
			small_rotation(v);
		}
		else if(v == parent->right && parent == grandparent->right) {
			small_rotation(parent);
			small_rotation(v);
		}
		else {
			small_rotation(v);
			small_rotation(v);
		}
	}

public:
	void insert(STNode*& root, int i, const char key) {
		//insert the ith largest element into the Splay tree.
		if(root == NULL) {
			assert(i == 0);
			root = new STNode(key, 1, NULL, NULL, NULL);
		}
		else {
			STNode* left = NULL;
			STNode* right = NULL;
			STNode* new_node = new STNode(key, 1, NULL, NULL, NULL);
			split(root, i, left, right);
			root = merge(merge(left, new_node), right);
		}
	}
	void split(STNode* root, int i, STNode*& left, STNode*& right) {
		//split the tree into two subtrees with elements ranging from (1...i-1) && (i...N)
		if(root == NULL)
			return;
		left = find(root, i);
		splay(root, left);
		if(left == NULL) {
			right = root;
			return;
		}

		right = left->right;		
		left->right = NULL;
		if(right != NULL){
			right->parent = NULL;
		}
		update(left);
		update(right);
	}

	STNode* merge(STNode *left, STNode *right) {
		//merge two trees rooted at left and right.
		if(left == NULL) {
			return right;
		}
		else if(right == NULL) {
			return left;
		}
		else {
			STNode* min_right = right;
			while(min_right->left != NULL) {
				min_right = min_right->left;
			}
			splay(right, min_right);
			right->left = left;
			update(right);
			return right;
		}
	}

	void get_string(STNode* root, string &result) {
		if(root == NULL) {
			return;
		}
		if(root->left != NULL) {
			get_string(root->left, result);
		}
		result.append(string(1, root->key));
		if(root->right != NULL) {
			get_string(root->right, result);
		}
	}
};

class Rope {
	std::string s;
	STOps st;
	STNode* root;
public:
	Rope(const std::string &s) : s(s), st(STOps()), root(NULL) {
		for(int i = 0; i < s.size(); ++i) {
			st.insert(root, i, s[i]);
		}
	}

	void process(int i, int j, int k ) {
		STNode* left = NULL;
		STNode* middle = NULL;
		STNode* right = NULL;
		st.split(root, i, left, right);
		st.split(right, j - i + 1, middle, right);
		root = st.merge(left, right);
		st.split(root, k, left, right);
		root = st.merge(st.merge(left, middle), right);
	}

	std::string result() {
		string result;
		st.get_string(root, result);
		return result;
	}
};

int main() {
	std::ios_base::sync_with_stdio(0);
	std::string s;
	std::cin >> s;
	Rope rope(s);
	int actions;
	std::cin >> actions;
        for (int action_index = 0; action_index < actions; ++action_index) {
                int i, j, k;
		std::cin >> i >> j >> k;
		rope.process(i, j, k);
	}
	std::cout << rope.result() << std::endl;
}
