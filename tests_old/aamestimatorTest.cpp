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
 * File:   aamestimatorTest.cpp
 * Author: Иван Губочкин
 *
 * Created on 10.09.2012, 16:16:54
 */

#include <stdlib.h>
#include <iostream>
#include <exception>
#include <iosfwd>
#include <string>
#include <boost/spirit/include/classic.hpp>
#include <vector>
#include <fstream>

#include "aam/AAMEstimator.h"

using namespace BOOST_SPIRIT_CLASSIC_NS;

#define TRIANGLES_COUNT         93

int trianglesData[] =
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

bool loadModelInfo(const std::string& fileName,
        std::vector<aam::ModelPathType>& modelPaths)
{
    std::ifstream stream(fileName.c_str());
    std::vector<std::string> strData;

    rule<> quotedString =
            confix_p('"', (*anychar_p)[push_back_a(strData)], '"');
    rule<> item = quotedString >> ',' >> *space_p >>
            quotedString;
    
    if (!stream)
    {
        return false;
    }

    while (!stream.eof())
    {
        std::string line;
        std::getline(stream, line);

        if (!line.empty())
        {
            bool result = parse(line.c_str(), item, space_p).full;

            if (!result || strData.size() != 2)
            {
                std::cout << "Bad format of line: " << line << std::endl;
            }
            else
            {
                aam::ModelPathType modelPath(strData[0], strData[1]);
                modelPaths.push_back(modelPath);
            }
            
            strData.clear();
        }
    }

    stream.close();
    
    return true;
}

void testTrainGray()
{
    std::cout << "aamestimatorTest testTrainGray" << std::endl;

    aam::AAMEstimator estimator;
    std::vector<aam::ModelPathType> modelPaths;
    std::vector<cv::Vec3i> triangles;

    for (int i = 0; i < TRIANGLES_COUNT; i++)
    {
        triangles.push_back(cv::Vec3i(trianglesData[i * 3],
                trianglesData[i * 3 + 1], trianglesData[i * 3 + 2]));
    }

    if (!loadModelInfo("data/cootes_list.txt", modelPaths))
    {
        std::cout << "%TEST_FAILED% time=0 testname=testTrainGray (aamestimatorTest) message=Can' load model info list" << std::endl;
        return;
    }
    else if (modelPaths.empty())
    {
        std::cout << "%TEST_FAILED% time=0 testname=testTrainGray (aamestimatorTest) message=Empty model info list" << std::endl;
        return;
    }

    std::cout << "Found " << modelPaths.size() << " models." << std::endl <<
            "Start training..." << std::endl;

    try
    {
        aam::TrainOptions options;

        options.setPCACutThreshold(0.95);
        options.setGrayScale(true);
        options.setMultithreading(true);
        options.setAAMAlgorithm(aam::algorithm::conventional);
        options.setTriangles(triangles);

        estimator.setTrainOptions(options);
        estimator.train(modelPaths);
        estimator.save("data/aam_test.xml");
    }
    catch (std::exception& e)
    {
        std::cout << "%TEST_FAILED% time=0 testname=testTrainGray (aamestimatorTest) message=Exception occured: " <<
                e.what() << std::endl;
    }
}

void testTrainColor()
{
    std::cout << "aamestimatorTest testTrainColor" << std::endl;

    aam::AAMEstimator estimator;
    std::vector<aam::ModelPathType> modelPaths;
    std::vector<cv::Vec3i> triangles;

    for (int i = 0; i < TRIANGLES_COUNT; i++)
    {
        triangles.push_back(cv::Vec3i(trianglesData[i * 3],
                trianglesData[i * 3 + 1], trianglesData[i * 3 + 2]));
    }

    if (!loadModelInfo("data/cootes_list.txt", modelPaths))
    {
        std::cout << "%TEST_FAILED% time=0 testname=testTrainColor (aamestimatorTest) message=Can' load model info list" << std::endl;
        return;
    }
    else if (modelPaths.empty())
    {
        std::cout << "%TEST_FAILED% time=0 testname=testTrainColor (aamestimatorTest) message=Empty model info list" << std::endl;
        return;
    }

    std::cout << "Found " << modelPaths.size() << " models." << std::endl <<
            "Start training..." << std::endl;

    try
    {
        aam::TrainOptions options;

        options.setPCACutThreshold(0.95);
        options.setGrayScale(false);
        options.setMultithreading(true);
        options.setAAMAlgorithm(aam::algorithm::conventional);
        options.setTriangles(triangles);

        estimator.setTrainOptions(options);
        estimator.train(modelPaths);
        estimator.save("data/aam_c_test.xml");
    }
    catch (std::exception& e)
    {
        std::cout << "%TEST_FAILED% time=0 testname=testTrainColor (aamestimatorTest) message=Exception occured: " <<
                e.what() << std::endl;
    }
}

void testTrainICGray()
{
    std::cout << "aamestimatorTest testTrainICGray" << std::endl;

    aam::AAMEstimator estimator;
    std::vector<aam::ModelPathType> modelPaths;
    std::vector<cv::Vec3i> triangles;

    for (int i = 0; i < TRIANGLES_COUNT; i++)
    {
        triangles.push_back(cv::Vec3i(trianglesData[i * 3],
                trianglesData[i * 3 + 1], trianglesData[i * 3 + 2]));
    }

    if (!loadModelInfo("data/cootes_list.txt", modelPaths))
    {
        std::cout << "%TEST_FAILED% time=0 testname=testTrainICGray (aamestimatorTest) message=Can' load model info list" << std::endl;
        return;
    }
    else if (modelPaths.empty())
    {
        std::cout << "%TEST_FAILED% time=0 testname=testTrainICGray (aamestimatorTest) message=Empty model info list" << std::endl;
        return;
    }

    std::vector<aam::ModelPathType> tmp(modelPaths.begin(),
            modelPaths.begin() + 10);

    std::cout << "Found " << modelPaths.size() << " models." << std::endl <<
            "Start training..." << std::endl;

    try
    {
        aam::TrainOptions options;

        options.setPCACutThreshold(0.95);
        options.setGrayScale(true);
        options.setMultithreading(true);
        options.setAAMAlgorithm(aam::algorithm::inverseComposition);
        options.setTriangles(triangles);

        estimator.setTrainOptions(options);
        estimator.train(modelPaths);
        estimator.save("data/aam_ic_test.xml");
    }
    catch (std::exception& e)
    {
        std::cout << "%TEST_FAILED% time=0 testname=testTrainICGray (aamestimatorTest) message=Exception occured: " <<
                e.what() << std::endl;
    }
}

void testTrainICColor()
{
    std::cout << "aamestimatorTest testTrainICColor" << std::endl;

    aam::AAMEstimator estimator;
    std::vector<aam::ModelPathType> modelPaths;
    std::vector<cv::Vec3i> triangles;

    for (int i = 0; i < TRIANGLES_COUNT; i++)
    {
        triangles.push_back(cv::Vec3i(trianglesData[i * 3],
                trianglesData[i * 3 + 1], trianglesData[i * 3 + 2]));
    }

    if (!loadModelInfo("data/cootes_list.txt", modelPaths))
    {
        std::cout << "%TEST_FAILED% time=0 testname=testTrainICColor (aamestimatorTest) message=Can' load model info list" << std::endl;
        return;
    }
    else if (modelPaths.empty())
    {
        std::cout << "%TEST_FAILED% time=0 testname=testTrainICColor (aamestimatorTest) message=Empty model info list" << std::endl;
        return;
    }

    std::vector<aam::ModelPathType> tmp(modelPaths.begin(),
            modelPaths.begin() + 10);

    std::cout << "Found " << modelPaths.size() << " models." << std::endl <<
            "Start training..." << std::endl;

    try
    {
        aam::TrainOptions options;

        options.setPCACutThreshold(0.95);
        options.setGrayScale(false);
        options.setMultithreading(true);
        options.setAAMAlgorithm(aam::algorithm::inverseComposition);
        options.setTriangles(triangles);

        estimator.setTrainOptions(options);
        estimator.train(modelPaths);
        estimator.save("data/aam_ic_c_test.xml");
    }
    catch (std::exception& e)
    {
        std::cout << "%TEST_FAILED% time=0 testname=testTrainICColor (aamestimatorTest) message=Exception occured: " <<
                e.what() << std::endl;
    }
}

int main(int argc, char** argv)
{
    std::cout << "%SUITE_STARTING% aamestimatorTest" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% testTrainGray (aamestimatorTest)" << std::endl;
    testTrainGray();
    std::cout << "%TEST_FINISHED% time=0 testTrainGray (aamestimatorTest)" << std::endl;

    std::cout << "%TEST_STARTED% testTrainColor (aamestimatorTest)" << std::endl;
    testTrainColor();
    std::cout << "%TEST_FINISHED% time=0 testTrainColor (aamestimatorTest)" << std::endl;

    std::cout << "%TEST_STARTED% testTrainICGray (aamestimatorTest)" << std::endl;
    testTrainICGray();
    std::cout << "%TEST_FINISHED% time=0 testTrainICGray (aamestimatorTest)" << std::endl;

    std::cout << "%TEST_STARTED% testTrainICColor (aamestimatorTest)" << std::endl;
    testTrainICColor();
    std::cout << "%TEST_FINISHED% time=0 testTrainICColor (aamestimatorTest)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}
