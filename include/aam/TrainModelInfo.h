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
 * File:   TrainModelInfo.h
 * Author: Иван Губочкин
 *
 * Created on 7 Август 2012 г., 15:55
 */

#ifndef TRAINMODELINFO_H
#define	TRAINMODELINFO_H

#include "aam.h"

namespace aam
{    
    class TrainModelInfo
    {
    public:
        TrainModelInfo();
        virtual ~TrainModelInfo();

        void setVertices(const Vertices2DList& v);
        Vertices2DList& getVertices();
        std::vector<LineType>& getLines();
        cv::Mat getImage();
        const cv::Mat getImage() const;
        void setImage(const cv::Mat& im, bool setGrayScale = false);
        void setTForm(const TForm& tf);
        TForm& getTForm();
        const TForm& getTForm() const;
        void setCVertices(const Vertices2DList& v);
        Vertices2DList& getCVertices();
        const Vertices2DList& getCVertices() const;
        const Vertices2DList& getVertices() const;
        const std::vector<cv::Vec3i> getTriangles() const;
        
    private:
        Vertices2DList vertices;
        std::vector<LineType> lines;
        cv::Mat image;
        TForm tform;
        Vertices2DList cVertices;
        std::vector<cv::Vec3i> triangles;
    };
}

#endif	/* TRAINMODELINFO_H */
