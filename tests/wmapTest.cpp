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
 * File:   wmapTest.cpp
 * Author: Иван Губочкин
 *
 * Created on 01.10.2012, 13:42:14
 */

#include <stdlib.h>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <iterator>

#include "aam/CommonFunctions.h"

#define POINTS_COUNT            58
#define TRIANGLES_COUNT         93

aam::RealType s0Data[2 * POINTS_COUNT] =
{
    29.233948561134525,
    11.148359423376007,
    2,
    2.1303392507400645,
    18.094694140191947,
    25.524334211639939,
    9.463122050427387,
    13.487850875858413,
    25.492627768412092,
    50.673433180720934,
    55.195592709946084,
    45.823340585398967,
    41.451269575659524,
    46.039196835203711,
    56.274951516992957,
    58.790057046192175,
    60.360771606314586,
    58.842621968192447,
    62.051937847211889,
    55.42626158210831,
    52.438069348205431,
    58.967527259987122,
    70.45916288154632,
    73.297889546934698,
    72.088492132114936,
    68.071907756553486,
    55.316966783933339,
    89.895998627330414,
    114.31711805243123,
    149.77086144172995,
    132.86052225417413,
    148.95246416410328,
    130.4008827799552,
    148.73361694786621,
    113.06414018581776,
    87.921281125556646,
    53.629284698143266,
    204.63506969320042,
    184.40745959204355,
    189.14635471363829,
    187.11068624863964,
    214.20139369747852,
    231.03881900385107,
    230.27468627176245,
    228.15048964523993,
    214.52067178591955,
    240.43115452694269,
    263.43672566875523,
    284.65995084997957,
    303.27782955594819,
    313.50954991723847,
    313.4285537884403,
    306.15604600127205,
    286.96109313274883,
    263.50993123226209,
    239.30190146899429,
    214.72592311663453,
    189.21174941905377,
    21.360009450578218,
    31.324042370996381,
    58.915981051058338,
    92.469338706215524,
    104.49004013751517,
    154.66267309926297,
    167.73506538718419,
    201.81441377761882,
    228.51452752592667,
    243.56973842190132,
    40.830357837635972,
    50.271305032151361,
    66.216978580620719,
    81.778888382988328,
    97.449047651474359,
    83.251889852914871,
    66.525555090069531,
    52.085042741201846,
    164.3326524405914,
    176.73214855200172,
    194.60034842664169,
    209.5111167365464,
    219.17392682763796,
    207.13095060445977,
    192.38816684161947,
    177.5587294649489,
    147.18197607238187,
    147.40779256177171,
    163.87212288297451,
    163.82975430566961,
    147.41186749897565,
    126.26076504337925,
    106.8122209112629,
    89.095343201611399,
    88.713000029832813,
    106.63384978526568,
    111.30263457651591,
    57.752886957381861,
    104.77250687783476,
    119.62529208441515,
    137.78862890335387,
    184.77038613103605,
    137.6965511857959,
    119.64600422486785,
    98.988797848881063,
    252.20745364229776,
    242.64338251474248,
    227.85536041661169,
    211.00629258734051,
    189.96705635298378,
    163.80599599778651,
    114.65372637549632,
    66.613499762198444,
    42.472605427126837,
    26.449768413425772,
    13.284966048147112,
    6.0309874238302541,
    2
};

int trianglesData[3 * TRIANGLES_COUNT] =
{
    57, 10, 0,
    52, 44, 53,
    53, 44, 54,
    22, 45, 9,
    29, 41, 45,
    40, 29, 31,
    41, 29, 40,
    47, 41, 48,
    55, 54, 37,
    37, 54, 44,
    37, 56, 55,
    37, 33, 57,
    57, 56, 37,
    20, 25, 24,
    19, 25, 20,
    8, 7, 20,
    6, 19, 20,
    20, 7, 6,
    31, 29, 30,
    35, 30, 27,
    35, 27, 26,
    11, 12, 2,
    11, 0, 10,
    6, 4, 5,
    5, 19, 6,
    36, 4, 14,
    36, 35, 26,
    14, 35, 36,
    26, 5, 36,
    36, 5, 4,
    3, 4, 6,
    2, 12, 3,
    24, 25, 28,
    28, 25, 27,
    27, 30, 28,
    28, 30, 29,
    28, 29, 45,
    41, 40, 42,
    51, 50, 42,
    48, 41, 42,
    38, 37, 44,
    33, 37, 38,
    31, 33, 38,
    45, 41, 46,
    41, 47, 46,
    1, 11, 2,
    0, 11, 1,
    18, 25, 19,
    18, 5, 26,
    19, 5, 18,
    26, 27, 18,
    27, 25, 18,
    21, 20, 24,
    21, 22, 9,
    9, 8, 21,
    8, 20, 21,
    12, 16, 13,
    14, 4, 13,
    13, 3, 12,
    4, 3, 13,
    12, 11, 17,
    17, 16, 12,
    17, 11, 10,
    17, 10, 57,
    16, 17, 34,
    57, 33, 34,
    34, 17, 57,
    24, 28, 23,
    23, 21, 24,
    22, 21, 23,
    45, 22, 23,
    23, 28, 45,
    48, 42, 49,
    49, 42, 50,
    39, 38, 44,
    39, 42, 40,
    39, 40, 31,
    31, 38, 39,
    14, 13, 15,
    15, 13, 16,
    15, 35, 14,
    15, 34, 35,
    16, 34, 15,
    30, 35, 32,
    35, 34, 32,
    31, 30, 32,
    32, 33, 31,
    32, 34, 33,
    43, 39, 44,
    42, 39, 43,
    51, 42, 43,
    43, 52, 51,
    44, 52, 43
};

/*
 * Simple C++ Test Suite
 */

void testGetWarpMap()
{
    std::cout << "wmapTest testGetWarpMap" << std::endl;

    aam::Vertices2DList s0;
    std::vector<cv::Vec3i> triangles;

    for (int i = 0; i < POINTS_COUNT; i++)
    {
        s0.push_back(aam::Point2D(s0Data[i + POINTS_COUNT] - 1,
                s0Data[i] - 1));
    }
    
    for (int i = 0; i < TRIANGLES_COUNT; i++)
    {
        triangles.push_back(cv::Vec3i(trianglesData[i * 3],
                trianglesData[i * 3 + 1], trianglesData[i * 3 + 2]));
    }

    try
    {
        cv::Mat1i targetMap = cv::imread("data/warp_map.bmp",
                cv::IMREAD_GRAYSCALE);

        if (targetMap.empty())
        {
            std::cout << "%TEST_FAILED% time=0 testname=testGetWarpMap (wmapTest) message=Can't read target map image" << std::endl;
            return;
        }

        cv::Mat1i warpMap;
        
        aam::CommonFunctions::getWarpMap(s0, triangles, 
                cv::Size(targetMap.cols, targetMap.rows),
                warpMap);

        if (warpMap.size != targetMap.size)
        {
            std::cout << "%TEST_FAILED% time=0 testname=testGetWarpMap (wmapTest) message=Invalid warp map size" << std::endl;
        }
        else if (cv::countNonZero(warpMap - (targetMap - 1)))
        {
            std::cout << "%TEST_FAILED% time=0 testname=testGetWarpMap (wmapTest) message=Invalid warp map data" << std::endl;
        }
    }
    catch (std::exception& e)
    {
        std::cout << "%TEST_FAILED% time=0 testname=testGetWarpMap (wmapTest) message=Exception occured: " <<
                e.what() << std::endl;
    }
}

int main(int argc, char** argv)
{
    std::cout << "%SUITE_STARTING% wmapTest" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% testGetWarpMap (wmapTest)" << std::endl;
    testGetWarpMap();
    std::cout << "%TEST_FINISHED% time=0 testGetWarpMap (wmapTest)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}
