#include <QCoreApplication>
#include <QtDebug>

#include "heap_sort.hpp"
#include "quick_sort.hpp"

#include <iostream>

std::vector<int> v{9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

template <typename Iterator>
void max_sum(std::vector<int>& n, Iterator start, Iterator stop) {
    using std::swap;
    using ElementType = typename std::iterator_traits<Iterator>::value_type;

    n[11] = -50;

    auto s = 0,
         answer = 0,
         min_pos = -1,
         answer_l = 0, answer_r = 0;

    for (std::size_t r = 0; r < n.size(); ++r) {
        s += *(start + r);

        if (s > answer) {
            answer = s;
            answer_l = min_pos + 1;
            answer_r = r;
        }

        if (s < 0) {
            s = 0;
            min_pos = r;
        }
    }

    std::cout << std::endl;
}

int main(int argc, char *argv[])
{
    namespace chrono = std::chrono;
    QCoreApplication a(argc, argv);

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

    max_sum(vec, begin(vec), end(vec));

    return EXIT_SUCCESS;
}
