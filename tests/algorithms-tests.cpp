#include <algorithm>
#include <chrono>
#include <iostream>
#include <iterator>
#include <random>
#include <thread>

#include <gtest/gtest.h>

#include <heap_sort.hpp>
#include <quick_sort.hpp>
#include <interval.hpp>

class HeapSortTest: public ::testing::Test {
protected:
    void shuffle() {
        std::seed_seq seed{reinterpret_cast<unsigned long>(&seed_function_ptr),
                           static_cast<unsigned long>(std::chrono::high_resolution_clock::now()
                                                       .time_since_epoch()
                                                       .count()),
                           reinterpret_cast<unsigned long>(&seed),
                           static_cast<unsigned long>(std::hash<std::thread::id>()(std::this_thread::get_id()))};
        std::mt19937 g(seed);


        std::shuffle(std::begin(v), std::end(v), g);
    }

    std::vector<int> v{-2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 9};

private:
    static void seed_function_ptr() {}
};

TEST_F(HeapSortTest, SortedWhenInitialized) {
    ASSERT_TRUE(std::is_sorted(std::begin(v), std::end(v)));
}

TEST_F(HeapSortTest, NotSortedAfterShuffle) {
    shuffle();

    ASSERT_FALSE(std::is_sorted(std::begin(v), std::end(v)));
}

TEST_F(HeapSortTest, ShuffleAndSort) {
    shuffle();

    alg::heap_sort(std::begin(v), std::end(v));

    ASSERT_TRUE(std::is_sorted(std::begin(v), std::end(v)));
}

TEST_F(HeapSortTest, SortSmallVector) {
    v = {1, 2};
    auto v1 = v;

    ASSERT_EQ(v, v1);

    alg::heap_sort(std::begin(v), std::end(v));

    ASSERT_EQ(v, v1);
}

TEST_F(HeapSortTest, SortVectorOfOnes) {
    v = std::vector<int>(100, 1);
    auto v1 = v;

    ASSERT_EQ(v, v1);

    alg::heap_sort(std::begin(v), std::end(v));

    ASSERT_EQ(v, v1);
}

TEST_F(HeapSortTest, SortDescending) {
    v = {-2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 9};

    shuffle();

    alg::heap_sort(std::begin(v), std::end(v), std::greater<int>{});

    ASSERT_FALSE(std::is_sorted(std::begin(v), std::end(v)));
    ASSERT_TRUE(std::is_sorted(std::rbegin(v), std::rend(v)));
}

TEST_F(HeapSortTest, SortEmpty) {
    v.clear();

    alg::heap_sort(std::begin(v), std::end(v));

    ASSERT_TRUE(v.empty());
}

TEST_F(HeapSortTest, SortSorted) {
    v = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto v1 = v;

    alg::heap_sort(std::begin(v), std::end(v));

    ASSERT_EQ(v, v1);
}

class QuickSortTest: public ::testing::Test {
protected:
    void shuffle() {
        std::seed_seq seed{reinterpret_cast<unsigned long>(&seed_function_ptr),
                           static_cast<unsigned long>(std::chrono::high_resolution_clock::now()
                                                       .time_since_epoch()
                                                       .count()),
                           reinterpret_cast<unsigned long>(&seed),
                           static_cast<unsigned long>(std::hash<std::thread::id>()(std::this_thread::get_id()))};
        std::mt19937 g(seed);


        std::shuffle(std::begin(v), std::end(v), g);
    }

    std::vector<int> v{-2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 9};

private:
    static void seed_function_ptr() {}
};

TEST_F(QuickSortTest, SortedWhenInitialized) {
    ASSERT_TRUE(std::is_sorted(std::begin(v), std::end(v)));
}

TEST_F(QuickSortTest, NotSortedAfterShuffle) {
    shuffle();

    ASSERT_FALSE(std::is_sorted(std::begin(v), std::end(v)));
}

TEST_F(QuickSortTest, ShuffleAndSort) {
    shuffle();

    alg::quick_sort(std::begin(v), std::end(v));

    ASSERT_TRUE(std::is_sorted(std::begin(v), std::end(v)));
}

TEST_F(QuickSortTest, SortSmallVector) {
    v = std::vector<int>{1, 2};
    auto v1 = v;

    ASSERT_EQ(v, v1);

    alg::quick_sort(std::begin(v), std::end(v));

    ASSERT_EQ(v, v1);
}

TEST_F(QuickSortTest, SortVectorOfOnes) {
    v = std::vector<int>(100, 1);
    auto v1 = v;

    ASSERT_EQ(v, v1);

    alg::quick_sort(std::begin(v), std::end(v));

    ASSERT_EQ(v, v1);
}

TEST_F(QuickSortTest, SortDescending) {
    v = std::vector<int>{-2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 9};

    shuffle();

    alg::quick_sort(std::begin(v), std::end(v), std::greater<int>{});

    ASSERT_FALSE(std::is_sorted(std::begin(v), std::end(v)));
    ASSERT_TRUE(std::is_sorted(std::rbegin(v), std::rend(v)));
}

TEST_F(QuickSortTest, SortEmpty) {
    v.clear();

    alg::quick_sort(std::begin(v), std::end(v));

    ASSERT_TRUE(v.empty());
}

TEST_F(QuickSortTest, SortSorted) {
    v = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto v1 = v;

    alg::quick_sort(std::begin(v), std::end(v));

    ASSERT_EQ(v, v1);
}

TEST(IntervalTest, ZeroInput) {
    std::vector<int> v = {0, 0, 0, 0, 0};

    auto [start, stop, val] = alg::interval::max_sum(std::begin(v), std::end(v));

    ASSERT_EQ(start, std::begin(v));
    ASSERT_EQ(stop,  std::begin(v) + 1);
    ASSERT_EQ(val, 0);
}

TEST(IntervalTest, ConstantFillInput) {
    for (auto i = 1; i < 100; ++i) {
        std::vector<int> v(100, i);

        auto [start, stop, val] = alg::interval::max_sum(std::begin(v), std::end(v));

        ASSERT_EQ(start, std::begin(v));
        ASSERT_EQ(stop,  std::end(v));
        ASSERT_EQ(val, size_t(i) * v.size());
    }

}

TEST(IntervalTest, Input) {
    std::vector<int> v{1, 2, 3, 4, -11, 5, 6, 7, 8};

    auto [start, stop, val] = alg::interval::max_sum(std::begin(v), std::end(v));

    ASSERT_EQ(start, std::begin(v) + 5);
    ASSERT_EQ(stop,  std::end(v));
    ASSERT_EQ(val, std::accumulate(start, stop, 0));
}

TEST(IntervalTest, Z_functionTest) {
    {
        std::string S = "abacaba";
        std::vector<int> ans{0, 0, 1, 0, 3, 0 ,1};
        std::vector<int> zs(S.size());
        alg::interval::z(std::begin(S), std::end(S), std::begin(zs));

        ASSERT_EQ(zs, ans);
    }
    {
        std::string S = "aaaaa";
        std::vector<int> ans{0, 4, 3, 2, 1};
        std::vector<int> zs(S.size());
        alg::interval::z(std::begin(S), std::end(S), std::begin(zs));

        ASSERT_EQ(zs, ans);
    }
    {
        std::string S = "aaabaab";
        std::vector<int> ans{0, 2, 1, 0, 2, 1, 0};
        std::vector<int> zs(S.size());
        alg::interval::z(std::begin(S), std::end(S), std::begin(zs));

        ASSERT_EQ(zs, ans);
    }
    {
        std::string S = "aabcaabxaaz";
        std::vector<int> ans{0, 1, 0, 0, 3, 1, 0, 0, 2, 1, 0};
        std::vector<int> zs(S.size());
        alg::interval::z(std::begin(S), std::end(S), std::begin(zs));

        ASSERT_EQ(zs, ans);
    }
    {
        std::string S = "abcdefgh";
        std::vector<int> ans{0, 0, 0, 0, 0, 0, 0, 0};
        std::vector<int> zs(S.size());
        alg::interval::z(std::begin(S), std::end(S), std::begin(zs));

        ASSERT_EQ(zs, ans);
    }
}

TEST(IntervalTest, Z_functionInvertedTest) {
    {
        std::string S = "abacaba";
        std::vector<int> ans{0, 0, 1, 0, 3, 0 ,1};
        std::vector<int> zs(S.size());
        alg::interval::z(std::rbegin(S), std::rend(S), std::begin(zs));

        ASSERT_EQ(zs, ans);
    }
    {
        std::string S = "aaaaa";
        std::vector<int> ans{0, 4, 3, 2, 1};
        std::vector<int> zs(S.size());
        alg::interval::z(std::rbegin(S), std::rend(S), std::begin(zs));

        ASSERT_EQ(zs, ans);
    }
    {
        std::string S = "baabaaa";
        std::vector<int> ans{0, 2, 1, 0, 2, 1, 0};
        std::vector<int> zs(S.size());
        alg::interval::z(std::rbegin(S), std::rend(S), std::begin(zs));

        ASSERT_EQ(zs, ans);
    }
    {
        std::string S = "zaaxbaacbaa";
        std::vector<int> ans{0, 1, 0, 0, 3, 1, 0, 0, 2, 1, 0};
        std::vector<int> zs(S.size());
        alg::interval::z(std::rbegin(S), std::rend(S), std::begin(zs));

        ASSERT_EQ(zs, ans);
    }
    {
        std::string S = "hgfedcba";
        std::vector<int> ans{0, 0, 0, 0, 0, 0, 0, 0};
        std::vector<int> zs(S.size());
        alg::interval::z(std::rbegin(S), std::rend(S), std::begin(zs));

        ASSERT_EQ(zs, ans);
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
