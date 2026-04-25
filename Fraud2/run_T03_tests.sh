#!/bin/bash
# =============================================================================
# run_T03_tests.sh
# Script para ejecutar TODOS los tests de integración T03 (131-141) de Fraud2
#
# USO:
#   chmod +x run_T03_tests.sh
#   ./run_T03_tests.sh
#
# REQUISITOS:
#   - El binario ya compilado en:  build/Fraud2
#   - El archivo de dataset en:    ../Datasets/dataP2/princeton_names.loc
#     (ajusta DATASET más abajo si tu ruta es diferente)
#   - valgrind instalado (opcional, para los checks de memoria)
# =============================================================================

# -----------------------------------------------------------
# CONFIGURACIÓN — ajusta estas rutas si es necesario
# -----------------------------------------------------------
BINARY="../build/Fraud2"
DATASET="../Datasets/dataP2/princeton_names.loc"
VALGRIND_OPTS="--leak-check=full --error-exitcode=1 -q"

# -----------------------------------------------------------
# Colores para la salida
# -----------------------------------------------------------
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
CYAN='\033[0;36m'
NC='\033[0m' # sin color

# -----------------------------------------------------------
# Contadores
# -----------------------------------------------------------
TOTAL=0
PASSED=0
FAILED=0

# -----------------------------------------------------------
# Función auxiliar: ejecuta un test y compara salida
#
#   run_test  <id> <descripción> <salida_esperada_en_stdout>
#             <salida_esperada_en_stderr> <args_del_binario...>
#
# Para tests que esperan salida en stderr (errores), pasa
# el expected_stdout vacío y rellena expected_stderr.
# -----------------------------------------------------------
run_test() {
    local id="$1"
    local desc="$2"
    local expected_stdout="$3"
    local expected_stderr="$4"
    shift 4
    local args=("$@")

    TOTAL=$((TOTAL + 1))

    # Ejecutar el binario capturando stdout y stderr por separado
    actual_stdout=$("$BINARY" "${args[@]}" 2>/tmp/fraud2_stderr_tmp)
    exit_code=$?
    actual_stderr=$(cat /tmp/fraud2_stderr_tmp)

    # Comparar stdout
    stdout_ok=true
    if [ -n "$expected_stdout" ]; then
        if [ "$actual_stdout" != "$expected_stdout" ]; then
            stdout_ok=false
        fi
    fi

    # Comparar stderr (solo comprobamos que NO esté vacío si se espera error)
    stderr_ok=true
    if [ "$expected_stderr" = "NONEMPTY" ]; then
        if [ -z "$actual_stderr" ]; then
            stderr_ok=false
        fi
    fi

    if $stdout_ok && $stderr_ok; then
        echo -e "${GREEN}[PASS]${NC} T03-${id}: ${desc}"
        PASSED=$((PASSED + 1))
    else
        echo -e "${RED}[FAIL]${NC} T03-${id}: ${desc}"
        if ! $stdout_ok; then
            echo -e "  ${YELLOW}STDOUT esperado:${NC}"
            echo "$expected_stdout" | head -20 | sed 's/^/    /'
            echo -e "  ${YELLOW}STDOUT obtenido:${NC}"
            echo "$actual_stdout"   | head -20 | sed 's/^/    /'
        fi
        if ! $stderr_ok; then
            echo -e "  ${YELLOW}Se esperaba mensaje en stderr pero estaba vacío${NC}"
        fi
        FAILED=$((FAILED + 1))
    fi
}

# -----------------------------------------------------------
# Función auxiliar: test de valgrind (sin fugas de memoria)
# -----------------------------------------------------------
run_valgrind_test() {
    local id="$1"
    local desc="$2"
    shift 2
    local args=("$@")

    TOTAL=$((TOTAL + 1))

    if ! command -v valgrind &>/dev/null; then
        echo -e "${YELLOW}[SKIP]${NC} T03-${id} valgrind: valgrind no instalado"
        return
    fi

    valgrind $VALGRIND_OPTS "$BINARY" "${args[@]}" \
        >/dev/null 2>/tmp/fraud2_valgrind_tmp
    exit_code=$?

    if [ $exit_code -eq 0 ]; then
        echo -e "${GREEN}[PASS]${NC} T03-${id} (valgrind): ${desc} — SIN FUGAS"
        PASSED=$((PASSED + 1))
    else
        echo -e "${RED}[FAIL]${NC} T03-${id} (valgrind): ${desc} — FUGAS DETECTADAS"
        cat /tmp/fraud2_valgrind_tmp | sed 's/^/    /'
        FAILED=$((FAILED + 1))
    fi
}

# =============================================================================
# COMPROBACIONES PREVIAS
# =============================================================================
echo -e "${CYAN}============================================================${NC}"
echo -e "${CYAN}  Tests de integración T03 — Fraud2${NC}"
echo -e "${CYAN}============================================================${NC}"
echo ""

if [ ! -f "$BINARY" ]; then
    echo -e "${RED}ERROR: No se encuentra el binario: $BINARY${NC}"
    echo "Compílalo primero con:  make  (o el comando habitual de tu proyecto)"
    exit 1
fi

if [ ! -f "$DATASET" ]; then
    echo -e "${RED}AVISO: No se encuentra el dataset: $DATASET${NC}"
    echo "Algunos tests de integración fallarán. Ajusta la variable DATASET en este script."
    echo ""
fi

mkdir -p tests/output

# =============================================================================
# T03 — Tests de integración (131 – 141)
# =============================================================================

echo -e "${CYAN}--- T03: Sin argumentos / argumentos incorrectos ---${NC}"

# -----------------------------------------------------------
# 131: Sin ningún argumento
# Descripción: Running without arguments.
# El programa debe mostrar ayuda en stderr y salir con código != 0
# -----------------------------------------------------------
run_test 131 "Sin argumentos — muestra ayuda en stderr" \
    "" \
    "NONEMPTY"
    # sin args

# -----------------------------------------------------------
# 132: Solo un argumento (no suficientes)
# Descripción: Running without enough arguments.
# -----------------------------------------------------------
run_test 132 "Un argumento — no suficientes argumentos" \
    "" \
    "NONEMPTY" \
    "5"

# -----------------------------------------------------------
# 133: Parámetros numéricos correctos pero fichero inexistente
# Descripción: Correct numeric parameters but a non-existent location file.
# -----------------------------------------------------------
run_test 133 "Fichero .loc inexistente" \
    "" \
    "NONEMPTY" \
    "5" "0" "3" "no_existe.loc"

# -----------------------------------------------------------
# 134: Rango de semillas vacío (minSeed > maxSeed)
# Descripción: empty interval for seed. No clustering is done, nothing happen.
# No hay salida en stdout (no se hace ningún clustering)
# -----------------------------------------------------------
run_test 134 "Rango de semillas vacío (minSeed > maxSeed) — sin salida" \
    "" \
    "" \
    "5" "3" "0" "$DATASET"

# -----------------------------------------------------------
# 135: Solo una semilla — un clustering
# Descripción: interval for only one seed. Only one clustering is done.
# build/Fraud2 5 0 0 ../Datasets/dataP2/princeton_names.loc
# -----------------------------------------------------------
EXPECTED_135="Clustering 0:
K=5
Sum of within-cluster variances: 194.455556
Number of iterations: 3
"
run_test 135 "Una semilla (seed=0), K=5 — un clustering" \
    "$EXPECTED_135" \
    "" \
    "5" "0" "0" "$DATASET"

# -----------------------------------------------------------
# 136: Solo una semilla diferente — un clustering
# Descripción: interval for only one seed. Only one clustering is done.
# build/Fraud2 5 1 1 ../Datasets/dataP2/princeton_names.loc
# -----------------------------------------------------------
EXPECTED_136="Clustering 0:
K=5
Sum of within-cluster variances: 233.319889
Number of iterations: 3
"
run_test 136 "Una semilla (seed=1), K=5 — un clustering" \
    "$EXPECTED_136" \
    "" \
    "5" "1" "1" "$DATASET"

# -----------------------------------------------------------
# 137: Tres clusterings K=4
# Descripción: interval for three clustering, K=4.
# build/Fraud2 4 0 2 ../Datasets/dataP2/princeton_names.loc
# -----------------------------------------------------------
EXPECTED_137="Clustering 0:
K=4
Sum of within-cluster variances: 130.516667
Number of iterations: 4

Clustering 1:
K=4
Sum of within-cluster variances: 188.990000
Number of iterations: 3

Clustering 2:
K=4
Sum of within-cluster variances: 204.290000
Number of iterations: 4
"
run_test 137 "Tres semillas (0-2), K=4 — tres clusterings ordenados" \
    "$EXPECTED_137" \
    "" \
    "4" "0" "2" "$DATASET"

# -----------------------------------------------------------
# 138: K=1 — un único cluster
# Descripción: interval for three clustering. K=1. Ties only one cluster.
# build/Fraud2 1 0 2 ../Datasets/dataP2/princeton_names.loc
# -----------------------------------------------------------
EXPECTED_138="Clustering 0:
K=1
Sum of within-cluster variances: 649.869048
Number of iterations: 2

Clustering 1:
K=1
Sum of within-cluster variances: 649.869048
Number of iterations: 2

Clustering 2:
K=1
Sum of within-cluster variances: 649.869048
Number of iterations: 2
"
run_test 138 "Tres semillas (0-2), K=1 — empates, mismo sumWCV" \
    "$EXPECTED_138" \
    "" \
    "1" "0" "2" "$DATASET"

# -----------------------------------------------------------
# 139: K=3, mejor clustering con it=4
# Descripción: interval for three clustering. K=3. Best cluster with it=4.
# build/Fraud2 3 0 2 ../Datasets/dataP2/princeton_names.loc
# -----------------------------------------------------------
EXPECTED_139="Clustering 0:
K=3
Sum of within-cluster variances: 180.130476
Number of iterations: 4

Clustering 1:
K=3
Sum of within-cluster variances: 212.519048
Number of iterations: 3

Clustering 2:
K=3
Sum of within-cluster variances: 312.819048
Number of iterations: 3
"
run_test 139 "Tres semillas (0-2), K=3 — mejor con it=4" \
    "$EXPECTED_139" \
    "" \
    "3" "0" "2" "$DATASET"

# -----------------------------------------------------------
# 140: K=3, mejor clustering con it=2
# Descripción: interval for three clustering. K=3. Best clustering with it=2.
# build/Fraud2 3 3 5 ../Datasets/dataP2/princeton_names.loc
# -----------------------------------------------------------
EXPECTED_140="Clustering 0:
K=3
Sum of within-cluster variances: 176.711905
Number of iterations: 2

Clustering 1:
K=3
Sum of within-cluster variances: 180.130476
Number of iterations: 4

Clustering 2:
K=3
Sum of within-cluster variances: 319.219048
Number of iterations: 3
"
run_test 140 "Tres semillas (3-5), K=3 — mejor con it=2" \
    "$EXPECTED_140" \
    "" \
    "3" "3" "5" "$DATASET"

# -----------------------------------------------------------
# 141: K=5, tres clusterings
# Descripción: interval for three clustering. K=5. Three registered clusterings.
# build/Fraud2 5 0 3 ../Datasets/dataP2/princeton_names.loc
# -----------------------------------------------------------
EXPECTED_141="Clustering 0:
K=5
Sum of within-cluster variances: 194.455556
Number of iterations: 3

Clustering 1:
K=5
Sum of within-cluster variances: 233.319889
Number of iterations: 3

Clustering 2:
K=5
Sum of within-cluster variances: 250.044571
Number of iterations: 3
"
run_test 141 "Cuatro semillas (0-3), K=5 — tres clusterings distintos" \
    "$EXPECTED_141" \
    "" \
    "5" "0" "3" "$DATASET"

# =============================================================================
# TESTS VALGRIND (memoria) — mismos argumentos, sin salida esperada
# =============================================================================
echo ""
echo -e "${CYAN}--- T03 valgrind: comprobación de fugas de memoria ---${NC}"

run_valgrind_test 131 "Sin argumentos"
run_valgrind_test 132 "Un argumento"                           "5"
run_valgrind_test 133 "Fichero inexistente"                    "5" "0" "3" "no_existe.loc"
run_valgrind_test 134 "Rango vacío"                            "5" "3" "0" "$DATASET"
run_valgrind_test 135 "Una semilla K=5 seed=0"                 "5" "0" "0" "$DATASET"
run_valgrind_test 136 "Una semilla K=5 seed=1"                 "5" "1" "1" "$DATASET"
run_valgrind_test 137 "Tres semillas K=4"                      "4" "0" "2" "$DATASET"
run_valgrind_test 138 "Tres semillas K=1"                      "1" "0" "2" "$DATASET"
run_valgrind_test 139 "Tres semillas K=3 seeds 0-2"            "3" "0" "2" "$DATASET"
run_valgrind_test 140 "Tres semillas K=3 seeds 3-5"            "3" "3" "5" "$DATASET"
run_valgrind_test 141 "Cuatro semillas K=5"                    "5" "0" "3" "$DATASET"

# =============================================================================
# RESUMEN FINAL
# =============================================================================
echo ""
echo -e "${CYAN}============================================================${NC}"
echo -e "  RESULTADO FINAL: ${GREEN}${PASSED} PASSED${NC} / ${RED}${FAILED} FAILED${NC} / Total: ${TOTAL}"
echo -e "${CYAN}============================================================${NC}"

if [ $FAILED -eq 0 ]; then
    echo -e "${GREEN}  ✓ Todos los tests T03 han pasado.${NC}"
    exit 0
else
    echo -e "${RED}  ✗ Hay ${FAILED} test(s) fallando.${NC}"
    echo ""
    echo "  PISTAS:"
    echo "  - Si falla el dataset: ajusta la variable DATASET en este script"
    echo "  - Si falla la salida: comprueba el formato exacto de cout en main.cpp"
    echo "  - Si falla valgrind:  revisa que DeallocateArrayClustering libera toda la memoria"
    exit 1
fi