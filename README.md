# motion-detector-tracker

This project uses OpenCV to capture frames and do motion detection on them.
If motion has been detected, the next 10 seconds will be recorded into an avi file.
Additionally, the discovered motion is averaged into one of four locations :
top right, top left, bottom right, bottom left. After determining the general area of motion, a command is sent out that can be used by a servo controller code, in order to move a possible camera setup and try to center to the average motion area.
