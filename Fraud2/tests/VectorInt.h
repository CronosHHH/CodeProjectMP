/*
 * Metodología de la Programación
 * Curso 2025/2026
 * VectorInt.h — versión con soporte -DTESTING
 */

#ifndef VECTORINT_H
#define VECTORINT_H

#include <iostream>
#include <string>

class VectorInt {
public:
    /**
     * Constant with the capacity of the array _values.
     * Exposed as public so tests can use VectorInt::DIM_VECTOR_VALUES.
     */
    static const int DIM_VECTOR_VALUES = 100;

    VectorInt(int size = 0);
    int getSize() const;
    int getCapacity() const;
    int countIdenticalElements(const VectorInt &other) const;
    std::string toString() const;
    double distance(const VectorInt &other) const;
    void assign(int value = 0);
    void append(int value);
    void clear();
    const int &at(int pos) const;
    int &at(int pos);

#ifdef TESTING
public:
#else
private:
#endif
    /**
     * Array of integers
     */
    int _values[DIM_VECTOR_VALUES];

    /**
     * Number of elements contained in the array
     */
    int _size;
};

#endif // VECTORINT_H
