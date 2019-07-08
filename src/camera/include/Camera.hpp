#include <opencv4/opencv2/highgui.hpp>

#include <eventbus/EventBus.h>

#include "NewFrameEvent.hpp"


class Camera {
  public:
    cv::VideoCapture vid;
    int outputWidth, outputHeight;
    float a = 5;

    Camera(const std::shared_ptr<Dexode::EventBus>& eb);
    ~Camera();
    bool getStatus();

    void publishFrameEvent(NewFrameEvent e);
    void turnOn();
    void turnOff();
  
  private:
    std::shared_ptr<Dexode::EventBus> _cameraEventBus;
    bool _cameraOn = false;

    // event listener /subscriber (for settings change etc.)
    // event emitter (for sending new images)

};
