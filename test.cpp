#include <iostream>
#include <cstddef>
#include <assert/stdexcept.hpp>
#include "range.hpp"
#include "configs/common.hpp"
#include "utils/size.hpp"
#include "utils/swap.hpp"

using namespace yarr;

int main()
{
    int v[] = {1, 2, 4, 6, 8};
    range<configs::array<const int&>, assert::stdexcept> r(v, v + sizeof v / sizeof v[0]);
    std::cout << r.next() << std::endl;
    range<configs::array<const int&>, assert::stdexcept> r2(r);
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
    std::cout << r[2] << std::endl;
    std::cout << r[3] << std::endl;
    /*range<common_configs::stream_input<result_config<tags::result::value, int> > > r3(v, v + sizeof v / sizeof v[0]);
    range<common_configs::stream_input<result_config<tags::result::value, int> > > r4;
    r3.swap(r4);
    std::cout << r4.next() << std::endl;
    std::swap(r4, r3);
    std::cout << size(r2) << std::endl;*/
}
