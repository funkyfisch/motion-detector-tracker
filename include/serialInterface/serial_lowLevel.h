#include <iostream>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

#define USB_DEVICE_IDENTIFIER "/dev/ttyUSB0"

#ifndef EXIT_FAILURE 
#define EXIT_FAILURE -1
#endif
#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS 0
#endif

void initSerial(char[]);
int checkSerialDevice(char[]);
void setupSerialSettings(char[]);
void writeSerial(char[], char[]);
std::string readSerial(char[], int);