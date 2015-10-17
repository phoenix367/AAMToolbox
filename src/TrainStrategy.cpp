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

#include <opencv/cv.h>

#include "aam/TrainStrategy.h"
#include "aam/TrainConventional.h"
#include "aam/TrainIC2D.h"
#include "aam/TrainOptions.h"

namespace aam
{
    const char *TrainStrategy::AAM_ALGORITHM_TAG = "aam_algorithm";
    const char *TrainStrategy::AAM_COLOR_CHANNELS_TAG = "aam_color_channels";

    TrainStrategy::TrainStrategy()
    : colorChannels(0)
    {

    }

    TrainStrategy::~TrainStrategy()
    {
        
    }
    
    std::shared_ptr<TrainStrategy> TrainStrategy::load(
            const std::string& fileName)
    {
        std::shared_ptr<TrainStrategy> trainer;
        
        cv::FileStorage storage(fileName, cv::FileStorage::READ);

        if (!storage.isOpened())
        {
            throw FileNotFoundError();
        }

        int algType;

        if (storage[AAM_ALGORITHM_TAG].size() == 0)
        {
            throw InvalidModelFileException();
        }
        
        storage[AAM_ALGORITHM_TAG] >> algType;

        int ch;
        storage[AAM_COLOR_CHANNELS_TAG] >> ch;
        if (ch != 1 && ch != 3)
        {
            throw InvalidModelFileException();
        }

        switch (algType)
        {
            case algorithm::conventional:
                trainer = std::make_shared<TrainConventional>(ch);
                break;
            case algorithm::inverseComposition:
                trainer = std::make_shared<TrainIC2D>(ch);
                break;
            default:
                throw InvalidModelFileException();
        }

        trainer->load(storage);

        storage.release();

        return trainer;
    }

    void TrainStrategy::setOptions(const TrainOptions& newOptions)
    {
        this->options = newOptions;
    }

    std::shared_ptr<TrainStrategy> TrainStrategy::create(
        algorithm::AAMAlgorithm alg, int channels)
    {
        std::shared_ptr<TrainStrategy> ptr;

        switch (alg)
        {
            case algorithm::conventional:
                ptr = std::make_shared<TrainConventional>(channels);
                break;
            case algorithm::inverseComposition:
                ptr = std::make_shared<TrainIC2D>(channels);
                break;
            default:
                throw InternalException();
        }

        return ptr;
    }

    int TrainStrategy::getColorChannels()
    {
        return this->colorChannels;
    }
}
