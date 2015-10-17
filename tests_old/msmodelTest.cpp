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
 * File:   msmodelTest.cpp
 * Author: Иван Губочкин
 *
 * Created on 10.08.2012, 23:34:38
 */

#include <stdlib.h>
#include <iostream>

#include "aam/TrainModelInfo.h"
#include "aam/AAMFunctions2D.h"

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

void testMakeShape()
{
    std::cout << "msmodelTest testMakeShape" << std::endl;

    std::vector<aam::TrainModelInfo> models(2);
    aam::Vertices2DList verticesA(TOTAL_POINTS_NUMBER),
            verticesB(TOTAL_POINTS_NUMBER);

    for (int i = 0; i < TOTAL_POINTS_NUMBER; i++)
    {
        verticesA[i].x = verticesAData[i * 2];
        verticesA[i].y = verticesAData[i * 2 + 1];
        verticesB[i].x = verticesBData[i * 2];
        verticesB[i].y = verticesBData[i * 2 + 1];
    }

    try
    {
        models[0].setVertices(verticesA);
        models[1].setVertices(verticesB);

        aam::ShapeData shapeData;
        aam::AAMFunctions2D::makeShapeModel(1,
                aam::AAMFunctions2D::DEFAULT_PCA_CUT_THRESOLD,
                models, shapeData);

        if (fabs(shapeData.rVariance - 1.2224311632926757e-006) > 1e-6 )
        {
            std::cout << "%TEST_FAILED% time=0 testname=testMakeShape (msmodelTest) message=Invalid angle variance value" << std::endl;
        }
        else if (fabs(shapeData.sVariance - 0.033839399224875541) > 1e-6)
        {
            std::cout << "%TEST_FAILED% time=0 testname=testMakeShape (msmodelTest) message=Invalid S variance value" << std::endl;
        }
        else if (shapeData.textureSize.width != 255 ||
                shapeData.textureSize.height != 255)
        {
            std::cout << "%TEST_FAILED% time=0 testname=testMakeShape (msmodelTest) message=Invalid texture size" << std::endl;
        }
    }
    catch (std::exception& e)
    {
        std::cout << "%TEST_FAILED% time=0 testname=testMakeShape (msmodelTest) message=Exception occured: " <<
                e.what() << std::endl;
    }
}

int main(int argc, char** argv)
{
    std::cout << "%SUITE_STARTING% msmodelTest" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% testMakeShape (msmodelTest)" << std::endl;
    testMakeShape();
    std::cout << "%TEST_FINISHED% time=0 testMakeShape (msmodelTest)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}
