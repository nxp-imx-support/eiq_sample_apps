/* Copyright (C) 2019 NXP Semiconductors
* See LICENSE file in the project root for full license information.
* Author:
* Rogerio Pimentel da Silva rogerio.silva@nxp.com
*
* SPDX-License-Identifier:    Apache-2.0
*
*/

#include <iostream>
#include "inference.hpp"
#include "displayvideo.hpp"
#include <unistd.h>

#include <thread>

#include <opencv2/dnn.hpp>
#include <opencv2/core/ocl.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <sys/time.h>

using namespace std;
using namespace cv;


int main(int argc, const char *argv[])
{
    DisplayVideo video;

    video.cap.open("v4l2src device=/dev/video0 ! video/x-raw,width=640,height=480 ! appsink");
    video.cap >> video.img;
    Inference inf(&video.img);
    thread video_t(&DisplayVideo::DisplayVideoThread, &video);
    thread inference_t(&Inference::InferenceThread, &inf);

    while (1) {
        video.xLeftBottom = inf.xLeftBottom;
        video.yLeftBottom = inf.yLeftBottom;
        video.xRightTop = inf.xRightTop;
        video.yRightTop = inf.yRightTop;
        video.label = inf.label;
        usleep(100000);
      }

  return 0;
}
