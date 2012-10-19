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
 * File:   wtriangleTest.cpp
 * Author: Иван Губочкин
 *
 * Created on 16.08.2012, 16:01:11
 */

#include <stdlib.h>
#include <iostream>
#include <opencv/highgui.h>

#include "aam/PiecewiseWarp.h"

/*
 * Simple C++ Test Suite
 */

#define TOTAL_POINTS_NUMBER             (58)
#define TRIANGLES_NUMBER                (95)

aam::RealType verticesAData[2 * TOTAL_POINTS_NUMBER] =
{
   307,   228,
   327,   232,
   350,   239,
   374,   255,
   392,   270,
   406,   294,
   410,   314,
   403,   343,
   388,   361,
   370,   372,
   349,   382,
   331,   388,
   312,   393,
   243,   374,
   236,   364,
   234,   354,
   235,   339,
   243,   334,
   245,   346,
   247,   355,
   247,   366,
   242,   251,
   234,   263,
   230,   275,
   235,   286,
   242,   297,
   245,   285,
   245,   274,
   244,   262,
   228,   325,
   215,   333,
   210,   366,
   219,   387,
   241,   391,
   226,   305,
   213,   292,
   208,   259,
   215,   240,
   236,   236,
   333,   277,
   329,   305,
   333,   313,
   328,   321,
   329,   348,
   347,   325,
   348,   314,
   347,   302,
   244,   303,
   268,   304,
   284,   290,
   299,   288,
   303,   299,
   303,   314,
   303,   328,
   295,   338,
   281,   333,
   269,   325,
   245,   324
};

int trianglesData[3 * TRIANGLES_NUMBER] =
{
    31,    30,    36,
     1,    39,     0,
    21,    38,     0,
    21,    37,    38,
    50,    39,     0,
    50,    21,     0,
    50,    21,    28,
     3,    39,    46,
    44,     9,    43,
    54,    53,    43,
    54,    43,    12,
    10,     9,    43,
    35,    30,    36,
    35,    23,    36,
    22,    37,    36,
    22,    21,    37,
    22,    21,    28,
    22,    23,    36,
    27,    26,    23,
    27,    22,    23,
    27,    22,    28,
    40,    39,    46,
     4,     5,    46,
     4,     3,    46,
     2,     1,    39,
     2,     3,    39,
    11,    43,    12,
    11,    10,    43,
     8,    44,     9,
    49,    26,    48,
    49,    27,    26,
    49,    50,    28,
    49,    27,    28,
    51,    49,    50,
    51,    50,    39,
    51,    40,    39,
    51,    49,    48,
    45,     7,     6,
    45,     8,     7,
    45,     8,    44,
    45,     5,     6,
    45,     5,    46,
    42,    53,    43,
    42,    44,    43,
    15,    31,    30,
    25,    34,    47,
    25,    47,    48,
    25,    26,    48,
    52,    51,    40,
    52,    42,    53,
    52,    51,    48,
    52,    56,    48,
    52,    56,    53,
    41,    40,    46,
    41,    45,    46,
    41,    52,    40,
    41,    52,    42,
    41,    45,    44,
    41,    42,    44,
    14,    31,    32,
    14,    15,    31,
    14,    15,    19,
    55,    54,    53,
    55,    56,    53,
    24,    25,    26,
    24,    25,    34,
    24,    26,    23,
    24,    35,    23,
    24,    34,    35,
    18,    15,    19,
    18,    17,    56,
    18,    55,    19,
    18,    55,    56,
    57,    17,    56,
    57,    47,    48,
    57,    56,    48,
    13,    33,    12,
    13,    33,    32,
    13,    14,    32,
    16,    15,    30,
    16,    18,    15,
    16,    18,    17,
    20,    14,    19,
    20,    13,    14,
    20,    55,    19,
    20,    55,    54,
    20,    54,    12,
    20,    13,    12,
    29,    57,    17,
    29,    16,    17,
    29,    16,    30,
    29,    35,    30,
    29,    34,    35,
    29,    34,    47,
    29,    57,    47
};

aam::RealType basePointsData[2 * TOTAL_POINTS_NUMBER] =
{
    120.381247175054,                         0,
    143.586642919077,           3.7634321108053,
    171.79315529451,          16.6534577599896,
    201.899793972034,          40.1492950461264,
    226.370756711916,          62.1431504246363,
    245.844776997987,          93.9780563590183,
               254,          127.373705138116,
    245.240733583923,          168.305575039926,
    225.164745615991,          197.119107797988,
    200.050837072688,          218.355786404131,
    171.17784313927,          237.315175831649,
    147.970528185273,          247.175054706985,
    124.145905056845,                       254,
    42.0244712576932,           222.94949022241,
    32.6279918122369,          204.736255453846,
    31.3738389363565,          190.342681657497,
    33.8920559251268,          166.081637940268,
    42.6683745234153,          157.727399119262,
    43.9120913121285,          177.438468771515,
    45.7850792449457,          192.604608819584,
    45.7871592625178,          209.285332081968,
    40.1208121968224,          35.6629999434447,
    30.0897451602259,          53.8619816666699,
    26.9684662192314,           71.311578834427,
    32.6115429068518,           87.986800367684,
    41.4000015675516,          103.142831803603,
    43.2707182476051,          84.9319175763725,
    42.6351950510158,          69.0083814493467,
    42.0085973442265,          50.8158159919247,
    23.2171194794298,           145.60169697339,
    8.15611403741522,          161.552549902277,
    1.90954278542666,          207.788134392066,
    12.5783879862371,          238.103643876259,
    38.2632797077818,          247.958984267861,
    22.6017283722878,          113.763550779504,
    6.91412308079881,          96.3419366255442,
                 0,          47.8196428382356,
    8.14213319169915,          19.7630711721115,
    33.2336263930217,          10.6376524134732,
    144.865027064363,          62.8192488362866,
    146.101571193938,          115.985411516485,
    150.493518343097,            127.3500278278,
    146.117316013742,          138.734136079768,
    143.547091396503,          190.312989269103,
    171.192503545796,          147.850409471651,
    173.711476904592,           129.65508330438,
    171.832411869342,          109.930709343108,
    42.0055358648149,           115.27405795992,
    75.2729492924326,          112.999064450562,
    90.2946621603083,          92.4920721063838,
    109.117603522492,           87.171146737946,
    116.011447848699,          106.910213913072,
    118.533637922792,          129.674088958547,
    116.650374710406,          150.129479014908,
    107.86418730247,          168.350501854288,
    88.4153883183843,          160.758480120356,
    75.8868298022072,          147.885677169957,
    43.9007217621975,           145.60011363403
};

void testWarpGray()
{
    std::cout << "wtriangleTest testWarpGray" << std::endl;

    aam::Vertices2DList vertices(TOTAL_POINTS_NUMBER);
    aam::Vertices2DList basePoints(TOTAL_POINTS_NUMBER);

    for (int i = 0; i < TOTAL_POINTS_NUMBER; i++)
    {
        vertices[i].y = verticesAData[2 * i];
        vertices[i].x = verticesAData[2 * i + 1];
        basePoints[i].y = basePointsData[2 * i];
        basePoints[i].x = basePointsData[2 * i + 1];
    }

    std::vector<cv::Vec3i> triangles(TRIANGLES_NUMBER);

    for (int i = 0; i < TRIANGLES_NUMBER; i++)
    {
        triangles[i] = cv::Vec3i(&trianglesData[i * 3]);
    }

    try
    {
        cv::Mat im = cv::imread("data/IMM/01-1m.jpg",
                cv::IMREAD_GRAYSCALE);
        aam::RealMatrix grayImage = aam::RealMatrix(im) / 255.0;
        cv::Mat outImage;
        
        int64 start = cv::getTickCount();
        aam::PiecewiseWarp::warpTriangle(grayImage, outImage, vertices,
                basePoints, triangles, cv::Size(255, 255));
        std::cout << "Warping working time " <<
                (cv::getTickCount() - start) / cv::getTickFrequency() <<
                std::endl;

//        cv::imshow("Warp", outImage);
//        cv::waitKey(0);
    }
    catch (std::exception& e)
    {
        std::cout << "%TEST_FAILED% time=0 testname=testWarpGray (wtriangleTest) message=Exception occured: " <<
                e.what() << std::endl;
    }
}

void testWarpColor()
{
    std::cout << "wtriangleTest testWarpColor" << std::endl;

    aam::Vertices2DList vertices(TOTAL_POINTS_NUMBER);
    aam::Vertices2DList basePoints(TOTAL_POINTS_NUMBER);

    for (int i = 0; i < TOTAL_POINTS_NUMBER; i++)
    {
        vertices[i].y = verticesAData[2 * i];
        vertices[i].x = verticesAData[2 * i + 1];
        basePoints[i].y = basePointsData[2 * i];
        basePoints[i].x = basePointsData[2 * i + 1];
    }

    std::vector<cv::Vec3i> triangles(TRIANGLES_NUMBER);

    for (int i = 0; i < TRIANGLES_NUMBER; i++)
    {
        triangles[i] = cv::Vec3i(&trianglesData[i * 3]);
    }

    try
    {
        cv::Mat im = cv::imread("data/IMM/01-1m.jpg");
        aam::ColorMatrix colorImage = cv::Mat(im) / 255.0;
        cv::Mat outImage;

        int64 start = cv::getTickCount();
        aam::PiecewiseWarp::warpTriangle(colorImage, outImage, vertices,
                basePoints, triangles, cv::Size(255, 255));
        std::cout << "Warping working time " <<
                (cv::getTickCount() - start) / cv::getTickFrequency() <<
                std::endl;

//        cv::imshow("Warp", outImage);
//        cv::waitKey(0);
    }
    catch (std::exception& e)
    {
        std::cout << "%TEST_FAILED% time=0 testname=testWarpColor (wtriangleTest) message=Exception occured: " <<
                e.what() << std::endl;
    }
}

void testWarpPrecompute()
{
    std::cout << "wtriangleTest testWarpPrecompute" << std::endl;

    aam::Vertices2DList vertices(TOTAL_POINTS_NUMBER);
    aam::Vertices2DList basePoints(TOTAL_POINTS_NUMBER);

    for (int i = 0; i < TOTAL_POINTS_NUMBER; i++)
    {
        vertices[i].y = verticesAData[2 * i];
        vertices[i].x = verticesAData[2 * i + 1];
        basePoints[i].y = basePointsData[2 * i];
        basePoints[i].x = basePointsData[2 * i + 1];
    }

    std::vector<cv::Vec3i> triangles(TRIANGLES_NUMBER);

    for (int i = 0; i < TRIANGLES_NUMBER; i++)
    {
        triangles[i] = cv::Vec3i(&trianglesData[i * 3]);
    }

    try
    {
        cv::Mat im = cv::imread("data/IMM/01-1m.jpg",
                cv::IMREAD_GRAYSCALE);
        aam::RealMatrix grayImage = aam::RealMatrix(im) / 255.0;
        aam::PiecewiseWarp::WarpInfo info;
        cv::Mat outImage;

        aam::PiecewiseWarp::precomputeWarp(
                basePoints, triangles, cv::Size(255, 255),
                info);

        int64 start = cv::getTickCount();
        aam::PiecewiseWarp::warpTriangle(grayImage, outImage,
                basePoints, triangles, cv::Size(255, 255),
                info);
        std::cout << "Warping working time " <<
                (cv::getTickCount() - start) / cv::getTickFrequency() <<
                std::endl;

//        cv::imshow("Warp", outImage);
//        cv::waitKey(0);
    }
    catch (std::exception& e)
    {
        std::cout << "%TEST_FAILED% time=0 testname=testWarpPrecompute (wtriangleTest) message=Exception occured: " <<
                e.what() << std::endl;
    }
}

int main(int argc, char** argv)
{
    std::cout << "%SUITE_STARTING% wtriangleTest" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% testWarpGray (wtriangleTest)" << std::endl;
    testWarpGray();
    std::cout << "%TEST_FINISHED% time=0 testWarpGray (wtriangleTest)" << std::endl;

    std::cout << "%TEST_STARTED% testWarpColor (wtriangleTest)" << std::endl;
    testWarpColor();
    std::cout << "%TEST_FINISHED% time=0 testWarpColor (wtriangleTest)" << std::endl;

    std::cout << "%TEST_STARTED% testWarpPrecompute (wtriangleTest)" << std::endl;
    testWarpPrecompute();
    std::cout << "%TEST_FINISHED% time=0 testWarpPrecompute (wtriangleTest)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}
