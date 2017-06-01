#ifndef VECTOR_H
#define VECTOR_H

#include <cstring>

size_t const scaleFactor = 2;

template<typename T>
struct vector
{
    T *data = nullptr;
    size_t size = 0; // Заполненный размер вектора
    size_t cap = 0; // Доступный для заполнения размер
};

template<typename T>
vector<T> constructVector(size_t initCap = 10)
{
   vector<T> vec;
   vec.data = new T[initCap];
   if(!vec.data)
   {
       vec.cap = 0;
       vec.size = 0;
       return vec;
   }

   vec.cap = initCap;
   vec.size = 0;

   return vec;
}

template<typename T>
void destroyVector(vector<T> &vec)
{
    delete[] vec.data;
    vec.data = nullptr;
    vec.size = vec.cap = 0;
}

template<typename T>
void resize(vector<T> &vec)
{
    size_t newCap = vec.cap*scaleFactor + 1;

    T *tmp = new T[newCap];
    if(tmp == nullptr)
        return;

    //std::copy(vec.data, vec.data + vec.cap, tmp);
    memcpy(tmp, vec.data, vec.size * sizeof(T));
    delete[] vec.data;
    vec.data = tmp;
    vec.cap = newCap;
}

template<typename T>
void push_back(vector<T> &vec, T elem)
{
    if(vec.size == vec.cap)
        resize(vec);

    vec.data[vec.size++] = elem;
}

template<typename T>
size_t count(vector<T> &vec)
{
    return vec.size;
}

template<typename T>
size_t reserved(vector<T> &vec)
{
    return vec.cap;
}

#endif // VECTOR_H
