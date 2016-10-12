#ifndef FILTERS_H
#define FILTERS_H

#include <cmath>
#include <iostream>

double getGaussianValue(int x, int y, double sigma) {
  const double twoSigmaSquared = 2.0 * sigma * sigma;
  const double twoPiSigmaSquared = 2.0 * M_PI * sigma * sigma;

  double exponent = -(x*x + y*y)/twoSigmaSquared;
  return exp(exponent)/twoPiSigmaSquared;
}

double** createGaussian(int size, double sigma) {
  int halfSize = size/2;
  double sum = 0;

  double** kernel = new double*[size];

  // Fill up kernel with Gaussian formula
  for (int i = -halfSize; i <= halfSize; i++) {
    kernel[i+halfSize] = new double[size];

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

#endif
