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
 * File:   TrainBasic.cpp
 * Author: Иван Губочкин
 * 
 * Created on 9 Октябрь 2012 г., 15:52
 */

#include "aam/TrainConventional.h"
#include "aam/AAMFunctions2D.h"
#include "aam/vector_op.h"

namespace aam
{
    TrainConventional::TrainConventional(int channels)
    {
        this->colorChannels = channels;
    }

    TrainConventional::~TrainConventional()
    {
    }

    void TrainConventional::train(std::vector<TrainModelInfo>& trainData)
    {
        aam::ShapeData shapeData;
        aam::AppearanceData appearanceData;

        for (int scale = 0; scale < this->options.getScales(); scale++)
        {
            std::cout << "Processing samples at scale " <<
                    std::dec << scale <<
                    std::endl << std::endl;

            shapeData.triangles = this->options.getTriangles();
            aam::AAMFunctions2D::makeShapeModel(1,
                    this->options.getPCACutThreshold(),
                    trainData, shapeData);
            aam::AAMFunctions2D::makeAppearanceModel(trainData,
                    shapeData,
                    this->options.getPCACutThreshold(),
                    appearanceData);

            aam::ShapeAppearanceData shapeAppearance;
            aam::AAMFunctions2D::combineShapeAppearance(trainData,
                    shapeData, appearanceData,
                    this->options.getPCACutThreshold(),
                    shapeAppearance);

            aam::RealMatrix R;

            if (this->options.isMultithreading())
            {
                aam::AAMFunctions2D::makeSearchModel_mt(shapeAppearance,
                        shapeData, appearanceData, trainData, R);
            }
            else
            {
                aam::AAMFunctions2D::makeSearchModel(shapeAppearance,
                        shapeData, appearanceData, trainData, R);
            }

            AAMModelItem modelItem;

            modelItem.shapeData = shapeData;
            modelItem.appearanceData = appearanceData;
            modelItem.shapeAppearance = shapeAppearance;
            modelItem.R = R;

            this->modelData.addModel(modelItem);

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

    void TrainConventional::save(cv::FileStorage& storage)
    {
        storage << AAM_ALGORITHM_TAG << getTrainerType();
        storage << AAM_COLOR_CHANNELS_TAG << getColorChannels();
        this->modelData.save(storage);
    }

    algorithm::AAMAlgorithm TrainConventional::getTrainerType()
    {
        return algorithm::conventional;
    }

    void TrainConventional::load(cv::FileStorage& storage)
    {
        this->modelData.load(storage);

        if (this->modelData.getModelsCount() > 0)
        {
            this->initShape = 
                    this->modelData.getModel(0).shapeData.meanVertices;
            this->shapeRect = cv::boundingRect(
                    convertVector<float>(this->initShape));
        }
        else
        {
            this->initShape.clear();
        }
    }

    void TrainConventional::estimateAAM(const cv::Mat& img,
            const Vertices2DList& initialPoints,
            Vertices2DList& foundPoints, bool verbose)
    {
        aam::TForm tform;

        tform.offsetSX = 1;
        
        aam::Vertices2DList pos;
        aam::AAMFunctions2D::alignDataInverse(initialPoints,
                tform, pos);
        cv::Rect r = cv::boundingRect(convertVector<float>(
                initialPoints));

        tform.offsetV.x = cvRound(r.x + r.width * 0.5);
        tform.offsetV.y = cvRound(r.y + r.height * 0.5);

        aam::TForm resultTform;
        aam::RealMatrix b;

        aam::AAMFunctions2D::aplyModel(img, tform, this->modelData,
                this->options.getMaxIters(), 
                this->options.getDeviationFactor(), foundPoints,
                resultTform, b, verbose);
    }

    void TrainConventional::estimateAAM(const cv::Mat& img,
            const Point2D& centralPoint,
            Vertices2DList& foundPoints, bool verbose)
    {
        aam::TForm tform;

        tform.offsetSX = 1;

        aam::Vertices2DList pos;
        aam::AAMFunctions2D::alignDataInverse(this->initShape,
                tform, pos);

        tform.offsetV = centralPoint;

        aam::TForm resultTform;
        aam::RealMatrix b;

        aam::AAMFunctions2D::aplyModel(img, tform, this->modelData,
                this->options.getMaxIters(), 
                this->options.getDeviationFactor(), foundPoints,
                resultTform, b, verbose);
    }
}
