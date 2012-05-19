#include <iostream>
#include <assert/stdexcept.hpp>
#include "utils/size.hpp"
#include "utils/swap.hpp"
#include "configs/common.hpp"
#include "container/array.hpp"
#include "rebind/rebind.hpp"

using namespace yarr;

int main()
{
    int v[] = {1, 2, 4, 6, 8};
    auto c = container_range<assert::stdexcept>(v);
    std::cout << c.next() << std::endl;
    auto c2 = c;
    while (!c.empty()) {
        std::cout << c.front() << std::endl;
        c.pop();
    }
    std::cout << std::endl;
    range<configs::array<int&>::type, assert::stdexcept> c3(rebind<configs::array<int&>::type>(c2.release()));
    while (!c3.empty()) {
        std::cout << c3.front() << std::endl;
        c3.pop();
    }
    std::cout << std::endl;
}
