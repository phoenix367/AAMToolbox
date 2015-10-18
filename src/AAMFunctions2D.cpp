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
 * File:   AAMFunctions2D.cpp
 * Author: Иван Губочкин
 * 
 * Created on 9 Август 2012 г., 15:53
 */

#include <iostream>
#include <vector>
#include <iterator>
#include <opencv2/highgui/highgui.hpp>
#include <algorithm>

#include "dlib/optimization.h"
#include <boost/thread/thread.hpp>
#include <iomanip>
#include <thread>

#include "aam/AAMFunctions2D.h"
#include "aam/PiecewiseWarp.h"
#include "aam/vector_op.h"
#include "aam/CommonFunctions.h"
#include "aam/Exceptions.h"
#include "aam/OptimHelper2D.h"

#define MODEL_OFFSETS                   6
#define POSE_OFFSETS                    4
#define POSE_STD                        2

namespace aam
{
    const RealType AAMFunctions2D::DEFAULT_PCA_CUT_THRESOLD = 0.95;
    
    void AAMFunctions2D::alignData(const Vertices2DList& aVertices,
            const Vertices2DList& bVertices, Vertices2DList& result,
            TForm& tform)
    {
        Point2D offsetvA, offsetvB;
        Vertices2DList av(aVertices), bv(bVertices);

        offsetvA = -mean(aVertices);
        offsetvB = -mean(bVertices);

        av += offsetvA;
        bv += offsetvB;

        RealType dA = mean(dist(av));
        RealType dB = mean(dist(bv));
        RealType offsetS = dB / dA;

        result = av * offsetS;

        std::vector<RealType> rotA, rotB;
        rotationAngle(av, rotA);
        rotationAngle(bv, rotB);

        RealType offsetR = -mean(rotA - rotB);
        std::vector<RealType> rot = rotA + offsetR;

        std::vector<RealType> d = dist(result);
        for (int i = 0; i < result.size(); i++)
        {
            result[i].x = d[i] * cos(rot[i]);
            result[i].y = d[i] * sin(rot[i]);
        }

        tform.offsetV = offsetvA;
        tform.offsetSX = offsetS * cos(offsetR);
        tform.offsetSY = offsetS * sin(offsetR);
        tform.offsetS = offsetS;
        tform.offsetR = offsetR;
    }

    void AAMFunctions2D::rotationAngle(const Vertices2DList& list,
            std::vector<RealType>& angle)
    {
        angle.resize(list.size());

        for (int i = 0; i < list.size(); i++)
        {
            angle[i] = atan2(list[i].y, list[i].x);
        }
    }

    void AAMFunctions2D::alignDataInverse(const Vertices2DList& vertices,
            const TForm& tform, Vertices2DList& result)
    {
        RealType offsetS = sqrt(tform.offsetSX * tform.offsetSX +
            tform.offsetSY * tform.offsetSY);
        RealType offsetR = atan2(tform.offsetSY, tform.offsetSX);

        std::vector<RealType> rot;
        rotationAngle(vertices, rot);

        rot -= offsetR;
        std::vector<RealType> d = dist(vertices);

        result.resize(vertices.size());
        for (int i = 0; i < result.size(); i++)
        {
            result[i].x = d[i] * cos(rot[i]) / offsetS - tform.offsetV.x;
            result[i].y = d[i] * sin(rot[i]) / offsetS - tform.offsetV.y;
        }
    }

    void AAMFunctions2D::makeShapeModel(
        int textureSize,
        RealType pcaCutThreshold,
        std::vector<TrainModelInfo>& trainData,
        ShapeData& shapeData)
    {
        int niter = 2;

        if (trainData.empty())
        {
            return;
        }

        Vertices2DList meanVertices = trainData[0].getVertices();

        for (int k = 0; k < niter; k++)
        {
            Vertices2DList tmp(meanVertices.size());
            Point2D offsetv;
            RealType offsetSX = 0.0, offsetSY = 0.0;
            
            for (int s = 0; s < trainData.size(); s++)
            {
                Vertices2DList cVertices;
                TForm tform;

                alignData(trainData[s].getVertices(), meanVertices,
                        cVertices, tform);

                tmp += cVertices;
                offsetv += tform.offsetV;
                offsetSX += tform.offsetSX;
                offsetSY += tform.offsetSY;
            }

            TForm meanTform;

            meanTform.offsetV.x = offsetv.x / trainData.size();
            meanTform.offsetV.y = offsetv.y / trainData.size();
            meanTform.offsetSX = offsetSX / trainData.size();
            meanTform.offsetSY = offsetSY / trainData.size();

            alignDataInverse(tmp / trainData.size(), meanTform,
                    meanVertices);
        }

        RealMatrix x = RealMatrix::zeros(2 * meanVertices.size(),
                trainData.size());
        for (int i = 0; i < trainData.size(); i++)
        {
            alignData(trainData[i].getVertices(), meanVertices,
                        trainData[i].getCVertices(),
                        trainData[i].getTForm());

            cv::Mat cv(trainData[i].getCVertices());
            
            std::vector<cv::Mat> channels;
            cv::split(cv, channels);

            cv::Mat tmp = x(cv::Range(0, meanVertices.size()),
                    cv::Range(i, i + 1));
            channels[0].copyTo(tmp);
            tmp = x(cv::Range(meanVertices.size(), 2 * meanVertices.size()),
                    cv::Range(i, i + 1));
            channels[1].copyTo(tmp);
        }

        RealMatrix xMeans, eigValues, eigVectors;
        CommonFunctions::PCA(x, xMeans, eigVectors, eigValues);
        CommonFunctions::removeEigNoise(eigVectors, eigValues, 
                pcaCutThreshold);
        
        RealVector r(trainData.size()), s(trainData.size());
        for (int i = 0; i < trainData.size(); i++)
        {
            r[i] = trainData[i].getTForm().offsetR;
            s[i] = trainData[i].getTForm().offsetS;
        }

        shapeData.rVariance = var(r);
        shapeData.sVariance = var(s);
        shapeData.meanVertices = meanVertices;
        shapeData.x = x;
        shapeData.xMean = mat2PointVector<RealType>(xMeans);
        shapeData.eigValues = eigValues;
        shapeData.eigVectors = eigVectors;
        shapeData.lines = trainData[0].getLines();

        if (shapeData.triangles.empty())
        {
            CommonFunctions::delaunay(shapeData.xMean, shapeData.triangles);
        }

        Point2D minShapePt = minCoords(shapeData.xMean);
        Point2D maxShapePt = maxCoords(shapeData.xMean);
        RealType maxX = std::max(-minShapePt.x, maxShapePt.x);
        RealType maxY = std::max(-minShapePt.y, maxShapePt.y);

        int ts = ceil(std::max(maxX, maxY) * 2 * textureSize);
        shapeData.textureSize.width = ts;
        shapeData.textureSize.height = ts;
    }

    void AAMFunctions2D::makeAppearanceModel(
            const std::vector<TrainModelInfo>& trainData,
            const ShapeData& shapeData,
            RealType pcaCutThreshold,
            AppearanceData& appearanceData)
    {
        if (trainData.empty())
        {
            return;
        }

        Vertices2DList basePoints(shapeData.xMean);

        // Normalize contour points to range 0..1
        Point2D minPoint = minCoords(basePoints);
        basePoints -= minPoint;
        Point2D maxPoint = maxCoords(basePoints);
        basePoints /= maxPoint;

        for (int i = 0; i < basePoints.size(); i++)
        {
            basePoints[i].x *= shapeData.textureSize.width - 1;
            basePoints[i].y *= shapeData.textureSize.height - 1;
        }

        cv::Mat1b objectPixels;

        CommonFunctions::drawObject(shapeData.textureSize, shapeData.lines,
                basePoints, objectPixels);

        int nPixels = cv::countNonZero(objectPixels);
        RealMatrix grayVector = RealMatrix::zeros(nPixels *
                trainData[0].getImage().channels(),
                trainData.size());

        for (int i = 0; i < trainData.size(); i++)
        {
            cv::Mat J;
            RealMatrix g;
            
            appearance2Vector(trainData[i].getImage(),
                    trainData[i].getVertices(), basePoints,
                    objectPixels, nPixels, shapeData.triangles,
                    J, g);
            cv::Mat tmp  = grayVector.col(i);
            g.copyTo(tmp);
        }

        normalizeAppearance(grayVector);
        
        RealMatrix gMeans, eigValues, eigVectors;
        CommonFunctions::appPCA(grayVector, gMeans, eigVectors, eigValues);
        CommonFunctions::removeEigNoise(eigVectors, eigValues, 
                pcaCutThreshold);

        appearanceData.basePoints = basePoints;
        appearanceData.grayVector = grayVector;
        appearanceData.objectPixels = objectPixels;
        appearanceData.nPixels = nPixels;
        appearanceData.eigenValues = eigValues;
        appearanceData.eigenVectors = eigVectors;
        appearanceData.grayMean = gMeans;
    }

    void AAMFunctions2D::appearance2Vector(const cv::Mat& img,
            const Vertices2DList& trainVertices, 
            const cv::Mat1b& objectPixels, 
            int pixelsCount, 
            const std::vector<cv::Vec3i>& triangles, 
            const PiecewiseWarp::WarpInfo& warpInfo, 
            cv::Mat& J, RealMatrix& grayVector)
    {
        PiecewiseWarp::warpTriangle(img, J, trainVertices,
                triangles, cv::Size(objectPixels.cols,
                objectPixels.rows), warpInfo);

        std::vector<cv::Mat> rgbChannels;
        cv::split(J, rgbChannels);

        grayVector = RealMatrix(pixelsCount * J.channels(), 1);

        int cp = 0;

        for (int ch = 0; ch < rgbChannels.size(); ch++)
        {
            for (int i = 0; i < objectPixels.rows; i++)
            {
                for (int j = 0; j < objectPixels.cols; j++)
                {
                    if (objectPixels(i, j))
                    {
                        grayVector(cp, 0) =
                                rgbChannels[ch].at<RealType>(i, j);
                        cp++;
                    }
                }
            }
        }
    }
    
    void AAMFunctions2D::appearance2Vector(const cv::Mat& img,
            const Vertices2DList& trainVertices,
            const Vertices2DList& baseVertices,
            const cv::Mat1b& objectPixels,
            int pixelsCount,
            const std::vector<cv::Vec3i>& triangles,
            cv::Mat& J, RealMatrix& grayVector)
    {
        PiecewiseWarp::warpTriangle(img, J, trainVertices,
                baseVertices, triangles, cv::Size(objectPixels.cols,
                objectPixels.rows));

        std::vector<cv::Mat> rgbChannels;
        cv::split(J, rgbChannels);

        grayVector = RealMatrix(pixelsCount * J.channels(), 1);

        int cp = 0;

        for (int ch = 0; ch < rgbChannels.size(); ch++)
        {
            for (int i = 0; i < objectPixels.rows; i++)
            {
                for (int j = 0; j < objectPixels.cols; j++)
                {
                    if (objectPixels(i, j))
                    {
                        grayVector(cp, 0) =
                                rgbChannels[ch].at<RealType>(i, j);
                        cp++;
                    }
                }
            }
        }
    }

    void AAMFunctions2D::normalizeAppearance(cv::Mat& g)
    {
        cv::Mat m, s;
        cv::meanStdDev(g, m, s);

        g = (g - m) / s;
    }

    void AAMFunctions2D::normalizeAppearanceTrain(cv::Mat& g)
    {
        cv::Mat m, s;

        for (int i = 0; i < g.cols; i++)
        {
            cv::meanStdDev(g.col(i), m, s);
            g.col(i) = (g.col(i) - m) / s;
        }
    }

    void AAMFunctions2D::computeWeights(
        const std::vector<TrainModelInfo>& trainData,
        const ShapeData& shapeData,
        const AppearanceData& appearanceData,
        RealMatrix& w)
    {
        cv::Mat_<RealType> changes = cv::Mat_<RealType>::zeros(
                trainData.size(), shapeData.eigVectors.cols);
        int nPixels = cv::countNonZero(appearanceData.objectPixels);

        for (int i = 0; i < trainData.size(); i++)
        {
            Vertices2DList pos;
            TForm tform;

            alignData(trainData[i].getVertices(), shapeData.meanVertices,
                    pos, tform);

            RealMatrix x = pointVector2Mat(pos - shapeData.xMean);
            RealMatrix b = shapeData.eigVectors.t() * x;
            Vertices2DList posNormal = shapeData.xMean +
                    mat2PointVector<RealType>(shapeData.eigVectors * b);

            alignDataInverse(posNormal, tform, posNormal);
            cv::Mat J;
            RealMatrix gNormal;
            appearance2Vector(trainData[i].getImage(), posNormal,
                    appearanceData.basePoints, appearanceData.objectPixels,
                    nPixels, shapeData.triangles, J, gNormal);
            normalizeAppearance(gNormal);

            RealType changeValues[2] = { -0.5, 0.5 };
            for (int j = 0; j < shapeData.eigVectors.cols; j++)
            {
                for (int k = 0; k < 2; k++)
                {
                    RealMatrix bOffset = b.clone();
                    bOffset(j) += changeValues[k];

                    Vertices2DList xOffset = shapeData.xMean +
                        mat2PointVector<RealType>(
                            shapeData.eigVectors * bOffset);

                    Vertices2DList posOffset;
                    alignDataInverse(xOffset, tform, posOffset);

                    cv::Mat Joffset;
                    RealMatrix gOffset;
                    appearance2Vector(trainData[i].getImage(),
                            posOffset, appearanceData.basePoints,
                            appearanceData.objectPixels, nPixels,
                            shapeData.triangles, Joffset, gOffset);
                    normalizeAppearance(gOffset);

                    RealType n = cv::norm(gOffset - gNormal,
                            cv::NORM_L2);
                    changes(i, j) += sqrt(n * n / gNormal.rows);
                }
            }
        }

        w = cv::Mat::zeros(shapeData.eigVectors.cols,
                shapeData.eigVectors.cols, OpenCVRealType::type);
        for (int i = 0; i < shapeData.eigVectors.cols; i++)
        {
            w.at<RealType>(i, i) = cv::mean(changes.col(i))[0];
        }
    }

    void AAMFunctions2D::vector2Appearance(const cv::Mat& grayVector,
            const cv::Mat1b& objectPixels, const cv::Size& textureSize,
            cv::Mat& outputTexture)
    {
        assert(grayVector.channels() == 1 && grayVector.cols == 1);
        assert(objectPixels.rows == textureSize.height &&
                objectPixels.cols == textureSize.width);

        int nPixels = cv::countNonZero(objectPixels);
        assert(grayVector.rows % nPixels == 0);
        
        int nChannels = grayVector.rows / nPixels;
        int elemSize = grayVector.elemSize();
        outputTexture = cv::Mat::zeros(textureSize.height, textureSize.width,
                CV_MAKETYPE(grayVector.depth(), nChannels));

        int pos = 0;
        for (int i = 0; i < outputTexture.rows; i++)
        {
            for (int j = 0; j < outputTexture.cols; j++)
            {
                if (objectPixels(i, j))
                {
                    uchar *p = outputTexture.ptr(i, j);
                    for (int ch = 0; ch < nChannels; ch++)
                    {
                        memcpy(p + elemSize * ch, grayVector.ptr(pos +
                                nPixels * ch, 0),
                                elemSize);
                    }

                    pos++;
                }
            }
        }
    }

    void AAMFunctions2D::combineShapeAppearance(
        const std::vector<TrainModelInfo>& trainData,
        const ShapeData& shapeData,
        const AppearanceData& appearanceData,
        RealType pcaCutThreshold,
        ShapeAppearanceData& shapeAppearance)
    {
        RealMatrix w;
        computeWeights(trainData, shapeData, appearanceData, w);

        RealMatrix xMeans = pointVector2Mat(shapeData.xMean);
        RealMatrix b = RealMatrix::zeros(shapeData.eigVectors.cols +
                appearanceData.eigenVectors.cols, trainData.size());

        for (int i = 0; i < trainData.size(); i++)
        {
            RealMatrix b1 = w * shapeData.eigVectors.t() *
                    (shapeData.x.col(i) - xMeans);
            RealMatrix b2 = appearanceData.eigenVectors.t() *
                    (appearanceData.grayVector.col(i) -
                        appearanceData.grayMean);

            RealMatrix tmp;
            cv::vconcat(b1, b2, tmp);

            RealMatrix c = b.col(i);
            tmp.copyTo(c);
        }

        RealMatrix bMeans, eigValues, eigVectors;
        CommonFunctions::PCA(b, bMeans, eigVectors, eigValues);
        CommonFunctions::removeEigNoise(eigVectors, eigValues,
                pcaCutThreshold);

        shapeAppearance.eigValues = eigValues;
        shapeAppearance.eigVectors = eigVectors;
        shapeAppearance.bMeans = bMeans;
        shapeAppearance.b = b;
        shapeAppearance.w = w;
    }

    void AAMFunctions2D::makeSearchModel(
        const ShapeAppearanceData& shapeAppearance,
        const ShapeData& shapeData,
        const AppearanceData& appearanceData,
        const std::vector<TrainModelInfo>& trainData,
        RealMatrix& R)
    {
        RealMatrix drdp;
        makeAAMHelper(trainData.begin(), trainData.end(), 0,
                shapeAppearance, shapeData, appearanceData,
                drdp);

        drdp /= MODEL_OFFSETS * trainData.size();
        cv::invert(drdp, R, cv::DECOMP_SVD);
        R = R.t();
    }

    void AAMFunctions2D::makeSearchModel_mt(
        const ShapeAppearanceData& shapeAppearance,
        const ShapeData& shapeData,
        const AppearanceData& appearanceData,
        const std::vector<TrainModelInfo>& trainData,
        RealMatrix& R)
    {
        if (trainData.empty())
        {
            R = RealMatrix();
            return;
        }

        int threadsCount = std::min(trainData.size(),
                std::thread::hardware_concurrency());

        boost::thread_group threadGroup;
        std::vector<RealMatrix> drdps(threadsCount);
        int step = trainData.size() / threadsCount;
        std::vector<TrainModelInfo>::const_iterator p =
                trainData.begin();
        
        for (int i = 0; i < threadsCount - 1; i++, p += step)
        {
            threadGroup.create_thread(boost::bind(makeAAMHelper,
                    p, p + step, p - trainData.begin(),
                    shapeAppearance, shapeData,
                    appearanceData, boost::ref(drdps[i])));
        }

        threadGroup.create_thread(boost::bind(makeAAMHelper,
                p, trainData.end(), p - trainData.begin(),
                shapeAppearance, shapeData,
                appearanceData, boost::ref(drdps[threadsCount - 1])));
        
        threadGroup.join_all();

        RealMatrix drdpt = RealMatrix::zeros(
                shapeAppearance.eigVectors.cols + POSE_OFFSETS,
                appearanceData.grayMean.rows);
        for (int i = 0; i < threadsCount; i++)
        {
            drdpt = drdpt + drdps[i];
        }

        drdpt /= MODEL_OFFSETS * trainData.size();
        cv::invert(drdpt, R, cv::DECOMP_SVD);
        R = R.t();
    }
    
    void AAMFunctions2D::aplyModel(const cv::Mat& img, const TForm& tformLarge,
            const AAMModel& model, int maxIters, RealType deviationFactor,
            Vertices2DList& foundPoints, TForm& outTform,
            RealMatrix& bOut, bool verbose)
    {
        int scale = 0;
        RealType scaling = pow(2, -scale);
        TForm tform = tformLarge;

        tform.offsetV *= scaling;

        AAMModelItem modelItem = model.getModel(scale);
        ShapeAppearanceData shapeApperance = modelItem.shapeAppearance;
        ShapeData shapeData = modelItem.shapeData;
        AppearanceData appearanceData = modelItem.appearanceData;

        cv::Mat J;
        RealMatrix g;
        RealMatrix b = shapeApperance.bMeans.clone();
        RealMatrix bShape = shapeApperance.w.inv() *
                b.rowRange(0, shapeApperance.w.rows);

        RealMatrix x = pointVector2Mat(shapeData.xMean) +
                shapeData.eigVectors * bShape;
        Vertices2DList pos = mat2PointVector<RealType>(x);
        alignDataInverse(pos, tform, pos);

        RealMatrix p, oldc;
        RealType E = 0.0;
        RealType Eold = std::numeric_limits<RealType>::infinity();
        TForm tformOld = tform;
        RealMatrix R, xMean, invW;

        RealType w = 1; // Adaptation step
        for (scale = model.getModelsCount() - 1; scale >= 0; scale--)
        {
            if (verbose)
            {
                std::cout << "Start aply model at scale: " << scale <<
                        std::endl;
            }

            modelItem = model.getModel(scale);
            shapeApperance = modelItem.shapeAppearance;
            shapeData = modelItem.shapeData;
            appearanceData = modelItem.appearanceData;
            R = modelItem.R;
            xMean = pointVector2Mat(shapeData.xMean);
            invW = shapeApperance.w.inv();
            
            RealMatrix shaEigVSqrt;
            cv::sqrt(shapeApperance.eigValues, shaEigVSqrt);

            scaling = pow(2, -scale);
            cv::Mat imTest;
            cv::resize(img, imTest,
                    cv::Size(img.cols * scaling, img.rows * scaling));

            for (int i = 0; i < pos.size(); i++)
            {
                pos[i].x *= scaling;
                pos[i].y *= scaling;
            }

            Vertices2DList posAlign;
            alignData(pos, shapeData.meanVertices, posAlign, tform);

            appearance2Vector(imTest, pos, 
                    appearanceData.objectPixels,
                    appearanceData.nPixels,
                    shapeData.triangles,
                    modelItem.warpInfo, J, g);
            normalizeAppearance(g);

            bShape = shapeApperance.w * shapeData.eigVectors.t() *
                    pointVector2Mat(posAlign - shapeData.xMean);

            RealMatrix bAppearance = appearanceData.eigenVectors.t() *
                    (g - appearanceData.grayMean);
            cv::vconcat(bShape, bAppearance, b);

            RealMatrix cin = shapeApperance.eigVectors.t() *
                    (b - shapeApperance.bMeans);

            RealMatrix x = pointVector2Mat(posAlign);
            RealMatrix x2 = x.clone();

            RealMatrix maxc = shaEigVSqrt.clone();
            maxc *= deviationFactor;

            for (int i = 0; i < maxc.rows; i++)
            {
                if (cin(i, 0) < -maxc(i, 0))
                {
                    cin(i, 0) = -maxc(i, 0);
                }
                else if (cin(i, 0) > maxc(i, 0))
                {
                    cin(i, 0) = maxc(i, 0);
                }
            }
            
            dlib::matrix<RealType, 0, 1> dlibC;
            CommonFunctions::opencvMat2Dlib(cin, dlibC);

            dlib::find_min_using_approximate_derivatives(
                dlib::bfgs_search_strategy(),
                dlib::objective_delta_stop_strategy(1e-3f),
                OptimHelper2D(x2, shapeData, shapeApperance),
                dlibC, -1);

            CommonFunctions::dlibMat2OpenCV(dlibC, p);

            oldc = p;
            tformOld = tform;
            Eold = std::numeric_limits<RealType>::infinity();

            Vertices2DList oldPos(pos);

            b = shapeApperance.bMeans + shapeApperance.eigVectors * p;
            bShape = invW * b.rowRange(0, shapeApperance.w.rows);
            x = xMean + shapeData.eigVectors * bShape;

            alignDataInverse(mat2PointVector<RealType>(x),
                tform, pos);
            
            for (int i = 0; i < maxIters; i++)
            {
                appearance2Vector(imTest, pos,
                        appearanceData.objectPixels,
                        appearanceData.nPixels,
                        shapeData.triangles,
                        modelItem.warpInfo, J, g);
                normalizeAppearance(g);
                
                RealMatrix xd = x - xMean;
                RealMatrix gd = g - appearanceData.grayMean;

                if (verbose)
                {
                    cv::Mat showedImg = imTest.clone();
                    for (int i = 0; i < pos.size(); i++)
                    {
                        cv::circle(showedImg, pos[i], 3, CV_RGB(0, 0, 0));
                    }
                    cv::imshow("Image", showedImg);

                    vector2Appearance(gd, appearanceData.objectPixels,
                            shapeData.textureSize, J);
                    cv::normalize(J, J, 1, 0, cv::NORM_MINMAX);
                    cv::imshow("Error texture", cv::abs(J));
                    cv::waitKey(300);
                }

                bShape = shapeApperance.w * shapeData.eigVectors.t() * xd;
                bAppearance = appearanceData.eigenVectors.t() * gd;
                cv::vconcat(bShape, bAppearance, b);

                RealMatrix bd = b - shapeApperance.bMeans;
                RealMatrix c2 = shapeApperance.eigVectors.t() * bd;

                b = shapeApperance.bMeans + shapeApperance.eigVectors * c2;
                bAppearance = b.rowRange(shapeApperance.w.rows, b.rows);
                RealMatrix gModel = appearanceData.grayMean +
                        appearanceData.eigenVectors * bAppearance;
                RealMatrix modelDiff = g - gModel;

                E = cv::norm(modelDiff);

                if (E > Eold)
                {
                    w *= 0.9;
                    p = oldc;
                    tform = tformOld;
                }
                else
                {
                    w *= 1.1;
                    Eold = E;
                    oldc = p;
                    tformOld = tform;
                }

                RealMatrix cdiff = R * modelDiff;
                RealMatrix subC = cdiff.rowRange(0, cdiff.rows - 4);

                RealMatrix tmp;
                cv::multiply(subC, shaEigVSqrt, tmp);

                p+= tmp * w;

                tform.offsetV.x += cdiff(cdiff.rows - 4, 0) * w;
                tform.offsetV.y += cdiff(cdiff.rows - 3, 0) * w;
                tform.offsetSX += cdiff(cdiff.rows - 2, 0) * w;
                tform.offsetSY += cdiff(cdiff.rows - 1, 0) * w;

                for (int j = 0; j < p.rows; j++)
                {
                    p(j, 0) = std::max(std::min(p(j, 0), maxc(j, 0)),
                            -maxc(j, 0));
                }

                b = shapeApperance.bMeans + shapeApperance.eigVectors * p;
                bShape = invW * b.rowRange(0, shapeApperance.w.rows);
                x = xMean + shapeData.eigVectors * bShape;

                alignDataInverse(mat2PointVector<RealType>(x),
                    tform, pos);

                RealType shiftNorm = cv::norm(
                        pointVector2Mat(pos - oldPos));

                if (verbose)
                {
                    std::cout << "Shift in pixels at iteration " << i <<
                            " : " << shiftNorm <<
                            std::endl;
                }
                
                if (shiftNorm < 1)
                {
                    break;
                }
                else
                {
                    oldPos = pos;
                }
            }

            for (int i = 0; i < pos.size(); i++)
            {
                pos[i].x /= scaling;
                pos[i].y /= scaling;
            }
        }

        for (int i = 0; i < pos.size(); i++)
        {
            pos[i].x /= scaling;
            pos[i].y /= scaling;
        }
        
        foundPoints = pos;
        outTform = tform;
        bOut = b;

        if (verbose)
        {
            cv::destroyWindow("Image");
            cv::destroyWindow("Error texture");
        }
    }

    void AAMFunctions2D::realAndModel(
        const TrainModelInfo& trainModel,
        const Vertices2DList& pos,
        const AppearanceData& appearanceData,
        const ShapeData& shapeData,
        const ShapeAppearanceData& shapeAppearance,
        RealMatrix& gOffset, RealMatrix& g)
    {
        cv::Mat J;

        appearance2Vector(trainModel.getImage(), pos,
                appearanceData.basePoints, appearanceData.objectPixels,
                appearanceData.nPixels, shapeData.triangles,
                J, gOffset);
        normalizeAppearance(gOffset);

        RealMatrix b1 = shapeAppearance.w * shapeData.eigVectors.t() *
                pointVector2Mat(trainModel.getCVertices() - shapeData.xMean);
        RealMatrix b2 = appearanceData.eigenVectors.t() *
                (gOffset - appearanceData.grayMean);

        RealMatrix b;
        cv::vconcat(b1, b2, b);

        RealMatrix c2 = shapeAppearance.eigVectors.t() *
                (b - shapeAppearance.bMeans);
        b = shapeAppearance.bMeans + shapeAppearance.eigVectors * c2;
        g = appearanceData.grayMean + appearanceData.eigenVectors *
                b.rowRange(shapeAppearance.w.rows, b.rows);
    }

    void AAMFunctions2D::makeAAMHelper(
        std::vector<TrainModelInfo>::const_iterator beginSeq,
        std::vector<TrainModelInfo>::const_iterator endSeq,
        int baseIndex,
        const ShapeAppearanceData& shapeAppearance,
        const ShapeData& shapeData,
        const AppearanceData& appearanceData,
        RealMatrix& drdp)
    {
        static const RealType offsetsTransX[MODEL_OFFSETS] =
        {
            -2   / POSE_STD,
            -1.2 / POSE_STD,
            -0.4 / POSE_STD,
             0.4 / POSE_STD,
             1.2 / POSE_STD,
             2   / POSE_STD
        };

        static const RealType offsetsTransY[MODEL_OFFSETS] =
        {
            -2   / POSE_STD,
            -1.2 / POSE_STD,
            -0.4 / POSE_STD,
             0.4 / POSE_STD,
             1.2 / POSE_STD,
             2   / POSE_STD
        };

        static const RealType offsetsScaleRtX[MODEL_OFFSETS] =
        {
            -0.2  / POSE_STD,
            -0.12 / POSE_STD,
            -0.04 / POSE_STD,
             0.04 / POSE_STD,
             0.12 / POSE_STD,
             0.2  / POSE_STD
        };

        static const RealType offsetsScaleRtY[MODEL_OFFSETS] =
        {
            -0.2  / POSE_STD,
            -0.12 / POSE_STD,
            -0.04 / POSE_STD,
             0.04 / POSE_STD,
             0.12 / POSE_STD,
             0.2  / POSE_STD
        };

        drdp = RealMatrix::zeros(
                shapeAppearance.eigVectors.cols + POSE_OFFSETS,
                appearanceData.grayMean.rows);
        int currentIndex = baseIndex;
        
        for (std::vector<TrainModelInfo>::const_iterator p = beginSeq;
                p != endSeq; p++, currentIndex++)
        {
            std::cout << "Processing sample " << std::dec <<
                    (int) (currentIndex + 1) <<
                    " of thread " << std::hex <<
                    boost::this_thread::get_id() <<
                    "...." << std::dec << std::endl;

            for (int j = 0; j < shapeAppearance.eigVectors.cols +
                    POSE_OFFSETS; j++)
            {
                if (j < shapeAppearance.eigVectors.cols)
                {
                    RealType de[MODEL_OFFSETS] =
                    {
                        -0.5, -0.3, -0.1, 0.1, 0.3, 0.5
                    };

                    RealMatrix c = shapeAppearance.eigVectors.t() *
                            (shapeAppearance.b.col(currentIndex) -
                                shapeAppearance.bMeans);
                    RealType cstd = cv::sqrt(
                            shapeAppearance.eigValues(j, 0));

                    for (int k = 0; k < MODEL_OFFSETS; k++)
                    {
                        RealMatrix cOffset = c.clone();
                        cOffset(j) += cstd * de[k];

                        RealMatrix bOffset = shapeAppearance.bMeans +
                                shapeAppearance.eigVectors * cOffset;
                        RealMatrix b1Offset = shapeAppearance.w.inv() *
                                bOffset.rowRange(0, shapeAppearance.w.cols);

                        RealMatrix x = pointVector2Mat(shapeData.xMean) +
                                shapeData.eigVectors * b1Offset;
                        Vertices2DList pos = mat2PointVector<RealType>(x);

                        alignDataInverse(pos, p->getTForm(),
                                pos);

                        RealMatrix g, gOffset;
                        realAndModel(*p, pos, appearanceData,
                                shapeData, shapeAppearance, gOffset, g);

                        RealType w = exp((-de[k] * de[k]) /
                                (2 * cstd * cstd)) / de[k];
                        RealMatrix tmp = (g - gOffset) * w;

                        for (int m = 0; m < tmp.rows; m++)
                        {
                            drdp(j, m) += tmp(m, 0);
                        }
                    }
                }
                else
                {
                    int mode = j - shapeAppearance.eigVectors.cols;
                    const RealType *de;

                    switch (mode)
                    {
                        case 0: // Translation x
                            de = offsetsTransX;
                            break;
                        case 1: // Translation y
                            de = offsetsTransY;
                            break;
                        case 2: // Scaling & Rotation Sx
                            de = offsetsScaleRtX;
                            break;
                        case 3: // Scaling & Rotation Sy
                            de = offsetsScaleRtY;
                            break;
                        default:
                            throw InternalException();
                    }

                    for (int k = 0; k < MODEL_OFFSETS; k++)
                    {
                        TForm tform = p->getTForm();

                        switch (mode)
                        {
                            case 0: // Translation x
                                tform.offsetV.x += de[k];
                                break;
                            case 1: // Translation y
                                tform.offsetV.y += de[k];
                                break;
                            case 2: // Scaling & Rotation Sx
                                tform.offsetSX += de[k];
                                break;
                            case 3: // Scaling & Rotation Sy
                                tform.offsetSY += de[k];
                                break;
                            default:
                                throw InternalException();
                        }

                        Vertices2DList pos;
                        alignDataInverse(p->getCVertices(),
                                tform, pos);

                        RealMatrix g, gOffset;
                        realAndModel(*p, pos, appearanceData,
                                shapeData, shapeAppearance, gOffset, g);

                        RealType w = exp((-de[k] * de[k]) /
                                (2 * POSE_STD * POSE_STD)) / de[k];
                        RealMatrix tmp = (g - gOffset) * w;

                        for (int m = 0; m < tmp.rows; m++)
                        {
                            drdp(j, m) += tmp(m, 0);
                        }
                    }
                }
            }
       }
    }

    void AAMFunctions2D::aplyModelIC(const cv::Mat& img,
            const Vertices2DList& initShape,
            const ICAAMModel& model,
            int maxIters,
            RealType deviationFactor,
            Vertices2DList& foundPoints,
            bool verbose)
    {
        if (model.getModelsCount() == 0)
        {
            return;
        }
        
        Vertices2DList curShape = initShape;
        cv::Mat J;
        RealMatrix g;
        std::vector<cv::Mat> adaptImages(model.getModelsCount());

        adaptImages[0] = img;
        for (int i = 1; i < adaptImages.size(); i++)
        {
            cv::pyrDown(adaptImages[i - 1], adaptImages[i],
                    cv::Size(adaptImages[i - 1].cols / 2,
                        adaptImages[i - 1].rows / 2));
        }

        int maxScale = model.getModelsCount() - 1;
        //maxScale = 0;
        for (int scale = maxScale; scale >= 0; scale--)
        {
            if (verbose)
            {
                std::cout << "Start adaptation at scale " << scale <<
                        std::endl;
            }

            RealType scaling = pow(2, -scale);
            AppearanceDataIC modelItem = model.getModel(scale);

            for (int i = 0; i < curShape.size(); i++)
            {
                curShape[i].x *= scaling;
                curShape[i].y *= scaling;
            }

            cv::Mat processedImage = adaptImages[scale];
            RealMatrix p;

            RealMatrix maxP, minP;
            RealMatrix lambdaA = modelItem.lambdaA;
            
            cv::sqrt(modelItem.lambdaS, maxP);
            maxP *= deviationFactor;
            minP = -maxP;

            bool doConstraints = false;

            for (int i = 0; i < maxIters; i++)
            {
                Vertices2DList compWarp;

                appearance2Vector(processedImage, curShape, modelItem.mask,
                        modelItem.nPixels, modelItem.triangles,
                        modelItem.warpInfo, J, g);
                normalizeAppearance(g);

                //RealMatrix A = modelItem.A0 + modelItem.A * lambdaA;
                RealMatrix errorImg = g - modelItem.A0;

                if (verbose)
                {
                    cv::Mat plotImg = processedImage.clone();
                    for (int j = 0; j < curShape.size(); j++)
                    {
                        cv::circle(plotImg, curShape[j], 3, CV_RGB(0, 0, 0));
                    }
                    cv::imshow("Image", plotImg);

                    cv::Mat outTexture;
                    vector2Appearance(errorImg, modelItem.mask,
                            modelItem.textureSize, outTexture);
                    cv::normalize(outTexture, outTexture, 1, 0,
                            cv::NORM_MINMAX);
                    cv::imshow("Error texture", outTexture);

                    cv::waitKey(300);
                }

                RealType shiftNorm = 0;
                RealMatrix M;

                if (scale == 0 || (scale != 0 && i >= 5))
                {
                    RealMatrix deltaQP = modelItem.R * errorImg;

                    RealMatrix deltaQ = deltaQP.rowRange(0, 4);
                    RealMatrix deltaP = deltaQP.rowRange(4, deltaQP.rows);

                    if (!doConstraints)
                    {
                        const cv::Vec3i& tr = modelItem.triangles[0];

                        cv::Point2f base[3] =
                        {
                            modelItem.s0[tr[0]],
                            modelItem.s0[tr[1]],
                            modelItem.s0[tr[2]]
                        };

                        cv::Point2f warp[3] =
                        {
                            curShape[tr[0]],
                            curShape[tr[1]],
                            curShape[tr[2]]
                        };

                        cv::Mat t = cv::getAffineTransform(base, warp);
                        cv::Mat it;
                        cv::invertAffineTransform(t, it);

                        Vertices2DList invertNS;
                        cv::transform(curShape, invertNS, it);
                        p = modelItem.s.t() * pointVector2Mat(
                                invertNS - modelItem.s0);
                        doConstraints = true;
                    }

                    for (int j = 0; j < p.rows; j++)
                    {
                        if (p(j) + deltaP(j) > maxP(j))
                        {
                            deltaP(j) = maxP(j) - p(j);
                        }

                        if (p(j) + deltaP(j) < minP(j))
                        {
                            deltaP(j) = minP(j) - p(j);
                        }
                    }

                    p += deltaP;

                    Vertices2DList ds0 = modelItem.s0 -
                            mat2PointVector<RealType>(
                                modelItem.s * deltaP);
                    deltaQ = -deltaQ;

                    toAffine(modelItem, deltaQ, M);
                    Vertices2DList r;
                    cv::transform(ds0, r, M);

                    warpComposition(modelItem, curShape, 
                            r, compWarp);
                }
                else if (i < 5)
                {
                    RealMatrix deltaQ = modelItem.R.rowRange(0, 4) *
                            errorImg;
                    Vertices2DList ds0;

                    deltaQ = -deltaQ;

                    toAffine(modelItem, deltaQ, M);
                    cv::transform(modelItem.s0, ds0, M);
                    ds0 -= modelItem.s0;

                    compWarp = curShape + ds0;
                }

                for (int j = 0; j < compWarp.size(); j++)
                {
                    RealType dx = compWarp[j].x - curShape[j].x;
                    RealType dy = compWarp[j].y - curShape[j].y;

                    shiftNorm += dx * dx + dy * dy;
                }

                shiftNorm = std::sqrt(shiftNorm);

                if (verbose)
                {
                    std::cout << "Shift in pixels at iteration " << i <<
                            " : " << shiftNorm <<
                            std::endl;
                }

                curShape = compWarp;
                //lambdaA = modelItem.A.t() * errorImg;

                if (shiftNorm < 1)
                {
                    break;
                }
            }

            for (int i = 0; i < curShape.size(); i++)
            {
                curShape[i].x /= scaling;
                curShape[i].y /= scaling;
            }
        }

        foundPoints = curShape;

        if (verbose)
        {
            cv::destroyWindow("Image");
            cv::destroyWindow("Error texture");
        }
    }

    void AAMFunctions2D::trainModelIC(
        RealType pcaCutThreshold,
        std::vector<TrainModelInfo>& trainData, 
        AppearanceDataIC& model)
    {
        std::cout << "Compute shape model" << std::endl;

        makeShapeModelIC(1, pcaCutThreshold, trainData,
                model);        
        std::cout << "Compute appearance model" << std::endl;

        makeAppearanceModelIC(pcaCutThreshold, trainData, model);

        std::cout << "Compute texture gradient" << std::endl;
        // Compute mean image gradient
        XYDerivation dA0;
        computeGradient(model, model.A0, dA0);

        std::cout << "Compute jacobian" << std::endl;
        XYDerivation dWdp, dNdq;
        computeJacobian(model, dWdp, dNdq);

        std::cout << "Compute steepest descent image" << std::endl;
        aam::RealMatrix SD;
        computeSDImage(model, dA0, dWdp, dNdq, SD);

        model.SD = SD.t();

        std::cout << "Compute R matrix" << std::endl;
        RealMatrix H = model.SD * model.SD.t();
        model.invH = H.inv();
        model.R = model.invH * model.SD;
    }

    void AAMFunctions2D::toAffine(const AppearanceDataIC& model,
            const RealMatrix& q, RealMatrix& M)
    {
        assert(!model.triangles.empty());

        const cv::Vec3i& tr = model.triangles[0];
        int np = (int) model.s0.size();

        cv::Point2f base[3] =
        {
            model.s0[tr[0]],
            model.s0[tr[1]],
            model.s0[tr[2]]
        };

        RealMatrix delta[6] =
        {
            model.sStar.row(tr[0]) * q,
            model.sStar.row(np + tr[0]) * q,
            model.sStar.row(tr[1]) * q,
            model.sStar.row(np + tr[1]) * q,
            model.sStar.row(tr[2]) * q,
            model.sStar.row(np + tr[2]) * q
        };

        cv::Point2f warp[3] =
        {
            base[0] + cv::Point2f(delta[0](0, 0), delta[1](0, 0)),
            base[1] + cv::Point2f(delta[2](0, 0), delta[3](0, 0)),
            base[2] + cv::Point2f(delta[4](0, 0), delta[5](0, 0))
        };

        cv::Mat t = cv::getAffineTransform(base, warp);
        M = RealMatrix(t);
    }

    void AAMFunctions2D::warpComposition(const AppearanceDataIC& model,
            const Vertices2DList& curShape, const Vertices2DList& inc,
            Vertices2DList& compWarp)
    {
        int np = curShape.size();
        std::vector<int> nt(np);
        compWarp.resize(np);
        
        for (int i = 0; i < model.triangles.size(); i++)
        {
            cv::Vec3i t = model.triangles[i];

            nt[t[0]]++; nt[t[1]]++; nt[t[2]]++;

            for (int k = 0; k < 3; k++)
            {
                cv::Vec3i t2 = t;

                t2[0] = t[k];
                t2[k] = t[0];

                RealType x1 = model.s0[t2[0]].x;
                RealType y1 = model.s0[t2[0]].y;
                RealType x2 = model.s0[t2[1]].x;
                RealType y2 = model.s0[t2[1]].y;
                RealType x3 = model.s0[t2[2]].x;
                RealType y3 = model.s0[t2[2]].y;

                RealType xCoord = inc[t2[0]].x;
                RealType yCoord = inc[t2[0]].y;

                RealType den = (x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1);
                RealType alpha = ((xCoord - x1) * (y3 - y1) -
                        (yCoord - y1) * (x3 - x1)) / den;
                RealType beta = ((yCoord - y1) * (x2 - x1) -
                        (xCoord - x1) * (y2 - y1)) / den;

                compWarp[t2[0]].x += alpha * (curShape[t2[1]].x - 
                        curShape[t2[0]].x) + beta * (curShape[t2[2]].x -
                        curShape[t2[0]].x);
                compWarp[t2[0]].y += alpha * (curShape[t2[1]].y -
                        curShape[t2[0]].y) + beta * (curShape[t2[2]].y -
                        curShape[t2[0]].y);
            }
        }
        
        for (int i = 0; i < np; i++)
        {
            compWarp[i].x = curShape[i].x + compWarp[i].x / nt[i];
            compWarp[i].y = curShape[i].y + compWarp[i].y / nt[i];
        }
    }

    void AAMFunctions2D::computeJacobian(const AppearanceDataIC& model,
            XYDerivation& dW_dp, XYDerivation& dN_dq)
    {
        //int dWdpSizes[4] = { model.warpMap.rows, model.warpMap.cols, 2,
        //    model.s.cols };
        dW_dp.xDerivation = RealMatrix::zeros(model.nPixels,
                model.s.cols);
        dW_dp.yDerivation = RealMatrix::zeros(model.nPixels,
                model.s.cols);
        
        //int dNdqSizes[4] = { model.warpMap.rows, model.warpMap.cols, 2,
        //    4 };
        dN_dq.xDerivation = RealMatrix::zeros(model.nPixels, 4);
        dN_dq.yDerivation = RealMatrix::zeros(model.nPixels, 4);

        int ptIndex = 0;
        for (int y = 0; y < model.warpMap.rows; y++)
        {
            for (int x = 0; x < model.warpMap.cols; x++)
            {
                if (model.warpMap(y, x) != -1)
                {
                    assert(ptIndex < model.nPixels);
                    
                    int triangleIndex = model.warpMap(y, x);
                    cv::Vec3i t = model.triangles.at(triangleIndex);

                    for (int k = 0; k < 3; k++)
                    {
                        RealMatrix dxdp = model.s.row(t[k]);
                        RealMatrix dydp = model.s.row(t[k] +
                                model.s0.size());
                        
                        RealMatrix dxdq = model.sStar.row(t[k]);
                        RealMatrix dydq = model.sStar.row(t[k] +
                                model.s0.size());

                        cv::Vec3i t2 = t;
                        std::swap(t2[0], t2[k]);

                        RealType x1 = model.s0[t2[0]].x;
                        RealType y1 = model.s0[t2[0]].y;
                        RealType x2 = model.s0[t2[1]].x;
                        RealType y2 = model.s0[t2[1]].y;
                        RealType x3 = model.s0[t2[2]].x;
                        RealType y3 = model.s0[t2[2]].y;

                        RealType den = (x2 - x1) * (y3 - y1) - (y2 - y1) *
                                (x3 - x1);
                        RealType alpha = ((x - x1) * (y3 - y1) -
                                (y - y1) * (x3 - x1)) / den;
                        RealType beta = ((y - y1) * (x2 - x1) -
                                (x - x1) * (y2 - y1)) / den;

                        RealType dWdxy = 1 - alpha - beta;
                        //RealMatrix dxydp, dxydq;

                        for (int s = 0; s < model.s.cols; s++)
                        {
                            dW_dp.xDerivation(ptIndex, s) += dWdxy *
                                    dxdp(0, s);
                            dW_dp.yDerivation(ptIndex, s) += dWdxy *
                                    dydp(0, s);
                        }

                        for (int s = 0; s < model.sStar.cols; s++)
                        {
                            dN_dq.xDerivation(ptIndex, s) += dWdxy *
                                    dxdq(0, s);
                            dN_dq.yDerivation(ptIndex, s) += dWdxy *
                                    dydq(0, s);
                        }
                    }

                    ptIndex++;
                }
            }
        }
    }

    void AAMFunctions2D::makeShapeModelIC(
        int textureSize,
        RealType pcaCutThreshold,
        std::vector<TrainModelInfo>& trainData,
        AppearanceDataIC& model)
    {
        int niter = 2;

        assert(!trainData.empty());

        Vertices2DList meanVertices = trainData[0].getVertices();
        Vertices2DList referenceVertices = meanVertices;
        std::vector<Vertices2DList> cVertices(trainData.size());

        for (int i = 0; i < trainData.size(); i++)
        {
            cVertices[i] = trainData[i].getVertices();
        }

        for (int k = 0; k < niter; k++)
        {
            Vertices2DList tmp(meanVertices.size());

            for (int s = 0; s < cVertices.size(); s++)
            {
                Vertices2DList Y;
                CommonFunctions::procrustes(meanVertices,
                        cVertices[s],
                        Y);
                cVertices[s] = Y;
            }

            for (int i = 0; i < cVertices.size(); i++)
            {
                tmp += cVertices[i];
            }

            CommonFunctions::procrustes(referenceVertices,
                    tmp / trainData.size(),
                    meanVertices);
        }

        std::fill(meanVertices.begin(), meanVertices.end(), Point2D());
        for (int i = 0; i < cVertices.size(); i++)
        {
            meanVertices += cVertices[i];
        }

        meanVertices /= Point2D(cVertices.size(), cVertices.size());
        
        Point2D minShapePt = minCoords(meanVertices);
        Point2D maxShapePt = maxCoords(meanVertices);
        meanVertices -= Point2D(minShapePt.x - 1, minShapePt.y - 1);

        int np = meanVertices.size();
        RealMatrix shapeMatrix(2 * np, trainData.size());

        for (int i = 0; i < trainData.size(); i++)
        {
            RealMatrix shape = pointVector2Mat(cVertices[i] - meanVertices);
            shape.copyTo(shapeMatrix.col(i));
        }

        RealMatrix xMeans, eigValues, eigVectors;
        CommonFunctions::varPCA(shapeMatrix, xMeans, eigVectors,
                eigValues);
        CommonFunctions::removeEigNoise(eigVectors, eigValues,
                pcaCutThreshold);

        RealMatrix s1Star = pointVector2Mat(meanVertices);        
        RealMatrix s2Star(s1Star.rows, 1), s3Star(s1Star.rows, 1),
                s4Star(s1Star.rows, 1);
        for (int i = 0; i < np; i++)
        {
            s2Star(i, 0) = meanVertices[i].y;
            s2Star(i + np, 0) = -meanVertices[i].x;
            s3Star(i, 0) = 0;
            s3Star(i + np, 0) = 1;
            s4Star(i, 0) = 1;
            s4Star(i + np, 0) = 0;
        }

        RealMatrix sStar = RealMatrix::zeros(2 * np, 4 + eigVectors.cols);
        RealMatrix sStarNorm;
        
        s1Star.copyTo(sStar.col(0));
        s2Star.copyTo(sStar.col(1));
        s3Star.copyTo(sStar.col(2));
        s4Star.copyTo(sStar.col(3));
        eigVectors.copyTo(sStar.colRange(4, sStar.cols));
        
        //std::cout << sStar.colRange(0, 4) << std::endl;

        CommonFunctions::orthonormGS(sStar, sStarNorm);

        model.textureSize.width = ceil(maxShapePt.x - minShapePt.x + 3);
        model.textureSize.height = ceil(maxShapePt.y - minShapePt.y + 3);
        model.s0 = meanVertices;
        model.s = sStarNorm.colRange(4, sStarNorm.cols);
        model.sStar = sStarNorm.colRange(0, 4);
        model.lambdaS = eigValues;

        if (model.triangles.empty())
        {
            CommonFunctions::delaunay(meanVertices, model.triangles);
        }
    }

    void AAMFunctions2D::makeAppearanceModelIC(RealType pcaCutThreshold,
            std::vector<TrainModelInfo>& trainData, AppearanceDataIC& model)
    {
        if (trainData.empty())
        {
            return;
        }

        CommonFunctions::getWarpMap(model.s0,
                model.triangles, model.textureSize,
                model.warpMap);
        model.mask = (model.warpMap != -1);
        model.nPixels = cv::countNonZero(model.mask);

        RealMatrix grayVector = RealMatrix::zeros(model.nPixels *
                trainData[0].getImage().channels(),
                trainData.size());

        for (int i = 0; i < trainData.size(); i++)
        {
            cv::Mat J;
            RealMatrix g;

            appearance2Vector(trainData[i].getImage(),
                    trainData[i].getVertices(), model.s0,
                    model.mask, model.nPixels, model.triangles,
                    J, g);
            g.copyTo(grayVector.col(i));
        }

        normalizeAppearance(grayVector);

        RealMatrix gMeans, eigValues, eigVectors;
        CommonFunctions::appPCA(grayVector, gMeans, eigVectors,
                eigValues);
        CommonFunctions::removeEigNoise(eigVectors, eigValues,
                pcaCutThreshold);

        model.A0 = gMeans;
        model.A = eigVectors;
        model.colorChannels = gMeans.rows / model.nPixels;
        model.lambdaA = eigValues;
    }

    void AAMFunctions2D::computeSDImage(const AppearanceDataIC& model,
            const XYDerivation& dA0, const XYDerivation& dW_dp,
            const XYDerivation& dN_dq,
            RealMatrix& SD)
    {
        int nc = model.colorChannels;
        int totalPixels = nc * model.nPixels;
        assert(totalPixels == model.A.rows);
        assert(totalPixels == dA0.xDerivation.rows &&
               totalPixels == dA0.yDerivation.rows);
        
        int nv = 4 + model.s.cols;
        SD = RealMatrix::zeros(totalPixels, nv);

        // Compute steepest descent images for the 4 global transformation
        // parameters
        for (int i = 0; i < 4; i++)
        {
            RealMatrix prjDiff = RealMatrix::zeros(nc, model.A.cols);

            for (int j = 0; j < model.A.cols; j++)
            {
                for (int ch = 0; ch < nc; ch++)
                {
                    int channelBaseIndex = ch * model.nPixels;
                    RealMatrix eigVector(model.A.col(j));

                    for (int s = 0; s < model.nPixels; s++)
                    {
                        prjDiff(ch, j) += eigVector(s + channelBaseIndex, 0) *
                                (dA0.xDerivation(s + channelBaseIndex, 0) *
                                 dN_dq.xDerivation(s, i) +
                                 dA0.yDerivation(s + channelBaseIndex, 0) *
                                 dN_dq.yDerivation(s, i));
                    }
                }

            }
            
            for (int ch = 0; ch < nc; ch++)
            {
                int channelBaseIndex = ch * model.nPixels;
                for (int s = 0; s < model.nPixels; s++)
                {
                    SD.at<RealType>(s + channelBaseIndex, i) =
                            dA0.xDerivation(s + channelBaseIndex, 0) *
                            dN_dq.xDerivation(s, i) +
                            dA0.yDerivation(s + channelBaseIndex, 0) *
                            dN_dq.yDerivation(s, i);
                }
            }

            for (int j = 0; j < model.A.cols; j++)
            {
                for (int ch = 0; ch < nc; ch++)
                {
                    int channelBaseIndex = ch * model.nPixels;
                    RealMatrix eigVector(model.A.col(j));

                    for (int s = 0; s < model.nPixels; s++)
                    {
                        SD.at<RealType>(s + channelBaseIndex, i) -=
                                prjDiff(ch, j) *
                                eigVector(s + channelBaseIndex, 0);
                    }
                }
            }
        }

        // Compute steepest descent images for the shape parameters
        for (int i = 0; i < model.s.cols; i++)
        {
            RealMatrix prjDiff = RealMatrix::zeros(nc, model.A.cols);

            for (int j = 0; j < model.A.cols; j++)
            {
                for (int ch = 0; ch < nc; ch++)
                {
                    int channelBaseIndex = ch * model.nPixels;
                    RealMatrix eigVector(model.A.col(j));

                    for (int s = 0; s < model.nPixels; s++)
                    {
                        prjDiff(ch, j) += eigVector(s + channelBaseIndex, 0) *
                                (dA0.xDerivation(s + channelBaseIndex, 0) *
                                 dW_dp.xDerivation(s, i) +
                                 dA0.yDerivation(s + channelBaseIndex, 0) *
                                 dW_dp.yDerivation(s, i));
                    }
                }
            }

            for (int ch = 0; ch < nc; ch++)
            {
                int channelBaseIndex = ch * model.nPixels;
                for (int s = 0; s < model.nPixels; s++)
                {
                    SD.at<RealType>(s + channelBaseIndex, i + 4) =
                            dA0.xDerivation(s + channelBaseIndex, 0) *
                            dW_dp.xDerivation(s, i) +
                            dA0.yDerivation(s + channelBaseIndex, 0) *
                            dW_dp.yDerivation(s, i);
                }
            }

            for (int j = 0; j < model.A.cols; j++)
            {
                for (int ch = 0; ch < nc; ch++)
                {
                    int channelBaseIndex = ch * model.nPixels;
                    RealMatrix eigVector(model.A.col(j));

                    for (int s = 0; s < model.nPixels; s++)
                    {
                        SD.at<RealType>(s + channelBaseIndex, i + 4) -=
                                prjDiff(ch, j) *
                                eigVector(s + channelBaseIndex, 0);
                    }
                }
            }
        }
    }

    void AAMFunctions2D::computeGradient(const AppearanceDataIC& model,
            const RealMatrix& A, XYDerivation& dA)
    {
        cv::Mat outImage;
        vector2Appearance(A, model.mask, model.textureSize, outImage);

        std::vector<RealMatrix> imgChannels;
        cv::split(outImage, imgChannels);

        dA.xDerivation = RealMatrix(model.nPixels * imgChannels.size(), 1);
        dA.yDerivation = RealMatrix(model.nPixels * imgChannels.size(), 1);

        for (int ch = 0; ch < imgChannels.size(); ch++)
        {
            RealMatrix di, dj;
            CommonFunctions::gradient2D(imgChannels[ch],
                    model.mask, di, dj);

            int ptIndex = 0;
            for (int i = 0; i < outImage.rows; i++)
            {
                for (int j = 0; j < outImage.cols; j++)
                {
                    if (model.mask(i, j))
                    {
                        dA.xDerivation(ptIndex + ch * model.nPixels, 0) =
                                dj(i, j);
                        dA.yDerivation(ptIndex + ch * model.nPixels, 0) =
                                di(i, j);
                        ptIndex++;
                    }
                }
            }
        }
    }
}
