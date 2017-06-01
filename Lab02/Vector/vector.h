#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>
#include <iostream>
#include "array.h"

template<typename T = double>
class Vector: public Object
{
public:
    explicit Vector(size_t dim = 3) throw(AllocFail);
    explicit Vector(const Vector<T> &other) throw(AllocFail);
    Vector(Vector<T> &&other) noexcept;
    explicit Vector(const Array<T> &arr) throw(AllocFail);
    Vector(const std::initializer_list<T> &list) throw(AllocFail);
    Vector(const basicIterator<T> &begin, const basicIterator<T> &end) throw(AllocFail);
    ~Vector() noexcept = default;

    Vector<T> &operator=(const Vector<T> &other) throw(AllocFail);
    Vector<T> &operator=(Vector<T> &&other) noexcept;
    Vector<T> &equalize(const Vector<T> &other) throw(AllocFail);
    Vector<T> &operator+=(const Vector<T> &other) throw(SizeMissmatch);
    Vector<T> &add(const Vector<T> &other) throw(SizeMissmatch);
    Vector<T> &operator-=(const Vector<T> &other) throw(SizeMissmatch);
    Vector<T> &subtract(const Vector<T> &other) throw(SizeMissmatch);
    Vector<T> &operator*=(double scalar) noexcept;
    Vector<T> &multiply(double scalar) noexcept;
    Vector<T> &operator/=(double scalar) throw(DivisionZero);
    Vector<T> &divide(double scalar) throw(DivisionZero);
    Vector<T> &operator^=(const Vector<T> &other) throw(NonThreeD); // Векторное произведение
    Vector<T> &selfVectorProduct(const Vector<T> &other) throw(NonThreeD);

    Vector<T> operator+(const Vector<T> &other) const throw(SizeMissmatch);
    Vector<T> operator-(const Vector<T> &other) const throw(SizeMissmatch);
    double operator*(const Vector<T> &other) const throw(SizeMissmatch); //Скалярное произведение
    double dotProduct(const Vector<T> &other) const throw(SizeMissmatch); // Скалярное произведение
    Vector<T> operator*(double scalar) const noexcept; // Умножение на скаляр
    Vector<T> operator/(double scalar) const throw(DivisionZero);
    Vector<T> operator^(const Vector<T> &other) const throw(NonThreeD); // Векторное произведение
    Vector<T> vectorProduct(const Vector<T> &other) const throw(NonThreeD);

    bool operator==(const Vector<T> &other) const throw(SizeMissmatch);
    bool operator!=(const Vector<T> &other) const throw(SizeMissmatch);
    bool isEqual(const Vector<T> &other) const throw(SizeMissmatch);
    bool operator||(const Vector<T> &other) const throw(SizeMissmatch); // Проверка на параллельность; Погрешность = 0
    bool checkParallel(const Vector<T> &other, double tolerance = 0) const throw(SizeMissmatch); // Погрешность задаётся

    T &operator[](size_t id) throw(OutOfRange);
    const T &operator[](size_t id) const throw(OutOfRange);
    T &at(size_t id) throw(OutOfRange);
    const T &at(size_t id) const throw(OutOfRange);

    double getLength() const noexcept;
    double angle(const Vector<T> &other) const throw(DivisionZero); // Угл в радианах
    bool isNull(double tolerance = 0) const noexcept; // Нулевой вектор?
    size_t dimensions() const noexcept;

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
    Array<T> _vec;
};

template<typename T>
std::ostream &operator<<(std::ostream &out, const Vector<T> &v);

template<typename T>
Vector<T> operator*(double scalar,const Vector<T> &vec);

// Vector - реализация

template<typename T>
Vector<T>::Vector(size_t dim) throw(AllocFail): Object(), _vec(dim)
{
}

template<typename T>
Vector<T>::Vector(Vector<T> &&other) noexcept : _vec(0)
{
    std::swap(_vec, other._vec);
}


template<typename T>
Vector<T>::Vector(const Vector &other) throw(AllocFail): Object(other), _vec(other._vec)
{
}

template<typename T>
Vector<T>::Vector(const Array<T> &arr) throw(AllocFail): Object(), _vec(arr)
{
}

template<typename T>
Vector<T>::Vector(const std::initializer_list<T> &list) throw(AllocFail): Object(), _vec(list)
{
}

template<typename T>
Vector<T>::Vector(const basicIterator<T> &begin, const basicIterator<T> &end) throw(AllocFail)
    : Object(), _vec(begin, end)
{
}

template<typename T>
Vector<T> &Vector<T>::operator=(const Vector &other) throw(AllocFail)
{
    _vec = other._vec;

    return *this;
}

template<typename T>
Vector<T> &Vector<T>::operator=(Vector<T> &&other) noexcept
{
    std::swap(_vec, other._vec);

    return *this;
}

template<typename T>
Vector<T> &Vector<T>::operator+=(const Vector &other) throw(SizeMissmatch)
{
    if(_vec.count() != other._vec.count())
        throw SizeMissmatch("Size missmatch: left id:" + std::to_string(this->getId()) + "; right id: " + std::to_string(other.getId()));

    for(size_t i = 0; i < _vec.count(); i++)
        _vec[i] += other._vec[i];

    return *this;
}

template<typename T>
Vector<T> &Vector<T>::operator-=(const Vector &other) throw(SizeMissmatch)
{
    if(_vec.count() != other._vec.count())
        throw SizeMissmatch("Size missmatch: left id:" + std::to_string(this->getId()) + "; right id: " + std::to_string(other.getId()));

    for(size_t i = 0; i < _vec.count(); i++)
        _vec[i] -= other._vec[i];

    return *this;
}

template<typename T>
Vector<T> &Vector<T>::operator*=(double scalar) noexcept
{
    for(size_t i = 0; i < _vec.count(); i++)
        _vec[i] *= scalar;

    return *this;
}

template<typename T>
Vector<T> &Vector<T>::operator/=(double scalar) throw(DivisionZero)
{
    if(!scalar)
        throw DivisionZero("Divide by zero: id = " + std::to_string(this->getId()));

    for(size_t i = 0; i < _vec.count(); i++)
        _vec[i] /= scalar;

    return *this;
}

template<typename T>
double Vector<T>::dotProduct(const Vector &other) const throw(SizeMissmatch)
{
    return operator*(other);
}


template<typename T>
Vector<T> &Vector<T>::equalize(const Vector &other) throw(AllocFail)
{
    return operator=(other);
}

template<typename T>
Vector<T> &Vector<T>::add(const Vector &other) throw(SizeMissmatch)
{
    return operator+=(other);
}

template<typename T>
Vector<T> &Vector<T>::subtract(const Vector &other) throw(SizeMissmatch)
{
    return operator-=(other);
}

template<typename T>
Vector<T> &Vector<T>::multiply(double scalar) noexcept
{
    return operator*=(scalar);
}

template<typename T>
Vector<T> &Vector<T>::divide(double scalar) throw(DivisionZero)
{
    return operator/=(scalar);
}

template<typename T>
Vector<T> &Vector<T>::operator^=(const Vector<T> &other) throw(NonThreeD)
{
    /*
     | i| j| k|
     |x1|y1|z1| = i*(y1*z2 - y2*z1) - j(x1*z2 - x2*z1) + k(x1*y2 - x2*y1)
     |x2|y2|z2|
     */

    if(_vec.count() != 3 || other._vec.count() != 3)
        throw NonThreeD("Only 3d vectors are acceptable; Current ids: " +
                        std::to_string(this->getId()) + "; " + std::to_string(other.getId()));

    Array<T> tmp(3);

    tmp[0] = _vec[1]*other._vec[2] - other._vec[1]*_vec[2];
    tmp[1] = -(_vec[0]*other._vec[2] - other._vec[0]*_vec[2]);
    tmp[2] = _vec[0]*other._vec[1] - other._vec[0]*_vec[1];

    _vec = tmp;

    return *this;
}

template<typename T>
Vector<T> &Vector<T>::selfVectorProduct(const Vector<T> &other) throw(NonThreeD)
{
    return operator^=(other);
}

template<typename T>
Vector<T> Vector<T>::vectorProduct(const Vector<T> &other) const throw(NonThreeD)
{
    if(_vec.count() != 3 || other._vec.count() != 3)
        throw NonThreeD("Only 3d vectors are acceptable; Current ids: " +
                        std::to_string(this->getId()) + "; " + std::to_string(other.getId()));

    Vector<T> tmp(3);
    tmp[0] = _vec[1]*other._vec[2] - other._vec[1]*_vec[2];
    tmp[1] = -(_vec[0]*other._vec[2] - other._vec[0]*_vec[2]);
    tmp[2] = _vec[0]*other._vec[1] - other._vec[0]*_vec[1];

    return tmp;
}

template<typename T>
Vector<T> Vector<T>::operator+(const Vector<T> &other) const throw(SizeMissmatch)
{
    if(_vec.count() != other._vec.count())
        throw SizeMissmatch("Size missmatch: left id:" + std::to_string(this->getId()) + "; right id: " + std::to_string(other.getId()));

    Vector<T> tmp(dimensions());
    for(size_t i = 0; i < _vec.count(); i++)
        tmp._vec[i] = _vec[i] + other._vec[i];

    return tmp;
}

template<typename T>
Vector<T> Vector<T>::operator-(const Vector<T> &other) const throw(SizeMissmatch)
{
    if(_vec.count() != other._vec.count())
        throw SizeMissmatch("Size missmatch: left id:" + std::to_string(this->getId()) + "; right id: " + std::to_string(other.getId()));

    Vector<T> tmp(dimensions());

    for(size_t i = 0; i < _vec.count(); i++)
        tmp._vec[i] = _vec[i] - other._vec[i];

    return tmp;
}

template<typename T>
double Vector<T>::operator*(const Vector &other) const throw(SizeMissmatch)
{
    if(_vec.count() != other._vec.count())
        throw SizeMissmatch("Size missmatch: left id:" + std::to_string(this->getId()) + "; right id: " + std::to_string(other.getId()));


    double res = 0;
    for(size_t i = 0; i < _vec.count(); i++)
        res += other._vec[i]*_vec[i];

    return res;
}

template<typename T>
Vector<T> Vector<T>::operator*(double scalar) const noexcept
{
    Vector v(*this);
    for(size_t i = 0; i < _vec.count(); i++)
        v._vec[i] *= scalar;

    return v;
}

template<typename T>
Vector<T> Vector<T>::operator/(double scalar) const throw(DivisionZero)
{
    if(!scalar)
        throw DivisionZero("Divide by zero: id = " + std::to_string(this->getId()));

    Vector v(*this);
    for(size_t i = 0; i < _vec.count(); i++)
        v._vec[i] /= scalar;

    return v;
}

template<typename T>
Vector<T> Vector<T>::operator^(const Vector<T> &other) const throw(NonThreeD)
{
    return vectorProduct(other);
}

template<typename T>
bool Vector<T>::operator==(const Vector &other) const throw(SizeMissmatch)
{
    if(_vec.count() != other._vec.count())
        throw SizeMissmatch("Size missmatch: left id:" + std::to_string(this->getId()) + "; right id: " + std::to_string(other.getId()));

    for(size_t i = 0; i < _vec.count(); i++)
        if(other._vec[i] != _vec[i])
            return false;

    return true;
}

template<typename T>
bool Vector<T>::operator!=(const Vector &other) const throw(SizeMissmatch)
{
    return !(operator==(other));
}

template<typename T>
bool Vector<T>::operator||(const Vector<T> &other) const throw(SizeMissmatch)
{
    return checkParallel(other);
}

template<typename T>
bool Vector<T>::checkParallel(const Vector<T> &other, double tolerance) const throw(SizeMissmatch)
{
    if(dimensions() != other.dimensions())
        throw SizeMissmatch("Missmatching vectors parallel check attempt: id1:" + std::to_string(this->getId()) +
                            "; id2: " + std::to_string(other.getId()));

    return fabs(fabs(dotProduct(other)) - getLength()*other.getLength()) <= tolerance; // Дольше, чем через угол
                                                                                       // Но точнее
}

template<typename T>
bool Vector<T>::isEqual(const Vector &other) const throw(SizeMissmatch)
{
    return operator==(other);
}

template<typename T>
T &Vector<T>::operator[](size_t id) throw(OutOfRange)
{

    return _vec[id];
}

template<typename T>
const T &Vector<T>::operator[](size_t id) const throw(OutOfRange)
{

    return _vec[id];
}

template<typename T>
T &Vector<T>::at(size_t id) throw(OutOfRange)
{
    return operator[](id);
}

template<typename T>
const T &Vector<T>::at(size_t id) const throw(OutOfRange)
{
    return operator[](id);
}

template<typename T>
double Vector<T>::getLength() const noexcept
{
    double squares = 0;
    for(size_t i = 0; i < _vec.count(); i++)
        squares += pow(_vec[i], 2);

    return sqrt(squares);
}

template<typename T>
double Vector<T>::angle(const Vector &other) const throw(DivisionZero)
{
    double len1 = getLength();
    double len2 = other.getLength();

    if(!len1 && !len2)
        throw DivisionZero("Zero length of vectors: id: " + std::to_string(this->getId()) +
                           "; id: " + std::to_string(other.getId()));

    return acos(operator*(other)/(len1+len2));
}

template<typename T>
bool Vector<T>::isNull(double tolerance) const noexcept
{
    for(auto i: _vec)
        if(fabs(i) > tolerance)
            return false;

    return true;
}

template<typename T>
size_t Vector<T>::dimensions() const noexcept
{
    return _vec.count();
}

template<typename T>
basicIterator<T> Vector<T>::begin() noexcept
{
    return _vec.begin();
}

template<typename T>
basicIterator<T> Vector<T>::end() noexcept
{
    return _vec.end();
}

template<typename T>
constIterator<T> Vector<T>::begin() const noexcept
{
    return _vec.begin();
}

template<typename T>
constIterator<T> Vector<T>::end() const noexcept
{
    return _vec.end();
}

template<typename T>
constIterator<T> Vector<T>::cbegin() const noexcept
{
    return _vec.cbegin();
}

template<typename T>
constIterator<T> Vector<T>::cend() const noexcept
{
    return _vec.cend();
}

template<typename T>
basicIterator<T> Vector<T>::rbegin() noexcept
{
    return _vec.rbegin();
}

template<typename T>
basicIterator<T> Vector<T>::rend() noexcept
{
    return _vec.rend();
}

template<typename T>
constIterator<T> Vector<T>::rbegin() const noexcept
{
    return _vec.rbegin();
}

template<typename T>
constIterator<T> Vector<T>::rend() const noexcept
{
    return _vec.rend();
}

template<typename T>
constIterator<T> Vector<T>::crbegin() const noexcept
{
    return _vec.crbegin();
}

template<typename T>
constIterator<T> Vector<T>::crend() const noexcept
{
    return _vec.crend();
}

template<typename T>
std::ostream &operator<<(std::ostream &out, const Vector<T> &v)
{
    for(auto i : v)
        out << i << " ";
    out << std::endl;

    return out;
}

template<typename T>
Vector<T> operator*(double scalar,const Vector<T> &vec)
{
    return vec*scalar;
}

#endif // VECTOR_H
