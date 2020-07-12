#include <iostream>
#include <vector>
#include <cassert>
using std::vector;

long long get_fibonacci_partial_sum_naive(long long from, long long to) {
    long long sum = 0;

    long long current = 0;
    long long next  = 1;

    for (long long i = 0; i <= to; ++i) {
        if (i >= from) {
            sum += current;
        }

        long long new_current = next;
        next = next + current;
        current = new_current;
    }

    return sum % 10;
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

int find_pisano_period_sum(long long period) {
    long long previous = 0;
    long long current = 1;
    long long sum = 1;
    for(long long i = 0; i < period - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = (tmp_previous + current) % 10;
        sum = (sum + current) % 10;
    }

    return sum;
}

int get_fibonacci_partial_sum(long long from, long long to) {
    long long n = to - from + 1;
    long long pisano_period = find_pisano_period(10);
    from %= pisano_period;
    to = from + n % pisano_period - 1;

    long long n_cycles = n / pisano_period;
    long long sum = (n_cycles * find_pisano_period_sum(pisano_period)) % 10;

    long long current = 0;
    long long next = 1;
    for(long long i = 0; i <= to; ++i) {
        if(i >= from) {
            sum = (sum + current) % 10;
        }

        long long new_current = next;
        next = (next + current) % 10;
        current = new_current;
    }

    return sum;
}

void test_solution() {
    assert(get_fibonacci_partial_sum(3, 7) == 1);
    assert(get_fibonacci_partial_sum(10, 10) == 5);
    assert(get_fibonacci_partial_sum(10, 200) == 2);

    int n_test = 1000;
    for(int i = 0; i < n_test; ++i) {
        long long m = rand() % 10;
        long long n = rand() % 20 + 10;
        assert(get_fibonacci_partial_sum(m, n) == get_fibonacci_partial_sum_naive(m, n));
    }

    std::cout << "Tests passed..." << std::endl;
}


int main() {
    long long from, to;
    std::cin >> from >> to;
    //std::cout << get_fibonacci_partial_sum_naive(from, to) << '\n';
    //test_solution();
    std::cout << get_fibonacci_partial_sum(from, to) << '\n';

    return 0;
}
