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
 * File:   reignoiseTest.cpp
 * Author: Иван Губочкин
 *
 * Created on 23.08.2012, 23:51:05
 */

#include <stdlib.h>
#include <iostream>
#include <exception>

#include "aam/CommonFunctions.h"

/*
 * Simple C++ Test Suite
 */

void testRemoveNoise()
{
    std::cout << "reignoiseTest testRemoveNoise" << std::endl;

    aam::RealType eigVectorsData[] =
    {
        1, 5, 9,
        2, 6, 10,
        3, 7, 11,
        4, 6, 12
    };

    aam::RealType eigValuesData[] =
    {
        1, 0.3, 1e-4
    };

    try
    {
        aam::RealMatrix eigVectors(4, 3, eigVectorsData);
        aam::RealMatrix targetEigVectors(eigVectors.colRange(0, 2));
        aam::RealMatrix eigValues(3, 1, eigValuesData);
        aam::RealMatrix targetEigValues(eigValues.rowRange(0, 2));

        aam::CommonFunctions::removeEigNoise(eigVectors, eigValues, 0.99);

        if (eigVectors.rows != 4 || eigVectors.cols != 2)
        {
            std::cout << "%TEST_FAILED% time=0 testname=testRemoveNoise (reignoiseTest) message=Invalid eigen vectors matrix size" << std::endl;
        }
        else if (eigValues.rows != 2 || eigValues.cols != 1)
        {
            std::cout << "%TEST_FAILED% time=0 testname=testRemoveNoise (reignoiseTest) message=Invalid eigen values array size" << std::endl;
        }
        else if (cv::countNonZero(cv::abs(
                eigVectors - targetEigVectors) > 1e-6))
        {
            std::cout << "%TEST_FAILED% time=0 testname=testRemoveNoise (reignoiseTest) message=Invalid eigen vectors matrix data" << std::endl;
        }
        else if (cv::countNonZero(cv::abs(
                eigValues - targetEigValues) > 1e-6))
        {
            std::cout << "%TEST_FAILED% time=0 testname=testRemoveNoise (reignoiseTest) message=Invalid eigen values array data" << std::endl;
        }
    }
    catch (std::exception& e)
    {
        std::cout << "%TEST_FAILED% time=0 testname=testRemoveNoise (reignoiseTest) message=Exception occured: " <<
                e.what() << std::endl;
    }
}

void testRemoveNoiseOne()
{
    std::cout << "reignoiseTest testRemoveNoiseOne" << std::endl;

    aam::RealType eigVectorsData[] =
    {
        1,
        2,
        3,
        4
    };

    aam::RealType eigValuesData[] =
    {
        1
    };

    try
    {
        aam::RealMatrix eigVectors(4, 1, eigVectorsData);
        aam::RealMatrix targetEigVectors(eigVectors);
        aam::RealMatrix eigValues(1, 1, eigValuesData);
        aam::RealMatrix targetEigValues(eigValues);

        aam::CommonFunctions::removeEigNoise(eigVectors, eigValues, 0.99);

        if (eigVectors.rows != 4 || eigVectors.cols != 1)
        {
            std::cout << "%TEST_FAILED% time=0 testname=testRemoveNoiseOne (reignoiseTest) message=Invalid eigen vectors matrix size" << std::endl;
        }
        else if (eigValues.rows != 1 || eigValues.cols != 1)
        {
            std::cout << "%TEST_FAILED% time=0 testname=testRemoveNoiseOne (reignoiseTest) message=Invalid eigen values array size" << std::endl;
        }
        else if (cv::countNonZero(cv::abs(
                eigVectors - targetEigVectors) > 1e-6))
        {
            std::cout << "%TEST_FAILED% time=0 testname=testRemoveNoiseOne (reignoiseTest) message=Invalid eigen vectors matrix data" << std::endl;
        }
        else if (cv::countNonZero(cv::abs(
                eigValues - targetEigValues) > 1e-6))
        {
            std::cout << "%TEST_FAILED% time=0 testname=testRemoveNoiseOne (reignoiseTest) message=Invalid eigen values array data" << std::endl;
        }
    }
    catch (std::exception& e)
    {
        std::cout << "%TEST_FAILED% time=0 testname=testRemoveNoiseOne (reignoiseTest) message=Exception occured: " <<
                e.what() << std::endl;
    }
}

void testRemoveNoiseEmpty()
{
    std::cout << "reignoiseTest testRemoveNoiseEmpty" << std::endl;

    try
    {
        aam::RealMatrix eigVectors;
        aam::RealMatrix eigValues;

        aam::CommonFunctions::removeEigNoise(eigVectors, eigValues, 0.99);

        if (!eigVectors.empty())
        {
            std::cout << "%TEST_FAILED% time=0 testname=testRemoveNoiseEmpty (reignoiseTest) message=Eigen vectors matrix isn't empty" << std::endl;
        }
        else if (!eigValues.empty())
        {
            std::cout << "%TEST_FAILED% time=0 testname=testRemoveNoiseEmpty (reignoiseTest) message=Eigen values array isn't empty" << std::endl;
        }
    }
    catch (std::exception& e)
    {
        std::cout << "%TEST_FAILED% time=0 testname=testRemoveNoiseEmpty (reignoiseTest) message=Exception occured: " <<
                e.what() << std::endl;
    }
}

int main(int argc, char** argv)
{
    std::cout << "%SUITE_STARTING% reignoiseTest" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% testRemoveNoise (reignoiseTest)" << std::endl;
    testRemoveNoise();
    std::cout << "%TEST_FINISHED% time=0 testRemoveNoise (reignoiseTest)" << std::endl;

    std::cout << "%TEST_STARTED% testRemoveNoiseOne (reignoiseTest)" << std::endl;
    testRemoveNoiseOne();
    std::cout << "%TEST_FINISHED% time=0 testRemoveNoiseOne (reignoiseTest)" << std::endl;

    std::cout << "%TEST_STARTED% testRemoveNoiseEmpty (reignoiseTest)" << std::endl;
    testRemoveNoiseEmpty();
    std::cout << "%TEST_FINISHED% time=0 testRemoveNoiseEmpty (reignoiseTest)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}
