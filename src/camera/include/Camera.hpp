#include <opencv4/opencv2/highgui.hpp>

#include <eventbus/EventBus.h>

#include "Event.hpp"

class Camera {
  public:

    Camera(const std::shared_ptr<Dexode::EventBus>& eb);
    ~Camera();
    bool getStatus();
    void run();
    void turnOn(int deviceID);
    void turnOff();

  
  private:
    std::shared_ptr<Dexode::EventBus> _cameraEventBus;
    bool _cameraOn = false;
    cv::VideoCapture _vid;
    int outputWidth, outputHeight;

};
