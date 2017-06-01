#ifndef VECTORARRAY_H
#define VECTORARRAY_H

#include <algorithm>
#include <initializer_list>
#include "Object.h"
#include "exceptions.h"

template<typename T = double>
class VectorArray: public Object
{
public:
    VectorArray(size_t initSize = 10) throw(AllocFail);
    explicit VectorArray(const VectorArray &other) noexcept;
    VectorArray(const std::initializer_list<T> &list) throw(AllocFail);
    ~VectorArray() noexcept;

    VectorArray &operator=(const VectorArray &other) throw(AllocFail);
    const VectorArray &operator=(const VectorArray &other) const throw(AllocFail);
    T &operator[](size_t id) throw(OutOfRange);
    const T &operator[](size_t id) const throw(OutOfRange);

    T &at(size_t id) throw(OutOfRange);
    const T &at(size_t id) const throw(OutOfRange);
    void pushBack(T elem) throw(AllocFail);
    bool removeFirst(T elem) noexcept;
    bool removeLast(T elem) noexcept;
    // Подумать над pushBack и remove для ссылок

    size_t size() const noexcept;
    bool isEmpty() const noexcept;

    // Итератор самый простой - указатель
    // За валидностью этих итераторов никто не следит
    // За правильным их использованием тоже
    T *begin() noexcept;
    T *end() noexcept;
    const T *begin() const noexcept;
    const T *end() const noexcept;
    const T *cbegin() const noexcept;
    const T *cend() const noexcept;

private:
    void resize() throw(AllocFail);

protected:
    T *data;
    size_t count; // Кол-во заполненных ячеек массива
    size_t capacity; // Кол-во выделенных ячеек массива
};


template<typename T>
VectorArray<T>::VectorArray(size_t initSize) throw(AllocFail)
    try: Object(), data(new T[initSize]), count(0), capacity(initSize)
{
}
catch(const std::bad_alloc &ba)
{
    throw AllocFail("Allocation failure(id = " +  std::to_string(getId()) + "): " + ba.what());
}

template<typename T>
VectorArray<T>::VectorArray(const VectorArray &other) noexcept: Object(other), count(other.count), capacity(other.capacity)
{
    std::copy(other.data, other.data + count, data);
}

template<typename T>
VectorArray<T>::VectorArray(const std::initializer_list<T> &list) throw(AllocFail)
    try: Object(), data(new T[list.size()]), count(list.size()), capacity(list.size())
{
    size_t i = 0;
    for(auto elem: list)
        data[i++] = elem;
}
catch(const std::bad_alloc &ba)
{
    count = capacity = 0;
    data = nullptr;

    throw AllocFail("Allocation failure(id = " +  std::to_string(getId()) + "): " + ba.what());
}

template<typename T>
VectorArray<T>::~VectorArray() noexcept
{
    delete[] data;
}

template<typename T>
VectorArray<T> &VectorArray<T>::operator=(const VectorArray &other) throw(AllocFail)
{
    if(data)
        delete[] data;

    count = other.count;
    capacity = other.capacity;
    try
    {
        data = new T[capacity];
    }
    catch(const std::bad_alloc &ba)
    {
        count = capacity = 0;

        throw AllocFail("Allocation failure(id = " +  std::to_string(getId()) + "): " + ba.what());
    }

    std::copy(other.data, other.data + count, data);

    return *this;
}

template<typename T>
const VectorArray<T> &VectorArray<T>::operator=(const VectorArray &other) const throw(AllocFail)
{
    return operator=(other);
}

template<typename T>
T &VectorArray<T>::operator[](size_t id) throw(OutOfRange)
{
    if(id >= count)
        throw OutOfRange("Out of range: " + std::to_string(getId()));

    return data[id];
}

template<typename T>
const T &VectorArray<T>::operator[](size_t id) const throw(OutOfRange)
{
    if(id >= count)
        throw OutOfRange("Out of range(const): " + std::to_string(getId()));

    return data[id];
}

template<typename T>
T &VectorArray<T>::at(size_t id) throw(OutOfRange)
{
    return operator[](id);
}

template<typename T>
const T &VectorArray<T>::at(size_t id) const throw(OutOfRange)
{
    return operator[](id);
}

template<typename T>
void VectorArray<T>::pushBack(T elem) throw(AllocFail)
{
    if(capacity == count)
        resize();

    data[count++] = elem;
}

template<typename T>
bool VectorArray<T>::removeFirst(T elem) noexcept
{
    for(size_t i = 0; i < count; i++)
    {
        if(data[i] == elem)
        {
            std::copy(data + i + 1, data + count--, data + i);

            return true;
        }
    }

    return false;
}

template<typename T>
bool VectorArray<T>::removeLast(T elem) noexcept
{
    for(size_t i = count; i > 0;)
    {
        i--;

        if(data[i] == elem)
        {
            std::copy(data + i + 1, data + count--, data + i);

            return true;
        }
    }

    return false;
}

template<typename T>
size_t VectorArray<T>::size() const noexcept
{
    return count;
}

template<typename T>
bool VectorArray<T>::isEmpty() const noexcept
{
    return count == 0;
}

template<typename T>
T *VectorArray<T>::begin() noexcept
{
    return data;
}

template<typename T>
T *VectorArray<T>::end() noexcept
{
    return data + count;
}

template<typename T>
const T *VectorArray<T>::begin() const noexcept
{
    return data;
}

template<typename T>
const T *VectorArray<T>::end() const noexcept
{
    return data + count;
}

template<typename T>
const T *VectorArray<T>::cbegin() const noexcept
{
    return data;
}

template<typename T>
const T *VectorArray<T>::cend() const noexcept
{
    return data + count;
}

template<typename T>
void VectorArray<T>::resize() throw(AllocFail)
{
    try
    {
        int newCapacity = capacity*2 + 1;
        T *tmp = new T[newCapacity];

        std::copy(data, data + count, tmp);
        delete[] data;
        data = tmp;
        capacity = newCapacity;
    }
    catch(const std::bad_alloc &ba)
    {
        throw AllocFail("Allocation failure(id = " +  std::to_string(getId()) + "): " + ba.what());
    }
}

#endif // VECTORARRAY_H
