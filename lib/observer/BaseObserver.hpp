#ifndef BASEOBSERVER_HPP
#define BASEOBSERVER_HPP

/* Interface */

class BaseObserver {
    public:
        virtual void update() = 0;
};

#endif