#include "../include/serial.h"

using namespace std;

int main(int argc, char** argv) {

    char device[] = USB_DEVICE_IDENTIFIER;
    int deviceOk = checkSerialDevice(device);
    if (deviceOk != 0) {
        return -1;
    } else {
        setupSerialSettings(device);
        int trials;
        for(trials = 1; trials < 4; trials++) {
            string handshake = readSerial(device, 1);
            if (handshake == "G") {
                cout << "Handshake success!" << endl;
                break;
            } else {
                cerr << "Attempt no " << trials << " failed, retrying" << endl;
            }
        }
    }
}



int checkSerialDevice(char device[]) {
    int code;
    int fd = open(device, O_RDWR | O_NOCTTY);
    if (fd == -1) {
        cerr << "Could not open device " << device << endl;
        code = EXIT_FAILURE;
    } else {
        cout << "Opened device " << device << "successfully" << endl;
        code = EXIT_SUCCESS;
    }
    close(fd);
    return code;
}

void setupSerialSettings(char device[]) {

    // Read more at http://xanthium.in/Serial-Port-Programming-on-Linux 
    struct termios SerialPortSettings;
    int fd = open(device, O_RDWR | O_NOCTTY);
    tcgetattr(fd, &SerialPortSettings);
    cfsetispeed(&SerialPortSettings, B9600);
    cfsetospeed(&SerialPortSettings, B9600);
    SerialPortSettings.c_cflag &= ~PARENB;   // No Parity
    SerialPortSettings.c_cflag &= ~CSTOPB; //Stop bits = 1 
    SerialPortSettings.c_cflag &= ~CSIZE; /* Clears the Mask       */
    SerialPortSettings.c_cflag |=  CS8;   /* Set the data bits = 8 */
    SerialPortSettings.c_cflag |= CREAD | CLOCAL;//enable receiver
        /* Setting Time outs */                                       
    SerialPortSettings.c_cc[VMIN]  = 10; /* Read 10 characters */  
    SerialPortSettings.c_cc[VTIME] = 0;  /* Wait indefinitely   */
    
    if((tcsetattr(fd,TCSANOW,&SerialPortSettings)) != 0) /* Set the attributes to the termios structure*/
	    cerr << "ERROR ! in Setting attributes" << endl;
	else
        cout << "BaudRate = 9600 StopBits = 1 Parity = none" << endl;
}

void writeSerial(char device[], char buffer[]) {
    int code;
    int fd = open(device, O_RDWR | O_NOCTTY);
    int bytesWritten = write(fd, buffer, sizeof(&buffer));
    close(fd);
}

string readSerial(char device[], int length) {
    string message = "";
    int fd = open(device, O_RDWR | O_NOCTTY);
    tcflush(fd, TCIFLUSH);   /* Discards old data in the rx buffer            */
    char readBuffer[length];
    int bytesRead = 0;
    bytesRead = read(fd, &readBuffer, length);
    close(fd);
    for(int i = 0; i < bytesRead; i++ ) {
        message += readBuffer[i];
    }
    return message;
}