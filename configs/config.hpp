/*
 * config.hpp               -- configuration wrapper
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

#ifndef __CONFIGS__CONFIG_HPP__2012_05_08__
#define __CONFIGS__CONFIG_HPP__2012_05_08__

namespace yarr {
    namespace configs {
        struct empty {};

        template <class Pass, class Order, class IOType, class Length,
            class Result>
        struct range {
            typedef Pass pass;
            typedef Order order;
            typedef IOType iotype;
            typedef Length length;
            typedef Result result;
        };

        template <class Config, class Assert>
        struct complete: Config {
            typedef Config config_type;
            typedef Assert assert_type;
        };

        template <class Config>
        struct copy {
            typedef range<
                typename Config::pass,
                typename Config::order,
                typename Config::iotype,
                typename Config::length,
                typename Config::result> type;
        };

        template <class Config>
        struct complete_copy {
            typedef complete<typename copy<Config>::type,
                typename Config::assert_type> type;
        };
    }
}

#endif

