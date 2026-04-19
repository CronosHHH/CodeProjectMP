/*
 * Metodología de la Programación
 * Curso 2025/2026
 */

/**
 * @file ArrayClustering.cpp
 * @author Silvia Acid Carrillo <acid@decsai.ugr.es>
 * @author Andrés Cano Utrera <acu@decsai.ugr.es>
 * @author Luis Castillo Vidal <L.Castillo@decsai.ugr.es>
 * 
 * Created on 22 de octubre de 2025, 11:57
 */

#include <stdexcept>
#include "ArrayClustering.h"

/**
 * @brief Initializes the provided ArrayClustering with a given capacity. It
 * allocates a dynamic array of Clustering objects with the provided capacity, 
 * sets the capacity field and initializes the size field to 0.
 * @throw std::out_of_range Throws a std::out_of_range exception if the
 * provided capacity is less than or equal to 0.
 * @param arrayClustering The ArrayClustering to initialize. Output parameter
 * @param capacity The initial capacity of the array. Input parameter
 */
void InitializeArrayClustering(ArrayClustering arrayClustering, int capacity){
    if (capacity <= 0) {
        throw std::out_of_range("Capacity must be greater than 0");
    }
    arrayClustering.clustering = new Clustering[capacity];
    arrayClustering.capacity = capacity;
    arrayClustering.size = 0;
};

/**
 * @brief Deallocates the dynamic array of Clustering objects in the provided
 * ArrayClustering. It also sets the clustering pointer to nullptr, and the
 * capacity and size fields to 0.
 * @param arrayClustering The ArrayClustering to deallocate. Output parameter
 */
void DeallocateArrayClustering(ArrayClustering arrayClustering){
    if (arrayClustering.clustering != nullptr) {
        delete[] arrayClustering.clustering;
        arrayClustering.clustering = nullptr;
    }
    arrayClustering.capacity = 0;
    arrayClustering.size = 0;
};

/**
 * @brief Searches for a given Clustering object in the provided
 * ArrayClustering. The search is performed by comparing each Clustering object
 * in the array with the provided Clustering object using the
 * Clustering::isEquivalentTo() method.
 * @param arrayClustering The ArrayClustering where to search will be 
 * performed. Input parameter
 * @param clustering The Clustering object to search for. Input parameter
 * @return The position of the Clustering object in the array if found;
 * -1 otherwise.
 */
int FindArrayClustering(ArrayClustering arrayClustering,Clustering clustering){
    for (int i = 0; i < arrayClustering.size; i++) {
        if (arrayClustering.clustering[i].isEquivalentTo(clustering)) {
            return i;
        }
    }
    return -1;
};

/**
 * @brief Appends a given Clustering object to the provided
 * ArrayClustering. If the array is full, it resizes the array by doubling its
 * capacity before appending the new Clustering object.
 * @param arrayClustering The ArrayClustering where the Clustering object will
 * be appended. Output parameter
 * @param clustering The Clustering object to append. Input parameter
 */
void AppendArrayClustering(ArrayClustering arrayClustering,Clustering clustering){
    // Si el array está lleno, redimensionamos
    if (arrayClustering.size >= arrayClustering.capacity) {
        int newCapacity = arrayClustering.capacity + ARRAY_CLUSTERING_CAPACITY_INCREMENT;
        Clustering *newClustering = new Clustering[newCapacity];
        
        // Copiar elementos del array antiguo
        for (int i = 0; i < arrayClustering.size; i++) {
            newClustering[i] = arrayClustering.clustering[i];
        }
        
        // Liberar el array antiguo y actualizar referencias
        delete[] arrayClustering.clustering;
        arrayClustering.clustering = newClustering;
        arrayClustering.capacity = newCapacity;
    }
    
    // Añadir el nuevo Clustering
    arrayClustering.clustering[arrayClustering.size] = clustering;
    arrayClustering.size++;
};

/**
 * @brief Sorts the Clustering objects in the provided ArrayClustering in
 * ascending order based on their sum of within-cluster variances. If two
 * Clustering objects have the same sum of within-cluster variances, they are
 * further sorted by their number of iterations in ascending order.
 * @param arrayClustering The ArrayClustering to sort. Output parameter
 */

void SortArrayClustering(ArrayClustering arrayClustering){
    // Bubble sort
    for (int i = 0; i < arrayClustering.size - 1; i++) {
        for (int j = 0; j < arrayClustering.size - 1 - i; j++) {
            double sumWCV_j = arrayClustering.clustering[j].getSumWCV();
            double sumWCV_j1 = arrayClustering.clustering[j + 1].getSumWCV();
            int numIter_j = arrayClustering.clustering[j].getNumIterations();
            int numIter_j1 = arrayClustering.clustering[j + 1].getNumIterations();
            
            // Comparar por suma de varianzas, y si son iguales por número de iteraciones
            bool shouldSwap = false;
            if (sumWCV_j > sumWCV_j1) {
                shouldSwap = true;
            } else if (sumWCV_j == sumWCV_j1 && numIter_j > numIter_j1) {
                shouldSwap = true;
            }
            
            if (shouldSwap) {
                // Intercambiar
                Clustering temp = arrayClustering.clustering[j];
                arrayClustering.clustering[j] = arrayClustering.clustering[j + 1];
                arrayClustering.clustering[j + 1] = temp;
            }
        }
    }
};


