#ifndef ARRAYCLUSTERING_H
#define ARRAYCLUSTERING_H

#include "Clustering.h"

const int INITIAL_ARRAY_CLUSTERING_CAPACITY = 2;
const int ARRAY_CLUSTERING_CAPACITY_INCREMENT = 2;

struct ArrayClustering{
    Clustering *clustering; 
    int capacity; 
    int size; 
};

void InitializeArrayClustering(ArrayClustering &arrayClustering, 
    int capacity = INITIAL_ARRAY_CLUSTERING_CAPACITY );

void DeallocateArrayClustering(ArrayClustering &arrayClustering);

int FindArrayClustering(const ArrayClustering &arrayClustering,
                        const Clustering &clustering);

void AppendArrayClustering(ArrayClustering &arrayClustering,
                           const Clustering &clustering);

void SortArrayClustering(ArrayClustering &arrayClustering);

#endif /* ARRAYCLUSTERING_H */