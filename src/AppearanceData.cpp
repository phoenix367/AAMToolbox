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

#include "aam/AppearanceData.h"
#include "aam/CommonFunctions.h"

namespace aam
{
    const char* AppearanceData::FIELD_APPEARANCE_BASE_POINTS =
        "appearance_base_points";
    const char* AppearanceData::FIELD_APPEARANCE_GRAY_VECTOR =
        "appearance_gray_vector";
    const char* AppearanceData::FIELD_APPEARANCE_OBJECT_PIXELS =
        "appearance_object_pixels";
    const char* AppearanceData::FIELD_APPEARANCE_NPIXELS =
        "appearance_npixels";
    const char* AppearanceData::FIELD_APPEARANCE_EIGVALUES =
        "appearance_eigvalues";
    const char* AppearanceData::FIELD_APPEARANCE_EIGVECTORS =
        "appearance_eigvectors";
    const char* AppearanceData::FIELD_APPEARANCE_GRAY_MEAN =
        "appearance_gray_mean";

    AppearanceData::AppearanceData()
    : nPixels(0)
    {

    }

    void AppearanceData::save(cv::FileStorage& storage, int scale)
    {
        storage << CommonFunctions::combineScaleField(
                scale, FIELD_APPEARANCE_BASE_POINTS) << cv::Mat(this->basePoints);
        storage << CommonFunctions::combineScaleField(
                scale, FIELD_APPEARANCE_EIGVALUES) << this->eigenValues;
        storage << CommonFunctions::combineScaleField(
                scale, FIELD_APPEARANCE_EIGVECTORS) << this->eigenVectors;
        storage << CommonFunctions::combineScaleField(
                scale, FIELD_APPEARANCE_GRAY_MEAN) << this->grayMean;
        storage << CommonFunctions::combineScaleField(
                scale, FIELD_APPEARANCE_GRAY_VECTOR) << this->grayVector;
        storage << CommonFunctions::combineScaleField(
                scale, FIELD_APPEARANCE_NPIXELS) << this->nPixels;
        storage << CommonFunctions::combineScaleField(
                scale, FIELD_APPEARANCE_OBJECT_PIXELS) << this->objectPixels;
    }

    void AppearanceData::load(cv::FileStorage& storage, int scale)
    {
        cv::Mat tmp;

        storage[CommonFunctions::combineScaleField(
                scale, FIELD_APPEARANCE_BASE_POINTS)] >> tmp;
        this->basePoints = tmp;
        
        storage[CommonFunctions::combineScaleField(
                scale, FIELD_APPEARANCE_EIGVALUES)] >> this->eigenValues;
        storage[CommonFunctions::combineScaleField(
                scale, FIELD_APPEARANCE_EIGVECTORS)] >> this->eigenVectors;
        storage[CommonFunctions::combineScaleField(
                scale, FIELD_APPEARANCE_GRAY_MEAN)] >> this->grayMean;
        storage[CommonFunctions::combineScaleField(
                scale, FIELD_APPEARANCE_GRAY_VECTOR)] >> this->grayVector;
        storage[CommonFunctions::combineScaleField(
                scale, FIELD_APPEARANCE_NPIXELS)] >> this->nPixels;
        storage[CommonFunctions::combineScaleField(
                scale, FIELD_APPEARANCE_OBJECT_PIXELS)] >> this->objectPixels;
    }

    bool AppearanceData::operator ==(const AppearanceData& appearance) const
    {
        if (this->eigenValues.size != appearance.eigenValues.size)
        {
            return false;
        }

        if (this->eigenVectors.size != appearance.eigenVectors.size)
        {
            return false;
        }

        if (this->grayMean.size != appearance.grayMean.size)
        {
            return false;
        }

        if (this->grayVector.size != appearance.grayVector.size)
        {
            return false;
        }

        if (this->objectPixels.size != appearance.objectPixels.size)
        {
            return false;
        }
        
        return (this->basePoints == appearance.basePoints) &&
               (this->nPixels == appearance.nPixels) &&
               (cv::countNonZero(
                    this->eigenValues != appearance.eigenValues) == 0) &&
               (cv::countNonZero(
                    this->eigenVectors != appearance.eigenVectors) == 0) &&
               (cv::countNonZero(
                    this->grayMean != appearance.grayMean) == 0) &&
               (cv::countNonZero(
                    this->grayVector != appearance.grayVector) == 0) &&
               (cv::countNonZero(
                    this->objectPixels != appearance.objectPixels) == 0);
    }
}
