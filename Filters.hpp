#ifndef FILTERS_H
#define FILTERS_H

#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

double getGaussianValue(int x, int y, double sigma) {
  const double twoSigmaSquared = 2.0 * sigma * sigma;
  const double twoPiSigmaSquared = 2.0 * M_PI * sigma * sigma;

  double exponent = -(x*x + y*y)/twoSigmaSquared;
  return exp(exponent)/twoPiSigmaSquared;
}

vector< vector<double> > createGaussian(int size, double sigma) {
  int halfSize = size/2;
  double sum = 0;

  vector< vector<double> > kernel(size, vector<double>(size));

  // Fill up kernel with Gaussian formula
  for (int i = -halfSize; i <= halfSize; i++) {
    for (int j = -halfSize; j <= halfSize; j++) {
      double value = getGaussianValue(i, j, sigma);
      kernel[i+halfSize][j+halfSize] = value;
      sum += value;
    }
  }

  // normalize
  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++)
      kernel[i][j] /= sum;

  return kernel;
}

int getGaussianConvolution(Mat &image, int x, int y, vector< vector<double> > gKernel) {
  int value = 0;
  int halfSize = gKernel.size()/2;

  for (int i = -halfSize; i <= halfSize; i++) {
    for (int j = -halfSize; j <= halfSize; j++) {
      value += gKernel[i+halfSize][j+halfSize] * image.at<uchar>(x + i, y + j);
    }
  }

  return value;
}

void applyGaussian(Mat &src, Mat &dest, vector< vector<double> > gKernel) {
  dest.create(src.size(), src.type());

  int margin = gKernel.size()/2;
  for (int i = margin; i < src.rows - margin; i++) {
    for (int j = margin; j < src.cols - margin; j++) {
      /* if (src.at<uchar>(i, j) > 140) src.at<uchar>(i,j) = 255; */
      /* else src.at<uchar>(i,j) = 0; */

      int intensity = getGaussianConvolution(src, i, j, gKernel);
      dest.at<uchar>(i, j) = intensity;
    }
  }
}

#endif
