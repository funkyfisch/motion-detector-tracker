#include "opencv2/highgui.hpp"

#include <time.h>
#include <chrono>
#include <iostream>
#include "motion_detect.h"
#include "gui.h"

using namespace std;
using namespace cv;
using namespace std::chrono;

bool guiEnabled = false;
bool serialEnabled = false;
bool recordingEnabled = false;
const int fps = 30;

int main(int argc, char* argv[]) {
  if (argc > 0) {
    cout << argc << " Arguments included  " <<  argv[1] << endl;
    for(int i = 0; i < argc; i++) {
      string argument = string(argv[i]);
      if (argument == "--enable-gui") guiEnabled = true;
      if (argument == "--enable-serial") serialEnabled = true;
      if (argument == "--enable-recording") recordingEnabled = true;
    }
  }

  bool recording = false;
  int start = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
  int stop = start;

  VideoCapture vid(0); // open the default camera
  if (guiEnabled) setupGUI(vid);
  int outputWidth = vid.get(CV_CAP_PROP_FRAME_WIDTH);
  int outputHeight = vid.get(CV_CAP_PROP_FRAME_HEIGHT);
  if(!vid.isOpened()) {
    return -1;
  }

  Mat edges;
  
  Mat newFrame;
  Mat oldFrame;
  vid >> oldFrame;

  VideoWriter video("out.avi", CV_FOURCC('M', 'J', 'P', 'G'), 20, Size(oldFrame.cols, oldFrame.rows), true);
  int debounceCounter = 0;

  bool motionDetected;
  //cvtColor(oldFrame, oldFrame, COLOR_BGR2GRAY);
  //vector<cv::Mat> newRgbChannels;
  //vector<cv::Mat> oldRgbChannels;
  for(;;) {

    vid >> newFrame; // get a new frame from camera
    Mat videoFrame = newFrame.clone();
    cvtColor(newFrame, newFrame, COLOR_BGR2GRAY);
    Mat displayFrame = newFrame.clone();
    if (debounceCounter < 10 && recordingEnabled) {
      debounceCounter++;
    } else {
      if (!recording) {
        // bool motionDetected = motionDetect(oldRgbChannels, newRgbChannels);
        displayFrame = motionDetectBW(oldFrame, newFrame, displayFrame, &motionDetected);
        if (motionDetected) {
          start = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
          stop = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
          //recording = true;
        }
        
        if (guiEnabled) showFrame(displayFrame);
        cout << "NOT_RECORDING" <<endl;
      } else {
        stop = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
        if (stop - start > 4*1000) {
          recording = false;
          start = stop;
        }
        //video.write(videoFrame);
        //cout << "RECORDING" <<endl;
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
