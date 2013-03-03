#include <utility>

#include <yarr/rational.hpp>

#define BOOST_TEST_MODULE BacktraceTest
#include <boost/test/included/unit_test.hpp>

namespace std {
    template <class CharT, class T, class U>
    basic_ostream<CharT>& operator <<(basic_ostream<CharT>& out,
        const pair<T, U>& p)
    {
        return out << p.first << '/' << p.second;
    }
}

BOOST_AUTO_TEST_CASE(straight) {
    typedef yarr::rational::rational<> range;
    range r;
    BOOST_REQUIRE_EQUAL(r.next(), std::make_pair(1u, 2u));
    BOOST_REQUIRE_EQUAL(r.next(), std::make_pair(1u, 3u));
    BOOST_REQUIRE_EQUAL(r.next(), std::make_pair(2u, 3u));
    BOOST_REQUIRE_EQUAL(r.next(), std::make_pair(3u, 4u));
    BOOST_REQUIRE_EQUAL(r.next(), std::make_pair(1u, 4u));
    BOOST_REQUIRE_EQUAL(r.next(), std::make_pair(1u, 5u));
    BOOST_REQUIRE_EQUAL(r.next(), std::make_pair(2u, 5u));
    BOOST_REQUIRE_EQUAL(r.next(), std::make_pair(3u, 5u));
    BOOST_REQUIRE_EQUAL(r.next(), std::make_pair(4u, 5u));
    BOOST_REQUIRE_EQUAL(r.next(), std::make_pair(5u, 6u));
}

struct rational {
    const char num;
    const char den;

    rational(char num, char den)
        : num(num)
        , den(den)
    {
    }

    bool operator ==(rational rhs) const {
        return num == rhs.num && den == rhs.den;
    }

    friend std::ostream& operator <<(std::ostream& out, rational r) {
        return out << '(' << r.num << '/' << r.den << ')';
    }
};

BOOST_AUTO_TEST_CASE(copy) {
    typedef yarr::rational::rational<char, rational> range;
    range r;
    BOOST_REQUIRE_EQUAL(r.next(), rational(1, 2));
    range r2(r);
    BOOST_REQUIRE_EQUAL(r.next(), r2.next());
    r2 = r;
    BOOST_REQUIRE_EQUAL(r.next(), r2.next());
    BOOST_REQUIRE_EQUAL(r2.next(), rational(3, 4));
}

