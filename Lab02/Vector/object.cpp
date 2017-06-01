#include "object.h"

size_t Object::idGen = 0;

Object::Object(Observable *_eventMaster): id(idGen++), eventMaster(_eventMaster)
{
}

Object::Object(const Object &other): id(idGen++), eventMaster(other.eventMaster)
{
}

Object &Object::operator=(const Object & other)
{
    eventMaster = other.eventMaster;

    return *this;
}

size_t Object::getId() const
{
    return id;
}

void Object::eventTriggered()
{
    // В Объекте не делает ничего - поведение определяется дочерним классом
}

void Object::setEventMaster(Observable *master)
{
    eventMaster = master;
}

Observable *Object::getEventMaster() const
{
    return eventMaster;
}
