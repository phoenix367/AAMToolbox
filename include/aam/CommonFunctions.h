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
 * File:   CommonFunctions.h
 * Author: Иван Губочкин
 *
 * Created on 12 Август 2012 г., 22:19
 */

#ifndef COMMONFUNCTIONS_H
#define	COMMONFUNCTIONS_H

#include <opencv/cv.h>
#include <dlib/matrix.h>

#include "aam.h"

namespace aam
{
    class CommonFunctions
    {
    public:
        static void PCA(const RealMatrix& data, RealMatrix& means,
                RealMatrix& eigenVectors, RealMatrix& eigenValues);
        static void varPCA(const RealMatrix& data, RealMatrix& means,
                RealMatrix& eigenVectors, RealMatrix& eigenValues);
        static void appPCA(const RealMatrix& data, RealMatrix& means,
                RealMatrix& eigenVectors, RealMatrix& eigenValues);
        static void delaunay(const Vertices2DList& pts,
            std::vector<cv::Vec3i>& triangles);
        static void drawObject(const cv::Size& textureSize,
            const std::vector<LineType>& lines, const Vertices2DList& points,
            cv::Mat1b& objectPixels);
        static void removeEigNoise(RealMatrix& eigVectors,
            RealMatrix& eigValues, RealType threshold);
        static std::string combineScaleField(int scale,
            const std::string& filedName);
        static void opencvMat2Dlib(const RealMatrix& src,
            dlib::matrix<RealType, 0, 1>& dst);
        static void dlibMat2OpenCV(const dlib::matrix<RealType, 0, 1>& src,
            RealMatrix& dst);
        static void gradient2D(const RealMatrix& M, const cv::Mat1b& mask,
            RealMatrix& di, RealMatrix& dj);
        static void gradient2D(const ColorMatrix& M,
                const cv::Mat1b& mask,
                ColorMatrix& di, ColorMatrix& dj);
        static void orthonormGS(const RealMatrix& M, RealMatrix& V);
        static void getWarpMap(const Vertices2DList& shape,
            const std::vector<cv::Vec3i>& triangles,
            const cv::Size& warpSize,
            cv::Mat1i& warpMap);
        static RealType procrustes(const Vertices2DList& X,
            const Vertices2DList& Y, Vertices2DList& Z);
        static bool convertImage(const cv::Mat& srcImage,
            cv::Mat& cvtImage, bool toGrayScale);
        static RealType cond(const RealMatrix& A, int normType =
            cv::NORM_L2);

    private:
        static bool triPred(const cv::Rect& r, const cv::Vec6f& t);
        static bool findPointNumber(const Vertices2DList& pts,
            const cv::Point2f& pt, int& ptNumber);
    };
}

#endif	/* COMMONFUNCTIONS_H */
