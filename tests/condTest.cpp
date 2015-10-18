/* Active Appearance Model toolbox
 * Copyright (C) 2012 Ivan Gubochkin
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

/* 
 * File:   condTest.cpp
 * Author: Ivan Gubochkin <jhng@yandex.ru>
 *
 * Created on 26.10.2012, 18:04:24
 */

#include <stdlib.h>
#include <iostream>

#include "aam/CommonFunctions.h"
#include "gtest/gtest.h"
#include "test_config.h"
#include "load_vector.h"

#define ROWS_COUNT          6
#define COLUMNS_COUNT       66

/*
 * Simple C++ Test Suite
 */

TEST(Cond, testCond)
{
    aam::RealMatrix A;

    std::ostringstream pathStream;
    pathStream << AAM_TEST_DATA_PATH << "/cond_A.raw";
    EXPECT_TRUE(loadVector(pathStream.str(), ROWS_COUNT, COLUMNS_COUNT, A));

    aam::RealType n = aam::CommonFunctions::cond(A);

    EXPECT_LE(fabs(n - 1686.0076855698678), 1e-10);
}
