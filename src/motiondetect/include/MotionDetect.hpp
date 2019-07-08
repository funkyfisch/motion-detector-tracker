#include <opencv4/opencv2/imgproc.hpp>

cv::Mat motionDetectBW(cv::Mat, cv::Mat, cv::Mat, bool*, int*);
int determineMotionRegion(float, float, int, int);