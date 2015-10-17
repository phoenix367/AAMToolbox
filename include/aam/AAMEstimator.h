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
 * File:   AAMEstimator.h
 * Author: Иван Губочкин
 *
 * Created on 7 Август 2012 г., 16:11
 */

#ifndef AAMESTIMATOR_H
#define	AAMESTIMATOR_H

#include <utility>
#include <string>
#include <vector>

#include "TrainModelLoader.h"
#include "TrainOptions.h"
#include "TrainStrategy.h"

namespace aam
{
    typedef std::pair<std::string, std::string> ModelPathType;
    
    class AAMEstimator
    {
    public:
        AAMEstimator();
        virtual ~AAMEstimator();

        void train(const std::vector<ModelPathType>& modelsList);
        void setTrainOptions(const TrainOptions& op);
        TrainOptions getTrainOptions();

        void save(const std::string& fileName);
        void load(const std::string& fileName);

        void estimateAAM(const cv::Mat& img,
            const Vertices2DList& initialPoints,
            Vertices2DList& foundPoints,
            bool verbose = false);
        void estimateAAM(const cv::Mat& img,
            const Point2D& centralPoint,
            Vertices2DList& foundPoints,
            bool verbose = false);

    private:
        bool checkImage(const cv::Mat& img);
        
    private:
        TrainModelLoader loader;
        TrainOptions options;
        std::shared_ptr<TrainStrategy> trainStrategy;
    };
}

#endif	/* AAMESTIMATOR_H */
