#include <iostream>

int get_fibonacci_last_digit(int n) {
    if (n <= 1)
        return n;

    int fib[3] = {0, 1};
    for(int i = 2; i <= n; ++i) {
        fib[2] = (fib[0] + fib[1]) % 10;
        fib[0] = fib[1];
        fib[1] = fib[2];
    }

    return fib[2];
}

int main() {
    int n;
    std::cin >> n;

    int c = get_fibonacci_last_digit(n);
    
    std::cout << c << '\n';
}
