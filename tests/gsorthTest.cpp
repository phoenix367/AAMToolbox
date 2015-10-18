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
 * File:   gsorthTest.cpp
 * Author: Иван Губочкин
 *
 * Created on 26.09.2012, 23:36:50
 */

#include <stdlib.h>
#include <iostream>
#include <exception>
#include <iterator>

#include "aam/CommonFunctions.h"
#include "gtest/gtest.h"
#include "test_config.h"
#include "load_vector.h"

/*
 * Simple C++ Test Suite
 */

TEST(Orth, testGSOrth)
{
    aam::RealType srcData[4 * 4] =
    {
        0.63787,   0.11209,   0.13878,   0.45578,
        0.94683,   0.12062,   0.33320,   0.89226,
        0.76691,   0.17863,   0.18085,   0.46860,
        0.74186,   0.76346,   0.73360,   0.25635
    };

    aam::RealMatrix x(4, 4, srcData);
    aam::RealMatrix y;
    aam::CommonFunctions::orthonormGS(x, y);

    EXPECT_EQ(y.rows, x.rows);

    for (int i = 0; i < y.cols; i++)
    {
        aam::RealMatrix r = y.col(i).t() * y.col(i);
        EXPECT_EQ(cv::countNonZero(cv::abs(r - 1) > 1e-12), 0);

        for (int j = i + 1; j < y.cols; j++)
        {
            aam::RealMatrix r = y.col(i).t() * y.col(j);
            EXPECT_EQ(cv::countNonZero(cv::abs(r) > 1e-12), 0);
        }
    }
}

TEST(Orth, testGSOrth2)
{
    aam::RealMatrix srcData, targetData;

    std::ostringstream pathStream;
    pathStream << AAM_TEST_DATA_PATH << "/s_star_pc.dat";
    EXPECT_TRUE(loadVector(pathStream.str(), 116, 20, srcData));

    pathStream.str(std::string());
    pathStream << AAM_TEST_DATA_PATH << "/s_star_pc_norm.dat";
    EXPECT_TRUE(loadVector(pathStream.str(), 116, 20, targetData));

    aam::RealMatrix y;
    aam::CommonFunctions::orthonormGS(srcData, y);

    EXPECT_EQ(y.rows, targetData.rows);
    EXPECT_EQ(y.cols, targetData.cols);
    EXPECT_EQ(cv::countNonZero(cv::abs(y - targetData) > 1e-10), 0);
}

TEST(Orth, testGSOrth3)
{
    aam::RealMatrix srcData, targetData;

    std::ostringstream pathStream;
    pathStream << AAM_TEST_DATA_PATH << "/s_star_pc.dat";
    EXPECT_TRUE(loadVector(pathStream.str(), 116, 20, srcData));

    pathStream.str(std::string());
    pathStream << AAM_TEST_DATA_PATH << "/s_star_pc_norm.dat";
    if (!loadVector(pathStream.str(), 116, 20, targetData))

    for (int i = 0; i < 58; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            std::swap(srcData(i, j), srcData(i + 58, j));
        }

        srcData(i, 0) -= 1;
        srcData(i + 1, 0) -= 1;
        srcData(i, 1) -= 1;
        srcData(i + 58, 1) += 1;
    }

    aam::RealMatrix y;
    aam::CommonFunctions::orthonormGS(srcData, y);

    EXPECT_EQ(y.rows, targetData.rows);
    EXPECT_EQ(y.cols, targetData.cols);
}
