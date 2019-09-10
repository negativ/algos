#include <chrono>
#include <iostream>

#include "heap_sort.hpp"
#include "quick_sort.hpp"
#include "interval.hpp"

int main(int, char *[])
{
    namespace chrono = std::chrono;
    std::vector<int> v{9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

    alg::heap_sort(std::begin(v), std::end(v));

    for (const auto & x : v)
        std::cout << x << " ";

    std::cout << std::endl;

    alg::quick_sort(std::begin(v), std::end(v));

    std::random_device rd;
    std::mt19937 g{rd()};
    auto duration = chrono::steady_clock::now().time_since_epoch();
    auto mcs = chrono::duration_cast<chrono::microseconds>(duration).count();

    g.seed(mcs & 0xFFFFFFFF);

    std::uniform_int_distribution<int> dist(-2, 10);

    std::vector<int> vec(20);
    std::generate(begin(vec), end(vec), [&]() { return dist(g); });

    auto [b, e, m] = alg::interval::max_sum(begin(vec), end(vec));

    while (b != e)
        std::cout << *b++ << " ";

    std::cout << " = " << m << std::endl;

    return EXIT_SUCCESS;
}
