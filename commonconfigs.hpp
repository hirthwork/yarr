/*
 * commonconfigs.hpp        -- some common range configurations
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

#ifndef __COMMONCONFIGS_HPP_2012_05_08__
#define __COMMONCONFIGS_HPP_2012_05_08__

#include <cstddef>

#include "config.hpp"
#include "iotypeconfig.hpp"
#include "iotypetags.hpp"
#include "orderconfig.hpp"
#include "ordertags.hpp"
#include "passconfig.hpp"
#include "passtags.hpp"
#include "resultconfig.hpp"
#include "resulttags.hpp"
#include "sizeconfig.hpp"
#include "sizetags.hpp"

namespace yarr {
    namespace configs {
        // user should define result type using set_result_config
        template <class ResultConfig>
        struct device_input: range<
            pass<tags::pass::one_pass>,
            order<tags::order::sequential>,
            iotype<tags::iotype::input>,
            size<tags::size::unlimited>,
            ResultConfig>
        {
        };

        template <class ResultConfig>
        struct device_output: set_iotype<device_input<ResultConfig>,
            iotype<tags::iotype::output> >
        {
        };

        template <class ResultConfig>
        struct stream_input: set_pass<device_input<ResultConfig>,
            pass<tags::pass::swappable> >
        {
        };

        template <class ResultConfig>
        struct stream_output: set_pass<device_output<ResultConfig>,
            pass<tags::pass::swappable> >
        {
        };

        template <class ResultType, class IOType = tags::iotype::input>
        struct linked_list: set_iotype<set_pass<
            device_input<result<tags::result::reference, ResultType> >,
            pass<tags::pass::forward> >,
            iotype<IOType> >
        {
        };

        template <class ResultType, class IOType = tags::iotype::input>
        struct doubly_linked_list: set_iotype<set_pass<linked_list<ResultType>,
            pass<tags::pass::double_ended> >, iotype<IOType> >
        {
        };

        template <class ResultType, class SizeType = std::size_t,
            class PosType = SizeType, class IOType = tags::iotype::input>
        struct array: range<
            pass<tags::pass::forward>,
            order<tags::order::random, PosType>,
            iotype<IOType>,
            size<tags::size::limited, SizeType>,
            result<tags::result::solid, ResultType> >
        {
        };

        template <class ResultType, class SizeType = std::size_t,
            class PosType = std::ptrdiff_t, class IOType = tags::iotype::input>
        struct double_ended_array: set_pass<
            array<ResultType, SizeType, PosType, IOType>,
            pass<tags::pass::double_ended> >
        {
        };
    }
}

#endif

