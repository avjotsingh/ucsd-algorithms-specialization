#include <iostream>
#include <map>
#include <chrono>
using namespace std;
using namespace std::chrono;

// #define x1 31
// #define x2 119
// #define m1 1000000007
// #define m2 1000000009

struct Answer {
	long long i, j, len;
};

// inline long long hash_1(const string &s) {
// 	long long hash = 0;
// 	for(long long i = 0; i < s.size(); ++i) {
// 		hash = (hash * x1 + s[i]) % m1;
// 	}
// 	return hash;
// }

// inline long long update_hash1(long long h, long long m, char a, char b) {
// 	h = h - (m * a) % m1;
// 	if(h < 0)
// 		h += m1;
// 	h = (h * x1 + b) % m1;
// 	return h;
// }

// inline long long hash_2(const string &s) {
// 	long long hash = 0;
// 	for(long long i = 0; i < s.size(); ++i) {
// 		hash = (hash * x2 + s[i]) % m2;
// 	}
// 	return hash;
// }

// inline long long update_hash2(long long h, long long m, char a, char b) {
// 	h = h - (m * a) % m2;
// 	if(h < 0)
// 		h += m2;
// 	h = (h * x2 + b) % m2;
// 	return h;
// }

Answer solve(const string &s, const string &t) {
	Answer ans = {0, 0, 0};
	long long low = 1;
	long long high = s.size();

	long long x1, x2, m1, m2;
	x1 = rand() % 1000000000;
	x2 = rand() % 1000000000;
	m1 = 10000000007;
//	m2 = 1000000009;

	while(low <= high) {
		bool match = false;
		long long k = (low + high) / 2;
		
		std::map<long long, long long> hashes_1;
//		std::map<long long, long long> hashes_2;	
		long long h1, h2, mult1, mult2;

		mult1 = mult2 = 1;
		for(long long i = 1; i <= k - 1; ++i) {
			mult1 = (mult1 * x1) % m1;
//			mult2 = (mult2 * x2) % m2;
		}

//		std::cout << "k: " << k <<'\n';
		for(long long i = 0; i + k <= s.size(); ++i) {
			// if(i == 0) {
			// 	h1 = hash_1(s.substr(0, k));
			// 	h2 = hash_2(s.substr(0, k));
			// }
			// else {
			if(i == 0) {
				h1 = h2 = 0;
				for(long long i = 0; i < k; ++i) {
					h1 = (h1 * x1 + s[i]) % m1;
//					h2 = (h2 * x2 + s[i]) % m2;
				}
			}
			else {
				h1 = h1 - (mult1 * s[i - 1]) % m1;
				if(h1 < 0)
					h1 += m1;
				h1 = (h1 * x1 + s[i + k - 1]) % m1;

				// h2 = h2 - (mult2 * s[i - 1]) % m2;
				// if(h2 < 0)
				// 	h2 += m2;
				// h2 = (h2 * x2 + s[i + k - 1]) % m2;
			}
			//h1 = update_hash1(h1, mult1, s[i - 1], s[i + k - 1]);
			//h2 = update_hash2(h2, mult2, s[i - 1], s[i + k - 1]);
			//}

//			std::cout << s << " i: " << i << " h1: " << h1 << " h2: " << h2 << '\n';
			hashes_1.insert({h1, i});
//			hashes_2.insert({h2, i});
		}

		
		for(long long i = 0; i + k <= t.size(); ++i) {
			// if(i == 0) {
			// 	h1 = hash_1(t.substr(0, k));
			// 	h2 = hash_2(t.substr(0, k));
			// }
			// else {
			//h1 = update_hash1(h1, mult1, t[i - 1], t[i + k - 1]);
			//h2 = update_hash2(h2, mult2, t[i - 1], t[i + k - 1]);
			//}
			if(i == 0) {
				h1 = h2 = 0;
				for(long long i = 0; i < k; ++i) {
					h1 = (h1 * x1 + t[i]) % m1;
//					h2 = (h2 * x2 + t[i]) % m2;
				}
			}
			else {

				h1 = h1 - (mult1 * t[i - 1]) % m1;
				if(h1 < 0)
					h1 += m1;
				h1 = (h1 * x1 + t[i + k - 1]) % m1;

				// h2 = h2 - (mult2 * t[i - 1]) % m2;
				// if(h2 < 0)
				// 	h2 += m2;
				// h2 = (h2 * x2 + t[i + k - 1]) % m2;
			}
//			std::cout << t << " i: " << i << " h1: " << h1 << " h2: " << h2 << '\n';
			if(hashes_1.find(h1) != hashes_1.end()){//} && hashes_2.find(h2) != hashes_2.end() && hashes_1[h1] == hashes_2[h2]) {
				match = true;
				ans = {hashes_1[h1], i, k};
//				std::cout << "breaking...\n";
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
	for(size_t i = 0; i < l1; ++i)
		s.append(string(1, 'a' + rand() % 25));
	for(size_t i = 0; i < l2; ++i)
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
