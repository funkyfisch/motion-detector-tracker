#include <iostream>

#include "serialInterface/SerialInterface.h"
#include "serialInterface/ObservableSerialConnection.cpp"

using namespace std;

SerialInterface::SerialInterface(int baudRate) {
    return;
}

void SerialInterface::initialiseConnection() {
    cout << "[SERIAL_INTERFACE] " << "Initialising serial connection...." << endl;
    _connection.addObserver(this);
    cout << "[SERIAL_INTERFACE] " << "Connection initialised" << endl;
}

std::string SerialInterface::readIncomingData() {
    cout << "[SERIAL_INTERFACE] " << "Incoming message: sample data" << endl;
    return std::string("sample data");
}

void SerialInterface::sendOutgoingData(std::string data) {
    cout << "[SERIAL_INTERFACE] " << "Outgoing message: " << data << endl;
}

void SerialInterface::closeConnection() {
    cout << "[SERIAL_INTERFACE] " << "Closing serial connection..." << endl;
    _connection.removeObserver(this);
    cout << "[SERIAL_INTERFACE] " << "Serial connection terminated" << endl;
}