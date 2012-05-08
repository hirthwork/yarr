/*
 * passtags.hpp             -- range pass tags
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

#ifndef __PASSTAGS_HPP_2012_05_08__
#define __PASSTAGS_HPP_2012_05_08__

namespace yarr {
    namespace tags {
        namespace pass {
            // one pass ranges allows to go through the range once
            // ranges of this type must provide next() function which returns
            // result_type and goes to the next element
            // it is a good idea to have output ranges, which performs I/O, to
            // be one pass ranges
            struct one_pass {};

            // swappable ranges provides function swap() which allows to swap
            // two ranges perfroming output to streams of the same type
            struct swappable: one_pass {};

            // forward ranges provides operator =(), copy c'tor,
            // front() and pop() functions
            // buffer filling output ranges can be forward ranges
            struct forward: swappable {};

            // double ended ranges allows to access not only front elements,
            // but also elements from the back of the range using functions
            // back() and pop_back().
            // for convinience, double ended ranges provides pop_front()
            // function which should have same effect as pop()
            struct double_ended: forward {};
        }
    }
}

#endif

