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
 * File:   trainICTest.cpp
 * Author: Иван Губочкин
 *
 * Created on 26.09.2012, 18:05:01
 */

#include <stdlib.h>
#include <iostream>
#include <opencv/highgui.h>
#include <vector>
#include <boost/assign/list_of.hpp>
#include <boost/filesystem/operations.hpp>
#include <iosfwd>

#include "aam/AAMFunctions2D.h"
#include "aam/TrainModelLoader.h"

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

void testTrainICAAMGray()
{
    std::cout << "trainICTest testTrainICAAMGray" << std::endl;
    aam::AppearanceDataIC model;
    aam::TrainModelLoader loader;
    loader.useGrayImages(true);

    for (int i = 0; i < TRIANGLES_COUNT; i++)
    {
        model.triangles.push_back(cv::Vec3i(trianglesData[i * 3],
                trianglesData[i * 3 + 1], trianglesData[i * 3 + 2]));
    }

    try
    {
        std::vector<std::string> fileNames =
                boost::assign::list_of<std::string>
                ("107_0764.bmp")  /*("107_0766.bmp")*/  ("107_0779.bmp")
                ("107_0780.bmp")  ("107_0781.bmp")  ("107_0782.bmp")
                ("107_0783.bmp")  ("107_0784.bmp")  ("107_0785.bmp")
                ("107_0786.bmp")  ("107_0787.bmp")  ("107_0788.bmp")
                ("107_0789.bmp")  ("107_0790.bmp")  ("107_0791.bmp")
                ("107_0792.bmp")  ("107_0793.bmp")  ("107_0794.bmp")
                ("107_0795.bmp")  ("107_0798.bmp")  ("107_0799.bmp")
                ("107_0800.bmp")  ("108_0801.bmp")  ("108_0802.bmp")
                ("108_0803.bmp")  ("108_0804.bmp");
        
        for (int i = 0; i < fileNames.size(); i++)
        {
            std::ostringstream stream;

            stream << "data/cootes/" << fileNames[i] << ".mat.dat";
            std::string markupFile = stream.str();

            stream.str(std::string());

            stream << "data/cootes/" << fileNames[i];
            std::string imageFile = stream.str();

            loader.load(markupFile, imageFile);
        }

        std::vector<aam::TrainModelInfo> trainData = loader.getModels();
        aam::AAMFunctions2D::trainModelIC(0.95, trainData, model);

        if (!boost::filesystem::exists("output"))
        {
            boost::filesystem::create_directory("output");
        }

        cv::FileStorage storage("output/aam_ic_test.xml",
                cv::FileStorage::WRITE);
        storage << "R" << model.R;
        storage << "s" << model.s;
        storage << "s_star" << model.sStar;
        storage << "s0" << model.s0;
        storage << "A0" << model.A0;
        storage << "mask" << model.mask;
        storage << "triangles" << model.triangles;

        cv::Mat1i tmp(2, 1);
        tmp(0, 0) = model.textureSize.width;
        tmp(1, 0) = model.textureSize.height;
        storage << "texture_size" << tmp;
        storage.release();

        aam::RealMatrix targetR;
        if (!loadVector("data/aam_r_vectors.raw", model.nPixels, 20,
                targetR))
        {
            std::cout << "%TEST_FAILED% time=0 testname=testTrainICAAMGray (trainICTest) message=Can't reference R matrix" << std::endl;
            return;
        }

        aam::RealMatrix targetA;
        if (!loadVector("data/aam_a_vectors.raw", model.nPixels, 22,
                targetA))
        {
            std::cout << "%TEST_FAILED% time=0 testname=testTrainICAAMGray (trainICTest) message=Can't reference A matrix" << std::endl;
            return;
        }

        cv::Mat m, s;
        cv::meanStdDev(model.A, m, s);
        std::cout << m << std::endl;
        std::cout << s << std::endl;

        cv::meanStdDev(targetA, m, s);
        std::cout << m << std::endl;
        std::cout << s << std::endl;

        aam::RealMatrix Rsum, Rsum2;
        cv::reduce(model.R.t(), Rsum, 1, CV_REDUCE_SUM);
        cv::reduce(targetR, Rsum2, 1, CV_REDUCE_SUM);
        
            cv::Mat img, img2;
            aam::AAMFunctions2D::vector2Appearance(Rsum,
                    model.mask,
                    model.textureSize, img);
            aam::AAMFunctions2D::vector2Appearance(Rsum2,
                    model.mask,
                    model.textureSize, img2);

            cv::normalize(img2, img, 1, 0, cv::NORM_MINMAX);
            cv::imshow("test", img);
            cv::waitKey(0);
    }
    catch (std::exception& e)
    {
        std::cout << "%TEST_FAILED% time=0 testname=testTrainICAAMGray (trainICTest) message=Exception occured: " <<
                e.what() << std::endl;
    }
}

void testTrainICAAMColor()
{
    std::cout << "trainICTest testTrainICAAMColor" << std::endl;
    aam::AppearanceDataIC model;
    aam::TrainModelLoader loader;
    loader.useGrayImages(false);

    for (int i = 0; i < TRIANGLES_COUNT; i++)
    {
        model.triangles.push_back(cv::Vec3i(trianglesData[i * 3],
                trianglesData[i * 3 + 1], trianglesData[i * 3 + 2]));
    }

    try
    {
        std::vector<std::string> fileNames =
                boost::assign::list_of<std::string>
                ("107_0764.bmp")  /*("107_0766.bmp")*/  ("107_0779.bmp")
                ("107_0780.bmp")  ("107_0781.bmp")  ("107_0782.bmp")
                ("107_0783.bmp")  ("107_0784.bmp")  ("107_0785.bmp")
                ("107_0786.bmp")  ("107_0787.bmp")  ("107_0788.bmp")
                ("107_0789.bmp")  ("107_0790.bmp")  ("107_0791.bmp")
                ("107_0792.bmp")  ("107_0793.bmp")  ("107_0794.bmp")
                ("107_0795.bmp")  ("107_0798.bmp")  ("107_0799.bmp")
                ("107_0800.bmp")  ("108_0801.bmp")  ("108_0802.bmp")
                ("108_0803.bmp")  ("108_0804.bmp");

        for (int i = 0; i < fileNames.size(); i++)
        {
            std::ostringstream stream;

            stream << "data/cootes/" << fileNames[i] << ".mat.dat";
            std::string markupFile = stream.str();

            stream.str(std::string());

            stream << "data/cootes/" << fileNames[i];
            std::string imageFile = stream.str();

            loader.load(markupFile, imageFile);
        }

        std::vector<aam::TrainModelInfo> trainData = loader.getModels();
        aam::AAMFunctions2D::trainModelIC(0.98, trainData, model);

        cv::FileStorage storage("output/aam_ic_c_test.xml",
                cv::FileStorage::WRITE);
        storage << "R" << model.R;
        storage << "s" << model.s;
        storage << "s_star" << model.sStar;
        storage << "s0" << model.s0;
        storage << "A0" << model.A0;
        storage << "mask" << model.mask;
        storage << "triangles" << model.triangles;

        cv::Mat1i tmp(2, 1);
        tmp(0, 0) = model.textureSize.width;
        tmp(1, 0) = model.textureSize.height;
        storage << "texture_size" << tmp;
        storage.release();

        for (int i = 0; i < model.R.rows; i++)
        {
            cv::Mat img;
            aam::AAMFunctions2D::vector2Appearance(model.R.t().col(i),
                    model.mask,
                    model.textureSize, img);

            cv::normalize(img, img, 1, 0, cv::NORM_MINMAX);
            cv::imshow("test", img);
            cv::waitKey(500);
        }
        cv::waitKey(0);
    }
    catch (std::exception& e)
    {
        std::cout << "%TEST_FAILED% time=0 testname=testTrainICAAMColor (trainICTest) message=Exception occured: " <<
                e.what() << std::endl;
    }
}

int main(int argc, char** argv)
{
    std::cout << "%SUITE_STARTING% trainICTest" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% testTrainICAAMGray (trainICTest)" << std::endl;
    testTrainICAAMGray();
    std::cout << "%TEST_FINISHED% time=0 testTrainICAAMGray (trainICTest)" << std::endl;

    std::cout << "%TEST_STARTED% testTrainICAAMColor (trainICTest)\n" << std::endl;
    testTrainICAAMColor();
    std::cout << "%TEST_FINISHED% time=0 testTrainICAAMColor (trainICTest)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}
