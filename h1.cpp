#include "Utilities.hpp"
#include "Filters.hpp"
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;


int main(int argc, char *argv[]) {
  const int GSIZE = 7;
  const double GSIGMA = 3;
  vector< vector<double> > gKernel = createGaussian(GSIZE, GSIGMA);

  if (!argsH1Check(argc)) return -1;
  Mat image = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
  if (!imageValidityCheck(image)) return -1;
  Mat blurImage;

  CV_Assert(image.depth() == CV_8U);
  applyGaussian(image, blurImage, gKernel);

  Mat realGaussianImage;
  GaussianBlur(image, realGaussianImage, Size(7, 7), 3);

  namedWindow("Original Image", WINDOW_AUTOSIZE);
  namedWindow("Blur Image", WINDOW_AUTOSIZE);
  namedWindow("Real Gaussian Image", WINDOW_AUTOSIZE);

  imshow("Original Image", image);
  imshow("Blur Image", blurImage);
  imshow("Real Gaussian Image", realGaussianImage);

  waitKey(0);

  return 0;
}
