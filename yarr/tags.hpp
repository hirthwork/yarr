/*
 * tags.hpp                 range tags definition
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

#ifndef __YARR__TAGS_HPP__2013_01_26__
#define __YARR__TAGS_HPP__2013_01_26__

namespace yarr {
    namespace tags {
        template <class Config>
        struct root_tag {
            typedef typename Config::pass::tag tag;
        };

        template <class Tag, class Config>
        struct next_tag {
            // `void' means that there is no next tag
            typedef void tag;
        };

        // return value tags
        // these tags defines category of the values returned by front(),
        // back() and operator[]
        namespace result {
            // this tag requires range to return element by value
            // ranges with this tag must provide value_type typedef,
            // which can be a reference for non-copyable objects
            //
            // provides:
            //  * next()
            //  * value_type
            //
            // for double ended ranges provides:
            //  * prev()
            struct value {};

            // ranges with this tag should return const reference from their
            // element access functions and this references must stay valid
            // until range destruction
            // these ranges must provide reference typedef
            //
            // provides:
            //  * pop()
            //  * front()
            //  * reference
            //
            // for double ended ranges provides:
            //  * back()
            //  * pop_back()
            struct reference: value {};

            // ranges which elements goes one-by-one in memory and can be
            // accessed by "*(&front() + n)"
            struct contiguous: reference {};
        }

        template <class Config>
        struct next_tag<result::reference, Config> {
            typedef result::value tag;
        };

        template <class Config>
        struct next_tag<result::contiguous, Config> {
            typedef result::reference tag;
        };

        // length tags
        namespace length {
            // endless range, which always have next element.
            // for example, prime numbers returning range
            struct endless {};

            // defines ranges which size can be obtained until all range is
            // traversed. empty() function returns true at the end of range
            //
            // provides:
            //  * empty()
            struct finite {};

            // defines ranges which size can be obtained using size() function
            //
            // provides:
            //  * size()
            //  * size_type
            struct fixed: finite {};
        }

        template <class Config>
        struct next_tag<length::endless, Config> {
            typedef typename Config::result::tag tag;
        };

        template <class Config>
        struct next_tag<length::finite, Config> {
            typedef typename Config::result::tag tag;
        };

        template <class Config>
        struct next_tag<length::fixed, Config> {
            typedef length::finite tag;
        };

        namespace iotype {
            struct input {};

            // ordered ranges shall provide elements sorted according to their
            // predicate when traversed from begin to end
            //
            // provides:
            //  * predicate()
            //  * predicate_type
            struct ordered: input {};

            // the predicate of strictly ordered ranges should meet the
            // following requirement:
            // ∀ x, y ∈ range: x ≠ y ⇒ Pred(x, y) == true ⇔ Pred(y, x) == false
            // and consequent calls to next() function return different values
            struct strictly_ordered: ordered {};

            struct output {};
        }

        template <class Config>
        struct next_tag<iotype::input, Config> {
            typedef typename Config::length::tag tag;
        };

        template <class Config>
        struct next_tag<iotype::ordered, Config> {
            typedef iotype::input tag;
        };

        template <class Config>
        struct next_tag<iotype::strictly_ordered, Config> {
            typedef iotype::ordered tag;
        };

        template <class Config>
        struct next_tag<iotype::output, Config> {
            typedef typename Config::length::tag tag;
        };

        // access order tags
        // defines order in which elements of range can be accessed
        namespace order {
            // elements of such ranges can be accesses one by one using
            // front(), next() or back() functions
            struct sequential {};

            // in addition to sequential ranges element access functions,
            // random access ranges provides operator[] function. implies
            // reference value type
            //
            // provides:
            //  * at()
            //  * skip()
            //  * pos_type
            //
            // for double ended ranges provides:
            //  * rat()
            //  * truncate()
            //
            struct random: sequential {};
        }

        template <class Config>
        struct next_tag<order::sequential, Config> {
            typedef typename Config::iotype::tag tag;
        };

        template <class Config>
        struct next_tag<order::random, Config> {
            typedef order::sequential tag;
        };

        namespace pass {
            // one pass ranges allows to go through the range once
            // ranges of this type must provide next() function which returns
            // `type' and goes to the next element
            // it is a good idea to have output ranges, which performs I/O, to
            // be one pass ranges
            struct one_pass {};

            // swappable ranges provides function swap() which allows to swap
            // two ranges performing output to streams of the same type
            //
            // provides:
            //  * swap()
            struct swappable: one_pass {};

            // forward ranges provides operator =(), copy c'tor,
            // front() and pop() functions
            // buffer filling output ranges can be forward ranges
            //
            // provides:
            //  * copy c'tor
            //  * operator =()
            struct forward: swappable {};

            // double ended ranges allows to access not only front elements,
            // but also elements from the back of the range using functions
            // back() and pop_back().
            struct double_ended: forward {};
        }

        template <class Config>
        struct next_tag<pass::one_pass, Config> {
            typedef typename Config::order::tag tag;
        };

        template <class Config>
        struct next_tag<pass::swappable, Config> {
            typedef pass::one_pass tag;
        };

        template <class Config>
        struct next_tag<pass::forward, Config> {
            typedef pass::swappable tag;
        };

        template <class Config>
        struct next_tag<pass::double_ended, Config> {
            typedef pass::forward tag;
        };
    }
}

#endif

