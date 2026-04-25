#include <iostream>
#include <string>
#include <cmath>
#include <stdexcept>
#include "Clustering.h"




/*
 * Metodología de la Programación
 * Curso 2025/2026
 */

/**
 * @file Clustering.cpp
 * @author Silvia Acid Carrillo <acid@decsai.ugr.es>
 * @author Andrés Cano Utrera <acu@decsai.ugr.es>
 * @author Luis Castillo Vidal <L.Castillo@decsai.ugr.es>
 * 
 * Created on 22 de octubre de 2025, 11:57
 */

 /**
 * @brief Constructor de la clase Clustering.
 * Inicializa todos los campos en el orden de declaración de la clase:
 * - _locations y _centroids se inicializan como vectores vacíos (tamaño 0)
 * - _clusters se inicializa como un vector vacío (tamaño 0)
 * - _K se inicializa a 0
 * - _isDone se inicializa a false
 * - _seed se inicializa con DEFAULT_RANDOM_SEED
 * - _sumWCV se inicializa a 0
 * - _numIterations se inicializa a 0
 */
Clustering::Clustering(): _locations(), _K(0), _clusters(), 
    _centroids(), _isDone(false), _seed(DEFAULT_RANDOM_SEED),
    _sumWCV(0), _numIterations(0) {}
    
/**
 * @brief Nos devuelve el numero de clusters.
 * Es un metodo de consulta, asi que aniadimos "const" al final.
 * @return Numero de clusters.
 */
int Clustering::getK() const{
    return _K;
}

/**
 * @brief Nos devuelve el vector de centroides.
 * Es un metodo de consulta, asi que aniadimos "const" al final.
 * @return Vector de centroides.
 */
const VectorLocation& Clustering::getCentroids() const{
    return _centroids;
}

/**
 * @brief Metodo de constulta (const). Mira si el algoritmo
 * ya ha sido ejecutado.
 * @return true si run() ya ha sido ejecutado. En caso contrario,
 * false.
 */
bool Clustering::isDone() const{
    if(_isDone)
    {
        return true;
    }
    else{
        return false;
    }
    
}

/**
 * @brief Nos devuelve el numero de ubicaciones.
 * Es un metodo de consulta, así que aniadimos "const" al final.
 * @return Numero de ubicaciones.
 */
int Clustering::getNumLocations()const {
    return _locations.getSize();
}

/**
 * @brief Metodo de consulta. Nos dice el numero de cluster
 * de una localizacion determinado por locationIndex.
 * @return Si es false, -1. Si es true, el numero de cluster
 * correspondiente a locationIndex.
 */
int Clustering::clusterOf(int locationIndex)const{
    if(_isDone)
    {
        return _clusters.at(locationIndex);
    }
    else
    {
        // throw std::invalid_argument("El algoritmo aun no ha sido ejecutado");
        return -1;
    }
}

/**
 * @brief Metodo de consuta. Devuelve el valor del sumatorio de
 * las variaciones dentro del cluster.
 * @return Si el metodo aun no ha sido ejectuado, el sumatorio devuelve
 * -1 (para evitar que devuelva basura). Si _isDone = true, devuelve el sumatorio.
 */

double Clustering::getSumWCV() const{
    if(!_isDone){
        // throw std::invalid_argument("El algoritmo aun no ha sido ejecutado");
        return -1;
    }
    else{
    return _sumWCV;
    }
}

/**
 * @brief Metodo de consulta. Devuelve el numero de interacciones que 
 * ha usado el algoritmo KMeans.
 * @return Si el algoritmo aun no ha sido ejecutado, controlamos el error y devuelve
 * -1. Si ya ha sido ejecutado, devuelve _numIterations.
 */
int Clustering::getNumIterations() const{
    if(!_isDone){
        // throw std::invalid_argument("El algoritmo aun no ha sido ejecutado");
        return -1;
    }
    else{
    return _numIterations;
    }
}

/**
 * @brief Metodo de consulta. Devuelve un string con la informacion que solicita
 * el parametro de entrada "int cluster".
 * @result Un string con la informacion del cluster
 */
std::string Clustering::clusterInfo(int cluster) const
{
    //Creamos la variable que almacenara el resultado.
    std::string result_clusterInfo;
    
    //Si no se cumple alguna de las condiciones de seguridad del metodo, devuelve empty.
    if(!_isDone || cluster < 0 || cluster >= _K){
        result_clusterInfo = "";
    }
    else{

        //Se ejecuta un bucle donde se repasan todas las localizaciones.
        for(int i = 0; i < _locations.getSize(); i++)
        {

            //Si el cluster de entrada coincide con el valor de cluster de la localizacion, se ejecuta.
            if(cluster == _clusters.at(i))
            {
                //Se almacena en el string la location y sus datos.
                result_clusterInfo += std::to_string(i) + " ";
                result_clusterInfo += _locations.at(i).toString();
                result_clusterInfo += "\n";
            }
        }
    }

    return result_clusterInfo;
}

/**
 * @brief Metodo de consulta. Devuelve algunas estadisticas sobre
 * el objeto: valor de k, valor de la suma de with-in cluster variances,
 * valor del numero de iteraciones usados en Kmeans.
 * @return Un string con lo ya descrito.
 */
std::string Clustering::getStatistics() const{
    return "K=" + std::to_string(_K) + "\n"
            "Sum of within-cluster variances: " + std::to_string(_sumWCV) + "\n"
            "Number of iterations: " + std::to_string(_numIterations) + "\n";

 }

/**
 * @brief Metodo de consulta. Pregunta si dos objetos clustering son
 * equivalentes. Para ello, comprueba si sus metodos run() ya han sido ejecutados,
 * y si sus valores de _K, _sumWCV y _numIterations coinciden.
 * @result Devuelve true si son equivalentes (se cumple lo ya mencionado); falso si
 * no se cumple.
 */
bool Clustering::isEquivalentTo(const Clustering& other) const{ //PONER CONST
    bool result_equivalence = false;

    if(_isDone && other._isDone
        && getK() == other.getK()
        && _sumWCV == other._sumWCV
        && _numIterations == other._numIterations){
        
        result_equivalence = true;
        }

    return result_equivalence;
}

/**
 * @brief Metodo de consulta. Obtiene un string con los datos del objeto:
 * valores de getStatistics(), informacion sobre el numero de cluster de
 * cada localizacion y de cada centroide y informacion de las localizacioens de 
 * cada cluster.
 * @return Un string con el contenido que se ha descrito.
 */
std::string Clustering::toString() const {
    std::string result_toString = getStatistics();
    result_toString += "Cluster number for each location:\n";
    result_toString += _clusters.toString();
    result_toString += "Centroids:\n";
    result_toString += _centroids.toString();

    for(int i=0; i<_K; i++){
        result_toString += "Cluster " + std::to_string(i) + " information:\n";
        result_toString += clusterInfo(i);
    }

    return result_toString;
}

/**
 * @brief Establecer:
 * Guardar _locations = locations
 * Guardar _K = K y lanzar std::invalid_argument si K <= 0
 * Guardar _seed = seed
 * Inicializar _isDone = false
 * Inicializar _clusters con un VectorInt del tamaño del vector de ubicaciones
 * Inicializar _centroids con un VectorLocation de tamaño K
 * Inicializar _sumWCV = 0 y _numIterations = 0
 */
void Clustering::set(const VectorLocation& locations, int K, unsigned int seed){
    if(K <= 0){
        throw std::invalid_argument("Valor de K no correspondiente.");
    }
    if(K > locations.getSize()){
        throw std::invalid_argument("Valor de K supera el numero de locations.");
    }
    else{
        _K = K;
        _locations = locations;
        _seed = seed;
        _isDone = false;
        _clusters = VectorInt(locations.getSize());
        _centroids = VectorLocation(K);
        _sumWCV = 0;
        _numIterations = 0;
    }
}

/**
 * @brief Metodo run. Realiza el algoritmo KMeans. Para ello, inicializa clusters aleatorios a
 * las localizaciones. Posteriormente, recalcula los centroides haciendo una media de las localizaciones
 * de cada cluster. Finalmente, reasigna cada localizacion a su centroide mas cercano. Esto se repite hasta
 * que los centroides estan en la posicion perfecta y ninguna localizacion cambia de cluster.
 * 
 * @result No devuelve nada. Sin embargo, modifica lso valores de _numIterations y _isDone; además de lo ya mencionado.
 */
void Clustering::run(){

    //Asignamos clusters aleatorios a las localizaciones.
    initialClusterAssignment();

    //Inicializamos
    bool repetir_interaccion = true;
    _numIterations = 0;

    while(repetir_interaccion)
    {
        _numIterations++;

        /*Apartado 1. Vamos a recalcular los centroides. Para ello,
        acumulamos la suma de coordenadas de cada cluster*/

        //Inicializamos variables.
        VectorLocation nuevo_centroide(_K);
        VectorInt contador(_K);

        //Sumamos todas las coordenadas de cada cluster.
        for(int i = 0; i < _locations.getSize(); i++)
        {
            int j = _clusters.at(i);
            nuevo_centroide.at(j).setX(nuevo_centroide.at(j).getX() + _locations.at(i).getX());
            nuevo_centroide.at(j).setY(nuevo_centroide.at(j).getY() + _locations.at(i).getY());
            contador.at(j)++;
        }

        //Hacenmos la media
        for(int j = 0; j < _K; j++)
        {
            if(contador.at(j) > 0){
                _centroids.at(j).setX(nuevo_centroide.at(j).getX() / contador.at(j));
                _centroids.at(j).setY(nuevo_centroide.at(j).getY() / contador.at(j));
            }
        }

        /*Aoartado 2. Vamos a reasignar cada localizacion a su centroide mas cercano.
        Entonces, si algun parametro ha cambiado, el repetir_interaccion se mantiene en true 
        y aumentaremos el _numIterations.*/

        repetir_interaccion = false;

        for(int i = 0; i < _locations.getSize(); i++){
            int mejor_cluster = 0;
            double mejor_dist = _locations.at(i).squaredDistance(_centroids.at(0));

            for(int j = 1; j < _K; j++){

                double dist = _locations.at(i).squaredDistance(_centroids.at(j));
                
                //Si su distancia es menor, se establece como el mejor.
                if(dist < mejor_dist)
                {
                    mejor_dist = dist;
                    mejor_cluster = j;
                }
            }

            if(_clusters.at(i) != mejor_cluster){
                _clusters.at(i) = mejor_cluster;
                repetir_interaccion = true;
            }
        } 
    }

    calculateSumWCV();
    _isDone = true;
}

/**
 * @brief Metodo modificador. Asignación inicial aleatoria de cada localizacion en uno de
 * los clusteres (entre 0 y K-1). Para ello, fija la generacion aleatoria mediante srand(_seed).
 */
void Clustering::initialClusterAssignment(){
    srand(_seed);
    for(int i = 0; i < _locations.getSize(); i++){
        _clusters.at(i) = rand() % _K;
    }
}

/**
 * @brief Metodo modificador. Calcula el sumatorio de los within cluster variances.
 * Para ello, inicializa la variable _sumWCV = 0.0, y recorre todas las localizaciones.
 * En cada una de ellas, establece int j como el numero de cluster de esa localizacion, y luego
 * realiza la SquaredDistance entre la localizacion y el centroide de ese cluster.
 * 
 * @result Un sumatorio de las within cluster variances.
 */

double Clustering::calculateSumWCV(){
    _sumWCV = 0.0;
    
    for(int i = 0; i < _locations.getSize(); i++)
    {
        int j = _clusters.at(i);

        _sumWCV += _locations.at(i).squaredDistance(_centroids.at(j));
    }

    return _sumWCV;
}