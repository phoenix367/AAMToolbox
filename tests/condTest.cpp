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
 * File:   condTest.cpp
 * Author: Ivan Gubochkin <jhng@yandex.ru>
 *
 * Created on 26.10.2012, 18:04:24
 */

#include <stdlib.h>
#include <iostream>

#include "aam/CommonFunctions.h"

#define ROWS_COUNT          6
#define COLUMNS_COUNT       66

bool loadVector(const std::string& fileName, int rows,
        int columns, aam::RealMatrix& target)
{
    cv::Mat1d result(rows, columns);

    FILE *in = fopen(fileName.c_str(), "rb");
    if (in == NULL)
    {
        return false;
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (fread(result.ptr(i, j), sizeof(double), 1, in) != 1)
            {
                fclose(in);
                return false;
            }
        }
    }

    target = result;

    fclose(in);
    return true;
}

/*
 * Simple C++ Test Suite
 */

void testCond()
{
    std::cout << "condTest testCond" << std::endl;

    aam::RealMatrix A;
    if (!loadVector("data/cond_A.raw", ROWS_COUNT, COLUMNS_COUNT, A))
    {
        std::cout << "%TEST_FAILED% time=0 testname=testCond (condTest) message=Can't load source matrix" << std::endl;
        return;
    }

    try
    {
        aam::RealType n = aam::CommonFunctions::cond(A);

        if (fabs(n - 1686.0076855698678) > 1e-10)
        {
            std::cout << "%TEST_FAILED% time=0 testname=testCond (condTest) message=Invalid condition number" << std::endl;
        }
    }
    catch (std::exception& e)
    {
        std::cout << "%TEST_FAILED% time=0 testname=testCond (condTest) message=Exception occured: " <<
                e.what() << std::endl;
    }
}

int main(int argc, char** argv)
{
    std::cout << "%SUITE_STARTING% condTest" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% testCond (condTest)" << std::endl;
    testCond();
    std::cout << "%TEST_FINISHED% time=0 testCond (condTest)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}
