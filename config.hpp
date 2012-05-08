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

#ifndef __CONFIG_HPP_2012_05_08__
#define __CONFIG_HPP_2012_05_08__

namespace yarr {
    namespace configs {
        template <class PassConfig,
            class OrderConfig,
            class IOTypeConfig,
            class SizeConfig,
            class ResultConfig>
        struct range {
            typedef PassConfig pass_config;
            typedef OrderConfig order_config;
            typedef IOTypeConfig iotype_config;
            typedef SizeConfig size_config;
            typedef ResultConfig result_config;
        };

        template <class RangeConfig, class Assert, class Allocator>
        struct complete: RangeConfig {
            typedef Assert assert_type;
            typedef Allocator allocator_type;
        };
    }
}

#endif

