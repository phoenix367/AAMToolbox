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
 * File:   aldataTest.cpp
 * Author: Иван Губочкин
 *
 * Created on 09.08.2012, 23:55:09
 */

#include <stdlib.h>
#include <iostream>
#include <exception>
#include <vector>

#include "aam/AAMFunctions2D.h"
#include "aam/TrainModelLoader.h"

/*
 * Simple C++ Test Suite
 */

#define TOTAL_POINTS_NUMBER             (58)

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

aam::RealType verticesBData[2 * TOTAL_POINTS_NUMBER] =
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

aam::RealType alignedVerticesData[2 * TOTAL_POINTS_NUMBER] =
{
    21.076154931359774,
    38.213049950695279,
    60.286576082441805,
    84.318089492531342,
    105.3352479972213,
    122.26978027901133,
    131.06286749588909,
    123.7040051778248,
    106.31713265916839,
    83.922206885437859,
    58.524829896751612,
    39.275199623302996,
    20.061280421185952,
    -42.219516036479867,
    -50.122887292515031,
    -50.015754078520374,
    -46.787132745131451,
    -40.66319341078151,
    -40.82984507699544,
    -39.952032806596684,
    -40.082973401479059,
    -42.760964152004455,
    -50.973831359579769,
    -52.113524819743283,
    -48.209453953501118,
    -41.255317110527812,
    -41.112472825201579,
    -42.002188786044201,
    -41.859344500717967,
    -56.719913422172759,
    -67.970942916035369,
    -73.348010574868951,
    -65.504157771053016,
    -46.444986544706055,
    -55.44927936712687,
    -67.43527684606201,
    -73.118779633989405,
    -66.851996014313229,
    -47.590462050420797,
    33.785216704923585,
    39.337778897968604,
    42.280711660705052,
    40.179880097035799,
    34.648064462432153,
    61.268460744388896,
    64.449467316002398,
    62.598613251654051,
    -42.383106880247475,
    -13.08165902531905,
    -4.856888127299853,
    10.333923304136489,
    17.216638004446668,
    21.073094108913434,
    17.892087537299933,
    11.672918679399164,
    -5.4163615781609291,
    -13.379251286415359,
    -40.5917712681184,
    -84.967990142070533,
    -83.756874539243896,
    -73.407464696667759,
    -57.990483146798226,
    -43.617965533541373,
    -25.258051220935389,
    -0.94084924019338712,
    24.194646558728106,
    44.167341126805383,
    61.054258646819981,
    75.887959364940741,
    82.723059303475509,
    86.531900646166861,
    63.60130880246296,
    49.383539164976213,
    40.304763377445951,
    23.191675738998168,
    17.210580689974446,
    31.333120803910386,
    42.441306012446759,
    53.537587530539284,
    -61.507853873285924,
    -49.498049013463095,
    -38.41367118581443,
    -27.269774905946473,
    -18.107673285309264,
    -30.212707668682942,
    -40.312140011938162,
    -52.417174395311825,
    9.9588515859048279,
    22.941698239677262,
    51.127260015329874,
    70.388793979222328,
    79.693739885185778,
    -12.221807759836361,
    -22.452180697973972,
    -53.794941664352393,
    -71.881071096749778,
    -79.72492390056567,
    -50.515644746741749,
    -8.0766022622708125,
    -0.97962113397128248,
    6.0578415421089806,
    47.357190566416399,
    14.377841963678998,
    1.2997657863557535,
    -12.846581708467891,
    -8.0320483229417352,
    -11.721852761194564,
    -24.74041048629854,
    -29.605619456046444,
    -14.391000643722402,
    0.78790709727008901,
    13.865983274593331,
    27.91710124586616,
    22.670974181914968,
    13.496968870833905,
    11.158063498287605
};

void testAlign()
{
    std::cout << "aldataTest testAlign" << std::endl;
    aam::Point2D targetOffsetV(289.10344827586209, 311.4655172413793);

    try
    {
        aam::TForm tform;
        aam::Vertices2DList result;
        aam::Vertices2DList verticesA(TOTAL_POINTS_NUMBER),
                verticesB(TOTAL_POINTS_NUMBER),
                targetVertices(TOTAL_POINTS_NUMBER);

        for (int i = 0; i < TOTAL_POINTS_NUMBER; i++)
        {
            verticesA[i].x = verticesAData[i * 2];
            verticesA[i].y = verticesAData[i * 2 + 1];
            verticesB[i].x = verticesBData[i * 2];
            verticesB[i].y = verticesBData[i * 2 + 1];
            targetVertices[i].x = alignedVerticesData[i];
            targetVertices[i].y = alignedVerticesData[
                    TOTAL_POINTS_NUMBER + i];
        }

        aam::AAMFunctions2D::alignData(verticesA,
                verticesB, result, tform);

        if (result.size() != TOTAL_POINTS_NUMBER)
        {
            std::cout << "%TEST_FAILED% time=0 testname=testAlign (aldataTest) message=Invalid result models vertices array size" << std::endl;
        }
        else if (fabs(tform.offsetSX - 1.0087528652811386) > 1e-6)
        {
            std::cout << "%TEST_FAILED% time=0 testname=testAlign (aldataTest) message=Invalid offset X" << std::endl;
        }
        else if (fabs(tform.offsetSY - 0.011903690443852661) > 1e-6)
        {
            std::cout << "%TEST_FAILED% time=0 testname=testAlign (aldataTest) message=Invalid offset Y" << std::endl;
        }
        else if (fabs(targetOffsetV.x - tform.offsetV.x) > 1e-6 ||
                 fabs(targetOffsetV.y - tform.offsetV.y) > 1e-6)
        {
            std::cout << "%TEST_FAILED% time=0 testname=testAlign (aldataTest) message=Invalid shape offset" << std::endl;
        }
        else
        {
            for (int i = 0; i < result.size(); i++)
            {
                if (fabs(result[i].x - targetVertices[i].x) > 1e-6 ||
                    fabs(result[i].y - targetVertices[i].y) > 1e-6)
                {
                    std::cout << "%TEST_FAILED% time=0 testname=testAlign (aldataTest) message=Invalid result vertices coords" << std::endl;
                    break;
                }
            }
        }
    }
    catch (std::exception& e)
    {
        std::cout << "%TEST_FAILED% time=0 testname=testAlign (aldataTest) message=Exception occured: " <<
                e.what() << std::endl;
    }
}

void testAlignInverse()
{
    std::cout << "aldataTest testAlignInverse" << std::endl;

    try
    {
        aam::TForm tform;

        tform.offsetV = aam::Point2D(289.10344827586209, 311.4655172413793);
        tform.offsetSX = 1.0087528652811386;
        tform.offsetSY = 0.011903690443852661;
        
        aam::Vertices2DList result;
        aam::Vertices2DList verticesA(TOTAL_POINTS_NUMBER),
                targetVertices(TOTAL_POINTS_NUMBER);

        for (int i = 0; i < TOTAL_POINTS_NUMBER; i++)
        {
            verticesA[i].x = alignedVerticesData[i];
            verticesA[i].y = alignedVerticesData[
                    TOTAL_POINTS_NUMBER + i];
            targetVertices[i].x = verticesAData[i * 2];
            targetVertices[i].y = verticesAData[i * 2 + 1];
        }

        aam::AAMFunctions2D::alignDataInverse(verticesA,
                tform, result);
        if (result.size() != TOTAL_POINTS_NUMBER)
        {
            std::cout << "%TEST_FAILED% time=0 testname=testAlignInverse (aldataTest) message=Invalid result models vertices array size" << std::endl;
        }
        else
        {
            for (int i = 0; i < result.size(); i++)
            {
                if (fabs(result[i].x - targetVertices[i].x) > 1e-6 ||
                    fabs(result[i].y - targetVertices[i].y) > 1e-6)
                {
                    std::cout << "%TEST_FAILED% time=0 testname=testAlignInverse (aldataTest) message=Invalid result vertices coords" << std::endl;
                    break;
                }
            }
        }
    }
    catch (std::exception& e)
    {
        std::cout << "%TEST_FAILED% time=0 testname=testAlignInverse (aldataTest) message=Exception occured: " <<
                e.what() << std::endl;
    }
}

int main(int argc, char** argv)
{
    std::cout << "%SUITE_STARTING% aldataTest" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% testAlign (aldataTest)" << std::endl;
    testAlign();
    std::cout << "%TEST_FINISHED% time=0 testAlign (aldataTest)" << std::endl;

    std::cout << "%TEST_STARTED% testAlignInverse (aldataTest)" << std::endl;
    testAlignInverse();
    std::cout << "%TEST_FINISHED% time=0 testAlignInverse (aldataTest)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}
