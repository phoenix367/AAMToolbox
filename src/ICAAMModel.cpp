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
 * File:   ICAAMModel.cpp
 * Author: Иван Губочкин
 * 
 * Created on 9 Октябрь 2012 г., 14:37
 */

#include "aam/ICAAMModel.h"
#include "aam/Exceptions.h"

namespace aam
{
    const char *ICAAMModel::MODEL_COUNT_FIELD = "model_count";
    
    ICAAMModel::ICAAMModel()
    {
    }

    ICAAMModel::~ICAAMModel()
    {
    }

    void ICAAMModel::addModel(const AppearanceDataIC& newModel)
    {
        this->modelData.push_back(newModel);
    }

    AppearanceDataIC ICAAMModel::getModel(int scale) const
    {
        if (scale < 0 || scale >= this->modelData.size())
        {
            throw InvalidArgumentException();
        }

        return this->modelData[scale];
    }
    
    int ICAAMModel::getModelsCount() const
    {
        return this->modelData.size();
    }

    void ICAAMModel::clear()
    {
        this->modelData.clear();
    }

    void ICAAMModel::save(cv::FileStorage& storage)
    {
        storage << MODEL_COUNT_FIELD << (int) this->modelData.size();
        
        for (int i = 0; i < this->modelData.size(); i++)
        {
            this->modelData[i].save(storage, i);
        }
    }

    void ICAAMModel::load(cv::FileStorage& storage)
    {
        int modelCount;

        storage[MODEL_COUNT_FIELD] >> modelCount;

        this->modelData.resize(modelCount);
        for (int i = 0; i < modelCount; i++)
        {
            this->modelData[i].load(storage, i);
        }
    }
}
