/*
 * Metodología de la Programación
 * Curso 2025/2026
 */
/**
 * @file main.cpp
 * @author estudiante1: Ramírez , Renato
 * @author estudiante2: Verger, Toni
 */
#include <iostream>
#include "Location.h"
#include "VectorLocation.h"
#include "ArrayLocation.h"

// Inclusión de ficheros .h que deben eliminarse tras comprobar los tests de unidad
#include <sstream>
#include <regex>
#include <cmath>
#include <string>

// Macros que deben eliminarse tras comprobar los tests de unidad
#define ENDL "\n"
#define LOCATION_DEFAULT "0.000000 0.000000"
#define LOCATION_OTHER "37.200000 -3.600000 Granada"


using namespace std;

int main(int argc, char *argv[]) {

    // =========================================================
    // T01_Basics.Location_Location_def1
    // Expected: "0.000000 0.000000"
    // =========================================================
    {
        Location loc;
        string s = to_string(0.0) + string(" ") + to_string(0.0);
        cout << "T01-1: " << loc.toString() << endl;
    }

    // =========================================================
    // T01_Basics.Location_get_XY
    // Expected: 0.000000
    // =========================================================
    {
        Location loc;
        cout << "T01-2: " << loc.getX() + loc.getY() + loc.getX() * loc.getY() << endl;
    }

    // =========================================================
    // T01_Basics.Location_getName
    // Expected: ""
    // =========================================================
    {
        Location loc;
        cout << "T01-3: " << loc.getName() << endl;
    }

    // =========================================================
    // T01_Basics.Location_set_Onelocation
    // Expected: "37.200001 -3.600000 Granada"
    // =========================================================
    {
        float f1 = 37.2; float f2 = -3.6; string nam = "Granada";
        Location loc;
        loc.set(f1, f2, nam);
        cout << "T01-4: " << loc.toString() << endl;
    }

    // =========================================================
    // T01_Basics.Location_set_XY
    // Expected: "37.200001 -3.600000"
    // =========================================================
    {
        float f1 = 37.2; float f2 = -3.6;
        Location loc;
        loc.setX(f1); loc.setY(f2);
        cout << "T01-5: " << loc.toString() << endl;
    }

    // =========================================================
    // T01_Basics.Location_setName
    // Expected: "0.000000 0.000000 Granada"
    // =========================================================
    {
        Location loc;
        string name = "Granada";
        loc.setName(name);
        cout << "T01-6: " << loc.toString() << endl;
    }

    // =========================================================
    // T01_Basics.Location_isInsideArea_in0
    // Expected: true (1)
    // =========================================================
    {
        float f1 = 37.2; float f2 = -3.6; float f3 = 39.47; float f4 = -0.37;
        Location loc1; Location loc2;
        loc1.set(f1, f2, ""); loc2.set(f3, f4, "");
        cout << "T01-7: " << loc1.isInsideArea(loc1, loc2) << endl;
    }

    // =========================================================
    // T01_Basics.Location_isInsideArea_in1
    // Expected: true (1)
    // =========================================================
    {
        float f1 = 37.2; float f2 = -3.6; float f3 = 39.47; float f4 = -0.37;
        Location loc1; Location loc2;
        loc1.set(f1, f2, ""); loc2.set(f3, f4, "");
        cout << "T01-8: " << loc2.isInsideArea(loc1, loc2) << endl;
    }

    // =========================================================
    // T01_Basics.Location_isInsideArea_in2
    // Expected: true (1)
    // =========================================================
    {
        float f1 = 37.2; float f2 = -3.6; float f3 = 39.47; float f4 = -0.37;
        Location loc1; Location loc2; Location loc3;
        loc1.set(f1, f2, ""); loc2.set(f3, f4, ""); loc3.set(f1 + 0.2, f2 + 0.2, "");
        cout << "T01-9: " << loc3.isInsideArea(loc1, loc2) << endl;
    }

    // =========================================================
    // T01_Basics.Location_isInsideArea_out0
    // Expected: false (0)
    // =========================================================
    {
        float f1 = 37.2; float f2 = -3.6; float f3 = 39.47; float f4 = -0.37;
        Location loc1; Location loc2; Location loc3;
        loc1.set(f1, f2, ""); loc2.set(f3, f4, ""); loc3.set(f3 + 0.2, f4, "");
        cout << "T01-10: " << loc3.isInsideArea(loc1, loc2) << endl;
    }

    // =========================================================
    // T01_Basics.Location_isInsideArea_out1
    // Expected: false (0)
    // =========================================================
    {
        float f1 = 37.2; float f2 = -3.6; float f3 = 39.47; float f4 = -0.37;
        Location loc1; Location loc2; Location loc3;
        loc1.set(f1, f2, ""); loc2.set(f3, f4, ""); loc3.set(f3, f4 + 0.2, "");
        cout << "T01-11: " << loc3.isInsideArea(loc1, loc2) << endl;
    }

    // =========================================================
    // T01_Basics.Location_isInsideArea_out2
    // Expected: false (0)
    // =========================================================
    {
        float f1 = 37.2; float f2 = -3.6; float f3 = 39.47; float f4 = -0.37;
        Location loc1; Location loc2; Location loc3;
        loc1.set(f1, f2, ""); loc2.set(f3, f4, ""); loc3.set(f1 - 0.2, f2, "");
        cout << "T01-12: " << loc3.isInsideArea(loc1, loc2) << endl;
    }

    // =========================================================
    // T01_Basics.Location_isInsideArea_out3
    // Expected: false (0)
    // =========================================================
    {
        float f1 = 37.2; float f2 = -3.6; float f3 = 39.47; float f4 = -0.37;
        Location loc1; Location loc2; Location loc3;
        loc1.set(f1, f2, ""); loc2.set(f3, f4, ""); loc3.set(f1, f2 - 0.2, "");
        cout << "T01-13: " << loc3.isInsideArea(loc1, loc2) << endl;
    }

    // =========================================================
    // T01_Basics.Location_squaredDistance_l0
    // Expected: 0.000000
    // =========================================================
    {
        float f1 = 37.2; float f2 = -3.6;
        Location loc1; loc1.set(f1, f2, "");
        cout << "T01-14: " << loc1.squaredDistance(loc1) << endl;
    }

    // =========================================================
    // T01_Basics.Location_squaredDistance_l1
    // Expected: 8.000000
    // =========================================================
    {
        Location loc1; Location loc2;
        loc2.set(2.0, 2.0, "");
        cout << "T01-15: " << loc1.squaredDistance(loc2) << endl;
    }

    // =========================================================
    // T01_Basics.Location_distance_l0
    // Expected: 0.000000
    // =========================================================
    {
        float f1 = 37.2; float f2 = -3.6;
        Location loc1; loc1.set(f1, f2, "");
        cout << "T01-16: " << loc1.distance(loc1) << endl;
    }

    // =========================================================
    // T01_Basics.Location_distance_l1
    // Expected: 2.828427
    // =========================================================
    {
        Location loc1; Location loc2;
        loc2.set(2.0, 2.0, "");
        double r = sqrt(8.0);
        cout << "T01-17: " << loc1.distance(loc2) << endl;
    }

    // =========================================================
    // T01_Basics.Location_distance_l2
    // Expected: 2.828427
    // =========================================================
    {
        Location loc1; Location loc2;
        loc2.set(2.0, 2.0, "");
        double r = sqrt(8.0);
        cout << "T01-18: " << loc2.distance(loc1) << endl;
    }

    // =========================================================
    // T01_Basics.Location_load_0
    // Expected: "37.200000 -3.600000"
    // =========================================================
    {
        Location loc;
        const string LOCATION_OTHER_LOCAL = "37.200000 -3.600000";
        istringstream ssin(LOCATION_OTHER_LOCAL);
        loc.load(ssin);
        cout << "T01-19: " << loc.toString() << endl;
    }

    // =========================================================
    // T01_Basics.Location_load_1
    // Expected: "37.200000 -3.600000 Granada"
    // =========================================================
    {
        Location loc;
        const string LOCATION_OTHER_LOCAL = "37.200000 -3.600000 Granada";
        istringstream ssin(LOCATION_OTHER_LOCAL);
        loc.load(ssin);
        cout << "T01-20: " << loc.toString() << endl;
    }

    // =========================================================
    // T01_Basics.VectorLocation_getCapacity
    // Expected: 100
    // =========================================================
    {
        VectorLocation vloc;
        vloc._size = 2;
        cout << "T01-21: " << vloc.getCapacity() << endl;
    }

    // =========================================================
    // T01_Basics.VectorLocation_getCapacity2
    // Expected: 100
    // =========================================================
    {
        int n = 10;
        VectorLocation vloc(n);
        vloc._size = 2;
        cout << "T01-22: " << vloc.getCapacity() << endl;
    }

    // =========================================================
    // T01_Basics.VectorLocation_Clear_1
    // Expected: 0
    // =========================================================
    {
        VectorLocation vloc;
        vloc._size = VectorLocation::DIM_VECTOR_LOCATIONS;
        vloc.clear();
        cout << "T01-23: " << vloc.getSize() << endl;
    }

    // =========================================================
    // T01_Basics.VectorLocation_VectorLocation_def3
    // Expected: 100
    // =========================================================
    {
        VectorLocation vloc(VectorLocation::DIM_VECTOR_LOCATIONS);
        cout << "T01-24: " << vloc._size << endl;
    }

    // =========================================================
    // T01_Basics.VectorLocation_VectorLocation_def1
    // Expected: "0 "
    // =========================================================
    {
        VectorLocation vloc;
        cout << "T01-25: " << std::regex_replace(vloc.toString(), std::regex(ENDL), " ") << endl;
    }

    // =========================================================
    // T01_Basics.VectorLocation_VectorLocation_def2
    // Expected: "1 0.000000 0.000000 "
    // =========================================================
    {
        string s = "1 " + string(LOCATION_DEFAULT) + " ";
        VectorLocation vloc(1);
        cout << "T01-26: " << std::regex_replace(vloc.toString(), std::regex(ENDL), " ") << endl;
    }

    // =========================================================
    // T01_Basics.VectorLocation_getSize0
    // Expected: 0
    // =========================================================
    {
        VectorLocation vloc;
        cout << "T01-27: " << vloc.getSize() << endl;
    }

    // =========================================================
    // T01_Basics.VectorLocation_getSize1
    // Expected: 2
    // =========================================================
    {
        VectorLocation vloc(2);
        cout << "T01-28: " << vloc.getSize() << endl;
    }

    // =========================================================
    // T01_Basics.VectorLocation_toString
    // Expected: "2 0.000000 0.000000 37.200000 -3.600000 Granada "
    // =========================================================
    {
        string s = "2 " + string(LOCATION_DEFAULT) + " " + string(LOCATION_OTHER) + " ";
        Location loc1; Location loc2;
        loc2.set(37.2, -3.6, "Granada");
        VectorLocation vloc(2);
        vloc._locations[0] = loc1;
        vloc._locations[1] = loc2;
        cout << "T01-29: " << std::regex_replace(vloc.toString(), std::regex(ENDL), " ") << endl;
    }

    // =========================================================
    // T01_Basics.VectorLocation_Clear_0
    // Expected: 0
    // =========================================================
    {
        VectorLocation vloc;
        vloc.clear();
        cout << "T01-30: " << vloc.getSize() << endl;
    }

    // =========================================================
    // T01_Basics.VectorLocation_append_0
    // Expected: "1 37.200000 -3.600000 Granada "
    // =========================================================
    {
        Location loc;
        loc.set(37.2, -3.6, "Granada");
        VectorLocation vloc;
        vloc.append(loc);
        cout << "T01-31: " << std::regex_replace(vloc.toString(), std::regex(ENDL), " ") << endl;
    }

    // =========================================================
    // T01_Basics.VectorLocation_append_1
    // Expected: "2 0.000000 0.000000 37.200000 -3.600000 Granada "
    // =========================================================
    {
        Location loc1; Location loc2;
        loc2.set(37.2, -3.6, "Granada");
        VectorLocation vloc;
        vloc.append(loc1); vloc.append(loc2);
        cout << "T01-32: " << std::regex_replace(vloc.toString(), std::regex(ENDL), " ") << endl;
    }

    // =========================================================
    // T01_Basics.VectorLocation_at_0
    // Expected: "0.000000 0.000000"
    // =========================================================
    {
        VectorLocation vloc(2);
        cout << "T01-33: " << vloc.at(0).toString() << endl;
    }

    // =========================================================
    // T01_Basics.VectorLocation_at_1
    // Expected: "0.000000 0.000000"
    // =========================================================
    {
        VectorLocation vloc(2);
        cout << "T01-34: " << vloc.at(1).toString() << endl;
    }

    // =========================================================
    // T01_Basics.VectorLocation_at_2
    // Expected: "37.200000 -3.600000 Granada"
    // =========================================================
    {
        Location loc; VectorLocation vloc(2);
        loc.set(37.2, -3.6, "Granada");
        vloc.at(0) = loc;
        cout << "T01-35: " << vloc.at(0).toString() << endl;
    }

    // =========================================================
    // T01_Basics.VectorLocation_at_3
    // Expected: "37.200000 -3.600000 Granada"
    // =========================================================
    {
        Location loc; VectorLocation vloc(2);
        loc.set(37.2, -3.6, "Granada");
        vloc.at(1) = loc;
        cout << "T01-36: " << vloc.at(1).toString() << endl;
    }

    // =========================================================
    // T01_Basics.VectorLocation_findLocation_0
    // Expected: -1
    // =========================================================
    {
        Location loc; VectorLocation vloc;
        cout << "T01-37: " << vloc.findLocation(loc) << endl;
    }

    // =========================================================
    // T01_Basics.VectorLocation_findLocation_1
    // Expected: 0
    // =========================================================
    {
        Location loc1; Location loc2;
        loc2.set(37.2, -3.6, "Granada");
        VectorLocation vloc(2);
        vloc._locations[0] = loc2;
        cout << "T01-38: " << vloc.findLocation(loc2) << endl;
    }

    // =========================================================
    // T01_Basics.VectorLocation_findLocation_2
    // Expected: 1
    // =========================================================
    {
        Location loc1; Location loc2;
        loc2.set(37.2, -3.6, "Granada");
        VectorLocation vloc(2);
        vloc._locations[1] = loc2;
        cout << "T01-39: " << vloc.findLocation(loc2) << endl;
    }

    // =========================================================
    // T01_Basics.VectorLocation_findLocation_3
    // Expected: -1
    // =========================================================
    {
        Location loc;
        loc.setName("OTHER");
        VectorLocation vloc(5);
        cout << "T01-40: " << vloc.findLocation(loc) << endl;
    }

    // =========================================================
    // T02_Intermediate.VectorLocation_VectorLocation_def4
    // Expected: THROWS std::out_of_range
    // =========================================================
    {
        try {
            VectorLocation vloc(VectorLocation::DIM_VECTOR_LOCATIONS + 1);
            cout << "T02-41: FAIL (no exception thrown)" << endl;
        } catch (const std::out_of_range& e) {
            cout << "T02-41: OK (out_of_range thrown)" << endl;
        }
    }

    // =========================================================
    // T02_Intermediate.VectorLocation_findLocation_4
    // Expected: 99
    // =========================================================
    {
        Location loc;
        loc.setName("OTHER");
        VectorLocation vloc(VectorLocation::DIM_VECTOR_LOCATIONS);
        vloc._locations[VectorLocation::DIM_VECTOR_LOCATIONS - 1] = loc;
        cout << "T02-42: " << vloc.findLocation(loc) << endl;
    }

    // =========================================================
    // T02_Intermediate.VectorLocation_out_of_range__append_4
    // Expected: 100 (size stays at DIM when duplicate)
    // =========================================================
    {
        Location loc;
        loc.set(37.2, -3.6, "Granada");
        VectorLocation vloc;
        vloc._size = VectorLocation::DIM_VECTOR_LOCATIONS;
        vloc._locations[0] = loc;
        vloc.append(loc);
        cout << "T02-43: " << vloc._size << endl;
    }

    // =========================================================
    // T02_Intermediate.VectorLocation_out_of_range__append_5
    // Expected: THROWS std::out_of_range
    // =========================================================
    {
        try {
            Location loc;
            loc.set(0, 0, "Terrace");
            VectorLocation vloc;
            vloc._size = VectorLocation::DIM_VECTOR_LOCATIONS;
            vloc.append(loc);
            cout << "T02-44: FAIL (no exception thrown)" << endl;
        } catch (const std::out_of_range& e) {
            cout << "T02-44: OK (out_of_range thrown)" << endl;
        }
    }

    // =========================================================
    // T02_Intermediate.VectorLocation_VectorLocation_def5
    // Expected: THROWS std::out_of_range
    // =========================================================
    {
        try {
            VectorLocation vloc(-1);
            cout << "T02-45: FAIL (no exception thrown)" << endl;
        } catch (const std::out_of_range& e) {
            cout << "T02-45: OK (out_of_range thrown)" << endl;
        }
    }

    // =========================================================
    // T02_Intermediate.VectorLocation_append_2  (duplicate not added)
    // Expected: "1 37.200000 -3.600000 Granada "
    // =========================================================
    {
        Location loc;
        loc.set(37.2, -3.6, "Granada");
        VectorLocation vloc;
        vloc.append(loc); vloc.append(loc);
        cout << "T02-46: " << std::regex_replace(vloc.toString(), std::regex(ENDL), " ") << endl;
    }

    // =========================================================
    // T02_Intermediate.VectorLocation_at_exception0
    // Expected: THROWS std::out_of_range
    // =========================================================
    {
        try {
            VectorLocation vloc(2);
            vloc.at(-1).toString();
            cout << "T02-47: FAIL (no exception thrown)" << endl;
        } catch (const std::out_of_range& e) {
            cout << "T02-47: OK (out_of_range thrown)" << endl;
        }
    }

    // =========================================================
    // T02_Intermediate.VectorLocation_at_exception1
    // Expected: THROWS std::out_of_range
    // =========================================================
    {
        try {
            VectorLocation vloc(2);
            vloc.at(2).toString();
            cout << "T02-48: FAIL (no exception thrown)" << endl;
        } catch (const std::out_of_range& e) {
            cout << "T02-48: OK (out_of_range thrown)" << endl;
        }
    }

    // =========================================================
    // T02_Intermediate.VectorLocation_select_0
    // Expected: 0
    // =========================================================
    {
        int n = 5;
        Location loc0; Location loc1; Location loc2;
        loc1.set(1, 1, "1"); loc2.set(n, n, std::to_string(n));
        VectorLocation l1(n); VectorLocation l2;
        for (int i = 1; i <= n; i++) {
            l1._locations[i-1].set(-i, i, std::to_string(i));
        }
        l2 = l1.select(loc0, loc2);
        cout << "T02-49: " << l2._size << endl;
    }

    // =========================================================
    // T02_Intermediate.VectorLocation_select_1
    // Expected: 5
    // =========================================================
    {
        int sizeOriginal = 5;
        Location loc1; Location loc2;
        loc2.set(sizeOriginal, sizeOriginal, std::to_string(sizeOriginal));
        VectorLocation l1(sizeOriginal); VectorLocation l2;
        for (int i = 1; i <= sizeOriginal; i++) {
            l1._locations[i-1].set(i, i, std::to_string(i));
        }
        l2 = l1.select(loc1, loc2);
        cout << "T02-50: " << l2._size << endl;
    }

    // =========================================================
    // T02_Intermediate.VectorLocation_select_2
    // Expected: 1
    // =========================================================
    {
        int n = 5;
        Location loc0; Location loc1; Location loc2;
        loc1.set(1.0, 1.0, "1"); loc2.set(n, n, std::to_string(n));
        VectorLocation l1(n+1); VectorLocation l2;
        for (int i = 0; i <= n; i++) {
            l1._locations[i].set(i*(n+1), i*(n+1), std::to_string(i));
        }
        l2 = l1.select(loc0, loc2);
        cout << "T02-51: " << l2._size << endl;
    }

    // =========================================================
    // T02_Intermediate.VectorLocation_select_3
    // Expected: "1 0.000000 0.000000 0 "
    // =========================================================
    {
        int n = 5;
        Location loc0; Location loc1; Location loc2;
        loc0.set(0, 0, "0"); loc1.set(1, 1, "1"); loc2.set(n, n, std::to_string(n));
        VectorLocation l1(n+1); VectorLocation l2; VectorLocation sol;
        sol.append(loc0);
        for (int i = 0; i <= n; i++) {
            l1._locations[i].set(i*(n+1), i*(n+1), std::to_string(i));
        }
        l2 = l1.select(loc0, loc2);
        cout << "T02-52: " << std::regex_replace(l2.toString(), std::regex(ENDL), " ") << endl;
    }

    // =========================================================
    // T02_Intermediate.VectorLocation_select_4
    // Expected: "5 1.000000 1.000000 1 2.000000 2.000000 2 3.000000 3.000000 3 4.000000 4.000000 4 5.000000 5.000000 5 "
    // =========================================================
    {
        int sizeOriginal = 5;
        Location loc0; Location loc1; Location loc2;
        loc1.set(1, 1, "1"); loc2.set(sizeOriginal, sizeOriginal, std::to_string(sizeOriginal));
        VectorLocation l1(sizeOriginal); VectorLocation l2; VectorLocation sol;
        for (int i = 1; i <= sizeOriginal; i++) {
            l1._locations[i-1].set(i, i, std::to_string(i));
            sol.append(l1._locations[i-1]);
        }
        l2 = l1.select(loc1, loc2);
        cout << "T02-53: " << std::regex_replace(l2.toString(), std::regex(ENDL), " ") << endl;
    }

    // =========================================================
    // T02_Intermediate.VectorLocation_sort_1_no_change
    // Expected: true (1)
    // =========================================================
    {
        int sizeOriginal = 3;
        Location loc;
        VectorLocation l1(sizeOriginal); VectorLocation sol;
        for (int i = 0; i < sizeOriginal; i++) {
            loc.setName(std::to_string(i));
            l1.at(i) = loc;
            sol.append(loc);
        }
        l1.sort();
        cout << "T02-54: " << (sol.toString() == l1.toString()) << endl;
    }

    // =========================================================
    // T02_Intermediate.VectorLocation_sort_2
    // Expected: true (1)
    // =========================================================
    {
        int sizeOriginal = 3;
        Location loc;
        VectorLocation l1(sizeOriginal); VectorLocation sol;
        for (int i = 0; i < sizeOriginal; i++) {
            loc.setName(std::to_string(i));
            l1.at(sizeOriginal - (i+1)) = loc;
            sol.append(loc);
        }
        l1.sort();
        cout << "T02-55: " << (sol.toString() == l1.toString()) << endl;
    }

    // =========================================================
    // T02_Intermediate.VectorLocatioin_join_intersection_empy_0
    // Expected: 10
    // =========================================================
    {
        int n = 5;
        VectorLocation l1(n); VectorLocation l2(n);
        for (int i = 0; i < n; i++) {
            l1._locations[i].set(i, i, std::to_string(i));
            l2._locations[i].set((i+1)*n, (i+1)*n, std::to_string((i+1)*n));
        }
        l1.join(l2);
        cout << "T02-56: " << l1.getSize() << endl;
    }

    // =========================================================
    // T02_Intermediate.VectorLocatioin_joinShouldRemainEqual_1
    // Expected: 5
    // =========================================================
    {
        int n = 5;
        VectorLocation l1(n); VectorLocation l2(n);
        for (int i = 0; i < n; i++) {
            l1._locations[i].set(i, i, std::to_string(i));
            l2._locations[i].set(i, i, std::to_string(i));
        }
        l1.join(l2);
        cout << "T02-57: " << l1.getSize() << endl;
    }

    // =========================================================
    // T02_Intermediate.VectorLocatioin_joinShouldRemainEqual_2
    // Expected: "1 37.200000 -3.600000 Granada "
    // =========================================================
    {
        VectorLocation l1(1); VectorLocation l2(1);
        l1._locations[0].set(37.2, -3.6, "Granada");
        l2._locations[0].set(37.2, -3.6, "Granada");
        l1.join(l2);
        cout << "T02-58: " << std::regex_replace(l1.toString(), std::regex(ENDL), " ") << endl;
    }

    // =========================================================
    // T02_Intermediate.ArrayLocation_ToArrayLocation_0
    // Expected: "10 0.000000 0.000000 0 1.000000 ... "
    // =========================================================
    {
        const int DIM = 10;
        Location array[DIM];
        int n = 5; int size = 0;
        VectorLocation l1(DIM); VectorLocation l2(DIM);
        for (int i = 0; i < n; i++) {
            l1._locations[i].set(i, i, std::to_string(i));
        }
        ToArrayLocation(l1, array, DIM, size);
        for (int i = 0; i < size; i++) {
            l2._locations[i] = array[i];
        }
        cout << "T02-59: " << std::regex_replace(l2.toString(), std::regex(ENDL), " ") << endl;
    }

    // =========================================================
    // T02_Intermediate.ArrayLocation_ToArrayLocation_1
    // Expected: THROWS std::invalid_argument
    // =========================================================
    {
        try {
            const int DIM = 10;
            Location array[DIM];
            int n = 5; int size = 0;
            VectorLocation l1(DIM);
            for (int i = 0; i < n; i++) {
                l1._locations[i].set(i, i, std::to_string(i));
            }
            ToArrayLocation(l1, array, n, size);
            cout << "T02-60: FAIL (no exception thrown)" << endl;
        } catch (const std::invalid_argument& e) {
            cout << "T02-60: OK (invalid_argument thrown)" << endl;
        }
    }

    // =========================================================
    // T02_Intermediate.ArrayLocation_ToVectorLocation_0
    // Expected: "5 0.000000 0.000000 0 1.000000 1.000000 1 ... "
    // =========================================================
    {
        const int DIM = 10;
        Location array[DIM];
        int n = 5; int size = 0;
        VectorLocation l1(n); VectorLocation l2;
        for (int i = 0; i < n; i++) {
            l1._locations[i].set(i, i, std::to_string(i));
            array[i] = l1._locations[i];
        }
        size = n;
        l2 = ToVectorLocation(array, size);
        cout << "T02-61: " << std::regex_replace(l2.toString(), std::regex(ENDL), " ") << endl;
    }

    // =========================================================
    // T02_Intermediate.ArrayLocation_ToVectorLocation_1
    // Expected: THROWS std::out_of_range
    // =========================================================
    {
        try {
            const int DIM = 10;
            Location array[DIM];
            int n = 5; int size = -1;
            VectorLocation l1(n);
            for (int i = 0; i < n; i++) {
                l1._locations[i].set(i, i, std::to_string(i));
                array[i] = l1._locations[i];
            }
            ToVectorLocation(array, size);
            cout << "T02-62: FAIL (no exception thrown)" << endl;
        } catch (const std::out_of_range& e) {
            cout << "T02-62: OK (out_of_range thrown)" << endl;
        }
    }

    return 0;

    /*
     * Código de la práctica Fraud, temporalmente comentado
     *
    const int MAX_NLOCATIONS = 20;
    Location bottomLeft1, topRight1, bottomLeft2, topRight2;
    VectorLocation locations, selectedLocations1, selectedLocations2;
    Location arrayLocations[MAX_NLOCATIONS], arrayUnionLocations[MAX_NLOCATIONS];
    int nLocs, nUnionLocs;
    bottomLeft1.load(cin);
    topRight1.load(cin);
    bottomLeft2.load(cin);
    topRight2.load(cin);
    ReadArrayLocation(arrayLocations, MAX_NLOCATIONS, nLocs);
    locations = ToVectorLocation(arrayLocations, nLocs);
    selectedLocations1 = locations.select(bottomLeft1, topRight1);
    selectedLocations2 = locations.select(bottomLeft2, topRight2);
    selectedLocations1.join(selectedLocations2);
    selectedLocations1.sort();
    ToArrayLocation(selectedLocations1, arrayUnionLocations, MAX_NLOCATIONS, nUnionLocs);
    PrintArrayLocation(arrayUnionLocations, nUnionLocs);
    return 0;
    */
}