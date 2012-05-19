/*
 * pass.hpp                 -- implementation pass functions builder
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

#ifndef __IMPLS__PASS_HPP__2012_05_08__
#define __IMPLS__PASS_HPP__2012_05_08__

#include <tags/pass.hpp>

#include "order.hpp"

namespace yarr {
    namespace impls {
        template <class Config, class Category>
        struct pass;

        template <class Config>
        struct pass<Config, tags::pass::one_pass>:
            order<Config, typename Config::order::category>
        {
            virtual typename order<Config,
                typename Config::order::category>::result_type
            next() = 0;

            virtual void destroy() = 0;
        };

        template <class Config>
        struct pass<Config, tags::pass::swappable>:
            pass<Config, tags::pass::one_pass>
        {
        };

        template <class Config>
        struct impl;

        template <class Config>
        struct pass<Config, tags::pass::forward>:
            pass<Config, tags::pass::swappable>
        {
            virtual typename pass<Config, tags::pass::swappable>::result_type
            front() const = 0;

            virtual void pop() = 0;

            virtual impl<Config>* clone() const = 0;
        };

        template <class Config>
        struct pass<Config, tags::pass::double_ended>:
            pass<Config, tags::pass::forward>
        {
            virtual typename pass<Config, tags::pass::forward>::result_type
            prev() = 0;

            virtual typename pass<Config, tags::pass::forward>::result_type
            back() const = 0;

            virtual void pop_back() = 0;
        };
    }
}

#endif

