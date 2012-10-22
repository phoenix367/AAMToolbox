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
 * File:   aplymodelicTest.cpp
 * Author: Иван Губочкин
 *
 * Created on 30.09.2012, 0:26:59
 */

#include <stdlib.h>
#include <iostream>

#include "aam/vector_op.h"
#include <exception>

#include "aam/AAMEstimator.h"
#include <opencv2/highgui/highgui.hpp>

#include "aam/AAMFunctions2D.h"
#include "aam/CommonFunctions.h"
#include "aam/TrainModelLoader.h"

/*
 * Simple C++ Test Suite
 */

#define POINTS_COUNT            58
#define TRIANGLES_COUNT         93

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

void testAplyModelGray()
{
    std::cout << "aplymodelicTest testAplyModelGray" << std::endl;

    try
    {
        aam::AAMEstimator estimator;
        estimator.load("data/aam_ic_test.xml");
        
        cv::CascadeClassifier cascadeFace(
            "data/haarcascade_frontalface_alt.xml");
        cv::CascadeClassifier cascadeEyes(
            "data/haarcascade_eye_tree_eyeglasses.xml");

        if (cascadeFace.empty())
        {
            std::cout << "%TEST_FAILED% time=0 testname=testAplyModelGray (aplymodelicTest) message=Can't load haar cascade" << std::endl;
            return;
        }

        if (cascadeEyes.empty())
        {
            std::cout << "%TEST_FAILED% time=0 testname=testAplyModelGray (aplymodelicTest) message=Can't load eye haar cascade" << std::endl;
            return;
        }

//        loader.load("data/cootes/107_0789.bmp.mat.dat",
//                "data/cootes/107_0789.bmp");
        cv::Mat im = cv::imread("data/cootes/107_0766.bmp");
        //cv::Mat im = cv::imread("data/muct/i005ra-fn.jpg");
        //cv::Mat im = cv::imread("data/IMM/01-1m.jpg");
//        cv::Mat im = cv::imread(
//                "/home/ivan/Документы/databases/CUAVE/cuavebmp/frames/s19f.bmp");

        std::vector<cv::Rect> faces;
        cv::cvtColor(im, im, CV_BGR2GRAY);
        cascadeFace.detectMultiScale(im, faces,
            1.1, 2, 0
            |CV_HAAR_FIND_BIGGEST_OBJECT
            //|CV_HAAR_DO_ROUGH_SEARCH
            |CV_HAAR_SCALE_IMAGE
            ,
            cv::Size(30, 30) );

        if (faces.empty())
        {
            std::cout << "%TEST_FAILED% time=0 testname=testAplyModelGray (aplymodelicTest) message=No faces on test picture" << std::endl;
            return;
        }

        cv::Rect r = faces[0];
        aam::Point2D startPoint(r.x + r.width * 0.5 + 20, r.y +
            r.height * 0.5 + 40);
        aam::Vertices2DList foundPoints;

        int64 start = cv::getTickCount();
        estimator.estimateAAM(im, startPoint, foundPoints,
                true);
        std::cout << "Working time: " << (cv::getTickCount() - start) /
                cv::getTickFrequency() << std::endl;

        for (int j = 0; j < foundPoints.size(); j++)
        {
            cv::circle(im, foundPoints[j], 3, CV_RGB(255, 255, 255));
        }
        cv::imshow("test", im);
        cv::waitKey(0);
    }
    catch (std::exception& e)
    {
        std::cout << "%TEST_FAILED% time=0 testname=testAplyModelGray (aplymodelicTest) message=Exception occured: " <<
                e.what() << std::endl;
    }
}

void testAplyModelColor()
{
    std::cout << "aplymodelicTest testAplyModelColor" << std::endl;

    try
    {
        aam::AAMEstimator estimator;
        estimator.load("data/aam_ic_c_test.xml");

        cv::CascadeClassifier cascadeFace(
            "data/haarcascade_frontalface_alt.xml");
        cv::CascadeClassifier cascadeEyes(
            "data/haarcascade_eye_tree_eyeglasses.xml");

        if (cascadeFace.empty())
        {
            std::cout << "%TEST_FAILED% time=0 testname=testAplyModelColor (aplymodelicTest) message=Can't load haar cascade" << std::endl;
            return;
        }

        if (cascadeEyes.empty())
        {
            std::cout << "%TEST_FAILED% time=0 testname=testAplyModelColor (aplymodelicTest) message=Can't load eye haar cascade" << std::endl;
            return;
        }

//        loader.load("data/cootes/107_0789.bmp.mat.dat",
//                "data/cootes/107_0789.bmp");
        cv::Mat im = cv::imread("data/cootes/107_0766.bmp");
        //cv::Mat im = cv::imread("data/muct/i005ra-fn.jpg");
        //cv::Mat im = cv::imread("data/IMM/01-1m.jpg");
//        cv::Mat im = cv::imread(
//                "/home/ivan/Документы/databases/CUAVE/cuavebmp/frames/s19f.bmp");

        std::vector<cv::Rect> faces;
        cv::Mat1b detectImage;
        cv::cvtColor(im, detectImage, CV_BGR2GRAY);
        cascadeFace.detectMultiScale(im, faces,
            1.1, 2, 0
            |CV_HAAR_FIND_BIGGEST_OBJECT
            //|CV_HAAR_DO_ROUGH_SEARCH
            |CV_HAAR_SCALE_IMAGE
            ,
            cv::Size(30, 30) );

        if (faces.empty())
        {
            std::cout << "%TEST_FAILED% time=0 testname=testAplyModelColor (aplymodelicTest) message=No faces on test picture" << std::endl;
            return;
        }

        cv::Rect faceRect = faces[0];
        cv::Mat eyeRegion = detectImage(cv::Range(faceRect.y,
                faceRect.y + faceRect.height),
                cv::Range(faceRect.x, faceRect.x + faceRect.width));
        std::vector<cv::Rect> eyes;

        cascadeEyes.detectMultiScale(eyeRegion, eyes,
            1.1, 2, 0
            //|CV_HAAR_FIND_BIGGEST_OBJECT
            //|CV_HAAR_DO_ROUGH_SEARCH
            |CV_HAAR_SCALE_IMAGE
            ,
            cv::Size(30, 30) );

        if (eyes.empty())
        {
            //std::cout << "%TEST_FAILED% time=0 testname=testAplyModelGray (aplymodelicTest) message=No eyes found on test picture" << std::endl;
            //return;
        }

        cv::Rect r = faceRect;
        aam::Point2D startPoint(r.x + r.width * 0.5 + 20, r.y +
            r.height * 0.5 + 40);
        aam::Vertices2DList foundPoints;

        int64 start = cv::getTickCount();
        estimator.estimateAAM(im, startPoint, foundPoints,
                true);
        std::cout << "Working time: " << (cv::getTickCount() - start) /
                cv::getTickFrequency() << std::endl;

        for (int j = 0; j < foundPoints.size(); j++)
        {
            cv::circle(im, foundPoints[j], 3, CV_RGB(255, 255, 255));
        }
        cv::imshow("test", im);
        cv::waitKey(0);
    }
    catch (std::exception& e)
    {
        std::cout << "%TEST_FAILED% time=0 testname=testAplyModelColor (aplymodelicTest) message=Exception occured: " <<
                e.what() << std::endl;
    }
}

int main(int argc, char** argv)
{
    std::cout << "%SUITE_STARTING% aplymodelicTest" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% testAplyModelGray (aplymodelicTest)" << std::endl;
    testAplyModelGray();
    std::cout << "%TEST_FINISHED% time=0 testAplyModelGray (aplymodelicTest)" << std::endl;

    std::cout << "%TEST_STARTED% testAplyModelColor (aplymodelicTest)" << std::endl;
    testAplyModelColor();
    std::cout << "%TEST_FINISHED% time=0 testAplyModelColor (aplymodelicTest)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}
