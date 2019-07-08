#pragma once

#include <gtkmm-3.0/gtkmm.h>
#include <opencv4/opencv2/highgui.hpp>

class CameraDrawingArea: public Gtk::DrawingArea {
    public:
        CameraDrawingArea();
        virtual ~CameraDrawingArea();

    protected:
        bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override; 
        void on_size_allocate(Gtk::Allocation& allocation) override;

        bool everyNowAndThen(); 

    private: 
        sigc::connection everyNowAndThenConnection; 
        cv::VideoCapture videoCapture; 
        cv::Mat webcam; 
        cv::Mat output; 
        int width, height;
};