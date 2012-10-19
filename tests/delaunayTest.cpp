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
 * File:   delaunayTest.cpp
 * Author: Иван Губочкин
 *
 * Created on 13.08.2012, 23:17:17
 */

#include <stdlib.h>
#include <iostream>
#include <set>
#include <opencv2/core/core.hpp>

#include "aam/aam.h"
#include "aam/CommonFunctions.h"

/*
 * Simple C++ Test Suite
 */

#define TOTAL_POINTS_NUMBER             (58)
#define TRIANGLES_NUMBER                (95)

aam::RealType verticesAData[2 * TOTAL_POINTS_NUMBER] =
{
   309,   227,
   326,   228,
   348,   238,
   372,   253,
   393,   267,
   410,   285,
   419,   309,
   412,   334,
   395,   354,
   373,   371,
   348,   386,
   329,   393,
   310,   397,
   248,   375,
   240,   361,
   240,   352,
   243,   335,
   249,   329,
   249,   343,
   250,   354,
   250,   365,
   246,   251,
   238,   263,
   237,   274,
   241,   285,
   248,   294,
   248,   282,
   247,   272,
   247,   260,
   233,   322,
   222,   335,
   217,   363,
   225,   382,
   244,   391,
   234,   300,
   222,   290,
   216,   259,
   222,   241,
   241,   233,
   322,   261,
   328,   303,
   331,   310,
   329,   317,
   324,   358,
   350,   325,
   353,   312,
   351,   298,
   247,   304,
   276,   300,
   284,   287,
   299,   282,
   306,   297,
   310,   312,
   307,   325,
   301,   339,
   284,   334,
   276,   325,
   249,   323
};

int targetTriData[3 * TRIANGLES_NUMBER] =
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

bool checkTriangle(const cv::Vec3i& tri,
        const cv::vector<cv::Vec3i>& target)
{
    cv::Vec3i tri1(tri[1], tri[0], tri[2]);
    cv::Vec3i tri2(tri[2], tri[0], tri[1]);
    cv::Vec3i tri3(tri[2], tri[1], tri[0]);
    cv::Vec3i tri4(tri[0], tri[2], tri[1]);
    cv::Vec3i tri5(tri[1], tri[2], tri[0]);

    for (int i = 0; i < target.size(); i++)
    {
        if (tri == target[i])
        {
            return true;
        }
        else if (tri1 == target[i])
        {
            return true;
        }
        else if (tri2 == target[i])
        {
            return true;
        }
        else if (tri3 == target[i])
        {
            return true;
        }
        else if (tri4 == target[i])
        {
            return true;
        }
        else if (tri5 == target[i])
        {
            return true;
        }
    }
    
    return false;
}

void testDelaunay()
{
    std::cout << "delaunayTest testDelaunay" << std::endl;
    aam::Vertices2DList vertices(TOTAL_POINTS_NUMBER);

    for (int i = 0; i < TOTAL_POINTS_NUMBER; i++)
    {
        vertices[i].x = verticesAData[2 * i];
        vertices[i].y = verticesAData[2 * i + 1];
    }

    std::vector<cv::Vec3i> targetTrinagles(TRIANGLES_NUMBER);

    for (int i = 0; i < TRIANGLES_NUMBER; i++)
    {
        targetTrinagles[i] = cv::Vec3i(&targetTriData[i * 3]);
    }
    
    try
    {
        std::vector<cv::Vec3i> result;
        aam::CommonFunctions::delaunay(vertices, result);

        if (result.size() != TRIANGLES_NUMBER)
        {
            std::cout << "%TEST_FAILED% time=0 testname=testDelaunay (delaunayTest) message=Invalid triangle list size" << std::endl;
        }
        else
        {
            // Check for duplicates
            std::vector<cv::Vec3i>::iterator endSeqIt = std::unique(
                    result.begin(), result.end());
            if (endSeqIt - result.begin() != TRIANGLES_NUMBER)
            {
                std::cout << "%TEST_FAILED% time=0 testname=testDelaunay (delaunayTest) message=Duplicated triangles found" << std::endl;
                return;
            }

            for (int i = 0; i < result.size(); i++)
            {
                if (!checkTriangle(result[i], targetTrinagles))
                {
                    std::cout << "%TEST_FAILED% time=0 testname=testDelaunay (delaunayTest) message=Invalid triangle data" << std::endl;
                    break;
                }
            }
        }
    }
    catch (std::exception& e)
    {
        std::cout << "%TEST_FAILED% time=0 testname=testDelaunay (delaunayTest) message=Exception occured: " <<
                e.what() << std::endl;
    }
}

void testEmpty()
{
    std::cout << "delaunayTest testEmpty" << std::endl;

    try
    {
        aam::Vertices2DList vertices;

        std::vector<cv::Vec3i> result;
        aam::CommonFunctions::delaunay(vertices, result);

        if (!result.empty())
        {
            std::cout << "%TEST_FAILED% time=0 testname=testDelaunay (delaunayTest) message=Triangulation result is not empty" << std::endl;
        }
    }
    catch (std::exception& e)
    {
        std::cout << "%TEST_FAILED% time=0 testname=testEmpty (delaunayTest) message=Exception occured: " <<
                e.what() << std::endl;
    }
}

int main(int argc, char** argv)
{
    std::cout << "%SUITE_STARTING% delaunayTest" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% testDelaunay (delaunayTest)" << std::endl;
    testDelaunay();
    std::cout << "%TEST_FINISHED% time=0 testDelaunay (delaunayTest)" << std::endl;

    std::cout << "%TEST_STARTED% testEmpty (delaunayTest)" << std::endl;
    testEmpty();
    std::cout << "%TEST_FINISHED% time=0 testEmpty (delaunayTest)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}
