#pragma once

#include <iterator>
#include <type_traits>
#include <vector>

namespace alg {

template <typename Iterator,
          typename ElementType = typename std::iterator_traits<Iterator>::value_type,
          typename LessPred = typename std::less<ElementType>,
          typename Container = std::vector<ElementType>>
void heap_sort(Iterator start, Iterator stop, LessPred less = LessPred{} ) {
    using std::swap;

    constexpr auto ROOT_ID = 0ull;
    auto parent = [](size_t n) { return n == ROOT_ID? n : ((n - 1) / 2); };
    auto child  = [](size_t n) { return 2 * n + 1; };

    auto distance = size_t(abs(std::distance(start, stop)));

    Container v;
    v.reserve(distance);

    auto it = start;

    while (it != stop) {
        if constexpr (std::is_move_constructible<ElementType>::value)
                v.emplace_back(std::move(*it));
        else
        v.push_back(*it);

        auto id = v.size() - 1;

        while (id != ROOT_ID) {
            auto p = parent(id);

            if (!less(v[p], v[id])) {
                swap(v[p], v[id]);
                id = p;
            }
            else
                break;
        }

        ++it;
    }

    it = start;

    while (it != stop) {
        if constexpr (std::is_move_constructible<ElementType>::value)
            *it = std::move(v.front());
        else
            *it = v.front();

        ++it;

        swap(v.front(), v.back());
        v.resize(v.size() - 1);

        auto id = ROOT_ID;

        while (true) {
            auto c = child(id);
            auto minimal = id;

            for (size_t i = c; i <= (c + 1) && (i < v.size()); ++i)
                if (less(v[i], v[minimal]))
                    minimal = i;

            if (id != minimal) {
                swap(v[minimal], v[id]);

                id = minimal;
            }
            else
                break;
        }
    }
}

}
