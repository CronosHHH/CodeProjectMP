#include <iostream>  
#include <string>
#include <cmath>   
#include <stdexcept>  

#include "Location.h"
#include "VectorLocation.h"

/**
 * @class VectorLocation
 * @brief A VectorLocation object contains a vector of Location objects. It has
 * a capacity (maximun number of Locations that can be stored in the vector)
 * and a size (number of Locations the vector currently contains).
 * The public methods of this class do not allow a VectorLocation to contain two
 * Location objects with identical names.
 * This class uses an array of Location objects with a fixed capacity
 * to store the set of locations.
 */

 /**

    static const int DIM_VECTOR_LOCATIONS = 100;

    Location _locations[DIM_VECTOR_LOCATIONS];

    int _size;

* @brief It builds a VectorLocation object (vector of Location objects)
* with a size equal to the provided value (@p size).
* Each element in the vector is initialized with the default Location
* constructor.
* @throw std::out_of_range Throws a std::out_of_range exception if
* @p size < 0 or size>DIM_VECTOR_LOCATIONS
* @param size The size for the vector of Location in this object. Input
* parameter
*/

//es  un setter condicional
VectorLocation::VectorLocation(int size){
    if (size < 0 || size > DIM_VECTOR_LOCATIONS) {
        throw std::out_of_range("VectorLocation: size invalido, que sea entre 1 y 100");
    }
    _size = size;
};

/**
 * @brief Gets the number of elements in the vector of this object
 * Query method
 * @return The number of elements -> _size
 */
int VectorLocation::getSize() const{
    return _size;
};

/**
 * @brief Gets the capacity of the vector in this object
 * Query method
 * @return The capacity of the vector in this object
 */

int VectorLocation::getCapacity() const{
    return DIM_VECTOR_LOCATIONS;
};

/**
 * @brief Obtains a string with information about this VectorLocation object, 
 * in the following format:
 * - First line, the number of Location objects in this vector, converted to
 * a string (using the to_string(int) C++ function). 
 * 
 * - For each Location, a line with its information, converted to
 * a string with the Location::toString() method.
 * 
 * For example, the following is the content of the string for a 
 * VectorLocation object with 4 locations:
4
24.8 14.9 Quadrangle
25.6 14.9 Ivy
26.4 14.9 Cottage
27.3 14.5 Cap & Gown
    * Query method
    * @return string with information about this VectorLocation object
    */
std::string VectorLocation::toString() const{
    std::string output;
    output = std::to_string(_size) + "\n";
    for (int i=0; i<_size; i++){
        output += _locations[i].toString() + "\n";
    }

    return output;
};

/**
 * @brief Searches the provided Location in the array of locations in this
 * object. If found, it returns the position where it was found. If not,
 * it returns -1. 
 * 
 * We consider that position 0 is the first location in the
 * list of locations and this->getSize()-1 the last location.
 * 
 * In order to find a location consider only equality in the name field.
 * 
 * Query method
 * @param location A Location. Input parameter
 * @return If found, it returns the position where the location
 * was found. Otherwise it returns -1
 */
int VectorLocation::findLocation(const Location &location) const{
    for (int i=0; i<_size; i++){
        if(_locations[i].getName() == location.getName() ) return i;
    }
    return -1;
};

/**
 * @brief Returns a VectorLocation object with those locations whose
 * positions are inside the area determined by the two given Locations.
 * Query method

//conviene usar isInsideArea && append

 * @param bottomLeft The Location of the bottom left point. Input parameter
 * @param topRight The Location of the top right point. Input parameter
 * @return A VectorLocation with the selected Locations.
 */

//recordar que en una funcion que devuelve un VALOR tipo T (en este caso, un vector), 
//podemos crear un varlor tipo T RESULT, modificarlo, para despues ponerlo en return.
// en este tipo de funciones por cojones hay que devolver una variable del mismo
// tipo que la funcion, lo que sirve para entender un poco el enunciado.

// si es un método de de una clase, por cojones va a tener que tener contenida
// la clase en algun momento, ya sea para obtener un dato, cambiarlo o estudiarlo...


VectorLocation VectorLocation::select(const Location &bottomLeft, const Location &topRight) const{
    VectorLocation vector_result;
        for (int i = 0; i < _size; i++) {
        // Si la location esta dentro del area, la anadimos al resultado
        if (_locations[i].isInsideArea(bottomLeft, topRight)) {
            vector_result.append(_locations[i]);
        }
    }
    return vector_result;
};

/**
 * @brief 
 * Removes all the elements in this object, leaving the container
 * with a size equal to 0. It only needs to set the number of elements
 * (_size field) to zero.
 * Modifier method
 */

void VectorLocation::clear(){
    _size = 0;
};

/**
 * @brief Gets a const reference to the Location element at the given
 * position
 * Query method
 * @throw std::out_of_range Throws an std::out_of_range exception if the
 * given position is not valid.
 * @param pos position in the VectorLocation object. Input parameter
 * @return A const reference to the Location element at the given position
 */

 // es como un getLocation que vamos a usar para cuando la entrada sea una posición 
const Location &VectorLocation::at(int pos) const{
    if (pos < 0 || pos >= _size) {
        throw std::out_of_range("VectorLocation::at posicion invalida");
    }
    return _locations[pos]; 
    // recordar que _locations[] es un vecotr de location
    // aunque lo que devuelve no es una referencia constante de
    // un elemento de Localicon
};

/**
 * @brief Gets a reference to the Location element at the given position.
 * Modifier method
 * @throw std::out_of_range Throws an std::out_of_range exception if the
 * given position is not valid
 * @param pos position in the VectorLocation object. Input parameter
 * @return A reference to the Location element at the given position.
 */
Location &VectorLocation::at(int pos){
    if (pos < 0 || pos >= _size) {
        throw std::out_of_range("VectorLocation::at posicion invalida");
    }
    return _locations[pos]; 
};

/**
 * @brief Appends a copy of the given Location object at the first free
 * position in the array of Location in this object. The location is only
 * appended to this object if:
 * 0----it was not already found in this object 
 * 0----its name is an empty string.
 * 
 * @throw 
 * 
 * 1---std::out_of_range Throws a std::out_of_range exception if the
 * provided location is going to be appended but the array of Location 
 * was full (its capacity was full).
 * 
 * 2---If the provided location is not going 
 * to be appended because it was already found in this object or its name 
 * is an empty string, then no exception is thrown.
 * 
 * Modifier method
 * @param value the new Location object to be appended. Input parameter
 * @return true if the given Location could be inserted in this
 * VectorLocation object; false otherwise (the location was already found
 * in this object)
 */
bool VectorLocation::append(const Location &location){
    // 0---- Si el nombre esta vacio, no anadimos
    if (location.getName().empty()) {
        return false;
    }

    // 0---- Si ya existe una Location con ese nombre, no anadimos
    if (findLocation(location) != -1) {
        return false;
    }

    // 1. Si el array esta lleno, lanzamos excepcion
    if (_size >= DIM_VECTOR_LOCATIONS) {
        throw std::out_of_range("VectorLocation::append its capacity was full");
    }

    // 2. Todo ok: anadimos la location en la siguiente posicion libre
    _locations[_size] = location;
    _size++;

    return true;
};

/**
 * @brief Appends to this VectorLocation object, the list of
 * Location objects contained in the provided VectorLocation object
 * that are not found (using VectorLocation::findLocation(Location)) in
 * this object.
 * This method could be implemented with the help of the method
 * VectorLocation::append(const Location & location), to append to this
 * object, the Locations of the provided VectorLocation object.
 * Modifier method
 * @param crimeSet A VectorLocation object. Input parameter
 */
void VectorLocation::join(const VectorLocation &locations){
    for (int i = 0; i < locations.getSize(); i++) {
        append(locations.at(i));
    }
};

/**
 * Sorts the array of locations in this object by increasing alphabetical
 * order of the name of its location (a string).
 * Modifier method
 */
void VectorLocation::sort(){
    for (int i = 0; i < _size - 1; i++) {
        // Suponemos que el minimo esta en la posicion i
        int posMin = i;

        // Buscamos si hay alguno menor desde i+1 hasta el final
        for (int j = i + 1; j < _size; j++) {
            if (_locations[j].getName() < _locations[posMin].getName()) {
                posMin = j;  // Nuevo minimo encontrado
            }
        }

        // Si el minimo no estaba en i, intercambiamos
        if (posMin != i) {
            Location temp = _locations[i];
            _locations[i] = _locations[posMin];
            _locations[posMin] = temp;
        }
    }
};