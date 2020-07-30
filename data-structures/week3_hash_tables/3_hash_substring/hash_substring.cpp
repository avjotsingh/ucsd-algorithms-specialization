#include <iostream>
#include <map>
#include <chrono>
#include <vector>
using namespace std;
using namespace std::chrono;
using std::vector;

struct Answer {
	size_t i, j, len;
};

Answer solve(const string &s, const string &t) {
	Answer ans = {0, 0, 0};
	size_t low = 1;
	size_t high = s.size();

	size_t x1, x2, m1, m2;
	x1 = 31;
	x2 = 119;
	m1 = 1000007;
	m2 = 1000009;

	while(low <= high) {
		bool match = false;
		size_t k = (low + high) / 2;
		
		std::map<size_t, size_t> hashes_1;
		std::map<size_t, size_t> hashes_2;	
		size_t h1, h2, multiplier1, multiplier2;

		multiplier1 = multiplier2 = 1;
		for(size_t i = 1; i <= k - 1; ++i) {
			multiplier1 = (multiplier1 * x1) % m1;
			multiplier2 = (multiplier2 * x2) % m2;
		}

		for(size_t i = 0; i + k <= s.size(); ++i) {
			if(i == 0) {
				h1 = h2 = 0;
				for(size_t i = 0; i < k; ++i) {
					h1 = (h1 * x1 + s[i]) % m1;
					h2 = (h2 * x2 + s[i]) % m2;
				}
			}
			else {
				size_t a = (multiplier1 * s[i - 1]) % m1;
				if(h1 >= a)
					h1 = h1 - a;
				else
					h1 = (h1 + m1 - a) % m1;
				h1 = (h1 * x1 + s[i + k - 1]) % m1;

				size_t b = (multiplier2 * s[i - 1]) % m2;
				if(h2 >= b)
					h2 = h2 - b;
				else
					h2 = (h2 + m2 - b) % m2;
				h2 = (h2 * x2 + s[i + k - 1]) % m2;
			}
			hashes_1.insert({h1, i});
			hashes_2.insert({h2, i});
		}
		for(size_t i = 0; i + k <= t.size(); ++i) {
			if(i == 0) {
				h1 = h2 = 0;
				for(size_t i = 0; i < k; ++i) {
					h1 = (h1 * x1 + t[i]) % m1;
					h2 = (h2 * x2 + t[i]) % m2;
				}
			}
			else {
				size_t a = (multiplier1 * t[i - 1]) % m1;
				if(h1 >= a)
					h1 = h1 - a;
				else
					h1 = (h1 + m1 - a) % m1;
				h1 = (h1 * x1 + t[i + k - 1]) % m1;

				size_t b = (multiplier2 * t[i - 1]) % m2;
				if(h2 >= b)
					h2 = h2 - b;
				else
					h2 = (h2 + m2 - b) % m2;
				h2 = (h2 * x2 + t[i + k - 1]) % m2;
			}
			if(hashes_1.find(h1) != hashes_1.end() && hashes_2.find(h2) != hashes_2.end() && hashes_1[h1] == hashes_2[h2]) {
				match = true;
				ans = {hashes_1[h1], i, k};
				break;
			}
		}

		if(match)
			low = k + 1;
		else
			high = k - 1;
	}

	return ans;
}

void test_solution() {
	string s, t;
	size_t l1 = 1 + rand() % 100000;
	size_t l2 = 1 + rand() % 100000;
	for(size_t i = 0; i < 100000; ++i)
		s.append(string(1, 'a' + rand() % 25));
	for(size_t i = 0; i < 100000; ++i)
		t.append(string(1, 'a' + rand() % 25));
	auto start = high_resolution_clock::now();
	auto ans = solve(s, t);
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(stop - start);
	std::cout << ans.i << " " << ans.j << " " << ans.len << "\n";
	std::cout << "Time taken: " << duration.count() << " ms\n";
}

int main() {
	//test_solution();
	ios_base::sync_with_stdio(false), cin.tie(0);
	string s, t;
	while (cin >> s >> t) {
		auto ans = solve(s, t);
		cout << ans.i << " " << ans.j << " " << ans.len << "\n";
	}
}
