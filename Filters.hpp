#ifndef FILTERS_H
#define FILTERS_H

#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

double getLoGValue(int x, int y, double sigma) {
  const double twoSigmaSquared = 2.0 * sigma * sigma;
  const double twoPiSigmaSquared = 2.0 * M_PI * sigma * sigma;

  double exponent = (pow(x, 2) + pow(y, 2))/twoSigmaSquared;
  double coefficient = (exponent - 1)/(M_PI * pow(sigma, 4));
  return coefficient * exp(-exponent);
}

vector< vector<double> > createLoG(int size, double sigma) {
  int halfSize = size/2;
  double sum = 0;

  vector< vector<double> > kernel(size, vector<double>(size));

  // Fill up kernel with Laplacian of Gaussian formula
  for (int i = -halfSize; i <= halfSize; i++) {
    for (int j = -halfSize; j <= halfSize; j++) {
      double value = getLoGValue(i, j, sigma);
      kernel[i+halfSize][j+halfSize] = value;
      sum += value;
    }
  }

  return kernel;
}

int getLoGConvolution(Mat &image, int x, int y, vector< vector<double> > logKernel) {
  int value = 0;
  int halfSize = logKernel.size()/2;

  for (int i = -halfSize; i <= halfSize; i++) {
    for (int j = -halfSize; j <= halfSize; j++) {
      value += logKernel[i+halfSize][j+halfSize] * (double)image.at<uchar>(x + i, y + j);
    }
  }

  return value;
}

void applyLoG(Mat &src, Mat &dest, vector< vector<double> > logKernel) {
  dest.create(src.size(), CV_8S);

  int margin = logKernel.size()/2;
  for (int i = margin; i < src.rows - margin; i++) {
    for (int j = margin; j < src.cols - margin; j++) {
      int intensity = getLoGConvolution(src, i, j, logKernel);
      dest.at<char>(i, j) = intensity;
    }
  }
}

void applyBinary(Mat &src, Mat &dest, int threshold) {
  dest.create(src.size(), src.type());

  for (int i = 0; i < src.rows; i++) {
    for (int j = 0; j < src.cols; j++) {
      if (src.at<uchar>(i, j) > threshold) dest.at<uchar>(i,j) = 255;
      else dest.at<uchar>(i,j) = 0;
    }
  }
}

double getRho(int x, int y, double theta, double increments) {
  theta *= increments;
  double rad = theta * M_PI/180;
  double rho = x * cos(rad) + y * sin(rad);
  return rho;
}

int getYFromRhoTheta(Mat &src, int rho, double theta, int x) {
  cout << "rho: " << rho << " theta: " << theta << endl;
  double rad = theta * M_PI/180;
  int y = (rho - x * cos(rad))/sin(rad);
  return y;
}

#endif
