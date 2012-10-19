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
 * File:   OptimHelper2D.h
 * Author: Иван Губочкин
 *
 * Created on 13 Сентябрь 2012 г., 16:26
 */

#ifndef OPTIMHELPER2D_H
#define	OPTIMHELPER2D_H

#include "dlib/matrix.h"

#include "aam.h"
#include "ShapeData.h"
#include "ShapeAppearanceData.h"

namespace aam
{
    class OptimHelper2D
    {
        public:
            OptimHelper2D(const RealMatrix& x, const ShapeData& sd,
                const ShapeAppearanceData& sad);
            virtual ~OptimHelper2D();

            double operator()(
                const dlib::matrix<RealType, 0, 1>& arg) const;
            
        private:
            const RealMatrix& x2;
            const ShapeData& shapeData;
            const ShapeAppearanceData& shapeAppearance;
            RealMatrix invW;
            RealMatrix xMean;
    };
}

#endif	/* OPTIMHELPER2D_H */
