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
 * File:   CommonFunctions.cpp
 * Author: Иван Губочкин
 * 
 * Created on 12 Август 2012 г., 22:19
 */

#include <boost/math/special_functions/sign.hpp>
#include <boost/math/special_functions/round.hpp>
#include <boost/bind/bind.hpp>
#include <vector>
#include <boost/assign/list_of.hpp>
#include <limits>
#include <algorithm>

#include "aam/CommonFunctions.h"
#include "aam/aam.h"
#include "aam/vector_op.h"

namespace aam
{
    void CommonFunctions::PCA(const RealMatrix& data, RealMatrix& means,
            RealMatrix& eigenVectors, RealMatrix& eigenValues)
    {
//        cv::PCA pca(data, cv::Mat(), CV_PCA_DATA_AS_COL);
//        means = pca.mean;
//        eigenValues = pca.eigenvalues;
//        eigenVectors = pca.eigenvectors.t();
        
        int c = data.cols;
        cv::Mat covar;

        cv::calcCovarMatrix(data, covar, means, CV_COVAR_COLS,
                OpenCVRealType::type);
        cv::Mat x(data.rows, data.cols, data.type());
        RealType n = sqrt(c - 1);

        for (int i = 0; i < data.cols; i++)
        {
            cv::Mat d = data.col(i) - means;
            cv::Mat c = x.col(i);
            d.copyTo(c);
        }

        x /= n;

        cv::Mat w, u, vt;
        cv::SVDecomp(x, w, u, vt, cv::SVD::MODIFY_A);
        cv::multiply(w, w, eigenValues);

        for (int i = 0; i < u.cols; i++)
        {
            int sgn = boost::math::sign(u.at<RealType>(0, i));

            u.col(i) *= sgn;
        }

        eigenVectors = u;
    }

    void CommonFunctions::varPCA(const RealMatrix& data, RealMatrix& means,
            RealMatrix& eigenVectors, RealMatrix& eigenValues)
    {
        cv::Mat covar;

        cv::calcCovarMatrix(data, covar, means, CV_COVAR_COLS,
                OpenCVRealType::type);
        RealMatrix x0 = data.clone();

        for (int i = 0; i < data.cols; i++)
        {
            x0.col(i) -= means;
        }

        cv::Mat w, u, vt;
        cv::SVDecomp(x0.t(), w, u, vt, cv::SVD::MODIFY_A);

//        for (int i = 0; i < vt.rows; i++)
//        {
//            int sgn = boost::math::sign(vt.at<RealType>(i, 0));
//
//            vt.row(i) *= sgn;
//        }

        w /= sqrt(data.cols - 1);
        cv::multiply(w, w, eigenValues);
        eigenVectors = vt.t();
    }
    
    void CommonFunctions::delaunay(const Vertices2DList& pts,
            std::vector<cv::Vec3i>& triangles)
    {
        if (pts.size() < 3)
        {
            triangles = std::vector<cv::Vec3i>();
            return;
        }

        std::vector<cv::Point2f> delaunayPoints = convertVector<float>(pts);
        cv::Rect r = cv::boundingRect(delaunayPoints);
        r.x -= 1;
        r.y -= 1;
        r.width += 2;
        r.height += 2;
        
        cv::Subdiv2D sd(r);
        sd.insert(delaunayPoints);

        std::vector<cv::Vec6f> tmp;
        sd.getTriangleList(tmp);

        std::vector<cv::Vec6f>::iterator itTriEnd =
                std::remove_if(tmp.begin(), tmp.end(), boost::bind(
                    CommonFunctions::triPred, r, _1));
        
        triangles.resize(itTriEnd - tmp.begin());

        for (int i = 0; i < triangles.size(); i++)
        {
            cv::Vec3i v;

            findPointNumber(pts, cv::Point2f(tmp[i][0], tmp[i][1]), v[0]);
            findPointNumber(pts, cv::Point2f(tmp[i][2], tmp[i][3]), v[1]);
            findPointNumber(pts, cv::Point2f(tmp[i][4], tmp[i][5]), v[2]);

            triangles[i] = v;
        }
    }

    bool CommonFunctions::triPred(const cv::Rect& r, const cv::Vec6f& t)
    {
        bool result = r.contains(cv::Point2f(t[0], t[1])) &&
                    r.contains(cv::Point2f(t[2], t[3])) &&
                    r.contains(cv::Point2f(t[4], t[5]));

        return !result;
    }

    void CommonFunctions::drawObject(const cv::Size& textureSize,
            const std::vector<LineType>& lines, const Vertices2DList& points,
            cv::Mat1b& objectPixels)
    {
        objectPixels = cv::Mat1b::zeros(textureSize.height, textureSize.width);
        std::vector<cv::Point> polyPoints(lines.size());

        if (lines.empty())
        {
            return;
        }

        for (int i = 0; i < lines.size(); i++)
        {
            polyPoints[i].x = boost::math::round(points[lines[i]].x);
            polyPoints[i].y = boost::math::round(points[lines[i]].y);
        }

        std::vector<std::vector<cv::Point> > t(1, polyPoints);
        cv::fillPoly(objectPixels,
                t,
                255);
        cv::drawContours(objectPixels, t, 0, 0);
    }

    bool CommonFunctions::findPointNumber(const Vertices2DList& pts,
            const cv::Point2f& pt, int& ptNumber)
    {
        for (int i = 0; i < pts.size(); i++)
        {
            if (fabs(pts[i].x - pt.x) < 1e-5 && fabs(pts[i].y - pt.y) < 1e-5)
            {
                ptNumber = i;
                return true;
            }
        }
        
        return false;
    }

    void CommonFunctions::removeEigNoise(RealMatrix& eigVectors,
            RealMatrix& eigValues, RealType threshold)
    {
        assert(threshold > 0 && threshold <= 1.0);

        // Nothing to do for empty matrixes
        if (eigVectors.empty() && eigValues.empty())
        {
            return;
        }

        assert(eigValues.cols == 1 && eigVectors.cols == eigValues.rows);

        RealType cs = 0;
        RealType s = cv::sum(eigValues)[0];
        int index = 0;

        do
        {
            if (cs > threshold * s)
            {
                break;
            }

            cs += eigValues(index, 0);
            index++;
        } while (index < eigValues.rows);

        eigVectors = eigVectors.colRange(0, index);
        eigValues = eigValues.rowRange(0, index);
    }

    std::string CommonFunctions::combineScaleField(int scale,
            const std::string& filedName)
    {
        std::ostringstream stream;

        stream << "scale_" << scale << "_" << filedName;
        return stream.str();
    }

    void CommonFunctions::opencvMat2Dlib(const RealMatrix& src,
            dlib::matrix<RealType, 0, 1>& dst)
    {
        dst = dlib::matrix<RealType>(src.rows, src.cols);

        for (int i = 0; i < src.rows; i++)
        {
            for (int j = 0; j < src.cols; j++)
            {
                dst(i, j) = src.at<RealType>(i, j);
            }
        }
    }

    void CommonFunctions::dlibMat2OpenCV(
            const dlib::matrix<RealType, 0, 1>& src,
            RealMatrix& dst)
    {
        dst = RealMatrix(src.nr(), src.nc());

        for (int i = 0; i < src.nr(); i++)
        {
            for (int j = 0; j < src.nc(); j++)
            {
                dst(i, j) = src(i, j);
            }
        }
    }

    void CommonFunctions::gradient2D(const ColorMatrix& M,
            const cv::Mat1b& mask,
            ColorMatrix& di, ColorMatrix& dj)
    {
        assert(M.rows == mask.rows && M.cols == mask.cols);

        std::vector<RealMatrix> channels;
        cv::split(M, channels);
        
        std::vector<cv::Mat> diChannels(M.channels()),
                djChannels(M.channels());

        for (int i = 0; i < channels.size(); i++)
        {
            RealMatrix tmpI, tmpJ;
            gradient2D(channels[i], mask, tmpI, tmpJ);

            diChannels[i] = tmpI;
            djChannels[i] = tmpJ;
        }

        cv::merge(diChannels, di);
        cv::merge(djChannels, dj);
    }

    void CommonFunctions::gradient2D(const RealMatrix& M,
            const cv::Mat1b& mask,
            RealMatrix& di, RealMatrix& dj)
    {
        assert(M.size == mask.size);

        int nr = M.rows;
        int nc = M.cols;

        di = RealMatrix::zeros(nr, nc);
        dj = RealMatrix::zeros(nr, nc);
        
        RealMatrix p(3, 2), v(3, 1), pInv, n;

        p(0, 0) = 1; p(0, 1) = 0;
        p(1, 0) = 0; p(1, 1) = 1;
        p(2, 0) = 1; p(2, 1) = 1;

        v(0, 0) = M(1, 0) - M(0, 0);
        v(1, 0) = M(0, 1) - M(0, 0);
        v(2, 0) = M(1, 1) - M(0, 0);

        cv::invert(p, pInv, cv::DECOMP_SVD);
        n = pInv * v;
        
        di(0, 0) = n(0, 0);
        dj(0, 0) = n(1, 0);

        p(0, 0) = 0; p(0, 1) = -1;
        p(1, 0) = 1; p(1, 1) = -1;
        p(2, 0) = 1; p(2, 1) =  0;

        v(0, 0) = M(0, nc - 2) - M(0, nc - 1);
        v(1, 0) = M(1, nc - 2) - M(0, nc - 1);
        v(2, 0) = M(1, nc - 1) - M(0, nc - 1);

        cv::invert(p, pInv, cv::DECOMP_SVD);
        n = pInv * v;

        di(0, nc - 1) = n(0, 0);
        dj(0, nc - 1) = n(1, 0);

        p(0, 0) = -1; p(0, 1) = 0;
        p(1, 0) = -1; p(1, 1) = 1;
        p(2, 0) =  0; p(2, 1) = 1;

        v(0, 0) = M(nr - 2, 0) - M(nr - 1, 0);
        v(1, 0) = M(nr - 2, 1) - M(nr - 1, 0);
        v(2, 0) = M(nr - 1, 1) - M(nr - 1, 0);

        cv::invert(p, pInv, cv::DECOMP_SVD);
        n = pInv * v;

        di(nr - 1, 0) = n(0, 0);
        dj(nr - 1, 0) = n(1, 0);

        p(0, 0) = -1; p(0, 1) = -1;
        p(1, 0) =  0; p(1, 1) = -1;
        p(2, 0) = -1; p(2, 1) =  0;

        v(0, 0) = M(nr - 2, nc - 2) - M(nr - 1, nc - 1);
        v(1, 0) = M(nr - 1, nc - 2) - M(nr - 1, nc - 1);
        v(2, 0) = M(nr - 2, nc - 1) - M(nr - 1, nc - 1);

        cv::invert(p, pInv, cv::DECOMP_SVD);
        n = pInv * v;

        di(nr - 1, nc - 1) = n(0, 0);
        dj(nr - 1, nc - 1) = n(1, 0);

        p = RealMatrix(5, 2);
        v = RealMatrix(5, 1);
        
        for (int j = 1; j < nc - 1; j++)
        {
            p(0, 0) = 0; p(0, 1) = -1;
            p(1, 0) = 1; p(1, 1) = -1;
            p(2, 0) = 1; p(2, 1) =  0;
            p(3, 0) = 0; p(3, 1) =  1;
            p(4, 0) = 1; p(4, 1) =  1;
            v(0, 0) = M(0, j - 1) - M(0, j);
            v(1, 0) = M(1, j - 1) - M(0, j);
            v(2, 0) = M(1, j)     - M(0, j);
            v(3, 0) = M(0, j + 1) - M(0, j);
            v(4, 0) = M(1, j + 1) - M(0, j);

            cv::invert(p, pInv, cv::DECOMP_SVD);
            n = pInv * v;

            di(0, j) = n(0, 0);
            dj(0, j) = n(1, 0);

            p(0, 0) = -1; p(0, 1) = -1;
            p(1, 0) =  0; p(1, 1) = -1;
            p(2, 0) = -1; p(2, 1) =  0;
            p(3, 0) = -1; p(3, 1) =  1;
            p(4, 0) =  0; p(4, 1) =  1;
            v(0, 0) = M(nr - 2, j -1)  - M(nr - 1, j);
            v(1, 0) = M(nr - 1, j -1)  - M(nr - 1, j);
            v(2, 0) = M(nr - 2, j)     - M(nr - 1, j);
            v(3, 0) = M(nr - 2, j + 1) - M(nr - 1, j);
            v(4, 0) = M(nr - 1, j + 1) - M(nr - 1, j);

            cv::invert(p, pInv, cv::DECOMP_SVD);
            n = pInv * v;

            di(nr - 1, j) = n(0, 0);
            dj(nr - 1, j) = n(1, 0);
        }

        for (int i = 1; i < nr - 1; i++)
        {
            p(0, 0) = -1; p(0, 1) = 0;
            p(1, 0) =  1; p(1, 1) = 0;
            p(2, 0) = -1; p(2, 1) = 1;
            p(3, 0) =  0; p(3, 1) = 1;
            p(4, 0) =  1; p(4, 1) = 1;
            v(0, 0) = M(i - 1, 0) - M(i, 0);
            v(1, 0) = M(i + 1, 0) - M(i, 0);
            v(2, 0) = M(i - 1, 1) - M(i, 0);
            v(3, 0) = M(i,     1) - M(i, 0);
            v(4, 0) = M(i + 1, 1) - M(i, 0);

            cv::invert(p, pInv, cv::DECOMP_SVD);
            n = pInv * v;

            di(i, 0) = n(0, 0);
            dj(i, 0) = n(1, 0);

            p(0, 0) = -1; p(0, 1) = -1;
            p(1, 0) =  0; p(1, 1) = -1;
            p(2, 0) =  1; p(2, 1) = -1;
            p(3, 0) = -1; p(3, 1) =  0;
            p(4, 0) =  1; p(4, 1) =  0;
            v(0, 0) = M(i - 1, nc - 2) - M(i, nc - 1);
            v(1, 0) = M(i,     nc - 2) - M(i, nc - 1);
            v(2, 0) = M(i + 1, nc - 2) - M(i, nc - 1);
            v(3, 0) = M(i - 1, nc - 1) - M(i, nc - 1);
            v(4, 0) = M(i + 1, nc - 1) - M(i, nc - 1);

            cv::invert(p, pInv, cv::DECOMP_SVD);
            n = pInv * v;

            di(i, nc - 1) = n(0, 0);
            dj(i, nc - 1) = n(1, 0);
        }
        
        p = RealMatrix(8, 2);
        v = RealMatrix(8, 1);

        for (int i = 1; i < nr - 1; i++)
        {
            for (int j = 1; j < nc - 1; j++)
            {
                if (mask(i, j))
                {
                    int k = 0;

                    if (mask(i - 1, j - 1))
                    {
                        p(k, 0) = -1; p(k, 1) = -1;
                        v(k, 0) = M(i - 1, j - 1) - M(i,j);
                        k++;
                    }

                    if (mask(i - 1, j))
                    {
                        p(k, 0) = -1; p(k, 1) = 0;
                        v(k, 0) = M(i - 1, j) - M(i, j);
                        k++;
                    }

                    if (mask(i - 1, j + 1))
                    {
                        p(k, 0) = -1; p(k, 1) = 1;
                        v(k, 0) = M(i - 1, j + 1) - M(i, j);
                        k++;
                    }

                    if (mask(i, j - 1))
                    {
                        p(k, 0) = 0; p(k, 1) = -1;
                        v(k, 0) = M(i, j - 1) - M(i, j);
                        k++;
                    }

                    if (mask(i, j + 1))
                    {
                        p(k, 0) = 0; p(k, 1) = 1;
                        v(k, 0) = M(i, j + 1) - M(i, j);
                        k++;
                    }

                    if (mask(i + 1, j - 1))
                    {
                        p(k, 0) = 1; p(k, 1) = -1;
                        v(k, 0) = M(i + 1, j - 1) - M(i, j);
                        k++;
                    }

                    if (mask(i + 1, j))
                    {
                        p(k, 0) = 1; p(k, 1) = 0;
                        v(k, 0) = M(i + 1, j) - M(i, j);
                        k++;
                    }

                    if (mask(i + 1, j + 1))
                    {
                        p(k, 0) = 1; p(k, 1) = 1;
                        v(k, 0) = M(i + 1, j + 1) - M(i, j);
                        k++;
                    }

                    if (k > 1)
                    {
                        cv::invert(p.rowRange(0, k), pInv,
                                cv::DECOMP_SVD);
                        n = pInv * v.rowRange(0, k);

                        di(i, j) = n(0, 0);
                        dj(i, j) = n(1, 0);
                    }
                }
            }
        }
    }

    void CommonFunctions::orthonormGS(const RealMatrix& M,
            RealMatrix& V)
    {
        V = M.clone();

        for (int i = 0; i < V.cols; i++)
        {
            V.col(i) /= cv::norm(V.col(i));

            RealMatrix vi(V.col(i));
            RealType prodU = vi.dot(vi);
            for (int j = i + 1; j < V.cols; j++)
            {
                RealMatrix vj(V.col(j));
                RealType prodV = vj.dot(vi);
                RealMatrix proj = prodV / prodU * V.col(i);

                V.col(j) -= proj;
            }
        }
    }

    void CommonFunctions::getWarpMap(const Vertices2DList& shape,
            const std::vector<cv::Vec3i>& triangles, const cv::Size& warpSize,
            cv::Mat1i& warpMap)
    {
        warpMap = cv::Mat1i(warpSize.height, warpSize.width, -1);

        for (int y = 0; y < warpSize.height; y++)
        {
            for (int x = 0; x < warpSize.width; x++)
            {
                if (warpMap(y, x) == -1)
                {
                    for (int t = 0; t < triangles.size(); t++)
                    {
                        cv::Vec3i triangle = triangles[t];

                        // Vertices of the triangle in the mean shape
                        RealType x1 = shape[triangle[0]].x;
                        RealType y1 = shape[triangle[0]].y;
                        RealType x2 = shape[triangle[1]].x;
                        RealType y2 = shape[triangle[1]].y;
                        RealType x3 = shape[triangle[2]].x;
                        RealType y3 = shape[triangle[2]].y;

                        // Compute the two barjcentric coordinates
                        RealType den = (x2 - x1) * (y3 - y1) - (y2 - y1) *
                                (x3 - x1);
                        RealType alpha = ((x - x1) * (y3 - y1) - (y - y1) *
                                (x3 - x1)) / den;
                        RealType beta = ((y - y1) * (x2 - x1) - (x - x1) *
                                (y2 - y1)) / den;

                        if (alpha >= 0 && beta >= 0 && (alpha + beta) <= 1)
                        {
                            // Found the triangle, save data to the bitmaps
                            // and break
                            warpMap(y, x) = t;
                            break;
                        }
                    }
                }
            }
        }
    }

    RealType CommonFunctions::procrustes(const Vertices2DList& X,
            const Vertices2DList& Y, Vertices2DList& Z)
    {
        assert(X.size() == Y.size());
        RealType d;

        Point2D muX = mean(X);
        Point2D muY = mean(Y);
        Vertices2DList X0 = X - muX;
        Vertices2DList Y0 = Y - muY;

        Point2D ssqX, ssqY;
        for (int i = 0; i < X0.size(); i++)
        {
            ssqX += Point2D(X0[i].x * X0[i].x, X0[i].y * X0[i].y);
            ssqY += Point2D(Y0[i].x * Y0[i].x, Y0[i].y * Y0[i].y);
        }

        Point2D epsX(pow(fabs(std::numeric_limits<RealType>::epsilon() *
                    X.size() * muX.x), 2),
                    pow(fabs(std::numeric_limits<RealType>::epsilon() *
                    X.size() * muX.y), 2));
        Point2D epsY(pow(fabs(std::numeric_limits<RealType>::epsilon() *
                    Y.size() * muY.x), 2),
                    pow(fabs(std::numeric_limits<RealType>::epsilon() *
                    Y.size() * muY.y), 2));
        bool constX = (ssqX.x <= epsX.x && ssqX.y <= epsX.y);
        bool constY = (ssqY.x <= epsY.x && ssqY.y <= epsY.y);

        if (!constX && !constY)
        {
            RealType normX = sqrt(ssqX.x + ssqX.y);
            RealType normY = sqrt(ssqY.x + ssqY.y);

            X0 /= Point2D(normX, normX);
            Y0 /= Point2D(normY, normY);

            RealMatrix xm0(X0.size(), 2), ym0(Y0.size(), 2);
            for (int i = 0; i < X0.size(); i++)
            {
                xm0(i, 0) = X0[i].x;
                xm0(i, 1) = X0[i].y;
                ym0(i, 0) = Y0[i].x;
                ym0(i, 1) = Y0[i].y;
            }

            RealMatrix A = xm0.t() * ym0;
            RealMatrix w, u, vt;
            cv::SVDecomp(A, w, u, vt);

            RealMatrix T = vt.t() * u.t();
            RealType trsqrtAA = cv::sum(w)[0];

            d = 1 - trsqrtAA * trsqrtAA;
            RealMatrix z = normX * trsqrtAA * ym0 * T;

            Z.resize(X0.size());
            for (int i = 0; i < Z.size(); i++)
            {
                Z[i] = Point2D(z(i, 0) + muX.x, z(i, 1) + muX.y);
            }
        }
        else if (constX)
        {
            d = 0;
            Z.resize(X.size(), muX);
        }
        else
        {
            d = 1;
            Z.resize(X.size(), muX);
        }
        
        return d;
    }

    void CommonFunctions::appPCA(const RealMatrix& data, RealMatrix& means,
            RealMatrix& eigenVectors, RealMatrix& eigenValues)
    {
        aam::RealMatrix covar;
        
        cv::calcCovarMatrix(data, covar, means, 
                CV_COVAR_COLS | CV_COVAR_SCRAMBLED | CV_COVAR_SCALE,
                OpenCVRealType::type);

        cv::Mat w, u, vt;
        cv::SVDecomp(covar, w, u, vt, cv::SVD::MODIFY_A);

        cv::Mat neiv = w / cv::sum(w)[0];
        aam::RealMatrix pc = data * u;

        for (int i = 0; i < pc.cols; i++)
        {
            RealType n = cv::norm(pc.col(i));
            pc.col(i) /= n;
        }

        eigenVectors = pc;
        eigenValues = neiv;
    }
}
