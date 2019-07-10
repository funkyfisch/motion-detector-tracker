#include <iostream>

#include <iostream>
#include <chrono>
#include <thread>

#include <opencv4/opencv2/imgproc.hpp>


#include <eventbus/EventBus.h>
#include "Event.hpp"

class MotionDetect {

    public:
        MotionDetect(const std::shared_ptr<Dexode::EventBus>& eb);
        void run();

    private:
        std::shared_ptr<Dexode::EventBus> _eventBus;
        // cv::Mat motionDetectBW(cv::Mat, cv::Mat, cv::Mat, bool*, int*);
        bool motionDetectBW(cv::Mat, cv::Mat);
        int determineMotionRegion(float, float, int, int);
        void onReceiveFrame(const Event::NewFrame& e);
        cv::Mat _previousFrame;
        cv::Mat _nextFrame;
        bool _hasFirstFrame = false;
};
