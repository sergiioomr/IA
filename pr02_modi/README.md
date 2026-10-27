# Práctica: Algoritmo Genético para el Permutation Flow Shop Problem (PFSP)

Este proyecto implementa una solución al problema del *Permutation Flow Shop Scheduling Problem* (PFSP) mediante tres enfoques: una Búsqueda Aleatoria, la heurística determinista NEH y un Algoritmo Genético (AG) canónico.

---

## 1. Estructura del Proyecto
``` text
.
├── README.md               # Instrucciones de compilación y ejecución
├── CMakeLists.txt          # Archivo de configuración de CMake
├── src/                    # Archivos de código fuente (.cc)
├── include/                # Archivos de cabecera (.h)
├── test/                   # Instancias de prueba del benchmark (.fsp)
├── script_t6.sh            # Script que ejecuta el programa para poder obtener los datos de la tabla de la Tarea 6
├── docs/                   # Documentación adicional
    ├── results_t5.txt      # Resultados obtenidos en la tarea 5 para la elección de parámetros
    ├── grafica_tai50.csv   # Datos usados para generar las gráficas de convergencia
    ├── grafica_tai100.csv  # Datos usados para generar las gráficas de covergencia
    ├── Guión_Práctica      # Guión de la práctica
    ├── DocumentoAnalisis   # Documento donde se incluyen las gráficas, la tabla y las conclusiones de la práctica
    └── tabla_t6.csv        # Resultados obtenidos para la generación de la tabla y gráficas de la T6    
└── build/                  # Carpeta de compilación y salida de resultados
    └── PFSP                # Ejecutable generado
```
## 2. Instrucciones de Compilación (CMake)

El proyecto utiliza **CMake** para la gestión del proceso de construcción. Todo el proceso de compilación se realiza de forma aislada dentro de la carpeta `build/`.

### Pasos para compilar el proyecto:

1. **Crear e ingresar a la carpeta de compilación** (desde la raíz del proyecto):
   ```bash
   mkdir -p build && cd build
   ```

2. **Generar los archivos de compilación (Makefile) con CMake**:
   ```bash
   cmake ..
   ```

3. **Compilar el código fuente**:
   ```bash
   make
   ```

Tras completar el proceso, el ejecutable **`PFSP`** quedará generado y listo para su uso dentro del directorio `build/`.

---
## 3. Instrucciones de Ejecución Manual

El ejecutable `PFSP` recibe los parámetros por línea de comandos en el siguiente orden:

```bash
./PFSP <fichero_instancia> <N> <Pc> <Pm> <k> <max_evaluaciones> [semilla]
```

### Descripción de Parámetros:
1. `<fichero_instancia>`: Ruta al archivo `.fsp` (ej. `../test/tai20_5_1.fsp`).
2. `<N>`: Tamaño de la población del Algoritmo Genético (ej. `50`).
3. `<Pc>`: Probabilidad de cruce en porcentaje. Debe ser un entero en el rango 0-100 (ej. `80`).
4. `<Pm>`: Probabilidad de mutación en porcentaje. Debe ser un entero en el rango 0-100 (ej. `10`).
5. `<k>`: Tamaño del torneo para la selección (ej. `2`).
6. `<max_evaluaciones>`: Presupuesto máximo de evaluaciones (ej. `50000`).
7. `[semilla]` *(opcional)*: Semilla para el generador aleatorio. Si se omite, usa la semilla por defecto de la instancia.

### Ejemplo de uso (ejecutando desde la carpeta `build/`):

```bash
cd build
./PFSP ../test/tai50_10_1.fsp 50 80 10 2 50000 123456
```

---

## 4. Ejecución Automatizada (Tarea 6)

Para lanzar la batería completa de experimentos de la Tarea 6 (12 instancias representativas con 10 semillas independientes cada una):

```bash
# Desde la raíz del proyecto
chmod +x script_t6.sh
./script_t6.sh
```

El script ejecutará automáticamente las iteraciones llamando al ejecutable `build/PFSP` y guardará la tabla consolidada en `build/resultados_tarea6.csv`.

---