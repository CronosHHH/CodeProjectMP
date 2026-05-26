#include "Location.h"
#include <iostream>
#include <cmath>
#include <string>
#include <stdexcept>



//_____________________________________________________


/**
 * @brief Constructor that builds a Location object with a value of 0 
 * for the x and y coordinates, and an empty string for the name.
 */
Location::Location(){
    _x = _y = 0;
    _name = "";
};

/**
 * @brief Returns the x-coordinate of this location
 * Query method
 * @return The x-coordinate of this location
 */
double Location::getX() const{
    return _x;
};

/**
 * @brief Returns the y-coordinate of this location
 * Query method
 * @return The y-coordinate of this location
 */    
double Location::getY() const{
    return _y;
};

/**
 * @brief Returns the name of this location
 * Query method
 * @return The name of this location
 */     
std::string Location::getName() const{
    return _name;
};

/**
 * @brief Checks if the position of this object is inside the area
 * determined by the two given locations: Location A (@p bottomLeft) and 
 * B (@p topRight). 
 *  ~~~~
 *     +-----------+(B)
 *     |           |
 *     |           |  +(O3)
 *     |           | 
 *     |    +(O2)  |
 *     |           |
 *     |           |
 *  (A)+-----------+
 *        +(O1)
 * ~~~~
 * Examples of returning false:
 * - Object O3 is outside the given area (O3.x > B.x)
 * - Object O1 is outside the given area (O1.y < A.y) 
 * Example of returning true:
 * - Object O2 is inside the given area
 * - Object A is inside the given area
 * - Object B is inside the given area
 * 
 * Query method.
 * @param bottomLeft The Location of the bottom left point. Input parameter
 * @param topRight The Location of the top right point. Input parameter
 * @return true if the Location of this object is inside the area
 * determined by the two given Locations
 */
bool Location::isInsideArea(const Location &bottomLeft, const Location &topRight) const{
    return  bottomLeft.getX()<=_x && 
            topRight.getX()>=_x &&
            bottomLeft.getY()<=_y && 
            topRight.getY()>=_y;
};

/**
 * @brief Calculates the square of the Euclidean distante from this location 
 * to the provided location. That is, it loc1 and loc2 are two 
 * Location objects, then this method returns: 
 * \f$ (loc1.x - loc2.x)^2 + (loc1.y - loc2.y)^2 \f$
 * Query method
 * @param location A Location object. Input parameter
 * @return Returns the square of the Euclidean distante from this 
 * location to the provided location.
 */    
double Location::squaredDistance(const Location& location) const{
    return std::pow(_x - location.getX(), 2) + std::pow(_y - location.getY(),2 );
};

/**
 * @brief Calculates the Euclidean distante from this location to the provided 
 * location. That is, it loc1 and loc2 are two Location objects, then 
 * this method returns: 
 * \f$ \sqrt{ (loc1.x - loc2.x)^2 + (loc1.y - loc2.y)^2 } \f$
 * Note that this method can be implemented using the squaredDistance() 
 * method.
 * Query method
 * @param location A Location object. Input parameter
 * @return The Euclidean distante from this location to the provided 
 * location.
 */  

double Location::distance(const Location& location) const{
    return std::sqrt(squaredDistance(location));
}


/**
 * @brief Obtains a string with the x and y coordinates 
 * and the name (whitespace separated). If the name is an empty string,
 * then only the x and y coordinates are included in the resulting string.
 * To convert the x and y coordinates to a string you must use the
 * std::to_string(int) C++ function.
 * Query method
 * @return string with information about this Location object
 */

std::string Location::toString() const{
    std::string output;
    output = std::to_string(_x) + " " + std::to_string(_y);
        if(!_name.empty()) 
    output += " " + getName();
    return output;
}

/**
 * @brief Sets the x-coordinate in this object
 * Modifier method
 * @param x The new value for the x-coordinate. Input parameter
 */
void Location::setX(double x){
    this->_x = x;
};

/**
 * @brief Sets the y-coordinate in this object
 * Modifier method
 * @param y The new value for the y-coordinate. Input parameter
 */
void Location::setY(double y){
    this->_y = y;
};

/**
 * @brief Sets the name in this object
 * Modifier method
 * @param name A string with the new value for the name. Input parameter
 */
void Location::setName(const std::string& name){
    this->_name = name;
};

/**
 * @brief Sets the x and y coordinates, and the the name in this object
 * Modifier method
 * @param x The new value for the x-coordinate. Input parameter
 * @param y The new value for the y-coordinate. Input parameter
 * @param name A string with the new value for the name. Input parameter
 */
void Location::set(double x, double y, const std::string& name){
    setX(x);
    setY(y);
    setName(name);
};

/**
 * @brief Reads from the provided input stream the information
 * to fill this Location object.
 * @note This method reads two double values (space separated) from the 
 * input stream that are used to set the x and y coordinates of this object.
 * Then, it reads the string that can be formed from the current position of 
 * the input stream to the end of the line. This string is then trimmed 
 * (see the Trim(string) function) to remove its spaces at the beginning 
 * and at the end. The resulting string is used to set the name of this 
 * Location object. Note that the name can have several words separated by 
 * whitespaces. 
 * @param is Input stream. Input/output parameter
 */
void Location::load(std::istream &is) {
    // Paso 1: Leemos las dos coordenadas del flujo de entrada
    is >> _x;
    is >> _y;

    // Paso 2: Leemos el resto de la linea (el nombre, que puede tener espacios)
    // getline lee desde la posicion actual hasta el fin de linea
    std::getline(is, _name);

    // Paso 3: Quitamos espacios/tabs sobrantes al inicio y al final del nombre
    Trim(_name);
}

/**
 * @brief Adds to the values of the x and y coordinates of this object,
 * the x and y coordinates of the provided location
 * Modifier method
 * @param location A Location object. Input parameter
 * @return A reference to this object.
 */
Location &Location::operator+=(const Location &location)
{
    _x += location._x;
    _y += location._y;
    return *this;
}

/**
 * @brief Divides the value of the x and y coordinates of this object by the
 * provided double value.
 * Modifier method
 * @throw std::invalid_argument Throws an std::invalid_argument exception
 * if value==0
 * @param value A double value. Input parameter
 * @return A reference to this object.
 */
Location &Location::operator/=(double value)
{
    if (value == 0.0)
    {
        throw std::invalid_argument("Location::operator/= division por cero");
    }

    _x /= value;
    _y /= value;
    return *this;
}

/**
 * @brief Overloading of the stream insertion operator for Location class.
 * Sends to the output stream the x and y coordinates (converted to string)
 * and name, separated by a whitespace.
 * The x and y coordinates should be converted to string using the
 * std::to_string() C++ function.
 * @param os The output stream to be used. Input/output parameter
 * @param obj The Location object. Input parameter
 * @return A reference to the output stream
 */
std::ostream &operator<<(std::ostream &os, const Location &location)
{
    os << location.toString();
    return os;
}

/**
 * @brief Overloading of the stream extraction operator for Location class.
 * It reads two double values (space separated) from the input stream that
 * are used to set the x and y coordinates of the given Location object. Then,
 * it reads the string that can be formed from the current position of the
 * input stream to the end of the line. This string is then trimmed (see
 * the Trim(string) function) to remove its spaces at the beginning
 * and at the end. The resulting string is used to set the name of the provided
 * location. Note that the name can have several words separated by whitespaces.
 * @param is The input stream to be used. Input/output parameter
 * @param obj The Location object. Output parameter
 * @return A reference to the input stream
 */
std::istream &operator>>(std::istream &is, Location &location)
{
    location.load(is);
    return is;
}

void Trim(std::string &myString) {
    size_t first = myString.find_first_not_of(" \t");

    if (first == std::string::npos) {
        myString="";
    }
    else {
        size_t last = myString.find_last_not_of(" \t");
        myString = myString.substr(first, last - first + 1);
    }
}