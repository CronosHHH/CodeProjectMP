#include <iostream>  
#include <string>
#include <stdexcept>
#include <cmath>


#include "VectorInt.h"

/**
 * @class VectorInt
 * @brief A VectorInt object contains a vector of integer elements. It has
 * a capacity (maximun number of elements that can be stored in the vector)
 * and a size (number of elements the vector currently contains).
 */

/**
*_____________________________________________
*
* Constant with the capacity of the array _values
*
* static const int DIM_VECTOR_VALUES = 100; 
*______________________________________________
*
* Array of integers with the integer elements in this object
*
* int _values[DIM_VECTOR_VALUES];
*______________________________________________
*
* 
* Number of elements contained in the array _values
*
* int _size;
*______________________________________________
**/

void VectorInt::liberar()
{
    if (_values != nullptr)
    {
        delete[] _values;
        _values = nullptr;
    }
    _size = 0;
    _capacity = 0;
}

void VectorInt::reservar(int capacity)
{
    if (capacity > 0)
    {
        _values = new int[capacity];
        _capacity = capacity;
    }
    else
    {
        _values = nullptr;
        _capacity = 0;
    }
}

void VectorInt::copiar(const VectorInt &orig)
{
    _size = orig._size;
    for (int i = 0; i < _size; ++i)
    {
        _values[i] = orig._values[i];
    }
}

void VectorInt::reallocar(int newCapacity)
{
    int *oldValues = _values;
    int oldSize = _size;

    reservar(newCapacity);
    for (int i = 0; i < oldSize; ++i)
    {
        _values[i] = oldValues[i];
    }

    delete[] oldValues;
}


/**
 * @brief It builds a VectorInt object (vector of integers) with a 
 * size and capacity equal to the provided value (@p size). Each element
 * will be filled with a value equal to 0.
 * @throw std::out_of_range Throws a std::out_of_range exception if
 * @p size < 0
 * @param size The size for the vector of integers in this object. Input
 * parameter
 */
VectorInt::VectorInt(int size) : _values(nullptr), _size(0), _capacity(0)
{
    if (size < 0)
    {
        throw std::out_of_range("VectorInt: size invalido");
    }

    reservar(size);
    _size = size;
    assign(0);
};

/**
 * @brief Copy constructor
 * @param orig the VectorInt object used as source for the copy. Input
 * parameter
 */
VectorInt::VectorInt(const VectorInt &orig) : _values(nullptr), _size(0), _capacity(0)
{
    reservar(orig._capacity);
    copiar(orig);
};

/**
 * @brief Destructor
 */
VectorInt::~VectorInt()
{
    liberar();
};

/**
 * @brief Overloading of the assignment operator for VectorInt class
 * Modifier method
 * @param orig the VectorInt object used as source for the assignment. Input
 * parameter
 * @return A reference to this object
 */
VectorInt &VectorInt::operator=(const VectorInt &orig)
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
 * @return The number of elements
 */
int VectorInt::getSize() const
{
    return _size;
};



/**
 * @brief Gets the capacity of the vector in this object
 * Query method
 * @return The capacity of the vector in this object
 */
int VectorInt::getCapacity() const
{
    return _capacity;
};

/**
 * @brief Compares the integer vectors of this object and the provided 
 * object, and returns the number of identical elements in both of them. The 
 * comparison is performed in order, element by element, in both vectors.
 * For example, given the following two vectors:
 * 2 1 2 3 5
 * 1 1 2 4 5
 * this method will return 3 (there is a match ​in positions 1, 2 and 4)
 * @throw std::invalid_argument Throws an std::invalid_argument exception 
 * if the sizes of this and the provided object are different
 * Query method
 * @param other A VectorInt object. Input parameter
 * @return The number of identical elements in the vectors of this
 * and the provided object.
 */

// otro que como es query method le pongo el const
int VectorInt::countIdenticalElements(const VectorInt &other) const
{
    int cont= 0;

    if (_size != other.getSize()) {
        throw std::invalid_argument("countIdenticalElements: tamanios diferentes");
    }

    for(int i=0; i<_size ; i++){
        if(_values[i] == other.at(i)) cont++;
    }
    return cont;
};

/**
 * @brief Obtains a string with information about this VectorInt object, 
 * in the following format:
 * - First line, the number of elements in this vector. 
 * - Second line, the elements in this vector, separated by a whitespace. 
 * Take into account that a '\n' should appear after the last element 
 * instead of a whitespace.
 * Query method
 * @return string with information about this VectorInt object
 */
// es una query, aniadir const 
std::string VectorInt::toString() const
{
    std::string result = std::to_string(_size) + "\n";
    for (int i = 0; i < _size; i++) {
        std::string espacio = ( i == _size -1) ? "\n" : " ";
        result += std::to_string(_values[i]) + espacio;
    }
    return result;
};

/**
 * @brief Gets the Euclidean distance between this and the provided object.
 * The Euclidean distance between two points \f$ P=(p_1, p_2, ... , p_n) \f$ 
 * and \f$ Q=(q_1, q_2, ... , q_n) \f$ in an n-dimensional space \f$ R^n \f$ 
 * is the length of the line segment connecting them, calculated as the 
 * square root of the sum of the squared differences of their components: 
 * \f$ d(P,Q)=\sqrt{ \sum_{i=1}^{n} (p_i-q_i)^{2} } \f$
 * @throw std::invalid_argument Throws an std::invalid_argument exception 
 * if the size of this object and the provided one are not equal
 * @throw std::invalid_argument Throws an std::invalid_argument exception 
 * if the size of the provided object is zero
 * Query method
 * @param other A VectorInt. Input parameter
 * @return The Euclidean distance between this and the provided objects
 */
double VectorInt::distance(const VectorInt &other) const
{
    if (_size != other.getSize()) {
        throw std::invalid_argument("distance: tamanios diferentes");
    }
    if (_size == 0) {
        throw std::invalid_argument("distance: tamanio es cero");
    }
    double sum = 0;
    for (int i = 0; i < _size; i++) {
        sum += std::pow(_values[i] - other.at(i), 2);
    }
    return std::sqrt(sum);
};

/**
 * @brief Assigns the provided value to all the elements in this vector
 * Modifier method
 * @param value An integer value. Input parameter
 */
void VectorInt::assign(int value)
{
    for (int i = 0; i < _size; i++) {
        _values[i] = value;
    }
};

/**
 * @brief Appends the given integer value at the end (first free position) 
 * of the array of integers in this object. 
 * Modifier method
 * @param value the new integer value to be appended. Input parameter
 */
void VectorInt::append(int value)
{
    if (_size >= _capacity)
    {
        int newCapacity = (_capacity > 0) ? (_capacity + BLOCK_SIZE) : BLOCK_SIZE;
        reallocar(newCapacity);
    }

    _values[_size] = value;
    _size++;
};

/**
 * @brief Removes all the elements in this object, leaving the container 
 * with a size equal to 0. It only need to set the number of elements 
 * (_size field) to zero.
 * Modifier method
 */
void VectorInt::clear()
{
    _size = 0;
};

/**
 * @brief Gets a const reference to the integer element at the given 
 * position
 * Query method
 * @param pos position in the VectorInt object. Input parameter
 * @throw std::out_of_range Throws an std::out_of_range exception if the 
 * given position is not valid.
 * @return A const reference to the integer element at the given position
 */
const int &VectorInt::at(int pos) const
{
    if (pos < 0 || pos >= _size)
    {
        throw std::out_of_range("VectorInt::at posicion invalida");
    }
    return _values[pos]; 
};

/**
 * @brief Gets a reference to the integer element at the given position. 
 * Modifier method
 * @param pos position in the VectorInt object. Input parameter
 * @throw std::out_of_range Throws an std::out_of_range exception if the 
 * given position is not valid
 * @return A reference to the integer element at the given position.
 */
int &VectorInt::at(int pos)
{
    if (pos < 0 || pos >= _size)
    {
        throw std::out_of_range("VectorInt::at posicion invalida");
    }
    return _values[pos]; 
};

/**
 * @brief Overloading of the [] operator for VectorInt class
 * Query method
 * @param index index of the element. Input parameter
 * @return A constant reference to the element at position @p index
 */
const int &VectorInt::operator[](int index) const
{
    return at(index);
}

/**
 * @brief Overloading of the [] operator for VectorInt class
 * Modifier method
 * @param index index of the element. Input parameter
 * @return A reference to the element at position @p index
 */
int &VectorInt::operator[](int index)
{
    return at(index);
}

/**
 * @brief Overloads the operator += for the VectorInt class.
 * It appends to this VectorInt object the given integer value. The
 * new element is put at the end.
 * Take into account, that this method increases the capacity
 * of the internal dynamic array of integers if that array is full.
 * Modifier method
 * @param value The integer value to append to this object. Input parameter
 * @return A reference to this object.
 */
VectorInt &VectorInt::operator+=(int value)
{
    append(value);
    return *this;
}

/**
 * @brief Overloading of the stream insertion operator for VectorInt class.
 * It sends to the output the information about the provided VectorInt
 * object in the following format:
 * - First line, the number of elements in this vector.
 * - Second line, the elements in the provided vector, separated by a whitespace.
 * Take into account that a '\n' should appear after the last element
 * instead of a whitespace.
 * @param os The output stream to be used. Input/output parameter
 * @param vector The VectorInt object. Input parameter
 * @return os A reference to the output stream
 */
std::ostream &operator<<(std::ostream &os, const VectorInt &vector)
{
    os << vector.toString();
    return os;
}

/**
 * @brief Overloading of the stream extraction operator for VectorInt class.
 * @note This operator should remove any previously information contained in the
 * provided VectorInt @p vector.
 * @note This operator throws an exception in some error cases (see below).
 * Before throwing the corresponding exception, this operator clears
 * the provided object (it calls to clear() method) to leave it in a
 * consistent state.
 * @throw std::out_of_range Throws a std::out_of_range exception if the number
 * of elements read from the file is negative.
 * @param is The input stream to be used. Input/output parameter
 * @param vector The VectorInt object to be filled. Input/output parameter
 * @return A reference to the input stream
 */
std::istream &operator>>(std::istream &is, VectorInt &vector)
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
        throw std::out_of_range("VectorInt::operator>> numero de elementos negativo");
    }

    VectorInt temp(n);
    for (int i = 0; i < n; ++i)
    {
        int value = 0;
        if (!(is >> value))
        {
            vector.clear();
            throw std::ios_base::failure("VectorInt::operator>> error de lectura");
        }
        temp.at(i) = value;
    }

    vector = temp;
    return is;
}
