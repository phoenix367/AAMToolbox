/* Active Appearance Model toolbox
 * Copyright (C) 2015 Ivan Gubochkin
 * e-mail: jhng@yandex.ru
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef AAM_LOAD_VECTOR_H
#define AAM_LOAD_VECTOR_H

#include "aam/CommonFunctions.h"

bool loadVector(const std::string& fileName, int rows,
        int columns, aam::RealMatrix& target);

#endif /* AAM_LOAD_VECTOR_H */
