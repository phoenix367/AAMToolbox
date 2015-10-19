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
 * File:   reignoiseTest.cpp
 * Author: Иван Губочкин
 *
 * Created on 23.08.2012, 23:51:05
 */

#include <stdlib.h>
#include <iostream>
#include <exception>

#include "aam/CommonFunctions.h"
#include "gtest/gtest.h"

/*
 * Simple C++ Test Suite
 */

TEST(EIGNoise, testRemoveNoise)
{
    aam::RealType eigVectorsData[] =
    {
        1, 5, 9,
        2, 6, 10,
        3, 7, 11,
        4, 6, 12
    };

    aam::RealType eigValuesData[] =
    {
        1, 0.3, 1e-4
    };

    aam::RealMatrix eigVectors(4, 3, eigVectorsData);
    aam::RealMatrix targetEigVectors(eigVectors.colRange(0, 2));
    aam::RealMatrix eigValues(3, 1, eigValuesData);
    aam::RealMatrix targetEigValues(eigValues.rowRange(0, 2));

    aam::CommonFunctions::removeEigNoise(eigVectors, eigValues, 0.99);

    EXPECT_EQ(eigVectors.rows, 4);
    EXPECT_EQ(eigVectors.cols, 2);
    EXPECT_EQ(eigValues.rows, 2);
    EXPECT_EQ(eigValues.cols, 1);

    EXPECT_EQ(cv::countNonZero(cv::abs(
            eigVectors - targetEigVectors) > 1e-6), 0);
    EXPECT_EQ(cv::countNonZero(cv::abs(
            eigValues - targetEigValues) > 1e-6), 0);
}

TEST(EIGNoise, testRemoveNoiseOne)
{
    aam::RealType eigVectorsData[] =
    {
        1,
        2,
        3,
        4
    };

    aam::RealType eigValuesData[] =
    {
        1
    };

    aam::RealMatrix eigVectors(4, 1, eigVectorsData);
    aam::RealMatrix targetEigVectors(eigVectors);
    aam::RealMatrix eigValues(1, 1, eigValuesData);
    aam::RealMatrix targetEigValues(eigValues);

    aam::CommonFunctions::removeEigNoise(eigVectors, eigValues, 0.99);

    EXPECT_EQ(eigVectors.rows, 4);
    EXPECT_EQ(eigVectors.cols, 1);
    EXPECT_EQ(eigValues.rows, 1);
    EXPECT_EQ(eigValues.cols, 1);
    EXPECT_EQ(cv::countNonZero(cv::abs(
            eigVectors - targetEigVectors) > 1e-6), 0);
    EXPECT_EQ(cv::countNonZero(cv::abs(
            eigValues - targetEigValues) > 1e-6), 0);
}

TEST(EIGNoise, testRemoveNoiseEmpty)
{
    aam::RealMatrix eigVectors;
    aam::RealMatrix eigValues;

    aam::CommonFunctions::removeEigNoise(eigVectors, eigValues, 0.99);

    EXPECT_TRUE(eigVectors.empty());
    EXPECT_TRUE(eigValues.empty());
}
