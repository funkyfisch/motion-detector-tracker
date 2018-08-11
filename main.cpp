#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <time.h>
#include <chrono>
#include <iostream>

using namespace std;
using namespace cv;
using namespace std::chrono;

const int fps = 30;
const float differenceThreshold = 20;
const int brightness_slider_max = 2*1000;
const int contrast_slider_max = 2*1000;
const int gain_slider_max = 2*1000;
const int exposure_slider_max = 8*1000;

Mat motionDetectBW(Mat, Mat, Mat, bool*);
void pointCameraTowards(int);

int main(int, char**) {
  int brightness = 340;
  int contrast = 0;
  int gain = 0;
  int exposure = 5000;
  bool recording = false;

  int start = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
  int stop = start;

  VideoCapture vid(0); // open the default camera
  int outputWidth = vid.get(CV_CAP_PROP_FRAME_WIDTH);
  int outputHeight = vid.get(CV_CAP_PROP_FRAME_HEIGHT);
  vid.set(CAP_PROP_AUTO_EXPOSURE, 0.25);
  if(!vid.isOpened()) {
    return -1;
  }


  Mat edges;
  namedWindow("display",1);
  Mat newFrame;
  Mat oldFrame;
  vid >> oldFrame;
  VideoWriter video("out.avi", CV_FOURCC('M', 'J', 'P', 'G'), 20, Size(oldFrame.cols, oldFrame.rows), true);
  bool motionDetected;
  //cvtColor(oldFrame, oldFrame, COLOR_BGR2GRAY);
  createTrackbar("brightness", "display", &brightness, brightness_slider_max );
  createTrackbar("contrast", "display", &contrast, contrast_slider_max );
  createTrackbar("gain", "display", &gain, gain_slider_max );
  createTrackbar("exposure", "display", &exposure, exposure_slider_max );
  //vector<cv::Mat> newRgbChannels;
  //vector<cv::Mat> oldRgbChannels;
  for(;;) {
    vid.set(10, ((float) brightness) /1000);
    vid.set(11, ((float) contrast)/1000);
    vid.set(14, ((float) gain)/1000);
    vid.set(15, (((float) exposure)/1000)*(-1));

    vid >> newFrame; // get a new frame from camera
    Mat videoFrame = newFrame.clone();
    cvtColor(newFrame, newFrame, COLOR_BGR2GRAY);
    Mat displayFrame = newFrame.clone();
    //newRgbChannels = split(newFrame);
    //oldRgbChannels = split(oldFrame);

    if (!recording) {
      // bool motionDetected = motionDetect(oldRgbChannels, newRgbChannels);
      displayFrame = motionDetectBW(oldFrame, newFrame, displayFrame, &motionDetected);
      if (motionDetected) {
        start = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
        stop = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
        recording = true;
      }
      imshow("display", displayFrame);
      cout << "NOT_RECORDING" <<endl;
    } else {
      stop = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
      if (stop - start > 4*1000) {
        recording = false;
        start = stop;
      }
      video.write(videoFrame);
      cout << "RECORDING" <<endl;
      imshow("display", newFrame);
    }



    //cvtColor(frame, edges, COLOR_BGR2GRAY);

    //Canny(edges, edges, 0, 30, 3);
    //imshow("display", edges);
    oldFrame = newFrame.clone();

    if(waitKey(1000 / 30) >= 0) {
      break;
    }
  }
  // the camera will be deinitialized automatically in VideoCapture destructor
  return 0;
}


Mat motionDetectBW(Mat oldFrame, Mat newFrame, Mat displayFrame, bool *motionDetected) {

  int count = 0;
  float avgX = 0;
  float avgY = 0;
  int width = oldFrame.cols;
  int height = oldFrame.rows;
  for(int i = 0; i < oldFrame.rows; i++) {
    for(int j = 0; j < oldFrame.cols; j++) {
      float oldPixel = (float) oldFrame.at<uchar>(i, j);
      float newPixel = (float) newFrame.at<uchar>(i, j);
      float dSquared = (oldPixel - newPixel)*(oldPixel - newPixel);
      if ( dSquared > differenceThreshold*differenceThreshold) {
        displayFrame.at<uchar>(i, j) = 255;
        count++;
        avgX += j;
        avgY += i;
      } else {
        displayFrame.at<uchar>(i, j) = newFrame.at<uchar>(i, j);
      }
    }
  }

  if(count > 50000) {
    int quarter;
    avgX /= count;
    avgY /= count;
    if (avgX > width/2 && avgY < height/2) quarter = 1;
    if (avgX > width/2 && avgY > height/2) quarter = 2;
    if (avgX < width/2 && avgY > height/2) quarter = 3;
    if (avgX < width/2 && avgY < height/2) quarter = 4;
    cout << "Motion Detected at quarter " << quarter << endl;
    pointCameraTowards(quarter);
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
