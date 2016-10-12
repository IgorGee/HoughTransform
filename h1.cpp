#include "Utilities.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char *argv[]) {
  if (!argsH1Check(argc)) return -1;
  Mat image = imread(argv[1], 1);
  if (!imageValidityCheck(image)) return -1;

  Mat blurImage;
  Mat cannyImage;
  GaussianBlur(image, blurImage, Size(15, 15), 1);
  Canny(blurImage, cannyImage, 10, 30);

  namedWindow("Original Image", WINDOW_AUTOSIZE);
  namedWindow("Blur Image", WINDOW_AUTOSIZE);
  namedWindow("Canny Image", WINDOW_AUTOSIZE);

  imshow("Original Image", image);
  imshow("Blur Image", blurImage);
  imshow("Canny Image", cannyImage);

  waitKey(0);

  return 0;
}
