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
 * File:   mappearanceTest.cpp
 * Author: Иван Губочкин
 *
 * Created on 15.08.2012, 22:00:45
 */

#include <stdlib.h>
#include <iostream>
#include <opencv/highgui.h>
#include <boost/assign.hpp>
#include <exception>
#include <boost/math/special_functions/detail/round_fwd.hpp>

#include "aam/ShapeData.h"
#include "aam/AAMFunctions2D.h"
#include "aam/CommonFunctions.h"
#include "aam/TrainModelLoader.h"
#include "aam/vector_op.h"

/*
 * Simple C++ Test Suite
 */

#define TOTAL_POINTS_NUMBER             (58)

aam::RealType verticesAData[2 * TOTAL_POINTS_NUMBER] =
{
   307,   228,
   327,   232,
   350,   239,
   374,   255,
   392,   270,
   406,   294,
   410,   314,
   403,   343,
   388,   361,
   370,   372,
   349,   382,
   331,   388,
   312,   393,
   243,   374,
   236,   364,
   234,   354,
   235,   339,
   243,   334,
   245,   346,
   247,   355,
   247,   366,
   242,   251,
   234,   263,
   230,   275,
   235,   286,
   242,   297,
   245,   285,
   245,   274,
   244,   262,
   228,   325,
   215,   333,
   210,   366,
   219,   387,
   241,   391,
   226,   305,
   213,   292,
   208,   259,
   215,   240,
   236,   236,
   333,   277,
   329,   305,
   333,   313,
   328,   321,
   329,   348,
   347,   325,
   348,   314,
   347,   302,
   244,   303,
   268,   304,
   284,   290,
   299,   288,
   303,   299,
   303,   314,
   303,   328,
   295,   338,
   281,   333,
   269,   325,
   245,   324
};

aam::RealType verticesBData[2 * TOTAL_POINTS_NUMBER] =
{
   309,   227,
   326,   228,
   348,   238,
   372,   253,
   393,   267,
   410,   285,
   419,   309,
   412,   334,
   395,   354,
   373,   371,
   348,   386,
   329,   393,
   310,   397,
   248,   375,
   240,   361,
   240,   352,
   243,   335,
   249,   329,
   249,   343,
   250,   354,
   250,   365,
   246,   251,
   238,   263,
   237,   274,
   241,   285,
   248,   294,
   248,   282,
   247,   272,
   247,   260,
   233,   322,
   222,   335,
   217,   363,
   225,   382,
   244,   391,
   234,   300,
   222,   290,
   216,   259,
   222,   241,
   241,   233,
   322,   261,
   328,   303,
   331,   310,
   329,   317,
   324,   358,
   350,   325,
   353,   312,
   351,   298,
   247,   304,
   276,   300,
   284,   287,
   299,   282,
   306,   297,
   310,   312,
   307,   325,
   301,   339,
   284,   334,
   276,   325,
   249,   323
};

aam::RealType meansData[2 * TOTAL_POINTS_NUMBER] =
{
    20.615238440807154,
    39.106878734859009,
    61.583749482929086,
    85.574770322603598,
    105.07490062103157,
    120.59312673453496,
    127.09176403141657,
    120.11178378921014,
    104.11386881521842,
    84.101395497237192,
    61.093426836903994,
    42.600257185590948,
    23.615174324175292,
    -41.824778995164934,
    -49.31253399199926,
    -50.311928447941852,
    -48.30524158716274,
    -41.311673004418552,
    -40.320594733733117,
    -38.828070343681446,
    -38.826412843970061,
    -43.341744229649279,
    -51.335181853053612,
    -53.8224295634976,
    -49.325641600460969,
    -42.322398988894655,
    -40.831684487783782,
    -41.338112668517581,
    -41.837428410892315,
    -56.81175822205072,
    -68.81339345260777,
    -73.791087000139143,
    -65.289424284168518,
    -44.821952669132571,
    -57.302143782329644,
    -69.803096462698903,
    -75.312740787203126,
    -68.824534342978268,
    -48.829923096626104,
    40.125582317120873,
    41.110944924337161,
    44.610747632664854,
    41.123491469439635,
    39.075361387058337,
    61.105109247625869,
    63.112398835572762,
    61.6150317962746,
    -41.839868006263643,
    -15.330126504636613,
    -3.3598022741252986,
    11.639599795333767,
    17.133084626603775,
    19.142937512451176,
    17.642225079592571,
    10.640792356967047,
    -4.8573357048072925,
    -14.840944691255778,
    -40.329654765716597,
    -84.920361953984056,
    -82.440064730436347,
    -73.944868354411,
    -58.459891272344365,
    -43.964798276298481,
    -22.983941846273957,
    -0.97447482080254444,
    26.001753335563176,
    44.991367920408038,
    58.987442097742054,
    71.482664430096378,
    77.980836704493854,
    82.478830121866039,
    62.014931498590734,
    50.011463839751151,
    40.52535114450319,
    24.536063281585928,
    19.030186001880324,
    32.020804642581375,
    42.016078622722389,
    53.009541604470456,
    -61.416592751095322,
    -49.422518589398251,
    -37.922327770769968,
    -26.932490714261981,
    -16.943878834541643,
    -28.945817136120052,
    -39.440254469406398,
    -51.430099978695623,
    11.038718511442113,
    21.551159035916079,
    52.022810566409674,
    72.002305822400373,
    78.49748700030068,
    -9.9442734178862651,
    -21.426021977059435,
    -53.404733700140142,
    -71.895471610877792,
    -77.909596522491384,
    -43.519214308290508,
    -8.4799517947535143,
    -0.99007939803601952,
    6.5126391999303745,
    40.505782318408578,
    12.520736839866208,
    0.52907187940278422,
    -12.470314991931261,
    -8.9487707343175895,
    -10.448109614019334,
    -23.963282646779632,
    -27.470048819111891,
    -14.460978356722322,
    0.54159759260098095,
    14.022762037606315,
    26.031362439605402,
    21.027825807784275,
    12.543980084759273,
    11.037675008569371
};

aam::RealType basePointsData[2 * TOTAL_POINTS_NUMBER] =
{
    120.381247175054,                         0,
    143.586642919077,           3.7634321108053,
    171.79315529451,          16.6534577599896,
    201.899793972034,          40.1492950461264,
    226.370756711916,          62.1431504246363,
    245.844776997987,          93.9780563590183,
               254,          127.373705138116,
    245.240733583923,          168.305575039926,
    225.164745615991,          197.119107797988,
    200.050837072688,          218.355786404131,
    171.17784313927,          237.315175831649,
    147.970528185273,          247.175054706985,
    124.145905056845,                       254,
    42.0244712576932,           222.94949022241,
    32.6279918122369,          204.736255453846,
    31.3738389363565,          190.342681657497,
    33.8920559251268,          166.081637940268,
    42.6683745234153,          157.727399119262,
    43.9120913121285,          177.438468771515,
    45.7850792449457,          192.604608819584,
    45.7871592625178,          209.285332081968,
    40.1208121968224,          35.6629999434447,
    30.0897451602259,          53.8619816666699,
    26.9684662192314,           71.311578834427,
    32.6115429068518,           87.986800367684,
    41.4000015675516,          103.142831803603,
    43.2707182476051,          84.9319175763725,
    42.6351950510158,          69.0083814493467,
    42.0085973442265,          50.8158159919247,
    23.2171194794298,           145.60169697339,
    8.15611403741522,          161.552549902277,
    1.90954278542666,          207.788134392066,
    12.5783879862371,          238.103643876259,
    38.2632797077818,          247.958984267861,
    22.6017283722878,          113.763550779504,
    6.91412308079881,          96.3419366255442,
                 0,          47.8196428382356,
    8.14213319169915,          19.7630711721115,
    33.2336263930217,          10.6376524134732,
    144.865027064363,          62.8192488362866,
    146.101571193938,          115.985411516485,
    150.493518343097,            127.3500278278,
    146.117316013742,          138.734136079768,
    143.547091396503,          190.312989269103,
    171.192503545796,          147.850409471651,
    173.711476904592,           129.65508330438,
    171.832411869342,          109.930709343108,
    42.0055358648149,           115.27405795992,
    75.2729492924326,          112.999064450562,
    90.2946621603083,          92.4920721063838,
    109.117603522492,           87.171146737946,
    116.011447848699,          106.910213913072,
    118.533637922792,          129.674088958547,
    116.650374710406,          150.129479014908,
    107.86418730247,          168.350501854288,
    88.4153883183843,          160.758480120356,
    75.8868298022072,          147.885677169957,
    43.9007217621975,           145.60011363403
};

void testMakeAppearance()
{
    std::cout << "mappearanceTest testMakeAppearance" << std::endl;

    aam::Vertices2DList verticesA(TOTAL_POINTS_NUMBER),
            verticesB(TOTAL_POINTS_NUMBER);
    aam::Vertices2DList meansVertices(TOTAL_POINTS_NUMBER);
    aam::Vertices2DList basePoints(TOTAL_POINTS_NUMBER);

    for (int i = 0; i < TOTAL_POINTS_NUMBER; i++)
    {
        verticesA[i].y = verticesAData[i * 2];
        verticesA[i].x = verticesAData[i * 2 + 1];
        verticesB[i].y = verticesBData[i * 2];
        verticesB[i].x = verticesBData[i * 2 + 1];
        meansVertices[i].y = meansData[i];
        meansVertices[i].x = meansData[i + TOTAL_POINTS_NUMBER];
        basePoints[i].y = basePointsData[2 * i];
        basePoints[i].x = basePointsData[2 * i + 1];
    }

    aam::ShapeData shapeData;
    shapeData.xMean = meansVertices;
    shapeData.lines = boost::assign::list_of<int>
        (0) (38) (37) (36) (31) (32) (33) (12) (11) (10) (9)
        (8) (7) (6) (5) (4) (3) (2) (1);
    shapeData.textureSize = cv::Size(255, 255);

    try
    {
        cv::Mat im = cv::imread("data/IMM/01-1m.jpg");
        std::vector<aam::TrainModelInfo> trainData(2);
        trainData[0].setVertices(verticesA);
        trainData[0].setImage(im, true);

        im = cv::imread("data/IMM/01-2m.jpg");
        trainData[1].setVertices(verticesB);
        trainData[1].setImage(im, true);

        aam::CommonFunctions::delaunay(verticesA, shapeData.triangles);

        aam::AppearanceData appearanceData;

        aam::AAMFunctions2D::makeAppearanceModel(
                trainData, shapeData,
                aam::AAMFunctions2D::DEFAULT_PCA_CUT_THRESOLD,
                appearanceData);

        cv::Mat objectPixels = cv::imread("data/object_pixels_synth.bmp",
                cv::IMREAD_GRAYSCALE);

        for (int i = 0; i < std::min(3, appearanceData.eigenVectors.cols);
                i++)
        {
            aam::RealMatrix eigv =
                    appearanceData.eigenVectors.col(i);
            aam::RealType minElem = *std::min_element(eigv.begin(),
                    eigv.end());
            aam::RealType maxElem = *std::max_element(eigv.begin(),
                    eigv.end());

            aam::RealMatrix result;
            aam::AAMFunctions2D::vector2Appearance(
                    appearanceData.eigenVectors.col(0), objectPixels,
                    cv::Size(255, 255), result);

            std::ostringstream winName;

            winName << "eigen appearance " << i + 1;
            cv::imshow(winName.str(), (result - minElem) /
                (maxElem - minElem));
        }
        cv::waitKey(0);

        if (appearanceData.basePoints.size() != TOTAL_POINTS_NUMBER)
        {
            std::cout << "%TEST_FAILED% time=0 testname=testMakeAppearance (mappearanceTest) message=Invalid base points array size" << std::endl;
        }
        else if (cv::countNonZero(cv::abs(
                aam::pointVector2Mat(aam::operator -(appearanceData.basePoints,
                basePoints))) > 1e-6))
        {
            std::cout << "%TEST_FAILED% time=0 testname=testMakeAppearance (mappearanceTest) message=Invalid base points array data" << std::endl;
        }
    }
    catch (std::exception& e)
    {
        std::cout << "%TEST_FAILED% time=0 testname=testMakeAppearance (mappearanceTest) message=Exception occured: " <<
                e.what() << std::endl;
    }
}

void testMakeAppearanceColor()
{
    std::cout << "mappearanceTest testMakeAppearanceColor" << std::endl;

    aam::Vertices2DList verticesA(TOTAL_POINTS_NUMBER),
            verticesB(TOTAL_POINTS_NUMBER);
    aam::Vertices2DList meansVertices(TOTAL_POINTS_NUMBER);
    aam::Vertices2DList basePoints(TOTAL_POINTS_NUMBER);

    for (int i = 0; i < TOTAL_POINTS_NUMBER; i++)
    {
        verticesA[i].y = verticesAData[i * 2];
        verticesA[i].x = verticesAData[i * 2 + 1];
        verticesB[i].y = verticesBData[i * 2];
        verticesB[i].x = verticesBData[i * 2 + 1];
        meansVertices[i].y = meansData[i];
        meansVertices[i].x = meansData[i + TOTAL_POINTS_NUMBER];
        basePoints[i].y = basePointsData[2 * i];
        basePoints[i].x = basePointsData[2 * i + 1];
    }

    aam::ShapeData shapeData;
    shapeData.xMean = meansVertices;
    shapeData.lines = boost::assign::list_of<int>
        (0) (38) (37) (36) (31) (32) (33) (12) (11) (10) (9)
        (8) (7) (6) (5) (4) (3) (2) (1);
    shapeData.textureSize = cv::Size(255, 255);

    try
    {
        cv::Mat im = cv::imread("data/IMM/01-1m.jpg");
        std::vector<aam::TrainModelInfo> trainData(2);
        trainData[0].setVertices(verticesA);
        trainData[0].setImage(im, false);

        im = cv::imread("data/IMM/01-2m.jpg");
        trainData[1].setVertices(verticesB);
        trainData[1].setImage(im, false);

        aam::CommonFunctions::delaunay(verticesA, shapeData.triangles);

        aam::AppearanceData appearanceData;

        aam::AAMFunctions2D::makeAppearanceModel(
                trainData, shapeData,
                aam::AAMFunctions2D::DEFAULT_PCA_CUT_THRESOLD,
                appearanceData);

        cv::Mat objectPixels = cv::imread("data/object_pixels_synth.bmp",
                cv::IMREAD_GRAYSCALE);

        for (int i = 0; i < std::min(3, appearanceData.eigenVectors.cols);
                i++)
        {
            aam::RealMatrix eigv =
                    appearanceData.eigenVectors.col(i);
            aam::RealType minElemR = *std::min_element(eigv.begin(),
                    eigv.begin() + appearanceData.nPixels);
            aam::RealType maxElemR = *std::max_element(eigv.begin(),
                    eigv.begin() + appearanceData.nPixels);
            aam::RealType minElemG = *std::min_element(
                    eigv.begin() + appearanceData.nPixels,
                    eigv.begin() + 2 * appearanceData.nPixels);
            aam::RealType maxElemG = *std::max_element(
                    eigv.begin() + appearanceData.nPixels,
                    eigv.begin() + 2 * appearanceData.nPixels);
            aam::RealType minElemB = *std::min_element(
                    eigv.begin() + 2 * appearanceData.nPixels,
                    eigv.begin() + 3 * appearanceData.nPixels);
            aam::RealType maxElemB = *std::max_element(
                    eigv.begin() + 2 * appearanceData.nPixels,
                    eigv.begin() + 3 * appearanceData.nPixels);

            cv::Mat result;
            aam::AAMFunctions2D::vector2Appearance(
                    appearanceData.eigenVectors.col(i), objectPixels,
                    cv::Size(255, 255), result);

            std::vector<cv::Mat> channels;
            cv::split(result, channels);
            channels[0] = (channels[0] - minElemR) / (maxElemR - minElemR);
            channels[1] = (channels[1] - minElemG) / (maxElemG - minElemG);
            channels[2] = (channels[2] - minElemB) / (maxElemB - minElemB);

            std::ostringstream winName;

            cv::Mat img;
            cv::merge(channels, img);

            winName << "eigen appearance " << i + 1;

            cv::imshow(winName.str(), img);
        }
        cv::waitKey(0);

        if (appearanceData.basePoints.size() != TOTAL_POINTS_NUMBER)
        {
            std::cout << "%TEST_FAILED% time=0 testname=testMakeAppearanceColor (mappearanceTest) message=Invalid base points array size" << std::endl;
        }
        else if (cv::countNonZero(cv::abs(
                aam::pointVector2Mat(aam::operator -(appearanceData.basePoints,
                basePoints))) > 1e-6))
        {
            std::cout << "%TEST_FAILED% time=0 testname=testMakeAppearanceColor (mappearanceTest) message=Invalid base points array data" << std::endl;
        }
    }
    catch (std::exception& e)
    {
        std::cout << "%TEST_FAILED% time=0 testname=testMakeAppearance (mappearanceTest) message=Exception occured: " <<
                e.what() << std::endl;
    }
}

void testMakeAppearanceScale()
{
    std::cout << "mappearanceTest testMakeAppearanceScale" << std::endl;

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

        for (int i = 0; i < trainData.size(); i++)
        {
            cv::Mat srcImage, resizedImage;
            srcImage = trainData[i].getImage();
            cv::pyrDown(srcImage, resizedImage,
                    cv::Size(srcImage.cols / 2, srcImage.rows / 2));
            cv::pyrDown(resizedImage, resizedImage,
                    cv::Size(resizedImage.cols / 2, resizedImage.rows / 2));
            cv::pyrDown(resizedImage, resizedImage,
                    cv::Size(resizedImage.cols / 2, resizedImage.rows / 2));

            trainData[i].setImage(resizedImage, false);

            aam::Vertices2DList vertices = trainData[i].getVertices();

            for (int j = 0; j < vertices.size(); j++)
            {
                vertices[j].x = vertices[j].x / 8;
                vertices[j].y = vertices[j].y / 8;
            }
            
            trainData[i].setVertices(vertices);
        }
        
        aam::AAMFunctions2D::makeShapeModel(1,
                aam::AAMFunctions2D::DEFAULT_PCA_CUT_THRESOLD,
                trainData, shapeData);
        aam::AAMFunctions2D::makeAppearanceModel(trainData,
                shapeData,
                aam::AAMFunctions2D::DEFAULT_PCA_CUT_THRESOLD,
                appearanceData);

        for (int i = 0; i < std::min(3, appearanceData.eigenVectors.cols);
                i++)
        {
            aam::RealMatrix eigv =
                    appearanceData.eigenVectors.col(i);
            aam::RealType minElem = *std::min_element(eigv.begin(),
                    eigv.end());
            aam::RealType maxElem = *std::max_element(eigv.begin(),
                    eigv.end());

            aam::RealMatrix result;
            aam::AAMFunctions2D::vector2Appearance(
                    appearanceData.eigenVectors.col(0),
                    appearanceData.objectPixels,
                    cv::Size(appearanceData.objectPixels.cols,
                        appearanceData.objectPixels.rows), result);

            std::ostringstream winName;

            winName << "eigen appearance " << i + 1;
            cv::imshow(winName.str(), (result - minElem) /
                (maxElem - minElem));
        }
        
        cv::waitKey(0);
    }
    catch (std::exception& e)
    {
        std::cout << "%TEST_FAILED% time=0 testname=testMakeAppearanceScale (mappearanceTest) message=Exception occured: " <<
                e.what() << std::endl;
    }
}

void testMakeAppearanceScale2()
{
    std::cout << "mappearanceTest testMakeAppearanceScale2" << std::endl;

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

        for (int i = 0; i < trainData.size(); i++)
        {
            cv::Mat srcImage, resizedImage;
            srcImage = trainData[i].getImage();
            cv::pyrDown(srcImage, resizedImage,
                    cv::Size(srcImage.cols / 2, srcImage.rows / 2));

            trainData[i].setImage(resizedImage, false);

            aam::Vertices2DList vertices = trainData[i].getVertices();

            for (int j = 0; j < vertices.size(); j++)
            {
                vertices[j].x = vertices[j].x / 2;
                vertices[j].y = vertices[j].y / 2;
            }

            trainData[i].setVertices(vertices);
        }

        aam::AAMFunctions2D::makeShapeModel(1,
                aam::AAMFunctions2D::DEFAULT_PCA_CUT_THRESOLD,
                trainData, shapeData);
        aam::AAMFunctions2D::makeAppearanceModel(trainData,
                shapeData,
                aam::AAMFunctions2D::DEFAULT_PCA_CUT_THRESOLD,
                appearanceData);

        for (int i = 0; i < std::min(3, appearanceData.eigenVectors.cols);
                i++)
        {
            aam::RealMatrix eigv =
                    appearanceData.eigenVectors.col(i);
            aam::RealType minElem = *std::min_element(eigv.begin(),
                    eigv.end());
            aam::RealType maxElem = *std::max_element(eigv.begin(),
                    eigv.end());

            aam::RealMatrix result;
            aam::AAMFunctions2D::vector2Appearance(
                    appearanceData.eigenVectors.col(0),
                    appearanceData.objectPixels,
                    cv::Size(appearanceData.objectPixels.cols,
                        appearanceData.objectPixels.rows), result);

            std::ostringstream winName;

            winName << "eigen appearance " << i + 1;
            cv::imshow(winName.str(), (result - minElem) /
                (maxElem - minElem));
        }

        cv::waitKey(0);
    }
    catch (std::exception& e)
    {
        std::cout << "%TEST_FAILED% time=0 testname=testMakeAppearanceScale2 (mappearanceTest) message=Exception occured: " <<
                e.what() << std::endl;
    }
}

int main(int argc, char** argv)
{
    std::cout << "%SUITE_STARTING% mappearanceTest" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% testMakeAppearance (mappearanceTest)" << std::endl;
    testMakeAppearance();
    std::cout << "%TEST_FINISHED% time=0 testMakeAppearance (mappearanceTest)" << std::endl;

    std::cout << "%TEST_STARTED% testMakeAppearanceColor (mappearanceTest)" << std::endl;
    testMakeAppearanceColor();
    std::cout << "%TEST_FINISHED% time=0 testMakeAppearanceColor (mappearanceTest)" << std::endl;

    std::cout << "%TEST_STARTED% testMakeAppearanceScale (mappearanceTest)" << std::endl;
    testMakeAppearanceScale();
    std::cout << "%TEST_FINISHED% time=0 testMakeAppearanceScale (mappearanceTest)" << std::endl;

    std::cout << "%TEST_STARTED% testMakeAppearanceScale2 (mappearanceTest)" << std::endl;
    testMakeAppearanceScale2();
    std::cout << "%TEST_FINISHED% time=0 testMakeAppearanceScale2 (mappearanceTest)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}
