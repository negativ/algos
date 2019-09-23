#pragma once

#include <algorithm>
#include <iterator>

namespace alg {

template <typename Iterator,
          typename ElementType,
          typename LessPred>
void __quick_sort_helper(Iterator start, Iterator stop, LessPred lesseq) {
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

            swap(*i, *peavot);

            return i;
        };

        auto p = partition(start, stop);

        __quick_sort_helper<Iterator, ElementType, LessPred>(start, p, lesseq);
        __quick_sort_helper<Iterator, ElementType, LessPred>(p + 1, stop, lesseq);
    }
}

/**
 *  Warning! Works great on randomly shuffled data, on sorted data regresses to O(N^2).
 *  Use std::random_shuffle for data if not sure that is random.
 */
template <typename Iterator,
          typename ElementType = typename std::iterator_traits<Iterator>::value_type,
          typename LessPred = typename std::less<ElementType>>
void quick_sort(Iterator start, Iterator stop, LessPred less = LessPred{}) {
    __quick_sort_helper<Iterator, ElementType, LessPred> (start, stop, less);
}

}
