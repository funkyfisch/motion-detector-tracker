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
  //namedWindow("display",1);
  Mat newFrame;
  Mat oldFrame;
  vid >> oldFrame;
  VideoWriter video("out.avi", CV_FOURCC('M', 'J', 'P', 'G'), 20, Size(oldFrame.cols, oldFrame.rows), true);
  bool motionDetected;
  //cvtColor(oldFrame, oldFrame, COLOR_BGR2GRAY);
  // createTrackbar("brightness", "display", &brightness, brightness_slider_max );
  // createTrackbar("contrast", "display", &contrast, contrast_slider_max );
  // createTrackbar("gain", "display", &gain, gain_slider_max );
  // createTrackbar("exposure", "display", &exposure, exposure_slider_max );
  //vector<cv::Mat> newRgbChannels;
  //vector<cv::Mat> oldRgbChannels;
  int debounceCounter = 0;
  for(;;) {
    // vid.set(10, ((float) brightness) /1000);
    // vid.set(11, ((float) contrast)/1000);
    // vid.set(14, ((float) gain)/1000);
    // vid.set(15, (((float) exposure)/1000)*(-1));

    vid >> newFrame; // get a new frame from camera
    Mat videoFrame = newFrame.clone();
    cvtColor(newFrame, newFrame, COLOR_BGR2GRAY);
    Mat displayFrame = newFrame.clone();
    if (debounceCounter < 10) {
      debounceCounter++;
    } else {
      if (!recording) {
        // bool motionDetected = motionDetect(oldRgbChannels, newRgbChannels);
        displayFrame = motionDetectBW(oldFrame, newFrame, displayFrame, &motionDetected);
        if (motionDetected) {
          start = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
          stop = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
          recording = true;
        }
        //imshow("display", displayFrame);
        cout << "NOT_RECORDING" <<endl;
      } else {
        stop = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
        if (stop - start > 4*1000) {
          recording = false;
          start = stop;
        }
        video.write(videoFrame);
        cout << "RECORDING" <<endl;
        // imshow("display", newFrame);
      }
    }
    oldFrame = newFrame.clone();

    if(waitKey(1000 / 30) >= 0) {
      break;
    }
  }
  // the camera will be deinitialized automatically in VideoCapture destructor
  return 0;
}
