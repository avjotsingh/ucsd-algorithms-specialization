#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int const Letters =    4;
int const NA      =   -1;

struct Node
{
	int next [Letters];
	bool patternEnd;

	Node ()
	{
		fill (next, next + Letters, NA);
		patternEnd = false;
	}
};

int letterToIndex (char letter)
{
	switch (letter)
	{
		case 'A': return 0; break;
		case 'C': return 1; break;
		case 'G': return 2; break;
		case 'T': return 3; break;
		default: assert (false); return -1;
	}
}

void constructTrie(vector<string> patterns, vector<Node> &trie) {
	trie.push_back(Node());
	for(auto pattern : patterns) {
		int current_node = 0;
		for(auto symbol : pattern) {
			int idx = letterToIndex(symbol);
			if(trie[current_node].next[idx] != NA) {
				current_node = trie[current_node].next[idx];
			}
			else {
				trie.push_back(Node());
				trie[current_node].next[idx] = trie.size() - 1;
				current_node = trie.size() - 1;
			}
		}
		trie[current_node].patternEnd = true;
	}
}


vector <int> solve (string text, int n, vector <string> patterns)
{
	vector <int> result;
	vector<Node> trie;
	constructTrie(patterns, trie);
	for(int i = 0; i < text.size(); ++i) {
		int j = i;
		int current_node = 0;
		while(true) {
			if(trie[current_node].patternEnd) {
				result.push_back(i);
				break;
			}
			else if(j == text.size()) {
				break;
			}
			else {
				auto symbol = text[j];
				int idx = letterToIndex(symbol);
				if(trie[current_node].next[idx] == NA) {
					break;
				}
				else {
					current_node = trie[current_node].next[idx];
					j++;
				}
			}
		}
	}
	return result;
}

int main (void)
{
	string text;
	cin >> text;

	int n;
	cin >> n;

	vector <string> patterns (n);
	for (int i = 0; i < n; i++)
	{
		cin >> patterns[i];
	}

	vector <int> ans;
	ans = solve (text, n, patterns);

	for (int i = 0; i < (int) ans.size (); i++)
	{
		cout << ans[i];
		if (i + 1 < (int) ans.size ())
		{
			cout << " ";
		}
		else
		{
			cout << endl;
		}
	}

	return 0;
}
