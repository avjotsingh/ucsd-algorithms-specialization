#include <iostream>
#include <vector>
#include <cassert>

long long get_fibonacci_huge_naive(long long n, long long m) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current  = 1;

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
    }

    return current % m;
}

long long find_pisano_period(long long m) {
    long long previous = 0;
    long long current = 1;
    long long pisano_period;
    for(pisano_period = 1; pisano_period <= m * m; ++pisano_period) {
        long long tmp_previous = previous;
        previous = current;
        current = (tmp_previous + current) % m;
        if(current == 1 && previous == 0)
            break;
    }

    return pisano_period;
}

long long get_fibonacci_huge(long long n, long long m) {
    long long previous = 0;
    long long current  = 1;
    long long pisano_period = find_pisano_period(m);

    n %= pisano_period;
    if(n <= 1)
        return n;

    previous = 0;
    current = 1;
    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = (tmp_previous + current)  % m;
    }

    return current;
}

// void test_solution() {

//     assert(get_fibonacci_huge(9, 2) == 0);
//     assert(get_fibonacci_huge(239, 1000) == 161);
//     assert(get_fibonacci_huge(2816213588, 239) == 151);
//     assert(get_fibonacci_huge(100000000000000, 3) == 0);

//     int n_tests = 1000;
//     for(int i = 0; i < n_tests; ++i) {
//         int n = rand() % 20;
//         int m = rand() % 1000;
//         std::cout << "n: " << n << " m: " << m << std::endl;
//         auto a = get_fibonacci_huge(n, m);
//         auto b = get_fibonacci_huge_naive(n, m);
//         std::cout << a << ' ' << b << std::endl;
//         assert(a == b);
//     }

//     std::cout << "Tests passed..." << '\n';
// }

int main() {
    long long n, m;
    std::cin >> n >> m;
    //std::cout << get_fibonacci_huge_naive(n, m) << '\n';
    //test_solution();
    std::cout << get_fibonacci_huge(n, m) << '\n';

    return 0;
}
