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
 * File:   AAMEstimator.cpp
 * Author: Иван Губочкин
 * 
 * Created on 7 Август 2012 г., 16:11
 */

#include <iterator>

#include "aam/AAMEstimator.h"
#include "aam/AAMFunctions2D.h"
#include "aam/vector_op.h"

namespace aam
{
    AAMEstimator::AAMEstimator()
    {
    }

    AAMEstimator::~AAMEstimator()
    {
    }

    void AAMEstimator::train(const std::vector<ModelPathType>& modelsList)
    {
        this->loader.clear();
        this->trainStrategy = TrainStrategy::create(
                this->options.getAAMAlgorithm());

        if (!this->trainStrategy.get())
        {
            throw InternalException();
        }

        this->loader.useGrayImages(this->options.isGrayscale());
        
        for (int i = 0; i < modelsList.size(); i++)
        {
            this->loader.load(modelsList[i].first, modelsList[i].second);
        }

        std::vector<aam::TrainModelInfo> trainData =
                this->loader.getModels();
        this->trainStrategy->setOptions(this->options);
        this->trainStrategy->train(trainData);
    }

    void AAMEstimator::setTrainOptions(const TrainOptions& op)
    {
        if (this->trainStrategy.get() &&
                this->trainStrategy->getTrainerType() !=
                op.getAAMAlgorithm())
        {
            throw InvalidArgumentException();
        }

        this->options = op;

        if (this->trainStrategy.get())
        {
            this->trainStrategy->setOptions(this->options);
        }
    }

    TrainOptions AAMEstimator::getTrainOptions()
    {
        return this->options;
    }

    void AAMEstimator::save(const std::string& fileName)
    {
        if (this->trainStrategy.get())
        {
            cv::FileStorage storage(fileName, cv::FileStorage::WRITE);
            if (!storage.isOpened())
            {
                throw FileNotFoundError();
            }
            
            this->trainStrategy->save(storage);
            storage.release();
        }
    }

    void AAMEstimator::load(const std::string& fileName)
    {
        this->trainStrategy = TrainStrategy::load(fileName);
        this->options.setAAMAlgorithm(this->trainStrategy->getTrainerType());
        this->trainStrategy->setOptions(this->options);
    }

    void AAMEstimator::estimateAAM(const cv::Mat& img,
            const Vertices2DList& initialPoints,
            Vertices2DList& foundPoints)
    {
        if (this->trainStrategy.get())
        {
            this->trainStrategy->estimateAAM(img, initialPoints,
                    foundPoints);
        }
        else
        {
            throw NotInitializedException();
        }
    }

    void AAMEstimator::estimateAAM(const cv::Mat& img,
            const Point2D& centralPoint,
            Vertices2DList& foundPoints,
            bool verbose)
    {
        if (this->trainStrategy.get())
        {
            this->trainStrategy->estimateAAM(img, centralPoint,
                    foundPoints, verbose);
        }
        else
        {
            throw NotInitializedException();
        }
    }
}
