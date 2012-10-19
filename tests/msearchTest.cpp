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
 * File:   msearchTest.cpp
 * Author: Иван Губочкин
 *
 * Created on 08.09.2012, 22:56:16
 */

#include <stdlib.h>
#include <iostream>
#include <exception>
#include <iosfwd>
#include <iterator>

#include "aam/AAMFunctions2D.h"
#include "aam/TrainModelLoader.h"
#include "aam/CommonFunctions.h"

/*
 * Simple C++ Test Suite
 */

void testTrainModel()
{
    std::cout << "msearchTest testTrainModel" << std::endl;

    aam::ShapeData shapeData;
    aam::AppearanceData appearanceData;

    aam::TrainModelLoader loader;
    loader.useGrayImages(true);

    try
    {
        for (int i = 0; i < 3; i++)
        {
            std::ostringstream stream;

            stream << "data/IMM/01-" << i + 1 << "m.dat";
            std::string markupFile = stream.str();

            stream.str(std::string());

            stream << "data/IMM/01-" << i + 1 << "m.jpg";
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

        aam::RealMatrix R;
        aam::AAMFunctions2D::makeSearchModel(shapeAppearance, shapeData,
                appearanceData, trainData, R);

        cv::FileStorage storage("data/R_target.xml", cv::FileStorage::READ);
        aam::RealMatrix targetR;
        storage["R"] >> targetR;

        if (R.cols != targetR.cols || R.rows != targetR.rows)
        {
            std::cout << "%TEST_FAILED% time=0 testname=testTrainModel (msearchTest) message=Invalid R matrix size" << std::endl;
        }
        else if (cv::countNonZero(cv::abs(R - targetR) > 1e-12))
        {
            std::cout << "%TEST_FAILED% time=0 testname=testTrainModel (msearchTest) message=Invalid R matrix data" << std::endl;
        }
    }
    catch (std::exception& e)
    {
        std::cout << "%TEST_FAILED% time=0 testname=testTrainModel (msearchTest) message=Exception occured: " <<
                e.what() << std::endl;
    }
}

void testTrainModelMt()
{
    std::cout << "msearchTest testTrainModelMt" << std::endl;

    aam::ShapeData shapeData;
    aam::AppearanceData appearanceData;

    aam::TrainModelLoader loader;
    loader.useGrayImages(true);

    try
    {
        for (int i = 0; i < 3; i++)
        {
            std::ostringstream stream;

            stream << "data/IMM/01-" << i + 1 << "m.dat";
            std::string markupFile = stream.str();

            stream.str(std::string());

            stream << "data/IMM/01-" << i + 1 << "m.jpg";
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

        aam::RealMatrix R;
        aam::AAMFunctions2D::makeSearchModel_mt(shapeAppearance, shapeData,
                appearanceData, trainData, R);

        cv::FileStorage storage("data/R_target.xml", cv::FileStorage::READ);
        aam::RealMatrix targetR;
        storage["R"] >> targetR;

        if (R.cols != targetR.cols || R.rows != targetR.rows)
        {
            std::cout << "%TEST_FAILED% time=0 testname=testTrainModelMt (msearchTest) message=Invalid R matrix size" << std::endl;
        }
        else if (cv::countNonZero(cv::abs(R - targetR) > 1e-12))
        {
            std::cout << "%TEST_FAILED% time=0 testname=testTrainModelMt (msearchTest) message=Invalid R matrix data" << std::endl;
        }
    }
    catch (std::exception& e)
    {
        std::cout << "%TEST_FAILED% time=0 testname=testTrainModelMt (msearchTest) message=Exception occured: " <<
                e.what() << std::endl;
    }
}

int main(int argc, char** argv)
{
    std::cout << "%SUITE_STARTING% msearchTest" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% testTrainModel (msearchTest)" << std::endl;
    testTrainModel();
    std::cout << "%TEST_FINISHED% time=0 testTrainModel (msearchTest)" << std::endl;

    std::cout << "%TEST_STARTED% testTrainModelMt (msearchTest)" << std::endl;
    testTrainModelMt();
    std::cout << "%TEST_FINISHED% time=0 testTrainModelMt (msearchTest)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}
