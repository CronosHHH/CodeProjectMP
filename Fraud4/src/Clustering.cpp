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
 * Inicializa los campos a 0 o false, y el campo _seed con DEFAULT_RANDOM_SEED. 

 */
Clustering::Clustering()
        : _locations(),
            _K(0),
            _clusters(),
            _centroids(),
            _isDone(false),
            _seed(DEFAULT_RANDOM_SEED),
            _sumWCV(0),
            _numIterations(0){}
    
/**
 * @brief Gets the number of clusters
 * Query method
 * @return The number of clusters
 */
int Clustering::getK() const{
    return _K;
}

/**
 * @brief Gets the current vector of centroids
 * Query method
 * @return A const reference to the vector of centroids (a VectorLocation
 * object).
 */
const VectorLocation &Clustering::getCentroids() const{
    return _centroids;
}

/**
 * @brief Indicates whether the clustering algorithm (run() method) has
 * already been executed for this Clustering object.
 * Query method
 * @return true if the run() method has already been executed for this
 * Clustering object; false otherwise
 */
bool Clustering::isDone() const{
    return _isDone;
}

/**
 * @brief Gets the number of locations in the set of locations of this
 * Clustering object.
 * Query method
 * @return The number of locations in the set of locations of this
 * Clustering
 */
int Clustering::getNumLocations() const {
    return _locations.getSize();
}

/**
 * @brief Gets the cluster number for the Location determined by the
 * provided integer (@p locationIndex)
 * Query method
 * @param locationIndex An integer that determines the position of a
 * location in the vector of Location objects. Input parameter
 * @return The cluster number for the Location determined by
 * the provided integer (@p locationIndex). If the
 * clustering algorithm has not been run (_isDone is false), then it returns
 * -1.
 */
int Clustering::clusterOf(int locationIndex) const{
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
 * @brief Gets the value of the sum of the within-cluster variances of this
 * Clustering. This value is obtained from the field _sumWCV
 * @note The returned value will likely be a garbage value if the run()
 * method has not yet been executed (_isDone is false)
 * Query method
 * @return A double with the sum of within-cluster variances of this
 * Clustering
 */
double Clustering::getSumWCV() const{
    return _sumWCV;
}

/**
 * @brief  Gets the number of iterations used in the KMeans
 * algorithm until no cluster assignment change occurs.
 * It obtains the number of iterations (field _numberIterations) used
 * in the KMeans algorithm until no cluster change occurred.
 * @note The returned value will likely be a garbage value if the run()
 * method has not yet been executed (_isDone is false)
 * Query method
 * @return The number of iterations used in the KMeans algorithm
 */
int Clustering::getNumIterations() const{
    return _numIterations;
}

/**
 * @brief  Gets a string with information about the provided cluster (index
 * of a cluster). That string contains a line for each location in the given
 * cluster. The information of each location consists of an integer with
 * its location index (whithin the _location field), a whitespace, and
 * the information returned by the Location::toString() method for that
 * location.
 * Query method
 * @param cluster An integer, that defines the index of a cluster. Input
 * parameter
 * @return Gets a string with information about the provided cluster. If the
 * clustering algorithm has not been run (_isDone is false) or an
 * invalid value of cluster is provide, then it returns an empty string.
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
 * @brief Obtains a string with the some statistics data about this
 * Clustering object.
 * The first line contains the value of K; the second line contains the
 * value of the sum of within-cluster variances; the third line contains
 * the number of iterations used in the KMeans algorithm.
 * Query method
 * @return A string with the content described above
 */
std::string Clustering::getStatistics() const{
    return "K=" + std::to_string(_K) + "\n"
            "Sum of within-cluster variances: " + std::to_string(_sumWCV) + "\n"
            "Number of iterations: " + std::to_string(_numIterations) + "\n";

 }

/**
 * @brief Indicates whether this Clustering object is equivalent to the
 * provided Clustering object (@p other). Two Clustering objects are
 * considered equivalent if they have the same K value,
 * the same sum of within-cluster variances and the same number of
 * iterations in the KMeans algorithm.
 * If either this Clustering object or the provided Clustering object
 * (@p other) has not yet run the clustering algorithm (the run() method),
 * then they are not considered equivalent.
 * Query method
 * @param other A Clustering object. Input parameter
 * @return true if this Clustering object is equivalent to the provided
 * Clustering object (@p other); false otherwise
 */
bool Clustering::isEquivalentTo(const Clustering &other) const{
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
 * @brief Obtains a string with the fields of this Clustering object.
 * The first line contains the value of K; the second line contains the
 * value of the sum of within-cluster variances; the third line contains
 * the number of iterations used in the KMeans algorithm.
 * In the next three lines, information about the cluster number for each
 * location.
 * If follows information about each centroid
 * Next, for each cluster, information about its locations
 * Query method
 * @return A string with the content described above
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
void Clustering::set(const VectorLocation &locations, int K, unsigned int seed){
    if(K <= 0){
        throw std::invalid_argument("Valor de K no correspondiente.");
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

bool operator<(const Clustering &clustering1, const Clustering &clustering2)
{
    if (clustering1.getSumWCV() < clustering2.getSumWCV())
    {
        return true;
    }
    if (clustering1.getSumWCV() > clustering2.getSumWCV())
    {
        return false;
    }
    return clustering1.getNumIterations() < clustering2.getNumIterations();
}

bool operator>(const Clustering &clustering1, const Clustering &clustering2)
{
    return clustering2 < clustering1;
}

bool operator==(const Clustering &clustering1, const Clustering &clustering2)
{
    return (clustering1.getSumWCV() == clustering2.getSumWCV())
        && (clustering1.getNumIterations() == clustering2.getNumIterations());
}

bool operator!=(const Clustering &clustering1, const Clustering &clustering2)
{
    return !(clustering1 == clustering2);
}

bool operator<=(const Clustering &clustering1, const Clustering &clustering2)
{
    return (clustering1 < clustering2) || (clustering1 == clustering2);
}

bool operator>=(const Clustering &clustering1, const Clustering &clustering2)
{
    return (clustering1 > clustering2) || (clustering1 == clustering2);
}