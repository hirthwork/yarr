/*
 * sequence.hpp             -- sequence range wrapper
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

#ifndef __SEQUENCE_HPP_2012_04_27__
#define __SEQUENCE_HPP_2012_04_27__

#include "impl.hpp"

namespace yarr {
    template <class impl_config, class InputIterator>
    class sequence_impl: public impl<impl_config> {
        InputIterator first;
        const InputIterator last;

    public:
        typedef sequence_impl<impl_config, InputIterator> this_type;

        sequence_impl(InputIterator first, InputIterator last)
            : first(first)
            , last(last)
        {
        }

        bool empty() const {
            return first == last;
        }

        typename impl<impl_config>::result_type next() {
            return *first++;
        }

        typename impl<impl_config>::result_type front() const {
            return *first;
        }

        void pop() {
            ++first;
        }

        this_type* clone(
            typename impl_config::allocator_type& allocator) const
        {
            typedef typename impl_config::allocator_type allocator_type;
            typename allocator_type::template rebind<this_type>::other
                new_allocator(allocator);
            this_type* p = new_allocator.allocate(1);
            try {
                new_allocator.construct(p, sequence_impl(first, last));
                allocator = new_allocator;
            } catch (...) {
                new_allocator.deallocate(p, 1);
            }
            return p;
        }

        void destroy(typename impl_config::allocator_type& allocator) {
            impl<impl_config>::template destroy<this_type>(allocator);
        }
    };
}

#endif

