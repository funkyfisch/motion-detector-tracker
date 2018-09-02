# motion-detector-tracker

This project uses OpenCV to capture frames and do motion detection on them.
If motion has been detected, the next 10 seconds will be recorded into an avi file.
Additionally, the discovered motion is averaged into one of four locations :
top right, top left, bottom right, bottom left. After determining the general area of motion, a command is sent out that can be used by a servo controller code, in order to move a possible camera setup and try to center to the average motion area.

## Troubleshooting

### Raspberry Pi - uv4l
If you have uv4l web server running on your RPi, and you seem to be getting segmentation faults while first trying to run the program, the culprit is probably the streaming server. To circumvent this, you need to stop the webserver streaming service like so

`sudo systemctl stop uv4l_raspicam.service`
`sudo systemctl disable uv4l_raspicam.service`

this might disable your video device as well. To bring it back up,

`sudo modprobe bcm2835-v4l2`