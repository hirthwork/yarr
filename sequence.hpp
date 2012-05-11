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

#include <iterator>
#include "impl.hpp"

namespace yarr {
    template <class Config, class InputIterator, class Allocator>
    class sequence_impl: public impl<Config>, Allocator {
        InputIterator first;
        const InputIterator last;

    public:
        typedef sequence_impl<Config, InputIterator, Allocator> this_type;

        sequence_impl(InputIterator first, InputIterator last,
            const Allocator& allocator)
            : Allocator(allocator)
            , first(first)
            , last(last)
        {
        }

        void set_allocator(const Allocator& allocator) {
            Allocator::operator =(allocator);
        }

        bool empty() const {
            return first == last;
        }

        typename Config::size::size_type size() const {
            return std::distance(first, last);
        }

        typename impl<Config>::result_type next() {
            return *first++;
        }

        typename impl<Config>::result_type front() const {
            return *first;
        }

        typename impl<Config>::result_type operator [](
            typename impl<Config>::pos_type pos) const
        {
            return *(first + pos);
        }

        void advance(typename impl<Config>::pos_type n) {
            std::advance(first, n);
        }

        void pop() {
            ++first;
        }

        this_type* clone() const
        {
            typename Allocator::template rebind<this_type>::other
                new_allocator(*this);
            this_type* p = new_allocator.allocate(1);
            try {
                new_allocator.construct(p, sequence_impl(first, last, *this));
                // TODO: simpler?
                *static_cast<Allocator*>(p) = new_allocator;
            } catch (...) {
                new_allocator.deallocate(p, 1);
                throw;
            }
            return p;
        }

        void destroy() {
            impl<Config>::template destroy<this_type, Allocator>(*this);
        }
    };
}

#endif

