#include "observable.h"

void Observable::addObserver(Object *it) throw(AllocFail)
{
    observers.pushBack(it);
}

void Observable::deleteObserver(Object *it) noexcept
{
    observers.removeFirst(it);
}

void Observable::sendEvent() noexcept
{
    for(auto i : observers)
        i->eventTriggered();
}
