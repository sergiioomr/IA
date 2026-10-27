#!/usr/bin/env bash

# ==============================================================================
# Script de automatización para la Tarea 6
# ==============================================================================

# 1. Configuración de parámetros
EXECUTABLE="./PFSP"   # Nombre de tu ejecutable
N=50
PC=80
PM=10
K=2                      # Valor del parámetro k (ej. tamaño del torneo)
MAX_EVAL=50000
INST_DIR="../test"       # Carpeta donde están las instancias
OUTPUT_CSV="resultados_tarea6.csv"

# 2. Las 12 instancias representativas (una por cada tamaño)
INSTANCIAS=(
  "tai20_5_1.fsp"
  "tai20_10_1.fsp"
  "tai20_20_1.fsp"
  "tai50_5_1.fsp"
  "tai50_10_1.fsp"
  "tai50_20_1.fsp"
  "tai100_5_1.fsp"
  "tai100_10_1.fsp"
  "tai100_20_1.fsp"
  "tai200_10_1.fsp"
  "tai200_20_1.fsp"
  "tai500_20_1.fsp"
)

# 3. Crear o sobrescribir el archivo CSV con la cabecera
echo "Instancia;NEH_Makespan;RS_Min;RS_Media;AG_Min;AG_Media" > "$OUTPUT_CSV"

echo "Iniciando experimentos de la Tarea 6..."
echo "--------------------------------------------------------"

# 4. Bucle principal sobre las instancias
for inst in "${INSTANCIAS[@]}"; do
  filepath="${INST_DIR}/${inst}"

  if [ ! -f "$filepath" ]; then
    echo "Aviso: No se encontró el fichero '$filepath'. Saltando..."
    continue
  fi

  echo "Procesando: $inst"

  rs_sum=0
  ag_sum=0
  rs_min=999999999
  ag_min=999999999
  neh_makespan=0

  # 10 ejecuciones independientes
  for i in $(seq 1 10); do
    # Generar una semilla distinta para cada ejecución
    SEED=$((123456 + i * 100))
    # Ejecución pasando los 6 argumentos requeridos por tu main:
    # argv[1]=filepath, argv[2]=N, argv[3]=Pc, argv[4]=Pm, argv[5]=k, argv[6]=max_evaluations
    output=$("$EXECUTABLE" "$filepath" "$N" "$PC" "$PM" "$K" "$MAX_EVAL" "$SEED")

    # Extraer los makespans parseando exactamente los std::cout de tu main.cc
    rs_m=$(echo "$output" | grep "búsqueda aleatoria" | awk -F'Makespan = ' '{print $2}' | tr -d ' \r\t')
    neh_m=$(echo "$output" | grep "heurístico NEH" | awk -F'Makespan = ' '{print $2}' | tr -d ' \r\t')
    ag_m=$(echo "$output" | grep "genético" | awk -F'Makespan = ' '{print $2}' | tr -d ' \r\t')

    # Valores por defecto de seguridad si por alguna razón falla la extracción
    rs_m=${rs_m:-0}
    neh_m=${neh_m:-0}
    ag_m=${ag_m:-0}

    neh_makespan=$neh_m

    # Acumular y calcular mínimos para Búsqueda Aleatoria (RS)
    if [ "$rs_m" -gt 0 ]; then
      rs_sum=$((rs_sum + rs_m))
      if [ "$rs_m" -lt "$rs_min" ]; then rs_min=$rs_m; fi
    fi

    # Acumular y calcular mínimos para Algoritmo Genético (AG)
    if [ "$ag_m" -gt 0 ]; then
      ag_sum=$((ag_sum + ag_m))
      if [ "$ag_m" -lt "$ag_min" ]; then ag_min=$ag_m; fi
    fi
  done

  # Calcular las medias con precisión decimal
  rs_avg=$(awk "BEGIN {printf \"%.2f\", $rs_sum / 10}")
  ag_avg=$(awk "BEGIN {printf \"%.2f\", $ag_sum / 10}")

  # Guardar la fila con el resumen acumulado en el archivo CSV
  echo "${inst};${neh_makespan};${rs_min};${rs_avg};${ag_min};${ag_avg}" >> "$OUTPUT_CSV"
done

echo "--------------------------------------------------------"
echo "¡Tarea 6 finalizada con éxito! Resultados guardados en '$OUTPUT_CSV'."