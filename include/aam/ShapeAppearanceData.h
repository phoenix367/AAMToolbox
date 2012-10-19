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
 * File:   ShapeAppearanceData.h
 * Author: Иван Губочкин
 *
 * Created on 17 Август 2012 г., 16:42
 */

#ifndef SHAPEAPPEARANCEDATA_H
#define	SHAPEAPPEARANCEDATA_H

#include "aam.h"

namespace aam
{
    class ShapeAppearanceData
    {
    public:
        RealMatrix eigVectors;
        RealMatrix eigValues;
        RealMatrix bMeans;
        RealMatrix b;
        RealMatrix w;

    public:
        void save(cv::FileStorage& storage, int scale);
        void load(cv::FileStorage& storage, int scale);

        bool operator ==(const ShapeAppearanceData& shapeAppearance) const;

    private:
        static const char* FIELD_SHAPE_APPEARANCE_EIGVALUES;
        static const char* FIELD_SHAPE_APPEARANCE_EIGVECTORS;
        static const char* FIELD_SHAPE_APPEARANCE_B_MEANS;
        static const char* FIELD_SHAPE_APPEARANCE_B;
        static const char* FIELD_SHAPE_APPEARANCE_W;
    };
}

#endif	/* SHAPEAPPEARANCEDATA_H */
