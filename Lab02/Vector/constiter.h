#ifndef CONSTITER_H
#define CONSTITER_H

#include "iteratorbase.h"

template<typename T>
class constIterator: public basicIterator<T>
{
public:
    constIterator(Observable *master = nullptr) noexcept;
    constIterator(const basicIterator<T> &other) noexcept;
    constIterator(T &elem, Observable *master = nullptr) noexcept;
    constIterator(T *elemPtr, Observable *master = nullptr) noexcept;
    ~constIterator() noexcept;

    const T &operator*() const throw(InvalidIterator);

//private:
//    T &operator*() throw(InvalidIterator);
};

template<typename T>
constIterator<T>::constIterator(Observable *master) noexcept: basicIterator<T>::basicIterator(master)
{
}

template<typename T>
constIterator<T>::constIterator(const basicIterator<T> &other) noexcept: basicIterator<T>::basicIterator(other)
{
}

template<typename T>
constIterator<T>::constIterator(T &elem, Observable *master) noexcept: basicIterator<T>::basicIterator(elem, master)
{
}

template<typename T>
constIterator<T>::constIterator(T *elemPtr, Observable *master) noexcept: basicIterator<T>::basicIterator(elemPtr, master)
{
}

template<typename T>
constIterator<T>::~constIterator() noexcept
{
    basicIterator<T>::~basicIterator();
}

template<typename T>
const T &constIterator<T>::operator*() const throw(InvalidIterator)
{
    return basicIterator<T>::operator*();
}

#endif // CONSTITER_H
