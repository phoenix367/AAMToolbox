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
 * File:   PiecewiseWarp.h
 * Author: Иван Губочкин
 *
 * Created on 16 Август 2012 г., 12:07
 */

#ifndef PIECEWISEWARP_H
#define	PIECEWISEWARP_H

#include "aam.h"

namespace aam
{
    class PiecewiseWarp
    {
    public:
        struct WarpInfo
        {
            std::vector<LambdaVector> lambda;
            std::vector<int> triData;
            std::vector<cv::Point> r;
            int nPixels;
        };

    public:
        static void warpTriangle(const cv::Mat& imgIn, cv::Mat& imgOut,
            const Vertices2DList& srcVertices,
            const Vertices2DList& trgVertices,
            const std::vector<cv::Vec3i>& triangles,
            const cv::Size& imageSize);
        static void warpTriangle(const cv::Mat& imgIn, cv::Mat& imgOut,
            const Vertices2DList& srcVertices,
            const std::vector<cv::Vec3i>& triangles,
            const cv::Size& imageSize,
            const WarpInfo& info);
        static void precomputeWarp(const Vertices2DList& trgVertices,
            const std::vector<cv::Vec3i>& triangles,
            const cv::Size& imageSize,
            WarpInfo& warpInfo);

    private:

    };
}

#endif	/* PIECEWISEWARP_H */
