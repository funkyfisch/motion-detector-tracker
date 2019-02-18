// // Code for testing motion tracker in isolation

// // #include "coordinates/FieldOfViewSectors.h"

// // #include "motionTracker/MotionTracker.cpp"
// // #include <stdio.h>

// // int main(int argc, char* argv[]) {
// //     MotionTracker mt = MotionTracker(false);
// //     DualAxisMovement dam = mt.getRequiredMovement((int) FieldOfViewSectors::BOTTOM_RIGHT);
// //     cout << "pan is : " << dam.getPanMovement() << " pitch is : " << dam.getPitchMovement() << endl;
// //     mt.toggleTracker();
// //     dam = mt.getRequiredMovement((int) FieldOfViewSectors::BOTTOM_RIGHT);
// //     cout << "pan is : " << dam.getPanMovement() << " pitch is : " << dam.getPitchMovement() << endl;
// // }

// // Code for testing serial interface in isolation

// // #include "serialInterface/SerialInterface.cpp"

// #include <iostream>
// #include <vector>
// #include <algorithm>
// #include <time.h>
// #include <sys/types.h>
// #include <sys/timeb.h>
#include <string.h>

// using namespace std;

// class Subject;

// class Observer {
//     public:
//         Observer();
//         ~Observer();
//         virtual void update(Subject* theChangeSubject) = 0;
// };

// class Subject {
//     public:
//         Subject();
//         virtual ~Subject();
//         virtual void attach(Observer*);
//         virtual void detach(Observer*);
//         virtual void notify();
//     private:
//         vector<Observer *> _observers;
// };

// void Subject::attach(Observer* o) {
//     _observers.push_back(o);
// }

// void Subject::detach(Observer *o) {
//     auto iterator = find(_observers.begin(), _observers.end(), o);

//     if (iterator != _observers.end()) {
//         _observers.erase(iterator);
//     }
// }

// void Subject::notify() {
//     for(Observer *observer : _observers) {
//         observer->update(this);
//     }
// }

// class ClockTimer : public Subject {
//     public:
//         int getHour();
//         int getMinute();
//         int getSecond();
//         void tick();

//     private:
//         char tmpbuf[128];

// };

// void ClockTimer::tick() {
//     notify();
// }

// int ClockTimer::getHour() {
//     char timebuf[128];
//     strncpy(timebuf, tmpbuf, 2);
//     timebuf[2] = NULL;
//     return atoi(timebuf);
// }

// int ClockTimer::getMinute() {
//     char timebuf[128];
//     strncpy(timebuf, tmpbuf+3, 2);
//     timebuf[2] = NULL;
//     return atoi(timebuf);
// }

// int ClockTimer::getSecond() {
//     char timebuf[128];
//     strncpy(timebuf, tmpbuf+6, 2);
//     timebuf[2] = NULL;
//     return atoi(timebuf);
// }

// class DigitalClock : public Observer {
//     public:
//         DigitalClock(ClockTimer *);
//         ~DigitalClock();
//         void update(Subject *);
//         void draw();
//     private:
//         ClockTimer *_subject;
// };

// DigitalClock::DigitalClock(ClockTimer *s) {
//     _subject = s;
//     _subject->attach(this);
// }

// DigitalClock::~DigitalClock() {
//     _subject->detach(this);
// }

// void DigitalClock::update(Subject *theChangedSubject) {
//     if(theChangedSubject == _subject) {
//         draw();
//     }
// }
// void DigitalClock::draw() {
//     int hour = _subject->getHour();
//     int minute = _subject->getMinute();
//     int second = _subject->getSecond();
//     cout << "Digital time is " << hour << ":" 
//           << minute << ":" 
//           << second << endl; 
// }
// int main(int argc, char* argv[]) {
//     // SerialInterface serial = SerialInterface(9600);
//     // serial.initialiseConnection();
//     // serial.readIncomingData();
//     // serial.sendOutgoingData("hello");
//     // serial.closeConnection();

//     ClockTimer timer;

//     DigitalClock digitalClock(&timer);

//     timer.tick();
// }

#include <iostream>
#include <stdexcept>
#include <thread>

#include "observable/observable.hpp"
#include "serialInterface/serial_lowLevel.h"
#define DEBUG 1

using namespace std;
using namespace observable;

int file_descriptor;
string device = "/dev/ttyUSB0";
const char *device_port = device.c_str();
bool characterReceived = false;
bool stopReading = false;

void probeSerial() {
     /* Open the file descriptor in non-blocking mode */
    file_descriptor = open(device_port, O_RDWR | O_NOCTTY);
    if (file_descriptor == -1) {
        cerr << "Could not open device : " << device_port << endl;
        throw invalid_argument("Could not open device");
    } else {
        cout << "Serial probe success!" << endl;
    }
    close(file_descriptor);
}

void setupSerialSettings() {
    /* Read more at http://xanthium.in/Serial-Port-Programming-on-Linux 
        tcflag_t c_iflag; input mode flags 
        tcflag_t c_oflag; output mode flags 
        tcflag_t c_cflag; control mode flags 
        tcflag_t c_lflag; local mode flags 
        cc_t c_line;      line discipline 
        cc_t c_cc[NCCS];  control characters
    */
    struct termios SerialPortSettings;

     /* Open the file descriptor in non-blocking mode */
    file_descriptor = open(device_port, O_RDWR | O_NOCTTY);

    /* wait for the device */
    usleep(350000);

    /* Get current settings for the serial device */
    tcgetattr(file_descriptor, &SerialPortSettings);

    /* Set custom options */

    /* Baud Rate */
    cfsetispeed(&SerialPortSettings, B9600);
    cfsetospeed(&SerialPortSettings, B9600);

    /* 8 bits, no parity, no stop bits */
    SerialPortSettings.c_cflag &= ~PARENB;
    SerialPortSettings.c_cflag &= ~CSTOPB;
    SerialPortSettings.c_cflag &= ~CSIZE;
    SerialPortSettings.c_cflag |= CS8;

    /* Canonical mode */
    SerialPortSettings.c_lflag |= ICANON;

    /* commit the serial port settings */
    tcsetattr(file_descriptor, TCSANOW, &SerialPortSettings);
             
    close(file_descriptor);
}

void openSerialConnection() {
     /* Open the file descriptor in non-blocking mode */
    file_descriptor = open(device_port, O_RDWR | O_NOCTTY);
    cout << "Connected to serial device!" << endl;
}

void closeSerialConnection() {
    close(file_descriptor);
    cout << "Connection to serial device has been closed!" << endl;
}

void serialMessageListener() {
    /* This will read bytes from buffer until it hits a new line */
    /* This is blocking, if a message is not received, this call will hang */
    /* Introduce some kind of timeout with a thread ? */
    /* https://stackoverflow.com/questions/2917881/how-to-implement-a-timeout-in-read-function-call */
    int n, i;
    char buffer[64];
    /* Receive string from Arduino */
    n = read(file_descriptor, buffer, 64);

    /* insert terminating zero in the string */
    buffer[n] = 0;
    printf("%i bytes read, buffer contains: %s", n, buffer);
}

void writeToSerial() {
    char write_buffer[] = "A"; 
    int  bytes_written  =  0 ;   
                                                            
    bytes_written = write(file_descriptor,write_buffer,sizeof(write_buffer));
}


void readLoop() {
    for(;;) {
        if (stopReading) break;
        serialMessageListener();
    }
}

void waitForExitKey() {
    for(;;) {
        if (cin.get() == 'x') {
            characterReceived = true;
            cout << "terminating" << endl;
            break;
        }
    }
}

void stopCommand() {
    for(;;) {
        if (stopReading == true) break;
    }
}

void startReading() {
    thread stopReadFromSerialListener(stopCommand);
    thread serialMessageListener(readLoop);
    stopReadFromSerialListener.join();
    serialMessageListener.join();
}

void manualStopTrigger() {
    sleep(7);
    stopReading = true;
}

int main() {
    probeSerial();
    setupSerialSettings();
    openSerialConnection();
    /* Sample trigger that will cause reading to stop */
    thread triggerListener(manualStopTrigger);
    startReading();

    
    triggerListener.join();

    closeSerialConnection();
}