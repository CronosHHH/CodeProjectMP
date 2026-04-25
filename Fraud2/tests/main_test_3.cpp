/*
 * Metodología de la Programación — Curso 2025/2026
 *
 * main_tests.cpp
 * Framework de testing secuencial para los 130 tests de unidad (T01 + T02)
 *
 * COMPILAR:
 *   g++ -DTESTING -std=c++17 -o build/tests \
 *       main.cpp Location.cpp VectorLocation.cpp VectorInt.cpp \
 *       Clustering.cpp ArrayClustering.cpp
 *
 * EJECUTAR:
 *   ./build/tests            ← todos los tests
 *   ./build/tests 44         ← solo el test 44
 *   ./build/tests 1 20       ← tests del 1 al 20
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <cmath>
#include <string>
#include <functional>
#include <vector>
#include <iomanip>

#include "VectorLocation.h"
#include "VectorInt.h"
#include "Clustering.h"
#include "ArrayClustering.h"

using namespace std;

// ============================================================
//  Macros de los tests
// ============================================================
#define ENDL "\n"
#define LOCATION_DEFAULT "0.000000 0.000000"
#define LOCATION_OTHER   "37.200000 -3.600000 Granada"

// ============================================================
//  Estructura de resultado de un test
// ============================================================
struct TestResult {
    int    id;
    string name;
    bool   passed;
    string detail;
};

static vector<TestResult> g_results;
static int    g_current_id   = 0;
static string g_current_name = "";

// ---- Registra un test de valor genérico ----
template<typename T>
void EXPECT_EQ(const T& result, const T& expected) {
    bool ok = (result == expected);
    string detail = "";
    if (!ok) {
        ostringstream oss;
        oss << "    Obtenido : [" << result  << "]\n"
            << "    Esperado : [" << expected << "]";
        detail = oss.str();
    }
    g_results.push_back({g_current_id, g_current_name, ok, detail});
}

void EXPECT_BOOL(bool result, bool expected) {
    EXPECT_EQ(result, expected);
}

// ---- Registra un test que DEBE lanzar excepción ----
void EXPECT_THROW(function<void()> fn, const string& exType) {
    bool ok = false;
    string detail = "";
    try {
        fn();
        detail = "    No se lanzó ninguna excepción (esperaba " + exType + ")";
    } catch (const std::out_of_range&) {
        ok = (exType == "std::out_of_range");
        if (!ok) detail = "    Lanzó out_of_range pero se esperaba " + exType;
    } catch (const std::invalid_argument&) {
        ok = (exType == "std::invalid_argument");
        if (!ok) detail = "    Lanzó invalid_argument pero se esperaba " + exType;
    } catch (const std::exception& e) {
        detail = string("    Lanzó excepción inesperada: ") + e.what();
    }
    g_results.push_back({g_current_id, g_current_name, ok, detail});
}

// ---- Macro para declarar el test activo ----
#define TEST(id, name)  g_current_id = (id); g_current_name = (name);

// ============================================================
//  inspectT para ArrayClustering (función libre)
// ============================================================
string inspectT(const ArrayClustering& ac) {
    string r = "capacity: " + to_string(ac.capacity) +
               " size: "    + to_string(ac.size) +
               " List of Clusters: ";
    for (int i = 0; i < ac.size; i++)
        r += regex_replace(ac.clustering[i].toString(), regex(ENDL), " ");
    return r;
}

// ============================================================
//  Funciones auxiliares de datos
// ============================================================
void fill_vlocation(VectorLocation& locs, int size) {
    Location loc;
    for (int i = 0; i < size; i++) {
        loc.set(i, i, "Location" + to_string(i));
        locs.append(loc);
    }
}

void refill_vlocation(VectorLocation& locs, int size) {
    locs.clear();
    Location loc;
    for (int i = 0; i < size; i++) {
        loc.set(i, i, "Location" + to_string(i));
        locs.append(loc);
    }
}

// ============================================================
//  TODOS LOS TESTS
// ============================================================
void run_all_tests() {

    // --------------------------------------------------------
    // T01 — Location (1-20)
    // --------------------------------------------------------

    TEST(1, "T01.Location_Location_def1")
    { Location loc;
      EXPECT_EQ(loc.toString(), string("0.000000 0.000000")); }

    TEST(2, "T01.Location_get_XY")
    { Location loc;
      EXPECT_EQ(loc.getX()+loc.getY()+loc.getX()*loc.getY(), 0.0); }

    TEST(3, "T01.Location_getName")
    { Location loc;
      EXPECT_EQ(loc.getName(), string("")); }

    TEST(4, "T01.Location_set_Onelocation")
    { float f1=37.2f,f2=-3.6f; Location loc; loc.set(f1,f2,"Granada");
      EXPECT_EQ(loc.toString(), string("37.200001 -3.600000 Granada")); }

    TEST(5, "T01.Location_set_XY")
    { float f1=37.2f,f2=-3.6f; Location loc; loc.setX(f1); loc.setY(f2);
      EXPECT_EQ(loc.toString(), string("37.200001 -3.600000")); }

    TEST(6, "T01.Location_setName")
    { Location loc; loc.setName("Granada");
      EXPECT_EQ(loc.toString(), string("0.000000 0.000000 Granada")); }

    TEST(7, "T01.Location_isInsideArea_in0")
    { float f1=37.2f,f2=-3.6f,f3=39.47f,f4=-0.37f;
      Location l1,l2; l1.set(f1,f2,""); l2.set(f3,f4,"");
      EXPECT_BOOL(l1.isInsideArea(l1,l2), true); }

    TEST(8, "T01.Location_isInsideArea_in1")
    { float f1=37.2f,f2=-3.6f,f3=39.47f,f4=-0.37f;
      Location l1,l2; l1.set(f1,f2,""); l2.set(f3,f4,"");
      EXPECT_BOOL(l2.isInsideArea(l1,l2), true); }

    TEST(9, "T01.Location_isInsideArea_in2")
    { float f1=37.2f,f2=-3.6f,f3=39.47f,f4=-0.37f;
      Location l1,l2,l3; l1.set(f1,f2,""); l2.set(f3,f4,""); l3.set(f1+0.2f,f2+0.2f,"");
      EXPECT_BOOL(l3.isInsideArea(l1,l2), true); }

    TEST(10, "T01.Location_isInsideArea_out0")
    { float f1=37.2f,f2=-3.6f,f3=39.47f,f4=-0.37f;
      Location l1,l2,l3; l1.set(f1,f2,""); l2.set(f3,f4,""); l3.set(f3+0.2f,f4,"");
      EXPECT_BOOL(l3.isInsideArea(l1,l2), false); }

    TEST(11, "T01.Location_isInsideArea_out1")
    { float f1=37.2f,f2=-3.6f,f3=39.47f,f4=-0.37f;
      Location l1,l2,l3; l1.set(f1,f2,""); l2.set(f3,f4,""); l3.set(f3,f4+0.2f,"");
      EXPECT_BOOL(l3.isInsideArea(l1,l2), false); }

    TEST(12, "T01.Location_isInsideArea_out2")
    { float f1=37.2f,f2=-3.6f,f3=39.47f,f4=-0.37f;
      Location l1,l2,l3; l1.set(f1,f2,""); l2.set(f3,f4,""); l3.set(f1-0.2f,f2,"");
      EXPECT_BOOL(l3.isInsideArea(l1,l2), false); }

    TEST(13, "T01.Location_isInsideArea_out3")
    { float f1=37.2f,f2=-3.6f,f3=39.47f,f4=-0.37f;
      Location l1,l2,l3; l1.set(f1,f2,""); l2.set(f3,f4,""); l3.set(f1,f2-0.2f,"");
      EXPECT_BOOL(l3.isInsideArea(l1,l2), false); }

    TEST(14, "T01.Location_squaredDistance_l0")
    { float f1=37.2f,f2=-3.6f; Location l1; l1.set(f1,f2,"");
      EXPECT_EQ(l1.squaredDistance(l1), 0.0); }

    TEST(15, "T01.Location_squaredDistance_l1")
    { Location l1,l2; l2.set(2.0,2.0,"");
      EXPECT_EQ(l1.squaredDistance(l2), 8.0); }

    TEST(16, "T01.Location_distance_l0")
    { float f1=37.2f,f2=-3.6f; Location l1; l1.set(f1,f2,"");
      EXPECT_EQ(l1.distance(l1), 0.0); }

    TEST(17, "T01.Location_distance_l1")
    { Location l1,l2; l2.set(2.0,2.0,"");
      EXPECT_EQ(l1.distance(l2), sqrt(8.0)); }

    TEST(18, "T01.Location_distance_l2")
    { Location l1,l2; l2.set(2.0,2.0,"");
      EXPECT_EQ(l2.distance(l1), sqrt(8.0)); }

    TEST(19, "T01.Location_load_0")
    { Location loc; istringstream ss("37.200000 -3.600000"); loc.load(ss);
      EXPECT_EQ(loc.toString(), string("37.200000 -3.600000")); }

    TEST(20, "T01.Location_load_1")
    { Location loc; istringstream ss("37.200000 -3.600000 Granada"); loc.load(ss);
      EXPECT_EQ(loc.toString(), string("37.200000 -3.600000 Granada")); }

    // --------------------------------------------------------
    // T01 — VectorLocation (21-46)
    // --------------------------------------------------------

    TEST(21, "T01.VectorLocation_getCapacity")
    { VectorLocation v; v._size=2;
      EXPECT_EQ(v.getCapacity(), 100); }

    TEST(22, "T01.VectorLocation_getCapacity2")
    { VectorLocation v(10); v._size=2;
      EXPECT_EQ(v.getCapacity(), 100); }

    TEST(23, "T01.VectorLocation_Clear_1")
    { VectorLocation v; v._size=VectorLocation::DIM_VECTOR_LOCATIONS; v.clear();
      EXPECT_EQ(v.getSize(), 0); }

    TEST(24, "T01.VectorLocation_VectorLocation_def3")
    { VectorLocation v(VectorLocation::DIM_VECTOR_LOCATIONS);
      EXPECT_EQ(v._size, 100); }

    TEST(25, "T01.VectorLocation_VectorLocation_def1")
    { VectorLocation v;
      EXPECT_EQ(regex_replace(v.toString(), regex(ENDL)," "), string("0 ")); }

    TEST(26, "T01.VectorLocation_VectorLocation_def2")
    { VectorLocation v(1);
      EXPECT_EQ(regex_replace(v.toString(),regex(ENDL)," "), string("1 0.000000 0.000000 ")); }

    TEST(27, "T01.VectorLocation_getSize0")
    { VectorLocation v; EXPECT_EQ(v.getSize(), 0); }

    TEST(28, "T01.VectorLocation_getSize1")
    { VectorLocation v(2); EXPECT_EQ(v.getSize(), 2); }

    TEST(29, "T01.VectorLocation_toString")
    { Location l1,l2; l2.set(37.2,-3.6,"Granada");
      VectorLocation v(2); v._locations[0]=l1; v._locations[1]=l2;
      EXPECT_EQ(regex_replace(v.toString(),regex(ENDL)," "),
                string("2 0.000000 0.000000 37.200000 -3.600000 Granada ")); }

    TEST(30, "T01.VectorLocation_Clear_0")
    { VectorLocation v; v.clear(); EXPECT_EQ(v.getSize(), 0); }

    TEST(31, "T01.VectorLocation_append_0")
    { Location loc; loc.set(37.2,-3.6,"Granada"); VectorLocation v; v.append(loc);
      EXPECT_EQ(regex_replace(v.toString(),regex(ENDL)," "),
                string("1 37.200000 -3.600000 Granada ")); }

    TEST(32, "T01.VectorLocation_append_1")
    { Location l1,l2; l2.set(37.2,-3.6,"Granada"); VectorLocation v;
      v.append(l1); v.append(l2);
      EXPECT_EQ(regex_replace(v.toString(),regex(ENDL)," "),
                string("2 0.000000 0.000000 37.200000 -3.600000 Granada ")); }

    TEST(33, "T01.VectorLocation_at_0")
    { VectorLocation v(2); EXPECT_EQ(v.at(0).toString(), string("0.000000 0.000000")); }

    TEST(34, "T01.VectorLocation_at_1")
    { VectorLocation v(2); EXPECT_EQ(v.at(1).toString(), string("0.000000 0.000000")); }

    TEST(35, "T01.VectorLocation_at_2")
    { Location loc; loc.set(37.2,-3.6,"Granada"); VectorLocation v(2); v.at(0)=loc;
      EXPECT_EQ(v.at(0).toString(), string("37.200000 -3.600000 Granada")); }

    TEST(36, "T01.VectorLocation_at_3")
    { Location loc; loc.set(37.2,-3.6,"Granada"); VectorLocation v(2); v.at(1)=loc;
      EXPECT_EQ(v.at(1).toString(), string("37.200000 -3.600000 Granada")); }

    TEST(37, "T01.VectorLocation_findLocation_0")
    { Location loc; VectorLocation v; EXPECT_EQ(v.findLocation(loc), -1); }

    TEST(38, "T01.VectorLocation_findLocation_1")
    { Location l2; l2.set(37.2,-3.6,"Granada"); VectorLocation v(2); v._locations[0]=l2;
      EXPECT_EQ(v.findLocation(l2), 0); }

    TEST(39, "T01.VectorLocation_findLocation_2")
    { Location l2; l2.set(37.2,-3.6,"Granada"); VectorLocation v(2); v._locations[1]=l2;
      EXPECT_EQ(v.findLocation(l2), 1); }

    TEST(40, "T01.VectorLocation_findLocation_3")
    { Location loc; loc.setName("OTHER"); VectorLocation v(5);
      EXPECT_EQ(v.findLocation(loc), -1); }

    TEST(41, "T01.VectorLocation_nearest_0")
    { Location loc; loc.set(1,1,"1"); VectorLocation v;
      EXPECT_EQ(v.nearest(loc), -1); }

    TEST(42, "T01.VectorLocation_nearest_1")
    { int n=5; Location loc; loc.set(0,0,"1"); VectorLocation v(n);
      for(int i=0;i<n;i++) v._locations[i].set(i,i,to_string(i));
      EXPECT_EQ(v.nearest(loc), 0); }

    TEST(43, "T01.VectorLocation_nearest_2")
    { int n=5; Location loc; loc.set(0,0,"1"); VectorLocation v(n);
      for(int i=0;i<n;i++) v._locations[n-(i+1)].set(i,i,to_string(i));
      EXPECT_EQ(v.nearest(loc), 4); }

    TEST(44, "T01.VectorLocation_loadFromFile_0")
    { int n=5; VectorLocation l1(n),l2; Location loc;
      for(int i=0;i<n;i++){loc.set(i,i,to_string(i));l1.at(i)=loc;}
      const char* fn="tests/output/test_save1.loc";
      ofstream fo(fn); fo<<l1.toString(); fo.close();
      ifstream fi(fn); l2.load(fi); fi.close();
      EXPECT_EQ(regex_replace(l2.toString(),regex(ENDL)," "),
                string("5 0.000000 0.000000 0 1.000000 1.000000 1 2.000000 2.000000 2 3.000000 3.000000 3 4.000000 4.000000 4 ")); }

    TEST(45, "T01.VectorLocation_loadFromCin_1")
    { VectorLocation l(1); string ss=string("1 ")+LOCATION_OTHER+" ";
      istringstream ssin(ss); l.load(ssin);
      EXPECT_EQ(regex_replace(l.toString(),regex(ENDL)," "),
                string("1 37.200000 -3.600000 Granada ")); }

    TEST(46, "T01.VectorLocation_loadEmptyName_4")
    { VectorLocation l(1); string ss=string("1 ")+LOCATION_DEFAULT+" ";
      istringstream ssin(ss); l.load(ssin); l.load(ssin);
      EXPECT_EQ(regex_replace(l.toString(),regex(ENDL)," "),
                string("1 0.000000 0.000000 ")); }

    // --------------------------------------------------------
    // T01 — VectorInt (47-63)
    // --------------------------------------------------------

    TEST(47, "T01.VectorInt_getCapacity")
    { VectorInt v; v._size=2; EXPECT_EQ(v.getCapacity(), 100); }

    TEST(48, "T01.VectorInt_def0")
    { VectorInt v; EXPECT_EQ(v._size, 0); }

    TEST(49, "T01.VectorInt_def1")
    { VectorInt v(5); EXPECT_EQ(v._size, 5); }

    TEST(50, "T01.VectorInt_getSize")
    { VectorInt v(5); EXPECT_EQ(v.getSize(), 5); }

    TEST(51, "T01.VectorInt_assign")
    { VectorInt v(4); v.assign(7);
      EXPECT_EQ(regex_replace(v.toString(),regex(ENDL)," "), string("4 7 7 7 7 ")); }

    TEST(52, "T01.VectorInt_append_0")
    { VectorInt v(2); v.append(7); EXPECT_EQ(v._size, 3); }

    TEST(53, "T01.VectorInt_append_1")
    { VectorInt v(2); v.append(7); EXPECT_EQ(v._values[2], 7); }

    TEST(54, "T01.VectorInt_clear")
    { VectorInt v(5); v.clear(); EXPECT_EQ(v.getSize(), 0); }

    TEST(55, "T01.VectorInt_at_0")
    { VectorInt v(2); v._values[0]=7; EXPECT_EQ(v.at(0), 7); }

    TEST(56, "T01.VectorInt_at_1")
    { VectorInt v(2); v._values[1]=7; EXPECT_EQ(v.at(1), 7); }

    TEST(57, "T01.VectorInt_at_2")
    { VectorInt v(2); v.at(1)=7;
      EXPECT_EQ(regex_replace(v.toString(),regex(ENDL)," "), string("2 0 7 ")); }

    TEST(58, "T01.VectorInt_toString1")
    { VectorInt v(5);
      EXPECT_EQ(regex_replace(v.toString(),regex(ENDL)," "), string("5 0 0 0 0 0 ")); }

    TEST(59, "T01.VectorInt_toString2")
    { VectorInt v(5); v.assign(7);
      EXPECT_EQ(regex_replace(v.toString(),regex(ENDL)," "), string("5 7 7 7 7 7 ")); }

    TEST(60, "T01.VectorInt_distance0")
    { VectorInt v1(3),v2(3);
      for(int i=0;i<3;i++){v1._values[i]=i+1;v2._values[i]=i+1;}
      EXPECT_EQ(v1.distance(v2), 0.0); }

    TEST(61, "T01.VectorInt_distance1")
    { VectorInt v1(3),v2(3);
      for(int i=0;i<3;i++){v1._values[i]=i+1;v2._values[i]=i+1;}
      v2._values[2]=6;
      EXPECT_EQ(v1.distance(v2), 3.0); }

    TEST(62, "T01.VectorInt_countIdenticalElements0")
    { VectorInt v1(3),v2(3); EXPECT_EQ(v1.countIdenticalElements(v2), 3); }

    TEST(63, "T01.VectorInt_countIdenticalElements1")
    { VectorInt v1(3),v2(3);
      for(int i=0;i<3;i++){v1._values[i]=5;v2._values[i]=5;} v2._values[0]=1;
      EXPECT_EQ(v1.countIdenticalElements(v2), 2); }

    // --------------------------------------------------------
    // T01 — Clustering (64-75)
    // --------------------------------------------------------

    TEST(64, "T01.Clustering_def0")
    { Clustering c;
      EXPECT_EQ(c._clusters.getSize()+c._isDone+c._K+c._numIterations+c._sumWCV, 0.0); }

    TEST(65, "T01.Clustering_def1")
    { Clustering c; EXPECT_EQ((unsigned)c._seed, 1761560597U); }

    TEST(66, "T01.Clustering_def2")
    { VectorLocation loc; fill_vlocation(loc,3); Clustering c; c.set(loc,2,12345);
      string e="K=2 Sum of within-cluster variances: 0.000000 Number of iterations: 0 "
               "Cluster number for each location: 3 0 0 0 Centroids: 2 "
               "0.000000 0.000000 0.000000 0.000000 "
               "Cluster 0 information: Cluster 1 information: ";
      EXPECT_EQ(regex_replace(c.toString(),regex(ENDL)," "), e); }

    TEST(67, "T01.Clustering_gets_5functions")
    { VectorLocation loc; fill_vlocation(loc,5); Clustering c; c.set(loc,3,12345);
      string r=to_string(c.getK())+" "+to_string(c.getNumLocations())+" "+
               to_string(c.getCentroids().getSize())+" "+to_string(c.getSumWCV())+" "+
               to_string(c.getNumIterations());
      EXPECT_EQ(r, string("3 5 3 0.000000 0")); }

    TEST(68, "T01.Clustering_clusterOf_BeforeRun")
    { VectorLocation loc; fill_vlocation(loc,3); Clustering c; c.set(loc,2,12345);
      EXPECT_EQ(c.clusterOf(1), -1); }

    TEST(69, "T01.Clustering_getSumWCV_BeforeRun")
    { VectorLocation loc; fill_vlocation(loc,3); Clustering c; c.set(loc,2,12345);
      EXPECT_EQ(c.getSumWCV(), 0.0); }

    TEST(70, "T01.Clustering_clusterInfo2_InvalidCluster")
    { VectorLocation loc; fill_vlocation(loc,3); Clustering c; c.set(loc,2,12345);
      EXPECT_EQ(regex_replace(c.clusterInfo(2),regex(ENDL)," "), string("")); }

    TEST(71, "T01.Clustering_isEquivalentTo_1")
    { VectorLocation loc; fill_vlocation(loc,3); Clustering c1,c2;
      c1.set(loc,2,12345); c2.set(loc,2,12345); c1.run(); c2.run();
      EXPECT_BOOL(c1.isEquivalentTo(c2), true); }

    TEST(72, "T01.Clustering_isEquivalentTo_2")
    { VectorLocation loc; fill_vlocation(loc,3); Clustering c1,c2;
      c1.set(loc,2,12345); c2.set(loc,2,12345); c1.run();
      EXPECT_BOOL(c1.isEquivalentTo(c2), false); }

    TEST(73, "T01.Clustering_toString")
    { VectorLocation loc; fill_vlocation(loc,3); Clustering c; c.set(loc,2,12345);
      string e="K=2 Sum of within-cluster variances: 0.000000 Number of iterations: 0 "
               "Cluster number for each location: 3 0 0 0 Centroids: 2 "
               "0.000000 0.000000 0.000000 0.000000 "
               "Cluster 0 information: Cluster 1 information: ";
      EXPECT_EQ(regex_replace(c.toString(),regex(ENDL)," "), e); }

    TEST(74, "T01.Clustering_set")
    { VectorLocation loc; fill_vlocation(loc,3); Clustering c; c.set(loc,2,12345);
      string e="K=2 Sum of within-cluster variances: 0.000000 Number of iterations: 0 "
               "Cluster number for each location: 3 0 0 0 Centroids: 2 "
               "0.000000 0.000000 0.000000 0.000000 "
               "Cluster 0 information: Cluster 1 information: ";
      EXPECT_EQ(regex_replace(c.toString(),regex(ENDL)," "), e); }

    TEST(75, "T01.Clustering_set_InvalidK")
    { VectorLocation loc; fill_vlocation(loc,3); Clustering c;
      EXPECT_THROW([&](){ c.set(loc,0,12345); }, "std::invalid_argument"); }

    // --------------------------------------------------------
    // T01 — ArrayClustering (76-89)
    // --------------------------------------------------------

    TEST(76, "T01.ArrayClustering_Initialize_0")
    { ArrayClustering ac; InitializeArrayClustering(ac);
      string r=inspectT(ac); DeallocateArrayClustering(ac);
      EXPECT_EQ(r, string("capacity: 2 size: 0 List of Clusters: ")); }

    TEST(77, "T01.ArrayClustering_Initialize_1")
    { ArrayClustering ac; InitializeArrayClustering(ac,1);
      string r=inspectT(ac); DeallocateArrayClustering(ac);
      EXPECT_EQ(r, string("capacity: 1 size: 0 List of Clusters: ")); }

    TEST(78, "T01.ArrayClustering_findClustering_1")
    { Clustering c; ArrayClustering ac; ac.clustering=nullptr; ac.capacity=0; ac.size=0;
      EXPECT_EQ(FindArrayClustering(ac,c), -1); }

    TEST(79, "T01.ArrayClustering_findClustering_2")
    { VectorLocation loc; refill_vlocation(loc,3);
      Clustering c2; c2.set(loc,3,12345); c2._numIterations=11; c2._sumWCV=1.2; c2._isDone=true;
      ArrayClustering ac; InitializeArrayClustering(ac); ac.size=2;
      ac.clustering[0]._K=3; ac.clustering[0]._numIterations=11;
      ac.clustering[0]._sumWCV=1.2; ac.clustering[0]._isDone=true;
      int r=FindArrayClustering(ac,c2); DeallocateArrayClustering(ac);
      EXPECT_EQ(r, 0); }

    TEST(80, "T01.ArrayClustering_findClustering_3")
    { VectorLocation loc; refill_vlocation(loc,3);
      Clustering c2; c2.set(loc,3,12345); c2._numIterations=11; c2._sumWCV=1.2; c2._isDone=true;
      ArrayClustering ac; InitializeArrayClustering(ac); ac.size=2;
      ac.clustering[1]._K=3; ac.clustering[1]._numIterations=11;
      ac.clustering[1]._sumWCV=1.2; ac.clustering[1]._isDone=true;
      int r=FindArrayClustering(ac,c2); DeallocateArrayClustering(ac);
      EXPECT_EQ(r, 1); }

    TEST(81, "T01.ArrayClustering_findClustering_4_diff_sumWCV")
    { VectorLocation loc; refill_vlocation(loc,3);
      Clustering c2; c2.set(loc,3,12345); c2._numIterations=11; c2._sumWCV=1.3; c2._isDone=true;
      ArrayClustering ac; InitializeArrayClustering(ac,3); ac.size=3;
      ac.clustering[1]._K=3; ac.clustering[1]._numIterations=11;
      ac.clustering[1]._sumWCV=1.2; ac.clustering[1]._isDone=true;
      int r=FindArrayClustering(ac,c2); DeallocateArrayClustering(ac);
      EXPECT_EQ(r, -1); }

    TEST(82, "T01.ArrayClustering_findClustering_5_diff_iteration")
    { VectorLocation loc; refill_vlocation(loc,3);
      Clustering c2; c2.set(loc,3,12345); c2._numIterations=11; c2._sumWCV=1.3; c2._isDone=true;
      ArrayClustering ac; InitializeArrayClustering(ac,3); ac.size=3;
      ac.clustering[1]._K=3; ac.clustering[1]._numIterations=13;
      ac.clustering[1]._sumWCV=1.2; ac.clustering[1]._isDone=true;
      int r=FindArrayClustering(ac,c2); DeallocateArrayClustering(ac);
      EXPECT_EQ(r, -1); }

    TEST(83, "T01.ArrayClustering_findClustering_6_diff_K")
    { VectorLocation loc; refill_vlocation(loc,3);
      Clustering c2; c2.set(loc,3,12345); c2._numIterations=11; c2._sumWCV=1.3; c2._isDone=true;
      ArrayClustering ac; InitializeArrayClustering(ac,3); ac.size=3;
      ac.clustering[1]._K=4; ac.clustering[1]._numIterations=11;
      ac.clustering[1]._sumWCV=1.2; ac.clustering[1]._isDone=true;
      int r=FindArrayClustering(ac,c2); DeallocateArrayClustering(ac);
      EXPECT_EQ(r, -1); }

    TEST(84, "T01.ArrayClustering_append_0")
    { VectorLocation loc; refill_vlocation(loc,3);
      Clustering c; c.set(loc,2,12345); c._numIterations=11; c._sumWCV=1.3; c._isDone=true;
      ArrayClustering ac; InitializeArrayClustering(ac,3); AppendArrayClustering(ac,c);
      string r=to_string(ac.capacity)+" "+to_string(ac.size);
      DeallocateArrayClustering(ac);
      EXPECT_EQ(r, string("3 1")); }

    TEST(85, "T01.ArrayClustering_append_1")
    { VectorLocation loc; refill_vlocation(loc,3);
      Clustering c; c.set(loc,2,12345); c._numIterations=11; c._sumWCV=1.3; c._isDone=true;
      ArrayClustering ac; InitializeArrayClustering(ac,3);
      AppendArrayClustering(ac,c); AppendArrayClustering(ac,c); // duplicado
      string r=inspectT(ac); DeallocateArrayClustering(ac);
      string e="capacity: 3 size: 1 List of Clusters: "
               "K=2 Sum of within-cluster variances: 1.300000 Number of iterations: 11 "
               "Cluster number for each location: 3 0 0 0 Centroids: 2 "
               "0.000000 0.000000 0.000000 0.000000 "
               "Cluster 0 information: "
               "0 0.000000 0.000000 Location0 "
               "1 1.000000 1.000000 Location1 "
               "2 2.000000 2.000000 Location2 "
               "Cluster 1 information: ";
      EXPECT_EQ(r, e); }

    TEST(86, "T01.ArrayClustering_append_2")
    { VectorLocation loc; refill_vlocation(loc,3);
      Clustering c; c.set(loc,2,12345); c._numIterations=11; c._sumWCV=1.3; c._isDone=true;
      ArrayClustering ac; InitializeArrayClustering(ac); ac.size=2; // capacity=2, lleno
      AppendArrayClustering(ac,c); // resize a 4
      string r=to_string(ac.capacity)+" "+to_string(ac.size);
      DeallocateArrayClustering(ac);
      EXPECT_EQ(r, string("4 3")); }

    TEST(87, "T01.ArrayClustering_sort_1_no_change")
    { ArrayClustering ac; InitializeArrayClustering(ac,5); ac.size=5;
      for(int i=0;i<5;i++){ac.clustering[i]._K=2;ac.clustering[i]._sumWCV=1.0+i;
                            ac.clustering[i]._numIterations=10;ac.clustering[i]._isDone=true;}
      SortArrayClustering(ac); string r=inspectT(ac); DeallocateArrayClustering(ac);
      string e="capacity: 5 size: 5 List of Clusters: "
        "K=2 Sum of within-cluster variances: 1.000000 Number of iterations: 10 Cluster number for each location: 0 Centroids: 0 Cluster 0 information: Cluster 1 information: "
        "K=2 Sum of within-cluster variances: 2.000000 Number of iterations: 10 Cluster number for each location: 0 Centroids: 0 Cluster 0 information: Cluster 1 information: "
        "K=2 Sum of within-cluster variances: 3.000000 Number of iterations: 10 Cluster number for each location: 0 Centroids: 0 Cluster 0 information: Cluster 1 information: "
        "K=2 Sum of within-cluster variances: 4.000000 Number of iterations: 10 Cluster number for each location: 0 Centroids: 0 Cluster 0 information: Cluster 1 information: "
        "K=2 Sum of within-cluster variances: 5.000000 Number of iterations: 10 Cluster number for each location: 0 Centroids: 0 Cluster 0 information: Cluster 1 information: ";
      EXPECT_EQ(r, e); }

    TEST(88, "T01.ArrayClustering_Deallocate_0")
    { ArrayClustering ac; ac.clustering=nullptr; DeallocateArrayClustering(ac);
      EXPECT_EQ(ac.capacity+ac.size, 0); }

    TEST(89, "T01.ArrayClustering_Deallocate_1")
    { ArrayClustering ac; InitializeArrayClustering(ac,5); ac.size=5;
      DeallocateArrayClustering(ac);
      EXPECT_EQ(ac.capacity+ac.size, 0); }

    // --------------------------------------------------------
    // T02 — VectorLocation (90-112)
    // --------------------------------------------------------

    TEST(90, "T02.VectorLocation_VectorLocation_def4")
    { EXPECT_THROW([&](){ VectorLocation v(VectorLocation::DIM_VECTOR_LOCATIONS+1); },
                   "std::out_of_range"); }

    TEST(91, "T02.VectorLocation_findLocation_4")
    { Location loc; loc.setName("OTHER");
      VectorLocation v(VectorLocation::DIM_VECTOR_LOCATIONS);
      v._locations[VectorLocation::DIM_VECTOR_LOCATIONS-1]=loc;
      EXPECT_EQ(v.findLocation(loc), 99); }

    TEST(92, "T02.VectorLocation_out_of_range_append_4")
    { Location loc; loc.set(37.2,-3.6,"Granada");
      VectorLocation v; v._size=VectorLocation::DIM_VECTOR_LOCATIONS; v._locations[0]=loc;
      v.append(loc); // ya existe → no lanza
      EXPECT_EQ(v._size, 100); }

    TEST(93, "T02.VectorLocation_out_of_range_append_5")
    { Location loc; loc.set(0,0,"Terrace");
      VectorLocation v; v._size=VectorLocation::DIM_VECTOR_LOCATIONS;
      EXPECT_THROW([&](){ v.append(loc); }, "std::out_of_range"); }

    TEST(94, "T02.VectorLocation_Load_4_exception")
    { VectorLocation l(1);
      istringstream ss(to_string(VectorLocation::DIM_VECTOR_LOCATIONS+1));
      EXPECT_THROW([&](){ l.load(ss); }, "std::out_of_range"); }

    TEST(95, "T02.VectorLocation_VectorLocation_def5")
    { EXPECT_THROW([&](){ VectorLocation v(-1); }, "std::out_of_range"); }

    TEST(96, "T02.VectorLocation_append_2")
    { Location loc; loc.set(37.2,-3.6,"Granada"); VectorLocation v;
      v.append(loc); v.append(loc); // duplicado
      EXPECT_EQ(regex_replace(v.toString(),regex(ENDL)," "),
                string("1 37.200000 -3.600000 Granada ")); }

    TEST(97, "T02.VectorLocation_at_exception0")
    { VectorLocation v(2); EXPECT_THROW([&](){ v.at(-1); }, "std::out_of_range"); }

    TEST(98, "T02.VectorLocation_at_exception1")
    { VectorLocation v(2); EXPECT_THROW([&](){ v.at(2); }, "std::out_of_range"); }

    TEST(99, "T02.VectorLocation_select_0")
    { int n=5; Location l0,l1,l2; l1.set(1,1,"1"); l2.set(n,n,to_string(n));
      VectorLocation v(n),r2;
      for(int i=1;i<=n;i++) v._locations[i-1].set(-i,i,to_string(i));
      r2=v.select(l0,l2); EXPECT_EQ(r2._size, 0); }

    TEST(100, "T02.VectorLocation_select_1")
    { int n=5; Location l1,l2; l2.set(n,n,to_string(n));
      VectorLocation v(n),r2;
      for(int i=1;i<=n;i++) v._locations[i-1].set(i,i,to_string(i));
      r2=v.select(l1,l2); EXPECT_EQ(r2._size, 5); }

    TEST(101, "T02.VectorLocation_select_2")
    { int n=5; Location l0,l1,l2; l1.set(1,1,"1"); l2.set(n,n,to_string(n));
      VectorLocation v(n+1),r2;
      for(int i=0;i<=n;i++) v._locations[i].set(i*(n+1),i*(n+1),to_string(i));
      r2=v.select(l0,l2); EXPECT_EQ(r2._size, 1); }

    TEST(102, "T02.VectorLocation_select_3")
    { int n=5; Location l0,l1,l2; l0.set(0,0,"0"); l1.set(1,1,"1"); l2.set(n,n,to_string(n));
      VectorLocation v(n+1),r2;
      for(int i=0;i<=n;i++) v._locations[i].set(i*(n+1),i*(n+1),to_string(i));
      r2=v.select(l0,l2);
      EXPECT_EQ(regex_replace(r2.toString(),regex(ENDL)," "),
                string("1 0.000000 0.000000 0 ")); }

    TEST(103, "T02.VectorLocation_select_4")
    { int n=5; Location l1,l2; l1.set(1,1,"1"); l2.set(n,n,to_string(n));
      VectorLocation v(n),r2;
      for(int i=1;i<=n;i++) v._locations[i-1].set(i,i,to_string(i));
      r2=v.select(l1,l2);
      EXPECT_EQ(regex_replace(r2.toString(),regex(ENDL)," "),
                string("5 1.000000 1.000000 1 2.000000 2.000000 2 3.000000 3.000000 3 4.000000 4.000000 4 5.000000 5.000000 5 ")); }

    TEST(104, "T02.VectorLocation_sort_1_no_change")
    { int n=3; Location loc; VectorLocation v(n),sol;
      for(int i=0;i<n;i++){loc.setName(to_string(i));v.at(i)=loc;sol.append(loc);}
      v.sort(); EXPECT_BOOL(sol.toString()==v.toString(), true); }

    TEST(105, "T02.VectorLocation_sort_2")
    { int n=3; Location loc; VectorLocation v(n),sol;
      for(int i=0;i<n;i++){loc.setName(to_string(i));v.at(n-(i+1))=loc;sol.append(loc);}
      v.sort(); EXPECT_BOOL(sol.toString()==v.toString(), true); }

    TEST(106, "T02.VectorLocation_join_intersection_empty_0")
    { int n=5; VectorLocation l1(n),l2(n);
      for(int i=0;i<n;i++){l1._locations[i].set(i,i,to_string(i));
                            l2._locations[i].set((i+1)*n,(i+1)*n,to_string((i+1)*n));}
      l1.join(l2); EXPECT_EQ(l1.getSize(), 10); }

    TEST(107, "T02.VectorLocation_joinShouldRemainEqual_1")
    { int n=5; VectorLocation l1(n),l2(n);
      for(int i=0;i<n;i++){l1._locations[i].set(i,i,to_string(i));
                            l2._locations[i].set(i,i,to_string(i));}
      l1.join(l2); EXPECT_EQ(l1.getSize(), 5); }

    TEST(108, "T02.VectorLocation_joinShouldRemainEqual_2")
    { VectorLocation l1(1),l2(1);
      l1._locations[0].set(37.2,-3.6,"Granada"); l2._locations[0].set(37.2,-3.6,"Granada");
      l1.join(l2);
      EXPECT_EQ(regex_replace(l1.toString(),regex(ENDL)," "),
                string("1 37.200000 -3.600000 Granada ")); }

    TEST(109, "T02.VectorLocation_assign_01")
    { int n=5; Location loc; loc.set(37.2,-3.6,"Granada"); VectorLocation v(n); v.assign(loc);
      EXPECT_EQ(regex_replace(v.toString(),regex(ENDL)," "),
                string("5 37.200000 -3.600000 Granada 37.200000 -3.600000 Granada 37.200000 -3.600000 Granada 37.200000 -3.600000 Granada 37.200000 -3.600000 Granada ")); }

    TEST(110, "T02.VectorLocation_assign_02")
    { int n=5; Location l0,l1; l1.set(37.2,-3.6,"Granada"); VectorLocation v(n);
      for(int i=0;i<5;i++) v._locations[i]=l1;
      v.assign(l0);
      EXPECT_EQ(regex_replace(v.toString(),regex(ENDL)," "),
                string("5 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 ")); }

    TEST(111, "T02.VectorLocation_loadLoad_2")
    { VectorLocation l(1); string ss=string("1 ")+LOCATION_OTHER+" ";
      istringstream ssin(ss); l.load(ssin); ssin.clear(); ssin.str(ss); l.load(ssin);
      EXPECT_EQ(regex_replace(l.toString(),regex(ENDL)," "),
                string("1 37.200000 -3.600000 Granada ")); }

    TEST(112, "T02.VectorLocation_Load_3_exception")
    { VectorLocation l(1); istringstream ss(string("-1 ")+LOCATION_OTHER+" ");
      EXPECT_THROW([&](){ l.load(ss); }, "std::out_of_range"); }

    // --------------------------------------------------------
    // T02 — VectorInt (113-120)
    // --------------------------------------------------------

    TEST(113, "T02.VectorInt_VectorInt_def3")
    { EXPECT_THROW([&](){ VectorInt v(VectorInt::DIM_VECTOR_VALUES+1); },
                   "std::out_of_range"); }

    TEST(114, "T02.VectorInt_append_2_full")
    { VectorInt v(VectorInt::DIM_VECTOR_VALUES);
      EXPECT_THROW([&](){ v.append(7); }, "std::out_of_range"); }

    TEST(115, "T02.VectorInt_VectorInt_def2")
    { VectorInt v(5);
      EXPECT_EQ(regex_replace(v.toString(),regex(ENDL)," "), string("5 0 0 0 0 0 ")); }

    TEST(116, "T02.VectorInt_at_exception0")
    { VectorInt v(2); EXPECT_THROW([&](){ v.at(-1); }, "std::out_of_range"); }

    TEST(117, "T02.VectorInt_at_exception1")
    { VectorInt v(2); EXPECT_THROW([&](){ v.at(2); }, "std::out_of_range"); }

    TEST(118, "T02.VectorInt_distance_fail1")
    { VectorInt v1(3),v2(5);
      EXPECT_THROW([&](){ v1.distance(v2); }, "std::invalid_argument"); }

    TEST(119, "T02.VectorInt_distance_fail2")
    { VectorInt v1,v2;
      EXPECT_THROW([&](){ v1.distance(v2); }, "std::invalid_argument"); }

    TEST(120, "T02.VectorInt_countIdenticalElements2_excep")
    { VectorInt v1(3),v2(2);
      EXPECT_THROW([&](){ v1.countIdenticalElements(v2); }, "std::invalid_argument"); }

    // --------------------------------------------------------
    // T02 — Clustering (121-126)
    // --------------------------------------------------------

    TEST(121, "T02.Clustering_run_0")
    { VectorLocation loc; fill_vlocation(loc,3); Clustering c; c.set(loc,2,12345); c.run();
      string e="K=2 Sum of within-cluster variances: 1.000000 Number of iterations: 2 "
               "Cluster number for each location: 3 0 1 1 Centroids: 2 "
               "0.000000 0.000000 1.500000 1.500000 "
               "Cluster 0 information: 0 0.000000 0.000000 Location0 "
               "Cluster 1 information: 1 1.000000 1.000000 Location1 2 2.000000 2.000000 Location2 ";
      EXPECT_EQ(regex_replace(c.toString(),regex(ENDL)," "), e); }

    TEST(122, "T02.Clustering_clusterOf_AfterRun")
    { VectorLocation loc; fill_vlocation(loc,3); Clustering c; c.set(loc,2,12345); c.run();
      string r=to_string(c.clusterOf(0))+" "+to_string(c.clusterOf(1))+" "+to_string(c.clusterOf(2));
      EXPECT_EQ(r, string("0 1 1")); }

    TEST(123, "T02.Clustering_getSumWCV_AfterRun")
    { VectorLocation loc; fill_vlocation(loc,3); Clustering c; c.set(loc,2,12345); c.run();
      EXPECT_EQ(c.getSumWCV(), 1.0); }

    TEST(124, "T02.Clustering_getNumIterations_AfterRun")
    { VectorLocation loc; fill_vlocation(loc,3); Clustering c; c.set(loc,2,12345); c.run();
      EXPECT_EQ(c.getNumIterations(), 2); }

    TEST(125, "T02.Clustering_clusterInfo1")
    { VectorLocation loc; fill_vlocation(loc,3); Clustering c; c.set(loc,2,12345); c.run();
      EXPECT_EQ(regex_replace(c.clusterInfo(1),regex(ENDL)," "),
                string("1 1.000000 1.000000 Location1 2 2.000000 2.000000 Location2 ")); }

    TEST(126, "T02.Clustering_getStatistics")
    { VectorLocation loc; fill_vlocation(loc,3); Clustering c; c.set(loc,2,12345); c.run();
      EXPECT_EQ(regex_replace(c.getStatistics(),regex(ENDL)," "),
                string("K=2 Sum of within-cluster variances: 1.000000 Number of iterations: 2 ")); }

    // --------------------------------------------------------
    // T02 — ArrayClustering (127-130)
    // --------------------------------------------------------

    TEST(127, "T02.ArrayClustering_Initialize_2")
    { ArrayClustering ac;
      EXPECT_THROW([&](){ InitializeArrayClustering(ac,0); }, "std::out_of_range"); }

    TEST(128, "T02.ArrayClustering_sort_2_no_change")
    { ArrayClustering ac; InitializeArrayClustering(ac,5); ac.size=5;
      for(int i=0;i<5;i++){ac.clustering[i]._K=2;ac.clustering[i]._sumWCV=1.0;
                            ac.clustering[i]._numIterations=10+i;ac.clustering[i]._isDone=true;}
      SortArrayClustering(ac); string r=inspectT(ac); DeallocateArrayClustering(ac);
      string e="capacity: 5 size: 5 List of Clusters: "
        "K=2 Sum of within-cluster variances: 1.000000 Number of iterations: 10 Cluster number for each location: 0 Centroids: 0 Cluster 0 information: Cluster 1 information: "
        "K=2 Sum of within-cluster variances: 1.000000 Number of iterations: 11 Cluster number for each location: 0 Centroids: 0 Cluster 0 information: Cluster 1 information: "
        "K=2 Sum of within-cluster variances: 1.000000 Number of iterations: 12 Cluster number for each location: 0 Centroids: 0 Cluster 0 information: Cluster 1 information: "
        "K=2 Sum of within-cluster variances: 1.000000 Number of iterations: 13 Cluster number for each location: 0 Centroids: 0 Cluster 0 information: Cluster 1 information: "
        "K=2 Sum of within-cluster variances: 1.000000 Number of iterations: 14 Cluster number for each location: 0 Centroids: 0 Cluster 0 information: Cluster 1 information: ";
      EXPECT_EQ(r, e); }

    TEST(129, "T02.ArrayClustering_sort_3_invert")
    { int n=5; ArrayClustering ac,acR; InitializeArrayClustering(ac,n); InitializeArrayClustering(acR,n);
      ac.size=n; acR.size=n;
      for(int i=0;i<n;i++){ac.clustering[n-i-1]._K=2;ac.clustering[n-i-1]._sumWCV=1.0+i;
                            ac.clustering[n-i-1]._numIterations=10;ac.clustering[n-i-1]._isDone=true;}
      SortArrayClustering(ac); string r=inspectT(ac);
      DeallocateArrayClustering(ac); DeallocateArrayClustering(acR);
      string e="capacity: 5 size: 5 List of Clusters: "
        "K=2 Sum of within-cluster variances: 1.000000 Number of iterations: 10 Cluster number for each location: 0 Centroids: 0 Cluster 0 information: Cluster 1 information: "
        "K=2 Sum of within-cluster variances: 2.000000 Number of iterations: 10 Cluster number for each location: 0 Centroids: 0 Cluster 0 information: Cluster 1 information: "
        "K=2 Sum of within-cluster variances: 3.000000 Number of iterations: 10 Cluster number for each location: 0 Centroids: 0 Cluster 0 information: Cluster 1 information: "
        "K=2 Sum of within-cluster variances: 4.000000 Number of iterations: 10 Cluster number for each location: 0 Centroids: 0 Cluster 0 information: Cluster 1 information: "
        "K=2 Sum of within-cluster variances: 5.000000 Number of iterations: 10 Cluster number for each location: 0 Centroids: 0 Cluster 0 information: Cluster 1 information: ";
      EXPECT_EQ(r, e); }

    TEST(130, "T02.ArrayClustering_sort_4_invert")
    { int n=5; ArrayClustering ac,acR; InitializeArrayClustering(ac,n); InitializeArrayClustering(acR,n);
      ac.size=n; acR.size=n;
      for(int i=0;i<n;i++){ac.clustering[n-i-1]._K=2;ac.clustering[n-i-1]._sumWCV=1.0;
                            ac.clustering[n-i-1]._numIterations=10+i;ac.clustering[n-i-1]._isDone=true;}
      SortArrayClustering(ac); string r=inspectT(ac);
      DeallocateArrayClustering(ac); DeallocateArrayClustering(acR);
      string e="capacity: 5 size: 5 List of Clusters: "
        "K=2 Sum of within-cluster variances: 1.000000 Number of iterations: 10 Cluster number for each location: 0 Centroids: 0 Cluster 0 information: Cluster 1 information: "
        "K=2 Sum of within-cluster variances: 1.000000 Number of iterations: 11 Cluster number for each location: 0 Centroids: 0 Cluster 0 information: Cluster 1 information: "
        "K=2 Sum of within-cluster variances: 1.000000 Number of iterations: 12 Cluster number for each location: 0 Centroids: 0 Cluster 0 information: Cluster 1 information: "
        "K=2 Sum of within-cluster variances: 1.000000 Number of iterations: 13 Cluster number for each location: 0 Centroids: 0 Cluster 0 information: Cluster 1 information: "
        "K=2 Sum of within-cluster variances: 1.000000 Number of iterations: 14 Cluster number for each location: 0 Centroids: 0 Cluster 0 information: Cluster 1 information: ";
      EXPECT_EQ(r, e); }
}

// ============================================================
//  MAIN
// ============================================================
int main(int argc, char* argv[]) {

    // Rango de tests (por defecto todos)
    int rangeMin=1, rangeMax=130;
    if (argc==2) { rangeMin=rangeMax=atoi(argv[1]); }
    if (argc==3) { rangeMin=atoi(argv[1]); rangeMax=atoi(argv[2]); }

    system("mkdir -p tests/output");   // necesario para test 44

    run_all_tests();

    // ---- Impresión de resultados ----
    const int W = 48;
    int total=0, passed=0, failed=0;

    cout << "\n" << string(72,'=') << "\n";
    cout << "  RESULTADOS DE TESTS (T01 + T02)";
    if (argc>1) cout << "   filtro: " << rangeMin << "-" << rangeMax;
    cout << "\n" << string(72,'=') << "\n\n";

    for (auto& tr : g_results) {
        if (tr.id < rangeMin || tr.id > rangeMax) continue;
        total++;
        if (tr.passed) {
            passed++;
            cout << "  [" << setw(3) << tr.id << "]  "
                 << left << setw(W) << tr.name
                 << "  \033[32mOK\033[0m\n";
        } else {
            failed++;
            cout << "  [" << setw(3) << tr.id << "]  "
                 << left << setw(W) << tr.name
                 << "  \033[31mFALLO\033[0m\n"
                 << tr.detail << "\n";
        }
    }

    // ---- Resumen ----
    cout << "\n" << string(72,'-') << "\n";
    cout << "  Total : " << total << "\n";
    cout << "  \033[32mOK    : " << passed << "\033[0m\n";
    if (failed > 0)
        cout << "  \033[31mFALLO : " << failed << "\033[0m\n";
    cout << string(72,'=') << "\n\n";

    return (failed==0) ? 0 : 1;
}