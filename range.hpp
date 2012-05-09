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
    template <class RangeConfig, class Assert = assert::empty,
        class Allocator = std::allocator<void*> >
    struct range:
        range_base<impl<configs::complete<RangeConfig, Assert, Allocator> >,
            Allocator>
    {
        typedef configs::complete<RangeConfig, Assert, Allocator> config_type;
        typedef range_base<impl<config_type>, Allocator> range_base_type;

        typedef Assert assert_type;

        range(const Allocator& allocator = Allocator())
            : range_base_type(allocator)
        {
        }

        template <class InputIterator>
        range(InputIterator first, InputIterator last,
            const Allocator& allocator = Allocator())
            : range_base_type(allocator)
        {
            if (first != last) {
                typedef sequence_impl<config_type, InputIterator> sequence;
                typedef typename range_base_type::allocator_type
                    allocator_type;
                typename allocator_type::template rebind<sequence>::other
                    new_allocator(*this);
                sequence* impl = new_allocator.allocate(1);
                try {
                    new_allocator.construct(impl, sequence(first, last));
                    allocator_type::operator =(new_allocator);
                    this->set(impl);
                } catch (...) {
                    new_allocator.deallocate(static_cast<sequence*>(impl), 1);
                    throw;
                }
            }
        }
    };
}

#endif

