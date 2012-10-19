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
 * File:   pcaTest.cpp
 * Author: Иван Губочкин
 *
 * Created on 12.08.2012, 22:51:41
 */

#include <stdlib.h>
#include <iostream>

#include "aam/CommonFunctions.h"
#include "aam/aam.h"

/*
 * Simple C++ Test Suite
 */

void testPCA()
{
    std::cout << "pcaTest testPCA" << std::endl;

    aam::RealType srcData[] =
    {
        1, 2,
        3, 4,
        5, 6,
        7, 8,
        9, 10,
        11, 12
    };

    aam::RealType meanData[] =
    {
        1.5,
        3.5,
        5.5,
        7.5,
        9.5,
        11.5
    };

    aam::RealType eigValuesData[] =
    {
        3,
        0
    };

    cv::Mat m(6, 2, aam::OpenCVRealType::type, srcData);
    cv::Mat targetMeans(6, 1, aam::OpenCVRealType::type, meanData);
    cv::Mat targetEigValues(2, 1, aam::OpenCVRealType::type, eigValuesData);

    try
    {
        aam::RealMatrix means, eigVectors, eigValues;
        
        aam::CommonFunctions::PCA(m, means, eigVectors, eigValues);

        if (means.rows != 6 || means.cols != 1)
        {
            std::cout << "%TEST_FAILED% time=0 testname=testPCA (pcaTest) message=Invalid means matrix size" << std::endl;
        }
        else if (eigVectors.rows != 6 || eigVectors.cols != 2)
        {
            std::cout << "%TEST_FAILED% time=0 testname=testPCA (pcaTest) message=Invalid eigen vectors matrix size" << std::endl;
        }
        else if (eigValues.rows != 2 || eigValues.cols != 1)
        {
            std::cout << "%TEST_FAILED% time=0 testname=testPCA (pcaTest) message=Invalid eigen values matrix size" << std::endl;
        }
        else if (cv::countNonZero(cv::abs(means - targetMeans) > 1e-6))
        {
            std::cout << "%TEST_FAILED% time=0 testname=testPCA (pcaTest) message=Invalid means matrix data" << std::endl;
        }
        else if (cv::countNonZero(cv::abs(eigValues - targetEigValues) > 1e-6))
        {
            std::cout << "%TEST_FAILED% time=0 testname=testPCA (pcaTest) message=Invalid eigen values matrix data" << std::endl;
        }
    }
    catch (std::exception& e)
    {
        std::cout << "%TEST_FAILED% time=0 testname=testPCA (pcaTest) message=Exception occured: " <<
                e.what() << std::endl;
    }
}

void testAppPCA()
{
    std::cout << "pcaTest testAppPCA" << std::endl;

    aam::RealType srcData[] =
    {
        1, 2,
        3, 4,
        5, 6,
        7, 8,
        9, 10,
        11, 12
    };

    aam::RealType meanData[] =
    {
        1.5,
        3.5,
        5.5,
        7.5,
        9.5,
        11.5
    };

    aam::RealType eigValuesData[] =
    {
        3,
        0
    };

    cv::Mat m(6, 2, aam::OpenCVRealType::type, srcData);
    cv::Mat targetMeans(6, 1, aam::OpenCVRealType::type, meanData);
    cv::Mat targetEigValues(2, 1, aam::OpenCVRealType::type, eigValuesData);

    try
    {
        aam::RealMatrix means, eigVectors, eigValues;

        aam::CommonFunctions::appPCA(m, means, eigVectors, eigValues);

        if (means.rows != 6 || means.cols != 1)
        {
            std::cout << "%TEST_FAILED% time=0 testname=testAppPCA (pcaTest) message=Invalid means matrix size" << std::endl;
        }
        else if (eigVectors.rows != 6 || eigVectors.cols != 2)
        {
            std::cout << "%TEST_FAILED% time=0 testname=testAppPCA (pcaTest) message=Invalid eigen vectors matrix size" << std::endl;
        }
        else if (eigValues.rows != 2 || eigValues.cols != 1)
        {
            std::cout << "%TEST_FAILED% time=0 testname=testAppPCA (pcaTest) message=Invalid eigen values matrix size" << std::endl;
        }
        else if (cv::countNonZero(cv::abs(means - targetMeans) > 1e-6))
        {
            std::cout << "%TEST_FAILED% time=0 testname=testAppPCA (pcaTest) message=Invalid means matrix data" << std::endl;
        }
        else if (cv::countNonZero(cv::abs(eigValues - targetEigValues) > 1e-6))
        {
            std::cout << "%TEST_FAILED% time=0 testname=testAppPCA (pcaTest) message=Invalid eigen values matrix data" << std::endl;
        }
        std::cout << means + eigVectors.col(1) * eigValues(1) << std::endl;

        std::cout << eigVectors << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << "%TEST_FAILED% time=0 testname=testAppPCA (pcaTest) message=Exception occured: " <<
                e.what() << std::endl;
    }
}

int main(int argc, char** argv)
{
    std::cout << "%SUITE_STARTING% pcaTest" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% testPCA (pcaTest)" << std::endl;
    testPCA();
    std::cout << "%TEST_FINISHED% time=0 testPCA (pcaTest)" << std::endl;

    std::cout << "%TEST_STARTED% testAppPCA (pcaTest)" << std::endl;
    testAppPCA();
    std::cout << "%TEST_FINISHED% time=0 testAppPCA (pcaTest)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}
