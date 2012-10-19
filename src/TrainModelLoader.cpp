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
 * File:   TrainModelLaoder.cpp
 * Author: Иван Губочкин
 * 
 * Created on 7 Август 2012 г., 15:52
 */

#include <opencv/highgui.h>
#include <fstream>
#include <boost/lexical_cast.hpp>
#include <string>
#include <iosfwd>
#include <vector>
#include <iterator>

#include "aam/TrainModelLoader.h"
#include "aam/Exceptions.h"

namespace aam
{
    struct PointInfo
    {
        unsigned int pointNumber;
        Point2D point;
    };
    
    TrainModelLoader::TrainModelLoader(int mk)
    : marksCount(mk)
    , grayFlag(true)
    {
    }

    TrainModelLoader::~TrainModelLoader()
    {
    }

    void TrainModelLoader::load(const std::string& markupFile,
            const std::string& imageFile)
    {
        TrainModelInfo model;

        cv::Mat img = cv::imread(imageFile);

        if (img.empty())
        {
            std::cout << "Not found image: " << imageFile << std::endl;
            return;
        }
        
        model.setImage(img, this->grayFlag);

        Vertices2DList markup = loadMarkup(markupFile);
        model.setVertices(markup);

        this->models.push_back(model);
    }

    void TrainModelLoader::clear()
    {
        this->models.clear();
    }

    Vertices2DList TrainModelLoader::loadMarkup(
            const std::string& markupFile)
    {
        Vertices2DList result;
        std::ifstream stream(markupFile.c_str());

        if (!stream)
        {
            throw FileNotFoundError();
        }

        while (!stream.eof())
        {
            std::string line;
            std::getline(stream, line);

            if (!line.empty())
            {
                std::istringstream stringStream(line);
                PointInfo info;

                stringStream >> info.pointNumber >> info.point.x >>
                        info.point.y;
                result.push_back(info.point);
            }
        }

        if (result.size() != this->marksCount && this->marksCount != -1)
        {
            throw InvalidMarkupFile();
        }

        return result;
    }

    int TrainModelLoader::getModelsCount()
    {
        return this->models.size();
    }

    std::vector<TrainModelInfo> TrainModelLoader::getModels()
    {
        return this->models;
    }

    void TrainModelLoader::useGrayImages(bool f)
    {
        this->grayFlag = f;
    }

    bool TrainModelLoader::isGrayImages()
    {
        return this->grayFlag;
    }
}
