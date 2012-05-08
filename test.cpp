#include <iostream>
#include <cstddef>
#include "range.hpp"
#include "config.hpp"
#include "commonconfigs.hpp"
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
#include "size.hpp"
#include "swap.hpp"

using namespace yarr;

int main()
{
    int v[] = {1, 2, 4, 6, 8};
    range<common_configs::array<const int&> > r(v, v + sizeof v / sizeof v[0]);
    std::cout << r.next() << std::endl;
    range<common_configs::array<const int&> > r2(r);
    std::cout << r.next() << std::endl;
    r = r2;
    while (!r.empty()) {
        std::cout << r.front() << std::endl;
        r.pop();
    }
    std::cout << std::endl;
    r.swap(r2);
    std::cout << r.next() << std::endl;
    std::cout << size(r) << std::endl;
    /*range<common_configs::stream_input<result_config<tags::result::value, int> > > r3(v, v + sizeof v / sizeof v[0]);
    range<common_configs::stream_input<result_config<tags::result::value, int> > > r4;
    r3.swap(r4);
    std::cout << r4.next() << std::endl;
    std::swap(r4, r3);
    std::cout << size(r2) << std::endl;*/
}
