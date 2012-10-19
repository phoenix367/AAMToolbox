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
 * File:   ShapeData.h
 * Author: Иван Губочкин
 *
 * Created on 10 Август 2012 г., 13:45
 */

#ifndef SHAPEDATA_H
#define	SHAPEDATA_H

#include "aam.h"

namespace aam
{
    class ShapeData
    {
    public:
        RealMatrix eigVectors;
        RealMatrix eigValues;
        Vertices2DList meanVertices;
        cv::Mat x;
        Vertices2DList xMean;
        RealType sVariance;
        RealType rVariance;
        std::vector<LineType> lines;
        std::vector<cv::Vec3i> triangles;
        cv::Size textureSize;

    public:
        ShapeData();
        
        void save(cv::FileStorage& storage, int scale);
        void load(cv::FileStorage& storage, int scale);

        bool operator ==(const ShapeData& shapeData) const;

    private:
        static const char* FIELD_SHAPE_EIG_VECTORS;
        static const char* FIELD_SHAPE_EIG_VALUES;
        static const char* FIELD_SHAPE_MEAN_VERTICES;
        static const char* FILED_SHAPE_X;
        static const char* FIELD_SHAPE_X_MEAN;
        static const char* FIELD_SHAPE_S_VARIANCE;
        static const char* FIELD_SHAPE_R_VARIANCE;
        static const char* FIELD_SHAPE_LINES;
        static const char* FIELD_SHAPE_TRIANGLES;
        static const char* FIELD_SHAPE_TEXTURE_SIZE;
    };
}

#endif	/* SHAPEDATA_H */
