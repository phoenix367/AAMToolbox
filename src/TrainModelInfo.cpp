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
 * File:   TrainModelInfo.cpp
 * Author: Иван Губочкин
 * 
 * Created on 7 Август 2012 г., 15:55
 */

#include "aam/vector_op.h"
#include "aam/TrainModelInfo.h"
#include "aam/Exceptions.h"
#include "aam/CommonFunctions.h"

namespace aam
{
    TrainModelInfo::TrainModelInfo()
    {
    }

    TrainModelInfo::~TrainModelInfo()
    {
    }

    void TrainModelInfo::setVertices(const Vertices2DList& v)
    {
        this->vertices = v;

        std::vector<int> c;
        if (!v.empty())
        {
            cv::convexHull(convertVector<float>(v), c);
        }

        this->lines.clear();
        
        if (c.size() > 1)
        {
            this->lines = c;
        }

        if (this->vertices.empty())
        {
            this->triangles.clear();
        }
        else
        {
            CommonFunctions::delaunay(v, this->triangles);
        }
    }

    std::vector<LineType>& TrainModelInfo::getLines()
    {
        return this->lines;
    }

    Vertices2DList& TrainModelInfo::getVertices()
    {
        return this->vertices;
    }

    void TrainModelInfo::setImage(const cv::Mat& im, bool setGrayScale)
    {
        if (!CommonFunctions::convertImage(im, this->image, setGrayScale))
        {
            throw InvalidImageFormat();
        }
    }

    cv::Mat TrainModelInfo::getImage()
    {
        return this->image;
    }

    const cv::Mat TrainModelInfo::getImage() const
    {
        return this->image;
    }

    void TrainModelInfo::setTForm(const TForm& tf)
    {
        this->tform = tf;
    }

    TForm& TrainModelInfo::getTForm()
    {
        return this->tform;
    }

    const TForm& TrainModelInfo::getTForm() const
    {
        return this->tform;
    }

    void TrainModelInfo::setCVertices(const Vertices2DList& v)
    {
        this->cVertices = v;
    }

    Vertices2DList& TrainModelInfo::getCVertices()
    {
        return this->cVertices;
    }

    const Vertices2DList& TrainModelInfo::getCVertices() const
    {
        return this->cVertices;
    }

    const Vertices2DList& TrainModelInfo::getVertices() const
    {
        return this->vertices;
    }

    const std::vector<cv::Vec3i> TrainModelInfo::getTriangles() const
    {
        return this->triangles;
    }
}
