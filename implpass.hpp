/*
 * implpass.hpp             -- implementation pass functions builder
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

#ifndef __IMPLPASS_HPP_2012_05_08__
#define __IMPLPASS_HPP_2012_05_08__

#include "implorder.hpp"
#include "passtags.hpp"

namespace yarr {
    template <class impl_config, class category>
    struct impl_pass;

    template <class impl_config>
    struct impl_pass<impl_config, tags::pass::one_pass>:
        impl_order<impl_config, typename impl_config::order_config::category>
    {
        virtual typename impl_order<impl_config,
            typename impl_config::order_config::category
            >::result_type next() = 0;
        virtual void destroy(
            typename impl_config::allocator_type& allocator) = 0;
    };

    template <class impl_config>
    struct impl_pass<impl_config, tags::pass::swappable>:
        impl_pass<impl_config, tags::pass::one_pass>
    {
    };

    template <class impl_config>
    struct impl_pass<impl_config, tags::pass::forward>:
        impl_pass<impl_config, tags::pass::swappable>
    {
        virtual typename impl_pass<impl_config,
            tags::pass::swappable>::result_type front() const = 0;
        virtual void pop() = 0;
        virtual impl_pass<impl_config, tags::pass::swappable>* clone(
            typename impl_config::allocator_type& allocator) const = 0;
    };

    template <class impl_config>
    struct impl_pass<impl_config, tags::pass::double_ended>:
        impl_pass<impl_config, tags::pass::forward>
    {
        virtual typename impl_pass<impl_config,
            tags::pass::forward>::result_type back() const = 0;
        virtual void pop_back() = 0;
    };
}

#endif

