#include <algorithm>
#include <chrono>
#include <iostream>
#include <iterator>
#include <random>
#include <thread>

#include <gtest/gtest.h>

#include <heap_sort.hpp>
#include <quick_sort.hpp>

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
    v = std::vector<int>{1, 2};
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
    v = std::vector<int>{-2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 9};

    shuffle();

    alg::heap_sort(std::begin(v), std::end(v), std::greater<int>{});

    ASSERT_FALSE(std::is_sorted(std::begin(v), std::end(v)));
    ASSERT_TRUE(std::is_sorted(std::rbegin(v), std::rend(v)));
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

    void print() {
        for (const auto& x : v)
            std::cout << x << " ";
        std::cout << std::endl;
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

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
