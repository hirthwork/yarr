/*
 * range.hpp                -- yet another reinvented range
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

#ifndef __RANGE_HPP_2012_04_26__
#define __RANGE_HPP_2012_04_26__

#include <memory>

#include <assert/empty.hpp>

#include "config.hpp"
#include "impl.hpp"
#include "rangebase.hpp"
#include "sequence.hpp"

namespace yarr {
    template <class RangeConfig, class Assert = assert::empty>
    struct range: range_base<impl<configs::complete<RangeConfig, Assert> > >
    {
        typedef configs::complete<RangeConfig, Assert> config_type;
        typedef range_base<impl<config_type> > range_base_type;
        typedef typename range_base_type::impl_type impl_type;

        typedef Assert assert_type;

        range(impl_type* impl)
            : range_base_type(impl)
        {
        }

        // TODO: remove all this shit and <memory> inclusion
        template <class InputIterator>
        range(InputIterator first, InputIterator last)
            : range_base_type(
                make_sequence<std::allocator<void*> >(first, last))
        {
        }

        template <class Allocator, class InputIterator>
        range(InputIterator first, InputIterator last,
            const Allocator& allocator = Allocator())
            : range_base_type(make_sequence(first, last, allocator))
        {
        }

        template <class Allocator, class InputIterator>
        static impl_type* make_sequence (InputIterator first,
            InputIterator last, const Allocator& allocator = Allocator())
        {
            if (first == last) {
                return 0;
            } else {
                typedef sequence_impl<config_type, InputIterator, Allocator>
                    sequence;
                typename Allocator::template rebind<sequence>::other
                    new_allocator(allocator);
                sequence* impl = new_allocator.allocate(1);
                try {
                    new_allocator.construct(impl, sequence(first, last, allocator));
                    impl->set_allocator(new_allocator);
                    return impl;
                } catch (...) {
                    new_allocator.deallocate(impl, 1);
                    throw;
                }
            }
        }
    };
}

#endif

