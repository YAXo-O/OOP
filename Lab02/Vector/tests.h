#ifndef TESTS_H
#define TESTS_H

#include <string>
#include "vector.h"

void doTests();

void constructors(); // Конструкторы/деструкторы
void equalsOperators(); // Операторы присвоения
void selfFunctions(); // Функции, выполняемые над вектором, вызыываемые из вектора
void vectorsOperators(); // Операции над векторами
void comparison(); // Сравнения векторов
void iterators(); // Итераторы
void idAccess(); // Доступ по индексу

template<typename T>
void printVec(const Vector<T> &v);

void drawTitle(std::string header, unsigned len = 70);

#endif // TESTS_H
