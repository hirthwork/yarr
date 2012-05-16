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

#include <tags/pass.hpp>

#include "pass.hpp"

namespace yarr {
    namespace impls {
        namespace container {
            template <class Config, class InputIterator, class Allocator>
            struct container:
                pass<Config, InputIterator, Allocator,
                    typename Config::pass::category>
            {
                container(InputIterator first, InputIterator last,
                    const Allocator& allocator)
                    : pass<Config, InputIterator, Allocator,
                        typename Config::pass::category>(first, last,
                            allocator)
                {
                }

                void destroy() {
                    typedef container<Config, InputIterator, Allocator> type;
                    impl<Config>::template destroy<type, Allocator>(*this);
                }

                typename reinvented_wheels::enable_if<
                    is_base<tags::pass::forward,
                        typename Config::pass::category>::value,
                    container<Config, InputIterator, Allocator>*>::type
                clone() const {
                    typedef container<Config, InputIterator, Allocator> type;
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
}

#endif

