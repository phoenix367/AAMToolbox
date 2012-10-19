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
 * File:   ICAAMModel.h
 * Author: Иван Губочкин
 *
 * Created on 9 Октябрь 2012 г., 14:37
 */

#ifndef ICAAMMODEL_H
#define	ICAAMMODEL_H

#include "AppearanceDataIC.h"

namespace aam
{
    class ICAAMModel
    {
    public:
        ICAAMModel();
        virtual ~ICAAMModel();

        void addModel(const AppearanceDataIC& newModel);
        AppearanceDataIC getModel(int scale) const;
        int getModelsCount() const;
        void clear();

        void save(cv::FileStorage& storage);
        void load(cv::FileStorage& storage);

    private:
        std::vector<AppearanceDataIC> modelData;

        static const char *MODEL_COUNT_FIELD;
    };
}

#endif	/* ICAAMMODEL_H */
