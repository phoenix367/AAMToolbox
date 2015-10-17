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
 * File:   makeappICTest.cpp
 * Author: Иван Губочкин
 *
 * Created on 03.10.2012, 18:37:26
 */

#include <stdlib.h>
#include <iostream>
#include <opencv/highgui.h>

#include "aam/AAMFunctions2D.h"
#include "aam/TrainModelLoader.h"

/*
 * Simple C++ Test Suite
 */

void testAppearanceIC()
{
    std::cout << "makeappICTest testAppearanceIC" << std::endl;
    aam::AppearanceDataIC model;
    aam::TrainModelLoader loader;
    loader.useGrayImages(true);

    try
    {
        for (int i = 0; i < 6; i++)
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
        aam::AAMFunctions2D::makeShapeModelIC(1,
                aam::AAMFunctions2D::DEFAULT_PCA_CUT_THRESOLD,
                trainData, model);
        aam::AAMFunctions2D::makeAppearanceModelIC(
                aam::AAMFunctions2D::DEFAULT_PCA_CUT_THRESOLD,
                trainData, model);

        cv::Mat img;
        aam::AAMFunctions2D::vector2Appearance(model.A0, model.mask,
                model.textureSize, img);
        cv::normalize(img, img, 1, 0, cv::NORM_MINMAX);
        cv::imshow("test", img);
        cv::waitKey(0);
    }
    catch (std::exception& e)
    {
        std::cout << "%TEST_FAILED% time=0 testname=testAppearanceIC (makeappICTest) message=Exception occured: " <<
                e.what() << std::endl;
    }
}

void testAppearanceICColor()
{
    std::cout << "makeappICTest testAppearanceICColor" << std::endl;
    aam::AppearanceDataIC model;
    aam::TrainModelLoader loader;
    loader.useGrayImages(false);

    try
    {
        for (int i = 0; i < 6; i++)
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
        aam::AAMFunctions2D::makeShapeModelIC(1,
                aam::AAMFunctions2D::DEFAULT_PCA_CUT_THRESOLD,
                trainData, model);
        aam::AAMFunctions2D::makeAppearanceModelIC(
                aam::AAMFunctions2D::DEFAULT_PCA_CUT_THRESOLD,
                trainData, model);

        cv::Mat img;
        aam::AAMFunctions2D::vector2Appearance(model.A0, model.mask,
                model.textureSize, img);
        cv::normalize(img, img, 1, 0, cv::NORM_MINMAX);
        cv::imshow("test", img);
        cv::waitKey(0);
    }
    catch (std::exception& e)
    {
        std::cout << "%TEST_FAILED% time=0 testname=testAppearanceICColor (makeappICTest) message=Exception occured: " <<
                e.what() << std::endl;
    }
}

int main(int argc, char** argv)
{
    std::cout << "%SUITE_STARTING% makeappICTest" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% testAppearanceIC (makeappICTest)" << std::endl;
    testAppearanceIC();
    std::cout << "%TEST_FINISHED% time=0 testAppearanceIC (makeappICTest)" << std::endl;

    std::cout << "%TEST_STARTED% testAppearanceICColor (makeappICTest)\n" << std::endl;
    testAppearanceICColor();
    std::cout << "%TEST_FINISHED% time=0 testAppearanceICColor (makeappICTest)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}
