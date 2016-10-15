#include "Utilities.hpp"
#include "Filters.hpp"
#include <cstdlib>
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;


int main(int argc, char *argv[]) {
  /* if (!argsH4Check(argc)) return -1; */
  Mat image = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
  if (!imageValidityCheck(image)) return -1;
  CV_Assert(image.depth() == CV_8U);

  ifstream houghArray(argv[2]);
  int threshold = atoi(argv[3]);

  vector< vector<int> > A = getHoughArray(houghArray);

  cout << "A.size(): " << A.size() << " A[0].size(): " << A[0].size() << endl;
  for (int i = 0; i < A.size(); i++) {
    for (int j = 0; j < A[i].size(); j++) {
      if (A[i][j] > threshold) {
        int rho = i - A.size()/2;
        double theta = ((double) j / A[0].size()) * 180;
        // if theta around 90, you should find x given a y instead
        int x0 = 0;
        int y0 = getYFromRhoTheta(image, rho, theta, x0);
        int x1 = image.cols - 1;
        int y1 = getYFromRhoTheta(image, rho, theta, x1);

        line(image, Point(x0, y0), Point(x1, y1), 255);
      }
    }
  }

  namedWindow("Original Image", WINDOW_AUTOSIZE);
  /* namedWindow("Edge Image", WINDOW_AUTOSIZE); */

  imshow("Original Image", image);
  /* imshow("Edge Image", edges); */

  waitKey(0);

  vector<int> params = { CV_IMWRITE_PXM_BINARY };
  /* imwrite(argv[4], image, params); */

  return 0;
}
