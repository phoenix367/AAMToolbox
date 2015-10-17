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
 * File:   aplymodelTest.cpp
 * Author: Иван Губочкин
 *
 * Created on 10.09.2012, 15:00:26
 */

#include <stdlib.h>
#include <iostream>
#include <exception>
#include <opencv2/highgui/highgui.hpp>
#include <boost/assign.hpp>
#include <iterator>

#include "aam/AAMFunctions2D.h"
#include "aam/AAMModel.h"
#include "aam/AAMEstimator.h"

/*
 * Simple C++ Test Suite
 */

void testAplyGray()
{
    std::cout << "aplymodelTest testAplyGray" << std::endl;

    try
    {
        aam::AAMEstimator estimator;
        estimator.load("data/aam_test.xml");

        cv::CascadeClassifier cascade("data/haarcascade_frontalface_alt.xml");

        if (cascade.empty())
        {
            std::cout << "%TEST_FAILED% time=0 testname=testAplyGray (aplymodelTest) message=Can't load haar cascade" << std::endl;
            return;
        }

        //model.load("data/aam_test.xml");

        //cv::Mat im = cv::imread("data/IMM/01-1m.jpg");
        cv::Mat im = cv::imread("data/cootes/107_0766.bmp");

        if (im.empty())
        {
            std::cout << "%TEST_FAILED% time=0 testname=testAplyGray (aplymodelTest) message=Can't read test image" << std::endl;
            return;
        }

        cv::Mat gray;
        cv::cvtColor(im, im, CV_BGR2GRAY);

        std::vector<cv::Rect> faces;
        cascade.detectMultiScale(im, faces,
            1.1, 2, 0
            |CV_HAAR_FIND_BIGGEST_OBJECT
            //|CV_HAAR_DO_ROUGH_SEARCH
            |CV_HAAR_SCALE_IMAGE
            ,
            cv::Size(30, 30) );

        if (faces.empty())
        {
            std::cout << "%TEST_FAILED% time=0 testname=testAplyGray (aplymodelTest) message=No faces on test picture" << std::endl;
            return;
        }

        cv::Rect faceRect = faces[0];
        
        aam::Point2D cp;
        cp.x = cvRound(
                (faceRect.x + faceRect.width * 0.5) + 10);
        cp.y = cvRound(
                (faceRect.y + faceRect.height * 0.5) + 30);

        aam::Vertices2DList pos;
        aam::TrainOptions options = estimator.getTrainOptions();
        options.setMaxIters(30);
        estimator.setTrainOptions(options);
        
        uint64 start = cv::getTickCount();
        estimator.estimateAAM(im, cp, pos, true);

        std::cout << "Working time " << (cv::getTickCount() -
                start) / cv::getTickFrequency() << std::endl;

        for (int i = 0; i < pos.size(); i++)
        {
            cv::circle(im, pos[i], 3, CV_RGB(255, 255, 255));
        }
        cv::imshow("result", im);
        cv::waitKey(0);
    }
    catch (std::exception& e)
    {
        std::cout << "%TEST_FAILED% time=0 testname=testAplyGray (aplymodelTest) message=Exception occured: " <<
                e.what() << std::endl;
    }
}

void testAplyColor()
{
    std::cout << "aplymodelTest testAplyColor" << std::endl;

    try
    {
        aam::AAMEstimator estimator;
        estimator.load("data/aam_c_test.xml");

        cv::CascadeClassifier cascade("data/haarcascade_frontalface_alt.xml");

        if (cascade.empty())
        {
            std::cout << "%TEST_FAILED% time=0 testname=testAplyColor (aplymodelTest) message=Can't load haar cascade" << std::endl;
            return;
        }

        //cv::Mat im = cv::imread("data/IMM/01-1m.jpg");
        cv::Mat im = cv::imread("data/cootes/107_0766.bmp");

        if (im.empty())
        {
            std::cout << "%TEST_FAILED% time=0 testname=testAplyColor (aplymodelTest) message=Can't read test image" << std::endl;
            return;
        }

        std::vector<cv::Rect> faces;
        cascade.detectMultiScale(im, faces,
            1.1, 2, 0
            |CV_HAAR_FIND_BIGGEST_OBJECT
            //|CV_HAAR_DO_ROUGH_SEARCH
            |CV_HAAR_SCALE_IMAGE
            ,
            cv::Size(30, 30) );

        if (faces.empty())
        {
            std::cout << "%TEST_FAILED% time=0 testname=testAplyColor (aplymodelTest) message=No faces on test picture" << std::endl;
            return;
        }

        cv::Rect faceRect = faces[0];

        aam::Point2D cp;
        cp.x = cvRound(
                (faceRect.x + faceRect.width * 0.5)  + 10);
        cp.y = cvRound(
                (faceRect.y + faceRect.height * 0.5)  + 30);

        aam::Vertices2DList pos;
        aam::TrainOptions options = estimator.getTrainOptions();
        options.setMaxIters(30);
        estimator.setTrainOptions(options);

        uint64 start = cv::getTickCount();
        estimator.estimateAAM(im, cp, pos, true);

        std::cout << "Working time " << (cv::getTickCount() -
                start) / cv::getTickFrequency() << std::endl;

        for (int i = 0; i < pos.size(); i++)
        {
            cv::circle(im, pos[i], 3, CV_RGB(255, 255, 255));
        }
        cv::imshow("result", im);
        cv::waitKey(0);
    }
    catch (std::exception& e)
    {
        std::cout << "%TEST_FAILED% time=0 testname=testAplyColor (aplymodelTest) message=Exception occured: " <<
                e.what() << std::endl;
    }
}

int main(int argc, char** argv)
{
    std::cout << "%SUITE_STARTING% aplymodelTest" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% testAplyGray (aplymodelTest)" << std::endl;
    testAplyGray();
    std::cout << "%TEST_FINISHED% time=0 testAplyGray (aplymodelTest)" << std::endl;

    std::cout << "%TEST_STARTED% testAplyColor (aplymodelTest)" << std::endl;
    testAplyColor();
    std::cout << "%TEST_FINISHED% time=0 testAplyColor (aplymodelTest)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}
