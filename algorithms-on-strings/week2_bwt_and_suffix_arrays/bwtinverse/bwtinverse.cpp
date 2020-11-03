#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <map>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using namespace std;

string InverseBWT(const string& bwt) {
  string text = "";
  map<char, int> last;
  map<char, int> first;
  map<pair<char, int>, pair<char, int>> last_to_first;
  for(auto c: bwt) {
  	if(last.find(c) == last.end()) {
  		last[c] = 0;
  		first[c] = 0;
  	}
  }

  string sorted_text = bwt;
  sort(sorted_text.begin(), sorted_text.end());
  for(int i = 0; i < bwt.size(); ++i) {
  	last_to_first[make_pair(bwt[i], last[bwt[i]])] = make_pair(sorted_text[i], first[sorted_text[i]]);
  	last[bwt[i]] += 1;
  	first[sorted_text[i]] += 1;
  }

  // for(auto p: last_to_first) {
  // 	cout << p.first.first << "," << p.first.second << "->" << p.second.first << "," << p.second.second << endl;
  // }

  auto reverse_map = last_to_first[{'$', 0}];
  while(true) {
  	text += reverse_map.first;
  	if (reverse_map.first == '$') {
  		break;
  	}
  	reverse_map = last_to_first[reverse_map];
  }

  return text;
}

int main() {
  string bwt;
  cin >> bwt;
  cout << InverseBWT(bwt) << endl;
  return 0;
}
