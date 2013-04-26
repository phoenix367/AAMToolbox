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
 * File:   AAMFunctions3D.cpp
 * Author: Иван Губочкин
 * 
 * Created on 23 Октябрь 2012 г., 16:27
 */

#include "aam/AAMFunctions3D.h"
#include "aam/Exceptions.h"

namespace aam
{
    void AAMFunctions3D::shapeMotionRecovery(
        const std::vector<Vertices2DList>& shapes,
            int np,
            RealMatrix& P, RealMatrix& c, RealMatrix& X,
            RealMatrix& M, RealMatrix& B, RealType K,
            RealType ratio)
    {
        assert(K > 0 && np > 0);
        
        RealMatrix W(2 * shapes.size(), np);
        RealMatrix W_mean = RealMatrix::zeros(W.rows, 1);

        for (int i = 0; i < shapes.size(); i++)
        {
            assert(np == shapes[i].size());
            
            for (int j = 0; j < np; j++)
            {
                W(2 * i, j) = shapes[i][j].x;
                W_mean(2 * i) += W(2 * i, j);

                W(2 * i + 1, j) = shapes[i][j].y;
                W_mean(2 * i + 1) += W(2 * i + 1, j);
            }
        }

        W_mean /= shapes.size();
        RealMatrix W_reg(W.rows, W.cols);
        for (int i = 0; i < W.rows; i++)
        {
            W_reg.row(i) = W.row(i) - W_mean(i);
        }

        RealMatrix U, S, Vt;
        cv::SVDecomp(W_reg, U, S, Vt, cv::SVD::MODIFY_A);

        if (K == 0)
        {
            int i = 1;
            while (S(0) / S(i) < ratio && i < S.rows - 1)
            {
                i++;
            }

            K = floor((i - 1) / 3);
        }

        int dim = 3 * K;

        if (dim > U.cols)
        {
            throw InternalException("K is too big. Either provide more useful"
                    "shape data or reduce its value.");
        }

        RealMatrix M_tilde = U.colRange(0, dim);
        std::vector<int> permutations;
        
        if (K > 2)
        {
            
        }
        else if (K == 2)
        {

        }
        else
        {
            
        }
    }
}
