#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include "Object.h"
#include "vectorarray.h"

/* Observable */
// Наблюдаемый - используется для отправки сигнала всем наблюдателям
// В данном случае используется для оповещания итераторов об их невалидности
class Observable
{
public:
    void addObserver(Object *it) throw(AllocFail);
    void deleteObserver(Object *it) noexcept;
    void sendEvent() noexcept;

private:
    VectorArray<Object *> observers;
};

#endif // OBSERVABLE_H
