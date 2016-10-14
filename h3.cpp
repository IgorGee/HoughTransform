#include "Utilities.hpp"
#include "Filters.hpp"
#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;


int main(int argc, char *argv[]) {
  if (!argsH3Check(argc)) return -1;
  Mat image = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
  if (!imageValidityCheck(image)) return -1;
  CV_Assert(image.depth() == CV_8U);

  ofstream houghArrayOutput(argv[3]);

  int maxRho = sqrt(pow(image.rows, 2) + pow(image.cols, 2));
  int maxTheta = 180;
  double thetaIncrements = 0.25;
  int houghCols = maxTheta / thetaIncrements;

  vector< vector<int> > A(maxRho * 2, vector<int>(houghCols, 0));

  int maxVote = 0;
  for (int i = 0; i < image.rows; i++) {
    for (int j = 0; j < image.cols; j++) {
      if (image.at<uchar>(i, j)) {
        for (int t = 0; t < houghCols; t++) {
          double rho = getRho(i, j, t, thetaIncrements);
          int val = A[rho + maxRho][t]++;
          if (val > maxVote) maxVote = val;
        }
      }
    }
  }

  cout << "Max: " << maxVote << endl;

  Mat houghImage(A.size(), A[0].size(), CV_8U);

  // Scale for hough image and write out Accumulator as ascii txt
  for (int i = 0; i < A.size(); i++) {
    for (int j = 0; j < A[i].size(); j++) {
      houghArrayOutput << A[i][j] << " ";
      houghImage.at<uchar>(i, j) = (A[i][j] / (double) maxVote) * 255;
    }
    houghArrayOutput << endl;
  }
  houghArrayOutput.close();

  namedWindow("Original Image", WINDOW_AUTOSIZE);
  namedWindow("Hough Image", WINDOW_AUTOSIZE);

  imshow("Original Image", image);
  imshow("Hough Image", houghImage);

  waitKey(0);

  vector<int> params = { CV_IMWRITE_PXM_BINARY };
  imwrite(argv[2], houghImage, params);

  return 0;
}
