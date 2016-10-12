#ifndef UTILITIES_H
#define UTILITIES_H

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

bool argsH1Check(int argc) {
  if (argc != 2) {
    cout << "usage: ./DisplayImage <Image_Path>" << endl;
    return false;
  }
  return true;
}

bool imageValidityCheck(Mat &image) {
  if (!image.data) {
    cout << "No image data " << endl;
    return false;
  }
  return true;
}

#endif
