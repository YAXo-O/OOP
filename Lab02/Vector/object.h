#ifndef OBJECT_H
#define OBJECT_H

#include <cctype>

class Observable;

class Object
{
public:
    Object(Observable *_eventMaster = nullptr);
    Object(const Object &other);
    virtual ~Object() = default;

    Object &operator=(const Object &other);

    size_t getId() const;

    virtual void eventTriggered();
    void setEventMaster(Observable *master);
    Observable *getEventMaster() const;

private:
    size_t id;
    static size_t idGen;

    Observable *eventMaster;
};

#endif // OBJECT_H
