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
 * File:   vector_op.h
 * Author: Иван Губочкин
 *
 * Created on 9 Август 2012 г., 17:07
 */

#ifndef VECTOR_OP_H
#define	VECTOR_OP_H

#include <vector>
#include <opencv/cv.h>

#include "aam.h"

namespace aam
{
    template<typename T> T mean(const std::vector<T>& v)
    {
        T sum = 0;

        for (int i = 0; i < v.size(); i++)
        {
            sum += v[i];
        }

        return sum / v.size();
    }

    static Point2D sum(const std::vector<Point2D>& v)
    {
        Point2D s;

        for (int i = 0; i < v.size(); i++)
        {
            s += v[i];
        }

        return s;
    }

    static Point2D mean(const std::vector<Point2D>& v)
    {
        Point2D s = aam::sum(v);

        s.x /= v.size();
        s.y /= v.size();

        return s;
    }

    static std::vector<Point2D>& operator /=(std::vector<Point2D>& a,
            Point2D b)
    {
        for (size_t i = 0; i < a.size(); i++)
        {
            a[i].x /= b.x;
            a[i].y /= b.y;
        }

        return a;
    }

    static std::vector<Point2D>& operator *=(std::vector<Point2D>& a,
            Point2D b)
    {
        for (size_t i = 0; i < a.size(); i++)
        {
            a[i].x *= b.x;
            a[i].y *= b.y;
        }

        return a;
    }

    template<typename T> std::vector<T>& operator /=(
        std::vector<T>& a, T b)
    {
        for (size_t i = 0; i < a.size(); i++)
        {
            a[i] /= b;
        }

        return a;
    }

    template<typename T> std::vector<T>& operator *=(
        std::vector<T>& a, T b)
    {
        for (size_t i = 0; i < a.size(); i++)
        {
            a[i] *= b;
        }

        return a;
    }

    template<typename T, typename U> std::vector<T> operator *(
        std::vector<T>& a, U b)
    {
        std::vector<T> r(a);
        for (size_t i = 0; i < a.size(); i++)
        {
            r[i] *= b;
        }

        return r;
    }

    template<typename T> std::vector<T>& operator +=(
        std::vector<T>& a, T b)
    {
        for (size_t i = 0; i < a.size(); i++)
        {
            a[i] += b;
        }

        return a;
    }

    template<typename T> std::vector<T>& operator +=(
        std::vector<T>& a, const std::vector<T>& b)
    {
        assert(a.size() == b.size());

        for (size_t i = 0; i < a.size(); i++)
        {
            a[i] += b[i];
        }

        return a;
    }

    template<typename T> std::vector<T>& operator -=(
        std::vector<T>& a, const std::vector<T>& b)
    {
        assert(a.size() == b.size());

        for (size_t i = 0; i < a.size(); i++)
        {
            a[i] -= b[i];
        }

        return a;
    }

    template<typename T, typename U> std::vector<T>& operator -=(
        std::vector<T>& a, U b)
    {
        for (size_t i = 0; i < a.size(); i++)
        {
            a[i] -= b;
        }

        return a;
    }

    template<typename T> std::vector<T> operator -(
        const std::vector<T>& a, const std::vector<T>& b)
    {
        assert(a.size() == b.size());

        std::vector<T> result(a.size());

        for (size_t i = 0; i < a.size(); i++)
        {
            result[i] = a[i] - b[i];
        }

        return result;
    }

    template<typename T> std::vector<T> operator +(
        const std::vector<T>& a, const std::vector<T>& b)
    {
        assert(a.size() == b.size());

        std::vector<T> result(a.size());

        for (size_t i = 0; i < a.size(); i++)
        {
            result[i] = a[i] + b[i];
        }

        return result;
    }

    template<typename T, typename U> std::vector<T> operator -(
        const std::vector<T>& a, U b)
    {
        std::vector<T> result(a.size());

        for (size_t i = 0; i < a.size(); i++)
        {
            result[i] = a[i] - b;
        }

        return result;
    }

    template<typename T, typename U> std::vector<T> operator /(
        const std::vector<T>& a, U b)
    {
        std::vector<T> result(a.size());

        for (size_t i = 0; i < a.size(); i++)
        {
            result[i] = a[i] / b;
        }

        return result;
    }

    template<typename U> std::vector<Point2D> operator /(
        const std::vector<Point2D>& a, U b)
    {
        std::vector<Point2D> result(a.size());

        for (size_t i = 0; i < a.size(); i++)
        {
            result[i].x = a[i].x / b;
            result[i].y = a[i].y / b;
        }

        return result;
    }

    template<typename T> std::vector<T> dist(
        const std::vector<cv::Point_<T> >& a)
    {
        std::vector<T> d(a.size());

        for (int i = 0; i < a.size(); i++)
        {
            cv::Point_<T> pt = a[i];
            d[i] = sqrt(pt.x * pt.x + pt.y * pt.y);
        }

        return d;
    }

    template<typename T> std::vector<cv::Point_<T> > convertVector(
        const Vertices2DList& list)
    {
        std::vector<cv::Point_<T> > result(list.size());

        for (int i = 0; i < list.size(); i++)
        {
            result[i].x = (T) list[i].x;
            result[i].y = (T) list[i].y;
        }

        return result;
    }

    template<typename T> T std(const cv::vector<T>& v)
    {
        T sum = 0;
        T m = mean(v);

        for (int i = 0; i < v.size(); i++)
        {
            sum += v[i] - m;
        }

        return sqrt(sum * sum / (v.size() - 1));
    }

    template<typename T> T var(const cv::vector<T>& v)
    {
        T sum = 0;
        T m = mean(v);

        for (int i = 0; i < v.size(); i++)
        {
            T d = v[i] - m;
            sum += d * d;
        }

        return (sum / (v.size() - 1));
    }

    template<typename T> cv::Point_<T> minCoords(const cv::vector<
        cv::Point_<T> >& v)
    {
        if (v.empty())
        {
            return cv::Point_<T>();
        }

        cv::Mat m(v);
        std::vector<cv::Mat> channels;
        cv::split(m, channels);
        
        cv::Mat_<T> colX = channels[0];
        cv::Mat_<T> colY = channels[1];

        cv::Point_<T> r;

        r.x = *std::min_element(colX.begin(), colX.end());
        r.y = *std::min_element(colY.begin(), colY.end());

        return r;
    }

    template<typename T> cv::Point_<T> maxCoords(const cv::vector<
        cv::Point_<T> >& v)
    {
        if (v.empty())
        {
            return cv::Point_<T>();
        }

        cv::Mat m(v);
        std::vector<cv::Mat> channels;
        cv::split(m, channels);

        cv::Mat_<T> colX = channels[0];
        cv::Mat_<T> colY = channels[1];

        cv::Point_<T> r;

        r.x = *std::max_element(colX.begin(), colX.end());
        r.y = *std::max_element(colY.begin(), colY.end());

        return r;
    }

    template<typename T> std::vector<cv::Point_<T> > mat2PointVector(
        const cv::Mat& m)
    {
        assert(m.cols == 1);

        int vs = m.rows / 2;
        std::vector<cv::Point_<T> > result(vs);

        for (int i = 0; i < vs; i++)
        {
            result[i].x = m.at<T>(i, 0);
            result[i].y = m.at<T>(i + vs, 0);
        }

        return result;
    }

    template<typename T> cv::Mat pointVector2Mat(
        const std::vector<cv::Point_<T> >& v)
    {
        cv::Mat_<T> result(v.size() * 2, 1);

        for (int i = 0; i < v.size(); i++)
        {
            result(i, 0) = v[i].x;
            result(i + v.size(), 0) = v[i].y;
        }

        return result;
    }
}

#endif	/* VECTOR_OP_H */
