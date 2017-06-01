#include <iostream>
#include "tests.h"

void doTests()
{
    constructors();
    equalsOperators();
    selfFunctions();
    vectorsOperators();
    comparison();
    iterators();
    idAccess();
}

void constructors()
{
    drawTitle("constructors");

    try
    {
        Vector<> v1(1000000000);
    }
    catch(const AllocFail &fail)
    {
        std::cout << "v1(too big size reservation) failure: " << fail.what() << std::endl;
    }

    Vector<> v1 = {0, 1, 2, 3, 4};
    Vector<> v2(v1);
    Vector<> v3(v1.begin(), v1.begin() + 2);
    Array<> arr = {4, 3, 2, 1};
    Vector<> v4(arr);
    Vector<> v5(0);
    v5 = {3, 4, 5};

    std::cout << "v1(initializer list): ";
    printVec(v1);

    std::cout << "v2(copy constructor): ";
    printVec(v2);

    std::cout << "v3(iterators): ";
    printVec(v3);

    std::cout << "v4(from array): ";
    printVec(v4);

    std::cout << "v5(move constructor): ";
    printVec(v5);
}

void selfFunctions()
{
    drawTitle("self functions");
    Vector<> v1 = {10, 0, 0};
    std::cout << "v1: ";
    printVec(v1);

    Vector<> v2(3);
    v2.equalize(v1);
    std::cout << "v2(equalize): ";
    printVec(v2);

    v2.add(v1);
    std::cout << "v2(add v1): ";
    printVec(v2);

    v2.subtract(v1);
    std::cout << "v2(subtract v1): ";
    printVec(v2);

    v2.multiply(2);
    std::cout << "v2(multiply 2): ";
    printVec(v2);

    v2.divide(2);
    std::cout << "v2(divide 2): ";
    printVec(v2);

    v2.selfVectorProduct(v1);
    std::cout << "v2(selfVectorProduct v1): ";
    printVec(v2);

    Vector<> v3 = {0, 1};
    std::cout << "v3: ";
    printVec(v3);

    try
    {
        v2.add(v3);
    }
    catch(const SizeMissmatch &m)
    {
        std::cout << "v2 + v3 size missmatch: " << m.what() << std::endl;
    }

    try
    {
        v2.subtract(v3);
    }
    catch(const SizeMissmatch &m)
    {
        std::cout << "v2 - v3 size missmatch: " << m.what() << std::endl;
    }

    try
    {
        v2.divide(0);
    }
    catch(const DivisionZero &div)
    {
        std::cout <<"v2/0 division error: " << div.what() << std::endl;
    }


    Vector<> v4 = {0, 10, 0};
    std::cout << "v4: ";
    printVec(v4);
    Vector<> v5 = v2.vectorProduct(v4);

    std::cout << "v5(v2*v4 - vector product): ";
    printVec(v5);

    std::cout << "v4*v5 - scalar product: " << v4.dotProduct(v5) << std::endl;

    try
    {
        v2.vectorProduct(v3);
    }
    catch(const NonThreeD &d)
    {
        std::cout << "v2*v3 - vector product;" << d.what() << std::endl;
    }

}

void vectorsOperators()
{
    drawTitle("vectors operators");

    Vector<> v1 = {10, 0, 0};
    Vector<> v2 = {0, 0, 10};
    Vector<> v3 = {0, 10};
    std::cout << "v1: ";
    printVec(v1);
    std::cout << "v2: ";
    printVec(v2);
    std::cout << "v3: ";
    printVec(v3);

    std::cout << "v1 + v2: ";
    printVec(v1 + v2);
    std::cout << "v1 - v2: ";
    printVec(v1 - v2);
    std::cout << "v1*v2 - scalar: " << v1*v2 << std::endl;
    std::cout << "v1*2: ";
    printVec(v1*2);
    std::cout << "v1/2: ";
    printVec(v1/2);
    std::cout << "[v1 x v2]: ";
    printVec(v1^v2);

    try
    {
        v1 + v3;
    }
    catch(const SizeMissmatch &m)
    {
        std::cout << "v1 + v3: " << m.what() << std::endl;
    }

    try
    {
        v1 - v3;
    }
    catch(const SizeMissmatch &m)
    {
        std::cout << "v1 - v3: " << m.what() << std::endl;
    }

    try
    {
        v1 * v3;
    }
    catch(const SizeMissmatch &m)
    {
        std::cout << "v1 * v3: " << m.what() << std::endl;
    }

    try
    {
        v1/0;
    }
    catch(const DivisionZero &div)
    {
        std::cout << "v1/0: " << div.what() << std::endl;
    }

    try
    {
        v1^v3;
    }
    catch(const NonThreeD &e)
    {
        std::cout << "[v1^v3]: " << e.what() << std::endl;
    }
}

void comparison()
{
    drawTitle("Vector comparisons");

    Vector<> v1 = {10, 0, 0};
    Vector<> v2 = {10, 0, 0};
    Vector<> v3 = {0, 10, 0};
    Vector<> v4 = {10, 0};

    std::cout << "v1: ";
    printVec(v1);
    std::cout << "v2: ";
    printVec(v2);
    std::cout << "v3: ";
    printVec(v3);
    std::cout << "v4: ";
    printVec(v4);

    std::cout << "v1 == v2: " << (v1 == v2) << std::endl;
    std::cout << "v1 == v3: " << (v1 == v3) << std::endl;
    std::cout << "v1.isEqual(v2): " << v1.isEqual(v2) << std::endl;
    std::cout << "v1.isEqual(v3): " << v1.isEqual(v3) << std::endl;
    std::cout << "v1 != v2: " << (v1 != v2) << std::endl;
    std::cout << "v1 != v3: " << (v1 != v3) << std::endl;
    std::cout << "v1 || v2: " << (v1 || v2) << std::endl;
    std::cout << "v1.checkParallel(v2, 0.1): " << v1.checkParallel(v2, 0.1) << std::endl;
    std::cout << "v1 || v3: " << (v1 || v3) << std::endl;
    std::cout << "v1.checkParallel(v3, 0.1): " << v1.checkParallel(v3, 0.1) << std::endl;

    try
    {
        v1 == v4;
    }
    catch(const SizeMissmatch &s)
    {
        std::cout << "v1 == v4: " << s.what() << std::endl;
    }

    try
    {
        v1 != v4;
    }
    catch(const SizeMissmatch &s)
    {
        std::cout << "v1 != v4: " << s.what() << std::endl;
    }

    try
    {
        v1.isEqual(v4);
    }
    catch(const SizeMissmatch &s)
    {
        std::cout << "v1.isEqual(v4): " << s.what() << std::endl;
    }
}

void iterators()
{
    drawTitle("Iterators");

    Vector<> v1 = {0, 10, 2, 15};
    std::cout << "v1: ";
    printVec(v1);

    std::cout << "Forward iterators: {";
    for(auto i : v1)
        std::cout << i << " ";
    std::cout << "}" << std::endl;

    std::cout << "Reverse iterators: {";
    for(auto i  = v1.rend(); i != v1.rbegin(); i--)
        std::cout << *i << " ";
    std::cout << "}" << std::endl;
}

void equalsOperators()
{
    drawTitle("eqauls operators");
    Vector<> v1 = {10, 0, 0};
    std::cout << "v1: ";
    printVec(v1);

    Vector<> v2(3);
    v2 = v1;
    std::cout << "v2(=): ";
    printVec(v2);

    v2 += v1;
    std::cout << "v2(+= v1): ";
    printVec(v2);

    v2 -= v1;
    std::cout << "v2(-= v1): ";
    printVec(v2);

    v2 *= 2;
    std::cout << "v2(*= 2): ";
    printVec(v2);

    v2 /= 2;
    std::cout << "v2(/= 2): ";
    printVec(v2);

    v2 ^= v1;
    std::cout << "v2 = [v2 x v1]: ";
    printVec(v2);

    Vector<> v3 = {0, 1};
    std::cout << "v3: ";
    printVec(v3);

    try
    {
        v2 += v3;
    }
    catch(const SizeMissmatch &m)
    {
        std::cout << "v2 + v3 size missmatch: " << m.what() << std::endl;
    }

    try
    {
        v2 -= v3;
    }
    catch(const SizeMissmatch &m)
    {
        std::cout << "v2 - v3 size missmatch: " << m.what() << std::endl;
    }

    try
    {
        v2 /= 0;
    }
    catch(const DivisionZero &div)
    {
        std::cout <<"v2/0 division error: " << div.what() << std::endl;
    }

    try
    {
        v2 ^= v3;
    }
    catch(const NonThreeD &e)
    {
        std::cout << "v2 = [v2 x v3]: " << e.what() << std::endl;
    }

}

void idAccess()
{
    Vector<> v = {0, 10, 15};
    std::cout << "v: ";
    printVec(v);

    std::cout << "v[1]: " << v[1] << std::endl;
    std::cout << "v.at(1): " << v.at(2) << std::endl;

    const Vector<> vc(v);
    std::cout << "vc[1]: " << v[1] << std::endl;
    std::cout << "v.at(2): " << v.at(2) << std::endl;

    try
    {
        v[4] = vc[1];
    }
    catch(const OutOfRange &o)
    {
        std::cout << "v[4] = vc[1]: " << o.what() << std::endl;
    }

    try
    {
        v.at(3) = vc[1];
    }
    catch(const OutOfRange &o)
    {
        std::cout <<  "v.at(3) = vc[1]: " << o.what() << std::endl;
    }

}

template<typename T>
void printVec(const Vector<T> &v)
{
    for(auto i: v)
        std::cout << i << " ";
    std::cout << std::endl;
}

void drawTitle(std::string header, unsigned len)
{
    for(unsigned i = 0; i < len; i++)
        std::cout << "-";
    std::cout << std::endl;

    unsigned leftLen = len/2 - header.size()/2;
    for(unsigned i = 0; i < leftLen; i++)
        std::cout << "-";

    std::cout << header;

    unsigned rightLen = leftLen;
    for(unsigned i = 0; i < rightLen; i++)
        std::cout << "-";
    std::cout << std::endl;
}
