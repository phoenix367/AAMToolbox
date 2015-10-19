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
 * File:   tminfoTest.cpp
 * Author: Иван Губочкин
 *
 * Created on 07.08.2012, 16:05:23
 */

#include <stdlib.h>
#include <iostream>
#include <vector>
#include <opencv2/highgui/highgui.hpp>

#include "aam/TrainModelInfo.h"
#include "gtest/gtest.h"

/*
 * Simple C++ Test Suite
 */

#define TOTAL_POINTS_NUMBER             (58)

const int points[2 * TOTAL_POINTS_NUMBER] =
{
   228,   307,
   232,   327,
   239,   350,
   255,   374,
   270,   392,
   294,   406,
   314,   410,
   343,   403,
   361,   388,
   372,   370,
   382,   349,
   388,   331,
   393,   312,
   374,   243,
   364,   236,
   354,   234,
   339,   235,
   334,   243,
   346,   245,
   355,   247,
   366,   247,
   251,   242,
   263,   234,
   275,   230,
   286,   235,
   297,   242,
   285,   245,
   274,   245,
   262,   244,
   325,   228,
   333,   215,
   366,   210,
   387,   219,
   391,   241,
   305,   226,
   292,   213,
   259,   208,
   240,   215,
   236,   236,
   277,   333,
   305,   329,
   313,   333,
   321,   328,
   348,   329,
   325,   347,
   314,   348,
   302,   347,
   303,   244,
   304,   268,
   290,   284,
   288,   299,
   299,   303,
   314,   303,
   328,   303,
   338,   295,
   333,   281,
   325,   269,
   324,   245
};

std::set<int> targetPtNumbers = {
     (0), (38), (37), (36), (31), (32), (33), (12), (11), (10), (9),
     (8), (7), (6), (5), (4), (3), (2), (1)};

bool checkCoordList(const std::vector<aam::LineType>& lines,
        const std::set<int>& ptNumbers)
{
    std::set<int> firstPtNumber;

    for (int i = 0; i < lines.size(); i++)
    {
        firstPtNumber.insert(lines[i]);
    }
    
    return (firstPtNumber == ptNumbers);
}

TEST(Model, testModel)
{
    std::vector<aam::Point2D> pt;

    for (int i = 0; i < TOTAL_POINTS_NUMBER; i++)
    {
        aam::Point2D facePoint;

        facePoint.x = points[i * 2 + 0];
        facePoint.y = points[i * 2 + 1];

        pt.push_back(facePoint);
    }

    aam::TrainModelInfo modelInfo;

    modelInfo.setVertices(pt);

    std::vector<aam::LineType> lines = modelInfo.getLines();

    EXPECT_EQ(lines.size(), 19);
    EXPECT_TRUE(checkCoordList(lines, targetPtNumbers));
}

TEST(Model, testEmpty)
{
    aam::TrainModelInfo modelInfo;

    modelInfo.setVertices(std::vector<aam::Point2D>());

    std::vector<aam::LineType> lines = modelInfo.getLines();
    EXPECT_TRUE(lines.empty());
}

TEST(Model, testOne)
{
    aam::TrainModelInfo modelInfo;

    aam::Vertices2DList pt = {
            (aam::Point2D(1.0, 2.0))
    };
    modelInfo.setVertices(pt);

    std::vector<aam::LineType> lines = modelInfo.getLines();
    EXPECT_TRUE(lines.empty());
}

void testSetImage()
{
    std::cout << "tminfoTest testSetImage" << std::endl;

    aam::TrainModelInfo modelInfo;
    try
    {
        cv::Mat im = cv::imread("data/IMM/01-1m.jpg");
        modelInfo.setImage(im);

        cv::Mat resImage = modelInfo.getImage();

        if (resImage.rows != 480 || resImage.cols != 640)
        {
            std::cout << "%TEST_FAILED% time=0 testname=testSetImage (tminfoTest) message=Invalid image size" << std::endl;
        }
        else if (resImage.type() != CV_64FC3)
        {
            std::cout << "%TEST_FAILED% time=0 testname=testSetImage (tminfoTest) message=Invalid result image type" << std::endl;
        }
        else
        {
            cv::Mat1b res;
            cv::inRange(resImage, cv::Matx13d::zeros(), cv::Matx13d::ones(), res);

            if (cv::countNonZero(res) != 640 * 480)
            {
                std::cout << "%TEST_FAILED% time=0 testname=testSetImage (tminfoTest) message=Image elements not in [0; 1] range" << std::endl;
            }
        }
    }
    catch (std::exception& e)
    {
        std::cout << "%TEST_FAILED% time=0 testname=testSetImage (tminfoTest) message=Exception occures: " <<
                e.what() << std::endl;
    }
}

void testSetImageGray()
{
    std::cout << "tminfoTest testSetImageGray" << std::endl;

    aam::TrainModelInfo modelInfo;
    try
    {
        cv::Mat im = cv::imread("data/IMM/01-1m.jpg");
        modelInfo.setImage(im, true);

        cv::Mat resImage = modelInfo.getImage();

        if (resImage.rows != 480 || resImage.cols != 640)
        {
            std::cout << "%TEST_FAILED% time=0 testname=testSetImageGray (tminfoTest) message=Invalid image size" << std::endl;
        }
        else if (resImage.type() != CV_64FC1)
        {
            std::cout << "%TEST_FAILED% time=0 testname=testSetImageGray (tminfoTest) message=Invalid result image type" << std::endl;
        }
        else
        {
            cv::Mat1b res;
            cv::inRange(resImage, 0, 1, res);

            if (cv::countNonZero(res) != 640 * 480)
            {
                std::cout << "%TEST_FAILED% time=0 testname=testSetImageGray (tminfoTest) message=Image elements not in [0; 1] range" << std::endl;
            }
        }
    }
    catch (std::exception& e)
    {
        std::cout << "%TEST_FAILED% time=0 testname=testSetImageGray (tminfoTest) message=Exception occures: " <<
                e.what() << std::endl;
    }
}
