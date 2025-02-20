#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

class Solver {
	string s;
	const size_t m1 = 5000007;
	const size_t m2 = 5000009;
	size_t x;
	vector<size_t> H1;
	vector<size_t> H2;
	vector<size_t> powx1;
	vector<size_t> powx2;
public:	
	Solver(string s) : s(s), 
					x(1 + rand() % 1000), 
					H1(vector<size_t>(1 + s.size())), 
					H2(vector<size_t>(1 + s.size())), 
					powx1(vector<size_t>(1 + s.size())),
					powx2(vector<size_t>(1 + s.size())) {	
		// initialization, precalculation
		H1[0] = H2[0] = 0;
		powx1[0] = powx2[0] = 1;
		for(size_t i = 1; i <= s.size(); ++i) {
			H1[i] = (x * H1[i - 1] + s[i - 1]) % m1;
			H2[i] = (x * H2[i - 1] + s[i - 1]) % m2;
			powx1[i] = (x * powx1[i - 1]) % m1;
			powx2[i] = (x * powx2[i - 1]) % m2;
		}
	}

	bool ask_naive(int a, int b, int l) {
		return s.substr(a, l) == s.substr(b, l);
	}

	bool ask(int a, int b, int l) {
		size_t hash_a1 = (powx1[l] * H1[a]) % m1;
		hash_a1 = (H1[a + l] >= hash_a1) ? H1[a + l] - hash_a1 : (H1[a + l] + m1 - hash_a1);

		size_t hash_b1 = (powx1[l] * H1[b]) % m1;
		hash_b1 = (H1[b + l] >= hash_b1) ? H1[b + l] - hash_b1 : (H1[b + l] + m1 - hash_b1);
		
		size_t hash_a2 = (powx2[l] * H2[a]) % m2;
		hash_a2 = (H2[a + l] >= hash_a2) ? H2[a + l] - hash_a2 : (H2[a + l] + m2 - hash_a2);

		size_t hash_b2 = (powx2[l] * H2[b]) % m2;
		hash_b2 = (H2[b + l] >= hash_b2) ? H2[b + l] - hash_b2 : (H2[b + l] + m2 - hash_b2);

		return (hash_a1 == hash_b1 && hash_a2 == hash_b2);
	}
};

void test_solution() {
	size_t str_len = rand() % 50;
	int q = rand() % 100;
	string s;
	for(size_t i = 0; i < str_len; ++i)
		s.append(string(1, 'a' + rand() % 26));

	Solver solver(s);
	for(int i = 0; i < q; ++i) {
		int a, b, l;
		a = rand() % str_len;
		b = rand() % str_len;
		l = rand() % std::min(str_len - a, str_len - b);
		auto res1 = solver.ask(a, b, l);
		auto res2 = solver.ask_naive(a, b, l);
		cout << a << " " << b << " " << l << " " << res1 << " " << res2 << "\n";
		assert(res1 == res2);
	}	

	cout << "Tests passed...\n";
}

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);
	string s;
	int q;
	cin >> s >> q;
	Solver solver(s);
	for (int i = 0; i < q; i++) {
		int a, b, l;
		cin >> a >> b >> l;
		cout << (solver.ask(a, b, l) ? "Yes\n" : "No\n");
	}
}
