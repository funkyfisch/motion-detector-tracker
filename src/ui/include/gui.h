#include <opencv4/opencv2/highgui.hpp>

const int BRIGHTNESS_SLIDER_MAX = 2*1000;
const int CONTRAST_SLIDER_MAX = 2*1000;
const int GAIN_SLIDER_MAX = 2*1000;
const int EXPOSURE_SLIDER_MAX = 8*1000;

void setupGUI(cv::VideoCapture);
void showFrame(cv::Mat);
