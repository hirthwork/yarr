#include <yarr/vector.hpp>

#define BOOST_TEST_MODULE VectorRangeTest
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE(straight) {
    typedef yarr::vector::vector<int> range;
    int arr[] = {2, 3, 1, 5, 4};
    range r(std::vector<int>(arr, arr + sizeof arr / sizeof arr[0]));
    r.skip(2);
    r.truncate(1);
    BOOST_REQUIRE_EQUAL(r.next(), 1);
    BOOST_REQUIRE_EQUAL(r.size(), 1);
    BOOST_REQUIRE_EQUAL(r.next(), 5);
    BOOST_REQUIRE_EQUAL(r.empty(), true);
}

