#include "Core.hpp"

Core::Core() {
    std::cout<<"Core has been initialised"<<std::endl;
    _eventBus = std::make_shared<Dexode::EventBus>();

    _eventBus->listen<Event::StatusChange>(std::bind(&Core::onStatusChange, this, std::placeholders::_1));

    _cameraInstance = std::make_shared<Camera>(_eventBus);
    _motionDetectInstance = std::make_shared<MotionDetect>(_eventBus); 

    std::thread cameraThread(&Core::manageCamera, this);
    // cameraThread.detach();
    std::thread motionDetectThread(&Core::manageMotionDetect, this);
    // motionDetectThread.detach();
    if (cameraThread.joinable()) {
        std::cout<< "camera joinable" <<std::endl;
        cameraThread.join();
    }

    if (motionDetectThread.joinable()) {
        std::cout<< "motiondetect joinable" <<std::endl;
        motionDetectThread.join();
    }

    // while(true) {

    // }


}

void Core::onStatusChange(const Event::StatusChange& e) {
    std::cout << e.message << std::endl;
}

void Core::manageCamera() {
    _cameraInstance->turnOn(0);
    while(true) {
        if(_cameraInstance->getStatus()) {
            _cameraInstance->run();
        }
    }
}

void Core::manageMotionDetect() {
    // this->_motionDetectInstance->run()
    while(true) {
        _motionDetectInstance->run();
    }
}

