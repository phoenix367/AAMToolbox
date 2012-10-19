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
 * File:   AAMFeature.cpp
 * Author: Иван Губочкин
 * 
 * Created on 7 Август 2012 г., 15:31
 */

#include "aam/AAMModel.h"
#include "aam/Exceptions.h"
#include "aam/CommonFunctions.h"

#define MODEL_COUNT_FIELD       "model_count"
#define R_MATRIX_FIELD          "R"

namespace aam
{
    AAMModel::AAMModel()
    {
    }

    AAMModel::~AAMModel()
    {
    }

    void AAMModel::addModel(const AAMModelItem& newModel)
    {
        this->models.push_back(newModel);
    }

    AAMModelItem AAMModel::getModel(int scale) const
    {
        if (scale < 0 || scale >= this->models.size())
        {
            throw InvalidArgumentException();
        }

        return this->models[scale];
    }
    
    int AAMModel::getModelsCount() const
    {
        return this->models.size();
    }

    void AAMModel::clear()
    {
        this->models.clear();
    }

    void AAMModel::save(cv::FileStorage& storage)
    {
        storage << MODEL_COUNT_FIELD << (int) this->models.size();
        for (int i = 0; i < this->models.size(); i++)
        {
            writeModel(storage, this->models[i], i);
        }
    }

    void AAMModel::load(cv::FileStorage& storage)
    {
        int count;
        storage[MODEL_COUNT_FIELD] >> count;
        this->models.resize(count);

        for (int i = 0; i < count; i++)
        {
            readModel(storage, this->models[i], i);
        }
    }

    void AAMModel::writeModel(cv::FileStorage& storage,
            AAMModelItem& item, int scale)
    {
        item.shapeData.save(storage, scale);
        item.appearanceData.save(storage, scale);
        item.shapeAppearance.save(storage, scale);
        storage << CommonFunctions::combineScaleField(
                scale, R_MATRIX_FIELD) << item.R;
    }

    void AAMModel::readModel(cv::FileStorage& storage, AAMModelItem& item,
            int scale)
    {
        item.shapeData.load(storage, scale);
        item.appearanceData.load(storage, scale);
        item.shapeAppearance.load(storage, scale);
        storage[CommonFunctions::combineScaleField(
                scale, R_MATRIX_FIELD)] >> item.R;
        
        PiecewiseWarp::precomputeWarp(item.appearanceData.basePoints,
                item.shapeData.triangles, item.shapeData.textureSize,
                item.warpInfo);
    }

    bool AAMModel::equals(const AAMModel& m)
    {
        return this->models == m.models;
    }
}
