#include <yarr/list.hpp>

#define BOOST_TEST_MODULE ListRangeTest
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE(straight) {
    typedef yarr::list::list<int> range;
    int arr[] = {2, 3, 1, 5, 4};
    std::list<int> list(arr, arr + sizeof arr / sizeof arr[0]);
    range r(list);
    BOOST_REQUIRE_EQUAL(r.next(), 2);
    BOOST_REQUIRE_EQUAL(r.next(), 3);
    BOOST_REQUIRE_EQUAL(r.next(), 1);
    BOOST_REQUIRE_EQUAL(r.next(), 5);
    BOOST_REQUIRE_EQUAL(r.next(), 4);
    BOOST_REQUIRE_EQUAL(r.empty(), true);
}

