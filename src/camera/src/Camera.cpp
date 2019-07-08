#include "Camera.hpp"
#include <iostream>

void Camera::publishFrameEvent(NewFrameEvent e) {
    _cameraEventBus->notify(e);
}

Camera::Camera(const std::shared_ptr<Dexode::EventBus>& eb) :
    _cameraEventBus{eb}
{
    std::cout << "Camera object initialised" << std::endl;
    turnOn();
}

Camera::~Camera() {
    turnOff();
    std::cout << "Camera object destroyed" << std::endl;
}

bool Camera::getStatus() {
    return _cameraOn;
}

void Camera::turnOn() {
    _cameraOn = true;
    NewFrameEvent e{std::string("turning camera on")};
    publishFrameEvent(e);
}

void Camera::turnOff() {
    _cameraOn = false;
    NewFrameEvent e{std::string("turning camera off")};
    publishFrameEvent(e);
}



