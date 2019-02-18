#ifndef BASEOBSERVABLE_HPP
#define BASEOBSERVABLE_HPP

#include "lib/observer/BaseObserver.hpp"

/* Interface */

class BaseObservable {
    public:
        virtual void addObserver(BaseObserver *baseObserver) = 0;
        virtual void removeObserver(BaseObserver *baseObserver) = 0;
        virtual void notifyObservers() = 0;
};

#endif