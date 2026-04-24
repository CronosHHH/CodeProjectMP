/*
 * Metodología de la Programación
 * Curso 2025/2026
 *
 * main_tests.cpp — Archivo main con los 130 tests de unidad (T01 + T02)
 * generado a partir de TestReport.md
 *
 * INSTRUCCIONES:
 *   1. Reemplaza tu main.cpp por este archivo (o renómbralo a main.cpp).
 *   2. Compila igual que siempre.
 *   3. Descomenta el bloque del test que quieras probar (solo uno a la vez)
 *      y comenta el resto, luego ejecuta el programa.
 *   4. Cuando termines, restaura tu main.cpp original.
 *
 * IMPORTANTE: los tests acceden a miembros privados (_size, _values,
 * _locations, _K, _sumWCV, _numIterations, _isDone, _seed).
 * Para que compile, añade al final de cada clase en su .h la línea:
 *
 *   // ---- solo para tests ----
 *   #ifdef TESTING
 *   public:
 *   #endif
 *
 * O bien compila con:   -DTESTING
 * y añade en cada .h (VectorInt, VectorLocation, Clustering) justo antes
 * del primer miembro privado:
 *
 *   #ifdef TESTING
 *   public:
 *   #endif
 *
 * Ver sección "Cómo habilitar acceso a privados" más abajo.
 */

// ============================================================
//  Includes obligatorios para los tests
// ============================================================
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <cmath>
#include <string>

#include "VectorLocation.h"
#include "VectorInt.h"
#include "Clustering.h"
#include "ArrayClustering.h"

using namespace std;

// ============================================================
//  Macros usadas en los tests
// ============================================================
#define ENDL "\n"
#define LOCATION_DEFAULT "0.000000 0.000000"
#define LOCATION_OTHER "37.200000 -3.600000 Granada"
#define VECTOR_527 "5 7 7 7 7 7 "
#define VECTOR_DEFAULT5 "5 0 0 0 0 0 "

// ============================================================
//  inspectT() — equivale a toString() para Location
// ============================================================
// Para Location usamos directamente loc.toString().
// Los tests llaman a vloc.inspectT() / v.inspectT() / clt.inspectT()
// que NO existen en vuestra implementación; sustituidlas por toString().
// En este archivo ya están sustituidas por toString() en cada test.

// inspectT para ArrayClustering (función libre)
std::string inspectT(const ArrayClustering& ac) {
    std::string result = "capacity: " + std::to_string(ac.capacity) +
                         " size: " + std::to_string(ac.size) +
                         " List of Clusters: ";
    for (int i = 0; i < ac.size; i++) {
        result += std::regex_replace(ac.clustering[i].toString(),
                                     std::regex(ENDL), " ");
    }
    return result;
}

// ============================================================
//  Funciones auxiliares usadas en varios tests
// ============================================================

void fill_vlocation(VectorLocation& locs, int size) {
    Location loc;
    for (int i = 0; i < size; i++) {
        loc.set(i, i, string("Location") + std::to_string(i));
        locs.append(loc);
    }
}

// refill_vlocation: igual que fill_vlocation pero llama a clear() primero
void refill_vlocation(VectorLocation& locs, int size) {
    locs.clear();
    Location loc;
    for (int i = 0; i < size; i++) {
        loc.set(i, i, string("Location") + std::to_string(i));
        locs.append(loc);
    }
}

// ============================================================
//  UTILIDAD: imprime resultado y expected para comparar
// ============================================================
template<typename T>
void CHECK(const string& testName, T result, T expected) {
    cout << "[" << testName << "]" << endl;
    cout << "  Resultado : " << result << endl;
    cout << "  Esperado  : " << expected << endl;
    cout << "  => " << (result == expected ? "OK" : "FALLO") << endl << endl;
}

void CHECK_BOOL(const string& testName, bool result, bool expected) {
    cout << "[" << testName << "]" << endl;
    cout << "  Resultado : " << (result ? "true" : "false") << endl;
    cout << "  Esperado  : " << (expected ? "true" : "false") << endl;
    cout << "  => " << (result == expected ? "OK" : "FALLO") << endl << endl;
}

// Para tests que deben lanzar excepción, usar bloques try/catch inline.

// ============================================================
//  MAIN — descomenta el bloque del test que quieras probar
// ============================================================
int main(int argc, char* argv[]) {

    // Para que compile, necesitamos que los miembros privados sean accesibles.
    // Compila con -DTESTING y añade en cada .h:
    //   #ifdef TESTING
    //   public:
    //   #endif
    // antes del bloque private:

    // ===========================================================
    // T01 — Location tests (1-20)
    // ===========================================================

    // --- TEST 1: Location_Location_def1 ---
    {
        Location loc;
        string s = to_string(0.0) + string(" ") + to_string(0.0);
        CHECK("T01-1 Location_Location_def1", loc.toString(), string("0.000000 0.000000"));
    }

    // --- TEST 2: Location_get_XY ---
    {
        Location loc;
        double r = loc.getX() + loc.getY() + loc.getX() * loc.getY();
        CHECK("T01-2 Location_get_XY", r, 0.0);
    }

    // --- TEST 3: Location_getName ---
    {
        Location loc;
        CHECK("T01-3 Location_getName", loc.getName(), string(""));
    }

    // --- TEST 4: Location_set_Onelocation ---
    {
        float f1 = 37.2f; float f2 = -3.6f; string nam = "Granada";
        Location loc;
        loc.set(f1, f2, nam);
        // Nota: to_string(float) puede dar "37.200001" por precisión
        CHECK("T01-4 Location_set_Onelocation", loc.toString(), string("37.200001 -3.600000 Granada"));
    }

    // --- TEST 5: Location_set_XY ---
    {
        float f1 = 37.2f; float f2 = -3.6f;
        Location loc;
        loc.setX(f1); loc.setY(f2);
        CHECK("T01-5 Location_set_XY", loc.toString(), string("37.200001 -3.600000"));
    }

    // --- TEST 6: Location_setName ---
    {
        Location loc;
        string name = "Granada";
        loc.setName(name);
        CHECK("T01-6 Location_setName", loc.toString(), string("0.000000 0.000000 Granada"));
    }

    // --- TEST 7: Location_isInsideArea_in0 ---
    {
        float f1=37.2f, f2=-3.6f, f3=39.47f, f4=-0.37f;
        Location loc1, loc2;
        loc1.set(f1,f2,""); loc2.set(f3,f4,"");
        CHECK_BOOL("T01-7 Location_isInsideArea_in0", loc1.isInsideArea(loc1,loc2), true);
    }

    // --- TEST 8: Location_isInsideArea_in1 ---
    {
        float f1=37.2f, f2=-3.6f, f3=39.47f, f4=-0.37f;
        Location loc1, loc2;
        loc1.set(f1,f2,""); loc2.set(f3,f4,"");
        CHECK_BOOL("T01-8 Location_isInsideArea_in1", loc2.isInsideArea(loc1,loc2), true);
    }

    // --- TEST 9: Location_isInsideArea_in2 ---
    {
        float f1=37.2f, f2=-3.6f, f3=39.47f, f4=-0.37f;
        Location loc1, loc2, loc3;
        loc1.set(f1,f2,""); loc2.set(f3,f4,""); loc3.set(f1+0.2f,f2+0.2f,"");
        CHECK_BOOL("T01-9 Location_isInsideArea_in2", loc3.isInsideArea(loc1,loc2), true);
    }

    // --- TEST 10: Location_isInsideArea_out0 ---
    {
        float f1=37.2f, f2=-3.6f, f3=39.47f, f4=-0.37f;
        Location loc1, loc2, loc3;
        loc1.set(f1,f2,""); loc2.set(f3,f4,""); loc3.set(f3+0.2f,f4,"");
        CHECK_BOOL("T01-10 Location_isInsideArea_out0", loc3.isInsideArea(loc1,loc2), false);
    }

    // --- TEST 11: Location_isInsideArea_out1 ---
    {
        float f1=37.2f, f2=-3.6f, f3=39.47f, f4=-0.37f;
        Location loc1, loc2, loc3;
        loc1.set(f1,f2,""); loc2.set(f3,f4,""); loc3.set(f3,f4+0.2f,"");
        CHECK_BOOL("T01-11 Location_isInsideArea_out1", loc3.isInsideArea(loc1,loc2), false);
    }

    // --- TEST 12: Location_isInsideArea_out2 ---
    {
        float f1=37.2f, f2=-3.6f, f3=39.47f, f4=-0.37f;
        Location loc1, loc2, loc3;
        loc1.set(f1,f2,""); loc2.set(f3,f4,""); loc3.set(f1-0.2f,f2,"");
        CHECK_BOOL("T01-12 Location_isInsideArea_out2", loc3.isInsideArea(loc1,loc2), false);
    }

    // --- TEST 13: Location_isInsideArea_out3 ---
    {
        float f1=37.2f, f2=-3.6f, f3=39.47f, f4=-0.37f;
        Location loc1, loc2, loc3;
        loc1.set(f1,f2,""); loc2.set(f3,f4,""); loc3.set(f1,f2-0.2f,"");
        CHECK_BOOL("T01-13 Location_isInsideArea_out3", loc3.isInsideArea(loc1,loc2), false);
    }

    // --- TEST 14: Location_squaredDistance_l0 ---
    {
        float f1=37.2f, f2=-3.6f;
        Location loc1; loc1.set(f1,f2,"");
        CHECK("T01-14 Location_squaredDistance_l0", loc1.squaredDistance(loc1), 0.0);
    }

    // --- TEST 15: Location_squaredDistance_l1 ---
    {
        Location loc1, loc2; loc2.set(2.0,2.0,"");
        CHECK("T01-15 Location_squaredDistance_l1", loc1.squaredDistance(loc2), 8.0);
    }

    // --- TEST 16: Location_distance_l0 ---
    {
        float f1=37.2f, f2=-3.6f;
        Location loc1; loc1.set(f1,f2,"");
        CHECK("T01-16 Location_distance_l0", loc1.distance(loc1), 0.0);
    }

    // --- TEST 17: Location_distance_l1 ---
    {
        Location loc1, loc2; loc2.set(2.0,2.0,"");
        CHECK("T01-17 Location_distance_l1", loc1.distance(loc2), sqrt(8.0));
    }

    // --- TEST 18: Location_distance_l2 ---
    {
        Location loc1, loc2; loc2.set(2.0,2.0,"");
        CHECK("T01-18 Location_distance_l2", loc2.distance(loc1), sqrt(8.0));
    }

    // --- TEST 19: Location_load_0 ---
    {
        Location loc;
        const string LOCATION_OTHER_STR = "37.200000 -3.600000";
        istringstream ssin(LOCATION_OTHER_STR);
        loc.load(ssin);
        CHECK("T01-19 Location_load_0", loc.toString(), string("37.200000 -3.600000"));
    }

    // --- TEST 20: Location_load_1 ---
    {
        Location loc;
        const string LOCATION_OTHER_STR = "37.200000 -3.600000 Granada";
        istringstream ssin(LOCATION_OTHER_STR);
        loc.load(ssin);
        CHECK("T01-20 Location_load_1", loc.toString(), string("37.200000 -3.600000 Granada"));
    }

    // ===========================================================
    // T01 — VectorLocation tests (21-46)
    // ===========================================================

    // --- TEST 21: VectorLocation_getCapacity ---
    // Requiere acceso a _size y DIM_VECTOR_LOCATIONS (public o -DTESTING)
    {
        VectorLocation vloc;
        //vloc._size = 2;   // acceso directo a privado — necesita -DTESTING
        CHECK("T01-21 VectorLocation_getCapacity", vloc.getCapacity(), 100);
    }

    // --- TEST 22: VectorLocation_getCapacity2 ---
    {
        int n = 10; VectorLocation vloc(n);
        //vloc._size = 2;
        CHECK("T01-22 VectorLocation_getCapacity2", vloc.getCapacity(), 100);
    }

    // --- TEST 23: VectorLocation_Clear_1 ---
    {
        VectorLocation vloc;
        //vloc._size = VectorLocation::DIM_VECTOR_LOCATIONS;
        vloc.clear();
        CHECK("T01-23 VectorLocation_Clear_1", vloc.getSize(), 0);
    }

    // --- TEST 24: VectorLocation_VectorLocation_def3 ---
    {
        VectorLocation vloc(VectorLocation::DIM_VECTOR_LOCATIONS);
        CHECK("T01-24 VectorLocation_VectorLocation_def3", vloc.getSize(), 100);
    }

    // --- TEST 25: VectorLocation_VectorLocation_def1 ---
    {
        VectorLocation vloc;
        string result = std::regex_replace(vloc.toString(), std::regex(ENDL), " ");
        CHECK("T01-25 VectorLocation_VectorLocation_def1", result, string("0 "));
    }

    // --- TEST 26: VectorLocation_VectorLocation_def2 ---
    {
        VectorLocation vloc(1);
        string result = vloc.toString();
        result = std::regex_replace(result, std::regex(ENDL), " ");
        CHECK("T01-26 VectorLocation_VectorLocation_def2", result, string("1 0.000000 0.000000 "));
    }

    // --- TEST 27: VectorLocation_getSize0 ---
    {
        VectorLocation vloc;
        CHECK("T01-27 VectorLocation_getSize0", vloc.getSize(), 0);
    }

    // --- TEST 28: VectorLocation_getSize1 ---
    {
        VectorLocation vloc(2);
        CHECK("T01-28 VectorLocation_getSize1", vloc.getSize(), 2);
    }

    // --- TEST 29: VectorLocation_toString ---
    {
        Location loc1, loc2;
        loc2.set(37.2, -3.6, "Granada");
        VectorLocation vloc(2);
        vloc.at(0) = loc1;
        vloc.at(1) = loc2;
        string result = std::regex_replace(vloc.toString(), std::regex(ENDL), " ");
        CHECK("T01-29 VectorLocation_toString", result,
              string("2 0.000000 0.000000 37.200000 -3.600000 Granada "));
    }

    // --- TEST 30: VectorLocation_Clear_0 ---
    {
        VectorLocation vloc;
        vloc.clear();
        CHECK("T01-30 VectorLocation_Clear_0", vloc.getSize(), 0);
    }

    // --- TEST 31: VectorLocation_append_0 ---
    {
        Location loc; loc.set(37.2, -3.6, "Granada");
        VectorLocation vloc;
        vloc.append(loc);
        string result = std::regex_replace(vloc.toString(), std::regex(ENDL), " ");
        CHECK("T01-31 VectorLocation_append_0", result, string("1 37.200000 -3.600000 Granada "));
    }

    // --- TEST 32: VectorLocation_append_1 ---
    {
        Location loc1, loc2; loc2.set(37.2, -3.6, "Granada");
        VectorLocation vloc;
        vloc.append(loc1); vloc.append(loc2);
        string result = std::regex_replace(vloc.toString(), std::regex(ENDL), " ");
        CHECK("T01-32 VectorLocation_append_1", result,
              string("2 0.000000 0.000000 37.200000 -3.600000 Granada "));
    }

    // --- TEST 33: VectorLocation_at_0 ---
    {
        VectorLocation vloc(2);
        CHECK("T01-33 VectorLocation_at_0", vloc.at(0).toString(), string("0.000000 0.000000"));
    }

    // --- TEST 34: VectorLocation_at_1 ---
    {
        VectorLocation vloc(2);
        CHECK("T01-34 VectorLocation_at_1", vloc.at(1).toString(), string("0.000000 0.000000"));
    }

    // --- TEST 35: VectorLocation_at_2 ---
    {
        Location loc; VectorLocation vloc(2);
        loc.set(37.2, -3.6, "Granada"); vloc.at(0) = loc;
        CHECK("T01-35 VectorLocation_at_2", vloc.at(0).toString(), string("37.200000 -3.600000 Granada"));
    }

    // --- TEST 36: VectorLocation_at_3 ---
    {
        Location loc; VectorLocation vloc(2);
        loc.set(37.2, -3.6, "Granada"); vloc.at(1) = loc;
        CHECK("T01-36 VectorLocation_at_3", vloc.at(1).toString(), string("37.200000 -3.600000 Granada"));
    }

    // --- TEST 37: VectorLocation_findLocation_0 ---
    {
        Location loc; VectorLocation vloc;
        CHECK("T01-37 VectorLocation_findLocation_0", vloc.findLocation(loc), -1);
    }

    // --- TEST 38: VectorLocation_findLocation_1 ---
    {
        Location loc1, loc2; loc2.set(37.2, -3.6, "Granada");
        VectorLocation vloc(2);
        vloc.at(0) = loc2;
        CHECK("T01-38 VectorLocation_findLocation_1", vloc.findLocation(loc2), 0);
    }

    // --- TEST 39: VectorLocation_findLocation_2 ---
    {
        Location loc1, loc2; loc2.set(37.2, -3.6, "Granada");
        VectorLocation vloc(2);
        vloc.at(1) = loc2;
        CHECK("T01-39 VectorLocation_findLocation_2", vloc.findLocation(loc2), 1);
    }

    // --- TEST 40: VectorLocation_findLocation_3 ---
    {
        Location loc; loc.setName("OTHER");
        VectorLocation vloc(5);
        CHECK("T01-40 VectorLocation_findLocation_3", vloc.findLocation(loc), -1);
    }

    // --- TEST 41: VectorLocation_nearest_0 ---
    {
        Location loc0; loc0.set(1,1,"1");
        VectorLocation l1;
        CHECK("T01-41 VectorLocation_nearest_0", l1.nearest(loc0), -1);
    }

    // --- TEST 42: VectorLocation_nearest_1 ---
    {
        int n = 5; Location loc1; loc1.set(0.0,0.0,"1");
        VectorLocation l1(n);
        for (int i = 0; i < n; i++) { l1.at(i).set(i,i,std::to_string(i)); }
        CHECK("T01-42 VectorLocation_nearest_1", l1.nearest(loc1), 0);
    }

    // --- TEST 43: VectorLocation_nearest_2 ---
    {
        int n = 5; Location loc1; loc1.set(0.0,0.0,"1");
        VectorLocation l1(n);
        for (int i = 0; i < n; i++) { l1.at(n-(i+1)).set(i,i,std::to_string(i)); }
        CHECK("T01-43 VectorLocation_nearest_2", l1.nearest(loc1), 4);
    }

    // --- TEST 44: VectorLocation_loadFromFile_0 ---
    {
        int n = 5; VectorLocation l1(n), l2; Location loc;
        for (int i = 0; i < n; i++) { loc.set(i,i,std::to_string(i)); l1.at(i) = loc; }
        const char* fileName = "test_save1.loc";
        ifstream fi; ofstream fo;
        fo.open(fileName); fo << l1.toString(); fo.close();
        fi.open(fileName); l2.load(fi); fi.close();
        string result = std::regex_replace(l2.toString(), std::regex(ENDL), " ");
        CHECK("T01-44 VectorLocation_loadFromFile_0", result,
              string("5 0.000000 0.000000 0 1.000000 1.000000 1 2.000000 2.000000 2 3.000000 3.000000 3 4.000000 4.000000 4 "));
    }

    // --- TEST 45: VectorLocation_loadFromCin_1 ---
    {
        int n = 1; VectorLocation l1(n);
        string ss = std::string("1 ") + string(LOCATION_OTHER) + " ";
        istringstream ssin(ss);
        l1.load(ssin);
        string result = std::regex_replace(l1.toString(), std::regex(ENDL), " ");
        CHECK("T01-45 VectorLocation_loadFromCin_1", result,
              string("1 37.200000 -3.600000 Granada "));
    }

    // --- TEST 46: VectorLocation_loadEmptyName_4 ---
    {
        int n = 1; VectorLocation l1(n);
        string ss = std::string("1 ") + string(LOCATION_DEFAULT) + " ";
        istringstream ssin(ss);
        l1.load(ssin); l1.load(ssin);
        string result = std::regex_replace(l1.toString(), std::regex(ENDL), " ");
        CHECK("T01-46 VectorLocation_loadEmptyName_4", result,
              string("1 0.000000 0.000000 "));
    }

    // ===========================================================
    // T01 — VectorInt tests (47-63)
    // ===========================================================

    // --- TEST 47: VectorInt_VectorInt_getCapacity ---
    {
        VectorInt v; //v._size = 2;
        CHECK("T01-47 VectorInt_getCapacity", v.getCapacity(), 100);
    }

    // --- TEST 48: VectorInt_VectorInt_def0 ---
    {
        VectorInt v;
        CHECK("T01-48 VectorInt_def0", v.getSize(), 0);
    }

    // --- TEST 49: VectorInt_VectorInt_def1 ---
    {
        VectorInt v(5);
        CHECK("T01-49 VectorInt_def1", v.getSize(), 5);
    }

    // --- TEST 50: VectorInt_getSize ---
    {
        VectorInt v(5);
        CHECK("T01-50 VectorInt_getSize", v.getSize(), 5);
    }

    // --- TEST 51: VectorInt_assign ---
    {
        VectorInt v(4); v.assign(7);
        string result = std::regex_replace(v.toString(), std::regex(ENDL), " ");
        CHECK("T01-51 VectorInt_assign", result, string("4 7 7 7 7 "));
    }

    // --- TEST 52: VectorInt_append_0 ---
    {
        VectorInt v(2); v.append(7);
        CHECK("T01-52 VectorInt_append_0", v.getSize(), 3);
    }

    // --- TEST 53: VectorInt_append_1 ---
    {
        VectorInt v(2); v.append(7);
        CHECK("T01-53 VectorInt_append_1", v.at(2), 7);
    }

    // --- TEST 54: VectorInt_clear ---
    {
        VectorInt v(5); v.clear();
        CHECK("T01-54 VectorInt_clear", v.getSize(), 0);
    }

    // --- TEST 55: VectorInt_at_0 ---
    {
        VectorInt v(2); v.at(0) = 7;
        CHECK("T01-55 VectorInt_at_0", v.at(0), 7);
    }

    // --- TEST 56: VectorInt_at_1 ---
    {
        VectorInt v(2); v.at(1) = 7;
        CHECK("T01-56 VectorInt_at_1", v.at(1), 7);
    }

    // --- TEST 57: VectorInt_at_2 ---
    {
        VectorInt v(2); v.at(1) = 7;
        string result = std::regex_replace(v.toString(), std::regex(ENDL), " ");
        CHECK("T01-57 VectorInt_at_2", result, string("2 0 7 "));
    }

    // --- TEST 58: VectorInt_toString1 ---
    {
        VectorInt v(5);
        string result = std::regex_replace(v.toString(), std::regex(ENDL), " ");
        CHECK("T01-58 VectorInt_toString1", result, string("5 0 0 0 0 0 "));
    }

    // --- TEST 59: VectorInt_toString2 ---
    {
        VectorInt v(5); v.assign(7);
        string result = std::regex_replace(v.toString(), std::regex(ENDL), " ");
        CHECK("T01-59 VectorInt_toString2", result, string("5 7 7 7 7 7 "));
    }

    // --- TEST 60: VectorInt_distance0 ---
    {
        VectorInt v1(3), v2(3);
        for (int i = 0; i < 3; i++) { v1.at(i) = i+1; v2.at(i) = i+1; }
        CHECK("T01-60 VectorInt_distance0", v1.distance(v2), 0.0);
    }

    // --- TEST 61: VectorInt_distance1 ---
    {
        VectorInt v1(3), v2(3);
        for (int i = 0; i < 3; i++) { v1.at(i) = i+1; v2.at(i) = i+1; }
        v2.at(2) = 6;
        CHECK("T01-61 VectorInt_distance1", v1.distance(v2), 3.0);
    }

    // --- TEST 62: VectorInt_countIdenticalElements0 ---
    {
        VectorInt v1(3), v2(3);
        CHECK("T01-62 VectorInt_countIdenticalElements0", v1.countIdenticalElements(v2), 3);
    }

    // --- TEST 63: VectorInt_countIdenticalElements1 ---
    {
        VectorInt v1(3), v2(3);
        for (int i = 0; i < 3; i++) { v1.at(i) = 5; v2.at(i) = 5; }
        v2.at(0) = 1;
        CHECK("T01-63 VectorInt_countIdenticalElements1", v1.countIdenticalElements(v2), 2);
    }

    // ===========================================================
    // T01 — Clustering tests (64-75)
    // ===========================================================

    // --- TEST 64: Clustering_Clustering_def0 ---
    {
        Clustering clt;
        double r = clt.getK() + clt.isDone() + clt.getNumIterations() + clt.getSumWCV();
        CHECK("T01-64 Clustering_def0", r, 0.0);
    }

    // --- TEST 65: Clustering_Clustering_def1 ---
    {
        Clustering clt;
        //CHECK("T01-65 Clustering_def1", (unsigned)clt._seed, 1761560597U);
    }

    // --- TEST 66: Clustering_Clustering_def2 ---
    {
        VectorLocation locations; fill_vlocation(locations, 3);
        Clustering clt; clt.set(locations, 2, 12345);
        string result = std::regex_replace(clt.toString(), std::regex(ENDL), " ");
        string expected = "K=2 Sum of within-cluster variances: 0.000000 Number of iterations: 0 Cluster number for each location: 3 0 0 0  Centroids: 2 0.000000 0.000000  0.000000 0.000000   Cluster 0 information:  Cluster 1 information:  ";
        CHECK("T01-66 Clustering_def2", result, expected);
    }

    // --- TEST 67: Clustering_Clustering_gets_5functions ---
    {
        VectorLocation locations; fill_vlocation(locations, 5);
        Clustering clt; clt.set(locations, 3, 12345);
        string result = std::to_string(clt.getK()) + " " +
                        std::to_string(clt.getNumLocations()) + " " +
                        std::to_string(clt.getCentroids().getSize()) + " " +
                        std::to_string(clt.getSumWCV()) + " " +
                        std::to_string(clt.getNumIterations());
        CHECK("T01-67 Clustering_gets_5functions", result, string("3 5 3 0.000000 0"));
    }

    // --- TEST 68: Clustering_clusterOf_BeforeRun ---
    {
        VectorLocation locations; fill_vlocation(locations, 3);
        Clustering clt; clt.set(locations, 2, 12345);
        CHECK("T01-68 Clustering_clusterOf_BeforeRun", clt.clusterOf(1), -1);
    }

    // --- TEST 69: Clustering_getSumWCV_BeforeRun ---
    {
        VectorLocation locations; fill_vlocation(locations, 3);
        Clustering clt; clt.set(locations, 2, 12345);
        CHECK("T01-69 Clustering_getSumWCV_BeforeRun", clt.getSumWCV(), 0.0);
    }

    // --- TEST 70: Clustering_clusterInfo2_InvalidCluster ---
    {
        VectorLocation locations; fill_vlocation(locations, 3);
        Clustering clt; clt.set(locations, 2, 12345);
        string result = std::regex_replace(clt.clusterInfo(2), std::regex(ENDL), " ");
        CHECK("T01-70 Clustering_clusterInfo2_InvalidCluster", result, string(""));
    }

    // --- TEST 71: Clustering_isEquivalentTo_1 ---
    {
        VectorLocation locations; fill_vlocation(locations, 3);
        Clustering clt1, clt2;
        clt1.set(locations, 2, 12345); clt2.set(locations, 2, 12345);
        clt1.run(); clt2.run();
        CHECK_BOOL("T01-71 Clustering_isEquivalentTo_1", clt1.isEquivalentTo(clt2), true);
    }

    // --- TEST 72: Clustering_isEquivalentTo_2 ---
    {
        VectorLocation locations; fill_vlocation(locations, 3);
        Clustering clt1, clt2;
        clt1.set(locations, 2, 12345); clt2.set(locations, 2, 12345);
        clt1.run();
        CHECK_BOOL("T01-72 Clustering_isEquivalentTo_2", clt1.isEquivalentTo(clt2), false);
    }

    // --- TEST 73: Clustering_toString ---
    {
        VectorLocation locations; fill_vlocation(locations, 3);
        Clustering clt; clt.set(locations, 2, 12345);
        string result = std::regex_replace(clt.toString(), std::regex(ENDL), " ");
        string expected = "K=2 Sum of within-cluster variances: 0.000000 Number of iterations: 0 Cluster number for each location: 3 0 0 0  Centroids: 2 0.000000 0.000000  0.000000 0.000000   Cluster 0 information:  Cluster 1 information:  ";
        CHECK("T01-73 Clustering_toString", result, expected);
    }

    // --- TEST 74: Clustering_set ---
    {
        VectorLocation locations; fill_vlocation(locations, 3);
        Clustering clt; clt.set(locations, 2, 12345);
        string result = std::regex_replace(clt.toString(), std::regex(ENDL), " ");
        string expected = "K=2 Sum of within-cluster variances: 0.000000 Number of iterations: 0 Cluster number for each location: 3 0 0 0  Centroids: 2 0.000000 0.000000  0.000000 0.000000   Cluster 0 information:  Cluster 1 information:  ";
        CHECK("T01-74 Clustering_set", result, expected);
    }

    // --- TEST 75: Clustering_set_InvalidK (excepción) ---
    {
        cout << "[T01-75 Clustering_set_InvalidK]" << endl;
        VectorLocation locations; fill_vlocation(locations, 3);
        Clustering clt;
        try {
            clt.set(locations, 0, 12345);
            cout << "  => FALLO (no lanzó excepción)" << endl;
        } catch (const std::invalid_argument& e) {
            cout << "  => OK (lanzó std::invalid_argument: " << e.what() << ")" << endl;
        }
        cout << endl;
    }

    // ===========================================================
    // T01 — ArrayClustering tests (76-89)
    // ===========================================================

    // --- TEST 76: ArrayClustering_Initialize_0 ---
    {
        ArrayClustering arrayClt;
        InitializeArrayClustering(arrayClt);
        string result = inspectT(arrayClt);
        DeallocateArrayClustering(arrayClt);
        CHECK("T01-76 ArrayClustering_Initialize_0", result,
              string("capacity: 2 size: 0 List of Clusters: "));
    }

    // --- TEST 77: ArrayClustering_Initialize_1 ---
    {
        ArrayClustering arrayClt;
        InitializeArrayClustering(arrayClt, 1);
        string result = inspectT(arrayClt);
        DeallocateArrayClustering(arrayClt);
        CHECK("T01-77 ArrayClustering_Initialize_1", result,
              string("capacity: 1 size: 0 List of Clusters: "));
    }

    // --- TEST 78: ArrayClustering_findClustering_1 ---
    {
        Clustering clt; ArrayClustering arrayClt;
        arrayClt.clustering = nullptr; arrayClt.capacity = 0; arrayClt.size = 0;
        CHECK("T01-78 ArrayClustering_findClustering_1", FindArrayClustering(arrayClt, clt), -1);
    }

    // --- TEST 79: ArrayClustering_findClustering_2 ---
    {
        VectorLocation locations; refill_vlocation(locations, 3);
        Clustering clt2; clt2.set(locations, 3, 12345);
        //clt2._numIterations = 11; clt2._sumWCV = 1.2; clt2._isDone = true;
        ArrayClustering arrayClt; InitializeArrayClustering(arrayClt);
        arrayClt.size = 2;
        //arrayClt.clustering[0]._K = 3; arrayClt.clustering[0]._numIterations = 11;
        //arrayClt.clustering[0]._sumWCV = 1.2; arrayClt.clustering[0]._isDone = true;
        CHECK("T01-79 ArrayClustering_findClustering_2", FindArrayClustering(arrayClt, clt2), 0);
        DeallocateArrayClustering(arrayClt);
    }

    // --- TEST 80: ArrayClustering_findClustering_3 ---
    {
        VectorLocation locations; refill_vlocation(locations, 3);
        Clustering clt2; clt2.set(locations, 3, 12345);
        //clt2._numIterations = 11; clt2._sumWCV = 1.2; clt2._isDone = true;
        ArrayClustering arrayClt; InitializeArrayClustering(arrayClt);
        arrayClt.size = 2;
        //arrayClt.clustering[1]._K = 3; arrayClt.clustering[1]._numIterations = 11;
        //arrayClt.clustering[1]._sumWCV = 1.2; arrayClt.clustering[1]._isDone = true;
        CHECK("T01-80 ArrayClustering_findClustering_3", FindArrayClustering(arrayClt, clt2), 1);
        DeallocateArrayClustering(arrayClt);
    }

    // --- TEST 81: ArrayClustering_findClustering_4_diff_sumWCV ---
    {
        VectorLocation locations; refill_vlocation(locations, 3);
        Clustering clt2; clt2.set(locations, 3, 12345);
        //clt2._numIterations = 11; clt2._sumWCV = 1.3; clt2._isDone = true;
        ArrayClustering arrayClt; InitializeArrayClustering(arrayClt, 3);
        arrayClt.size = 3;
        //arrayClt.clustering[1]._K = 3; arrayClt.clustering[1]._numIterations = 11;
        //arrayClt.clustering[1]._sumWCV = 1.2; arrayClt.clustering[1]._isDone = true;
        CHECK("T01-81 ArrayClustering_findClustering_4", FindArrayClustering(arrayClt, clt2), -1);
        DeallocateArrayClustering(arrayClt);
    }

    // --- TEST 82: ArrayClustering_findClustering_5_diff_iteration ---
    {
        VectorLocation locations; refill_vlocation(locations, 3);
        Clustering clt2; clt2.set(locations, 3, 12345);
        //clt2._numIterations = 11; clt2._sumWCV = 1.3; clt2._isDone = true;
        ArrayClustering arrayClt; InitializeArrayClustering(arrayClt, 3);
        arrayClt.size = 3;
        //arrayClt.clustering[1]._K = 3; arrayClt.clustering[1]._numIterations = 13;
        //arrayClt.clustering[1]._sumWCV = 1.2; arrayClt.clustering[1]._isDone = true;
        CHECK("T01-82 ArrayClustering_findClustering_5", FindArrayClustering(arrayClt, clt2), -1);
        DeallocateArrayClustering(arrayClt);
    }

    // --- TEST 83: ArrayClustering_findClustering_6_diff_K ---
    {
        VectorLocation locations; refill_vlocation(locations, 3);
        Clustering clt2; clt2.set(locations, 3, 12345);
        //clt2._numIterations = 11; clt2._sumWCV = 1.3; clt2._isDone = true;
        ArrayClustering arrayClt; InitializeArrayClustering(arrayClt, 3);
        arrayClt.size = 3;
        //arrayClt.clustering[1]._K = 4; arrayClt.clustering[1]._numIterations = 11;
        //arrayClt.clustering[1]._sumWCV = 1.2; arrayClt.clustering[1]._isDone = true;
        CHECK("T01-83 ArrayClustering_findClustering_6", FindArrayClustering(arrayClt, clt2), -1);
        DeallocateArrayClustering(arrayClt);
    }

    // --- TEST 84: ArrayClustering_append_0 ---
    {
        VectorLocation locations; refill_vlocation(locations, 3);
        Clustering clt1; clt1.set(locations, 2, 12345);
        //clt1._numIterations = 11; clt1._sumWCV = 1.3; clt1._isDone = true;
        ArrayClustering arrayClt; InitializeArrayClustering(arrayClt, 3);
        AppendArrayClustering(arrayClt, clt1);
        string result = std::to_string(arrayClt.capacity) + " " + std::to_string(arrayClt.size);
        DeallocateArrayClustering(arrayClt);
        CHECK("T01-84 ArrayClustering_append_0", result, string("3 1"));
    }

    // --- TEST 85: ArrayClustering_append_1 ---
    {
        VectorLocation locations; refill_vlocation(locations, 3);
        Clustering clt1; clt1.set(locations, 2, 12345);
        ArrayClustering arrayClt; InitializeArrayClustering(arrayClt, 3);
        arrayClt.size = 2;
        AppendArrayClustering(arrayClt, clt1);
        string result = std::to_string(arrayClt.capacity) + " " + std::to_string(arrayClt.size);
        DeallocateArrayClustering(arrayClt);
        CHECK("T01-85 ArrayClustering_append_1", result, string("3 3"));
    }

    // --- TEST 86: ArrayClustering_append_2 ---
    {
        VectorLocation locations; refill_vlocation(locations, 3);
        Clustering clt1; clt1.set(locations, 2, 12345);
        ArrayClustering arrayClt; InitializeArrayClustering(arrayClt);
        arrayClt.size = 2;
        AppendArrayClustering(arrayClt, clt1);
        string result = std::to_string(arrayClt.capacity) + " " + std::to_string(arrayClt.size);
        DeallocateArrayClustering(arrayClt);
        CHECK("T01-86 ArrayClustering_append_2", result, string("4 3"));
    }

    // --- TEST 87: ArrayClustering_sort_1_no_change ---
    {
        ArrayClustering arrayClt; InitializeArrayClustering(arrayClt, 5);
        arrayClt.size = 5;
        for (int i = 0; i < arrayClt.size; i++) {
            arrayClt.clustering[i]._K = 2;
            arrayClt.clustering[i]._sumWCV = 1.0 + i;
            arrayClt.clustering[i]._numIterations = 10;
            arrayClt.clustering[i]._isDone = true;
        }
        SortArrayClustering(arrayClt);
        string result = inspectT(arrayClt);
        DeallocateArrayClustering(arrayClt);
        string expected = "capacity: 5 size: 5 List of Clusters: "
            "K=2 Sum of within-cluster variances: 1.000000 Number of iterations: 10 Cluster number for each location: 0 Centroids: 0 Cluster 0 information: Cluster 1 information: "
            "K=2 Sum of within-cluster variances: 2.000000 Number of iterations: 10 Cluster number for each location: 0 Centroids: 0 Cluster 0 information: Cluster 1 information: "
            "K=2 Sum of within-cluster variances: 3.000000 Number of iterations: 10 Cluster number for each location: 0 Centroids: 0 Cluster 0 information: Cluster 1 information: "
            "K=2 Sum of within-cluster variances: 4.000000 Number of iterations: 10 Cluster number for each location: 0 Centroids: 0 Cluster 0 information: Cluster 1 information: "
            "K=2 Sum of within-cluster variances: 5.000000 Number of iterations: 10 Cluster number for each location: 0 Centroids: 0 Cluster 0 information: Cluster 1 information: ";
        CHECK("T01-87 ArrayClustering_sort_1_no_change", result, expected);
    }

    // --- TEST 88: ArrayClustering_Deallocate_0 ---
    {
        ArrayClustering arrayClt;
        arrayClt.clustering = nullptr;
        arrayClt.capacity = 0;
        arrayClt.size = 0;
        DeallocateArrayClustering(arrayClt);
        CHECK("T01-88 ArrayClustering_Deallocate_0", arrayClt.capacity + arrayClt.size, 0);
    }

    // --- TEST 89: ArrayClustering_Deallocate_1 ---
    {
        ArrayClustering arrayClt; InitializeArrayClustering(arrayClt, 5);
        arrayClt.size = 5;
        DeallocateArrayClustering(arrayClt);
        CHECK("T01-89 ArrayClustering_Deallocate_1", arrayClt.capacity + arrayClt.size, 0);
    }

    // ===========================================================
    // T02 — Intermediate tests (90-130)
    // ===========================================================

    // --- TEST 90: VectorLocation_VectorLocation_def4 (excepción) ---
    {
        cout << "[T02-90 VectorLocation_VectorLocation_def4]" << endl;
        try {
            VectorLocation vloc(VectorLocation::DIM_VECTOR_LOCATIONS + 1);
            cout << "  => FALLO (no lanzó excepción)" << endl;
        } catch (const std::out_of_range& e) {
            cout << "  => OK (lanzó std::out_of_range: " << e.what() << ")" << endl;
        }
        cout << endl;
    }

    // --- TEST 91: VectorLocation_findLocation_4 ---
    {
        Location loc; loc.setName("OTHER");
        VectorLocation vloc(VectorLocation::DIM_VECTOR_LOCATIONS);
        vloc.at(VectorLocation::DIM_VECTOR_LOCATIONS - 1) = loc;
        CHECK("T02-91 VectorLocation_findLocation_4", vloc.findLocation(loc), 99);
    }

    // --- TEST 92: VectorLocation_out_of_range_append_4 ---
    {
        Location loc; loc.set(37.2, -3.6, "Granada");
        VectorLocation vloc(VectorLocation::DIM_VECTOR_LOCATIONS);
        vloc.append(loc);  // ya lleno — debe ignorar (no lanzar)
        CHECK("T02-92 VectorLocation_out_of_range_append_4", vloc.getSize(), 100);
    }

    // --- TEST 93: VectorLocation_out_of_range_append_5 (excepción) ---
    {
        cout << "[T02-93 VectorLocation_out_of_range_append_5]" << endl;
        Location loc; loc.set(0, 0, "Terrace");
        VectorLocation vloc;
        for (int i = 0; i < VectorLocation::DIM_VECTOR_LOCATIONS; i++) { vloc.append(loc); }
        try {
            vloc.append(loc);
            cout << "  => FALLO (no lanzó excepción)" << endl;
        } catch (const std::out_of_range& e) {
            cout << "  => OK (lanzó std::out_of_range: " << e.what() << ")" << endl;
        }
        cout << endl;
    }

    // --- TEST 94: VectorLocation_Load_4_exception (excepción) ---
    {
        cout << "[T02-94 VectorLocation_Load_4_exception]" << endl;
        int n = 1; VectorLocation l1(n);
        std::string sin = std::to_string(VectorLocation::DIM_VECTOR_LOCATIONS + 1);
        istringstream ssin(sin);
        try {
            l1.load(ssin);
            cout << "  => FALLO (no lanzó excepción)" << endl;
        } catch (const std::out_of_range& e) {
            cout << "  => OK (lanzó std::out_of_range: " << e.what() << ")" << endl;
        }
        cout << endl;
    }

    // --- TEST 95: VectorLocation_VectorLocation_def5 (excepción) ---
    {
        cout << "[T02-95 VectorLocation_VectorLocation_def5]" << endl;
        try {
            VectorLocation vloc(-1);
            cout << "  => FALLO (no lanzó excepción)" << endl;
        } catch (const std::out_of_range& e) {
            cout << "  => OK (lanzó std::out_of_range: " << e.what() << ")" << endl;
        }
        cout << endl;
    }

    // --- TEST 96: VectorLocation_append_2 (duplicado se ignora) ---
    {
        Location loc; loc.set(37.2, -3.6, "Granada");
        VectorLocation vloc;
        vloc.append(loc); vloc.append(loc);
        string result = std::regex_replace(vloc.toString(), std::regex(ENDL), " ");
        CHECK("T02-96 VectorLocation_append_2", result, string("1 37.200000 -3.600000 Granada "));
    }

    // --- TEST 97: VectorLocation_at_exception0 (excepción) ---
    {
        cout << "[T02-97 VectorLocation_at_exception0]" << endl;
        VectorLocation vloc(2);
        try {
            vloc.at(-1);
            cout << "  => FALLO (no lanzó excepción)" << endl;
        } catch (const std::out_of_range& e) {
            cout << "  => OK (lanzó std::out_of_range: " << e.what() << ")" << endl;
        }
        cout << endl;
    }

    // --- TEST 98: VectorLocation_at_exception1 (excepción) ---
    {
        cout << "[T02-98 VectorLocation_at_exception1]" << endl;
        VectorLocation vloc(2);
        try {
            vloc.at(2);
            cout << "  => FALLO (no lanzó excepción)" << endl;
        } catch (const std::out_of_range& e) {
            cout << "  => OK (lanzó std::out_of_range: " << e.what() << ")" << endl;
        }
        cout << endl;
    }

    // --- TEST 99: VectorLocation_select_0 ---
    {
        int n = 5; Location loc0, loc1, loc2;
        loc1.set(1,1,"1"); loc2.set(n,n,std::to_string(n));
        VectorLocation l1(n), l2;
        for (int i = 1; i <= n; i++) { l1.at(i-1).set(-i, i, std::to_string(i)); }
        l2 = l1.select(loc0, loc2);
        CHECK("T02-99 VectorLocation_select_0", l2.getSize(), 0);
    }

    // --- TEST 100: VectorLocation_select_1 ---
    {
        int sizeOriginal = 5; Location loc1, loc2;
        loc2.set(sizeOriginal, sizeOriginal, std::to_string(sizeOriginal));
        VectorLocation l1(sizeOriginal), l2;
        for (int i = 1; i <= sizeOriginal; i++) { l1.at(i-1).set(i, i, std::to_string(i)); }
        l2 = l1.select(loc1, loc2);
        CHECK("T02-100 VectorLocation_select_1", l2.getSize(), 5);
    }

    // --- TEST 101: VectorLocation_select_2 ---
    {
        int n = 5; Location loc0, loc1, loc2;
        loc1.set(1.0,1.0,"1"); loc2.set(n,n,std::to_string(n));
        VectorLocation l1(n+1), l2;
        for (int i = 0; i <= n; i++) { l1.at(i).set(i*(n+1), i*(n+1), std::to_string(i)); }
        l2 = l1.select(loc0, loc2);
        CHECK("T02-101 VectorLocation_select_2", l2.getSize(), 1);
    }

    // --- TEST 102: VectorLocation_select_3 ---
    {
        int n = 5; Location loc0, loc1, loc2;
        loc0.set(0,0,"0"); loc1.set(1,1,"1"); loc2.set(n,n,std::to_string(n));
        VectorLocation l1(n+1), l2;
        for (int i = 0; i <= n; i++) { l1.at(i).set(i*(n+1), i*(n+1), std::to_string(i)); }
        l2 = l1.select(loc0, loc2);
        string result = std::regex_replace(l2.toString(), std::regex(ENDL), " ");
        CHECK("T02-102 VectorLocation_select_3", result, string("1 0.000000 0.000000 0 "));
    }

    // --- TEST 103: VectorLocation_select_4 ---
    {
        int sizeOriginal = 5; Location loc1, loc2;
        loc1.set(1,1,"1"); loc2.set(sizeOriginal,sizeOriginal,std::to_string(sizeOriginal));
        VectorLocation l1(sizeOriginal), l2;
        for (int i = 1; i <= sizeOriginal; i++) { l1.at(i-1).set(i, i, std::to_string(i)); }
        l2 = l1.select(loc1, loc2);
        string result = std::regex_replace(l2.toString(), std::regex(ENDL), " ");
        CHECK("T02-103 VectorLocation_select_4", result,
              string("5 1.000000 1.000000 1 2.000000 2.000000 2 3.000000 3.000000 3 4.000000 4.000000 4 5.000000 5.000000 5 "));
    }

    // --- TEST 104: VectorLocation_sort_1_no_change ---
    {
        int sizeOriginal = 3; Location loc; VectorLocation l1(sizeOriginal), sol;
        for (int i = 0; i < sizeOriginal; i++) {
            loc.setName(std::to_string(i));
            l1.at(i) = loc;
            sol.append(loc);
        }
        l1.sort();
        CHECK_BOOL("T02-104 VectorLocation_sort_1_no_change", sol.toString() == l1.toString(), true);
    }

    // --- TEST 105: VectorLocation_sort_2 ---
    {
        int sizeOriginal = 3; Location loc; VectorLocation l1(sizeOriginal), sol;
        for (int i = 0; i < sizeOriginal; i++) {
            loc.setName(std::to_string(i));
            l1.at(sizeOriginal-(i+1)) = loc;
            sol.append(loc);
        }
        l1.sort();
        CHECK_BOOL("T02-105 VectorLocation_sort_2", sol.toString() == l1.toString(), true);
    }

    // --- TEST 106: VectorLocation_join_intersection_empty_0 ---
    {
        int n = 5; VectorLocation l1(n), l2(n);
        for (int i = 0; i < n; i++) {
            l1.at(i).set(i, i, std::to_string(i));
            l2.at(i).set((i+1)*n, (i+1)*n, std::to_string((i+1)*n));
        }
        l1.join(l2);
        CHECK("T02-106 VectorLocation_join_intersection_empty_0", l1.getSize(), 10);
    }

    // --- TEST 107: VectorLocation_joinShouldRemainEqual_1 ---
    {
        int n = 5; VectorLocation l1(n), l2(n);
        for (int i = 0; i < n; i++) {
            l1.at(i).set(i, i, std::to_string(i));
            l2.at(i).set(i, i, std::to_string(i));
        }
        l1.join(l2);
        CHECK("T02-107 VectorLocation_joinShouldRemainEqual_1", l1.getSize(), 5);
    }

    // --- TEST 108: VectorLocation_joinShouldRemainEqual_2 ---
    {
        VectorLocation l1(1), l2(1);
        l1.at(0).set(37.2, -3.6, "Granada");
        l2.at(0).set(37.2, -3.6, "Granada");
        l1.join(l2);
        string result = std::regex_replace(l1.toString(), std::regex(ENDL), " ");
        CHECK("T02-108 VectorLocation_joinShouldRemainEqual_2", result,
              string("1 37.200000 -3.600000 Granada "));
    }

    // --- TEST 109: VectorLocation_assign_01 ---
    {
        int n = 5; Location loc; loc.set(37.2, -3.6, "Granada");
        VectorLocation l2(n);
        l2.assign(loc);
        string result = std::regex_replace(l2.toString(), std::regex(ENDL), " ");
        CHECK("T02-109 VectorLocation_assign_01", result,
              string("5 37.200000 -3.600000 Granada 37.200000 -3.600000 Granada 37.200000 -3.600000 Granada 37.200000 -3.600000 Granada 37.200000 -3.600000 Granada "));
    }

    // --- TEST 110: VectorLocation_assign_02 ---
    {
        int n = 5; Location loc0, loc1; loc1.set(37.2, -3.6, "Granada");
        VectorLocation l2(n);
        for (int i = 0; i < 5; i++) { l2.at(i) = loc1; }
        l2.assign(loc0);
        string result = std::regex_replace(l2.toString(), std::regex(ENDL), " ");
        CHECK("T02-110 VectorLocation_assign_02", result,
              string("5 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 "));
    }

    // --- TEST 111: VectorLocation_loadLoad_2 ---
    {
        int n = 1; VectorLocation l1(n);
        string ss = std::string("1 ") + string(LOCATION_OTHER) + " ";
        istringstream ssin(ss);
        l1.load(ssin);
        ssin.clear(); ssin.str(ss);
        l1.load(ssin);
        string result = std::regex_replace(l1.toString(), std::regex(ENDL), " ");
        CHECK("T02-111 VectorLocation_loadLoad_2", result, string("1 37.200000 -3.600000 Granada "));
    }

    // --- TEST 112: VectorLocation_Load_3_exception (excepción) ---
    {
        cout << "[T02-112 VectorLocation_Load_3_exception]" << endl;
        int n = 1; VectorLocation l1(n);
        string ss = std::string("-1 ") + string(LOCATION_OTHER) + " ";
        istringstream ssin(ss);
        try {
            l1.load(ssin);
            cout << "  => FALLO (no lanzó excepción)" << endl;
        } catch (const std::out_of_range& e) {
            cout << "  => OK (lanzó std::out_of_range: " << e.what() << ")" << endl;
        }
        cout << endl;
    }

    // --- TEST 113: VectorInt_VectorInt_def3 (excepción) ---
    {
        cout << "[T02-113 VectorInt_VectorInt_def3]" << endl;
        try {
            VectorInt v(VectorInt::DIM_VECTOR_VALUES + 1);
            cout << "  => FALLO (no lanzó excepción)" << endl;
        } catch (const std::out_of_range& e) {
            cout << "  => OK (lanzó std::out_of_range: " << e.what() << ")" << endl;
        }
        cout << endl;
    }

    // --- TEST 114: VectorInt_append_2_full (excepción) ---
    {
        cout << "[T02-114 VectorInt_append_2_full]" << endl;
        VectorInt v(VectorInt::DIM_VECTOR_VALUES);
        try {
            v.append(7);
            cout << "  => FALLO (no lanzó excepción)" << endl;
        } catch (const std::out_of_range& e) {
            cout << "  => OK (lanzó std::out_of_range: " << e.what() << ")" << endl;
        }
        cout << endl;
    }

    // --- TEST 115: VectorInt_VectorInt_def2 ---
    {
        VectorInt v(5);
        string result = std::regex_replace(v.toString(), std::regex(ENDL), " ");
        CHECK("T02-115 VectorInt_VectorInt_def2", result, string("5 0 0 0 0 0 "));
    }

    // --- TEST 116: VectorInt_at_exception0 (excepción) ---
    {
        cout << "[T02-116 VectorInt_at_exception0]" << endl;
        VectorInt v(2);
        try {
            v.at(-1);
            cout << "  => FALLO (no lanzó excepción)" << endl;
        } catch (const std::out_of_range& e) {
            cout << "  => OK (lanzó std::out_of_range: " << e.what() << ")" << endl;
        }
        cout << endl;
    }

    // --- TEST 117: VectorInt_at_exception1 (excepción) ---
    {
        cout << "[T02-117 VectorInt_at_exception1]" << endl;
        VectorInt v(2);
        try {
            v.at(2);
            cout << "  => FALLO (no lanzó excepción)" << endl;
        } catch (const std::out_of_range& e) {
            cout << "  => OK (lanzó std::out_of_range: " << e.what() << ")" << endl;
        }
        cout << endl;
    }

    // --- TEST 118: VectorInt_distance_fail1 (excepción) ---
    {
        cout << "[T02-118 VectorInt_distance_fail1]" << endl;
        VectorInt v1(3), v2(5);
        try {
            v1.distance(v2);
            cout << "  => FALLO (no lanzó excepción)" << endl;
        } catch (const std::invalid_argument& e) {
            cout << "  => OK (lanzó std::invalid_argument: " << e.what() << ")" << endl;
        }
        cout << endl;
    }

    // --- TEST 119: VectorInt_distance_fail2 (excepción) ---
    {
        cout << "[T02-119 VectorInt_distance_fail2]" << endl;
        VectorInt v1, v2;
        try {
            v1.distance(v2);
            cout << "  => FALLO (no lanzó excepción)" << endl;
        } catch (const std::invalid_argument& e) {
            cout << "  => OK (lanzó std::invalid_argument: " << e.what() << ")" << endl;
        }
        cout << endl;
    }

    // --- TEST 120: VectorInt_countIdenticalElements2_excep (excepción) ---
    {
        cout << "[T02-120 VectorInt_countIdenticalElements2_excep]" << endl;
        VectorInt v1(3), v2(2);
        try {
            v1.countIdenticalElements(v2);
            cout << "  => FALLO (no lanzó excepción)" << endl;
        } catch (const std::invalid_argument& e) {
            cout << "  => OK (lanzó std::invalid_argument: " << e.what() << ")" << endl;
        }
        cout << endl;
    }

    // --- TEST 121: Clustering_run_0 ---
    {
        VectorLocation locations; fill_vlocation(locations, 3);
        Clustering clt; clt.set(locations, 2, 12345);
        clt.run();
        string result = std::regex_replace(clt.toString(), std::regex(ENDL), " ");
        string expected = "K=2 Sum of within-cluster variances: 1.000000 Number of iterations: 2 "
            "Cluster number for each location: 3 0 1 1 "
            "Centroids: 2 0.000000 0.000000  1.500000 1.500000  "
            " Cluster 0 information: 0 0.000000 0.000000 Location0 "
            " Cluster 1 information: 1 1.000000 1.000000 Location1 2 2.000000 2.000000 Location2 "
            " ";
        CHECK("T02-121 Clustering_run_0", result, expected);
    }

    // --- TEST 122: Clustering_clusterOf_AfterRun ---
    {
        VectorLocation locations; fill_vlocation(locations, 3);
        Clustering clt; clt.set(locations, 2, 12345);
        clt.run();
        string result = std::to_string(clt.clusterOf(0)) + " " +
                        std::to_string(clt.clusterOf(1)) + " " +
                        std::to_string(clt.clusterOf(2));
        CHECK("T02-122 Clustering_clusterOf_AfterRun", result, string("0 1 1"));
    }

    // --- TEST 123: Clustering_getSumWCV_AfterRun ---
    {
        VectorLocation locations; fill_vlocation(locations, 3);
        Clustering clt; clt.set(locations, 2, 12345);
        clt.run();
        CHECK("T02-123 Clustering_getSumWCV_AfterRun", clt.getSumWCV(), 1.0);
    }

    // --- TEST 124: Clustering_getNumIterations_AfterRun ---
    {
        VectorLocation locations; fill_vlocation(locations, 3);
        Clustering clt; clt.set(locations, 2, 12345);
        clt.run();
        CHECK("T02-124 Clustering_getNumIterations_AfterRun", clt.getNumIterations(), 2);
    }

    // --- TEST 125: Clustering_clusterInfo1 ---
    {
        VectorLocation locations; fill_vlocation(locations, 3);
        Clustering clt; clt.set(locations, 2, 12345);
        clt.run();
        string result = std::regex_replace(clt.clusterInfo(1), std::regex(ENDL), " ");
        CHECK("T02-125 Clustering_clusterInfo1", result,
              string("1 1.000000 1.000000 Location1 2 2.000000 2.000000 Location2 "));
    }

    // --- TEST 126: Clustering_getStatistics ---
    {
        VectorLocation locations; fill_vlocation(locations, 3);
        Clustering clt; clt.set(locations, 2, 12345);
        clt.run();
        string result = std::regex_replace(clt.getStatistics(), std::regex(ENDL), " ");
        CHECK("T02-126 Clustering_getStatistics", result,
              string("K=2 Sum of within-cluster variances: 1.000000 Number of iterations: 2 "));
    }

    // --- TEST 127: ArrayClustering_Initialize_2 (excepción) ---
    {
        cout << "[T02-127 ArrayClustering_Initialize_2]" << endl;
        ArrayClustering arrayClt;
        try {
            InitializeArrayClustering(arrayClt, 0);
            cout << "  => FALLO (no lanzó excepción)" << endl;
        } catch (const std::out_of_range& e) {
            cout << "  => OK (lanzó std::out_of_range: " << e.what() << ")" << endl;
        }
        cout << endl;
    }

    // --- TEST 128: ArrayClustering_sort_2_no_change ---
    {
        ArrayClustering arrayClt; InitializeArrayClustering(arrayClt, 5);
        arrayClt.size = 5;
        for (int i = 0; i < arrayClt.size; i++) {
            arrayClt.clustering[i]._K = 2;
            arrayClt.clustering[i]._sumWCV = 1.0;
            arrayClt.clustering[i]._numIterations = 10 + i;
            arrayClt.clustering[i]._isDone = true;
        }
        SortArrayClustering(arrayClt);
        string result = inspectT(arrayClt);
        DeallocateArrayClustering(arrayClt);
        string expected = "capacity: 5 size: 5 List of Clusters: "
            "K=2 Sum of within-cluster variances: 1.000000 Number of iterations: 10 Cluster number for each location: 0 Centroids: 0 Cluster 0 information: Cluster 1 information: "
            "K=2 Sum of within-cluster variances: 1.000000 Number of iterations: 11 Cluster number for each location: 0 Centroids: 0 Cluster 0 information: Cluster 1 information: "
            "K=2 Sum of within-cluster variances: 1.000000 Number of iterations: 12 Cluster number for each location: 0 Centroids: 0 Cluster 0 information: Cluster 1 information: "
            "K=2 Sum of within-cluster variances: 1.000000 Number of iterations: 13 Cluster number for each location: 0 Centroids: 0 Cluster 0 information: Cluster 1 information: "
            "K=2 Sum of within-cluster variances: 1.000000 Number of iterations: 14 Cluster number for each location: 0 Centroids: 0 Cluster 0 information: Cluster 1 information: ";
        CHECK("T02-128 ArrayClustering_sort_2_no_change", result, expected);
    }

    // --- TEST 129: ArrayClustering_sort_3_invert ---
    {
        int n = 5;
        ArrayClustering arrayClt; InitializeArrayClustering(arrayClt, n);
        arrayClt.size = n;
        for (int i = 0; i < n; i++) {
            arrayClt.clustering[n-i-1]._K = 2;
            arrayClt.clustering[n-i-1]._sumWCV = 1.0 + i;
            arrayClt.clustering[n-i-1]._numIterations = 10;
            arrayClt.clustering[n-i-1]._isDone = true;
        }
        SortArrayClustering(arrayClt);
        string result = inspectT(arrayClt);
        DeallocateArrayClustering(arrayClt);
        string expected = "capacity: 5 size: 5 List of Clusters: "
            "K=2 Sum of within-cluster variances: 1.000000 Number of iterations: 10 Cluster number for each location: 0 Centroids: 0 Cluster 0 information: Cluster 1 information: "
            "K=2 Sum of within-cluster variances: 2.000000 Number of iterations: 10 Cluster number for each location: 0 Centroids: 0 Cluster 0 information: Cluster 1 information: "
            "K=2 Sum of within-cluster variances: 3.000000 Number of iterations: 10 Cluster number for each location: 0 Centroids: 0 Cluster 0 information: Cluster 1 information: "
            "K=2 Sum of within-cluster variances: 4.000000 Number of iterations: 10 Cluster number for each location: 0 Centroids: 0 Cluster 0 information: Cluster 1 information: "
            "K=2 Sum of within-cluster variances: 5.000000 Number of iterations: 10 Cluster number for each location: 0 Centroids: 0 Cluster 0 information: Cluster 1 information: ";
        CHECK("T02-129 ArrayClustering_sort_3_invert", result, expected);
    }

    // --- TEST 130: ArrayClustering_sort_4_invert ---
    {
        int n = 5;
        ArrayClustering arrayClt; InitializeArrayClustering(arrayClt, n);
        arrayClt.size = n;
        for (int i = 0; i < n; i++) {
            arrayClt.clustering[n-i-1]._K = 2;
            arrayClt.clustering[n-i-1]._sumWCV = 1.0;
            arrayClt.clustering[n-i-1]._numIterations = 10 + i;
            arrayClt.clustering[n-i-1]._isDone = true;
        }
        SortArrayClustering(arrayClt);
        string result = inspectT(arrayClt);
        DeallocateArrayClustering(arrayClt);
        string expected = "capacity: 5 size: 5 List of Clusters: "
            "K=2 Sum of within-cluster variances: 1.000000 Number of iterations: 10 Cluster number for each location: 0 Centroids: 0 Cluster 0 information: Cluster 1 information: "
            "K=2 Sum of within-cluster variances: 1.000000 Number of iterations: 11 Cluster number for each location: 0 Centroids: 0 Cluster 0 information: Cluster 1 information: "
            "K=2 Sum of within-cluster variances: 1.000000 Number of iterations: 12 Cluster number for each location: 0 Centroids: 0 Cluster 0 information: Cluster 1 information: "
            "K=2 Sum of within-cluster variances: 1.000000 Number of iterations: 13 Cluster number for each location: 0 Centroids: 0 Cluster 0 information: Cluster 1 information: "
            "K=2 Sum of within-cluster variances: 1.000000 Number of iterations: 14 Cluster number for each location: 0 Centroids: 0 Cluster 0 information: Cluster 1 information: ";
        CHECK("T02-130 ArrayClustering_sort_4_invert", result, expected);
    }

    return 0;
}
