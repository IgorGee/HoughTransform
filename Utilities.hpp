#ifndef UTILITIES_H
#define UTILITIES_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
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

bool argsH3Check(int argc) {
  if (argc != 4) {
    cout << "usage: ./h3 <input binary edge image> <output gray-level Hough image> <output Hough-voting-array>" << endl;
    return false;
  }
  return true;
}

bool argsH4Check(int argc) {
  if (argc != 5) {
    cout << "usage: ./h4 <input original gray-level image> <input Hough-voting-array> <input Hough threshold value> <output gray-level line image>" << endl;
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

vector< vector<int> > getHoughArray(ifstream &houghArray) {
  vector< vector<int> > A;

  string line;
  while (getline(houghArray, line)) {
    vector<int> temp;

    stringstream ss(line);
    int val;
    while (ss >> val) {
      temp.push_back(val);
    }

    A.push_back(temp);
  }

  return A;
}

#endif
