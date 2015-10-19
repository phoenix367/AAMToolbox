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
#include "gtest/gtest.h"
#include "test_config.h"

/*
 * Simple C++ Test Suite
 */

TEST(Load, testLoad)
{
    aam::TrainModelLoader loader(58);

    std::ostringstream pathStream;
    pathStream << AAM_TEST_DATA_PATH << "/IMM/01-1m.dat";
    
    std::string dataPath = pathStream.str();
    pathStream.str(std::string());
    
    pathStream << AAM_TEST_DATA_PATH << "/IMM/01-1m.jpg";
    std::string imagePath = pathStream.str();
    
    loader.load(dataPath, imagePath);

    EXPECT_EQ(loader.getModelsCount(), 1);
    loader.clear();

    EXPECT_EQ(loader.getModelsCount(), 0);
}
