#include <string>
#include <iostream>
#include <stdexcept>
#include "DataSet.h"

using namespace std;


/*  
_____________________________________________

    * Cadena magica del formato
    static const std::string MAGIC_STRING_T;

    * Matriz de valores de instancias
    int** _values;

    * Numero de instancias
    int _nInstances;

    * Numero de ubicaciones
    int _nLocations;

    * Etiquetas de cada instancia
    VectorInt _labels;
    
    * Ubicaciones del conjunto
    VectorLocation _locations;
_____________________________________________
*/ 

const string DataSet::MAGIC_STRING_T="MP-FRAUD_DATASET-T-1.0";

/**
 * @brief Libera la memoria dinamica reservada y resetea los atributos.
 */
void DataSet::liberar()
{
    if (_values != nullptr)
    {
        for (int i = 0; i < _nInstances; ++i)
        {
            delete[] _values[i];
        }
        delete[] _values;
        _values = nullptr;
    }

    _nInstances = 0;
    _nLocations = 0;
}

/**
 * @brief Reserva memoria para una matriz n x m.
 * @param nInstances Numero de instancias.
 * @param nLocations Numero de ubicaciones.
 */
void DataSet::reservar(int nInstances, int nLocations)
{
    _nInstances = nInstances;
    _nLocations = nLocations;

    if (_nInstances > 0 && _nLocations > 0)
    {
        _values = new int*[_nInstances];
        for (int i = 0; i < _nInstances; ++i)
        {
            _values[i] = new int[_nLocations];
        }
    }
    else
    {
        _values = nullptr;
    }
}

/**
 * @brief Copia los datos de otro DataSet.
 * Asume memoria reservada suficiente.
 * @param orig Objeto origen de la copia.
 */
void DataSet::copiar(const DataSet &orig)
{
    _nInstances = orig._nInstances;
    _nLocations = orig._nLocations;
    _labels = orig._labels;
    _locations = orig._locations;

    for (int i = 0; i < _nInstances; ++i)
    {
        for (int j = 0; j < _nLocations; ++j)
        {
            _values[i][j] = orig._values[i][j];
        }
    }
}

/**
 * @brief It builds a DataSet object with the provided number of instances
 * and number of locations. This class uses a bidimensional matrix with 
 * nInstances rows and nLocations columns to store the values of the set 
 * of instances.
 * Note that this constructor also builds the vector (with a size equal to 
 * nInstances) of labels and the vector of locations (with a size equal to 
 * nLocations).
 * This constructor initializes with a value of 0 all the values in the 2D
 * matrix. 
 * The vector of labels is initialized with a value of 0 for each instance.
 * The Location objects in the vector of locations are built with the 
 * Location default constructor.
 * @param nInstances An integer with the number of instances.
 * Input parameter
 * @param nLocations An integer with the number of locations.
 * Input parameter
 */
DataSet::DataSet(int nInstances, int nLocations)
    : _values(nullptr), _nInstances(0), _nLocations(0), _labels(), _locations()
{
    if (nInstances < 0 || nLocations < 0)
    {
        throw std::out_of_range("DataSet: tamanio invalido");
    }

    reservar(nInstances, nLocations);
    _labels = VectorInt(nInstances);
    _locations = VectorLocation(nLocations);

    for (int i = 0; i < _nInstances; ++i)
    {
        for (int j = 0; j < _nLocations; ++j)
        {
            _values[i][j] = 0;
        }
    }
};

/**
 * @brief Copy constructor
 * @param orig the DataSet object used as source for the copy. 
 * Input parameter
 */
DataSet::DataSet(const DataSet &orig)
    : _values(nullptr), _nInstances(0), _nLocations(0), _labels(), _locations()
{
    reservar(orig._nInstances, orig._nLocations);
    copiar(orig);
};

/**
 * @brief Destructor
 */
DataSet::~DataSet()
{
    liberar();
};

/**
 * @brief Overloading of the assignment operator for DataSet class
 * Modifier method
 * @param orig the DataSet object used as source for the assignment.
 * Input parameter
 * @return A reference to this object
 */
DataSet &DataSet::operator=(const DataSet &orig)
{
    if (this != &orig)
    {
        liberar();
        reservar(orig._nInstances, orig._nLocations);
        copiar(orig);
    }

    return *this;
};

/**
 * @brief Gets the number of instances in this DataSet
 * Query method
 * @return The number of instances in this DataSet
 */
int DataSet::getNumInstances() const
{
    return _nInstances;
};

/**
 * @brief Gets the number of localizations in this DataSet
 * Query method
 * @return The number of localizations in this DataSet
 */
int DataSet::getNumLocations() const
{
    return _nLocations;
}; 

/**
 * @brief Gets the value for the instance instanceIndex at the localization
 * locationIndex.
 * @throw std::out_of_range Throws a std::out_of_range exception if 
 * instanceIndex is not a valid index for an instance in this DataSet.
 * @throw std::out_of_range Throws a std::out_of_range exception if 
 * locationIndex is not a valid index for an location in this DataSet.
 * Query method
 * @param instanceIndex An integer with the index of the selected instance. 
 * Input parameter
 * @param locationIndex An integer with the index of the selected location. 
 * Input parameter
 * @return The value for the instance instanceIndex at the localization
 * locationIndex
 */   
int DataSet::getValue(int instanceIndex, int locationIndex) const
{
    if (instanceIndex < 0 || instanceIndex >= _nInstances)
    {
        throw std::out_of_range("DataSet::getValue instancia invalida");
    }
    if (locationIndex < 0 || locationIndex >= _nLocations)
    {
        throw std::out_of_range("DataSet::getValue ubicacion invalida");
    }

    return _values[instanceIndex][locationIndex];
};

/**
 * @brief Gets the label (integer value) of the instance at the provided
 * position (instanceIndex)
 * @throw std::out_of_range Throws a std::out_of_range exception if 
 * instanceIndex is not a valid index for an instance in this DataSet.
 * Query method
 * @param instanceIndex An integer with the index of the selected instance.
 * Input parameter
 * @return The label (integer value) of the instance at the provided
 * position
 */
int DataSet::getLabel(int instanceIndex) const
{
    if (instanceIndex < 0 || instanceIndex >= _nInstances)
    {
        throw std::out_of_range("DataSet::getLabel instancia invalida");
    }

    return _labels.at(instanceIndex);
};

/**
 * @brief Gets a const reference to the vector of Location objects in this
 * DataSet
 * Query method
 * @return A const reference to the vector of Location objects in this
 * DataSet
 */
VectorLocation DataSet::getVectorLocation() const
{
    return _locations;
};

/**
 * @brief Gets a const reference to the vector of labels in this DataSet
 * Query method
 * @return A const reference to the vector of labels in this DataSet
 */
VectorInt DataSet::getVectorLabels() const
{
    return _labels;
};

/**
 * @brief Obtains a string with information about this DataSet object, 
 * in the following format:
 * -Information about the set of locations of this DataSet:
 *    - A line with the number of locations
 *    - For each location, a line with its information, converted to
 *      a string with the Location::toString() method.
 * - Information about the labels of each instance in this DataSet:
 *    - A line with the number of instances
 *    - A line with the labels (space separated) of the set of instances.
 * - Instances of the Dataset. This is the information contained in the 
 *   2D matrix of this DataSet.
 *     - For each instance, a line with the values (space separated) of 
 *       that instance.
 * Query method
 * @return string with information about this CrimeSet object
 */
std::string DataSet::toString() const {
    string result;
    
    result += _locations.toString();
    result += _labels.toString();
    for(int instance=0; instance<getNumInstances(); instance++){
        for(int location=0; location<getNumLocations(); location++){
            //result += to_string((*this)(instance,location));
            result += to_string(this->getValue(instance,location));
            if(location<getNumLocations()-1){
                result += " ";
            }
        }
        result += "\n";
    }    
    return result;
}

/**
 * @brief Sets a new value for the instance instanceIndex at the 
 * localization locationIndex.
 * @throw std::out_of_range Throws a std::out_of_range exception if 
 * instanceIndex is out of the valid range
 * @throw std::out_of_range Throws a std::out_of_range exception if 
 * locationIndex is out of the valid range
 * Modifier method
 * @param instanceIndex An integer with the index of the selected instance. 
 * Input parameter
 * @param locationIndex An integer with the index of the selected location. 
 * Input parameter
 * @param value An integer with the new value for the selected instance.
 * Input parameter
 */
void DataSet::setValue(int instanceIndex, int locationIndex, int value)
{
    if (instanceIndex < 0 || instanceIndex >= _nInstances)
    {
        throw std::out_of_range("DataSet::setValue instancia invalida");
    }
    if (locationIndex < 0 || locationIndex >= _nLocations)
    {
        throw std::out_of_range("DataSet::setValue ubicacion invalida");
    }

    _values[instanceIndex][locationIndex] = value;
};

/**
 * @brief Sets a new the label for the provided instance.
 * Modifier method
 * @param instanceIndex An integer with the index of the selected instance. 
 * Input parameter
 * @param label An integer with the new value for the label of the selected
 * instance.
 * Input parameter
 */
void DataSet::setLabel(int instanceIndex, int label)
{
    if (instanceIndex < 0 || instanceIndex >= _nInstances)
    {
        throw std::out_of_range("DataSet::setLabel instancia invalida");
    }

    _labels.at(instanceIndex) = label;
};

/**
 * Assigns the provided value to each instance and location. That is, all 
 * instances of this DataSet are initialized with the provided value.
 * Modifier method
 * @param value An integer with the value to assign to every instance and
 * location
 * Input parameter
 */
void DataSet::initInstances(int value)
{
    for (int i = 0; i < _nInstances; ++i)
    {
        for (int j = 0; j < _nLocations; ++j)
        {
            _values[i][j] = value;
        }
    }
};

/**
 * @brief Removes all the information in this DataSet object:
 * - The vector of Location objects (_locations) is left empty. That is,
 * it should represent a vector with 0 locations.
 * - The vector of labels (_labels) is left empty. That is, it should 
 * represent a vector with 0 labels.
 * - The matrix (_values) with the values for each instance is left empty. 
 * That is, it should represent a matrix with 0 instances and 0 locations.
 * - The remaining fields of this object are updated accordingly.
 * Modifier method
 */
void DataSet::clear()
{
    liberar();
    _labels.clear();
    _locations.clear();
};

/**
 * @brief Saves this DataSet object in the given file. See files *.dts in 
 * the folder DataSets as example of files with DataSet information. 
 * Note that the format of the output file is the same as the string that
 * returns the toString() method, except that the save() method should 
 * insert the magic string at the beginning of the output file.
 * @throw std::ios_base::failure Throws a std::ios_base::failure exception 
 * if the given file cannot be opened or if an error occurs while writing
 * to the file.
 * Query method
 * @param fileName The name of the file where the DataSet will be saved. 
 * Input parameter
 */
void DataSet::save(std::string fileName)
{
    std::ofstream os(fileName);
    if (!os)
    {
        throw std::ios_base::failure("DataSet::save no se pudo abrir");
    }

    os << MAGIC_STRING_T << "\n";
    os << toString();

    if (!os)
    {
        throw std::ios_base::failure("DataSet::save error de escritura");
    }
};

/**
 * @brief Loads into this object the DataSet information stored in the 
 * given file. See files *.dts in the folder DataSets as example of files
 * with DataSet information. 
 * @note Note that this method should remove any previous information that
 * this object previously contained.
 * @note This method throws an exception in some error cases (see below). 
 * Before throwing the corresponding exception, this method clears
 * the object (it calls to clear() method) to leave the object in a 
 * consistent state.
 * @throw throw std::invalid_argument Throws a std::invalid_argument 
 * exception if an invalid magic string is found in the given file
 * @throw std::out_of_range Throws a std::out_of_range exception if the 
 * number of locations or the number of instances in the given file is 
 * negative.
 * Modifier method
 * @param fileName The name of the file where the DataSet is stored. 
 * Input parameter
 * @throw std::ios_base::failure Throws a std::ios_base::failure exception 
 * if the given file cannot be opened or if an error occurs while reading
 * from the file. 
 */
void DataSet::load(std::string fileName)
{
    clear();

    std::ifstream is(fileName);
    if (!is)
    {
        throw std::ios_base::failure("DataSet::load no se pudo abrir");
    }

    std::string magic;
    std::getline(is, magic);
    if (!is)
    {
        clear();
        throw std::ios_base::failure("DataSet::load error de lectura");
    }
    if (magic != MAGIC_STRING_T)
    {
        clear();
        throw std::invalid_argument("DataSet::load cadena magica invalida");
    }

    _locations.load(is);

    int nInstances = 0;
    if (!(is >> nInstances))
    {
        clear();
        throw std::ios_base::failure("DataSet::load error de lectura");
    }
    if (nInstances < 0)
    {
        clear();
        throw std::out_of_range("DataSet::load instancias negativas");
    }

    _labels = VectorInt(nInstances);
    for (int i = 0; i < nInstances; ++i)
    {
        int label = 0;
        if (!(is >> label))
        {
            clear();
            throw std::ios_base::failure("DataSet::load error de lectura");
        }
        _labels.at(i) = label;
    }

    reservar(nInstances, _locations.getSize());
    for (int i = 0; i < _nInstances; ++i)
    {
        for (int j = 0; j < _nLocations; ++j)
        {
            int value = 0;
            if (!(is >> value))
            {
                clear();
                throw std::ios_base::failure("DataSet::load error de lectura");
            }
            _values[i][j] = value;
        }
    }
};

/**
 * @brief Gets a new DataSet from this DataSet. The DataSet will contain 
 * the same number of instances as this DataSet, but the number of locations
 * is given by the number of clusters in the provided Clustering object.
 * Therefore, the returned DataSet will have a reduced number of columns 
 * and an equal number of rows compared to this DataSet. 
 * The provided Clustering object defines how to reduce the set of columns.
 * Column 0 will contain the sum of the columns of this DataSet belonging 
 * to cluster 0, column 1 the sum of the columns belonging to cluster 1, 
 * and so on.
 * The vector of locations will be a copy of the vector of centroids of the
 * provided Clustering object.
 * The vector of labels will be a copy of the vector of labels in this 
 * DataSet.
 * @throw throw std::invalid_argument Throws a std::invalid_argument 
 * exception if the method Clustering::isDone() return false with the 
 * provided Clustering object.
 * @throw throw std::invalid_argument Throws a std::invalid_argument 
 * exception if the number of locations in the provided Clustering object
 * is not equal to the number of locations in this DataSet.
 * Query method
 * @param clustering A Clustering object.
 * Input parameter
 * @return A reduced DataSet
 */
DataSet DataSet::getReducedDataSet(Clustering clustering)
{
    if (!clustering.isDone())
    {
        throw std::invalid_argument("DataSet::getReducedDataSet clustering no ejecutado");
    }
    if (clustering.getNumLocations() != _nLocations)
    {
        throw std::invalid_argument("DataSet::getReducedDataSet tamanio incompatible");
    }

    int newLocations = clustering.getK();
    DataSet reduced(_nInstances, newLocations);
    reduced._labels = _labels;
    reduced._locations = clustering.getCentroids();

    for (int i = 0; i < _nInstances; ++i)
    {
        for (int j = 0; j < _nLocations; ++j)
        {
            int cluster = clustering.clusterOf(j);
            if (cluster < 0 || cluster >= newLocations)
            {
                throw std::invalid_argument("DataSet::getReducedDataSet cluster invalido");
            }
            reduced._values[i][cluster] += _values[i][j];
        }
    }

    return reduced;
};

int DataSet::nearestInstance(VectorInt instance, bool selected[]) const
{
    if (instance.getSize() != _nLocations)
    {
        throw std::invalid_argument("DataSet::nearestInstance tamanio incompatible");
    }
    if (_nInstances == 0)
    {
        return -1;
    }

    int nearestIndex = -1;
    double bestDistance = 0.0;

    for (int i = 0; i < _nInstances; ++i)
    {
        if (selected != nullptr && selected[i])
        {
            continue;
        }

        double distance = 0.0;
        for (int j = 0; j < _nLocations; ++j)
        {
            double diff = static_cast<double>(_values[i][j] - instance.at(j));
            distance += diff * diff;
        }

        if (nearestIndex == -1 || distance < bestDistance)
        {
            bestDistance = distance;
            nearestIndex = i;
        }
    }

    return nearestIndex;
}

const int &DataSet::operator()(int instanceIndex, int locationIndex) const
{
    if (instanceIndex < 0 || instanceIndex >= _nInstances)
    {
        throw std::out_of_range("DataSet::operator() instancia invalida");
    }
    if (locationIndex < 0 || locationIndex >= _nLocations)
    {
        throw std::out_of_range("DataSet::operator() ubicacion invalida");
    }

    return _values[instanceIndex][locationIndex];
}

int &DataSet::operator()(int instanceIndex, int locationIndex)
{
    if (instanceIndex < 0 || instanceIndex >= _nInstances)
    {
        throw std::out_of_range("DataSet::operator() instancia invalida");
    }
    if (locationIndex < 0 || locationIndex >= _nLocations)
    {
        throw std::out_of_range("DataSet::operator() ubicacion invalida");
    }

    return _values[instanceIndex][locationIndex];
}

std::ostream &operator<<(std::ostream &os, const DataSet &dataset)
{
    os << dataset.toString();
    return os;
}

std::istream &operator>>(std::istream &is, DataSet &dataset)
{
    dataset.clear();

    dataset._locations.load(is);

    int nInstances = 0;
    if (!(is >> nInstances))
    {
        dataset.clear();
        throw std::ios_base::failure("DataSet::operator>> error de lectura");
    }
    if (nInstances < 0)
    {
        dataset.clear();
        throw std::out_of_range("DataSet::operator>> instancias negativas");
    }

    dataset._labels = VectorInt(nInstances);
    for (int i = 0; i < nInstances; ++i)
    {
        int label = 0;
        if (!(is >> label))
        {
            dataset.clear();
            throw std::ios_base::failure("DataSet::operator>> error de lectura");
        }
        dataset._labels.at(i) = label;
    }

    dataset.reservar(nInstances, dataset._locations.getSize());
    for (int i = 0; i < dataset._nInstances; ++i)
    {
        for (int j = 0; j < dataset._nLocations; ++j)
        {
            int value = 0;
            if (!(is >> value))
            {
                dataset.clear();
                throw std::ios_base::failure("DataSet::operator>> error de lectura");
            }
            dataset._values[i][j] = value;
        }
    }

    return is;
}

void classify(const DataSet &datasetModel, DataSet &datasetToClassify,
        int K1, int K2, bool doReductionDimensionality)
{
    if (datasetModel.getNumLocations() != datasetToClassify.getNumLocations())
    {
        throw std::invalid_argument("classify: tamanio incompatible");
    }
    if (doReductionDimensionality && K1 <= 0)
    {
        throw std::invalid_argument("classify: K1 invalido");
    }
    if (K2 < 1)
    {
        throw std::invalid_argument("classify: K2 invalido");
    }
    if (K2 > datasetModel.getNumInstances())
    {
        throw std::invalid_argument("classify: K2 demasiado grande");
    }

    DataSet dsM(datasetModel);
    DataSet dsC(datasetToClassify);

    if (doReductionDimensionality)
    {
        Clustering clustering;
        clustering.set(dsM.getVectorLocation(), K1);
        clustering.run();

        dsM = dsM.getReducedDataSet(clustering);
        dsC = dsC.getReducedDataSet(clustering);
    }

    int numInstances = dsC.getNumInstances();
    int numLocations = dsC.getNumLocations();
    int modelInstances = dsM.getNumInstances();

    for (int i = 0; i < numInstances; ++i)
    {
        int votes[2] = {0, 0};

        bool *selected = new bool[modelInstances];
        for (int s = 0; s < modelInstances; ++s)
        {
            selected[s] = false;
        }

        VectorInt instance(numLocations);
        for (int j = 0; j < numLocations; ++j)
        {
            instance.at(j) = dsC.getValue(i, j);
        }

        for (int k = 0; k < K2; ++k)
        {
            int nearest = dsM.nearestInstance(instance, selected);
            if (nearest < 0)
            {
                break;
            }

            selected[nearest] = true;

            int label = dsM.getLabel(nearest);
            if (label == 0)
            {
                votes[0]++;
            }
            else if (label == 1)
            {
                votes[1]++;
            }
        }

        delete[] selected;

        if (votes[0] >= votes[1])
        {
            dsC.setLabel(i, 0);
        }
        else
        {
            dsC.setLabel(i, 1);
        }
    }

    for (int i = 0; i < datasetToClassify.getNumInstances(); ++i)
    {
        datasetToClassify.setLabel(i, dsC.getLabel(i));
    }
}
