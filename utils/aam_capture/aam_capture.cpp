/* Active Appearance Model toolbox
 * Copyright (C) 2015 Ivan Gubochkin
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

#include "tclap/CmdLine.h"
#include "aam/AAMEstimator.h"

#include <opencv2/opencv.hpp>

int main(int argc, char* argv[]) {
    try {
        TCLAP::CmdLine cmd("AAM live capture utility", ' ', "0.1");

        TCLAP::ValueArg<std::string> modelArg("m", "aam-model", "Active appearance model file",
                true, "", "string", cmd);
        TCLAP::ValueArg<std::string> cascadesArg("c", "haar-cascades", "Path to file with Haar cascades",
                true, "", "string", cmd);

        // Parse the argv array.
        cmd.parse( argc, argv );
        
        aam::AAMEstimator estimator;
        
        estimator.load(modelArg.getValue());

        cv::VideoCapture cap(0); // open the default camera
        if (!cap.isOpened()) {  // check if we succeeded
            std::cerr << "Can't open camera capture" << std::endl;
            return -1;
        }
        
        cv::CascadeClassifier classifier;
        if (!classifier.load(cascadesArg.getValue())) {
            std::cerr << "Can't load Haar cascades" << std::endl;
            return -1;
        }

        for(;;)
        {
            cv::Mat frame;
            cap >> frame; // get a new frame from camera
            
            cv::Mat grayFrame;
            cv::cvtColor(frame, grayFrame, CV_BGR2GRAY);
            
            std::vector<cv::Rect> objects;
            classifier.detectMultiScale(grayFrame, objects, 1.3, 5);
            
            for (size_t i = 0; i < objects.size(); i++) {
                aam::Vertices2DList foundPoints;
                estimator.estimateAAM(frame, aam::Point2D(objects[i].x + objects[i].width / 2,
                        objects[i].y + objects[i].height / 2), foundPoints);
                
                for (int j = 0; j < foundPoints.size(); j++)
                {
                    cv::circle(frame, foundPoints[j], 3, CV_RGB(255, 255, 255));
                }
                
                cv::rectangle(frame, objects[i], cv::Scalar(0, 255, 0), 3);
                
            }
            
            cv::imshow("edges", frame);
            if (cv::waitKey(30) >= 0) {
                break;
            }
        }
    } catch (TCLAP::ArgException &e) {
        std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
    } catch (std::exception& e) {
        std::cerr << "unexpected exception: " << e.what() << std::endl;
    }

    return 0;
}
