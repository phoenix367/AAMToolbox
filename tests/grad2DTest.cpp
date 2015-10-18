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
 * File:   grad2DTest.cpp
 * Author: Иван Губочкин
 *
 * Created on 23.09.2012, 1:21:52
 */

#include <stdlib.h>
#include <iostream>
#include <opencv/highgui.h>

#include "aam/CommonFunctions.h"
#include "gtest/gtest.h"
#include "test_config.h"

/*
 * Simple C++ Test Suite
 */

bool loadVector(const std::string& fileName, int rows,
        int columns, aam::RealMatrix& target)
{
    cv::Mat1d result(rows, columns);

    FILE *in = fopen(fileName.c_str(), "rb");
    if (in == NULL)
    {
        return false;
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (fread(result.ptr(i, j), sizeof(double), 1, in) != 1)
            {
                fclose(in);
                return false;
            }
        }
    }

    target = result;

    fclose(in);
    return true;
}

TEST(Gradient, testGradient)
{
    std::ostringstream pathStream;
    
    pathStream << AAM_TEST_DATA_PATH << "/object_pixels.bmp";
    cv::Mat1b maskImage = cv::imread(pathStream.str(),
            cv::IMREAD_GRAYSCALE);
    EXPECT_FALSE(maskImage.empty());

    pathStream.str(std::string());
    pathStream << AAM_TEST_DATA_PATH << "/warped_image.bmp";
    aam::RealMatrix warpedImage = cv::imread(pathStream.str(),
            cv::IMREAD_GRAYSCALE);
    EXPECT_FALSE(warpedImage.empty());

    aam::RealMatrix targetDi, targetDj;

    pathStream.str(std::string());
    pathStream << AAM_TEST_DATA_PATH << "/di_grad.raw";
    EXPECT_TRUE(loadVector(pathStream.str(), 255, 255, targetDi));

    pathStream.str(std::string());
    pathStream << AAM_TEST_DATA_PATH << "/dj_grad.raw";
    EXPECT_TRUE(loadVector(pathStream.str(), 255, 255, targetDj));

    warpedImage /= 255.0;

    aam::RealMatrix di, dj;
    aam::CommonFunctions::gradient2D(warpedImage, maskImage,
            di, dj);

    EXPECT_EQ(di.size, targetDi.size);
    EXPECT_EQ(cv::countNonZero(cv::abs(di - targetDi) > 1e-8), 0);
    EXPECT_EQ(dj.size, targetDj.size);
    EXPECT_EQ(cv::countNonZero(cv::abs(dj - targetDj) > 1e-8), 0);
}

TEST(Gradient, DISABLED_testGradientColor)
{
    std::ostringstream pathStream;
    
    pathStream << AAM_TEST_DATA_PATH << "/object_pixels.bmp";
    cv::Mat1b maskImage = cv::imread(pathStream.str(),
            cv::IMREAD_GRAYSCALE);
    EXPECT_FALSE(maskImage.empty());

    pathStream.str(std::string());
    pathStream << AAM_TEST_DATA_PATH << "/warped_image_color.bmp";
    aam::ColorMatrix warpedImage = cv::imread(pathStream.str());
    EXPECT_FALSE(warpedImage.empty());

    aam::RealMatrix targetDi, targetDj;

    pathStream.str(std::string());
    pathStream << AAM_TEST_DATA_PATH << "/di_grad.raw";
    EXPECT_TRUE(loadVector(pathStream.str(), 255, 255, targetDi));

    pathStream.str(std::string());
    pathStream << AAM_TEST_DATA_PATH << "/dj_grad.raw";
    EXPECT_TRUE(loadVector(pathStream.str(), 255, 255, targetDj));

    warpedImage /= 255.0;

    aam::ColorMatrix di, dj;
    aam::CommonFunctions::gradient2D(warpedImage, maskImage,
            di, dj);

    EXPECT_EQ(di.size, targetDi.size);
    EXPECT_EQ(cv::countNonZero(cv::abs(di - targetDi) > 1e-8), 0);
    EXPECT_EQ(dj.size, targetDj.size);
    EXPECT_EQ(cv::countNonZero(cv::abs(dj - targetDj) > 1e-8), 0);
}
