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
 * File:   TrainStrategy.h
 * Author: Иван Губочкин
 *
 * Created on 5 Октябрь 2012 г., 17:33
 */

#ifndef TRAINSTRATEGY_H
#define	TRAINSTRATEGY_H

#include <memory>

#include "aam.h"
#include "TrainModelInfo.h"
#include "TrainOptions.h"

namespace aam
{
    class TrainStrategy
    {
    public:
        TrainStrategy();
        virtual ~TrainStrategy();

        virtual void train(std::vector<TrainModelInfo>& trainData) = 0;
        virtual void save(cv::FileStorage& storage) = 0;
        virtual algorithm::AAMAlgorithm getTrainerType() = 0;
        virtual void estimateAAM(const cv::Mat& img,
            const Vertices2DList& initialPoints,
            Vertices2DList& foundPoints, bool verbose = false) = 0;
        virtual void estimateAAM(const cv::Mat& img,
            const Point2D& centralPoint,
            Vertices2DList& foundPoints, bool verbose = false) = 0;
        int getColorChannels();
        
        static std::shared_ptr<TrainStrategy> load(
            const std::string& fileName);
        static std::shared_ptr<TrainStrategy> create(
            algorithm::AAMAlgorithm alg, int channels);

        void setOptions(const TrainOptions& newOptions);

    protected:
        virtual void load(cv::FileStorage& storage) = 0;

    protected:
        TrainOptions options;
        int colorChannels;

    protected:
        static const char *AAM_ALGORITHM_TAG;
        static const char *AAM_COLOR_CHANNELS_TAG;
    };
}

#endif	/* TRAINSTRATEGY_H */
