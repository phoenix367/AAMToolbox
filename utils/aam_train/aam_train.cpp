/*************************************************************************
 *
 * V5 SYSTEMS CONFIDENTIAL
 * __________________
 *
 *  [2013] - [2015] V5 Systems Incorporated
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of V5 Systems Incorporated and its suppliers,
 * if any.  The intellectual and technical concepts contained
 * herein are proprietary to V5 Systems Incorporated
 * and its suppliers and may be covered by U.S. and Foreign Patents,
 * patents in process, and are protected by trade secret or copyright law.
 * Dissemination of this information or reproduction of this material
 * is strictly forbidden unless prior written permission is obtained
 * from V5 Systems Incorporated.
 */

#include <memory>
#include <regex>

#include "tclap/CmdLine.h"
#include "aam/AAMEstimator.h"

std::string kModelGray = "gray", kModelColor = "color";
std::string kTrainConv = "conventional", kTrainIC = "inverse-composition";

std::vector<std::string> split(const std::string &s, char delim) {
    std::stringstream ss(s);
    std::string item;
    std::vector<std::string> elems;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    
    return elems;
}

// trim from start
static inline std::string &ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

// trim from both ends
static inline std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}

void removeQuotes(std::string& str) {
    if (str.size() >= 2) {
        if (str[0] == '"' && str[str.size() - 1] == '"') {
            str = str.substr(1, str.size() - 2);
        }
    }
}

bool loadModelInfo(const std::string& fileName,
        std::vector<aam::ModelPathType>& modelPaths,
        const std::string& basePath)
{
    std::ifstream stream(fileName.c_str());
    std::vector<std::string> strData;
    
    if (!stream)
    {
        return false;
    }

    while (!stream.eof())
    {
        std::string line;
        std::getline(stream, line);

        if (!line.empty())
        {
            strData = split(line, ',');

            if (strData.size() != 2)
            {
                std::cerr << "Bad format of line: " << line << std::endl;
            }
            else
            {
                std::string modelData = trim(strData[0]);
                removeQuotes(modelData);
                
                std::string modelImage = trim(strData[1]);
                removeQuotes(modelImage);
                
                if (!basePath.empty()) {
                    modelImage = basePath + "/" + modelImage;
                    modelData = basePath + "/" + modelData;
                }
                
                aam::ModelPathType modelPath(modelData, modelImage);
                modelPaths.push_back(modelPath);
            }
        }
    }

    stream.close();
    
    return true;
}

bool loadTriangles(const std::string& filePath, std::vector<cv::Vec3i>& triangles) {
    std::ifstream stream(filePath.c_str());
    std::vector<std::string> strData;
    
    if (!stream)
    {
        return false;
    }

    while (!stream.eof())
    {
        std::string line;
        std::getline(stream, line);

        if (!line.empty())
        {
            std::vector<std::string> strData = split(line, ',');
            
            if (strData.size() != 3 && strData.size() != 4) {
                std::cerr << "Bad format of line: " << line << std::endl;
            } else {
                std::string aStr = trim(strData[0]);
                std::string bStr = trim(strData[1]);
                std::string cStr = trim(strData[2]);
                
                size_t p;
                int a = std::stoi(aStr, &p);
                
                if (p != aStr.size() || aStr.empty()) {
                    std::cerr << "Invalid vertex A" << std::endl;
                    continue;
                }
                
                int b = std::stoi(bStr, &p);
                
                if (p != bStr.size() || bStr.empty()) {
                    std::cerr << "Invalid vertex B" << std::endl;
                    continue;
                }

                int c = std::stoi(cStr, &p);
                
                if (p != cStr.size() || cStr.empty()) {
                    std::cerr << "Invalid vertex C" << std::endl;
                    continue;
                }
                
                triangles.push_back(cv::Vec3i(a, b, c));
            }
        }
    }
    
    stream.close();
    
    return true;
}

int main(int argc, char* argv[]) {
    aam::AAMEstimator estimator;
    
    try {
        TCLAP::CmdLine cmd("AAM train utility", ' ', "0.1");
 
        TCLAP::ValueArg<double> pcaArg("p", "pca-cut-threshold", "PCA eigenvalues cutting threshold",
            false, 0.95, "double", cmd);
        
        std::vector<std::string> modelTypes = { kModelGray, kModelColor };
        TCLAP::ValuesConstraint<std::string> modelsContraint(modelTypes);
        TCLAP::ValueArg<std::string> colorArg("c", "color", "Train model color space",
                false, kModelColor, &modelsContraint, cmd);
        TCLAP::SwitchArg mtArg("m", "multithreaded", "Multithreaded AAM training",
                false);
        TCLAP::ValueArg<std::string> listArg("f", "file-list", "Path to list of model files",
                true, "", "string", cmd);
        TCLAP::ValueArg<std::string> basePathArg("b", "base-path", "Base path for model files",
                false, "", "string", cmd);
        TCLAP::ValueArg<std::string> outputArg("o", "output-model", "Output model files name",
                true, "", "string", cmd);
        TCLAP::ValueArg<std::string> trianglePathArg("t", "triangles-file", "Path to the file with initial model triangulation",
                false, "", "string", cmd);
        
        std::vector<std::string> algorithms = { kTrainConv, kTrainIC };
        TCLAP::ValuesConstraint<std::string> algContraint(algorithms);
        TCLAP::ValueArg<std::string> algorithmArg("a", "algorithm", "Training algorithm",
                false, kTrainConv, &algContraint, cmd);
        TCLAP::ValueArg<int> scalesArg("s", "pyr-scales", "Count of pyramid scales",
                false, 4, "positive integer", cmd);
           
        cmd.add(mtArg);
        
        // Parse the argv array.
        cmd.parse( argc, argv );
        
        double pcaCutThreshold = pcaArg.getValue();
        if (pcaCutThreshold <= 0.0 || pcaCutThreshold > 1.0) {
            std::cerr << "PCA cutting threshold should be > 0 and <= 1.0" << std::endl;
            return -1;
        }
        
        int nScales = scalesArg.getValue();
        if (nScales <= 0) {
            std::cerr << "Pyramid scales count should be positive" << std::endl;
            return -1;
        }
        
        aam::TrainOptions options;

        options.setPCACutThreshold(pcaCutThreshold);
        options.setScales(nScales);
        
        if (colorArg.getValue() == kModelColor) {
            options.setGrayScale(false);
        } else {
            options.setGrayScale(true);
        }
        
        std::vector<aam::ModelPathType> modelPaths;
        
        if (!loadModelInfo(listArg.getValue(), modelPaths, basePathArg.getValue())) {
            std::cerr << "Can't load model list file" << std::endl;
            return -1;
        }
        
        std::string trianglesPath = trianglePathArg.getValue();
        if (!trianglesPath.empty()) {
            std::vector<cv::Vec3i> triangles;
            if (!loadTriangles(trianglesPath, triangles)) {
                std::cerr << "Can't load triangles file" << std::endl;
                return -1;
            } else {
                options.setTriangles(triangles);
            }
        }
        
        options.setMultithreading(mtArg.getValue());
        
        aam::algorithm::AAMAlgorithm trainAlgorithm;

        if (algorithmArg.getValue() == kTrainConv) {
            trainAlgorithm = aam::algorithm::conventional;
        } else {
            trainAlgorithm = aam::algorithm::inverseComposition;
        }

        options.setAAMAlgorithm(trainAlgorithm);
        //options.setTriangles(triangles);

        estimator.setTrainOptions(options);

        std::cout << "Start model training..." << std::endl << std::endl;
        estimator.train(modelPaths);

        std::cout << "Save trained model...";
        estimator.save(outputArg.getValue());
        std::cout << " [done]" << std::endl;
    } catch (TCLAP::ArgException &e) {
        std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
    } catch (std::exception& e) {
        std::cerr << "unexpected exception: " << e.what() << std::endl;
    }
    
    return 0;
}
