#include "opencv2/highgui.hpp"

using namespace cv;

class Camera {
  public:
    VideoCapture vid();
    int outputWidth, outputHeight;
};
