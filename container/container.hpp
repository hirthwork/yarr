/*
 * container.hpp            -- container range implementation
 *
 * Copyright (C) 2012 Dmitry Potapov <potapov.d@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __CONTAINTER__CONTAINER_HPP__2012_05_13__
#define __CONTAINTER__CONTAINER_HPP__2012_05_13__

#include <cstddef>
#include <memory>

#include <assert/empty.hpp>

#include <configs/config.hpp>
#include <configs/iotype.hpp>
#include <configs/length.hpp>
#include <configs/order.hpp>
#include <configs/pass.hpp>
#include <configs/result.hpp>
#include <range.hpp>
#include <tags/iotype.hpp>
#include <tags/length.hpp>
#include <tags/order.hpp>
#include <tags/pass.hpp>
#include <tags/result.hpp>

#include "pass.hpp"

namespace yarr {
    namespace impls {
        namespace container {
            template <class Config, class InputIterator, class Allocator>
            struct base:
                pass<Config, InputIterator, Allocator,
                    typename Config::pass::category>
            {
                base(InputIterator first, InputIterator last,
                    const Allocator& allocator)
                    : pass<Config, InputIterator, Allocator,
                        typename Config::pass::category>(first, last,
                            allocator)
                {
                }

                void destroy() {
                    typedef base<Config, InputIterator, Allocator> type;
                    impl<Config>::template destroy<type, Allocator>(*this);
                }

                typename reinvented_wheels::enable_if<
                    is_base<tags::pass::forward,
                        typename Config::pass::category>::value,
                    base<Config, InputIterator, Allocator>*>::type
                clone() const {
                    typedef base<Config, InputIterator, Allocator> type;
                    typename Allocator::template rebind<type>::other
                        new_allocator(*this);
                    type* p = new_allocator.allocate(1);
                    try {
                        new_allocator.construct(p,
                            type(this->first, this->last, *this));
                        p->set_allocator(new_allocator);
                    } catch (...) {
                        new_allocator.deallocate(p, 1);
                        throw;
                    }
                    return p;
                }
            };
        }
    }

    template <class Assert, class Allocator, class T, std::size_t N>
    range<
        configs::range<
            configs::pass<tags::pass::double_ended>,
            configs::order<tags::order::random, std::ptrdiff_t>,
            configs::iotype<tags::iotype::input_output>,
            configs::length<tags::length::limited, std::size_t>,
            configs::result<tags::result::solid, T&> >,
        Assert>
    container_range(T (&array)[N], const Allocator& allocator = Allocator()) {
        typedef range<
            configs::range<
                configs::pass<tags::pass::double_ended>,
                configs::order<tags::order::random, std::ptrdiff_t>,
                configs::iotype<tags::iotype::input_output>,
                configs::length<tags::length::limited, std::size_t>,
                configs::result<tags::result::solid, T&> >, Assert> range_type;
        typedef impls::container::base<typename range_type::config_type, T*,
            Allocator> container;
        typename Allocator::template rebind<container>::other new_allocator(
            allocator);
        container* impl = new_allocator.allocate(1);
        try {
            new_allocator.construct(impl,
                container(array, array + N, allocator));
            impl->set_allocator(new_allocator);
            return range_type(impl);
        } catch (...) {
            new_allocator.deallocate(impl, 1);
            throw;
        }
    }

    template <class Assert, class T, std::size_t N>
    range<
        configs::range<
            configs::pass<tags::pass::double_ended>,
            configs::order<tags::order::random, std::ptrdiff_t>,
            configs::iotype<tags::iotype::input_output>,
            configs::length<tags::length::limited, std::size_t>,
            configs::result<tags::result::solid, T&> >,
        Assert>
    container_range(T (&array)[N]) {
        return container_range<Assert>(array, std::allocator<void*>());
    }

    template <class T, std::size_t N>
    range<
        configs::range<
            configs::pass<tags::pass::double_ended>,
            configs::order<tags::order::random, std::ptrdiff_t>,
            configs::iotype<tags::iotype::input_output>,
            configs::length<tags::length::limited, std::size_t>,
            configs::result<tags::result::solid, T&> >,
        assert::empty>
    container_range(T (&array)[N]) {
        return container_range<assert::empty>(array);
    }
}

#endif

