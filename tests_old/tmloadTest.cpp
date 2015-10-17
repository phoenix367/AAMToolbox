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
 * File:   tmloadTest.cpp
 * Author: Иван Губочкин
 *
 * Created on 08.08.2012, 17:11:23
 */

#include <stdlib.h>
#include <iostream>

#include "aam/TrainModelLoader.h"

/*
 * Simple C++ Test Suite
 */

void testLoad()
{
    std::cout << "tmloadTest testLoad" << std::endl;

    aam::TrainModelLoader loader(58);

    try
    {
        loader.load("data/IMM/01-1m.dat", "data/IMM/01-1m.jpg");

        if (loader.getModelsCount() != 1)
        {
            std::cout << "%TEST_FAILED% time=0 testname=testLoad (tmloadTest) message=Invalid model count" << std::endl;
        }
        else
        {
            loader.clear();

            if (loader.getModelsCount() != 0)
            {
                std::cout << "%TEST_FAILED% time=0 testname=test2 (tmloadTest) message=Can't clear loaded models" << std::endl;
            }
        }
    }
    catch (std::exception& e)
    {
        std::cout << "%TEST_FAILED% time=0 testname=testLoad (tmloadTest) message=Exception occured: " <<
                e.what() << std::endl;
    }
}

int main(int argc, char** argv)
{
    std::cout << "%SUITE_STARTING% tmloadTest" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% testLoad (tmloadTest)" << std::endl;
    testLoad();
    std::cout << "%TEST_FINISHED% time=0 testLoad (tmloadTest)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}
