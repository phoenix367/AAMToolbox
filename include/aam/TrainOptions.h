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
 * File:   TrainOptions.h
 * Author: Иван Губочкин
 *
 * Created on 9 Август 2012 г., 12:55
 */

#ifndef TRAINOPTIONS_H
#define	TRAINOPTIONS_H

#include "Exceptions.h"
#include "AAMFunctions2D.h"

namespace aam
{
    class TrainOptions
    {
    public:
        TrainOptions()
        : nScales(4)
        , bMultithreading(true)
        , pcaCutThreshold(AAMFunctions2D::DEFAULT_PCA_CUT_THRESOLD)
        , bGray(true)
        , aamAlgorithm(algorithm::invalid)
        , maxIters(15)
        , deviationFactor(3)
        {
            
        }

        void setScales(int value)
        {
            if (value <= 0)
            {

            }

            this->nScales = value;
        }

        int getScales() const
        {
            return this->nScales;
        }

        bool isMultithreading() const
        {
            return this->bMultithreading;
        }

        void setMultithreading(bool value)
        {
            this->bMultithreading = value;
        }

        void setPCACutThreshold(RealType value)
        {
            if (value < 0 || value > 1)
            {
                throw InvalidArgumentException();
            }
            
            this->pcaCutThreshold = value;
        }

        RealType getPCACutThreshold() const
        {
            return this->pcaCutThreshold;
        }

        bool isGrayscale() const
        {
            return this->bGray;
        }

        void setGrayScale(bool value)
        {
            this->bGray = value;
        }

        void setAAMAlgorithm(algorithm::AAMAlgorithm alg)
        {
            this->aamAlgorithm = alg;
        }

        algorithm::AAMAlgorithm getAAMAlgorithm() const
        {
            return this->aamAlgorithm;
        }

        void setTriangles(const std::vector<cv::Vec3i>& newTri)
        {
            this->triangles = newTri;
        }

        std::vector<cv::Vec3i> getTriangles() const
        {
            return this->triangles;
        }

        void setMaxIters(int value)
        {
            if (value <= 0)
            {
                throw InvalidArgumentException();
            }

            this->maxIters = value;
        }

        int getMaxIters() const
        {
            return this->maxIters;
        }

        void setDeviationFactor(RealType value)
        {
            if (value <= 0)
            {
                throw InvalidArgumentException();
            }

            this->deviationFactor = value;
        }

        RealType getDeviationFactor()
        {
            return this->deviationFactor;
        }

    private:
        int nScales;
        bool bMultithreading;
        RealType pcaCutThreshold;
        bool bGray;
        algorithm::AAMAlgorithm aamAlgorithm;
        std::vector<cv::Vec3i> triangles;
        int maxIters;
        RealType deviationFactor;
    };
}

#endif	/* TRAINOPTIONS_H */
