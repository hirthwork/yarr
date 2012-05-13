#include <iostream>
#include <assert/stdexcept.hpp>
#include "utils/size.hpp"
#include "utils/swap.hpp"
#include "container/container.hpp"

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
    std::swap(c, c2);
    std::cout << c.next() << std::endl;
    std::cout << size(c) << std::endl;
    std::cout << c[2] << std::endl;
    std::cout << c[-2] << std::endl;
    std::cout << c[3] << std::endl;
}
