#include <iostream>
#include <cassert>

int fibonacci_sum_squares_naive(long long n) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current  = 1;
    long long sum      = 1;

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
        sum += current * current;
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
    long long current = 0;
    long long next = 1;
    long long sum = 0;
    for(int i = 0; i < period; ++i) {
        sum = (sum + (current*current) % 10) % 10;
        //std::cout << "sq: " << current * current << std::endl;
        long long new_current = next;
        next = (next + current) % 10;
        current = new_current;
    }

    return sum;
}

int fibonacci_sum_squares(long long n) {
    if(n <= 1)
        return n;

    long long pisano_period = find_pisano_period(10);
    long long n_cycles = n / pisano_period;
    n %= pisano_period;

    long long sum = (n_cycles * find_pisano_period_sum(pisano_period)) % 10;
    long long current = 0;
    long long next = 1;
    for(int i = 0; i <= n; ++i) {
        sum = (sum + (current*current) % 10) % 10;
        long long new_current = next;
        next = (next + current) % 10;
        current = new_current;
    }

    return sum;
}

void test_solution() {
    assert(fibonacci_sum_squares(7) == 3);
    assert(fibonacci_sum_squares(73) == 1);
    assert(fibonacci_sum_squares(1234567890) == 0);

    int n_tests = 1000;
    for(int i = 0; i < n_tests; ++i) {
        long long n = rand() % 20;
        assert(fibonacci_sum_squares(n) == fibonacci_sum_squares_naive(n));
    }

    std::cout << "Tests passed..." << std::endl;
}

int main() {
    long long n = 0;
    std::cin >> n;
    //std::cout << fibonacci_sum_squares_naive(n);
    //test_solution();
    std::cout << fibonacci_sum_squares(n) << std::endl;

    return 0;
}
