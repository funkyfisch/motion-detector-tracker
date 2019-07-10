#include <iostream>

#include "Camera.hpp"

Camera::Camera(const std::shared_ptr<Dexode::EventBus>& eb) :
    _cameraEventBus{eb}
{
    std::cout << "Camera object initialised" << std::endl;
}

Camera::~Camera() {
    turnOff();
    std::cout << "Camera object destroyed" << std::endl;
}

bool Camera::getStatus() {
    return _cameraOn;
}

void Camera::turnOn(int deviceID) {
    _vid.open(deviceID);
    if (_vid.isOpened()) {
        _cameraOn = true;
        Event::StatusChange e1{std::string("on")};
        _cameraEventBus->notify(e1);
    }
}

void Camera::run() {
    cv::Mat frame;
    _vid >> frame;

    // std::vector<uchar> encodedFrame;
    // if (frame.isContinuous()) {
    //     encodedFrame.assign(frame.data, frame.data + frame.total());
    // } else {
    //     for (int i = 0; i < frame.rows; i++) {
    //         encodedFrame.insert(encodedFrame.end(), frame.ptr<uchar>(i), frame.ptr<uchar>(i)+frame.cols);
    //     }
    // }
    Event::NewFrame e2{frame.clone()};
    _cameraEventBus->notify(e2);
}

void Camera::turnOff() {
    _vid.release();
    _cameraOn = false;
    Event::StatusChange e{std::string("off")};
    _cameraEventBus->notify(e);
}



