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
 * File:   AAMFunctions3D.h
 * Author: Иван Губочкин
 *
 * Created on 23 Октябрь 2012 г., 16:27
 */

#ifndef AAMFUNCTIONS3D_H
#define	AAMFUNCTIONS3D_H

#include "aam.h"

namespace aam
{
    class AAMFunctions3D
    {
    public:
        static void shapeMotionRecovery(
            const std::vector<Vertices2DList>& shapes,
                int np,
                RealMatrix& P, RealMatrix& c, RealMatrix& X,
                RealMatrix& M, RealMatrix& B, RealType K = 0,
                RealType ratio = 100);

    private:

    };
}

#endif	/* AAMFUNCTIONS3D_H */
