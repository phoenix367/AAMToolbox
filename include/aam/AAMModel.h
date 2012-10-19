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
 * File:   AAMFeature.h
 * Author: Иван Губочкин
 *
 * Created on 7 Август 2012 г., 15:31
 */

#ifndef AAMFEATURE_H
#define	AAMFEATURE_H

#include <vector>

#include "ShapeData.h"
#include "AppearanceData.h"
#include "ShapeAppearanceData.h"
#include "PiecewiseWarp.h"

namespace aam
{
    struct AAMModelItem
    {
        ShapeData shapeData;
        AppearanceData appearanceData;
        ShapeAppearanceData shapeAppearance;
        RealMatrix R;
        PiecewiseWarp::WarpInfo warpInfo; // we don't serialize this

        bool operator ==(const AAMModelItem& item) const
        {
            if (this->R.size != item.R.size)
            {
                return false;
            }
            
            return (cv::countNonZero(this->R != item.R) == 0) &&
                   (this->shapeData == item.shapeData) &&
                   (appearanceData == item.appearanceData) &&
                   (shapeAppearance == item.shapeAppearance);
        }
    };

    class AAMModel
    {
    public:
        AAMModel();
        virtual ~AAMModel();

        void addModel(const AAMModelItem& newModel);
        AAMModelItem getModel(int scale) const;
        int getModelsCount() const;
        void clear();

        void save(cv::FileStorage& storage);
        void load(cv::FileStorage& storage);

        bool equals(const AAMModel& m);
        
    private:
        void writeModel(cv::FileStorage& storage, AAMModelItem& item,
                int scale);
        void readModel(cv::FileStorage& storage, AAMModelItem& item,
                int scale);

    private:
        std::vector<AAMModelItem> models;
    };
}

#endif	/* AAMFEATURE_H */
