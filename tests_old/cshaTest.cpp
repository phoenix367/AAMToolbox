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
 * File:   cshaTest.cpp
 * Author: Иван Губочкин
 *
 * Created on 24.08.2012, 16:15:49
 */

#include <stdlib.h>
#include <iostream>

#include "aam/AAMFunctions2D.h"
#include "aam/TrainModelLoader.h"
#include "aam/CommonFunctions.h"

/*
 * Simple C++ Test Suite
 */

void testCombineGray()
{
    std::cout << "cshaTest testCombineGray" << std::endl;

    aam::ShapeData shapeData;
    aam::AppearanceData appearanceData;

    aam::TrainModelLoader loader;
    loader.useGrayImages(true);

    try
    {
        for (int i = 0; i < 3; i++)
        {
            std::ostringstream stream;

            stream << "data/01-" << i + 1 << "m.dat";
            std::string markupFile = stream.str();

            stream.str(std::string());

            stream << "data/01-" << i + 1 << "m.jpg";
            std::string imageFile = stream.str();

            loader.load(markupFile, imageFile);
        }

        std::vector<aam::TrainModelInfo> trainData = loader.getModels();
        aam::AAMFunctions2D::makeShapeModel(1,
                aam::AAMFunctions2D::DEFAULT_PCA_CUT_THRESOLD,
                trainData, shapeData);
        aam::AAMFunctions2D::makeAppearanceModel(trainData,
                shapeData,
                aam::AAMFunctions2D::DEFAULT_PCA_CUT_THRESOLD,
                appearanceData);

        aam::ShapeAppearanceData shapeAppearance;
        aam::AAMFunctions2D::combineShapeAppearance(trainData,
                shapeData, appearanceData,
                aam::AAMFunctions2D::DEFAULT_PCA_CUT_THRESOLD,
                shapeAppearance);
    }
    catch (std::exception& e)
    {
        std::cout << "%TEST_FAILED% time=0 testname=testCombineGray (cshaTest) message=Exception occured: " <<
                e.what() << std::endl;
    }
}

int main(int argc, char** argv)
{
    std::cout << "%SUITE_STARTING% cshaTest" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% testCombineGray (cshaTest)" << std::endl;
    testCombineGray();
    std::cout << "%TEST_FINISHED% time=0 testCombineGray (cshaTest)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}
