#pragma once

#include <iostream>

#include <eventbus/EventBus.h>

#include "Camera.hpp"
#include "NewFrameEvent.hpp"

class Core {
    public:
        Core();
    private:
        std::shared_ptr<Camera> _cameraInstance;
        std::shared_ptr<Dexode::EventBus> _eventBus;
        void onEvent(const NewFrameEvent& e);
};
