#pragma once

#include <iostream>
#include <thread>

#include <eventbus/EventBus.h>

#include "Camera.hpp"
#include "MotionDetect.hpp"
#include "Event.hpp"

class Core {
    public:
        Core();
        void manageCamera();
        void manageMotionDetect();
    private:
        std::shared_ptr<Camera> _cameraInstance;
        std::shared_ptr<MotionDetect> _motionDetectInstance;
        std::shared_ptr<Dexode::EventBus> _eventBus;
        void onStatusChange(const Event::StatusChange& e);
};
