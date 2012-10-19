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
 * File:   AppearanceData.h
 * Author: Иван Губочкин
 *
 * Created on 14 Август 2012 г., 15:21
 */

#ifndef APPEARANCEDATA_H
#define	APPEARANCEDATA_H

#include <opencv/cv.h>

#include "aam.h"

namespace aam
{
    class AppearanceData
    {
    public:
        Vertices2DList basePoints;
        cv::Mat grayVector;
        cv::Mat1b objectPixels;
        int nPixels;
        RealMatrix eigenValues;
        RealMatrix eigenVectors;
        RealMatrix grayMean;

    public:
        AppearanceData();

        void save(cv::FileStorage& storage, int scale);
        void load(cv::FileStorage& storage, int scale);

        bool operator ==(const AppearanceData& appearance) const;

    private:
        static const char* FIELD_APPEARANCE_BASE_POINTS;
        static const char* FIELD_APPEARANCE_GRAY_VECTOR;
        static const char* FIELD_APPEARANCE_OBJECT_PIXELS;
        static const char* FIELD_APPEARANCE_NPIXELS;
        static const char* FIELD_APPEARANCE_EIGVALUES;
        static const char* FIELD_APPEARANCE_EIGVECTORS;
        static const char* FIELD_APPEARANCE_GRAY_MEAN;
    };
}

#endif	/* APPEARANCEDATA_H */
