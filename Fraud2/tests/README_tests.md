# Instrucciones para usar los tests de unidad

## Archivos generados

| Archivo | Descripción |
|---|---|
| `main_tests.cpp` | main con los 130 tests de unidad (T01 + T02) comentados |
| `VectorLocation.h` | Versión modificada con guard `-DTESTING` |
| `VectorInt.h` | Versión modificada con guard `-DTESTING` |
| `Clustering.h` | Versión modificada con guard `-DTESTING` |

---

## Pasos para probar un test

### 1. Reemplaza los `.h` en tu proyecto

Copia los tres `.h` generados encima de los originales. La única diferencia con los originales es:

- `DIM_VECTOR_LOCATIONS` y `DIM_VECTOR_VALUES` pasan a ser **públicos** (antes eran privados), para que los tests puedan usar `VectorLocation::DIM_VECTOR_LOCATIONS`.
- Los miembros `_size`, `_values`, `_locations`, `_K`, `_sumWCV`, etc. se exponen como públicos **solo cuando compilas con `-DTESTING`**.

### 2. Reemplaza `main.cpp` por `main_tests.cpp`

```bash
cp main_tests.cpp main.cpp
```

### 3. Descomenta el test que quieras probar

En `main.cpp`, localiza el bloque del test (por número) y quita los `/* ... */` que lo rodean.  
**Solo descomenta un test a la vez** (los demás deben permanecer comentados).

### 4. Compila con `-DTESTING`

```bash
g++ -DTESTING -std=c++17 -o build/Fraud2_test \
    main.cpp Location.cpp VectorLocation.cpp VectorInt.cpp \
    Clustering.cpp ArrayClustering.cpp
```

O con tu `Makefile` añadiendo `-DTESTING` a `CXXFLAGS`:

```makefile
CXXFLAGS += -DTESTING
```

### 5. Crea el directorio de salida para el test 44

El test T01-44 guarda un fichero temporal, necesita que exista la carpeta:

```bash
mkdir -p tests/output
```

### 6. Ejecuta

```bash
./build/Fraud2_test
```

Verás algo como:
```
[T01-1 Location_Location_def1]
  Resultado : 0.000000 0.000000
  Esperado  : 0.000000 0.000000
  => OK
```

---

## Referencia rápida de tests

| Nº | Nombre | Tipo |
|---|---|---|
| 1–20 | Location | valores / carga |
| 21–46 | VectorLocation | básico + carga |
| 47–63 | VectorInt | básico |
| 64–75 | Clustering | básico + set |
| 76–89 | ArrayClustering | básico |
| 90–112 | VectorLocation | intermedio + excepciones |
| 113–120 | VectorInt | intermedio + excepciones |
| 121–126 | Clustering | intermedio (run) |
| 127–130 | ArrayClustering | intermedio + sort |
| 131–141 | Integración (T03) | se prueban con el `main.cpp` original |

> Los tests T03 (integración) usan el `main.cpp` original con argumentos de línea de comandos; no están en `main_tests.cpp`.

---

## Notas importantes

- `inspectT()` **no existe** en vuestras clases. En `main_tests.cpp` ya está sustituida por `toString()` en todos los tests.  
- La función libre `inspectT(ArrayClustering&)` sí está definida en `main_tests.cpp`.
- `refill_vlocation` es igual que `fill_vlocation` pero llama a `clear()` primero; también está definida en `main_tests.cpp`.
- Los tests que acceden directamente a `vloc._size`, `v._values[i]`, `clt._K`, etc. **requieren `-DTESTING`** para compilar.
