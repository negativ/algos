#pragma once

#include <iterator>
#include <limits>
#include <tuple>

#include <vector>

namespace alg {

namespace interval {

/**
 * Returns tuple (start, stop, max sum). Based on: https://e-maxx.ru/algo/maximum_average_segment
 */
template <typename Iterator, typename Value = typename std::iterator_traits<Iterator>::value_type>
std::tuple<Iterator, Iterator, Value> max_sum(Iterator start, Iterator stop) {
    Value s{}, ans{std::numeric_limits<Value>::min()};
    auto l = start,
         r = start,
         it = start,
         mpos = stop;

    while (it != stop) {
        s += *it;

        if (s > ans) {
            ans = s;

            if (mpos != stop)
                l = mpos + 1;

            r = it;
        }

        if (s < 0) {
            s = 0;
            mpos = it;
        }

        ++it;
    }

    return {l, r + 1, ans};
}

template <typename ForwIterator, typename RAIterator>
void z(ForwIterator start, ForwIterator stop, RAIterator out) {
    static_assert (std::is_same<typename std::iterator_traits<RAIterator>::iterator_category, std::random_access_iterator_tag>::value, "Out iterator must be random-access");

    auto len = std::abs(std::distance(start, stop));
    auto l = start, r = start;

    for (size_t i = 1; i < len; ++i) {
        if (r < start + i) {
            size_t count = 0;

            while (*(start + count) == *(start + i + count))
                ++count;

            *(out + i) = count;

            if (count > 0) { // Z-block found
                l = start + i;
                r = start + i + count - 1;
            }
        }
        else {
            auto j = (start + i) - l;
            auto b = r - (start + i) + 1;

            if (*(out + j) < b) // inside Z-block
                *(out + i) = *(out + j);
            else {
                size_t q = std::abs(std::distance(start, r + 1));
                for (; *(start + b++) == *(start + q); ++q);

                *(out + i) = q - i;
                l = start + i;
                r = start + q - 1;
            }
        }
    }
}

}

}
