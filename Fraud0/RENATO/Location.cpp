/*
 * Metodología de la Programación
 * Curso 2025/2026
 */

/**
 * @file Location.cpp
 * @author Silvia Acid Carrillo <acid@decsai.ugr.es>
 * @author Andrés Cano Utrera <acu@decsai.ugr.es>
 * @author Luis Castillo Vidal <L.Castillo@decsai.ugr.es>
 * 
 * Created on 6 de octubre de 2025, 12:27
 */

// Incluimos las librerias necesarias
#include <iostream>  // Para usar istream (en load)
#include <string>    // Para usar string y to_string
#include <cmath>     // Para usar sqrt (en distance)
#include "Location.h"

using namespace std;
// Usamos "using namespace std;" igual que en Point2D.cpp
// Asi podemos escribir "string" en vez de "std::string", "cout" en vez de "std::cout", etc.


// =============================================
// CONSTRUCTOR
// =============================================

// Inicializa _x y _y a 0 y _name a cadena vacia ""
// Mismo estilo que Point2D::Point2D() donde px = py = 0
Location::Location() {
    _x = 0.0;
    _y = 0.0;
    _name = "";
}


// =============================================
// GETTERS (metodos de consulta)
// =============================================

// Devuelve la coordenada x
// Mismo estilo que Point2D::getX() -> return px;
double Location::getX() const {
    return _x;
}

// Devuelve la coordenada y
// Mismo estilo que Point2D::getY() -> return py;
double Location::getY() const {
    return _y;
}

// Devuelve el nombre de la localizacion
string Location::getName() const {
    return _name;
}


// =============================================
// SETTERS (metodos modificadores)
// =============================================

// Establece la coordenada x
// Mismo estilo que Point2D::setX(int px) { this->px = px; }
// Usamos this-> para distinguir el parametro "x" del atributo "_x"
// (en este caso no seria estrictamente necesario porque el atributo
// se llama "_x" y el parametro "x", pero lo ponemos por coherencia
// con el estilo de Point2D)
void Location::setX(double x) {
    this->_x = x;
}

// Establece la coordenada y
// Mismo estilo que Point2D::setY
void Location::setY(double y) {
    this->_y = y;
}

// Establece el nombre
void Location::setName(const string& name) {
    this->_name = name;
}

// Establece x, y, y nombre de una sola vez
// Reutilizamos los setters anteriores para no repetir codigo
void Location::set(double x, double y, const string& name) {
    this->_x = x;
    this->_y = y;
    this->_name = name;
}


// =============================================
// METODOS DE CONSULTA (query methods)
// =============================================

// Comprueba si la posicion de este objeto esta dentro del area
// definida por las esquinas bottomLeft (abajo-izquierda) y topRight (arriba-derecha)
//
//                  +-----------+(topRight)
//                  |           |
//                  |    +(this)|
//                  |           |
//      (bottomLeft)+-----------+
//
// Para estar dentro, se deben cumplir las 4 condiciones:
//   _x >= bottomLeft._x  (no estar mas a la izquierda)
//   _x <= topRight._x    (no estar mas a la derecha)
//   _y >= bottomLeft._y  (no estar mas abajo)
//   _y <= topRight._y    (no estar mas arriba)
bool Location::isInsideArea(const Location &bottomLeft, const Location &topRight) const {
    return _x >= bottomLeft.getX() &&
           _x <= topRight.getX() &&
           _y >= bottomLeft.getY() &&
           _y <= topRight.getY();
}

// Calcula el cuadrado de la distancia euclidea entre este punto y otro
// Formula: (x1 - x2)^2 + (y1 - y2)^2
// No hacemos sqrt porque a veces solo necesitamos comparar distancias
// y el cuadrado es mas eficiente (evita la raiz cuadrada)
double Location::squaredDistance(const Location& location) const {
    double dx = _x - location.getX();  // diferencia en x
    double dy = _y - location.getY();  // diferencia en y
    return dx * dx + dy * dy;          // suma de cuadrados
}

// Calcula la distancia euclidea real
// Reutiliza squaredDistance() y le aplica sqrt
// Formula: sqrt( (x1-x2)^2 + (y1-y2)^2 )
double Location::distance(const Location& location) const {
    return sqrt(squaredDistance(location));
}

// Convierte este Location a un string con formato: "x y nombre"
// Si el nombre esta vacio, solo devuelve "x y"
// Usa std::to_string() para convertir doubles a string
string Location::toString() const {
    string output;

    // Primero anadimos las coordenadas separadas por espacio
    output += to_string(_x) + " " + to_string(_y);

    // Si hay nombre, lo anadimos separado por espacio
    if (!_name.empty())
        output += " " + _name;

    return output;
}


// =============================================
// METODO DE LECTURA (load)
// =============================================

// Lee de un flujo de entrada (cin, fichero, etc.) los datos de un Location
// Formato esperado en una linea: "x y nombre con varias palabras"
//
// Pasos:
// 1. Leer x e y (dos doubles separados por espacio)
// 2. Leer el resto de la linea como nombre (puede tener varias palabras)
// 3. Hacer Trim al nombre para quitar espacios al inicio y al final
//
// Estilo similar a Point2D::read() que hace: cin >> px >> py;
// pero aqui ademas leemos el nombre con getline
void Location::load(istream& is) {
    // Paso 1: Leemos las dos coordenadas del flujo de entrada
    is >> _x >> _y;

    // Paso 2: Leemos el resto de la linea (el nombre, que puede tener espacios)
    // getline lee desde la posicion actual hasta el fin de linea
    getline(is, _name);

    // Paso 3: Quitamos espacios/tabs sobrantes al inicio y al final del nombre
    Trim(_name);
}


// =============================================
// FUNCION LIBRE: Trim
// =============================================

// Elimina espacios y tabuladores al principio y al final de myString
// Ejemplo: "   Frist Campus Center   " -> "Frist Campus Center"
// Ejemplo: "   " -> ""
// Ejemplo: "" -> ""
//
// Usa find_first_not_of para encontrar el primer caracter que NO sea espacio/tab
// Usa find_last_not_of para encontrar el ultimo caracter que NO sea espacio/tab
// Luego se queda solo con el tramo entre esos dos
void Trim(string &myString) {
    // Caracteres que queremos eliminar de los bordes
    const string BLANKS = " \t";

    // Buscamos la posicion del primer caracter util (no espacio ni tab)
    size_t first = myString.find_first_not_of(BLANKS);

    // Si no encuentra ninguno, la cadena es solo espacios/tabs (o vacia)
    if (first == string::npos) {
        myString.clear();  // La dejamos vacia
        return;
    }

    // Buscamos la posicion del ultimo caracter util
    size_t last = myString.find_last_not_of(BLANKS);

    // Nos quedamos solo con el trozo entre first y last (ambos incluidos)
    myString = myString.substr(first, last - first + 1);
}
