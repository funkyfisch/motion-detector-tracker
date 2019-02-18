#include "opencv2/imgproc.hpp"
#include "include/MotionDetector.h"
#include <iostream>

using namespace std;
using namespace cv;

float differenceThreshold = 30;

int determineMotionRegion(float avgX, float avgY, int width, int height) {
  // first row regions
  if (avgY < height/3) {  
    if (avgX < width/3) return 1;
    else if (avgX < 2*width/3) return 2;
    else if (avgX > 2*width/3) return 3;
  }
  // second row regions
  else if (avgY < 2*height/3) {
    if (avgX < width/3) return 4;
    else if (avgX < 2*width/3) return 5;
    else if (avgX > 2*width/3) return 6;
  }
  // third row regions
  else if (avgY > 2*height/3) {
    if (avgX < width/3) return 7;
    else if (avgX < 2*width/3) return 8;
    else if (avgX > 2*width/3) return 9;
  }
}

Mat motionDetectBW(Mat oldFrame, Mat newFrame, Mat displayFrame, bool *motionDetected, int *region) {

  int count = 0;
  float avgX = 0;
  float avgY = 0;
  //TODO:add a bit of blurring to counteract noise, when very underexposed only, to both images
  int width = oldFrame.cols;
  int height = oldFrame.rows;

  for(int i = 0; i < height; i++) {
    for(int j = 0; j < width; j++) {
      // paint grid
      
      float oldPixel = (float) oldFrame.at<uchar>(i, j);
      float newPixel = (float) newFrame.at<uchar>(i, j);
      float distanceSquared = (oldPixel - newPixel)*(oldPixel - newPixel);
      if ( distanceSquared > differenceThreshold*differenceThreshold) {
        displayFrame.at<uchar>(i, j) = 255;
        count++;
        avgX += j;
        avgY += i;
      } else if ((i == height/3 || i == 2*height/3) || (j == width/3 || j == 2*width/3)) {
        displayFrame.at<uchar>(i, j) = 255;

      } else {
        displayFrame.at<uchar>(i, j) = newFrame.at<uchar>(i, j);
      }
    }
  }

  if(count > 100) {
    avgX /= count;
    avgY /= count;
    *region = determineMotionRegion(avgX, avgY, width, height);
    cout << "Motion Detected at region " << *region << endl;
    *motionDetected = true;
    circle(displayFrame, Point(avgX, avgY), 30, Scalar(100, 0, 200), 20, 8, 0);
  } else {
    *motionDetected = false;
  }
  return displayFrame;
}

