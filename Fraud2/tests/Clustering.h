/*
 * Metodología de la Programación
 * Curso 2025/2026
 * Clustering.h — versión con soporte -DTESTING
 */

#ifndef CLUSTERING_H
#define CLUSTERING_H

#include "VectorInt.h"
#include "VectorLocation.h"

class Clustering {
public:
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
             unsigned int seed = DEFAULT_RANDOM_SEED);
    void run();

    static const unsigned int DEFAULT_RANDOM_SEED = 1761560597U;

#ifdef TESTING
public:
#else
private:
#endif
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
