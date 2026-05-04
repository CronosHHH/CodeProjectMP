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
_______________________________
ANTES ERA ASÍ:

   static const int DIM_VECTOR_LOCATIONS = 100;

   Location _locations[DIM_VECTOR_LOCATIONS];

   int _size;
_______________________________
AHORA ES ASÍ:

   Location* _locations;

   int _size;

   int _capacity;

   static const int BLOCK_SIZE=20;

*/

// es  un setter condicional

/**
 * @class VectorLocation
 * @brief A VectorLocation object contains a vector of Location objects. It has
 * a capacity (maximun number of Locations that can be stored in the vector)
 * and a size (number of Locations the vector currently contains).
 * The public methods of this class do not allow a VectorLocation to contain two
 * Location objects with identical names.
 */

/**
 * @brief It builds a VectorLocation object (vector of Location objects)
 * with a size and capacity equal to the provided value (@p size).
 * Each element in the vector is initialized with the default Location
 * constructor.
 * @throw std::out_of_range Throws a std::out_of_range exception if
 * @p size < 0
 * @param size The size for the vector of Location in this object. Input
 * parameter
 */

// CONSTRUCTOR POR PARAMETROS - POR DEFECTO - (con parametros)
// se crea el array dinámico
VectorLocation::VectorLocation(int size)
    : _locations(nullptr), _size(0), _capacity(0)
{
    // OJO: se permite size = 0 -> _capacity = 0.
    if (size < 0)
    {
        throw std::out_of_range("VectorLocation: size invalido");
    }

    _size = size;
    _capacity = size;

    // Each element in the vector is initialized with the default Location constructor.
    if (_capacity > 0)
    {
        _locations = new Location[_capacity];
    }
};

/**
 * @brief Copy constructor
 * @param orig the VectorLocation object used as source for the copy.
 * Input parameter
 */

// CONSTRUCTOR DE COPIA - POR DEFECTO (con parametros)
//
VectorLocation::VectorLocation(const VectorLocation &orig)
    : _locations(nullptr), _size(orig._size), _capacity(orig._capacity)
{
    if (_capacity > 0)
    {
        _locations = new Location[_capacity];
        // No copia el puntero, copia los elementos.
        for (int i = 0; i < _size; ++i)
        {
            _locations[i] = orig._locations[i];
        }
    }
};

/**
 * @brief Destructor
 */
VectorLocation::~VectorLocation()
{

    delete[] _locations;
};

/**
 * @brief Overloading of the assignment operator for VectorLocation class
 * Modifier method
 * @param orig the VectorLocation object used as source for the assignment.
 * Input parameter
 * @return A reference to this object
 */
VectorLocation &VectorLocation::operator=(const VectorLocation &orig)
{
    if (this != &orig)
    {
        Location *newLocations;
        newLocations = nullptr;

        if (orig._capacity > 0)
        {
            newLocations = new Location[orig._capacity];
            for (int i = 0; i < orig._size; ++i)
            {
                newLocations[i] = orig._locations[i];
            }
        }

        delete[] _locations;

        _locations = newLocations;
        _size = orig._size;
        _capacity = orig._capacity;
    }

    return *this;
}

/**
 * @brief Gets the number of elements in the vector of this object
 * Query method
 * @return The number of elements -> _size
 */
int VectorLocation::getSize() const
{
    return _size;
};

/**
 * @brief Gets the capacity of the vector in this object
 * Query method
 * @return The capacity of the vector in this object
 */

int VectorLocation::getCapacity() const
{
    return _capacity;
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
std::string VectorLocation::toString() const
{
    std::string result = std::to_string(_size) + "\n";
    for (int i = 0; i < _size; i++)
    {
        // he modificado esta linea de abajo porque sino no funcionaba
        // ya que std::to_string no acepta un Location
        // ,me suena que lo menciono en clase o en un correo.
        // result += std::to_string(_locations[i]) + "\n";

        // BIEN: Location ya tiene su propio metodo de toString()
        result += _locations[i].toString() + "\n";
    }
    return result;
}

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
int VectorLocation::findLocation(const Location &location) const
{
    for (int i = 0; i < _size; i++)
    {
        if (_locations[i].getName() == location.getName())
            return i;
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

VectorLocation VectorLocation::select(const Location &bottomLeft, const Location &topRight) const
{
    VectorLocation vector_result;
    for (int i = 0; i < _size; i++)
    {
        // Si la location esta dentro del area, la anadimos al resultado
        if (_locations[i].isInsideArea(bottomLeft, topRight))
        {
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

void VectorLocation::clear()
{
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
const Location &VectorLocation::at(int pos) const
{
    if (pos < 0 || pos >= _size)
    {
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

Location &VectorLocation::at(int pos)
{
    if (pos < 0 || pos >= _size)
    {
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

bool VectorLocation::append(const Location &location)
{
    // 0---- Si el nombre esta vacio, no anadimos
    if (location.getName().empty())
    {
        return false;
    }

    // 0---- Si ya existe una Location con ese nombre, no anadimos
    if (findLocation(location) != -1)
    {
        return false;
    }

    // 1. Si el array esta lleno, ampliamos la capacidad.
    if (_size >= _capacity)
    {
        int newCapacity = (_capacity > 0) ? (_capacity + BLOCK_SIZE) : BLOCK_SIZE;
        Location *newLocations = new Location[newCapacity];

        for (int i = 0; i < _size; ++i)
        {
            newLocations[i] = _locations[i];
        }

        delete[] _locations;
        _locations = newLocations;
        _capacity = newCapacity;
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

void VectorLocation::join(const VectorLocation &locations)
{
    for (int i = 0; i < locations.getSize(); i++)
    {
        append(locations.at(i));
    }
};

/**
 * Sorts the array of locations in this object by increasing alphabetical
 * order of the name of its location (a string).
 * Modifier method
 */

// el bubble sort q es mas eficiente

void VectorLocation::sort()
{
    for (int i = 0; i < _size - 1; i++)
    {
        for (int j = 0; j < _size - 1 - i; j++)
        {
            if (_locations[j].getName() > _locations[j + 1].getName())
            {
                Location temp = _locations[j];
                _locations[j] = _locations[j + 1];
                _locations[j + 1] = temp;
            }
        }
    }
};

/**
 * @brief Gets the position in this vector of the Location object nearest to
 * the provided location
 * Query method
 * @param location A Location object. Input parameter
 * @return the position of the Location object nearest to the provided
 * location.
 * If returns -1 if this vector is empty
 */

int VectorLocation::nearest(const Location &location) const
{

    // en verdad se podria usar el metodo distance en vez de squaredistance
    //, pero seria mas computo

    if (_size == 0)
        return -1;

    int posNearest = 0;
    double minDist = _locations[0].squaredDistance(location);

    for (int i = 1; i < _size; i++)
    {
        double dist = _locations[i].squaredDistance(location);
        if (dist < minDist)
        {
            minDist = dist;
            posNearest = i;
        }
    }
    return posNearest;
};

/**
 * Assigns the provided value to all the elements in this vector
 * Modifier method
 * @param location A Location object. Input parameter
 */

void VectorLocation::assign(const Location &location)
{

    for (int i = 0; i < _size; i++)
    {
        _locations[i] = location;
    }
};

/**
 * @brief Reads from the provided input stream the information
 * to fill this VectorLocation object.
 * @note This method should remove any Location previously contained in the
 * provided VectorLocation object. See files *.loc in the folder DataSets
 * as examples of this kind of file.
 * @note This operator throws an exception in some error cases (see below).
 * Before throwing the corresponding exception, this method clears
 * the object (it calls to clear() method) to leave the object in a
 * consistent state.
 * Modifier method
 * @throw std::out_of_range Throws a std::out_of_range exception if the
 * number of Location read from the input stream is negative.
 * @throw std::out_of_range Throws a std::out_of_range exception if the
 * number of locations read from the input stream is greater than the capacity
 * of this VectorLocation object.
 * @param is Input stream. Input/output parameter
 */

// le he afnadido & al istream, preguntar en clase
void VectorLocation::load(std::istream &is)
{

    VectorLocation::clear();

    int n;
    is >> n;

    if (n < 0)
    {
        VectorLocation::clear();
        throw std::out_of_range("VectorLocation::load: numero de locations negativo");
    }
    for (int i = 0; i < n; i++)
    {
        Location templocation;
        templocation.load(is);
        VectorLocation::append(templocation);
        // recordar q el append tenia excepciones capacidad superada,
        // nombre repetido o sin nombre;
        // y aparte es un metodo de tipo bunealno, pero su principal
        // funcion es añadir un elemento al final y aumentar 1 _size
    }
};
