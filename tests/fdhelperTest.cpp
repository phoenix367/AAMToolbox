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
 * File:   fdhelperTest.cpp
 * Author: Иван Губочкин
 *
 * Created on 15.10.2012, 17:47:12
 */

#include <stdlib.h>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <limits>
#include <iterator>

#include "aam/FDHelper.h"
#include "aam/vector_op.h"

#define TOTAL_POINTS_NUMBER             (58)

aam::RealType alignedVerticesData[2 * TOTAL_POINTS_NUMBER] =
{
    21.076154931359774,
    38.213049950695279,
    60.286576082441805,
    84.318089492531342,
    105.3352479972213,
    122.26978027901133,
    131.06286749588909,
    123.7040051778248,
    106.31713265916839,
    83.922206885437859,
    58.524829896751612,
    39.275199623302996,
    20.061280421185952,
    -42.219516036479867,
    -50.122887292515031,
    -50.015754078520374,
    -46.787132745131451,
    -40.66319341078151,
    -40.82984507699544,
    -39.952032806596684,
    -40.082973401479059,
    -42.760964152004455,
    -50.973831359579769,
    -52.113524819743283,
    -48.209453953501118,
    -41.255317110527812,
    -41.112472825201579,
    -42.002188786044201,
    -41.859344500717967,
    -56.719913422172759,
    -67.970942916035369,
    -73.348010574868951,
    -65.504157771053016,
    -46.444986544706055,
    -55.44927936712687,
    -67.43527684606201,
    -73.118779633989405,
    -66.851996014313229,
    -47.590462050420797,
    33.785216704923585,
    39.337778897968604,
    42.280711660705052,
    40.179880097035799,
    34.648064462432153,
    61.268460744388896,
    64.449467316002398,
    62.598613251654051,
    -42.383106880247475,
    -13.08165902531905,
    -4.856888127299853,
    10.333923304136489,
    17.216638004446668,
    21.073094108913434,
    17.892087537299933,
    11.672918679399164,
    -5.4163615781609291,
    -13.379251286415359,
    -40.5917712681184,
    -84.967990142070533,
    -83.756874539243896,
    -73.407464696667759,
    -57.990483146798226,
    -43.617965533541373,
    -25.258051220935389,
    -0.94084924019338712,
    24.194646558728106,
    44.167341126805383,
    61.054258646819981,
    75.887959364940741,
    82.723059303475509,
    86.531900646166861,
    63.60130880246296,
    49.383539164976213,
    40.304763377445951,
    23.191675738998168,
    17.210580689974446,
    31.333120803910386,
    42.441306012446759,
    53.537587530539284,
    -61.507853873285924,
    -49.498049013463095,
    -38.41367118581443,
    -27.269774905946473,
    -18.107673285309264,
    -30.212707668682942,
    -40.312140011938162,
    -52.417174395311825,
    9.9588515859048279,
    22.941698239677262,
    51.127260015329874,
    70.388793979222328,
    79.693739885185778,
    -12.221807759836361,
    -22.452180697973972,
    -53.794941664352393,
    -71.881071096749778,
    -79.72492390056567,
    -50.515644746741749,
    -8.0766022622708125,
    -0.97962113397128248,
    6.0578415421089806,
    47.357190566416399,
    14.377841963678998,
    1.2997657863557535,
    -12.846581708467891,
    -8.0320483229417352,
    -11.721852761194564,
    -24.74041048629854,
    -29.605619456046444,
    -14.391000643722402,
    0.78790709727008901,
    13.865983274593331,
    27.91710124586616,
    22.670974181914968,
    13.496968870833905,
    11.158063498287605
};

/*
 * Simple C++ Test Suite
 */

void testMatch()
{
    std::cout << "fdhelperTest testMatch" << std::endl;

    std::vector<cv::Point2f> objectVertices(TOTAL_POINTS_NUMBER);

    for (int i = 0; i < TOTAL_POINTS_NUMBER; i++)
    {
        objectVertices[i].y = alignedVerticesData[i];
        objectVertices[i].x = alignedVerticesData[
                TOTAL_POINTS_NUMBER + i];
    }

    try
    {
        aam::FDHelper helper;

        std::vector<cv::Rect> faces;
        cv::Mat im = cv::imread("data/IMM/02-1m.jpg",
                cv::IMREAD_GRAYSCALE);
        cv::CascadeClassifier cascadeFace(
            "data/haarcascade_frontalface_alt.xml");

        if (cascadeFace.empty())
        {
            std::cout << "%TEST_FAILED% time=0 testname=testMatch (fdhelperTest) message=Can't load haar cascade" << std::endl;
            return;
        }

        cascadeFace.detectMultiScale(im, faces,
            1.1, 2, 0
            |CV_HAAR_FIND_BIGGEST_OBJECT
            //|CV_HAAR_DO_ROUGH_SEARCH
            |CV_HAAR_SCALE_IMAGE
            ,
            cv::Size(30, 30) );

        if (faces.empty())
        {
            std::cout << "%TEST_FAILED% time=0 testname=testMatch (fdhelperTest) message=No faces on test picture" << std::endl;
            return;
        }

        cv::Rect faceRect = faces[0];
        faceRect.x -= 20;
        faceRect.y -= 20;
        faceRect.width += 40;
        faceRect.height += 40;

        cv::Mat1b sceneMask = cv::Mat1b::zeros(im.rows, im.cols);
        sceneMask(cv::Range(faceRect.y,
                faceRect.y + faceRect.height),
                cv::Range(faceRect.x, faceRect.x + faceRect.width)) = 1;
        cv::Mat faceRegion = im(cv::Range(faceRect.y,
                faceRect.y + faceRect.height),
                cv::Range(faceRect.x, faceRect.x + faceRect.width));
        cv::Mat wImage = cv::imread("data/warped_image.bmp",
                cv::IMREAD_GRAYSCALE);
        cv::Mat mask = cv::imread("data/object_pixels.bmp",
                cv::IMREAD_GRAYSCALE);
        int64 start = cv::getTickCount();
        helper.detectKeyPoints(wImage, mask);
        std::cout << "Detection time: " << (cv::getTickCount() - start) /
                cv::getTickFrequency() << std::endl;

        helper.matchImages(im, sceneMask);

        cv::Mat kpImage;
        std::vector<cv::KeyPoint> kpObject = helper.getKeyPoints();
        std::vector<cv::KeyPoint> kpScene = helper.getSampleKeyPoints();
        std::vector<cv::DMatch> matches = helper.getMatches();

        double max_dist = 0; 
        double min_dist = std::numeric_limits<double>::infinity();

        //-- Quick calculation of max and min distances between keypoints
        for( int i = 0; i < matches.size(); i++ )
        {
            double dist = matches[i].distance;
            if ( dist < min_dist )
            {
                min_dist = dist;
            }

            if ( dist > max_dist )
            {
                max_dist = dist;
            }
        }

        std::cout << "-- Max dist : " << max_dist << std::endl;
        std::cout << "-- Min dist : " << min_dist << std::endl;
        
        //-- Draw only "good" matches (i.e. whose distance is less than 3*min_dist )
        std::vector< cv::DMatch > good_matches;

        for( int i = 0; i < matches.size(); i++ )
        {
            if ( matches[i].distance < 3 * min_dist )
            {
                good_matches.push_back( matches[i]);
            }
        }
        
        //-- Localize the object
        std::vector<cv::Point2f> obj;
        std::vector<cv::Point2f> scene;

        for( int i = 0; i < good_matches.size(); i++ )
        {
            //-- Get the keypoints from the good matches
            obj.push_back( kpObject[ good_matches[i].queryIdx ].pt );
            scene.push_back( kpScene[ good_matches[i].trainIdx ].pt );
        }

        std::vector<cv::Point2f> basePoints(objectVertices);

        // Normalize contour points to range 0..1
        aam::Point2D minPoint = aam::minCoords(basePoints);
        aam::Point2D maxPoint = aam::maxCoords(basePoints);

        for (int i = 0; i < basePoints.size(); i++)
        {
            basePoints[i].x = (basePoints[i].x - minPoint.x)
                    / (maxPoint.x - minPoint.x) * mask.cols;
            basePoints[i].y = (basePoints[i].y - minPoint.y)
                    / (maxPoint.y - minPoint.y) * mask.rows;
        }

        cv::Mat H = cv::findHomography( obj, scene, CV_RANSAC );
        //-- Get the corners from the image_1 ( the object to be "detected" )
//        std::vector<cv::Point2f> obj_corners(basePoints.begin(),
//                basePoints.begin() + 10);
//        obj_corners[0] = cvPoint(0,0); obj_corners[1] = cvPoint( mask.cols, 0 );
//        obj_corners[2] = cvPoint( mask.cols, mask.rows );
//        obj_corners[3] = cvPoint( 0, mask.rows );
//        obj_corners[4] = cvPoint( 0 + 100, mask.rows - 100 );
        std::vector<cv::Point2f> scene_corners(4);

        cv::perspectiveTransform( basePoints, scene_corners, H);

        for (int i = 0; i < scene_corners.size(); i++)
        {
            cv::circle(im, scene_corners[i], 3, CV_RGB(255, 0, 0));
        }

        cv::drawMatches(wImage, kpObject, im, kpScene, matches,
                kpImage, CV_RGB(255, 255, 0));

        std::cout << basePoints << std::endl;
        
        cv::imshow("test", kpImage);
        cv::waitKey(0);
    }
    catch (std::exception& e)
    {
        std::cout << "%TEST_FAILED% time=0 testname=testMatch (fdhelperTest) message=Exception occured: " <<
                e.what() << std::endl;
    }
}

void test2()
{
    std::cout << "fdhelperTest test 2" << std::endl;
    std::cout << "%TEST_FAILED% time=0 testname=test2 (fdhelperTest) message=error message sample" << std::endl;
}

int main(int argc, char** argv)
{
    std::cout << "%SUITE_STARTING% fdhelperTest" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% testMatch (fdhelperTest)" << std::endl;
    testMatch();
    std::cout << "%TEST_FINISHED% time=0 testMatch (fdhelperTest)" << std::endl;

    std::cout << "%TEST_STARTED% test2 (fdhelperTest)\n" << std::endl;
    test2();
    std::cout << "%TEST_FINISHED% time=0 test2 (fdhelperTest)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}
