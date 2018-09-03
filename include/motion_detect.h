#include "opencv2/imgproc.hpp"

cv::Mat motionDetectBW(cv::Mat, cv::Mat, cv::Mat, bool*);
void pointCameraTowards(int);
int determineMotionRegion(float, float, int, int);