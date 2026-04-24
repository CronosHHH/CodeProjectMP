/*
 * Metodología de la Programación
 * Curso 2025/2026
 * VectorLocation.h — versión con soporte -DTESTING
 */

#ifndef VECTORLOCATION_H
#define VECTORLOCATION_H

#include "Location.h"

class VectorLocation {
public:
    /**
     * @brief Constant with the capacity of the array _locations.
     * Exposed as public so tests can use VectorLocation::DIM_VECTOR_LOCATIONS.
     */
    static const int DIM_VECTOR_LOCATIONS = 100;

    VectorLocation(int size = 0);
    int getSize() const;
    int getCapacity() const;
    std::string toString() const;
    int findLocation(const Location &location) const;
    VectorLocation select(const Location &bottomLeft,
                          const Location &topRight) const;
    void clear();
    const Location &at(int pos) const;
    Location &at(int pos);
    bool append(const Location &location);
    void join(const VectorLocation &locations);
    void sort();
    int nearest(const Location& location) const;
    void assign(const Location& location);
    void load(std::istream &is);

//____________________________________
#ifdef TESTING
public:
#else
//____________________________________

private:
//____________________________________
#endif
//____________________________________
    /**
     * Array of Location objects
     */
    Location _locations[DIM_VECTOR_LOCATIONS];

    /**
     * Number of Location objects contained in the array
     */
    int _size;
};

#endif /* VECTORLOCATION_H */
