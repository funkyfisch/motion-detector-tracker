// #include <opencv4/opencv2/highgui.hpp>

// #include <time.h>
// #include <chrono>
// #include <iostream>
// #include "motion_detect.h"
// #include "motion_track.h"
// #include "gui.h"

// using namespace std;
// using namespace cv;
// using namespace std::chrono;

// void loopWithoutRecordingEnabled();
// void loopWithRecordingEnabled();
// void printHelpSection();

// int main(int argc, char* argv[]) {

  
//   if (recordingEnabled) {
//     loopWithRecordingEnabled();
//   }
//   else {
//     loopWithoutRecordingEnabled();
//   }

//   return 0;
// }

// void loopWithRecordingEnabled() {
//   VideoCapture vid(0); // open the default camera
//   if (guiEnabled) setupGUI(vid);
//   int outputWidth = vid.get(CAP_PROP_FRAME_WIDTH);
//   int outputHeight = vid.get(CAP_PROP_FRAME_HEIGHT);
//   if(!vid.isOpened()) {
//     return;
//   }
//   bool motionDetected;
//   int region;
//   Mat newFrame;
//   Mat oldFrame;
//   vid >> oldFrame;
//   VideoWriter video("out.avi",  VideoWriter::fourcc('M', 'J', 'P', 'G'), 20, Size(oldFrame.cols, oldFrame.rows), true);
//   bool recording = false;
//   int start = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
//   int stop = start;
//   int debounceCounter = 0;


//   for (;;) {
//     vid >> newFrame; // get a new frame from camera
//     Mat videoFrame = newFrame.clone();
//     cvtColor(newFrame, newFrame, COLOR_BGR2GRAY);
//     Mat displayFrame = newFrame.clone();
//     if (debounceCounter < 10) debounceCounter++;
//     else {
//       displayFrame = motionDetectBW(oldFrame, newFrame, displayFrame, &motionDetected, &region);
//       if (!recording) {
//         if (motionDetected) {
//           start = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
//           stop = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
//           recording = true;
//           pointCameraTowards(region);
//         }
        
//         if (guiEnabled) showFrame(displayFrame);
//         cout << "NOT_RECORDING" <<endl;
//       } else {
//         stop = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
//         if (stop - start > 4*1000) {
//           recording = false;
//           start = stop;
//         }
//         if (guiEnabled) showFrame(displayFrame);
//         video.write(videoFrame);
//         cout << "RECORDING" <<endl;
//       }
//     }

//     oldFrame = newFrame.clone();

//     if(waitKey(1000 / 30) >= 0) {
//       break;
//     }
//   }
// }

// void loopWithoutRecordingEnabled() {
//   VideoCapture vid(0); // open the default camera
//   if (guiEnabled) {
//     setupGUI(vid);
//   }
//   int outputWidth = vid.get(CAP_PROP_FRAME_WIDTH);
//   int outputHeight = vid.get(CAP_PROP_FRAME_HEIGHT);
//   if(!vid.isOpened()) {
//     return;
//   }
//   bool motionDetected;
//   int region;
//   Mat newFrame;
//   Mat oldFrame;
//   vid >> oldFrame;
//   for(;;) {
//     vid >> newFrame; // get a new frame from camera
//     Mat videoFrame = newFrame.clone();
//     cvtColor(newFrame, newFrame, COLOR_BGR2GRAY);
//     Mat displayFrame = newFrame.clone();
//     displayFrame = motionDetectBW(oldFrame, newFrame, displayFrame, &motionDetected, &region);
//     if (motionDetected) {
//       pointCameraTowards(region);
//     }
//     if (guiEnabled) {
//       showFrame(displayFrame);
//     }
//     oldFrame = newFrame.clone();

//     if(waitKey(1000 / 30) >= 0) {
//       break;
//     }
//   }
// }

#include <iostream>
#include "Core.hpp"
#include <eventbus/EventBus.h>
using namespace std;

bool serialEnabled = false;
bool recordingEnabled = false;
const int fps = 30;

const std::shared_ptr<Dexode::EventBus> _bus;

void printHelpSection() {
  cout << "Motion Detector and Tracker" << endl << endl;
  cout << "Usage: motion-detector-tracker [OPTIONS]" << endl << endl;
  cout << "      --help                      Displays this page" << endl;
  cout << "      --enable-serial             Runs with serial motor controller" << endl;
  cout << "      --enable-recording          Records video on motion detection" << endl;
  cout << endl;
}

void parseArguments(int length, char* args[]) {
  if (length > 1) {
    for(int i = 0; i < length; i++) {
      string argument(args[i]);
      if (argument == "--enable-serial") serialEnabled = true;
      if (argument == "--enable-recording") recordingEnabled = true;
      if (argument == "--help" || argument == "-h") {
        printHelpSection();
      }
    }
  }
}

int main(int argc, char* argv[]) {
  std::cout<<"main is happening" << std::endl;
  Core coreInstance = Core();
  return 0;
}