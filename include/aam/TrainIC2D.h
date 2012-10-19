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
 * File:   TrainIC2D.h
 * Author: Иван Губочкин
 *
 * Created on 5 Октябрь 2012 г., 17:39
 */

#ifndef TRAINIC2D_H
#define	TRAINIC2D_H

#include "TrainStrategy.h"
#include "ICAAMModel.h"

namespace aam
{
    class TrainIC2D : public TrainStrategy
    {
    public:
        TrainIC2D();
        virtual ~TrainIC2D();

        virtual void train(std::vector<TrainModelInfo>& trainData);
        virtual void save(cv::FileStorage& storage);
        virtual algorithm::AAMAlgorithm getTrainerType();
        virtual void estimateAAM(const cv::Mat& img,
            const Vertices2DList& initialPoints,
            Vertices2DList& foundPoints, bool verbose = false);
        virtual void estimateAAM(const cv::Mat& img,
            const Point2D& centralPoint,
            Vertices2DList& foundPoints, bool verbose = false);

    protected:
        virtual void load(cv::FileStorage& storage);
        
    private:
        ICAAMModel model;
        Vertices2DList initShape;
        cv::Rect shapeRect;
    };
}

#endif	/* TRAINIC2D_H */
