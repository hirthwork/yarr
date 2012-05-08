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
    namespace common_configs {
        // user should define result type using set_result_config
        template <class ResultConfig>
        struct device_input: range_config<
            pass_config<tags::pass::one_pass>,
            order_config<tags::order::sequential>,
            iotype_config<tags::iotype::input>,
            size_config<tags::size::unlimited>,
            ResultConfig>
        {
        };

        template <class ResultConfig>
        struct device_output: set_iotype_config<device_input<ResultConfig>,
            iotype_config<tags::iotype::output> >
        {
        };

        template <class ResultConfig>
        struct stream_input: set_pass_config<device_input<ResultConfig>,
            pass_config<tags::pass::swappable> >
        {
        };

        template <class ResultConfig>
        struct stream_output: set_pass_config<device_output<ResultConfig>,
            pass_config<tags::pass::swappable> >
        {
        };

        template <class ResultType>
        struct linked_list: set_pass_config<
            device_input<result_config<tags::result::reference, ResultType> >,
            pass_config<tags::pass::forward> >
        {
        };

        template <class ResultType>
        struct doubly_linked_list: set_pass_config<linked_list<ResultType>,
            pass_config<tags::pass::double_ended> >
        {
        };

        template <class ResultType, class SizeType = std::size_t,
            class PosType = SizeType>
        struct array: range_config<
            pass_config<tags::pass::forward>,
            order_config<tags::order::random, PosType>,
            iotype_config<tags::iotype::input>,
            size_config<tags::size::limited, SizeType>,
            result_config<tags::result::solid, ResultType> >
        {
        };

        template <class ResultType, class SizeType = std::size_t,
            class PosType = std::ptrdiff_t>
        struct double_ended_array: range_config<
            pass_config<tags::pass::double_ended>,
            order_config<tags::order::random, PosType>,
            iotype_config<tags::iotype::input>,
            size_config<tags::size::limited, SizeType>,
            result_config<tags::result::solid, ResultType> >
        {
        };
    }
}

#endif

