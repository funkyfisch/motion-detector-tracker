#include "include/serialInterface/ObservableSerialConnection.hpp"

void ObservableSerialConnection::addObserver(BaseObserver *observer) {
    _observers.push_back(observer);
}

void ObservableSerialConnection::removeObserver(BaseObserver *observer) {
    auto iterator = std::find(_observers.begin(), _observers.end(), observer);

    if (iterator != _observers.end()) {
        _observers.erase(iterator);
    }
}

void ObservableSerialConnection::notifyObservers() {
    for(BaseObserver *observer : _observers) {
        observer->update();
    }
}