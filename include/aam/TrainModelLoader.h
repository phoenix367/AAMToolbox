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
 * File:   TrainModelLaoder.h
 * Author: Иван Губочкин
 *
 * Created on 7 Август 2012 г., 15:52
 */

#ifndef TRAINMODELLAODER_H
#define	TRAINMODELLAODER_H

#include <string>
#include <vector>

#include "TrainModelInfo.h"

namespace aam
{
    class TrainModelLoader
    {
    public:
        TrainModelLoader(int mk = -1);
        virtual ~TrainModelLoader();

        void load(const std::string& markupFile, const std::string& imageFile);
        void clear();
        int getModelsCount();
        std::vector<TrainModelInfo> getModels();
        void useGrayImages(bool f);
        bool isGrayImages();

    private:
        Vertices2DList loadMarkup(const std::string& markupFile);
        
    private:
        std::vector<TrainModelInfo> models;
        int marksCount;
        bool grayFlag;
    };
}

#endif	/* TRAINMODELLAODER_H */
