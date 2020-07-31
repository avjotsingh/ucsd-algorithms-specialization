#include <iostream>
#include <vector>

using namespace std;

vector<int> solve(int k, const string &text, const string &pattern) {
//	std::cout << text << " " << pattern << "\n";
	vector<int> pos;
	vector<size_t> thash_1(1 + text.size());
	vector<size_t> thash_2(1 + text.size());
	vector<size_t> phash_1(1 + pattern.size());
	vector<size_t> phash_2(1 + pattern.size());
	vector<size_t> powx_1(1 + pattern.size());
	vector<size_t> powx_2(1 + pattern.size());

	size_t x1 = 31;
	size_t x2 = 119;
	size_t m1 = 200007;
	size_t m2 = 200009;
//	std::cout << "beginning to solve...\n";
	thash_1[0] = 0;
	thash_2[0] = 0;
	for(size_t i = 1; i <= text.size(); ++i) {
		thash_1[i] = (thash_1[i - 1] * x1 + text[i - 1]) % m1;
		thash_2[i] = (thash_2[i - 1] * x2 + text[i - 1]) % m2;
//		std::cout << "i: " << i << " thash_1[i]: " << thash_1[i] << " thash_2[i]: " << thash_2[i] << "\n"; 
	}
	phash_1[0] = 0;
	phash_2[0] = 0;
	for(size_t i = 1; i <= pattern.size(); ++i) {
		phash_1[i] = (phash_1[i - 1] * x1 + pattern[i - 1]) % m1;
		phash_2[i] = (phash_2[i - 1] * x2 + pattern[i - 1]) % m2;
//		std::cout << "i: " << i << " phash_1[i]: " << phash_1[i] << " phash_2[i]: " << phash_2[i] << "\n";
	}
	powx_1[0] = 1;
	powx_2[0] = 1;
	for(size_t i = 1; i <= pattern.size(); ++i) {
		powx_1[i] = (powx_1[i - 1] * x1) % m1;
		powx_2[i] = (powx_2[i - 1] * x2) % m2;
//		std::cout << "i: " << i << " powx_1[i]: " << powx_1[i] << " powx_2[i]: " << powx_2[i] << "\n";
	}

	for(size_t i = 1; i <= text.size() - pattern.size() + 1; ++i) {
//		std::cout << "i: " << i << '\n';
		//find the number of mismatches between the two strings.
		size_t n_mismatches = 0;
		size_t start_index = 1;
		while(n_mismatches <= k && start_index <= pattern.size()) {
			size_t low = start_index, high = pattern.size();
			while(low <= high) {
				size_t mid = (low + high) / 2;
				//compare hashes for (mid - low + 1) leftmost characters i.e. pattern(low, mid) and text(i + low - 1, i + mid - 1)
				size_t L = mid - low + 1;
				size_t p1 = (powx_1[L] * phash_1[low - 1]) % m1;
				p1 = (phash_1[mid] >= p1) ? phash_1[mid] - p1 : phash_1[mid] + m1 - p1;

				size_t p2 = (powx_2[L] * phash_2[low - 1]) % m2;
				p2 = (phash_2[mid] >= p2) ? phash_2[mid] - p2 : phash_2[mid] + m2 - p2;

				size_t t1 = (powx_1[L] * thash_1[i + low - 2]) % m1;
				t1 = (thash_1[i + mid - 1] >= t1) ? thash_1[i + mid - 1] - t1 : thash_1[i + mid - 1] + m1 - t1;

				size_t t2 = (powx_2[L] * thash_2[i + low - 2]) % m2;
				t2 = (thash_2[i + mid - 1] >= t2) ? thash_2[i + mid - 1] - t2 : thash_2[i + mid - 1] + m2 - t2;

//				std::cout << "low: " << low << " high: " << high << " p1: " << p1 << " t1: " << t1 << " p2: " << p2 << " t2: " << t2 << "\n";

				if(p1 == t1 && p2 == t2)
					low = mid + 1;
				else
					high = mid - 1;
			}

			if(low == pattern.size() + 1) {
				break;
			}
			else {
				++n_mismatches;
				start_index = low + 1;
			}
//			std::cout << "mismatch pos: " << low << " n_mismatches: " << n_mismatches << " pattern.size(): " << pattern.size() << "\n";
			
		}

		if(n_mismatches <= k)
			pos.push_back(i - 1);
	}

	return pos;
}

int main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	int k;
	string t, p;
	while (cin >> k >> t >> p) {
		auto a = solve(k, t, p);
		cout << a.size();
		for (int x : a)
			cout << " " << x;
		cout << "\n";
	}

	return 0;
}
