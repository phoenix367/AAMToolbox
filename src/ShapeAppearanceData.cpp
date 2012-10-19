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

#include "aam/ShapeAppearanceData.h"
#include "aam/CommonFunctions.h"

namespace aam
{
    const char* ShapeAppearanceData::FIELD_SHAPE_APPEARANCE_EIGVALUES =
        "shape_appearance_eigvalues";
    const char* ShapeAppearanceData::FIELD_SHAPE_APPEARANCE_EIGVECTORS =
        "shape_appearance_eigvectors";
    const char* ShapeAppearanceData::FIELD_SHAPE_APPEARANCE_B_MEANS =
        "shape_appearance_b_means";
    const char* ShapeAppearanceData::FIELD_SHAPE_APPEARANCE_B =
        "shape_appearance_b";
    const char* ShapeAppearanceData::FIELD_SHAPE_APPEARANCE_W =
        "shape_appearance_w";

    void ShapeAppearanceData::save(cv::FileStorage& storage, int scale)
    {
        storage << CommonFunctions::combineScaleField(
                scale, FIELD_SHAPE_APPEARANCE_EIGVALUES) << this->eigValues;
        storage << CommonFunctions::combineScaleField(
                scale, FIELD_SHAPE_APPEARANCE_EIGVECTORS) << this->eigVectors;
        storage << CommonFunctions::combineScaleField(
                scale, FIELD_SHAPE_APPEARANCE_B_MEANS) << this->bMeans;
        storage << CommonFunctions::combineScaleField(
                scale, FIELD_SHAPE_APPEARANCE_B) << this->b;
        storage << CommonFunctions::combineScaleField(
                scale, FIELD_SHAPE_APPEARANCE_W) << this->w;
    }

    void ShapeAppearanceData::load(cv::FileStorage& storage, int scale)
    {
        storage[CommonFunctions::combineScaleField(
                scale, FIELD_SHAPE_APPEARANCE_EIGVALUES)] >> this->eigValues;
        storage[CommonFunctions::combineScaleField(
                scale, FIELD_SHAPE_APPEARANCE_EIGVECTORS)] >> this->eigVectors;
        storage[CommonFunctions::combineScaleField(
                scale, FIELD_SHAPE_APPEARANCE_B_MEANS)] >> this->bMeans;
        storage[CommonFunctions::combineScaleField(
                scale, FIELD_SHAPE_APPEARANCE_B)] >> this->b;
        storage[CommonFunctions::combineScaleField(
                scale, FIELD_SHAPE_APPEARANCE_W)] >> this->w;
    }

    bool ShapeAppearanceData::operator ==(
        const ShapeAppearanceData& shapeAppearance) const
    {
        if (this->eigValues.size != shapeAppearance.eigValues.size)
        {
            return false;
        }

        if (this->eigVectors.size != shapeAppearance.eigVectors.size)
        {
            return false;
        }

        if (this->b.size != shapeAppearance.b.size)
        {
            return false;
        }

        if (this->bMeans.size != shapeAppearance.bMeans.size)
        {
            return false;
        }

        if (this->w.size != shapeAppearance.w.size)
        {
            return false;
        }
        
        return (cv::countNonZero(
                    this->b != shapeAppearance.b) == 0) &&
               (cv::countNonZero(
                    this->bMeans != shapeAppearance.bMeans) == 0) &&
               (cv::countNonZero(
                    this->eigValues != shapeAppearance.eigValues) == 0) &&
               (cv::countNonZero(
                    this->eigVectors != shapeAppearance.eigVectors) == 0) &&
               (cv::countNonZero(
                    this->w != shapeAppearance.w) == 0);
    }
}
