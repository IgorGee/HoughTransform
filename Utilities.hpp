#ifndef UTILITIES_H
#define UTILITIES_H

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

bool argsH1Check(int argc) {
  if (argc != 3) {
    cout << "usage: ./h1 <input gray-level image> <output gray-level image>" << endl;
    return false;
  }
  return true;
}

bool argsH2Check(int argc) {
  if (argc != 4) {
    cout << "usage: ./h2 <input gray-level image> <input gray-level threshold> <output binary image>" << endl;
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
