#pragma once

#include <iterator>
#include <tuple>

namespace alg {

namespace interval {

/**
 * Returns tuple (start, stop, max sum). Based on: https://e-maxx.ru/algo/maximum_average_segment
 */
template <typename Iterator, typename Value = typename std::iterator_traits<Iterator>::value_type>
std::tuple<Iterator, Iterator, Value> max_sum(Iterator start, Iterator stop) {
    Value s{}, ans{};
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

}

}
