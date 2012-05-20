#include <iostream>
#include <assert/stdexcept.hpp>
#include "utils/size.hpp"
#include "utils/swap.hpp"
#include "configs/common.hpp"
#include "container/array.hpp"
#include "rebind/rebind.hpp"
#include "concat/concat.hpp"

using namespace yarr;

int main()
{
    int v[] = {1, 2, 4, 6, 8};
    range<configs::double_ended_array<int&, size_t, size_t, tags::iotype::input_output>::type> c(container_range<assert::stdexcept>(v));
    std::cout << c.next() << std::endl;
    auto c2 = c;
    while (!c.empty()) {
        std::cout << c.front() << std::endl;
        c.pop();
    }
    std::cout << std::endl;
    auto c4 = c2;
    range<configs::array<int&>::type, assert::stdexcept> c3(rebind<configs::array<int&>::type>(c2.release()));
    while (!c3.empty()) {
        std::cout << c3.front() << std::endl;
        c3.pop();
    }
    std::cout << std::endl;
    auto c5 = c4;
    auto c6 = range<configs::linked_list<const int&>::type >(concat<configs::linked_list<const int&>::type >(c4.release(), c5.release()));
    while (!c6.empty()) {
        std::cout << c6.front() << std::endl;
        c6.pop();
    }
    std::cout << std::endl;
}
