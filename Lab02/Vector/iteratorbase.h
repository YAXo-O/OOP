#ifndef ITERATORBASE_H
#define ITERATORBASE_H

#include "observable.h"

// В базовом итераторе реализованы функции обхода
// Для обычного массива
// В случае нужды особого обхода/другого контейнера нужно
// Переписать в дочерних классах соответствующие методы

template<typename T>
class basicIterator: public Object
{
public:
    basicIterator(Observable *master = nullptr) noexcept;
    basicIterator(const basicIterator<T> &other) noexcept;
    basicIterator(T &elem, Observable *master = nullptr) noexcept;
    basicIterator(T *elemPtr, Observable *master = nullptr) noexcept;
    ~basicIterator() noexcept;

    basicIterator &operator=(const basicIterator &other) noexcept;
    T &operator*() throw(InvalidIterator);
    const T &operator*() const throw(InvalidIterator);
    bool operator==(const basicIterator &other) const noexcept;
    bool operator!=(const basicIterator &other) const noexcept;
    size_t operator-(const basicIterator &other) const noexcept;
    basicIterator &operator++() noexcept;
    basicIterator &operator--() noexcept;
    basicIterator operator++(int) noexcept;
    basicIterator operator--(int) noexcept;
    basicIterator &operator+=(size_t offset) noexcept;
    basicIterator &operator-=(size_t offset) noexcept;
    basicIterator operator+(size_t offset) noexcept;
    basicIterator operator-(size_t offset) noexcept;

    bool isValid() const noexcept;
    void eventTriggered() noexcept override;


protected:
    T *ptr;

private:
    bool bValid;
};

template<typename T>
basicIterator<T>::basicIterator(Observable *master) noexcept: Object(master), ptr(nullptr), bValid(true)
{
}

template<typename T>
basicIterator<T>::basicIterator(const basicIterator<T> &other) noexcept: Object(other), ptr(other.ptr), bValid(true)
{
}

template<typename T>
basicIterator<T>::basicIterator(T &elem, Observable *master) noexcept: Object(master), ptr(&elem), bValid(true)
{
}

template<typename T>
basicIterator<T>::basicIterator(T *elemPtr, Observable *master) noexcept: Object(master), ptr(elemPtr), bValid(true)
{
}

template<typename T>
basicIterator<T>::~basicIterator() noexcept
{
    getEventMaster()->deleteObserver(this);
}

template<typename T>
basicIterator<T> &basicIterator<T>::operator=(const basicIterator<T> &other) noexcept
{
    ptr = other.ptr;
}

template<typename T>
T &basicIterator<T>::operator*() throw(InvalidIterator)
{
    if(!isValid())
        throw InvalidIterator("Invalid iterator access: id = " + std::to_string(getId()) + ";");

    return *ptr;
}

template<typename T>
const T &basicIterator<T>::operator*() const throw(InvalidIterator)
{
    if(!isValid())
        throw InvalidIterator("Invalid iterator access: id = " + std::to_string(getId()) + ";");

    return *ptr;
}

template<typename T>
bool basicIterator<T>::operator==(const basicIterator<T> &other) const noexcept
{
    return other.ptr == ptr;
}

template<typename T>
bool basicIterator<T>::operator!=(const basicIterator<T> &other) const noexcept
{
    return !(*this == other);
}

template<typename T>
size_t basicIterator<T>::operator-(const basicIterator<T> &other) const noexcept
{
    return ptr - other.ptr;
}

template<typename T>
basicIterator<T> &basicIterator<T>::operator++() noexcept
{
    ++ptr;

    return *this;
}

template<typename T>
basicIterator<T> &basicIterator<T>::operator--() noexcept
{
    --ptr;

    return *this;
}

template<typename T>
basicIterator<T> basicIterator<T>::operator++(int) noexcept
{
    auto tmp = *this;
    ptr++;

    return tmp;
}

template<typename T>
basicIterator<T> basicIterator<T>::operator--(int) noexcept
{
    auto tmp = *this;
    ptr--;

    return tmp;
}

template<typename T>
basicIterator<T> &basicIterator<T>::operator+=(size_t offset) noexcept
{
    ptr += offset;

    return *this;
}

template<typename T>
basicIterator<T> &basicIterator<T>::operator-=(size_t offset) noexcept
{
    ptr -= offset;

    return *this;
}

template<typename T>
basicIterator<T> basicIterator<T>::operator+(size_t offset) noexcept
{
    auto tmp = *this;
    tmp += offset;

    return tmp;
}

template<typename T>
basicIterator<T> basicIterator<T>::operator-(size_t offset) noexcept
{
    auto tmp = *this;
    tmp -= offset;

    return tmp;
}

template<typename T>
bool basicIterator<T>::isValid() const noexcept
{
    return bValid;
}

template<typename T>
void basicIterator<T>::eventTriggered() noexcept
{
    bValid = false;
}

#endif // ITERATORBASE_H
