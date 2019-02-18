#ifndef SERIALINTERFACE_H
#define SERIALINTERFACE_H

#include <string>

#include "lib/observer/BaseObserver.hpp"

class SerialInterface : public BaseObserver {
    public:
        void update() override;

        SerialInterface(int baudRate);
        void initialiseConnection();
        std::string readIncomingData();
        void sendOutgoingData(std::string);
        void closeConnection();

    private:
        ObservableSerialConnection _connection;
};

#endif