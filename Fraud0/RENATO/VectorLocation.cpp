/*
 * Metodología de la Programación
 * Curso 2025/2026
 */

/**
 * @file VectorLocation.cpp
 * @author Silvia Acid Carrillo <acid@decsai.ugr.es>
 * @author Andrés Cano Utrera <acu@decsai.ugr.es>
 * @author Luis Castillo Vidal <L.Castillo@decsai.ugr.es>
 * 
 * Created on 30 de julio de 2025, 11:27
 */

// Incluimos las librerias necesarias
#include <iostream>   // Para flujos de entrada/salida
#include <string>     // Para string y to_string
#include <stdexcept>  // Para std::out_of_range
#include "VectorLocation.h"

using namespace std;
// Usamos "using namespace std;" igual que en Rectangle.cpp
// Asi escribimos "string" en vez de "std::string", etc.


// =============================================
// CONSTRUCTOR
// =============================================

// Construye un VectorLocation con un tamaño inicial dado.
// Si size es invalido (< 0 o > capacidad maxima), lanza excepcion.
// Los elementos del array _locations ya se inicializan solos 
// con el constructor por defecto de Location (x=0, y=0, name="").
//
// Nota importante: el valor por defecto (= 0) solo se pone en el .h,
// NUNCA en el .cpp. Si lo pones aqui tambien, el compilador da error.
VectorLocation::VectorLocation(int size) {
    if (size < 0 || size > DIM_VECTOR_LOCATIONS) {
        throw out_of_range("VectorLocation: size invalido");
    }
    _size = size;
}


// =============================================
// GETTERS (metodos de consulta)
// =============================================

// Devuelve el numero de elementos que contiene actualmente el vector.
// Estilo similar a Rectangle::getTopLeft() -> return topleft;
int VectorLocation::getSize() const {
    return _size;
}

// Devuelve la capacidad maxima del array (constante DIM_VECTOR_LOCATIONS = 100).
int VectorLocation::getCapacity() const {
    return DIM_VECTOR_LOCATIONS;
}


// =============================================
// toString
// =============================================

// Devuelve un string con toda la informacion del VectorLocation:
// - Primera linea: numero de locations
// - Siguientes lineas: cada location con su toString()
//
// Ejemplo de salida:
// 4
// 23.700000 14.800000 Cannon Dial Elm
// 26.400000 14.900000 Cottage
// 25.600000 14.900000 Ivy
// 24.800000 14.900000 Quadrangle
string VectorLocation::toString() const {
    string output;

    // Primera linea: el numero de elementos
    output += to_string(_size);

    // Por cada Location almacenada, anadimos una linea con su informacion
    for (int i = 0; i < _size; i++) {
        output += "\n" + _locations[i].toString();
    }

    return output;
}


// =============================================
// findLocation
// =============================================

// Busca una Location en el array comparando SOLO por nombre.
// Si la encuentra, devuelve la posicion (0, 1, 2, ...).
// Si no la encuentra, devuelve -1.
//
// Similar a como en Rectangle se recorren puntos para comparar,
// aqui recorremos el array _locations.
int VectorLocation::findLocation(const Location &location) const {
    for (int i = 0; i < _size; i++) {
        // Comparamos solo por nombre (segun la especificacion)
        if (_locations[i].getName() == location.getName()) {
            return i;  // Encontrada en posicion i
        }
    }
    return -1;  // No encontrada
}


// =============================================
// select
// =============================================

// Devuelve un NUEVO VectorLocation con aquellas locations
// cuya posicion esta dentro del area definida por bottomLeft y topRight.
//
// Usa el metodo isInsideArea de Location para comprobar cada una.
// Usa append para añadir al resultado (asi evita duplicados automaticamente).
//
// Similar a la funcion isInside(Point2D, Rectangle) de Rectangle.cpp,
// pero aqui filtramos un conjunto entero de puntos.
VectorLocation VectorLocation::select(const Location &bottomLeft,
                                      const Location &topRight) const {
    VectorLocation result;  // VectorLocation vacio (size=0)

    for (int i = 0; i < _size; i++) {
        // Si la location esta dentro del area, la anadimos al resultado
        if (_locations[i].isInsideArea(bottomLeft, topRight)) {
            result.append(_locations[i]);
        }
    }

    return result;
}


// =============================================
// clear
// =============================================

// Vacia el vector poniendo _size a 0.
// No hace falta "borrar" los elementos del array, simplemente
// dejamos de considerarlos al poner _size = 0.
void VectorLocation::clear() {
    _size = 0;
}


// =============================================
// at (version const y version no-const)
// =============================================

// Devuelve una REFERENCIA CONSTANTE al elemento en la posicion pos.
// Si la posicion no es valida (< 0 o >= _size), lanza excepcion.
//
// Usamos referencia (const Location&) para no copiar el objeto,
// y const porque es un metodo de consulta (no modifica nada).
const Location& VectorLocation::at(int pos) const {
    if (pos < 0 || pos >= _size) {
        throw out_of_range("VectorLocation::at posicion invalida");
    }
    return _locations[pos];
}

// Version NO constante de at.
// Permite modificar el elemento devuelto, por ejemplo:
//   miVector.at(0).setName("Nuevo nombre");
// Tambien lanza excepcion si la posicion no es valida.
Location& VectorLocation::at(int pos) {
    if (pos < 0 || pos >= _size) {
        throw out_of_range("VectorLocation::at posicion invalida");
    }
    return _locations[pos];
}


// =============================================
// append
// =============================================

// Anade una Location al final del vector (en la posicion _size).
// Reglas segun la especificacion:
// 1. Si el nombre esta vacio -> no se anade, devuelve false (sin excepcion)
// 2. Si ya existe (mismo nombre) -> no se anade, devuelve false (sin excepcion)
// 3. Si el array esta lleno -> lanza excepcion out_of_range
// 4. Si pasa todos los filtros -> se anade, incrementa _size, devuelve true
bool VectorLocation::append(const Location &location) {
    // 1. Si el nombre esta vacio, no anadimos
    if (location.getName().empty()) {
        return false;
    }

    // 2. Si ya existe una Location con ese nombre, no anadimos
    if (findLocation(location) != -1) {
        return false;
    }

    // 3. Si el array esta lleno, lanzamos excepcion
    if (_size >= DIM_VECTOR_LOCATIONS) {
        throw out_of_range("VectorLocation::append array lleno");
    }

    // 4. Todo ok: anadimos la location en la siguiente posicion libre
    _locations[_size] = location;
    _size++;

    return true;
}


// =============================================
// join
// =============================================

// Une otro VectorLocation con este.
// Recorre todas las locations del VectorLocation proporcionado
// e intenta anadir cada una con append().
// append() ya se encarga de:
//   - No anadir duplicados (mismo nombre)
//   - No anadir nombres vacios
//   - Lanzar excepcion si se llena
//
// Similar a como en Rectangle.cpp se combinan dos rectangulos
// en doOverlap, aqui combinamos dos conjuntos de locations.
void VectorLocation::join(const VectorLocation &locations) {
    for (int i = 0; i < locations.getSize(); i++) {
        append(locations.at(i));
    }
}


// =============================================
// sort
// =============================================

// Ordena el array de locations por orden alfabetico creciente
// del nombre (string).
//
// Usamos el algoritmo de seleccion (selection sort):
// - Para cada posicion i, buscamos el minimo desde i hasta el final
// - Si el minimo no esta en i, intercambiamos
//
// Comparamos nombres con el operador < de string,
// que ya compara alfabeticamente.
void VectorLocation::sort() {
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
}
