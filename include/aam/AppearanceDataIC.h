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
 * File:   AppearanceDataIC.h
 * Author: Иван Губочкин
 *
 * Created on 21 Сентябрь 2012 г., 23:59
 */

#ifndef APPEARANCEDATAIC_H
#define	APPEARANCEDATAIC_H

#include "aam.h"
#include "PiecewiseWarp.h"

namespace aam
{
    class AppearanceDataIC
    {
    public:
        RealMatrix A0;
        RealMatrix A;
        RealMatrix R;
        RealMatrix sStar;
        RealMatrix s;
        RealMatrix xMean;
        RealMatrix lambdaS; // Shape eigen values
        RealMatrix lambdaA; // Appearance eigen value
        Vertices2DList s0;
        cv::Mat1b mask;
        int nPixels;
        std::vector<cv::Vec3i> triangles;
        cv::Size textureSize;
        cv::Mat1i warpMap;
        int colorChannels;
        RealMatrix SD;
        RealMatrix invH;
        PiecewiseWarp::WarpInfo warpInfo;
        
    public:
        AppearanceDataIC();
        virtual ~AppearanceDataIC();

        void save(cv::FileStorage& storage, int scale);
        void load(cv::FileStorage& storage, int scale);
        
    private:
        static const char *FIELD_APPEARANCEIC_A0;
        static const char *FIELD_APPEARANCEIC_A;
        static const char *FIELD_APPEARANCEIC_R;
        static const char *FIELD_APPEARANCEIC_S_STAR;
        static const char *FIELD_APPEARANCEIC_S;
        static const char *FIELD_APPEARANCEIC_S0;
        static const char *FIELD_APPEARANCEIC_MASK;
        static const char *FIELD_APPEARANCEIC_TRIANGLES;
        static const char *FIELD_APPEARANCEIC_TEXTURE_SIZE;
        static const char *FIELD_APPEARANCEIC_WARP_MAP;
        static const char *FIELD_COLOR_CHANNELS;
        static const char *FIELD_APPEARANCEIC_SD;
        static const char *FIELD_APPEARANCEIC_INV_H;
        static const char *FIELD_APPEARANCEIC_X_MEAN;
        static const char *FIELD_APPEARANCEIC_LAMBDA_S;
        static const char *FIELD_APPEARANCEIC_LAMBDA_A;
    };
}

#endif	/* APPEARANCEDATAIC_H */
