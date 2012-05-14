/*
 * result.hpp               -- range function for result tags
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

#ifndef __RANGES__RESULT_HPP__2012_05_07__
#define __RANGES__RESULT_HPP__2012_05_07__

#include <impls/holder.hpp>
#include <tags/result.hpp>

namespace yarr {
    namespace ranges {
        template <class Impl, class Category>
        struct result;

        template <class Impl>
        struct result<Impl, tags::result::value>: impls::holder<Impl>
        {
            typedef typename Impl::result_type result_type;

            explicit result(Impl* impl)
                : impls::holder<Impl>(impl)
            {
            }
        };

        template <class Impl>
        struct result<Impl, tags::result::reference>:
            result<Impl, tags::result::value>
        {
            explicit result(Impl* impl)
                : result<Impl, tags::result::value>(impl)
            {
            }
        };

        template <class Impl>
        struct result<Impl, tags::result::solid>:
            result<Impl, tags::result::reference>
        {
            explicit result(Impl* impl)
                : result<Impl, tags::result::reference>(impl)
            {
            }
        };
    }
}

#endif

