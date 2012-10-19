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
 * File:   gsorthTest.cpp
 * Author: Иван Губочкин
 *
 * Created on 26.09.2012, 23:36:50
 */

#include <stdlib.h>
#include <iostream>
#include <exception>
#include <iterator>

#include "aam/CommonFunctions.h"

/*
 * Simple C++ Test Suite
 */

bool loadVector(const std::string& fileName, int rows,
        int columns, aam::RealMatrix& target)
{
    cv::Mat1d result(rows, columns);

    FILE *in = fopen(fileName.c_str(), "rb");
    if (in == NULL)
    {
        return false;
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (fread(result.ptr(i, j), sizeof(double), 1, in) != 1)
            {
                fclose(in);
                return false;
            }
        }
    }

    target = result;

    fclose(in);
    return true;
}

void testGSOrth()
{
    std::cout << "gsorthTest testGSOrth" << std::endl;

    aam::RealType srcData[4 * 4] =
    {
        0.63787,   0.11209,   0.13878,   0.45578,
        0.94683,   0.12062,   0.33320,   0.89226,
        0.76691,   0.17863,   0.18085,   0.46860,
        0.74186,   0.76346,   0.73360,   0.25635
    };

    aam::RealMatrix x(4, 4, srcData);
    try
    {
        aam::RealMatrix y;
        aam::CommonFunctions::orthonormGS(x, y);

        if (y.rows != x.rows)
        {
            std::cout << "%TEST_FAILED% time=0 testname=testGSOrth (gsorthTest) message=Invalid result size" << std::endl;
            return;
        }

        for (int i = 0; i < y.cols; i++)
        {
            aam::RealMatrix r = y.col(i).t() * y.col(i);
            if (cv::countNonZero(cv::abs(r - 1) > 1e-12))
            {
                std::cout << "%TEST_FAILED% time=0 testname=testGSOrth (gsorthTest) message=Vectors aren't normalized" << std::endl;
                return;
            }

            for (int j = i + 1; j < y.cols; j++)
            {
                aam::RealMatrix r = y.col(i).t() * y.col(j);
                if (cv::countNonZero(cv::abs(r) > 1e-12))
                {
                    std::cout << "%TEST_FAILED% time=0 testname=testGSOrth (gsorthTest) message=Vectors aren't orthogonalized" << std::endl;
                    return;
                }
            }
        }
    }
    catch (std::exception& e)
    {
        std::cout << "%TEST_FAILED% time=0 testname=testGSOrth (gsorthTest) message=Exception occured: " <<
                e.what() << std::endl;
    }
}

void testGSOrth2()
{
    std::cout << "gsorthTest testGSOrth2" << std::endl;

    aam::RealMatrix srcData, targetData;

    if (!loadVector("data/s_star_pc.dat", 116, 20, srcData))
    {
        std::cout << "%TEST_FAILED% time=0 testname=testGSOrth2 (gsorthTest) message=Can't load source data" << std::endl;
        return;
    }

    if (!loadVector("data/s_star_pc_norm.dat", 116, 20, targetData))
    {
        std::cout << "%TEST_FAILED% time=0 testname=testGSOrth2 (gsorthTest) message=Can't load target data" << std::endl;
        return;
    }

    try
    {
        aam::RealMatrix y;
        aam::CommonFunctions::orthonormGS(srcData, y);

        if (y.rows != targetData.rows || y.cols != targetData.cols)
        {
            std::cout << "%TEST_FAILED% time=0 testname=testGSOrth2 (gsorthTest) message=Invalid result size" << std::endl;
        }
        else if (cv::countNonZero(cv::abs(y - targetData) > 1e-10))
        {
            std::cout << "%TEST_FAILED% time=0 testname=testGSOrth2 (gsorthTest) message=Invalid normalized matrix data" << std::endl;
        }
    }
    catch (std::exception& e)
    {
        std::cout << "%TEST_FAILED% time=0 testname=testGSOrth2 (gsorthTest) message=Exception occured: " <<
                e.what() << std::endl;
    }
}

void testGSOrth3()
{
    std::cout << "gsorthTest testGSOrth3" << std::endl;

    aam::RealMatrix srcData, targetData;

    if (!loadVector("data/s_star_pc.dat", 116, 20, srcData))
    {
        std::cout << "%TEST_FAILED% time=0 testname=testGSOrth3 (gsorthTest) message=Can't load source data" << std::endl;
        return;
    }

    if (!loadVector("data/s_star_pc_norm.dat", 116, 20, targetData))
    {
        std::cout << "%TEST_FAILED% time=0 testname=testGSOrth3 (gsorthTest) message=Can't load target data" << std::endl;
        return;
    }

    for (int i = 0; i < 58; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            std::swap(srcData(i, j), srcData(i + 58, j));
        }

        srcData(i, 0) -= 1;
        srcData(i + 1, 0) -= 1;
        srcData(i, 1) -= 1;
        srcData(i + 58, 1) += 1;
    }

    try
    {
        aam::RealMatrix y;
        aam::CommonFunctions::orthonormGS(srcData, y);

        if (y.rows != targetData.rows || y.cols != targetData.cols)
        {
            std::cout << "%TEST_FAILED% time=0 testname=testGSOrth3 (gsorthTest) message=Invalid result size" << std::endl;
        }

        std::cout << y.colRange(0, 4) << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << "%TEST_FAILED% time=0 testname=testGSOrth3 (gsorthTest) message=Exception occured: " <<
                e.what() << std::endl;
    }
}

int main(int argc, char** argv)
{
    std::cout << "%SUITE_STARTING% gsorthTest" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% testGSOrth (gsorthTest)" << std::endl;
    testGSOrth();
    std::cout << "%TEST_FINISHED% time=0 testGSOrth (gsorthTest)" << std::endl;

    std::cout << "%TEST_STARTED% testGSOrth2 (gsorthTest)" << std::endl;
    testGSOrth2();
    std::cout << "%TEST_FINISHED% time=0 testGSOrth2 (gsorthTest)" << std::endl;

    std::cout << "%TEST_STARTED% testGSOrth3 (gsorthTest)" << std::endl;
    testGSOrth3();
    std::cout << "%TEST_FINISHED% time=0 testGSOrth3 (gsorthTest)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}
