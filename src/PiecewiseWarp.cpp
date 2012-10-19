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
 * File:   PiecewiseWarp.cpp
 * Author: Иван Губочкин
 * 
 * Created on 16 Август 2012 г., 12:07
 */

#include <boost/assign/list_of.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <iterator>

#include "aam/PiecewiseWarp.h"
#include "aam/vector_op.h"

namespace aam
{
    void PiecewiseWarp::warpTriangle(const cv::Mat& imgIn, cv::Mat& imgOut,
            const Vertices2DList& srcVertices,
            const Vertices2DList& trgVertices,
            const std::vector<cv::Vec3i>& triangles,
            const cv::Size& imageSize)
    {
        assert(srcVertices.size() == trgVertices.size());
        assert(imgIn.type() == CV_MAKETYPE(OpenCVRealType::type, 1) ||
               imgIn.type() == CV_MAKETYPE(OpenCVRealType::type, 3));
        
        imgOut = cv::Mat::zeros(imageSize.height, imageSize.width,
                imgIn.type());

        /* Interpolation percentages */
        std::vector<cv::Point> r;
        r.reserve(imgIn.rows * imgIn.cols);
        
        std::vector<float> posuvX, posuvY;
        posuvX.reserve(imgIn.rows * imgIn.cols);
        posuvY.reserve(imgIn.rows * imgIn.cols);

//        int64 start = cv::getTickCount();
        for (int t = 0; t < triangles.size(); t++)
        {
            cv::Vec3i tr = triangles[t];
            Point2D verticesSrc[3] =
            {
                srcVertices[tr[0]],
                srcVertices[tr[1]],
                srcVertices[tr[2]]
            };

            Point2D verticesDst[3] =
            {
                trgVertices[tr[0]],
                trgVertices[tr[1]],
                trgVertices[tr[2]]
            };

            std::vector<cv::Point2f> trianglePoints =
                    boost::assign::list_of
                    (cv::Point2f(verticesDst[0].x, verticesDst[0].y))
                    (cv::Point2f(verticesDst[1].x, verticesDst[1].y))
                    (cv::Point2f(verticesDst[2].x, verticesDst[2].y));
            cv::Rect boundRect = cv::boundingRect(trianglePoints);
            //cv::Rect boundRect(0, 0, imageSize.width, imageSize.height);
            
            cv::Point minBound(boundRect.x, boundRect.y);
            minBound.x = std::max(minBound.x, 0);
            minBound.y = std::max(minBound.y, 0);

            cv::Point maxBound(boundRect.x + boundRect.width,
                    boundRect.y + boundRect.height);
            maxBound.x = std::min(maxBound.x, imageSize.width - 1);
            maxBound.y = std::min(maxBound.y, imageSize.height - 1);

            Point2D p1(verticesDst[0].x, verticesDst[0].y);
            Point2D p2(verticesDst[1].x, verticesDst[1].y);
            Point2D p3(verticesDst[2].x, verticesDst[2].y);

            // Normalization factors
            RealType f12 = ( p2.y - p3.y ) * p1.x  + (p3.x - p2.x ) * p1.y +
                    p2.x * p3.y - p3.x *p2.y;
            RealType f20 = ( p3.y - p1.y ) * p2.x  + (p1.x - p3.x ) * p2.y +
                    p3.x * p1.y - p1.x *p3.y;
            RealType f01 = ( p1.y - p2.y ) * p3.x  + (p2.x - p1.x ) * p3.y +
                    p1.x * p2.y - p2.x *p1.y;

            // Lambda Gradient
            Point2D g12(( p2.y - p3.y ) / f12, (p3.x - p2.x ) / f12);
            Point2D g20(( p3.y - p1.y ) / f20, (p1.x - p3.x ) / f20);
            Point2D g01(( p1.y - p2.y ) / f01, (p2.x - p1.x ) / f01);

            // Center compensation
            RealType c12 = (p2.x * p3.y - p3.x *p2.y) / f12;
            RealType c20 = (p3.x * p1.y - p1.x *p3.y) / f20;
            RealType c01 = (p1.x * p2.y - p2.x *p1.y) / f01;

            RealType lambdat[3] =
            {
                g12.x * minBound.x + g12.y * minBound.y + c12,
                g20.x * minBound.x + g20.y * minBound.y + c20,
                g01.x * minBound.x + g01.y * minBound.y + c01
            };
            
            for (int j = minBound.y; j <= maxBound.y;
                    j++)
            {
                RealType lambda[3] =
                {
                    lambdat[0],
                    lambdat[1],
                    lambdat[2]
                };
                
                for (int i = minBound.x; i <= maxBound.x;
                        i++)
                {
                    if (lambda[0] <= 1 && lambda[0] >= 0 &&
                            lambda[1] <= 1 && lambda[1] >= 0 &&
                            lambda[2] <= 1 && lambda[2] >= 0)
                    {
                        posuvX.push_back(lambda[0] * verticesSrc[0].x +
                                lambda[1] * verticesSrc[1].x +
                                lambda[2] * verticesSrc[2].x);

                        posuvY.push_back(lambda[0] * verticesSrc[0].y +
                                lambda[1] * verticesSrc[1].y +
                                lambda[2] * verticesSrc[2].y);
                        r.push_back(cv::Point(i, j));
                    }

                    lambda[0] += g12.x;
                    lambda[1] += g20.x;
                    lambda[2] += g01.x;
                }

                lambdat[0] += g12.y;
                lambdat[1] += g20.y;
                lambdat[2] += g01.y;
            }
        }
//        std::cout << "Remap working time: " << (cv::getTickCount() - start) /
//                cv::getTickFrequency() << std::endl;

        cv::Mat imgTr;

        if (!posuvY.empty() && !posuvX.empty())
        {
            cv::remap(imgIn, imgTr, posuvX, posuvY, cv::INTER_LINEAR,
                    cv::BORDER_REPLICATE);
        }


        switch (imgIn.channels())
        {
            case 1:
                for (int i = 0; i < imgTr.cols; i++)
                {
                    imgOut.at<RealType>(r[i].y, r[i].x) =
                            imgTr.at<RealType>(0, i);
                }
                break;
            case 3:
                for (int i = 0; i < imgTr.cols; i++)
                {
                    imgOut.at<cv::Vec<RealType, 3> >(r[i].y, r[i].x) =
                            imgTr.at<cv::Vec<RealType, 3> >(0, i);
                }
                break;
        }
    }

    void PiecewiseWarp::precomputeWarp(const Vertices2DList& trgVertices,
            const std::vector<cv::Vec3i>& triangles,
            const cv::Size& imageSize,
            WarpInfo& warpInfo)
    {        
//        int64 start = cv::getTickCount();
        for (int t = 0; t < triangles.size(); t++)
        {
            cv::Vec3i tr = triangles[t];

            Point2D verticesDst[3] =
            {
                trgVertices[tr[0]],
                trgVertices[tr[1]],
                trgVertices[tr[2]]
            };

            std::vector<cv::Point2f> trianglePoints =
                    boost::assign::list_of
                    (cv::Point2f(verticesDst[0].x, verticesDst[0].y))
                    (cv::Point2f(verticesDst[1].x, verticesDst[1].y))
                    (cv::Point2f(verticesDst[2].x, verticesDst[2].y));
            cv::Rect boundRect = cv::boundingRect(trianglePoints);
            //cv::Rect boundRect(0, 0, imageSize.width, imageSize.height);

            cv::Point minBound(boundRect.x, boundRect.y);
            minBound.x = std::max(minBound.x, 0);
            minBound.y = std::max(minBound.y, 0);

            cv::Point maxBound(boundRect.x + boundRect.width,
                    boundRect.y + boundRect.height);
            maxBound.x = std::min(maxBound.x, imageSize.width - 1);
            maxBound.y = std::min(maxBound.y, imageSize.height - 1);

            Point2D p1(verticesDst[0].x, verticesDst[0].y);
            Point2D p2(verticesDst[1].x, verticesDst[1].y);
            Point2D p3(verticesDst[2].x, verticesDst[2].y);

            // Normalization factors
            RealType f12 = ( p2.y - p3.y ) * p1.x  + (p3.x - p2.x ) * p1.y +
                    p2.x * p3.y - p3.x *p2.y;
            RealType f20 = ( p3.y - p1.y ) * p2.x  + (p1.x - p3.x ) * p2.y +
                    p3.x * p1.y - p1.x *p3.y;
            RealType f01 = ( p1.y - p2.y ) * p3.x  + (p2.x - p1.x ) * p3.y +
                    p1.x * p2.y - p2.x *p1.y;

            // Lambda Gradient
            Point2D g12(( p2.y - p3.y ) / f12, (p3.x - p2.x ) / f12);
            Point2D g20(( p3.y - p1.y ) / f20, (p1.x - p3.x ) / f20);
            Point2D g01(( p1.y - p2.y ) / f01, (p2.x - p1.x ) / f01);

            // Center compensation
            RealType c12 = (p2.x * p3.y - p3.x *p2.y) / f12;
            RealType c20 = (p3.x * p1.y - p1.x *p3.y) / f20;
            RealType c01 = (p1.x * p2.y - p2.x *p1.y) / f01;

            RealType lambdat[3] =
            {
                g12.x * minBound.x + g12.y * minBound.y + c12,
                g20.x * minBound.x + g20.y * minBound.y + c20,
                g01.x * minBound.x + g01.y * minBound.y + c01
            };

            for (int j = minBound.y; j <= maxBound.y;
                    j++)
            {
                RealType lambda[3] =
                {
                    lambdat[0],
                    lambdat[1],
                    lambdat[2]
                };

                for (int i = minBound.x; i <= maxBound.x;
                        i++)
                {
                    if (lambda[0] <= 1 && lambda[0] >= 0 &&
                            lambda[1] <= 1 && lambda[1] >= 0 &&
                            lambda[2] <= 1 && lambda[2] >= 0)
                    {
                        warpInfo.r.push_back(cv::Point(i, j));
                        warpInfo.lambda.push_back(LambdaVector(
                                lambda[0], lambda[1], lambda[2]));
                        warpInfo.triData.push_back(t);
                    }

                    lambda[0] += g12.x;
                    lambda[1] += g20.x;
                    lambda[2] += g01.x;
                }

                lambdat[0] += g12.y;
                lambdat[1] += g20.y;
                lambdat[2] += g01.y;
            }
        }

        warpInfo.nPixels = warpInfo.r.size();
    }

    void PiecewiseWarp::warpTriangle(const cv::Mat& imgIn, cv::Mat& imgOut,
            const Vertices2DList& srcVertices,
            const std::vector<cv::Vec3i>& triangles,
            const cv::Size& imageSize, const WarpInfo& info)
    {
        assert(imgIn.type() == CV_MAKETYPE(OpenCVRealType::type, 1) ||
               imgIn.type() == CV_MAKETYPE(OpenCVRealType::type, 3));

        imgOut = cv::Mat::zeros(imageSize.height, imageSize.width,
                imgIn.type());
        std::vector<float> posuvX(info.nPixels), posuvY(info.nPixels);

        for (int i = 0; i < info.nPixels; i++)
        {
            cv::Vec3i tr = triangles[info.triData[i]];
            Point2D verticesSrc[3] =
            {
                srcVertices[tr[0]],
                srcVertices[tr[1]],
                srcVertices[tr[2]]
            };
            LambdaVector lambda = info.lambda[i];

            posuvX[i] = lambda[0] * verticesSrc[0].x +
                    lambda[1] * verticesSrc[1].x +
                    lambda[2] * verticesSrc[2].x;

            posuvY[i] = lambda[0] * verticesSrc[0].y +
                    lambda[1] * verticesSrc[1].y +
                    lambda[2] * verticesSrc[2].y;
        }

        cv::Mat imgTr;

        if (!posuvY.empty() && !posuvX.empty())
        {
            cv::remap(imgIn, imgTr, posuvX, posuvY, cv::INTER_LINEAR,
                    cv::BORDER_REPLICATE);
        }

        //int64 start = cv::getTickCount();
        switch (imgIn.channels())
        {
            case 1:
                for (int i = 0; i < imgTr.cols; i++)
                {
                    imgOut.at<RealType>(info.r[i].y, info.r[i].x) =
                            imgTr.at<RealType>(0, i);
                }
                break;
            case 3:
                for (int i = 0; i < imgTr.cols; i++)
                {
                    imgOut.at<ColorVector>(info.r[i].y,
                            info.r[i].x) = imgTr.at<ColorVector>(0, i);
                }
                break;
        }
//        std::cout << "Remap working time: " << (cv::getTickCount() - start) /
//                cv::getTickFrequency() << std::endl;
    }
}
