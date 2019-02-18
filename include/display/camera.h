#include "opencv2/highgui.hpp"

class Camera {
  public:
    cv::VideoCapture vid;
    int outputWidth, outputHeight;
};
