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
 * File:   aam.h
 * Author: Иван Губочкин
 *
 * Created on 7 Август 2012 г., 12:29
 */

#ifndef AAM_H
#define	AAM_H

#include <vector>
#include <opencv/cv.h>

namespace aam
{
    typedef double RealType;
    typedef cv::DataType<RealType> OpenCVRealType;
    typedef std::vector<RealType> RealVector;
    typedef cv::Mat_<RealType> RealMatrix;
    typedef cv::Vec<RealType, 3> ColorVector;
    typedef cv::Mat_<ColorVector> ColorMatrix;
    typedef ColorMatrix LambdaMatrix;
    typedef cv::Vec<RealType, 3> LambdaVector;

    typedef cv::Point_<RealType> Point2D;
    typedef cv::Point3_<RealType> Point3D;

    typedef std::vector<Point2D> Vertices2DList;
    typedef std::vector<Point3D> Vertices3DList;

    typedef int LineType;

    struct TForm
    {
        Point2D offsetV; // Shape central point
        RealType offsetSX; // Shape scale X
        RealType offsetSY; // Shape scale Y
        RealType offsetS;
        RealType offsetR;

        TForm()
        : offsetSX(0.0)
        , offsetSY(0.0)
        , offsetS(0.0)
        , offsetR(0.0)
        {

        }
    };

    namespace algorithm
    {
        enum AAMAlgorithm
        {
            conventional = 0,
            inverseComposition,
            invalid
        };
    }
}

#endif	/* AAM_H */
