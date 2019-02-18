#include "gui.h"

using namespace cv;
int brightness, contrast, gain, exposure;
void setupGUI(VideoCapture vid) {
    brightness = 340;
    contrast = 0;
    gain = 0;
    exposure = 5000;
    // vid.set(CAP_PROP_AUTO_EXPOSURE, 0.25);
    // vid.set(10, ((float) brightness) /1000);
    // vid.set(11, ((float) contrast)/1000);
    // vid.set(14, ((float) gain)/1000);
    // vid.set(15, (((float) exposure)/1000)*(-1));

    namedWindow("display", WINDOW_AUTOSIZE);

    // createTrackbar("brightness", "display", &brightness, BRIGHTNESS_SLIDER_MAX );
    // createTrackbar("contrast", "display", &contrast, CONTRAST_SLIDER_MAX );
    // createTrackbar("gain", "display", &gain, GAIN_SLIDER_MAX );
    // createTrackbar("exposure", "display", &exposure, EXPOSURE_SLIDER_MAX );
}

void showFrame(Mat displayFrame) {
    imshow("display", displayFrame);
}

