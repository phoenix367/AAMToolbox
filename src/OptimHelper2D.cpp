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
 * File:   OptimHelper2D.cpp
 * Author: Иван Губочкин
 * 
 * Created on 13 Сентябрь 2012 г., 16:26
 */

#include "aam/OptimHelper2D.h"
#include "aam/CommonFunctions.h"
#include "aam/vector_op.h"

namespace aam
{
    OptimHelper2D::OptimHelper2D(const RealMatrix& x, const ShapeData& sd,
                const ShapeAppearanceData& sad)
    : x2(x)
    , shapeData(sd)
    , shapeAppearance(sad)
    , invW(sad.w.inv())
    , xMean(pointVector2Mat(sd.xMean))
    {
    }

    OptimHelper2D::~OptimHelper2D()
    {
    }

    double OptimHelper2D::operator()(
        const dlib::matrix<RealType, 0, 1>& arg) const
    {
        RealMatrix c;
        CommonFunctions::dlibMat2OpenCV(arg, c);

        RealMatrix b = this->shapeAppearance.bMeans +
                this->shapeAppearance.eigVectors * c;
        RealMatrix b1 = this->invW *
                b.rowRange(0, this->shapeAppearance.w.rows);
        RealMatrix x = this->xMean +
                this->shapeData.eigVectors * b1;
        RealMatrix E = x - this->x2;

        //dlib::matrix<RealType, 0, 1> out;
        //CommonFunctions::opencvMat2Dlib(E, out);

        //std::cout << E << std::endl;

        return cv::norm(E);
    }
}
