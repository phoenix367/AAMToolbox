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
 * File:   AppearanceDataIC.cpp
 * Author: Иван Губочкин
 * 
 * Created on 21 Сентябрь 2012 г., 23:59
 */

#include "aam/AppearanceDataIC.h"
#include "aam/CommonFunctions.h"
#include "aam/Exceptions.h"

namespace aam
{
    const char *AppearanceDataIC::FIELD_APPEARANCEIC_A0 =
        "appearance_ic_a0";
    const char *AppearanceDataIC::FIELD_APPEARANCEIC_A =
        "appearance_ic_a";
    const char *AppearanceDataIC::FIELD_APPEARANCEIC_R =
        "appearance_ic_r";
    const char *AppearanceDataIC::FIELD_APPEARANCEIC_S_STAR =
        "appearance_ic_s_star";
    const char *AppearanceDataIC::FIELD_APPEARANCEIC_S =
        "appearance_ic_s";
    const char *AppearanceDataIC::FIELD_APPEARANCEIC_S0 =
        "appearance_ic_s0";
    const char *AppearanceDataIC::FIELD_APPEARANCEIC_MASK =
        "appearance_ic_mask";
    const char *AppearanceDataIC::FIELD_APPEARANCEIC_TRIANGLES =
        "appearance_ic_triangles";
    const char *AppearanceDataIC::FIELD_APPEARANCEIC_TEXTURE_SIZE =
        "appearance_ic_texture_size";
    const char *AppearanceDataIC::FIELD_APPEARANCEIC_WARP_MAP =
        "appearance_ic_warp_map";
    const char *AppearanceDataIC::FIELD_COLOR_CHANNELS =
        "appearance_ic_color_channels";
    const char *AppearanceDataIC::FIELD_APPEARANCEIC_SD =
        "appearance_ic_sd";
    const char *AppearanceDataIC::FIELD_APPEARANCEIC_INV_H =
        "appearance_ic_inv_h";
    const char *AppearanceDataIC::FIELD_APPEARANCEIC_X_MEAN =
        "appearance_ic_x_mean";
    const char *AppearanceDataIC::FIELD_APPEARANCEIC_LAMBDA_S =
        "appearance_ic_lambda_s";
    const char *AppearanceDataIC::FIELD_APPEARANCEIC_LAMBDA_A =
        "appearance_ic_lambda_a";

    AppearanceDataIC::AppearanceDataIC()
    : nPixels(0)
    , colorChannels(0)
    {
    }

    AppearanceDataIC::~AppearanceDataIC()
    {
    }

    void AppearanceDataIC::save(cv::FileStorage& storage, int scale)
    {
        storage << CommonFunctions::combineScaleField(
                scale, FIELD_APPEARANCEIC_A0) << this->A0;
        storage << CommonFunctions::combineScaleField(
                scale, FIELD_APPEARANCEIC_A) << this->A;
        storage << CommonFunctions::combineScaleField(
                scale, FIELD_APPEARANCEIC_R) << this->R;
        storage << CommonFunctions::combineScaleField(
                scale, FIELD_APPEARANCEIC_S_STAR) << this->sStar;
        storage << CommonFunctions::combineScaleField(
                scale, FIELD_APPEARANCEIC_S) << this->s;
        storage << CommonFunctions::combineScaleField(
                scale, FIELD_APPEARANCEIC_S0) << this->s0;
        storage << CommonFunctions::combineScaleField(
                scale, FIELD_APPEARANCEIC_MASK) << this->mask;
        storage << CommonFunctions::combineScaleField(
                scale, FIELD_APPEARANCEIC_TRIANGLES) << this->triangles;
        storage << CommonFunctions::combineScaleField(
                scale, FIELD_APPEARANCEIC_WARP_MAP) << this->warpMap;
        storage << CommonFunctions::combineScaleField(
                scale, FIELD_COLOR_CHANNELS) << this->colorChannels;
        storage << CommonFunctions::combineScaleField(
                scale, FIELD_APPEARANCEIC_SD) << this->SD;
        storage << CommonFunctions::combineScaleField(
                scale, FIELD_APPEARANCEIC_INV_H) << this->invH;
        storage << CommonFunctions::combineScaleField(
                scale, FIELD_APPEARANCEIC_X_MEAN) << this->xMean;
        storage << CommonFunctions::combineScaleField(
                scale, FIELD_APPEARANCEIC_LAMBDA_S) << this->lambdaS;
        storage << CommonFunctions::combineScaleField(
                scale, FIELD_APPEARANCEIC_LAMBDA_A) << this->lambdaA;
    }

    void AppearanceDataIC::load(cv::FileStorage& storage, int scale)
    {
        storage[CommonFunctions::combineScaleField(
                scale, FIELD_APPEARANCEIC_A0)] >> this->A0;
        storage[CommonFunctions::combineScaleField(
                scale, FIELD_APPEARANCEIC_A)] >> this->A;
        storage[CommonFunctions::combineScaleField(
                scale, FIELD_APPEARANCEIC_R)] >> this->R;
        storage[CommonFunctions::combineScaleField(
                scale, FIELD_APPEARANCEIC_S_STAR)] >> this->sStar;
        storage[CommonFunctions::combineScaleField(
                scale, FIELD_APPEARANCEIC_S)] >> this->s;
        storage[CommonFunctions::combineScaleField(
                scale, FIELD_APPEARANCEIC_S0)] >> this->s0;
        storage[CommonFunctions::combineScaleField(
                scale, FIELD_APPEARANCEIC_MASK)] >> this->mask;
        storage[CommonFunctions::combineScaleField(
                scale, FIELD_APPEARANCEIC_TRIANGLES)] >> this->triangles;
        storage[CommonFunctions::combineScaleField(
                scale, FIELD_APPEARANCEIC_WARP_MAP)] >> this->warpMap;
        storage[CommonFunctions::combineScaleField(
                scale, FIELD_COLOR_CHANNELS)] >> this->colorChannels;
        storage[CommonFunctions::combineScaleField(
                scale, FIELD_APPEARANCEIC_SD)] >> this->SD;
        storage[CommonFunctions::combineScaleField(
                scale, FIELD_APPEARANCEIC_INV_H)] >> this->invH;
        storage[CommonFunctions::combineScaleField(
                scale, FIELD_APPEARANCEIC_X_MEAN)] >> this->xMean;
        storage[CommonFunctions::combineScaleField(
                scale, FIELD_APPEARANCEIC_LAMBDA_S)] >> this->lambdaS;
        storage[CommonFunctions::combineScaleField(
                scale, FIELD_APPEARANCEIC_LAMBDA_A)] >> this->lambdaA;

        if (this->mask.size != this->warpMap.size)
        {
            throw InvalidModelFileException();
        }

        this->textureSize = cv::Size(this->mask.cols, this->mask.rows);
        PiecewiseWarp::precomputeWarp(this->s0, this->triangles,
                this->textureSize, this->warpInfo);
        this->nPixels = cv::countNonZero(this->mask);
    }
}
