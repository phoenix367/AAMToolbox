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
 * File:   grad2DTest.cpp
 * Author: Иван Губочкин
 *
 * Created on 23.09.2012, 1:21:52
 */

#include <stdlib.h>
#include <iostream>
#include <opencv/highgui.h>

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

void testGradient()
{
    std::cout << "grad2DTest testGradient" << std::endl;

    try
    {
        cv::Mat1b maskImage = cv::imread("data/object_pixels.bmp",
                cv::IMREAD_GRAYSCALE);
        if (maskImage.empty())
        {
            std::cout << "%TEST_FAILED% time=0 testname=testGradient (grad2DTest) message=Can't load mask image" << std::endl;
            return;
        }

        aam::RealMatrix warpedImage = cv::imread("data/warped_image.bmp",
                cv::IMREAD_GRAYSCALE);
        if (warpedImage.empty())
        {
            std::cout << "%TEST_FAILED% time=0 testname=testGradient (grad2DTest) message=Can't load warped image" << std::endl;
            return;
        }

        aam::RealMatrix targetDi, targetDj;

        if (!loadVector("data/di_grad.raw", 255, 255, targetDi))
        {
            std::cout << "%TEST_FAILED% time=0 testname=testGradient (grad2DTest) message=Can't load target di gradient" << std::endl;
            return;
        }

        if (!loadVector("data/dj_grad.raw", 255, 255, targetDj))
        {
            std::cout << "%TEST_FAILED% time=0 testname=testGradient (grad2DTest) message=Can't load target dj gradient" << std::endl;
            return;
        }

        warpedImage /= 255.0;

        aam::RealMatrix di, dj;
        aam::CommonFunctions::gradient2D(warpedImage, maskImage,
                di, dj);

        if (di.size != targetDi.size)
        {
            std::cout << "%TEST_FAILED% time=0 testname=testGradient (grad2DTest) message=Invalid di gradient size" << std::endl;
        }
        else if (cv::countNonZero(cv::abs(di - targetDi) > 1e-8))
        {
            std::cout << "%TEST_FAILED% time=0 testname=testGradient (grad2DTest) message=Invalid di gradient data" << std::endl;
        }
        else if (dj.size != targetDj.size)
        {
            std::cout << "%TEST_FAILED% time=0 testname=testGradient (grad2DTest) message=Invalid dj gradient size" << std::endl;
        }
        else if (cv::countNonZero(cv::abs(dj - targetDj) > 1e-8))
        {
            std::cout << "%TEST_FAILED% time=0 testname=testGradient (grad2DTest) message=Invalid dj gradient data" << std::endl;
        }
    }
    catch (std::exception& e)
    {
        std::cout << "%TEST_FAILED% time=0 testname=testGradient (grad2DTest) message=Exception occured: " <<
                e.what() << std::endl;
    }
}

void testGradientColor()
{
    std::cout << "grad2DTest testGradientColor" << std::endl;

    try
    {
        cv::Mat1b maskImage = cv::imread("data/object_pixels.bmp",
                cv::IMREAD_GRAYSCALE);
        if (maskImage.empty())
        {
            std::cout << "%TEST_FAILED% time=0 testname=testGradientColor (grad2DTest) message=Can't load mask image" << std::endl;
            return;
        }

        aam::ColorMatrix warpedImage = cv::imread("data/warped_image_color.bmp");
        if (warpedImage.empty())
        {
            std::cout << "%TEST_FAILED% time=0 testname=testGradientColor (grad2DTest) message=Can't load warped image" << std::endl;
            return;
        }

        aam::RealMatrix targetDi, targetDj;

        if (!loadVector("data/di_grad.raw", 255, 255, targetDi))
        {
            std::cout << "%TEST_FAILED% time=0 testname=testGradientColor (grad2DTest) message=Can't load target di gradient" << std::endl;
            return;
        }

        if (!loadVector("data/dj_grad.raw", 255, 255, targetDj))
        {
            std::cout << "%TEST_FAILED% time=0 testname=testGradientColor (grad2DTest) message=Can't load target dj gradient" << std::endl;
            return;
        }

        warpedImage /= 255.0;

        aam::ColorMatrix di, dj;
        aam::CommonFunctions::gradient2D(warpedImage, maskImage,
                di, dj);

        cv::imshow("test", dj * 10);
        cv::waitKey(0);
        return;
        if (di.size != targetDi.size)
        {
            std::cout << "%TEST_FAILED% time=0 testname=testGradientColor (grad2DTest) message=Invalid di gradient size" << std::endl;
        }
        else if (cv::countNonZero(cv::abs(di - targetDi) > 1e-8))
        {
            std::cout << "%TEST_FAILED% time=0 testname=testGradientColor (grad2DTest) message=Invalid di gradient data" << std::endl;
        }
        else if (dj.size != targetDj.size)
        {
            std::cout << "%TEST_FAILED% time=0 testname=testGradientColor (grad2DTest) message=Invalid dj gradient size" << std::endl;
        }
        else if (cv::countNonZero(cv::abs(dj - targetDj) > 1e-8))
        {
            std::cout << "%TEST_FAILED% time=0 testname=testGradientColor (grad2DTest) message=Invalid dj gradient data" << std::endl;
        }
    }
    catch (std::exception& e)
    {
        std::cout << "%TEST_FAILED% time=0 testname=testGradientColor (grad2DTest) message=Exception occured: " <<
                e.what() << std::endl;
    }
}

int main(int argc, char** argv)
{
    std::cout << "%SUITE_STARTING% grad2DTest" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% testGradient (grad2DTest)" << std::endl;
    testGradient();
    std::cout << "%TEST_FINISHED% time=0 testGradient (grad2DTest)" << std::endl;

    std::cout << "%TEST_STARTED% testGradientColor (grad2DTest)" << std::endl;
    testGradientColor();
    std::cout << "%TEST_FINISHED% time=0 testGradientColor (grad2DTest)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}
