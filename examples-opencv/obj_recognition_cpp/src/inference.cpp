/* Copyright (C) 2019 NXP Semiconductors
* See LICENSE file in the project root for full license information.
* Author:
* Rogerio Pimentel da Silva rogerio.silva@nxp.com
*
* SPDX-License-Identifier:    Apache-2.0
*
*/

#include "inference.hpp"

#include <thread>
#include <fstream>
#include <sstream>
#include <iostream>

#include <opencv2/dnn.hpp>
#include <opencv2/core/ocl.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <sys/time.h>

using namespace cv;
using namespace std;
using namespace dnn;

Inference::Inference(Mat *imgPtrArg){

    imgPtr = imgPtrArg;
    std::string model = "mobilenet_iter_73000.caffemodel";
    std::string config = "deploy.prototxt";

    std::string file = "classes.txt";
    std::ifstream ifs(file.c_str());
    std::string line;

    while (std::getline(ifs, line))
    classes.push_back(line);

    //Net net = readNetFromTensorflow(model, config);
    net = readNetFromCaffe(config, model);
}

void Inference::InferenceThread(){

  while(true){

    gettimeofday(&start, NULL);

    Mat inputBlob = blobFromImage(*imgPtr, 1.0f / 127.5, Size(224, 224), Scalar(127.5, 127.5, 127.5), true);

    net.setInput(inputBlob);

    Mat detection = net.forward();

    Mat detectionMat = Mat(detection.size[2], detection.size[3], CV_32F, detection.ptr<float>());
    gettimeofday(&end, NULL);
    std::cout << "Inference fps: " << 1/((end.tv_usec - start.tv_usec)* 1e-6) << std::endl;

    xLeftBottom = 0;
    yLeftBottom = 0;
    xRightTop = 0;
    yRightTop = 0;
    label = "";

    for(int i = 0; i < detectionMat.rows; i++) {
      float confidence = detectionMat.at<float>(i, 2);
      if(confidence > 0.6)
      {
          xLeftBottom = static_cast<int>(detectionMat.at<float>(i, 3) * (*imgPtr).cols);
          yLeftBottom = static_cast<int>(detectionMat.at<float>(i, 4) * (*imgPtr).rows);
          xRightTop = static_cast<int>(detectionMat.at<float>(i, 5) * (*imgPtr).cols);
          yRightTop = static_cast<int>(detectionMat.at<float>(i, 6) * (*imgPtr).rows);

          int classId = static_cast<int>(detectionMat.at<float>(i, 1));

          label = format("%s: %.4f", (classes.empty() ? format("Class #%d", classId).c_str() :  classes[classId].c_str()), confidence);
      }
    }
  }
}
