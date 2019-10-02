/* Copyright (C) 2019 NXP Semiconductors
* See LICENSE file in the project root for full license information.
* Author:
* Rogerio Pimentel da Silva rogerio.silva@nxp.com
*
* SPDX-License-Identifier:    Apache-2.0
*
*/

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

class Inference{

std::vector<std::string> classes;

Net net;
struct timeval start, end;

public:

  Mat *imgPtr;

  int xLeftBottom;
  int yLeftBottom;
  int xRightTop;
  int yRightTop;
  std::string label;

  Inference(Mat *imgPtr);
  void InferenceThread();

};
