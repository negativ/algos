#pragma once

#include <algorithm>
#include <iterator>
#include <random>

namespace alg {

template <typename Iterator,
          typename ElementType,
          typename LessEqPred>
void __quick_sort_helper(Iterator start, Iterator stop, LessEqPred lesseq) {
    using std::swap;

    const auto distance = abs(std::distance(start, stop));

    if (distance > 1) {
        auto partition = [lesseq](Iterator start, Iterator stop) {
            auto peavot = stop - 1;
            auto i = start;

            while (start != stop) {
                if (lesseq(*start, *peavot)) {
                    swap(*start, *i);
                    ++i;
                }

                ++start;
            }

            return i;
        };

        auto p = partition(start, stop);

        __quick_sort_helper<Iterator, ElementType, LessEqPred>(start, p - 1, lesseq);
        __quick_sort_helper<Iterator, ElementType, LessEqPred>(p, stop, lesseq);
    }
}

template <typename Iterator,
          typename ElementType = typename std::iterator_traits<Iterator>::value_type,
          typename LessEqPred = typename std::less_equal<ElementType>>
void quick_sort(Iterator start, Iterator stop, LessEqPred lesseq = LessEqPred{}) {
    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(start, stop, g);

    __quick_sort_helper<Iterator, ElementType, LessEqPred> (start, stop, lesseq);
}

}
