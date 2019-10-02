/* Copyright (C) 2019 NXP Semiconductors
* See LICENSE file in the project root for full license information.
* Author:
* Rogerio Pimentel da Silva rogerio.silva@nxp.com
*
* SPDX-License-Identifier:    Apache-2.0
*
*/

#include "displayvideo.hpp"
#include <thread>

#include <opencv2/dnn.hpp>
#include <opencv2/core/ocl.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <sys/time.h>

using namespace cv;
using namespace std;

DisplayVideo::DisplayVideo(){

}

void DisplayVideo::DisplayVideoThread(){

  while(true){
    gettimeofday(&end, NULL);
    std::cout << "Video fps: " << 1/((end.tv_usec - start.tv_usec)* 1e-6) << std::endl; // * 1e6
    gettimeofday(&start, NULL);

    cap >> img;

    Rect object((int)xLeftBottom, (int)yLeftBottom,
                (int)(xRightTop - xLeftBottom),
                (int)(yRightTop - yLeftBottom));

    rectangle(img, object, Scalar(0, 255, 0));

    int baseLine = 0;

    Size labelSize = getTextSize(label, FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);
    rectangle(img, Rect(Point(xLeftBottom, yLeftBottom - labelSize.height),
                          Size(labelSize.width, labelSize.height + baseLine)),
                          Scalar(255, 255, 255), cv::FILLED);
    putText(img, label, Point(xLeftBottom, yLeftBottom),
                          FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0,0,0));

    imshow("cam", img);
    waitKey(1);
  }
}
