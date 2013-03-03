/*
 * list.hpp                 list wrapping range
 *
 * Copyright (C) 2013 Dmitry Potapov <potapov.d@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
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

#ifndef __YARR__LIST_HPP__2013_03_03__
#define __YARR__LIST_HPP__2013_03_03__

#include <list>

#include "iterator.hpp"

namespace yarr {
    namespace list {
        template <class T>
        struct list: iterator::impl::start<
            typename std::list<T>::const_iterator,
            typename iterator::impl::config<
                typename std::list<T>::const_iterator>::type>
        {
            list(const std::list<T>& v)
                : iterator::impl::start<
                    typename std::list<T>::const_iterator,
                    typename iterator::impl::config<
                        typename std::list<T>::const_iterator>::type>(
                    v.begin(), v.end())
            {
            }
        };
    }
}

#endif

