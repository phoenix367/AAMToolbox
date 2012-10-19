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
 * File:   TrainIC2D.cpp
 * Author: Иван Губочкин
 * 
 * Created on 5 Октябрь 2012 г., 17:39
 */

#include "aam/TrainIC2D.h"
#include "aam/vector_op.h"

namespace aam
{
    TrainIC2D::TrainIC2D()
    {
    }

    TrainIC2D::~TrainIC2D()
    {
    }

    void TrainIC2D::train(std::vector<TrainModelInfo>& trainData)
    {
        for (int scale = 0; scale < this->options.getScales(); scale++)
        {
            std::cout << "Processing samples at scale " <<
                    std::dec << scale <<
                    std::endl << std::endl;

            AppearanceDataIC modelData;

            modelData.triangles = this->options.getTriangles();
            AAMFunctions2D::trainModelIC(this->options.getPCACutThreshold(),
                    trainData, modelData);

            this->model.addModel(modelData);
            for (int i = 0; i < trainData.size(); i++)
            {
                cv::Mat srcImage, resizedImage;
                srcImage = trainData[i].getImage();
                cv::pyrDown(srcImage, resizedImage,
                        cv::Size(srcImage.cols / 2, srcImage.rows / 2));

                trainData[i].setImage(resizedImage, false);

                Vertices2DList vertices = trainData[i].getVertices();
                vertices /= Point2D(2, 2);
                trainData[i].setVertices(vertices);
            }
        }
    }

    void TrainIC2D::save(cv::FileStorage& storage)
    {
        storage << AAM_ALGORITHM_TAG << getTrainerType();
        this->model.save(storage);
    }

    algorithm::AAMAlgorithm TrainIC2D::getTrainerType()
    {
        return algorithm::inverseComposition;
    }

    void TrainIC2D::load(cv::FileStorage& storage)
    {
        this->model.load(storage);

        if (this->model.getModelsCount() > 0)
        {
            this->initShape = this->model.getModel(0).s0;
            this->shapeRect = cv::boundingRect(
                    convertVector<float>(this->initShape));
        }
        else
        {
            this->initShape.clear();
        }
    }

    void TrainIC2D::estimateAAM(const cv::Mat& img,
            const Vertices2DList& initialPoints,
            Vertices2DList& foundPoints, bool verbose)
    {
        aam::AAMFunctions2D::aplyModelIC(img,
                initialPoints, this->model,
                this->options.getMaxIters(),
                this->options.getDeviationFactor(),
                foundPoints, verbose);
    }

    void TrainIC2D::estimateAAM(const cv::Mat& img,
            const Point2D& centralPoint,
            Vertices2DList& foundPoints, bool verbose)
    {
        Point2D increment(centralPoint.x - this->shapeRect.width / 2,
                centralPoint.y - this->shapeRect.height / 2);
        Vertices2DList points(this->initShape);

        points += increment;
        estimateAAM(img, points, foundPoints, verbose);
    }
}
