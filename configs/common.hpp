/*
 * common.hpp               -- some common range configurations
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

#ifndef __CONFIGS__COMMON_HPP__2012_05_08__
#define __CONFIGS__COMMON_HPP__2012_05_08__

#include <cstddef>

#include <tags/iotype.hpp>
#include <tags/length.hpp>
#include <tags/order.hpp>
#include <tags/pass.hpp>
#include <tags/result.hpp>

#include "config.hpp"
#include "iotype.hpp"
#include "length.hpp"
#include "order.hpp"
#include "pass.hpp"
#include "result.hpp"

namespace yarr {
    namespace configs {
        template <class ResultConfig>
        struct device_input {
            typedef range<
                pass<tags::pass::one_pass>,
                order<tags::order::sequential>,
                iotype<tags::iotype::input>,
                length<tags::length::unlimited>,
                ResultConfig> type;
        };

        template <class ResultConfig>
        struct device_output
        {
            typedef typename set_iotype<device_input<ResultConfig>,
                iotype<tags::iotype::output> >::type type;
        };

        template <class ResultConfig>
        struct stream_input {
            typedef typename set_pass<device_input<ResultConfig>,
                pass<tags::pass::swappable> >::type type;
        };

        template <class ResultConfig>
        struct stream_output {
            typedef typename set_pass<device_output<ResultConfig>,
                pass<tags::pass::swappable> >::type type;
        };

        template <class ResultType, class IOType = tags::iotype::input>
        struct linked_list {
            typedef typename set_iotype<typename set_pass<
                typename device_input<
                    result<tags::result::reference, ResultType> >::type,
                pass<tags::pass::forward> >::type,
                iotype<IOType> >::type type;
        };

        template <class ResultType, class IOType = tags::iotype::input>
        struct doubly_linked_list {
            typedef typename set_iotype<set_pass<linked_list<ResultType>,
                pass<tags::pass::double_ended> >, iotype<IOType> >::type type;
        };

        template <class ResultType, class SizeType = std::size_t,
            class PosType = SizeType, class IOType = tags::iotype::input>
        struct array {
            typedef range<
                pass<tags::pass::forward>,
                order<tags::order::random, PosType>,
                iotype<IOType>,
                length<tags::length::limited, SizeType>,
                result<tags::result::solid, ResultType> > type;
        };

        template <class ResultType, class SizeType = std::size_t,
            class PosType = SizeType, class IOType = tags::iotype::input>
        struct double_ended_array{
            typedef typename set_pass<
                typename array<ResultType, SizeType, PosType, IOType>::type,
                pass<tags::pass::double_ended> >::type type;
        };
    }
}

#endif

