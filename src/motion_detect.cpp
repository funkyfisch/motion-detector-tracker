#include "opencv2/imgproc.hpp"
#include "motion_detect.h"
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

Mat motionDetectBW(Mat oldFrame, Mat newFrame, Mat displayFrame, bool *motionDetected) {

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
    int region;
    avgX /= count;
    avgY /= count;
    region = determineMotionRegion(avgX, avgY, width, height);
    cout << "Motion Detected at region " << region << endl;
    pointCameraTowards(region);
    *motionDetected = true;
    circle(displayFrame, Point(avgX, avgY), 30, Scalar(100, 0, 200), 20, 8, 0);
  } else {
    *motionDetected = false;
  }
  return displayFrame;
}

void pointCameraTowards(int quarter) {
  switch(quarter)
  case 1:
  //panright(),pitchup();
  case 2:
  //panright(),pitchdown();
  case 3:
  //panleft(), pitchdown();
  case 4:
  //panleft(), pitchup();
  default:
    return;
  return;
}

//bool motionDetect(vector<Mat> oldRgb, vector<Mat> newRgb) {
//  int count = 0;
//  for(int i = 0; i < oldRgb.rows; i++) {
//    for(int j = 0; j < oldRgb.cols; j++) {
//      float oldRed = (float) oldRgb[0].at<uchar>(i,j);
//      float oldGreen = (float) oldRgb[1].at<uchar>(i,j);
//      float oldBlue = (float) oldRgb[2].at<uchar>(i,j);
//      float newRed = (float) newRgb[0].at<uchar>(i,j);
//      float newGreen = (float) newRgb[1].at<uchar>(i,j);
//      float newBlue = (float) newRgb[2].at<uchar>(i,j);
//
//      float d = distSq(oldRed, oldGreen, oldBlue, newRed, newGreen, newBlue);
//
//      if (d > differenceThreshold*differenceThreshold) {
//        count++;
//      }
//    }
//  }
//  if(count > 100) {
//    return true;
//  }
//  return false;
//}

//float distSq(float x1, float y1, float z1, float x2, float y2, float z2) {
//  return (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1) + (z2-z1)*(z2-z1);

//}
