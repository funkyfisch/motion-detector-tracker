#include "Core.hpp"

Core::Core() {
    std::cout<<"Core has been initialised"<<std::endl;
    _eventBus = std::make_shared<Dexode::EventBus>();
    _eventBus->listen<NewFrameEvent>(std::bind(&Core::onEvent, this, std::placeholders::_1));

    _cameraInstance = std::make_shared<Camera>(_eventBus);


}

void Core::onEvent(const NewFrameEvent& e) {
    std::cout << e.message << std::endl;
}