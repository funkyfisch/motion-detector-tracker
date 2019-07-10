#pragma once

namespace Event{
    struct NewFrame {
        cv::Mat frame;
    };
    struct StatusChange {
        std::string message = "";
    };
}
