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
 * File:   FDHelper.h
 * Author: Иван Губочкин
 *
 * Created on 15 Октябрь 2012 г., 17:14
 */

#ifndef FDHELPER_H
#define	FDHELPER_H

#include "aam.h"
#include <opencv2/nonfree/nonfree.hpp>

namespace aam
{
    class FDHelper
    {
    public:
        FDHelper();
        virtual ~FDHelper();

        void detectKeyPoints(const cv::Mat& img, const cv::Mat& mask);
        std::vector<cv::KeyPoint> getKeyPoints();
        std::vector<cv::KeyPoint> getSampleKeyPoints();
        void setKeyPoints(const std::vector<cv::KeyPoint>& kp);
        void matchImages(const cv::Mat& img, const cv::Mat& mask);
        std::vector<cv::DMatch> getMatches();

    private:
        cv::SURF detector;
        std::vector<cv::KeyPoint> templateKeyPoints;
        std::vector<cv::KeyPoint> sampleKeyPoints;
        cv::Mat templateDescriptors;
        cv::Ptr<cv::DescriptorExtractor> extractor;
        std::vector<cv::DMatch> matches;
    };
}

#endif	/* FDHELPER_H */
