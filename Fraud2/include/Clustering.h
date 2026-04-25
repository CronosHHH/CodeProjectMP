#ifndef CLUSTERING_H
#define CLUSTERING_H

#include "VectorInt.h"
#include "VectorLocation.h"

class Clustering {
public:

    //__________________________________
    static const unsigned int DEFAULT_RANDOM_SEED = 1761560597U;
    //__________________________________

    /**
     * @brief Construtor de la clase Clustering que inicializa todos los miembros.
     * Crea un objeto Clustering con estado inicial vacío (sin ubicaciones ni clusters).
     * Todos los miembros se inicializan en el orden de declaración de la clase.
     */
    Clustering();
    int getK() const;
    const VectorLocation& getCentroids() const;
    bool isDone() const;
    int getNumLocations() const;
    int clusterOf(int locationIndex) const;
    double getSumWCV() const;
    int getNumIterations() const;
    std::string clusterInfo(int cluster) const;
    std::string getStatistics() const;
    bool isEquivalentTo(const Clustering& other) const;
    std::string toString() const; 
    void set(const VectorLocation &locations, int K, 
        unsigned int seed=DEFAULT_RANDOM_SEED);
    void run();
//__________________________________
#ifdef TESTING
public:
#else
//__________________________________

private:

//__________________________________
#endif
//__________________________________
    // static const unsigned int DEFAULT_RANDOM_SEED=1761560597U; --> lo meto en public
    VectorLocation _locations;
    int _K;
    VectorInt _clusters;
    VectorLocation _centroids;
    bool _isDone;
    unsigned int _seed;
    double _sumWCV;
    int _numIterations;
    void initialClusterAssignment();
    double calculateSumWCV();
};

#endif /* CLUSTERING_H */