#pragma once
#include "Observer.h"
#include <vector>
class Observable {

public:
    virtual void AddObserver(Observer* _observer) = 0;
    virtual void RemoveObserser(Observer* _observer) = 0;
    virtual void NotifyObservers() = 0;
};
