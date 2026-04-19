#include <iostream> 
#include <string>    
#include <cmath>     
#include <stdexcept>

#include "ArrayLocation.h"

/**
 * @brief Displays on the standard output an integer (the value in nLocs,
 * number of locations in arrayLocations) and the content of the provided
 * array of locations. Each location is displayed on a new line with the help
 * of the Location::toString() method.
 * @param arrayLocations An array of Location objects. Input parameter
 * @param nLocs Number of Location objects in the array arrayLocations.
 * Input parameter
 */
void PrintArrayLocation(const Location arrayLocations[], int nLocs) {
    std::cout << nLocs << "\n";
    for (int i = 0; i < nLocs; i++) {
        std::cout << arrayLocations[i].toString() << "\n";
    }
}

/**
 * @brief Reads from the standard input an integer n and then reads
 * n Location objects that are placed into the provided array of locations.
 * @throw Throws a std::out_of_range exception if the integer n read from
 * standard input is negative. In that case, nLocs will be set to 0.
 * @throw Throws a std::out_of_range exception if the integer n read from
 * standard input exceeds the array capacity. In that case, nLocs will be set to 0.
 * @param arrayLocations An array of Location objects. Output parameter
 * @param capacity An integer with the capacity of arrayLocations.
 * Input parameter
 * @param nLocs An integer with the number of objects inserted in
 * arrayLocations. Output parameter
 */
void ReadArrayLocation(Location arrayLocations[], int capacity, int& nLocs) {
    int n;
    std::cin >> n;

    if (n < 0) {
        nLocs = 0;
        throw std::out_of_range("ReadArrayLocation: n es negativo");
    }
    if (n > capacity) {
        nLocs = 0;
        throw std::out_of_range("ReadArrayLocation: n supera la capacidad del array");
    }

    nLocs = n;
    for (int i = 0; i < nLocs; i++) {
        arrayLocations[i].load(std::cin);
    }
}

/**
 * @brief Places a copy of each Location of the provided VectorLocation object
 * into the provided array of Location (arrayLocations).
 * @throw Throws a std::out_of_range exception if the number of Location objects
 * in the provided VectorLocation exceeds the array capacity. In that case,
 * nLocs will be set to 0.
 * @param vector A VectorLocation object. Input parameter
 * @param arrayLocations Array of Location objects. Output parameter
 * @param capacity An integer with the capacity of arrayLocations.
 * Input parameter
 * @param nLocs An integer with the number of objects inserted in
 * arrayLocations. Output parameter
 */
void ToArrayLocation(const VectorLocation& vector, Location arrayLocations[], int capacity, int& nLocs) {
    if (vector.getSize() > capacity) {
        nLocs = 0;
        throw std::out_of_range("ToArrayLocation: el VectorLocation supera la capacidad del array");
    }

    nLocs = vector.getSize();
    for (int i = 0; i < nLocs; i++) {
        arrayLocations[i] = vector.at(i);
    }
}

/**
 * @brief Returns a VectorLocation object filled with a copy of the objects from
 * the provided array of Location objects (arrayLocation)
 * @throw Throws a std::out_of_range exception if nLocs is negative.
 * @param arrayLocations Array of Location objects. Input parameter
 * @param nLocs An integer with the number of objects in
 * arrayLocations. Input parameter
 * @return A VectorLocation object filled with the objects from the provided
 * array of Location objects (arrayLocation)
 */
VectorLocation ToVectorLocation(const Location arrayLocations[], int nLocs) {
    if (nLocs < 0) {
        throw std::out_of_range("ToVectorLocation: nLocs es negativo");
    }

    VectorLocation result;
    for (int i = 0; i < nLocs; i++) {
        result.append(arrayLocations[i]);
    }
    return result;
}