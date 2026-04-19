
HAZ <Ctrl+Shift+V>

# Fraud2 - Guía de Configuración y Ejecución

Este documento explica cómo configurar el proyecto **Fraud2** y ejecutar los diferentes scripts.

---

## 1. Crear la Carpeta Build y Configurar CMake

### Paso 1: Crear la carpeta build

Desde el terminal, navega a la carpeta raíz de **Fraud2**:

```bash
cd Fraud2
```

Crea la carpeta `build`:

```bash
mkdir build
```

### Paso 2: Ejecutar CMake

Navega a la carpeta `build`:

```bash
cd build
```

Ejecuta CMake para generar los archivos de compilación:

```bash
cmake ..
```

Este comando:
- Lee el archivo `CMakeLists.txt` de la carpeta padre
- Genera los archivos necesarios para compilar el proyecto (Makefile, etc.)
- Prepara el entorno de compilación

### Paso 3: Compilar el proyecto

Una vez configurado, compila el proyecto:

```bash
make
```

O si prefieres compilar desde VS Code, usa la tarea:
- **C/C++: g++ build active file** (Ctrl+Shift+B)

Al completarse, se generará un ejecutable llamado `Fraud2` en la carpeta `build/`.

---

## 2. Ejecutar los Scripts

Los scripts se encuentran en la carpeta `../Scripts` (carpeta Scripts en la raíz del proyecto).

### Requisitos previos

Antes de ejecutar cualquier script, asegúrate de que:
1. El directorio de trabajo es `../Scripts` (desde la carpeta Fraud2)
2. Los scripts tienen permisos de ejecución

Si es necesario darles permisos:

```bash
cd ../Scripts
chmod +x *.sh
```

### Script 1: settingsIDE.sh

**Propósito:** Configurar la IDE y directorios del proyecto.

**Contenido:**
```bash
./settingsIDE.sh
```

Este script define:
- IDE a usar: VSCODE
- Directorio de proyectos: CodeProjects
- Carpeta de compilación: `build`

**Nota:** Este script es principalmente de configuración y no requiere cambios normalmente.

---

### Script 2: doConfig.sh

**Propósito:** Configurar el proyecto automáticamente.

**Ejecución:**

```bash
./doConfig.sh
```

Este script:
- Lee la configuración de `settingsIDE.sh`
- Navega automáticamente a la carpeta correcta
- Ejecuta CMake si es necesario
- Prepara el proyecto para compilación

---

### Script 3: runTest.sh

**Propósito:** Ejecutar pruebas unitarias del proyecto.

**Ejecución:**

```bash
./runTest.sh
```

Este script:
- Busca archivos de prueba (`.test`)
- Ejecuta las pruebas automáticamente
- Genera un informe de resultados
- Limita la salida a las primeras 15 filas para claridad

**Nota:** Requiere que el proyecto esté compilado previamente.

---

### Script 4: runDocumentation.sh

**Propósito:** Generar documentación del proyecto en formato HTML.

**Ejecución:**

```bash
./runDocumentation.sh
```

Este script:
- Lee los comentarios en el código C++
- Genera documentación automática con Doxygen
- Crea archivos HTML en la carpeta `doc/`
- También puede generar PDF usando LaTeX

**Nota:** Requiere tener instalados `doxygen` y opcionalmente `LaTeX`.

---

### Script 5: runUpdate.sh

**Propósito:** Actualizar los scripts desde el repositorio de GitHub.

**Ejecución:**

```bash
./runUpdate.sh
```

Este script:
- Descarga la última versión de los scripts
- Copia los ficheros nuevos a la carpeta `Scripts`
- Mantiene los scripts sincronizados con el repositorio

**Uso:** Ejecuta este script cuando quieras actualizar los scripts a la versión más reciente.

---

### Script 6: runZipProject.sh

**Propósito:** Crear un archivo comprimido del proyecto.

**Ejecución:**

```bash
./runZipProject.sh
```

Este script:
- Comprime el contenido del proyecto
- Crea un archivo `.zip` en la carpeta `zip/`
- Excluye archivos innecesarios (build, objetos compilados, etc.)

**Resultado:** Se genera un archivo `PRACTICAMP.zip` con todo el proyecto.

---

## 3. Orden Recomendado de Ejecución

Para configurar y compilar el proyecto **por primera vez**:

```bash
# 1. Posiciónate en la carpeta Fraud2
cd Fraud2

# 2. Crea la carpeta build y configura CMake
mkdir build
cd build
cmake ..

# 3. Compila el proyecto
make
cd ..

# 4. Ahora puedes ejecutar los scripts desde ../Scripts
cd ../Scripts

# 5. (Opcional) Ver configuración
./settingsIDE.sh

# 6. (Opcional) Ejecutar pruebas si existen
./runTest.sh

# 7. (Opcional) Generar documentación
./runDocumentation.sh

# 8. (Opcional) Crear archivo comprimido
./runZipProject.sh
```

---

## 4. Información Adicional

- **Carpeta `src/`**: Código fuente del proyecto
- **Carpeta `include/`**: Archivos de encabezado (`.h`)
- **Carpeta `tests/`**: Pruebas unitarias
- **Carpeta `build/`**: Se genera automáticamente (no incluir en Git)
- **Carpeta `doc/`**: Documentación generada

---

## 5. Solución de Problemas

### Error: "cmake: command not found"
Instala CMake:
```bash
sudo apt-get install cmake
```

### Error: "g++: command not found"
Instala el compilador:
```bash
sudo apt-get install g++
```

### Error: "Permission denied" en scripts
Dale permisos de ejecución:
```bash
chmod +x *.sh
```

### Error: "No such file or directory: build"
Asegúrate de crear la carpeta build antes:
```bash
mkdir build
```

---

**Última actualización:** 2026-04-10
