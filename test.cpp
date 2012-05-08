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

using namespace yarr;

int main()
{
    int v[] = {1, 2, 4, 6, 8};
    yarr::range<range_config<
        pass_config<tags::pass::forward>,
        order_config<tags::order::sequental>,
        iotype_config<tags::iotype::input>,
        size_config<tags::size::unlimited>,
        result_config<tags::result::solid, const int&>
        > > r(v, v + sizeof v / sizeof v[0]);
    while (!r.empty()) {
        std::cout << r.front() << std::endl;
        r.pop();
    }
}
