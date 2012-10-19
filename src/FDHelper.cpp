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
 * File:   FDHelper.cpp
 * Author: Иван Губочкин
 * 
 * Created on 15 Октябрь 2012 г., 17:14
 */

#include "aam/FDHelper.h"

namespace aam
{
    FDHelper::FDHelper()
    : detector(1000)
    {
        this->extractor = cv::DescriptorExtractor::create(
                "BriefDescriptorExtractor");
    }

    FDHelper::~FDHelper()
    {
    }

    void FDHelper::detectKeyPoints(const cv::Mat& img,
            const cv::Mat& mask)
    {
        this->detector.detect(img, this->templateKeyPoints, mask);
        cv::SurfDescriptorExtractor extractor;
        extractor.compute(img, this->templateKeyPoints,
                this->templateDescriptors);
    }

    std::vector<cv::KeyPoint> FDHelper::getKeyPoints()
    {
        return this->templateKeyPoints;
    }

    void FDHelper::setKeyPoints(const std::vector<cv::KeyPoint>& kp)
    {
        this->templateKeyPoints = kp;
    }

    void FDHelper::matchImages(const cv::Mat& img, const cv::Mat& mask)
    {
        this->detector.detect(img, this->sampleKeyPoints, mask);
        
        cv::SurfDescriptorExtractor extractor;
        cv::Mat sampleDescriptors;
        extractor.compute(img, this->sampleKeyPoints, sampleDescriptors);

        cv::FlannBasedMatcher matcher;
        
        matcher.match(this->templateDescriptors, sampleDescriptors,
                this->matches);
    }

    std::vector<cv::DMatch> FDHelper::getMatches()
    {
        return this->matches;
    }

    std::vector<cv::KeyPoint> FDHelper::getSampleKeyPoints()
    {
        return this->sampleKeyPoints;
    }
}
