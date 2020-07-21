#include <iostream>
#include <cassert>

int fibonacci_sum_naive(long long n) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current  = 1;
    long long sum      = 1;

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
        sum += current;
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

int fibonacci_sum(long long n) {
    if(n <= 1)
        return n;

    long long pisano_period = find_pisano_period(10);
    long long n_cycles = n / pisano_period;
    n %= pisano_period;

    // std::cout << "cycles: " << n_cycles << std::endl;
    // std::cout << "remainder: " << n << std::endl;
    // std::cout << "pisano period: " << pisano_period << std::endl;

    long long sum = (n_cycles*find_pisano_period_sum(pisano_period)) % 10;
    long long current = 0;
    long long next = 1;
    for(long long i = 0; i <= n; ++i) {
        sum = (sum + current) % 10;
        long long new_current = next;
        next = (current + next) % 10;
        current = new_current;
    }

    return sum;
}

void test_solution() {
    assert(fibonacci_sum(3) == 4);
    assert(fibonacci_sum(100) == 5);

    int n_test = 1000;
    for(int i = 0; i < n_test; ++i) {
        long long n = rand() % 20;
        assert(fibonacci_sum(n) == fibonacci_sum_naive(n));
    }

    std::cout << "Tests passed..." << std::endl;
}

int main() {
    long long n = 0;
    std::cin >> n;
    //test_solution();
    std::cout << fibonacci_sum(n);

    return 0;
}
