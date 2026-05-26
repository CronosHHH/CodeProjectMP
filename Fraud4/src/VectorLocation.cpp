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

/**
 * @brief Libera la memoria dinamica reservada y resetea los atributos.
 */
void VectorLocation::liberar()
{
    if (_locations != nullptr)
    {
        delete[] _locations;
        _locations = nullptr;
    }
    _size = 0;
    _capacity = 0;
}

/**
 * @brief Reserva memoria para un numero especifico de elementos.
 * @param n Capacidad a reservar.
 */
void VectorLocation::reservar(int n)
{
    if (n > 0)
    {
        _locations = new Location[n];
        _capacity = n;
    }
    else
    {
        _locations = nullptr;
        _capacity = 0;
    }
}

/**
 * @brief Copia los datos de otro objeto VectorLocation.
 * Asume que ya existe memoria reservada suficiente en *this.
 * @param orig Objeto origen de la copia.
 */
void VectorLocation::copiar(const VectorLocation &orig)
{
    _size = orig._size;
    for (int i = 0; i < _size; ++i)
    {
        _locations[i] = orig._locations[i];
    }
}

void VectorLocation::reallocar(int newCapacity)
{
    Location *oldLocations = _locations;
    int oldSize = _size;

    reservar(newCapacity);
    for (int i = 0; i < oldSize; ++i)
    {
        _locations[i] = oldLocations[i];
    }

    delete[] oldLocations;
}

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
// CONSTRUCTOR POR PARAMETROS o DE RELLENO
VectorLocation::VectorLocation(int size) : _locations(nullptr), _size(0), _capacity(0)
{
    // OJO: se permite size = 0 -> _capacity = 0.
    if (size < 0){
        throw std::out_of_range("VectorLocation: size invalido");
    }

    reservar(size);
    _size = size;
};

/**
 * @brief Copy constructor
 * @param orig the VectorLocation object used as source for the copy.
 * Input parameter
 */
// CONSTRUCTOR POR COPIA
VectorLocation::VectorLocation(const VectorLocation &orig) : _locations(nullptr), _size(0), _capacity(0)
{
    reservar(orig._capacity);
    copiar(orig);
};

/**
 * @brief Destructor
 */
VectorLocation::~VectorLocation()
{
    liberar();
};

/**
 * @brief Overloading of the assignment operator for VectorLocation class
 * Modifier method --> cambia el valor de *this
 * @param orig the VectorLocation object used as source for the assignment.
 * Input parameter
 * @return A reference to this object
 */
VectorLocation &VectorLocation::operator=(const VectorLocation &orig)
{
    if (this != &orig)
    {
        liberar();
        reservar(orig._capacity);
        copiar(orig);
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
    int position = -1;
    for (int i = 0; i < _size; i++)
    {
        if (_locations[i].getName() == location.getName())
        {
            position = i;
        }
    }
    return position;
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
 * appended to this object if it was not already found in this object or
 * its name is an empty string.
 * If the dynamic array of Location was full (its capacity was full), this
 * method automatically reallocates a new array with a capacity equal to
 * the current capacity plus an extra block of size equal to BLOCK_SIZE.
 * Modifier method
 * @param value the new Location object to be appended. Input parameter
 * @return true if the given Location could be inserted in this
 * VectorLocation object; false otherwise (the location was already found
 * in this object)
 */
bool VectorLocation::append(const Location &location)
{
    // 0---- Si ya existe una Location con ese nombre, no anadimos
    if (findLocation(location) != -1)
    {
        return false;
    }

    // 1. Si el array esta lleno, ampliamos la capacidad.
    if (_size >= _capacity)
    {
        int newCapacity = (_capacity > 0) ? (_capacity + BLOCK_SIZE) : BLOCK_SIZE;
        reallocar(newCapacity);
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
 * to fill this VectorLocation object. See files *.loc in the folder
 * DataSets as examples of this kind of file.
 * @note This method should remove any Location previously contained in the
 * provided VectorLocation object.
 * @note This operator throws an exception in some error cases (see below).
 * Before throwing the corresponding exception, this method clears
 * the object (it calls to clear() method) to leave the object in a
 * consistent state.
 * Modifier method
 * @throw std::out_of_range Throws a std::out_of_range exception if the
 * number of Location read from the input stream is negative.
 * @param is Input stream. Input/output parameter
 */
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

/**
 * @brief Overloading of the [] operator for VectorLocation class
 * Query method
 * @param index index of the element. Input parameter
 * @return A constant reference to the element at position @p index
 */
const Location &VectorLocation::operator[](int index) const
{
    return at(index);
}

/**
 * @brief Overloading of the [] operator for VectorLocation class
 * Modifier method
 * @param index index of the element. Input parameter
 * @return A reference to the element at position @p index
 */
Location &VectorLocation::operator[](int index)
{
    return at(index);
}

/**
 * @brief Overloads the operator += for the VectorLocation class.
 * It appends to this VectorLocation object a copy of the given Location.
 * The new element is put at the end of the vector.
 * The location is not appended to this object, if it was already found in
 * this object.
 * Take into account, that this method increases the capacity
 * of the internal dynamic array of Location objects if that array is full.
 * Modifier method
 * @param location The Location object to append to this object. Input
 * parameter
 * @return A reference to this object.
 */
VectorLocation &VectorLocation::operator+=(const Location &location)
{
    append(location);
    return *this;
}

/**
 * @brief Overloading of the stream insertion operator for VectorLocation class.
 * It sends to the output stream a line for each Location of the given
 * VectorLocation object. Each line will contain the x and y coordinates of
 * a Location, separated by a whitespace.
 * @param os The output stream to be used. Input/output parameter
 * @param vector The VectorLocation object. Input parameter
 * @return @p os A reference to the output stream
 */
std::ostream &operator<<(std::ostream &os, const VectorLocation &vector)
{
    os << vector.toString();
    return os;
}

/**
 * @brief Overloading of the stream extraction operator for VectorLocation class.
 * This operator first reads from the input stream a line containing an integer n,
 * which corresponds to the number of Location objects to be read from the input stream.
 * Then, it reads n Location objects from the input stream, storing them in the provided
 * VectorLocation object (@p vector).
 * @note This operator should remove any Location previously contained in the
 * provided VectorLocation @p vector.
 * @note This operator throws an exception in some error cases (see below).
 * Before throwing the corresponding exception, this operator clears
 * the provided object (it calls to clear() method) to leave it in a
 * consistent state.
 * @throw std::out_of_range Throws a std::out_of_range exception if the number
 * of locations read from the file is negative.
 * @param is The input stream to be used. Input/output parameter
 * @param vector The VectorLocation object to be filled. Input/output parameter
 * @return @p is A reference to the input stream
 */
std::istream &operator>>(std::istream &is, VectorLocation &vector)
{
    vector.clear();

    int n = 0;
    if (!(is >> n))
    {
        return is;
    }
    if (n < 0)
    {
        vector.clear();
        throw std::out_of_range("VectorLocation::operator>> numero de locations negativo");
    }

    for (int i = 0; i < n; ++i)
    {
        Location location;
        location.load(is);
        vector.append(location);
    }

    return is;
}
