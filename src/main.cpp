#include "opencv2/highgui.hpp"

#include <time.h>
#include <chrono>
#include <iostream>
#include "motion_detect.h"
#include "motion_track.h"
#include "gui.h"

using namespace std;
using namespace cv;
using namespace std::chrono;

bool guiEnabled = false;
bool serialEnabled = false;
bool recordingEnabled = false;
const int fps = 30;

void loopWithoutRecordingEnabled();
void loopWithRecordingEnabled();

int main(int argc, char* argv[]) {
  if (argc > 1) {
    cout << argc << " Arguments included  " <<  argv[1] << endl;
    for(int i = 0; i < argc; i++) {
      string argument = string(argv[i]);
      if (argument == "--enable-gui") guiEnabled = true;
      if (argument == "--enable-serial") serialEnabled = true;
      if (argument == "--enable-recording") recordingEnabled = true;
    }
  }
  
  if (recordingEnabled) {
    loopWithRecordingEnabled();
  }
  else {
    loopWithoutRecordingEnabled();
  }

  return 0;
}

void loopWithRecordingEnabled() {
  VideoCapture vid(0); // open the default camera
  if (guiEnabled) setupGUI(vid);
  int outputWidth = vid.get(CV_CAP_PROP_FRAME_WIDTH);
  int outputHeight = vid.get(CV_CAP_PROP_FRAME_HEIGHT);
  if(!vid.isOpened()) {
    return;
  }
  bool motionDetected;
  int region;
  Mat newFrame;
  Mat oldFrame;
  vid >> oldFrame;

  VideoWriter video("out.avi", CV_FOURCC('M', 'J', 'P', 'G'), 20, Size(oldFrame.cols, oldFrame.rows), true);
  bool recording = false;
  int start = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
  int stop = start;
  int debounceCounter = 0;


  for (;;) {
    vid >> newFrame; // get a new frame from camera
    Mat videoFrame = newFrame.clone();
    cvtColor(newFrame, newFrame, COLOR_BGR2GRAY);
    Mat displayFrame = newFrame.clone();
    if (debounceCounter < 10) debounceCounter++;
    else {
      displayFrame = motionDetectBW(oldFrame, newFrame, displayFrame, &motionDetected, &region);
      if (!recording) {
        if (motionDetected) {
          start = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
          stop = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
          recording = true;
          pointCameraTowards(region);
        }
        
        if (guiEnabled) showFrame(displayFrame);
        cout << "NOT_RECORDING" <<endl;
      } else {
        stop = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
        if (stop - start > 4*1000) {
          recording = false;
          start = stop;
        }
        if (guiEnabled) showFrame(displayFrame);
        video.write(videoFrame);
        cout << "RECORDING" <<endl;
      }
    }

    oldFrame = newFrame.clone();

    if(waitKey(1000 / 30) >= 0) {
      break;
    }
  }
}

void loopWithoutRecordingEnabled() {
  VideoCapture vid(0); // open the default camera
  if (guiEnabled) {
    setupGUI(vid);
  }
  int outputWidth = vid.get(CV_CAP_PROP_FRAME_WIDTH);
  int outputHeight = vid.get(CV_CAP_PROP_FRAME_HEIGHT);
  if(!vid.isOpened()) {
    return;
  }
  bool motionDetected;
  int region;
  Mat newFrame;
  Mat oldFrame;
  vid >> oldFrame;
  for(;;) {
    vid >> newFrame; // get a new frame from camera
    Mat videoFrame = newFrame.clone();
    cvtColor(newFrame, newFrame, COLOR_BGR2GRAY);
    Mat displayFrame = newFrame.clone();
    displayFrame = motionDetectBW(oldFrame, newFrame, displayFrame, &motionDetected, &region);
    if (motionDetected) {
      pointCameraTowards(region);
    }
    if (guiEnabled) {
      showFrame(displayFrame);
    }
    oldFrame = newFrame.clone();

    if(waitKey(1000 / 30) >= 0) {
      break;
    }
  }
}