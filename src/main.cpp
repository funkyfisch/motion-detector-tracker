#include "opencv2/highgui.hpp"

#include <time.h>
#include <chrono>
#include <iostream>
#include "motion_detect.h"

using namespace std;
using namespace cv;
using namespace std::chrono;

const int fps = 30;

int main(int, char**) {
  bool recording = false;

  int start = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
  int stop = start;

  VideoCapture vid(0); // open the default camera
  int outputWidth = vid.get(CV_CAP_PROP_FRAME_WIDTH);
  int outputHeight = vid.get(CV_CAP_PROP_FRAME_HEIGHT);
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
  //vector<cv::Mat> newRgbChannels;
  //vector<cv::Mat> oldRgbChannels;
  for(;;) {
    vid >> newFrame; // get a new frame from camera
    Mat videoFrame = newFrame.clone();
    cvtColor(newFrame, newFrame, COLOR_BGR2GRAY);
    Mat displayFrame = newFrame.clone();

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
      if (stop - start < 4*1000) {
        recording = false;
        start = stop;
      }
      video.write(videoFrame);
      cout << "RECORDING" <<endl;
      imshow("display", newFrame);
    }
    oldFrame = newFrame.clone();

    if(waitKey(1000 / 30) >= 0) {
      break;
    }
  }
  // the camera will be deinitialized automatically in VideoCapture destructor
  return 0;
}
