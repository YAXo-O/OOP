#ifndef ARRAY_H
#define ARRAY_H

#include "observable.h"
#include "constiter.h"

template<typename T = double>
class Array: public Object
{
public:
    explicit Array(size_t _size) throw(AllocFail);
    Array(T *arr, size_t _size) throw(AllocFail);
    Array(Array<T> &&arr) noexcept; // move constructor
    explicit Array(const Array<T> &arr) throw(AllocFail);
    Array(const std::initializer_list<T> &init) throw(AllocFail);
    Array(const basicIterator<T> &bIterator, const basicIterator<T> &eIterator) throw(AllocFail);
    ~Array() noexcept override;

    Array<T> &operator=(const Array<T> &arr) throw(AllocFail);
    Array<T> &operator=(Array<T> &&arr) noexcept;
    Array<T> &equalize(const Array<T> &arr) throw(AllocFail);
    T &operator[](size_t id) throw(OutOfRange);
    T& at(size_t id) throw(OutOfRange);
    const T &operator[](size_t id) const throw(OutOfRange);
    T at(size_t id) const throw(OutOfRange);

    size_t count() const noexcept;
    bool isEmpty() const noexcept;

    basicIterator<T> begin() noexcept;
    basicIterator<T> end() noexcept;
    constIterator<T> begin() const noexcept;
    constIterator<T> end() const noexcept;
    constIterator<T> cbegin() const noexcept;
    constIterator<T> cend() const noexcept;

    basicIterator<T> rbegin() noexcept;
    basicIterator<T> rend() noexcept;
    constIterator<T> rbegin() const noexcept;
    constIterator<T> rend() const noexcept;
    constIterator<T> crbegin() const noexcept;
    constIterator<T> crend() const noexcept;

private:
    T *data;
    size_t size;

    Observable *arrayObservable; // Используется для изменения состояния итераторов на невалидные
                                 // Итераторы становятся невалидными при удалении массива
};

template<typename T>
std::ostream &operator<<(std::ostream &out, const Array<T> &arr);

// Array - реализация

template<typename T>
Array<T>::Array(size_t _size) throw(AllocFail)
    try: Object(), data(new T[_size]), size(_size), arrayObservable(new Observable)
{
}
catch(std::bad_alloc &ba)
{
    throw AllocFail("Allocation failure(id = " +  std::to_string(getId()) + "): " + ba.what());
}

template<typename T>
Array<T>::Array(T *arr, size_t _size) throw(AllocFail)
    try: Object(), data(new T[_size]), size(_size), arrayObservable(new Observable)
{
    std::copy(arr, arr+size, data);
}
catch(const std::bad_alloc &ba)
{
    throw AllocFail("Allocation failure(id = " +  std::to_string(getId()) + "): " + ba.what());
}

template<typename T>
Array<T>::Array(Array<T> &&arr) noexcept
{
    data = arr.data;
    arr.data = nullptr;

    size = arr.size;
    arrayObservable = arr.arrayObservable;
    arr.arrayObservable = nullptr;
}

template<typename T>
Array<T>::Array(const Array<T> &arr) throw(AllocFail)
    try: Object(arr), data(new T[arr.size]), size(arr.size), arrayObservable(new Observable)
{
    std::copy(arr.data, arr.data + size, data);
}
catch(const std::bad_alloc &ba)
{
    throw AllocFail("Allocation failure(id = " +  std::to_string(getId()) + "): " + ba.what());
}

template<typename T>
Array<T>::Array(const std::initializer_list<T> &init) throw(AllocFail)
    try: Object(), data(new T[init.size()]), size(init.size()), arrayObservable(new Observable)
{
    size_t i = 0;
    for(auto elem: init)
        data[i++] = elem;
}
catch(const std::bad_alloc &ba)
{
    throw AllocFail("Allocation failure(id = " +  std::to_string(getId()) + "): " + ba.what());
}

template<typename T>
Array<T>::Array(const basicIterator<T> &bIterator,const basicIterator<T> &eIterator) throw(AllocFail)
    try: Object(), data(new T[eIterator - bIterator]), size(eIterator - bIterator), arrayObservable(new Observable)
{
    basicIterator<T> cur(bIterator);
    for(size_t i = 0; cur != eIterator; cur++, i++)
        data[i] = *cur;
}
catch(const std::bad_alloc &ba)
{
    throw AllocFail("Allocation failure(id = " +  std::to_string(getId()) + "): " + ba.what());
}

template<typename T>
Array<T>::~Array() noexcept
{
    if(data)
        delete[] data;

    if(arrayObservable)
    {
        arrayObservable->sendEvent();
        delete arrayObservable;
    }
}

template<typename T>
Array<T> &Array<T>::operator=(const Array<T> &arr) throw(AllocFail)
{
    if(data)
        delete[] data;

    size = arr.size;
    try
    {
        data = new T[size];
    }
    catch(const std::bad_alloc &ba)
    {
        size = 0;

        throw AllocFail("Allocation failure(id = " +  std::to_string(getId()) + "): " + ba.what());
    }

    std::copy(arr.data, arr.data + size, data);

    return *this;
}

template<typename T>
Array<T> &Array<T>::operator=(Array<T> &&arr) noexcept
{
    if(data)
        delete[] data;
    if(arrayObservable)
        delete arrayObservable;

    size = arr.size;

    data = arr.data;
    arr.data = nullptr;

    arrayObservable = arr.arrayObservable;
    arr.arrayObservable = nullptr;

    return *this;
}

template<typename T>
T &Array<T>::operator[](size_t id) throw(OutOfRange)
{
    if(id >= size)
        throw OutOfRange("Out of range: " + std::to_string(getId()));

    return data[id];
}

template<typename T>
const T &Array<T>::operator[](size_t id) const throw(OutOfRange)
{
    if(id >= size)
        throw OutOfRange("Out of range: " + std::to_string(getId()));

    return data[id];
}

template<typename T>
Array<T> &Array<T>::equalize(const Array<T> &arr) throw(AllocFail)
{
    return *this = arr;
}

template<typename T>
T &Array<T>::at(size_t id) throw(OutOfRange)
{
    return data[id];
}

template<typename T>
T Array<T>::at(size_t id) const throw(OutOfRange)
{
    return data[id];
}

template<typename T>
size_t Array<T>::count() const noexcept
{
    return size;
}

template<typename T>
bool Array<T>::isEmpty() const noexcept
{
    return size == 0;
}


template<typename T>
basicIterator<T> Array<T>::begin() noexcept
{
    basicIterator<T> iter(data);
    arrayObservable->addObserver(&iter);
    iter.setEventMaster(arrayObservable);

    return iter;
}

template<typename T>
basicIterator<T> Array<T>::end() noexcept
{
    basicIterator<T> iter(data + size);
    arrayObservable->addObserver(&iter);
    iter.setEventMaster(arrayObservable);

    return iter;
}

template<typename T>
constIterator<T> Array<T>::begin() const noexcept
{
    constIterator<T> iter(data);
    arrayObservable->addObserver(&iter);
    iter.setEventMaster(arrayObservable);

    return iter;
}

template<typename T>
constIterator<T> Array<T>::end() const noexcept
{
    constIterator<T> iter(data + size);
    arrayObservable->addObserver(&iter);
    iter.setEventMaster(arrayObservable);

    return iter;
}

template<typename T>
constIterator<T> Array<T>::cbegin() const noexcept
{
    constIterator<T> iter(data);
    arrayObservable->addObserver(&iter);
    iter.setEventMaster(arrayObservable);

    return iter;
}

template<typename T>
constIterator<T> Array<T>::cend() const noexcept
{
    constIterator<T> iter(data + size);
    arrayObservable->addObserver(&iter);
    iter.setEventMaster(arrayObservable);

    return iter;
}

template<typename T>
basicIterator<T> Array<T>::rbegin() noexcept
{
    basicIterator<T> iter(data - 1);
    arrayObservable->addObserver(&iter);
    iter.setEventMaster(arrayObservable);

    return iter;
}

template<typename T>
basicIterator<T> Array<T>::rend() noexcept
{
    basicIterator<T> iter(data + size - 1);
    arrayObservable->addObserver(&iter);
    iter.setEventMaster(arrayObservable);

    return iter;
}

template<typename T>
constIterator<T> Array<T>::rbegin() const noexcept
{
    constIterator<T> iter(data - 1);
    arrayObservable->addObserver(&iter);
    iter.setEventMaster(arrayObservable);

    return iter;
}

template<typename T>
constIterator<T> Array<T>::rend() const noexcept
{
    constIterator<T> iter(data + size - 1);
    arrayObservable->addObserver(&iter);
    iter.setEventMaster(arrayObservable);

    return iter;
}


template<typename T>
constIterator<T> Array<T>::crbegin() const noexcept
{
    constIterator<T> iter(data - 1);
    arrayObservable->addObserver(&iter);
    iter.setEventMaster(arrayObservable);

    return iter;
}

template<typename T>
constIterator<T> Array<T>::crend() const noexcept
{
    constIterator<T> iter(data + size - 1);
    arrayObservable->addObserver(&iter);
    iter.setEventMaster(arrayObservable);

    return iter;
}

template<typename T>
std::ostream &operator<<(std::ostream &out, const Array<T> &arr)
{
    for(auto i: arr)
        out << i << " ";
    out << std::endl;

    return out;
}

#endif // ARRAY_H
