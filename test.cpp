#include <iostream>
#include <cstdlib>
#include "range.hpp"
#include "config.hpp"
#include "iotypeconfig.hpp"
#include "passconfig.hpp"
#include "orderconfig.hpp"
#include "sizeconfig.hpp"
#include "resultconfig.hpp"
#include "iotypetags.hpp"
#include "passtags.hpp"
#include "ordertags.hpp"
#include "sizetags.hpp"
#include "resulttags.hpp"
#include "swap.hpp"

using namespace yarr;

int main()
{
    int v[] = {1, 2, 4, 6, 8};
    typedef yarr::range<range_config<
        pass_config<tags::pass::forward>,
        order_config<tags::order::sequential>,
        iotype_config<tags::iotype::input>,
        size_config<tags::size::unlimited>,
        result_config<tags::result::solid, const int&>
        > > range_type;
    range_type r(v, v + sizeof v / sizeof v[0]);
    std::cout << r.next() << std::endl;
    range_type r2(r);
    std::cout << r.next() << std::endl;
    r = r2;
    while (!r.empty()) {
        std::cout << r.front() << std::endl;
        r.pop();
    }
    std::cout << std::endl;
    r.swap(r2);
    std::cout << r.next() << std::endl;
    typedef yarr::range<range_config<
        pass_config<tags::pass::swappable>,
        order_config<tags::order::sequential>,
        iotype_config<tags::iotype::input>,
        size_config<tags::size::unlimited>,
        result_config<tags::result::solid, const int&>
        > > swappable_range_type;
    swappable_range_type r3(v, v + sizeof v / sizeof v[0]);
    swappable_range_type r4;
    r3.swap(r4);
    std::cout << r4.next() << std::endl;
    std::swap(r4, r3);
}
