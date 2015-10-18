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
 * File:   pcaTest.cpp
 * Author: Иван Губочкин
 *
 * Created on 12.08.2012, 22:51:41
 */

#include <stdlib.h>
#include <iostream>

#include "aam/CommonFunctions.h"
#include "aam/aam.h"
#include "gtest/gtest.h"

/*
 * Simple C++ Test Suite
 */

TEST(PCA, testPCA)
{
    aam::RealType srcData[] =
    {
        1, 2,
        3, 4,
        5, 6,
        7, 8,
        9, 10,
        11, 12
    };

    aam::RealType meanData[] =
    {
        1.5,
        3.5,
        5.5,
        7.5,
        9.5,
        11.5
    };

    aam::RealType eigValuesData[] =
    {
        3,
        0
    };

    cv::Mat m(6, 2, aam::OpenCVRealType::type, srcData);
    cv::Mat targetMeans(6, 1, aam::OpenCVRealType::type, meanData);
    cv::Mat targetEigValues(2, 1, aam::OpenCVRealType::type, eigValuesData);

    aam::RealMatrix means, eigVectors, eigValues;

    aam::CommonFunctions::PCA(m, means, eigVectors, eigValues);

    EXPECT_EQ(means.rows, 6);
    EXPECT_EQ(means.cols, 1);
    EXPECT_EQ(eigVectors.rows, 6);
    EXPECT_EQ(eigVectors.cols, 2);
    EXPECT_EQ(eigValues.rows, 2);
    EXPECT_EQ(eigValues.cols, 1);

    EXPECT_EQ(cv::countNonZero(cv::abs(means - targetMeans) > 1e-6), 0);
    EXPECT_EQ(cv::countNonZero(cv::abs(eigValues - targetEigValues) > 1e-6), 0);
}

TEST(PCA, testAppPCA)
{
    aam::RealType srcData[] =
    {
        1, 2,
        3, 4,
        5, 6,
        7, 8,
        9, 10,
        11, 12
    };

    aam::RealType meanData[] =
    {
        1.5,
        3.5,
        5.5,
        7.5,
        9.5,
        11.5
    };

    aam::RealType eigValuesData[] =
    {
        3,
        0
    };

    cv::Mat m(6, 2, aam::OpenCVRealType::type, srcData);
    cv::Mat targetMeans(6, 1, aam::OpenCVRealType::type, meanData);
    cv::Mat targetEigValues(2, 1, aam::OpenCVRealType::type, eigValuesData);

    aam::RealMatrix means, eigVectors, eigValues;

    aam::CommonFunctions::appPCA(m, means, eigVectors, eigValues);

    EXPECT_EQ(means.rows, 6);
    EXPECT_EQ(means.cols, 1);
    EXPECT_EQ(eigVectors.rows, 6);
    EXPECT_EQ(eigVectors.cols, 2);
    EXPECT_EQ(eigValues.rows, 2);
    EXPECT_EQ(eigValues.cols, 1);

    EXPECT_EQ(cv::countNonZero(cv::abs(means - targetMeans) > 1e-6), 0);
    
    for (int i = 0; i < 2; i++) {
        EXPECT_EQ(cv::countNonZero(cv::abs(eigVectors.col(i).t() * eigVectors.col(i) - 
                aam::RealMatrix::ones(1, 1)) > 1e-6), 0);
    }
}
