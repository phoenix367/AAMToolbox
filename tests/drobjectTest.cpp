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
 * File:   drobjectTest.cpp
 * Author: Иван Губочкин
 *
 * Created on 15.08.2012, 13:04:17
 */

#include <stdlib.h>
#include <iostream>
#include <exception>
#include <boost/assign.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "aam/CommonFunctions.h"

/*
 * Simple C++ Test Suite
 */

#define TOTAL_POINTS_NUMBER             (58)

aam::RealType verticesAData[2 * TOTAL_POINTS_NUMBER] =
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

std::vector<int> targetPtNumbers = boost::assign::list_of<int>
     (0) (38) (37) (36) (31) (32) (33) (12) (11) (10) (9)
     (8) (7) (6) (5) (4) (3) (2) (1);

void testDraw()
{
    std::cout << "drobjectTest testDraw" << std::endl;

    cv::Size textureSize(255, 255);
    std::vector<aam::Point2D> pt;

    for (int i = 0; i < TOTAL_POINTS_NUMBER; i++)
    {
        aam::Point2D facePoint;

        facePoint.y = verticesAData[i * 2 + 0];
        facePoint.x = verticesAData[i * 2 + 1];

        pt.push_back(facePoint);
    }

    try
    {
        cv::Mat targetImage = cv::imread("data/object_pixels.bmp",
                cv::IMREAD_GRAYSCALE);
        cv::Mat1b img;
        
        aam::CommonFunctions::drawObject(textureSize, targetPtNumbers, pt,
                img);

        if (img.rows != 255 || img.cols != 255)
        {
            std::cout << "%TEST_FAILED% time=0 testname=testDraw (drobjectTest) message=Invalid result image size" << std::endl;
        }
        else if (cv::countNonZero(targetImage != img) > 50)
        {
            std::cout << "%TEST_FAILED% time=0 testname=testDraw (drobjectTest) message=Invalid drawn object" << std::endl;
        }
    }
    catch (std::exception& e)
    {
        std::cout << "%TEST_FAILED% time=0 testname=testDraw (drobjectTest) message=Exception occured: " <<
                e.what() << std::endl;
    }
}

int main(int argc, char** argv)
{
    std::cout << "%SUITE_STARTING% drobjectTest" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% testDraw (drobjectTest)" << std::endl;
    testDraw();
    std::cout << "%TEST_FINISHED% time=0 testDraw (drobjectTest)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}
