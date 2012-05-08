/*
 * resultconfig.hpp         -- result tag configuration trait
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

#ifndef __RESULTCONFIG_HPP_2012_05_08__
#define __RESULTCONFIG_HPP_2012_05_08__

namespace yarr {
    namespace configs {
        template <class Category, class ResultType>
        struct result {
            typedef Category category;
            typedef ResultType result_type;
        };

        template <class RangeConfig, class ResultConfig>
        struct set_result: RangeConfig {
            typedef ResultConfig result_config;
        };
    }
}

#endif
