#include "Utilities.hpp"
#include "Filters.hpp"
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;


int main(int argc, char *argv[]) {
  const int LOGSIZE = 7;
  const double LOGSIGMA = 1;
  vector< vector<double> > logKernel = createLoG(LOGSIZE, LOGSIGMA);

  if (!argsH1Check(argc)) return -1;
  Mat image = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
  if (!imageValidityCheck(image)) return -1;
  Mat logImage;

  CV_Assert(image.depth() == CV_8U);
  applyLoG(image, logImage, logKernel);

  namedWindow("Original Image", WINDOW_AUTOSIZE);
  namedWindow("LoG Image", WINDOW_AUTOSIZE);

  imshow("Original Image", image);
  imshow("LoG Image", logImage);

  waitKey(0);

  vector<int> params = { CV_IMWRITE_PXM_BINARY };
  imwrite(argv[2], logImage, params);

  return 0;
}
