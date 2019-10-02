/* Copyright (C) 2019 NXP Semiconductors
* See LICENSE file in the project root for full license information.
* Author:
* Rogerio Pimentel da Silva rogerio.silva@nxp.com
*
* SPDX-License-Identifier:    Apache-2.0
*
*/

#include <iostream>
#include <thread>

#include <opencv2/dnn.hpp>
#include <opencv2/core/ocl.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <sys/time.h>

using namespace cv;

class DisplayVideo{

struct timeval start, end;

public:

  Mat img;
  VideoCapture cap;
  int xLeftBottom;
  int yLeftBottom;
  int xRightTop;
  int yRightTop;
  std::string label;

  DisplayVideo();
  void DisplayVideoThread();

};
