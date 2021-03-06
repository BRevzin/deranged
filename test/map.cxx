#include "catch.hpp"
#include <deranged/algorithm.h>
#include <deranged/from_range.h>
#include <deranged/iota.h>

TEST_CASE("map basics") {
    std::vector<int> v = {1, 2, 3, 4, 5};
    std::vector<int> exp = {1, 4, 9, 16, 25};
    using namespace drng;

    auto squares = from_range(v)
                 ._(map, [](int i){ return i * i; });

    STATIC_REQUIRE(drng::forward_drange<decltype(squares)>);
    STATIC_REQUIRE(drng::sized_drange<decltype(squares)>);
    STATIC_REQUIRE(drng::finite_drange<decltype(squares)>);
    STATIC_REQUIRE_FALSE(drng::infinite_drange<decltype(squares)>);

    CHECK(squares.size() == 5);
    CHECK(equal(squares, from_range(exp)));
    CHECK(squares._(equal, from_range(exp)));

    squares.pop_front();
    CHECK(squares.size() == 4);
    CHECK(squares.front() == 4);
}

TEST_CASE("infinite map") {
    auto all_squares = drng::iota(0)._(drng::map, [](int i){ return i*i; });

    STATIC_REQUIRE(drng::forward_drange<decltype(all_squares)>);
    STATIC_REQUIRE_FALSE(drng::sized_drange<decltype(all_squares)>);
    STATIC_REQUIRE(drng::infinite_drange<decltype(all_squares)>);
}
