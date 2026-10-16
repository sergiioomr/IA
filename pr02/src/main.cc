/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Inteligencia Artificial
 * @file main.cc
 * @author Sergio Molina Ríos (alu0101718194@ull.edu.es)
 * @date 2026-10-12
 * @brief 
 * 
 */

#include "../include/ProblemPSFP.h"
#include "../include/algorithms.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Uso: " << argv[0] << " <archivo_de_entrada>" << std::endl;
        return EXIT_FAILURE;
    }

    ProblemPSFP problem(argv[1]);

    // Probar el algoritmo de búsqueda heurística
    std::vector<int> best_permutation = HeuristicNEH(problem);

    // Imprimir la mejor permutación encontrada
    std::cout << "Mejor permutación encontrada NEH: ";
    for (int job : best_permutation) {
        std::cout << job << " ";
    }
    std::cout << std::endl;

    std::cout << "Makespan de la mejor permutación NEH: " << problem.CalculateMakespan(best_permutation) << std::endl;

    // Probar el algoritmo de búsqueda aleatoria
    int max_evaluations = 100000; // Número máximo de evaluaciones
    std::vector<int> best_permutation_random = RandomSearch(problem, max_evaluations);

    // Imprimir la mejor permutación encontrada
    std::cout << "Mejor permutación encontrada randomsearch: ";
    for (int job : best_permutation_random) {
        std::cout << job << " ";
    }
    std::cout << std::endl;

    std::cout << "Makespan de la mejor permutación randomSearch: " << problem.CalculateMakespan(best_permutation_random) << std::endl;
    return 0;
}