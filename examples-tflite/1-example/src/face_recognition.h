/* Copyright 2017 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#ifndef FACE_RECOGNITION_H_
#define FACE_RECOGNITION_H_

#include <string.h>
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

using namespace cv;

namespace tflite {
namespace facerec {

struct Settings {
  bool verbose = false;
  bool accel = false;
  bool profiling = false;
  int camera = 1;
  int number_of_threads = 1;
  float threshold = 0.852;
  std::string model_name = "./mfn.tflite";
  std::string data_dir = "data/";
};

void add_new_face(Mat img, std::string label, Settings *s);

}  // namespace facerec
}  // namespace tflite

#endif  // FACE_RECOGNITION_H_
