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

#include "aam/ShapeData.h"
#include "aam/CommonFunctions.h"

namespace aam
{
    const char* ShapeData::FIELD_SHAPE_EIG_VECTORS =
        "shape_eig_vectors";
    const char* ShapeData::FIELD_SHAPE_EIG_VALUES =
        "shape_eig_values";
    const char* ShapeData::FIELD_SHAPE_MEAN_VERTICES =
        "shape_mean_vertices";
    const char* ShapeData::FILED_SHAPE_X =
        "shape_x";
    const char* ShapeData::FIELD_SHAPE_X_MEAN =
        "shape_x_mean";
    const char* ShapeData::FIELD_SHAPE_S_VARIANCE =
        "shape_s_variance";
    const char* ShapeData::FIELD_SHAPE_R_VARIANCE =
        "shape_r_variance";
    const char* ShapeData::FIELD_SHAPE_LINES =
        "shape_lines";
    const char* ShapeData::FIELD_SHAPE_TRIANGLES =
        "shape_triangles";
    const char* ShapeData::FIELD_SHAPE_TEXTURE_SIZE =
        "shape_texture_size";

    ShapeData::ShapeData()
    : sVariance(0)
    , rVariance(0)
    {

    }

    void ShapeData::save(cv::FileStorage& storage, int scale)
    {
        storage << CommonFunctions::combineScaleField(
                scale, FIELD_SHAPE_EIG_VECTORS) << this->eigVectors;
        storage << CommonFunctions::combineScaleField(
                scale, FIELD_SHAPE_EIG_VALUES) << this->eigValues;
        storage << CommonFunctions::combineScaleField(
                scale, FIELD_SHAPE_MEAN_VERTICES) << cv::Mat(
                    this->meanVertices);
        storage << CommonFunctions::combineScaleField(
                scale, FIELD_SHAPE_R_VARIANCE) << this->rVariance;
        storage << CommonFunctions::combineScaleField(
                scale, FIELD_SHAPE_S_VARIANCE) << this->sVariance;
        storage << CommonFunctions::combineScaleField(
                scale, FIELD_SHAPE_X_MEAN) << cv::Mat(this->xMean);
        storage << CommonFunctions::combineScaleField(
                scale, FIELD_SHAPE_LINES) << cv::Mat(this->lines);
        storage << CommonFunctions::combineScaleField(
                scale, FIELD_SHAPE_TRIANGLES) << cv::Mat(this->triangles);

        cv::Mat1i s(2, 1);
        s(0) = this->textureSize.width;
        s(1) = this->textureSize.height;
        storage << CommonFunctions::combineScaleField(
                scale, FIELD_SHAPE_TEXTURE_SIZE) << s;
    }

    void ShapeData::load(cv::FileStorage& storage, int scale)
    {
        storage[CommonFunctions::combineScaleField(
                scale, FIELD_SHAPE_EIG_VECTORS)] >> this->eigVectors;
        storage[CommonFunctions::combineScaleField(
                scale, FIELD_SHAPE_EIG_VALUES)] >> this->eigValues;

        cv::Mat v;
        storage[CommonFunctions::combineScaleField(
                scale, FIELD_SHAPE_MEAN_VERTICES)] >> v;
        this->meanVertices = v;
        
        storage[CommonFunctions::combineScaleField(
                scale, FIELD_SHAPE_R_VARIANCE)] >> this->rVariance;
        storage[CommonFunctions::combineScaleField(
                scale, FIELD_SHAPE_S_VARIANCE)] >> this->sVariance;
        storage[CommonFunctions::combineScaleField(
                scale, FIELD_SHAPE_X_MEAN)] >> v;
        this->xMean = v;
        
        storage[CommonFunctions::combineScaleField(
                scale, FIELD_SHAPE_LINES)] >> v;
        this->lines = v;
        
        storage[CommonFunctions::combineScaleField(
                scale, FIELD_SHAPE_TRIANGLES)] >> v;
        this->triangles = v;

        storage[CommonFunctions::combineScaleField(
                scale, FIELD_SHAPE_TEXTURE_SIZE)] >> v;
        this->textureSize.width = v.at<int>(0);
        this->textureSize.height = v.at<int>(1);
    }

    bool ShapeData::operator ==(const ShapeData& shapeData) const
    {
        return (cv::countNonZero(this->eigValues != shapeData.eigValues) == 0)
                &&
               (cv::countNonZero(this->eigVectors != shapeData.eigVectors) ==
                0) &&
               (this->lines == shapeData.lines) &&
               (this->meanVertices == shapeData.meanVertices) &&
               (this->rVariance == shapeData.rVariance) &&
               (this->sVariance == shapeData.sVariance) &&
               (this->textureSize == shapeData.textureSize);
    }
}
