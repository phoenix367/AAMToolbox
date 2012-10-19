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
 * File:   AAMFunctions2D.h
 * Author: Иван Губочкин
 *
 * Created on 9 Август 2012 г., 15:53
 */

#ifndef AAMFUNCTIONS2D_H
#define	AAMFUNCTIONS2D_H

#include <dlib/matrix.h>
#include <dlib/optimization.h>

#include "aam.h"
#include "ShapeData.h"
#include "TrainModelInfo.h"
#include "AppearanceData.h"
#include "ShapeAppearanceData.h"
#include "AAMModel.h"
#include "AppearanceDataIC.h"
#include "PiecewiseWarp.h"
#include "ICAAMModel.h"

namespace aam
{
    struct XYDerivation
    {
        RealMatrix xDerivation;
        RealMatrix yDerivation;
    };
    
    class AAMFunctions2D
    {
    public:
        static const RealType DEFAULT_PCA_CUT_THRESOLD;
        
    public:
        static void alignData(const Vertices2DList& aVertices,
            const Vertices2DList& bVertices,
            Vertices2DList& result, TForm& tform);
        static void alignDataInverse(const Vertices2DList& vertices,
            const TForm& tform, Vertices2DList& result);
        static void makeShapeModel(
            int textureSize,
            RealType pcaCutThreshold,
            std::vector<TrainModelInfo>& trainData,
            ShapeData& shapeData);
        static void makeAppearanceModel(
            const std::vector<TrainModelInfo>& trainData,
            const ShapeData& shapeData,
            RealType pcaCutThreshold,
            AppearanceData& appearanceData);
        static void appearance2Vector(const cv::Mat& img,
            const Vertices2DList& trainVertices,
            const Vertices2DList& baseVertices,
            const cv::Mat1b& objectPixels,
            int pixelsCount,
            const std::vector<cv::Vec3i>& triangles,
            cv::Mat& J, RealMatrix& grayVector);
        static void computeWeights(
            const std::vector<TrainModelInfo>& trainData,
            const ShapeData& shapeData,
            const AppearanceData& appearanceData,
            RealMatrix& w);
        static void vector2Appearance(const cv::Mat& grayVector,
            const cv::Mat1b& objectPixels, const cv::Size& textureSize,
            cv::Mat& outputTexture);
        static void combineShapeAppearance(
            const std::vector<TrainModelInfo>& trainData,
            const ShapeData& shapeData,
            const AppearanceData& appearanceData,
            RealType pcaCutThreshold,
            ShapeAppearanceData& shapeAppearance);
        static void makeSearchModel(
            const ShapeAppearanceData& shapeAppearance,
            const ShapeData& shapeData,
            const AppearanceData& appearanceData,
            const std::vector<TrainModelInfo>& trainData,
            RealMatrix& R);
        static void makeSearchModel_mt(
            const ShapeAppearanceData& shapeAppearance,
            const ShapeData& shapeData,
            const AppearanceData& appearanceData,
            const std::vector<TrainModelInfo>& trainData,
            RealMatrix& R);
        static void aplyModel(const cv::Mat& img, const TForm& tform,
            const AAMModel& model, int maxIters, RealType normFactor,
            Vertices2DList& foundPoints, TForm& outTform,
            RealMatrix& bOut, bool verbose);

        static void appearance2Vector(const cv::Mat& img,
            const Vertices2DList& trainVertices,
            const cv::Mat1b& objectPixels,
            int pixelsCount,
            const std::vector<cv::Vec3i>& triangles,
            const PiecewiseWarp::WarpInfo& warpInfo,
            cv::Mat& J, RealMatrix& grayVector);
        static void trainModelIC(
            RealType pcaCutThreshold,
            std::vector<TrainModelInfo>& trainData,
            AppearanceDataIC& model);
        static void aplyModelIC(const cv::Mat& img,
            const Vertices2DList& initShape,
            const ICAAMModel& model,
            int maxIters,
            RealType deviationFactor,
            Vertices2DList& foundPoints,
            bool verbose);
        static void toAffine(const AppearanceDataIC& model,
            const RealMatrix& q, RealMatrix& M);
        static void warpComposition(const AppearanceDataIC& model,
            const Vertices2DList& curShape, const Vertices2DList& inc,
            Vertices2DList& compWarp);
        static void computeJacobian(const AppearanceDataIC& model,
            XYDerivation& dW_dp, XYDerivation& dN_dq);
        static void makeShapeModelIC(
            int textureSize,
            RealType pcaCutThreshold,
            std::vector<TrainModelInfo>& trainData,
            AppearanceDataIC& model);
        static void makeAppearanceModelIC(
            RealType pcaCutThreshold,
            std::vector<TrainModelInfo>& trainData,
            AppearanceDataIC& model);
        static void computeSDImage(const AppearanceDataIC& model,
            const XYDerivation& dA0, const XYDerivation& dW_dp,
            const XYDerivation& dN_dq, RealMatrix& SD);
        static void computeGradient(const AppearanceDataIC& model,
            const RealMatrix& A, XYDerivation& dA);

        static void makeAAMHelper(
            std::vector<TrainModelInfo>::const_iterator beginSeq,
            std::vector<TrainModelInfo>::const_iterator endSeq,
            int baseIndex,
            const ShapeAppearanceData& shapeAppearance,
            const ShapeData& shapeData,
            const AppearanceData& appearanceData,
            RealMatrix& drdp);
        static void normalizeAppearance(cv::Mat& g);
        static void normalizeAppearanceTrain(cv::Mat& g);
        
    private:
        static void rotationAngle(const Vertices2DList& list,
            std::vector<RealType>& angle);
        static void realAndModel(const TrainModelInfo& trainModel,
            const Vertices2DList& pos, const AppearanceData& appearanceData,
            const ShapeData& shapeData,
            const ShapeAppearanceData& shapeAppearance,
            RealMatrix& gOffset, RealMatrix& g);
    };
}

#endif	/* AAMFUNCTIONS2D_H */
