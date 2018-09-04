# motion-detector-tracker

This project uses OpenCV to capture frames and do motion detection on them.
If motion has been detected, the next 10 seconds will be recorded into an avi file.
Additionally, the discovered motion is averaged into one of four locations :
top right, top left, bottom right, bottom left. After determining the general area of motion, a command is sent out that can be used by a servo controller code, in order to move a possible camera setup and try to center to the average motion area.

## Docker usage

If already familiar with docker, this project can be run very quickly. First, build the image, by running

`docker build motion-detector-tracker -f docker/Dockerfile .`

at the ROOT directory of the project.

Then you can proceed to run the program with distinct flags and modes.

#### Plain 
Plain mode has only motion detection and reports if there is motion and at which region.

`docker run --rm -ti --device=/dev/video0:/dev/video0 motion-detector-tracker /opt/motion-detector-tracker/Main.out`

Recording mode will automatically record 10 second segments everytime a motion has been detected.

`docker run --rm -ti --device=/dev/video0:/dev/video0 motion-detector-tracker /opt/motion-detector-tracker/Main.out --enable-recording`

## Build

Building is straightforward, assuming you have version of OpenCV version 3.3.0+ already installed.
Just run

`cmake .`

`make`

on the root directory.

## Running

Plain mode:

`./Main.out`

#### Parameters:
`--enable-gui`
Enables a graphical interface 

`--enable-serial`
Enables serial communication (experimental)

`--enable-recording`
Enables recording video fragments of 10s when motion is detected and saves it on an avi file.

## Troubleshooting

### Raspberry Pi - uv4l
If you have uv4l web server running on your RPi, and you seem to be getting segmentation faults while first trying to run the program, the culprit is probably the streaming server. To circumvent this, you need to stop the webserver streaming service like so

`sudo systemctl stop uv4l_raspicam.service`
`sudo systemctl disable uv4l_raspicam.service`

this might disable your video device as well. To bring it back up,

`sudo modprobe bcm2835-v4l2`