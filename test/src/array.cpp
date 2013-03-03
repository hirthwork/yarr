#include <yarr/array.hpp>

#define BOOST_TEST_MODULE ArrayRangeTest
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE(straight) {
    typedef yarr::array::array<int> range;
    int arr[] = {2, 3, 1, 5, 4};
    range r(arr);
    BOOST_REQUIRE_EQUAL(r.next(), 2);
    BOOST_REQUIRE_EQUAL(r.next(), 3);
    BOOST_REQUIRE_EQUAL(r.next(), 1);
    BOOST_REQUIRE_EQUAL(r.size(), 2);
    BOOST_REQUIRE_EQUAL(r.next(), 5);
    BOOST_REQUIRE_EQUAL(r.next(), 4);
    BOOST_REQUIRE_EQUAL(r.empty(), true);
}

